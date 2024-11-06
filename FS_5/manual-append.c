#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];
    int fd1 = open(filepath, O_WRONLY | O_CREAT, 0644);
    if (fd1 < 0) {
        perror("Error opening file");
        return 1;
    }

    // Duplicate the file descriptor
    int fd2 = dup(fd1);
    if (fd2 < 0) {
        perror("Error duplicating file descriptor");
        close(fd1);
        return 1;
    }

    // Write first line using fd1
    const char *line1 = "first line\n";
    if (write(fd1, line1, sizeof("first line\n") - 1) == -1) {
        perror("Error writing first line");
        close(fd1);
        close(fd2);
        return 1;
    }

    // Write second line using fd2
    const char *line2 = "second line\n";
    if (write(fd2, line2, sizeof("second line\n") - 1) == -1) {
        perror("Error writing second line");
        close(fd1);
        close(fd2);
        return 1;
    }

    // Close the file descriptors
    close(fd1);
    close(fd2);

    return 0;
}

