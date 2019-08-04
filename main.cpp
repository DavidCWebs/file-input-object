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
	int inputFromStdinFile()
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

	int input(std::string line)
	{
		int score;
		std::istringstream ss(line);
		while (ss >> score) {
			scores.push_back(score);
		}
		return 0;
	}

	friend std::ostream& operator<<(std::ostream& inStream, Record s)
	{
		inStream << "Record: ";
		for (auto& el : s.scores) {
			inStream << el << " ";
		}
		inStream << '\n';
		return inStream;
	}
	
	int& operator[](int i)
	{
		std::cout << "i = " << i << '\n';
		if (!isValidIndex(i))
			throw IndexOutOfBoundsException{};
		return scores[i];
	}

	bool isValidIndex(int i)
	{
		return (i >= 0 && i < (int)scores.size());
	}
};

int main()
{
	// Create a vector of *Record unique pointers
	std::vector<std::unique_ptr<Record>> records;
	while (1) {
		// Make a unique pointer to a Record
		auto s = std::make_unique<Record>();

		// Input data to this object - reset object if EOF is indicated
		if (s->inputFromStdinFile() == -1) {
			s.reset();
			break;
		}

		// Move the object to the array
		records.push_back(std::move(s));
	}
	
	// Reset stdin to terminal	
	std::fstream in("/dev/tty");
	std::cin.rdbuf(in.rdbuf());
     
	for (auto& record : records) {
		std::cout << *record;
	}
	
	try {
		int index;
		// Output to tty
		std::streambuf *backup = std::cout.rdbuf();
		std::ofstream out("/dev/tty");
		std::cout.rdbuf(out.rdbuf());

		std::cout << "Enter index: ";
		std::cin >> index;
		
		std::cout.rdbuf(backup); // write to original cout
		Record s = *(records[0]);
		std::cout << "value: " << s[index] << '\n';
	} catch (const IndexOutOfBoundsException& e) {
		std::cout << "ERROR: index out of bounds." << '\n';
	}
}
