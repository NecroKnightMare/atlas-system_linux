#!/bin/bash

# Write a sh script that sends the signal SIGQUIT to a process, given its PID

# Usage: signal_send.sh <pid>
# Where <pid> is the PID of the process to send a signal to
# If the number of arguments is not correct, your program must print Usage: %s <pid> (where %s is argv[0]), followed by a new line, and exit with 1

# Check if the number of arguments is correct
if [ "$#" -ne 1 ]; then
    printf "Usage: %s <pid>\n" "$0"
    exit 1
fi

# grab pid from the first argument
pid=$!

# Send SIGQUIT to the given pid
kill -SIGQUIT "$pid"
