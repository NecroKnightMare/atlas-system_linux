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


int trace_child(int argc, char **argv);
int trace(pid_t child);
int wait_syscall(pid_t child);

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
    
    if (child == -1){
        perror("fork failed");
        return EXIT_FAILURE;
    }
    if (child == 0) {
        return trace_child(argc-1, argv+1);
    } else {
        return trace(child);
    }
}

/**
 * trace_child - Sets up the child process for tracing
 * @argc: Number of arguments
 * @argv: Command and its arguments
 *
 * Description:
 * This function configures the child process to be traced
 * by the parent using ptrace.
 *
 * Return: Result of execvp call, or failure if execution doesn't start
 */
int trace_child(int argc, char **argv) 
{
    char *args [argc+1];
    memcpy(args, argv, argc * sizeof(char *));
    args[argc] = NULL;

    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    kill(getpid(), SIGSTOP);
    return execvp(args[0], args);
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
int trace(pid_t child)
{
    int status, retval;
    struct user_regs_struct regs;

    waitpid(child, &status, 0);
    ptrace(PTRACE_SETOPTIONS, child, NULL, PTRACE_O_TRACESYSGOOD);

    while(1)
    {
        if (wait_syscall(child) != 0) break;

        if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
        {
            perror("ptrace GETREGS failed");
            return EXIT_FAILURE;
        }


        // task 2
        int syscall = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_RAX);
        retval = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * RAX);
        // fprintf(stderr, "syscall(%d) = ", syscall);
        
        if (wait_syscall(child) != 0) break;

        //DEBUGGING 38
        if (retval == -38) {
            fprintf(stderr, "Warning: Invalid syscall return (-38). Possible GETREGS failure.\n");
            fflush(stderr);
        }

        printf("syscall(%lld) = %lld\n", (long long)syscall, (long long)retval);
        fflush(stdout);
    }
    return 0;
}
/**
 * wait_syscall - Waits for the next system call in the child process
 * @child: Process ID of the child
 *
 * Description:
 * This function uses ptrace to synchronize with the system calls
 * executed by the child process.
 *
 * Return: 0 when a syscall occurs, 1 when the process exits
 */
int wait_syscall(pid_t child)
{
    int status;
    while(1)
    {
        ptrace(PTRACE_SYSCALL, child, 0, 0);
        waitpid(child, &status, 0);
        if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
        {
            return 0;
        }
        if (WIFEXITED(status))
        {
            return 1;
        }
    }
}
