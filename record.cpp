#include "record.h"

/**
 * Designed to read stdin from a file redirect:
 * `./bin/main < input`
 *
 * There are better ways of processing data from a file (e.g. use fstream to read
 * from file), but this is an exercise that riffs on accepting a redirected file
 * as stdin.
 * */
int Record::inputFromStdin()
{
	// Discard leading whitespace from input stream
	std::cin >> std::ws;

	// Put the line into a string
	std::string line;
	getline(std::cin, line);

	// If trying to read a character past the end of the file,
	// return -1 so that the created object can be reset. 
	if (std::cin.eof())
		return -1;
	input(line);
	return 0;
}

int Record::input(std::string line)
{
	int score;
	std::istringstream ss(line);
	while (ss >> score) {
		scores.push_back(score);
	}
	return 0;
}

int& Record::operator[](int i)
{
	std::cout << "i = " << i << '\n';
	if (!isValidIndex(i))
		throw IndexOutOfBoundsException{};
	return scores[i];
}

bool Record::isValidIndex(int i)
{
	return (i >= 0 && i < (int)scores.size());
}

std::ostream& operator<<(std::ostream& inStream, Record s)
{
	inStream << "Record: ";
	for (auto& el : s.scores) {
		inStream << el << " ";
	}
	inStream << '\n';
	return inStream;
}
