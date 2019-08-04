#ifndef RECORD_H
#define RECORD_H
#endif

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <limits>
#include <fstream>

class IndexOutOfBoundsException {};

class Record {
private:
	std::vector<int> scores;
public:
	int inputFromStdinFile();
	int input(std::string line);
	int& operator[](int i);
	bool isValidIndex(int i);
	friend std::ostream& operator<<(std::ostream& inStream, Record s);
};

