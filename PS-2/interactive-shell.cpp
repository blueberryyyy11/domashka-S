#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstdlib>

void do_command(const std::vector<std::string>& args, bool silent) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        
        if (silent) {
           
            std::string log_file = std::to_string(getpid()) + ".log";
            int fd = open(log_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);
        }

        
        std::vector<char*> exec_args;
        for (const auto& arg : args) {
            exec_args.push_back(const_cast<char*>(arg.c_str()));
        }
        exec_args.push_back(nullptr);

       
        std::string current_path = getenv("PATH");
        std::string new_path = "PATH=." + current_path;
        char* envp[] = { const_cast<char*>(new_path.c_str()), nullptr };

        
        execvp(exec_args[0], exec_args.data());

       
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
      
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
        }
    }
}

int main() {
    std::string input;

    while (true) {
        std::cout << "shell> ";
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        
        std::istringstream iss(input);
        std::vector<std::string> args;
        std::string arg;
        while (iss >> arg) {
            args.push_back(arg);
        }

        if (args.empty()) {
            continue;
        }

    
        if (args[0] == "exit") {
            break;
        }

     
        bool silent = false;
        if (args[0] == "silent") {
            silent = true;
            args.erase(args.begin());
        }

        if (!args.empty()) {
            do_command(args, silent);
        }
    }

    return EXIT_SUCCESS;
}

