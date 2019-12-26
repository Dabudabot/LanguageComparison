# LanguageComparison
My small attempt to compare native C application, C++ application and Java application. The idea is not just compare languages or algorithms but working with disk and filesystem with multiple io operations.

## Idea
It is all started from the statistics logged by TODO

image todo

I totaly agree with such numbers, however I have decided to code a simple way to compare performance by my own.
The idea was to check to just a running time of the algorithm on different languages, but working with disk.
So, I came up with solution to implement O(n^2) sorting algorithm on numbers inside the files.
We have folder with 1000 files, each file contains random unique number. Algorithm have to put the smallest number
to the first file, larger number to the second file and so on.

In order to make results more precise: 
1. All work goes on VM and from snapshot
2. Algorithms repeat sorting 50 times on different files.
3. Algorithms sleeps first 10 minutes and 5 minutes after each folder in order to give VM enouth time to wake up after snapshot
4. Pseudocode are equal for each language, however, for opening, reading and writing best practicies for each language was used
    (eg. java and c++ uses buffered streams but native C read and write file in binary format)

## Pseudocode
```
for each folder:
  get current time1
  for each file1 from 0 to amount-1:
    open file1
    read number1 from file1
    for each file2 from file1 to amount:
      open file2
      read number2 from file2
      if number1 > number2:
        write number1 to file2
        number1 = number2
      close file2
    write number1 to file1
    close file1
  get current time2
  time2 - time1
  calc average time
```

## Steps
0. Prereq: VM - Windows 7x64 with JDK 11.0.5 and Visual Redistributable
1. Build Generator, Checker and sorters (CPP, Java, NativeC)
2. Copy binaries to virtual machine
3. Run Generator
4. Make a snapshot
5. Run one of the sorters and note the results
6. revert to snapshot and repeat step 5 if needed

## Results
Language  | Average Time (seconds)
------------- | -------------
Java  | TODO
C++  | TODO 
Native C | TODO

images todo