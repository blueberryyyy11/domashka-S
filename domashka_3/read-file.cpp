#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<file-path>" << std::endl;
        return 1;
    }
    
    // std::cerr: This outputs an error message to the standard error stream.
    // std::ifstream file(argv[1]);: This creates an input file stream named file and attempts to open the file specified by argv[1] (the first argument after the program name).

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    // std::getline reads a line from the file and stores it in the line variable. The loop continues until there are no more lines to read (i.e., until the end of the file is reached).
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    
    //  The bad() function indicates a serious problem with the file stream.
    if (file.bad()) {
        std::cerr << "Error: An error occured while reading the file." << std::endl;
        return 1;
    }

    return 0;

}
