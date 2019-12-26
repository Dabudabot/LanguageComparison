#include "ntifs.h"
#include "ntddk.h"

#define FILES_AMOUNT 1000
#define FOLDERS_AMOUNT 50
#define PREFIX L"\\??\\C:\\Data\\"

NTSYSAPI 
NTSTATUS
NTAPI
NtDelayExecution(
  IN BOOLEAN              Alertable,
  IN PLARGE_INTEGER       DelayInterval );

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

NTSTATUS RtlIntegerToChar
 (
  ULONG value,
  ULONG base,
  ULONG length,
  PCHAR str
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

HANDLE open(SHORT folder_num, SHORT file_num)
{
    UNICODE_STRING string;
	WCHAR buffer[24];
	UNICODE_STRING number;
	WCHAR numberBuffer[4];
	
    OBJECT_ATTRIBUTES oa;
    HANDLE file;
    IO_STATUS_BLOCK io;
    LARGE_INTEGER fileSize;
	
	number.Buffer = numberBuffer;
	number.MaximumLength = 8;
	
    fileSize.QuadPart = 0;
	
	string.Buffer = buffer;
	string.Length = 0;
	string.MaximumLength = 48;
	
	RtlZeroMemory(string.Buffer, string.MaximumLength);
	RtlAppendUnicodeToString(&string, PREFIX);
	RtlIntegerToUnicodeString(folder_num, 0, &number);
	RtlAppendUnicodeStringToString(&string, &number);
	RtlAppendUnicodeToString(&string, L"\\");
	RtlIntegerToUnicodeString(file_num, 0, &number);
	RtlAppendUnicodeStringToString(&string, &number);
	
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
	WCHAR numberBuffer[20];
	
	number.Buffer = numberBuffer;
	number.MaximumLength = 20;
	
    RtlInitUnicodeString(&string, Message);
    RtlIntegerToUnicodeString(time, 0, &number);
    NtDisplayString(&string);
    NtDisplayString(&number);
}

ULONG read(HANDLE f)
{
	IO_STATUS_BLOCK io;
	CHAR buffer[4];
	ULONG result;
	
	RtlZeroMemory(buffer, 4);
	NtReadFile(f, NULL, NULL, NULL, &io, buffer, 4, NULL, NULL);
	
	RtlCharToInteger(buffer, 10, &result);
	
	return result;
}

void write(HANDLE f, ULONG value)
{
	CHAR buffer[5];
	
	IO_STATUS_BLOCK io;
	LARGE_INTEGER offset;
	
	offset.QuadPart = 0;
	
	RtlIntegerToChar(value, 0, 5, buffer);
	NtWriteFile(f, NULL, NULL, NULL, &io, buffer, 5, &offset, NULL);
}

void NtProcessStartup(void* StartupArgument)
{
   SHORT i, j, k;
   ULONG n1, n2, total;
   HANDLE f1, f2;
   LARGE_INTEGER time1, time2, delay10, delay5;

   delay10.QuadPart = 600000000;
   delay5.QuadPart  = 300000000;
   total = 0;

   writeLn(L"Started", 0);

   NtDelayExecution(TRUE, &delay10);

   for (k = 0; k < FOLDERS_AMOUNT; k++)
   {
        NtQuerySystemTime(&time1); // time in 100 nanosecods interval

        for (i = 0; i < FILES_AMOUNT-1; i++)
        {
            f1 = open(k, i);
            n1 = read(f1);

            for (j = i + 1; j < FILES_AMOUNT; j++)
            {
                f2 = open(k, j);
                n2 = read(f2);

                if (n1 > n2)
                {
                    write(f2, n1);
                    n1 = n2;
                }

                NtClose(f2);
            }
            
            write(f1, n1);
            NtClose(f1);
        }

        NtQuerySystemTime(&time2);

        total += (ULONG) (time2.QuadPart - time1.QuadPart) / 10000;

        writeLn(L"Folder: ", (ULONG)k);
        writeLn(L"  elapsed time: ", (ULONG) (time2.QuadPart - time1.QuadPart) / 10000);
        writeLn(L"  average time: ", total / k);

        NtDelayExecution(TRUE, &delay5);
   }

   DbgBreakPoint(); // in order to see result (or we can wait on keyborad input)
   //waitOnInput();
   
   NtTerminateProcess(NtCurrentProcess(), 0);
}

