#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    // check if both source and destination files are provided
    if (argc < 3) {
        std::cerr << "Error: Source and destination paths must be provided." << std::endl;
        std::cerr << "Usage: ./simple-copy <source-file> <destination-file>" << std::endl;
        return 1;
}
    
    // Open the source file for reading
    std::ifstream sourceFile(argv[1], std::ios::binary);
    if (!sourceFile) {
        std::cerr << "Error: Could not open source file " << argv[1] << std::endl;
        return 1;
    }
   
    // Open destination file for writing (overwrite if it exists)
    //  std::ios::binary is a flag used when opening files in binary mode. typically used with file streams like std::ifstream (input file stream) and std::ofstream (output file stream) to specify how the file should be read or written.
    std::ofstream destFile(argv[2], std::ios::binary);
    if (!destFile) {
        std::cerr << "Error: Could not open destination file " << argv[2] << std::endl;
    return 1;
    }

    // Copy the contents from source to destination
    // rdbuf() is a member function that returns the underlying stream buffer associated with a stream object. It’s commonly used with file streams to transfer data between input and output streams efficiently.
    destFile << sourceFile.rdbuf();

    sourceFile.close();
    destFile.close();

    std::cout << "File copied successfully from " << argv[1] << " to " << argv[2] << std::endl;
    return 0;
}
 
