# LanguageComparison
My small attempt to compare native C application, C++ application, and Java application. The idea is not just to compare languages or algorithms but working with disk and filesystem with multiple io operations.

## Idea
It is all started from the statistics logged by TODO

image todo

I agree with such numbers, however, I have decided to code a simple way to compare performance on my own.
The idea was to check to just a running time of the algorithm on different languages, but working with a disk.
So, I came up with the solution to implement O(n^2) sorting algorithm on numbers inside the files.
We have a folder with 1000 files, each file contains a random unique number. The algorithm has to put the smallest number
to the first file, a larger number to the second file and so on.

To make results more precise: 
1. All work goes on VM and from a snapshot
2. Algorithms repeat sorting 50 times on different files.
3. Algorithms sleep first 10 minutes and 5 minutes after each folder to give VM enough time to wake up after snapshot
4. Pseudocode is equal for each language, however, for opening, reading and writing best practices for each language was used
    (eg. java and c++ use buffered streams but native C read and write a file in binary format)

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
1. Build Generator, Checker, and sorters (CPP, Java, NativeC)
2. Copy binaries to the virtual machine
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