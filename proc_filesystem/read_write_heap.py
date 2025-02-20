#!/usr/bin/python3

import gdb
import re
import sys

class ReplaceStringInHeap(gdb.Command):
    def __init__(self):
        super(ReplaceStringInHeap, self).__init__("replace_string", gdb.COMMAND_USER)

        def invoke(self, arg, from_tty):
            args = arg.split()
            if len(args) != 3:
                print("Usage: replace_string <pid> <old_string> <new_string>")
                return
            
            pid = args[0]
            old_string = args[1]
            new_string = args[2]

            gdb.execute(f"attach {pid}")

            output = gdb.execute("info proc mappings", to_string=True)
            match = re.search(r"[heap\]s+([0-9a-f]+)", output)
            if match:
                start = int(match.group(1), 16)
                end = int(match.group(2), 16)
                heap_size = end - startprint(f"Heap found from {start:x} to {end:x}")

                heap_data = gdb.selected_inferior().read_memory(start, heap_size)

                offset = heap_data.find(old_string.encode())
                if offset != -1:
                    addr = start + offset
                    print(f"Found '{old_string}' at {addr:x}")

                    gdb.selected_inferior().write_memory(addr, new_string.encode() + b'\x00')
                    print(f"Replaced '{old_string}' with '{new_string}'")
                else:
                    print(f"'{old_string}' not found in heap")

                gdb.execute("detach")

ReplaceStringInHeap()

if __name__ == "main":
    if len(sys.argv) != 4:
        print(f"Usage: {sys.argv[0]} <pid> <old_string> <new_string>")
        sys.exit(1)

    pid = sys.argv[1]
    old_string = sys.argv[2]
    new_string = sys.argv[3]

    gdb.execute(f"replace_string {pid} {old_string} {new_string}")