# Scan_utility
* Utility for scanning files in directory
* Written and tested on linux platform, results obtained on windows differ from those obtained on linux

## Problem
---

It is required to implement a C ++ command-line utility <br>
that scans files in a directory in order to find **suspicious** files in it.

### Within the framework of the task, 3 types of “suspicious” content in the file were identified:

1. JS suspicious: js file containing the line: ```<script>evil_script()</script>```
2. CMD suspicious: CMD/BAT file containing the line: ```rd /s /q "c:\windows"```
3. EXE suspicious: EXE/DLL file containing lines: ```CreateRemoteThread, CreateProcess```

### Upon completion of the utility, the user should be presented <br>
### with a scan report containing the following information:

* the total number of processed files;
* the number of detections for each type of **suspicious** content;
* the number of file analysis errors (for example, there are not enough rights to read the file);
* the runtime of the utility.

---

### Example

```cpp
>scan_util C:\Users\user\Downloads 



====== Scan result ====== 

Processed files: 150 

JS detects: 5 

CMD detects: 1 

EXE detects: 2 

Errors: 1 

Execution time: 00:00:31 

========================= 
```

### Technologies used:
* Programming language - C++
* std::filesystem - to travel the directory
* std::fstream - to work with files

### Main algorithm:
Knuth-Morrisph-Pratt algorithm was use to find **suspicious** lines <br>
in files.

### How to build:
Create directory ```build```, than open terminal and do this comands:
```cpp
>cd build
>cmake .. 
>cd ..
>cmake --build build
```
It will create the project in ```build```
```cpp
>./SCANNER <directory> //to run the utility
```
```cpp
>./RunUnitTests //to run tests
```

## Gratitude
Thanks to me for doing this project.



