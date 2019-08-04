Objects From Stdin: C++
=======================
This project is an example of how `stdin` data can be used to construct objects in C++ under Linux. 

Data is input via `stdin` either through the terminal or by means of file redirection.

You could use this as boilerplate for importing data stored in a file into C++ data structures. In this case, data is imported on a line-by-line basis, with each line providing data for a separate object.

A vector of `unique_ptr` to objects is used to store objects.

Use Case
--------
I put this project together to better understand input streams in C++. I don't know if there is a practical use case. The aim was to accept input by means of file redirection _or_ terminal input. I also wanted to switch to terminal input for additional interaction in the event of file redirection input of the main body of data.

One interesting result of this approach is that you can input data either by means of file redirection or by means of terminal input in the default `stdin` way.

File Redirection
----------------
Redirection in Linux involves changing standard input/output devices.

Usually, the standard input device `stdin` is the keyboard and the standard output device `stdout` is the screen.

This means that in C++ `std::cin >> input;` accepts input from the keyboard, and `std::cout >> output` outputs data to the screen.

To input data from a file, redirection can be used:

```bash
./myProg < input.txt
```
In this case, the shell streams in the contents of `input.txt` to stdin instead of typing input at the terminal.

Terminal Input
--------------
If you run the binary file without supplying data by means of file redirection, the user is required to supply data at the terminal. Data is entered:

* Line-by-line, with each line representing a separate object (`\n` delineates objects).
* Individual scores are separated by spaces.

Switching from File Redirection to Terminal
-------------------------------------------

