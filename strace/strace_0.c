#define _GNU_SOURCE
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/reg.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/user.h>
#include "syscalls.h"

// Remove nested loops, look for a way to simplify logic



int do_trace(pid_t child);


/**
 * main - Entry point for the tracer program
 * @argc: Number of arguments passed
 * @argv: Array of arguments
 *
 * Description:
 * This function forks a new process and traces the system calls
 * executed by the child process.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        exit(1);
    }

    pid_t child = fork();
    
    if (child == 0) {
        return ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        kill(getpid(), SIGSTOP);
        execve(argv[1], argv + 1, NULL);
        perror("failed");
    } else {
        return trace(child);
    }
}

/**
 * trace - Traces system calls in the child process
 * @child: Process ID of the child
 *
 * Description:
 * This function waits for system calls in the child process
 * and retrieves register data using ptrace.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int do_trace(pid_t child)
{
    int status;
    int retval; /*used to debug*/
    struct user_regs_struct regs;

    // waitpid(child, &status, 0);
    // ptrace(PTRACE_SETOPTIONS, child, NULL, PTRACE_O_TRACESYSGOOD);

    while(1)
    {
        if (waitpid(child, &status, 0) == -1)
        {
            if (errno == ECHILD)
            {
                fprintf(stderr, "Child process has terminated.\n");
                break;
            }
            perror("waitpid failed");
            return EXIT_FAILURE;
        }
            if (WIFEXITED(status))
        {
            return 1;
        }

        const syscall_t *get_syscall(size_t nr) {
        // Assuming syscalls_64_g is defined and populated with syscall information
        for (size_t i = 0; syscalls_64_g[i].name != NULL; i++) {
        if (syscalls_64_g[i].nr == nr)
        {
            return &syscalls_64_g[i];
        }

        if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
        {
            perror("ptrace GETREGS failed");
            return EXIT_FAILURE;
        }


        // task 2
        int syscall = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_RAX);
        // retval = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * RAX);
        // fprintf(stderr, "syscall(%d) = ", syscall);
        

        //DEBUGGING 38
        // if (retval == -38) {
        //     fprintf(stderr, "Warning: Invalid syscall return (-38). Possible GETREGS failure.\n");
        //     fflush(stderr);
        // }

        fflush(stderr);
    }
    return 0;
}
