#!/usr/bin/python3

python
"""
replace_string_in_heap.py: A Python script to find and replace a string in the heap memory of a running process using ptrace and ctypes.

Usage:
    python replace_string_in_heap.py <pid>

Arguments:
    <pid>          The process ID of the target process.

Example:
    python replace_string_in_heap.py 1234

Modules:
    os             The os module provides a way of using operating system-dependent functionality.
    sys            The sys module provides access to some variables used or maintained by the interpreter.
    ctypes         The ctypes module provides C compatible data types and allows calling functions in DLLs or shared libraries.

Classes:
    user_regs_struct: A ctypes Structure that represents the user registers of a process.
"""

import os
import sys
import ctypes
import struct

# ptrace will send a specific tracee using one of these
PTRACE_ATTACH = 16
PTRACE_DETACH = 17
PTRACE_PEEKDATA = 2
PTRACE_POKEDATA = 5

class user_regs_struct(ctypes.Structure):
    _fields_ = [("r15", ctypes.c_ulong),
                ("r14", ctypes.c_ulong),
                ("r13", ctypes.c_ulong),
                ("r12", ctypes.c_ulong),
                ("rbp", ctypes.c_ulong),
                ("rbx", ctypes.c_ulong),
                ("r11", ctypes.c_ulong),
                ("r10", ctypes.c_ulong),
                ("r9", ctypes.c_ulong),
                ("r8", ctypes.c_ulong),
                ("rax", ctypes.c_ulong),
                ("rcx", ctypes.c_ulong),
                ("rdx", ctypes.c_ulong),
                ("rsi", ctypes.c_ulong),
                ("rdi", ctypes.c_ulong),
                ("orig_rax", ctypes.c_ulong),
                ("rip", ctypes.c_ulong),
                ("cs", ctypes.c_ulong),
                ("eflags", ctypes.c_ulong),
                ("rsp", ctypes.c_ulong),
                ("ss", ctypes.c_ulong),
                ("fs_base", ctypes.c_ulong),
                ("gs_base", ctypes.c_ulong),
                ("ds", ctypes.c_ulong),
                ("es", ctypes.c_ulong),
                ("fs", ctypes.c_ulong),
                ("gs", ctypes.c_ulong)]

libc = ctypes.CDLL("libc.so.6")

# pid will thread ID of the corresponding Linux thread
def attach(pid):
    if libc.ptrace(PTRACE_ATTACH, pid, None, None) == -1:
        raise OSError("ptrace attach failed")
    os.waitpid(pid, 0)

def detach(pid):
    if libc.ptrace(PTRACE_DETACH, pid, None, None) == -1:
        raise OSError("ptrace detach failed")

def peek_data(pid, addr):
    word = libc.ptrace(PTRACE_PEEKDATA, pid, addr, None)
    if word == -1:
        raise OSError("ptrace peekdata failed")
    return word

def poke_data(pid, addr, data):
    if libc.ptrace(PTRACE_POKEDATA, pid, addr, data) == -1:
        raise OSError("ptrace pokedata failed")

def find_and_replace_string(pid, old_str, new_str):
    mem_path = f"/proc/{pid}/mem"
    maps_path = f"/proc/{pid}/maps"
    
    with open(maps_path, "r") as maps_file:
        for line in maps_file:
            if "heap" in line:
                addr_range = line.split()[0]
                start, end = [int(x, 16) for x in addr_range.split("-")]
                break
    
    with open(mem_path, "rb+") as mem_file:
        mem_file.seek(start)
        heap_data = mem_file.read(end - start)
        
        offset = heap_data.find(old_str.encode())
        if offset == -1:
            print("String not found in heap")
            return
        
        mem_file.seek(start + offset)
        mem_file.write(new_str.encode() + b'\x00' * (len(old_str) - len(new_str)))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <pid>")
        sys.exit(1)
    
    pid = int(sys.argv[1])
    
    try:
        attach(pid)
        find_and_replace_string(pid, "old_string", "new_string")
    finally:
        detach(pid)
