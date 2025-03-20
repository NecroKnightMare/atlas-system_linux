#!/bin/bash

# Gotta clean this up

# Write a sh script that sends the signal SIGQUIT to a process, given its PID

# Usage: signal_send.sh <pid>
# Where <pid> is the PID of the process to send a signal to
# If the number of arguments is not correct, your program must print Usage: %s <pid> (where %s is argv[0]), followed by a new line, and exit with 1


# pid=$1
# makes sure there's only one argument; exits otherwise
if [ $# -ne 1 ]; then
    echo "Usage: $0 <pid>"
    exit 1
fi

# saves the first argument as the pid
# pid=$1

# sends the SIGQUIT signal to the process with the given pid
# kill -3 "$pid"
# checks if the last signal was sent successfully
pkill -3 $1
# if ! kill -SIGQUIT <PID>; then
#     echo "Failed to send SIGQUIT to process $pid"
#     exit 1
#  saying permissions denied here in error