#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " source-file destination-file\n";
        return 1;
    }

    const char* sourcePath = argv[1];
    const char* destPath = argv[2];

    int srcFile = open(sourcePath, O_RDONLY);
    if (srcFile < 0) {
        std::cerr << "Error opening source file " << sourcePath << ": " << strerror(errno) << "\n";
        return errno;
    }

    // Open destination file
    int destFile = open(destPath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (destFile < 0) {
        std::cerr << "Error opening destination file " << destPath << ": " << strerror(errno) << "\n";
        close(srcFile);
        return errno;
    }

    char buffer[4096];
    ssize_t bytesRead;
    ssize_t totalBytes = 0, dataBytes = 0, holeBytes = 0;

    while ((bytesRead = read(srcFile, buffer, sizeof(buffer))) > 0) {
        ssize_t bytesWritten = 0;

        // Check for holes by finding empty (zeroed) segments in the buffer
        bool isHole = true;
        for (ssize_t i = 0; i < bytesRead; ++i) {
            if (buffer[i] != 0) {
                isHole = false;
                break;
            }
        }

        if (isHole) {
            // Create a hole in the destination file by seeking
            off_t hole = lseek(destFile, bytesRead, SEEK_CUR);
            if (hole < 0) {
                std::cerr << "Error creating hole: " << strerror(errno) << "\n";
                close(srcFile);
                close(destFile);
                return errno;
            }
            holeBytes += bytesRead;
        } else {
            // Write data segment
            bytesWritten = write(destFile, buffer, bytesRead);
            if (bytesWritten < 0) {
                std::cerr << "Error writing data: " << strerror(errno) << "\n";
                close(srcFile);
                close(destFile);
                return errno;
            }
            dataBytes += bytesWritten;
        }
        totalBytes += bytesRead;
    }

    if (bytesRead < 0) {
        std::cerr << "Error reading source file: " << strerror(errno) << "\n";
    } else {
        std::cout << "Successfully copied " << totalBytes << " bytes (data: " << dataBytes << ", hole: " << holeBytes << ").\n";
    }

    close(srcFile);
    close(destFile);
    return 0;
}

