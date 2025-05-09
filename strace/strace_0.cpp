#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/user.h> // For user_regs_struct
#include "syscall.h"

// Usage: ./strace_0 command [args...]
// Each time a syscall is intercepted, you must print its number, followed by a new line

// int main(int argc, char* argv[])
// {
//     if (argc < 2) {
//         fprintf(stderr, "Usage: %s <program> [args...]\n", argv[0]);
//         return 0;
//     }
//     // child process will be traced
//     pid_t child = fork();
//     if (child == 0) {
//         ptrace(PTRACE_TRACEME, 0, NULL, NULL);
//         execve(argv[1], argv, NULL);
//     } else {
//         // Parent process
//         int status;
//         while (1) {
//             wait(&status);
//             if (WIFEXITED(status)) {
//                 break;
//             }
//             // Here you can add code to inspect the child's registers or memory
//             ptrace(PTRACE_CONT, child, NULL, NULL);
//         }
//     }
//     return (0);
// }

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s command [args...]\n", argv[0]);
        return 1;
    }

    pid_t child = fork();
    if (child == 0) {
        // Child process: request tracing and execute command
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        fflush(stdout); // Ensure the output is flushed before execvp
        execvp(argv[1], &argv[1]);
        perror("execvp failed");
        return 1; // execvp failed
    } else {
        // Parent process: trace system calls
        int status;
        struct user_regs_struct regs;

        waitpid(child, &status, 0);
        while (!WIFEXITED(status)) {
            ptrace(PTRACE_SYSCALL, child, NULL, NULL);
            waitpid(child, &status, 0);

            ptrace(PTRACE_GETREGS, child, NULL, &regs);
            printf("%lld\n", regs.orig_rax); // Print syscall number
            fflush(stdout); // Ensure syscall output is printed immediately

            ptrace(PTRACE_SYSCALL, child, NULL, NULL);

        }
    }
    return 0;
}