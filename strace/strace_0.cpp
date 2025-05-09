#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "syscall.h"

// Usage: ./strace_0 command [args...]
// Each time a syscall is intercepted, you must print its number, followed by a new line

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program> [args...]\n", argv[0]);
        return 0;
    }
    // child process will be traced
    pid_t child = fork();
    if (child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execve(argv[1], argv, NULL);
    } else {
        // Parent process
        int status;
        while (1) {
            wait(&status);
            if (WIFEXITED(status)) {
                break;
            }
            // Here you can add code to inspect the child's registers or memory
            ptrace(PTRACE_CONT, child, NULL, NULL);
        }
    }
    return (0);
}
