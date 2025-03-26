# C - ELF: nm/objdump

## Resources

#### Read or Watch

- [ELF Wikipedia](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)
- [ELF](https://stevens.netmeister.org/631/elf.html)
- [The ELF Object File Format: Introduction](https://www.linuxjournal.com/article/1059)
- [The ELF Object File Format by Dissection](https://www.linuxjournal.com/article/1060)

#### man or help

- `elf (5)`
- `nm (1)`
- `objdump (1)`

## Learning Objectives

- What is the ELF format
- What are the commands `nm` and `objdump`
- How to use them properly
- How to parse the content of an `ELF` file
- What information can be extracted from an `ELF` file
- What are the differences between `nm` and `objdump`

## Requirements

### General

- Allowed editors: `vi`, `vim`, `emacs`
- All your files will be compiled on Ubuntu 14.04 LTS
- Your C programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall` `-Werror` `-Wextra` and `-pedantic`
- All your files should end with a new line
- A `README.md` file, at the root of the folder of the project, is mandatory
- Your code should use the `Betty` style. It will be checked using [betty-style.pl](https://github.com/hs-hq/Betty/blob/main/betty-style.pl) and [betty-doc.pl](https://github.com/hs-hq/Betty/blob/main/betty-doc.pl)
- You are not allowed to have more than 5 functions per file
- All your header files should be include guarded

### Allowed Functions and System Calls

- Unless specified otherwise, you are allowed to use the C standard library
- You’re not allowed to use `system`(3)
- You’re not allowed to use `exec*`(2 and 3)

### Compilation

- You have to provide a `Makefile` in order to compile each task
- Make sure each task compiles on `Ubuntu 14.04 LTS`, with `gcc 4.8.4`
- You must compile each task using the flags `-Wall` `-Werror` `-Wextra` and `-pedantic`

### Tests

- Your program must be able to handle both 32-bit and 64-bit ELF files
- Your program must be able to handle both little and big endian ELF files
- Your program must be able to handle all types of ELF files

## More Info

See also `/usr/include/elf.h`

#

## Tasks

#### 0. nm -p

Write a program that reproduces the GNU nm command

- Usage: `hnm [objfile ...]`
- The output should be the exact same as `nm -p`
- Your sources must be compiled and linked using a Makefile

Your makefile must define the rule `hnm` and compile the needed sources to form the executable `hnm`.

```
alex@~/nm_objdump$ ./hnm elf_files/ubuntu64 
0000000000600e20 d __JCR_LIST__
0000000000400630 t deregister_tm_clones
0000000000400670 t register_tm_clones
00000000004006b0 t __do_global_dtors_aux
0000000000601068 b completed.7585
0000000000600e18 t __do_global_dtors_aux_fini_array_entry
00000000004006d0 t frame_dummy
0000000000600e10 t __frame_dummy_init_array_entry
0000000000400b20 r __FRAME_END__
0000000000600e20 d __JCR_END__
0000000000600e18 t __init_array_end
0000000000600e28 d _DYNAMIC
0000000000600e10 t __init_array_start
00000000004009f8 r __GNU_EH_FRAME_HDR
0000000000601000 d _GLOBAL_OFFSET_TABLE_
0000000000400980 T __libc_csu_fini
                w _ITM_deregisterTMCloneTable
0000000000601058 W data_start
                U write@@GLIBC_2.2.5
0000000000601068 D _edata
0000000000400984 T _fini
                U __stack_chk_fail@@GLIBC_2.4
                U close@@GLIBC_2.2.5
                U dprintf@@GLIBC_2.2.5
                U read@@GLIBC_2.2.5
                U __libc_start_main@@GLIBC_2.2.5
0000000000601058 D __data_start
                w __gmon_start__
0000000000601060 D __dso_handle
0000000000400990 R _IO_stdin_used
0000000000400910 T __libc_csu_init
0000000000601070 B _end
0000000000400600 T _start
0000000000601068 B __bss_start
00000000004006f6 T main
                U open@@GLIBC_2.2.5
                w _Jv_RegisterClasses
                U exit@@GLIBC_2.2.5
0000000000601068 D __TMC_END__
                w _ITM_registerTMCloneTable
0000000000400540 T _init
alex@~/nm_objdump$ ./hnm elf_files/netbsd32 
0804858c t _strrchr
080487c4 t gcc2_compiled.
        U __syscall
080486cc W dlerror
08049988 B __mainprog_obj
08048700 T _dladdr
08049900 A _DYNAMIC
08048660 T _dlclose
080487c4 A _etext
08048698 T _dlsym
08048700 W dladdr
08048660 W dlclose
08048440 T _init
0804862c T _dlopen
0804998c B environ
080484c0 T __start
080486cc T _dlerror
080498a8 D __progname
080484c0 T _start
0804862c W dlopen
08048698 W dlsym
08049988 A __bss_start
08049990 B main
080487c4 T _fini
        U atexit
080484d8 T ___start
08049988 A _edata
080498cc A _GLOBAL_OFFSET_TABLE_
08049994 A _end
080498ac D __ps_strings
        U exit
080485b8 T _rtld_setup
alex@~/nm_objdump$
```

#

#### Repo

- GitHub repository: `atlas-system_linux`
- Directory: `nm_objdump`
- File: `Makefile`

#
