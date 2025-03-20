# Write a sh script that set a handler for the signals SIGABRT, SIGIO and SIGTERM

# The script must print Nope followed by a new line, each time a SIGABRT, SIGIO or SIGTERM is caught
# Your script must contain a shebang
# You’re not allowed to have more than 2 lines in your script
# You’re not allowed to have more than 1 instruction per line

# trap/catch signals
for s in ABRT IO TERM; do trap 'echo Nope' SIG$s; done
