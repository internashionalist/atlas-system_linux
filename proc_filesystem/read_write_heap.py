#!usr/bin/python3
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

    print(f"Error: Heap not found for process {pid}.")  # heap not found
    sys.exit(1)

