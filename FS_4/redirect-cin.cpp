#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <cerrno>

void initialize(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
        exit(1);
    }

    // Open the file specified in argv[1]
    int file = open(argv[1], O_RDONLY);
    if (file == -1) {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
        exit(errno);
    }

    // Redirect standard input to the file
    if (dup2(file, STDIN_FILENO) == -1) {
        std::cerr << "Error redirecting standard input: " << strerror(errno) << std::endl;
        close(file);
        exit(errno);
    }

    // Close the file descriptor as it's no longer needed after duplication
    close(file);
}

int main(int argc, char** argv) {
    // Initialize to redirect input from the specified file
    initialize(argc, argv);

    // Read the input from redirected std::cin
    std::string input;
    std::cin >> input;

    // Reverse the string
    std::string reversed(input.rbegin(), input.rend());

    // Print the reversed string to standard output
    std::cout << reversed << std::endl;

    return 0;
}

