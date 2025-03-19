#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <sys/types.h>


int handle_signal(void);
void sigint_handler(int signum);
void print_hello(int);
void set_print_hello(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
// ./describe <signum>;
void handler(int signum);
int pid_exist(pid_t pid);
// signal_send <pid>;
// signal_send.sh <pid>;
int pid_exist(pid_t pid);


#endif