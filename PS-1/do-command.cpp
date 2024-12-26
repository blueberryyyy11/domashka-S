#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <sys/wait.h>
#include <unistd.h>

void do_command(char** argv) {
    auto start_time = std::chrono::high_resolution_clock::now();

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
       
        execvp(argv[0], argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
       
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;

        if (WIFEXITED(status)) {
            std::cout << "Command completed with " << WEXITSTATUS(status)
                      << " exit code and took " << duration.count() << " seconds." << std::endl;
        } else {
            std::cout << "Command did not complete successfully." << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [arguments...]" << std::endl;
        return EXIT_FAILURE;
    }

   
    std::vector<char*> args;
    for (int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    args.push_back(nullptr); // Null-terminate the argument list

    do_command(args.data());

    return EXIT_SUCCESS;
}

