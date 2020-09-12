Objects From Stdin: C++
=======================
This project is an example of how `stdin` data can be used to construct objects in C++ under Linux. 

Data is input via `stdin` either through the terminal or by means of file redirection.

You could use this as boilerplate for importing data stored in a file into C++ data structures. In this case, data is imported on a line-by-line basis, with each line providing data for a separate object.

A vector of `unique_ptr` to objects is used to store objects.

Use Case
--------
I put this project together to better understand input streams in C++. The aim was to accept input by means of file redirection _or_ terminal input. I also wanted to switch to terminal input for additional interaction in the event of file redirection input of the main body of data.

One interesting result of this approach is that you can input data either by means of file redirection or by means of terminal input in the default `stdin` way.

File Redirection
----------------
Redirection in Linux involves changing standard input/output devices.

Usually, the standard input device `stdin` is the keyboard and the standard output device `stdout` is the screen.

This means that in C++ `std::cin >> input;` accepts input from the keyboard, and `std::cout << output` outputs data to the screen.

To input data from a file, redirection can be used:

```bash
./myProg < input.txt
```
In this case, the shell streams in the contents of `input.txt` to stdin instead of accepting keyboard input from the terminal.

Terminal Input
--------------
If you run the binary file without supplying data by means of file redirection, the user is required to supply data at the terminal. Data is entered:

* Line-by-line, with each line representing a separate object (`\n` delineates objects).
* Individual scores are separated by spaces.
* Input is ended by entering Ctrl-D which is the Linux end-of-file signal.

Switching from File Redirection to Terminal
-------------------------------------------
When input is redirected from a file, `std::cin` refers to the redirected file. If you need to get input from the terminal at a later stage in the programme, you can assign another input buffer using `std::cin.rdbuf()`.

```C++
// Define an input stream as the terminal for the current process (/dev/tty)
std::fstream in("/dev/tty");

// Set the streambuf of std::cin as the streambuf of /dev/tty.
std::cin.rdbuf(in.rdbuf());

// stdin is now /dev/tty - keyboard input.
```

For a working example, see [main.cpp line 22][1].

`std::fstream` is the input/output file stream class. The code above associates the `/dev/tty` (terminal device) stream with the variable `in`.

The next line sets the `std::streambuf` for `std::cin` to the `std::streambuf` of `in` which has been set to `dev/tty`. 

The function `std::ios::rdbuf()` is used to get and set a stream buffer:

```C++
streambuf* rdbuf() const; // get - returns a pointer to the stream buffer of the object associated with stream
streambuf* rdbuf (streambuf* sb); // sets the object pointed at by sb, clears error flags.
```
Headers: `<ios> <iostream>`.

Streams & Stream Buffers
------------------------
A _stream_ is a communication channel between a programme and it's environment.

Streams involve data flowing from a source to a destination - for example, data may flow from the programme to the screen, or may be read from the user's keyboard into the programme.

A _stream buffer_ is a memory buffer for the stream - the `streambuf` is an interface that defines a mapping from a stream to a device, file or memory. 

* The stream is responsible for converting data into an appropriate format.
* The streambuf actually communicates the data.


References
----------
* [fstream][2]
* [Controlling terminal: `/dev/tty`][3]
* [Stream Buffers][3]: YouTube, Bo Qian
* [Output with ostream & ios][5]

[1]: main.cpp#L22
[2]: http://www.cplusplus.com/reference/fstream/fstream/
[3]: http://tldp.org/HOWTO/Text-Terminal-HOWTO-7.html#ss7.3
[4]: https://www.youtube.com/watch?v=HwtFcT-ueu8
[5]: https://www.learncpp.com/cpp-tutorial/183-output-with-ostream-and-ios/
