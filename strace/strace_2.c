#define _GNU_SOURCE
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/user.h>
#include "syscalls.h"

// Print both string = hexadecimal

syscall_t ;

int main(int argc, char *argv[]) {
    syscall_t const syscalls_64_g;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t child = fork();
    if (child == -1){
        perror("fork failed");
        return EXIT_FAILURE;
    }
    if (child == 0) {
        // Child process: request tracing and execute command
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execv(argv[1], &argv[1]);
        perror("execv failed");
        return EXIT_FAILURE;
    } else {
        // Parent process: trace system calls
        int status;

        waitpid(child, &status, 0);
        // this ptrace was the infinite loop problem (dont put syscall here)
        ptrace(PTRACE_SETOPTIONS, child, NULL, PTRACE_O_TRACESYSGOOD);

        while (!WIFEXITED(status)) {
            ptrace(PTRACE_SYSCALL, child, NULL, NULL);

            if (WIFEXITED(status)) break;

            if (WIFSTOPPED(status))
            {
                // if (ptrace(child, NULL, &syscall) == -1)
                {
                    perror("ptrace GETREGS failed");
                    return EXIT_FAILURE;
                }
                // here is
                printf("%lld\n", syscall_t);
            }
        }
    }
    return EXIT_SUCCESS;
}