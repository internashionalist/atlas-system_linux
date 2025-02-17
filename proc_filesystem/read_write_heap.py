#!/usr/bin/python3
"""
This script uses the /proc filesystem to read and write to the heap of a pid.
"""
import os
import sys
import ctypes

def heap_region(pid):
    """
    Finds the start and end of a process's heap.
    
    Args:
        pid (str): process id
    
    Returns:
        tuple: start and end of heap as integers
    """
    maps_path = f"/proc/{pid}/maps"  # path to maps file

    if not os.path.exists(maps_path):  # check if process exists
        print(f"Error: Process {pid} not found.")
        sys.exit(1)

    with open(maps_path, "r") as maps_file:  # open maps file
        for line in maps_file:
            if "heap" in line:  # find heap
                parsed = line.split()  # split line
                addr_range = parsed[0].split('-')  # split address range
                start = int(addr_range[0], 16)
                end = int(addr_range[1], 16)
                return start, end

    print(f"Error: You have no heap. You are heapless. {pid}.")  # heap not found
    sys.exit(1)

def read_heap(pid, start, end):
    """
    Reads the heap of a process.
    
    Args:
        pid (str): process id
    
    Returns:
        None
    """
    mem_path = f"/proc/{pid}/mem"  # path to mem file

    if not os.path.exists(mem_path):
        print(f"Error: Your process {pid} has been forgotten.")
        sys.exit(1)

    mem_file = open(mem_path, "rb")
    mem_file.seek(start)
    memory = mem_file.read(end - start)  # read heap
    mem_file.close()

    return memory

def write_heap(pid, address, data):
    """
    Writes to the heap of a process.
    
    Args:
        pid (str): process id
        address (int): address to overwrite in heap
        data (bytes): replacement data
    
    Returns:
        None
    """
    mem_path = f"/proc/{pid}/mem"

    if not os.path.exists(mem_path):
        print(f"Error: Your process {pid} has been forgotten.")
        sys.exit(1)

    mem_file = open(mem_path, "r+b")
    mem_file.seek(address)
    mem_file.write(data)
    mem_file.close()

def main():
    """
    Puts it all together: parsing, memory search, and write/replacement
    
    Args:
        None
    
    Returns:
        None
    """
    if len(sys.argv) != 4:  # if arg count wrong
        print(f"Usage: {sys.argv[0]} pid search_string replace_string. Idiot.")
        sys.exit(1)

    pid = sys.argv[1]

    if not pid.isdigit():
        print("Error: Gotta be a number, kid.")
        sys.exit(1)

    search_string = sys.argv[2].encode("ascii")  # Convert search string to ASCII bytes
    replace_string = sys.argv[3].encode("ascii")

    start, end = heap_region(pid)  # get heap region/range
    memory = read_heap(pid, start, end) # read heap

    if search_string not in memory:
        print(f"Error: Search string {search_string} is nowhere to be found.")
        sys.exit(1)

    address = start + memory.find(search_string)  # address of search string
    # pad the replacement string with null bytes
    replace_string = replace_string.ljust(len(search_string), b'\x00') 

    write_heap(pid, address, replace_string)  # write replacement

    sys.exit(0)

if __name__ == "__main__":
    main()
