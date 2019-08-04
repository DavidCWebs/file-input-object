#include <ostream>
#include "record.h"

int main()
{
	// Create a vector of *Record unique pointers
	std::vector<std::unique_ptr<Record>> records;
	while (1) {
		// Make a unique pointer to a Record
		auto s = std::make_unique<Record>();

		// Input data to this object - reset object if EOF is indicated
		if (s->inputFromStdin() == -1) {
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
		
		// This should print to screen even if output is redirected to file.
		std::cout << "Enter index: ";
		std::cin >> index;
		
		std::cout.rdbuf(backup); // Reset the original streambuf to std::cout
		Record s = *(records[0]);
		std::cout << "value: " << s[index] << '\n';
	} catch (const IndexOutOfBoundsException& e) {
		std::cout << "ERROR: index out of bounds." << '\n';
	}
}
