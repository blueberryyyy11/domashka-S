#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

/**
 * @brief Securely deletes the file at the specified path.
 * @param filePath Path to the file to be deleted.
 * @return int 0 if successful, or an error code.
 */
int secureDelete(const char* filePath) {
    // Check if the file exists
    struct stat fileStat;
    if (stat(filePath, &fileStat) == -1) {
        std::cerr << "Error: File does not exist or cannot be accessed.\n";
        return errno;
    }

    // Open the file for writing
    int fd = open(filePath, O_WRONLY);
    if (fd == -1) {
        std::cerr << "Error: Could not open file for overwriting.\n";
        return errno;
    }

    // Overwrite the file with null characters
    off_t fileSize = fileStat.st_size;
    char nullChar = '\0';
    for (off_t i = 0; i < fileSize; ++i) {
        if (write(fd, &nullChar, 1) == -1) {
            std::cerr << "Error: Could not overwrite file contents.\n";
            close(fd);
            return errno;
        }
    }

    // Close the file
    if (close(fd) == -1) {
        std::cerr << "Error: Could not close the file.\n";
        return errno;
    }

    // Remove the file from the filesystem
    if (unlink(filePath) == -1) {
        std::cerr << "Error: Could not delete the file.\n";
        return errno;
    }

    std::cout << "File securely deleted.\n";
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file-to-erase>\n";
        return 1;
    }

    const char* filePath = argv[1];
    return secureDelete(filePath);
}

