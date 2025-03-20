#!/bin/bash

# Gotta clean this up

# Write a sh script that sends the signal SIGQUIT to a process, given its PID

# Usage: signal_send.sh <pid>
# Where <pid> is the PID of the process to send a signal to
# If the number of arguments is not correct, your program must print Usage: %s <pid> (where %s is argv[0]), followed by a new line, and exit with 1


# pid=$1
# makes sure there's only one argument; exits otherwise
# if [ $1 -ne 1 ]; 
# then
#     echo "Usage: $0 <pid>"
#     exit 1
# fi

# # checks if the process exists; exits if it doesn't
# if ! pkill -0 $1;
# then
#     echo "Process $1 does not exist"
#     exit 1
# fi
# # sends the signal SIGQUIT to the process
# if [ $1 -ne 0 ];
# then
#     pkill -3 $1
#     exit 0
# fi
# # if the signal was sent successfully, your program must print Signal sent to $1
# echo "Signal sent to $1"
# exit 0

#!/bin/bash

# check if one argument is passed
if [ $# -ne 1 ]; then
    echo "Usage: $0 <pid>"
    exit 1
fi

# Check if the process exists
if ! kill -0 $1;
then
    echo "Process $1 does not exist"
    exit 1
fi

#send SIGQUIT to process
if kill -3 $1;
then
    echo "Signal sent to $1"
    exit 0
else
    echo "Failed to send signal to $1"
    exit 1
fi
