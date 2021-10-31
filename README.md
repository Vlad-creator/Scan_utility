# Scan_utility
Utility for scanning files in directory

## Problem
---

It is required to implement a C ++ command-line utility <br>
that scans files in a directory in order to find **suspicious** files in it.

### Within the framework of the task, 3 types of “suspicious” content in the file were identified:

1. JS suspicious: js file containing the line: '<script>evil_script()</script>'
2. CMD suspicious: CMD/BAT file containing the line: 'rd /s /q "c:\windows"'
3. EXE suspicious: EXE/DLL file containing lines: 'CreateRemoteThread, CreateProcess'

### Upon completion of the utility, the user should be presented <br>
### with a scan report containing the following information:

* the total number of processed files;
* the number of detections for each type of **suspicious** content;
* the number of file analysis errors (for example, there are not enough rights to read the file);
* the runtime of the utility.

---

### Example

```cpp
>scan_util C:\Users\user\Downloads <br> <br> <br>



====== Scan result ====== <br>

Processed files: 150 <br>

JS detects: 5 <br>

CMD detects: 1 <br>

EXE detects: 2 <br>

Errors: 1 <br>

Execution time: 00:00:31 <br>

========================= <br>
```

