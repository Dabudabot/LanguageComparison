#include "ntifs.h"
#include "ntddk.h"

#define FILES_AMOUNT 1000

NTSYSAPI
NTSTATUS
NTAPI
NtTerminateProcess(
  IN HANDLE               ProcessHandle OPTIONAL,
  IN NTSTATUS             ExitStatus
);

NTSYSAPI 
NTSTATUS
NTAPI
NtDisplayString(
	IN PUNICODE_STRING String
);

NTSTATUS 
NtWaitForSingleObject(
  IN HANDLE         Handle,
  IN BOOLEAN        Alertable,
  IN PLARGE_INTEGER Timeout
);

NTSYSAPI 
NTSTATUS
NTAPI
NtCreateEvent(
    OUT PHANDLE             EventHandle,
    IN ACCESS_MASK          DesiredAccess,
    IN POBJECT_ATTRIBUTES   ObjectAttributes OPTIONAL,
    IN EVENT_TYPE           EventType,
    IN BOOLEAN              InitialState
);

__kernel_entry NTSTATUS NtQuerySystemTime(
  OUT PLARGE_INTEGER SystemTime
);

typedef struct _KEYBOARD_INPUT_DATA {
  USHORT UnitId;
  USHORT MakeCode;
  USHORT Flags;
  USHORT Reserved;
  ULONG  ExtraInformation;
} KEYBOARD_INPUT_DATA, *PKEYBOARD_INPUT_DATA;

void waitOnInput()
{
    HANDLE hKeyBoard, hEvent;
    UNICODE_STRING skull, keyboard;
    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK Iosb;
    LARGE_INTEGER ByteOffset;
    KEYBOARD_INPUT_DATA kbData;

    RtlInitUnicodeString(&keyboard, L"\\Device\\KeyboardClass0");
    InitializeObjectAttributes(&ObjectAttributes, &keyboard, OBJ_CASE_INSENSITIVE, NULL, NULL);

    NtCreateFile(&hKeyBoard,
                SYNCHRONIZE | GENERIC_READ | FILE_READ_ATTRIBUTES,
                &ObjectAttributes,
                &Iosb,
                NULL,
                FILE_ATTRIBUTE_NORMAL,
                0,
                FILE_OPEN,FILE_DIRECTORY_FILE,
                NULL, 0);

    InitializeObjectAttributes(&ObjectAttributes, NULL, 0, NULL, NULL);
    NtCreateEvent(&hEvent, EVENT_ALL_ACCESS, &ObjectAttributes, 1, 0);

    while (TRUE)
    {
        NtReadFile(hKeyBoard, hEvent, NULL, NULL, &Iosb, &kbData, sizeof(KEYBOARD_INPUT_DATA), &ByteOffset, NULL);
        NtWaitForSingleObject(hEvent, TRUE, NULL);

        if (kbData.MakeCode == 0x01)    //ESC
        {
                break;
        }
    }
}

HANDLE open(SHORT file_num)
{
    UNICODE_STRING string;
    UNICODE_STRING number;
    UNICODE_STRING suffix;
    OBJECT_ATTRIBUTES oa;
    HANDLE file;
    IO_STATUS_BLOCK io;
    LARGE_INTEGER fileSize;

    fileSize.QuadPart = 0;

    RtlInitUnicodeString(&string, L"\\??\\C:\\Users\\Daulet.Tumbayev\\source\\repos\\LanguageComparison\\Data\\");
    RtlInitUnicodeString(&suffix, L".txt");
    RtlIntegerToUnicodeString(file_num, 0, &number);
    RtlAppendUnicodeStringToString(&string, &number);
    RtlAppendUnicodeStringToString(&string, &suffix);

    InitializeObjectAttributes(&oa, &string, OBJ_CASE_INSENSITIVE, NULL, NULL);

    NtCreateFile(&file,
                GENERIC_READ | GENERIC_WRITE | SYNCHRONIZE,
                &oa,
                &io,
                &fileSize,
                FILE_ATTRIBUTE_NORMAL,
                0,
                FILE_OPEN,
                FILE_SEQUENTIAL_ONLY | FILE_SYNCHRONOUS_IO_NONALERT,
                NULL, 0
    );

    return file;
}

void writeLn(LPWSTR Message, ULONG time)
{
    UNICODE_STRING string;
    UNICODE_STRING number;
    RtlInitUnicodeString(&string, Message);
    RtlIntegerToUnicodeString(time, 0, &number);
    NtDisplayString(&string);
    NtDisplayString(&number);
}

void NtProcessStartup(void* StartupArgument)
{
   SHORT i, j, n1, n2;
   HANDLE f1, f2;
   IO_STATUS_BLOCK io;
   LARGE_INTEGER time1, time2;

   NtQuerySystemTime(&time1); // time in 100 nanosecods interval

   for (i = 0; i < FILES_AMOUNT-1; i++)
   {
       f1 = open(i);
       NtReadFile(f1, NULL, NULL, NULL, &io, &n1, sizeof(SHORT), NULL, NULL);

       for (j = i + 1; j < FILES_AMOUNT; j++)
       {
           f2 = open(j);
           NtReadFile(f2, NULL, NULL, NULL, &io, &n2, sizeof(SHORT), NULL, NULL);

           if (n1 > n2)
           {
               NtWriteFile(f2, NULL, NULL, NULL, &io, &n1, sizeof(SHORT), NULL, NULL);
               n1 = n2;
           }

           NtClose(f2);
       }

       NtWriteFile(f1, NULL, NULL, NULL, &io, &n1, sizeof(SHORT), NULL, NULL);
       NtClose(f1);
   }

   NtQuerySystemTime(&time2);

   writeLn(L"Time spend: ", (ULONG) (time2.QuadPart - time1.QuadPart) / 10000);

   DbgBreakPoint(); // in order to see result (or we can wait on keyborad input)
   //waitOnInput();
   
   NtTerminateProcess(NtCurrentProcess(), 0);
}

