#define _GNU_SOURCE
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/reg.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/user.h> // For user_regs_struct
#include "syscalls.h"

// extern char **environ;

// const syscall_t *get_syscall(size_t nr) {
//     // Assuming syscalls_64_g is defined and populated with syscall information
//     for (size_t i = 0; syscalls_64_g[i].name != NULL; i++) {
//         if (syscalls_64_g[i].nr == nr) {
//             return &syscalls_64_g[i];
//         }
//     }
//     return NULL;
// }

int trace_child(int argc, char **argv);
int trace(pid_t child);

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

int trace_child(int argc, char **argv) 
{
    char *args [argc+1];
    memcpy(args, argv, argc * sizeof(char *));
    args[argc] = NULL;

    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    kill(getpid(), SIGSTOP);
    return execvp(args[0], args);
}

int wait_syscall(pid_t child);

int trace(pid_t child)
{
    // int syscall --task 2
    int status, retval = 0;
    waitpid(child, &status, 0);
    ptrace(PTRACE_SETOPTIONS, child, NULL, PTRACE_O_TRACESYSGOOD);

    while(1)
    {
        if (wait_syscall(child) != 0) break;

        // task 2
        int syscall = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_RAX);
        retval = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * RAX);
        // fprintf(stderr, "syscall(%d) = ", syscall);
        
        if (wait_syscall(child) != 0) break;

        printf("syscall(%lld) = %lld\n", (long long)syscall, (long long)retval);
    }
    return 0;
}

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

// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
//         exit(1);
//     }

//     pid_t child = fork();
//     if (child == -1){
//         perror("fork failed");
//         return EXIT_FAILURE;
//     }
//     if (child == 0) {
//         // Child process: request tracing and execute command
//         ptrace(PTRACE_TRACEME, 0, NULL, NULL);
//         kill(getpid(), SIGSTOP);
//         execve(argv[1], argv + 1, environ);
//         perror("execv failed");
//         return EXIT_FAILURE;
//     } else {
//         // Parent process: trace system calls
//         int status = 0;
//         struct user_regs_struct regs;
//         int syscall_entry = 1; //Tracks entry

//         waitpid(child, &status, 0);
//         // this ptrace was the infinite loop problem(dont put syscall here)
//         ptrace(PTRACE_SETOPTIONS, child, NULL, PTRACE_O_TRACESYSGOOD);

//         while (1) {
//             if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1) {
//                 if (errno == ESRCH) break; // Child exited
//                 perror("ptrace SYSCALL failed");
//                 return EXIT_FAILURE;
//             }

//             waitpid(child, &status, 0);

//             if (WIFEXITED(status)) break;

//             if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP)
//             {
//                 if (syscall_entry)
//                 {
//                     if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
//                     {
//                         perror("ptrace GETREGS failed");
//                         return EXIT_FAILURE;
//                     }

//                     const syscall_t *syscall = get_syscall(regs.orig_rax);
                    
//                     if (syscall)
//                     {
//                         printf("%s (%lld)\n", syscall->name, regs.orig_rax);
//                     } else {
//                         printf("Syscall not found: %lld\n", regs.orig_rax);
//                     }
//                     fflush(stdout);
//                     // printf("%lld\n", regs.orig_rax);
//                 }
//                 syscall_entry = !syscall_entry; // entry/exit
//             }
//         }
//     }
//     return EXIT_SUCCESS;
// }