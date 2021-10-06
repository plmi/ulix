// old line comment removed
/*
Copyright (c) 2008-2015 Felix Freiling, University of Erlangen-Nürnberg, Germany
Copyright (c) 2011-2015 Hans-Georg Eßer, University of Erlangen-Nürnberg, Germany

This program is free software: you can redistribute it and/or modify it under 
the terms of the GNU General Public License as published by the Free Software 
Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY 
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this 
program.  If not, see <http://www.gnu.org/licenses/>.                            */
// old line comment removed
                     
// old line comment removed
/*
v0.01  2011/06     first version: boots, enables interrupts, keyboard handler,
                   protected mode; most code taken from kernel tutorials
v0.02  2011/07/31  paging for the kernel (not yet for user space)
v0.03  2011/08/12  paging with Higher Half Kernel / GDT trick (preparation for
                   user space)
v0.04  2011/08/17  dynamic memory allocation: request frame, request new page
                   (with update of page table; creation of new page table if
                   last used one is full) 
v0.05  2012/10/02  serial hard disk and external storage server (for use with
                   qemu & co.)
v0.07  2013/04/05  Scheduling and fork / exec / exit / waitpid are working.
v0.08  2013/07/13  Minix Filesystem support (replaces "simplefs"). Can read,
                   write, create files. 
                   Kernel uses floppy (FDC controller) instead of serial disk
                   Terminal support (up to ten terminals with shells)
v0.09  2013/11/02  execv (with ELF loader) works; moved internal shell 
                   commands to ELF binaries in the bin/ directory
v0.10  2014/01/07  Mounting works, VFS functions (u_open, u_read etc.) work 
                   across several mounted volumes
                   Enter kernel shell: Shift+Esc, return to user mode: exit
v0.11  2014/04/23  Filesystem code is complete, buffer cache also used for
                   writing. Kernel level threads with pthread_* and pthread_
                   mutex_* functions.
v0.12  2014/08/19  Code is complete for the first public release.
v0.13  2015/09/02  Modified version (error fixes).
*/
// old line comment removed
#define MAX_ADDRESS MEM_SIZE-1       // last valid physical address
#define PAGE_SIZE 4096               // Intel: 4K pages
#define NUMBER_OF_FRAMES (MEM_SIZE/PAGE_SIZE)
// old line comment removed
#define IRQ_TIMER      0
#define IRQ_KBD        1
#define IRQ_SLAVE      2     // Here the slave PIC connects to master
#define IRQ_COM2       3
#define IRQ_COM1       4
#define IRQ_FDC        6
#define IRQ_IDE       14     // primary IDE controller; secondary has IRQ 15
// old line comment removed
// I/O Addresses of the two programmable interrupt controllers
#define IO_PIC_MASTER_CMD   0x20  // Master (IRQs 0-7), command register
#define IO_PIC_MASTER_DATA  0x21  // Master, control register

#define IO_PIC_SLAVE_CMD    0xA0  // Slave (IRQs 8-15), command register
#define IO_PIC_SLAVE_DATA   0xA1  // Slave, control register
// old line comment removed
#define END_OF_INTERRUPT  0x20
// old line comment removed
#define MAX_ADDR_SPACES 1024
// old line comment removed
#define BINARY_LOAD_ADDRESS 0x0
// old line comment removed
#define TOP_OF_USER_MODE_STACK 0xb0000000
// old line comment removed
#define TOP_OF_KERNEL_MODE_STACK 0xc0000000
// old line comment removed
#define AS_FREE   0
#define AS_USED   1
#define AS_DELETE 2
// old line comment removed
#define KSTACK_DELETE_LIST_SIZE 1024
// old line comment removed
// kernel stack (per process): 1 page = 4 KByte
#define KERNEL_STACK_PAGES 4
#define KERNEL_STACK_SIZE PAGE_SIZE * KERNEL_STACK_PAGES
// old line comment removed
#define MAX_THREADS 1024
// old line comment removed
#define PROGSIZE 32768
// old line comment removed
#define MAX_SYSCALLS 1024         // max syscall number: 1023
// old line comment removed
#define ELF_PT_LOAD 1
// old line comment removed
#define MAX_SWAP_FRAMES 16384
// old line comment removed
#define PG_MAX_COUNTERS 1024
// old line comment removed
#define PG_COUNTER_THRESHOLD 100000
// old line comment removed
#define SYSTEM_KBD_BUFLEN 32
#define TERMINALS 10
// old line comment removed
#define IO_KEYBOARD 0x60
// old line comment removed
#define KEY_CTRL     29
#define KEY_L_SHIFT  42
#define KEY_R_SHIFT  54
#define KEY_ALT      56
// old line comment removed
#define VT_WIDTH  (80)
#define VT_HEIGHT (24)
#define VT_SIZE   (VT_WIDTH * VT_HEIGHT * 2)
// old line comment removed
#define MAX_VT 9
// old line comment removed
#define IO_VGA_TARGET           0x3D4
#define IO_VGA_VALUE            0x3D5
#define IO_VGA_CURSOR_LOC_HIGH  14
#define IO_VGA_CURSOR_LOC_LOW   15
// old line comment removed
#define IO_CLOCK_COMMAND   0x43
#define IO_CLOCK_CHANNEL0  0x40
// old line comment removed
#define IO_CMOS_CMD  0x70
#define IO_CMOS_DATA 0x71
// old line comment removed
#define SCHED_SRC_TIMER   0
#define SCHED_SRC_RESIGN  1
// old line comment removed
#define IO_COM1    0x3f8
#define IO_COM2    0x2f8
// old line comment removed
#define MAX_SEMAPHORES 1024
// old line comment removed
#define MAX_LOCKS 1024
// old line comment removed
#define FS_ERROR  0
#define FS_MINIX  1
#define FS_FAT    2
#define FS_DEV    3
// old line comment removed
// u_open parameter  int open_link:
#define DONT_FOLLOW_LINK 1
#define FOLLOW_LINK 0
// old line comment removed
#define DEV_STDIN     (-101)
#define DEV_STDOUT    (-102)
#define DEV_STDERR    (-103)
// old line comment removed
#define BLOCK_SIZE 1024
// old line comment removed
enum { MX_SB_NINODES, MX_SB_NZONES, MX_SB_IMAP_BLOCKS, MX_SB_ZMAP_BLOCKS,
       MX_SB_FIRSTDATAZONE, MX_SB_LOG_ZONE_SIZE, MX_SB_MAX_SIZE, 
       MX_SB_MAGIC, MX_SB_STATE, MX_SB_ZONES };
// old line comment removed
#define MAX_INT_INODES 256
// old line comment removed
#define MX_MAX_FILES 256
// old line comment removed
#define BLOCKADDRESSES_PER_BLOCK (BLOCK_SIZE / 4)
// old line comment removed
#define DEV_HDA_NAME   "hda"
#define DEV_HDB_NAME   "hdb"
#define DEV_FD0_NAME   "fd0"
#define DEV_FD1_NAME   "fd1"
#define DEV_KMEM_NAME  "kmem"
#define DEV_FD0_INODE  3
#define DEV_FD1_INODE  4
#define DEV_HDA_INODE  5
#define DEV_HDB_INODE  6
#define DEV_KMEM_INODE 7
// old line comment removed
#define MAX_DEV_FILES 32
// old line comment removed
#define MAJOR_FD      2
#define MAJOR_HD      3
#define MAJOR_KMEM    4
#define MAJOR_SERIAL 42
// old line comment removed
#define UPDATE_BUF      1
#define DONT_UPDATE_BUF 0
// old line comment removed
#define DEV_HDA  0x300  //  disk   /dev/hda
#define DEV_HDB  0x340  //  disk   /dev/hdb
#define DEV_FD0  0x200  //  floppy /dev/fd0
#define DEV_FD1  0x201  //  floppy /dev/fd1
#define DEV_KMEM 0x400  //  memory /dev/kmem
#define DEV_NONE 0      //  no device
// old line comment removed
#define BUFFER_CACHE_SIZE 512
// old line comment removed
#define BUFFER_CLEAN 0
#define BUFFER_DIRTY 1
// old line comment removed
#define BUF_STAT_NEW      0
#define BUF_STAT_TRANSFER 1
#define BUF_STAT_FINISHED 2
#define BUF_READ          100
#define BUF_WRITE         101
#define SER_BUF_SIZE      100
// old line comment removed
#define CMD_STAT   1   // status query
#define CMD_GET    2   // GET a block (1024 bytes)
#define CMD_PUT    3   // PUT a block (1024 bytes)
#define CMD_TERM   99  // terminate controller
// old line comment removed
#define TSTATE_WAITSD 12
// old line comment removed
#define IDE_CMD_READ  0x20     // read from disk, with retries
#define IDE_CMD_WRITE 0x30     // write to disk, with retries
#define IDE_CMD_IDENT 0xec     // identify disk
#define IDE_BSY       0x80     // 0b10000000  (bit 7),  device busy
#define IDE_DRDY      0x40     // 0b01000000  (bit 6),  device ready
#define IDE_DF        0x20     // 0b00100000  (bit 5),  drive fault
#define IDE_ERR       0x01     // 0b00000001  (bit 0),  error
// old line comment removed
// IDE output
#define IO_IDE_SEC_COUNT  0x1f2  // sector count register (read_/write_)
#define IO_IDE_SECTOR     0x1f3  // (32 bits in 0x1f3..0x1f6)
#define IO_IDE_DISKSEL    0x1f6  // disk select and upper 4 bits of sector no.
#define IO_IDE_COMMAND    0x1f7  // command register
#define IO_IDE_DEVCTRL    0x3f6  // device control register
// IDE input
#define IO_IDE_DATA       0x1f0  // data (read_/write_)
#define IO_IDE_STATUS     0x1f7  // status register (identical to command reg.)
// old line comment removed
#define HD_OP_READ     0
#define HD_OP_WRITE    1
#define HD_OP_NONE    -1

#define HD_SECSIZE   512
// old line comment removed
#define IO_FLOPPY_OUTPUT      0x3f2   // digital output register (DOR)
#define IO_FLOPPY_STATUS      0x3f4   // main status register (MSR)
#define IO_FLOPPY_COMMAND     0x3f5   // command/data register
#define IO_FLOPPY_RATE        0x3f7   // configuration control register
// old line comment removed
#define FLOPPY_DIRECTION     0b01000000  // bit 6 of status reg.
#define FLOPPY_MASTER        0b10000000  // bit 7 of status reg.
// old line comment removed
#define FLOPPY_CONTROLLER_BUSY    0b00010000  // bit 4 of status reg., busy
#define FLOPPY_NEW_BYTE  (FLOPPY_MASTER | FLOPPY_DIRECTION | FLOPPY_CONTROLLER_BUSY)
// old line comment removed
#define MAX_FLOPPY_RESULTS              0x07
// old line comment removed
#define FLOPPY_READ                     0xe6
#define FLOPPY_WRITE                    0xc5
// old line comment removed
#define HZ 100    // frequency of the timer
// old line comment removed
#define MAX_FLOPPY_ERRORS               0x08
// old line comment removed
#define FLOPPY_DTL                      0xFF
#define TRANSFER_OK                     0x00
#define WRITE_PROTECTED                 0x02
// old line comment removed
#define INVALID_TRACK   -1
// old line comment removed
#define FLOPPY_SPECIFY      0x03
#define FLOPPY_SPEC2        0x06
// old line comment removed
#define IO_DMA0_INIT        0x0A   // single channel mask register
#define IO_DMA0_MODE        0x0B   // mode register
#define IO_DMA0_FLIPFLOP    0x0C   // flip-flop reset register

#define IO_DMA_PAGE_2       0x81   // page    register for DMA channel 2
#define IO_DMA_ADDR_2       0x04   // address register for DMA channel 2
#define IO_DMA_COUNT_2      0x05   // count   register for DMA channel 2

#define DMA_READ_MODE       0x44
#define DMA_WRITE_MODE      0x48
// old line comment removed
#define FLOPPY_CHANNEL                  0x02
// old line comment removed
#define FLOPPY_CONTROLLER_ENABLE        0x04
#define FLOPPY_DMAINT_ENABLE            0x08
// old line comment removed
#define TEST_BITS     0b11111000   //   0xf8
#define SEEK_OK       0b00100000   //   0x20
// old line comment removed
#define FLOPPY_SEEK                     0x0f
#define FLOPPY_SENSE                    0x08
// old line comment removed
#define FD_SECSIZE                      512
// old line comment removed
#define FLOPPY_RECALIBRATE              0x07
// old line comment removed
#define CHECK_USER  6
#define CHECK_GROUP 3
#define CHECK_WORLD 0
// old line comment removed
#define SHELL_COMMANDS "help, ex" "it, test, div0, mem, stat, uname, "\
  "hexdump, clear, gf, gp, rp, gp1k, bdump, malloc, time, listas, "\
  "init, exec, testdisk, enable, longhelp, ps, queues, lsof"
// old line comment removed
               
// old line comment removed
#define true  1
#define false 0
#define NULL ((void*) 0)
// old line comment removed
#define MEM_SIZE 1024*1024*64       // 64 MByte
// old line comment removed
// Thread states
#define TSTATE_READY     1   // process is ready
#define TSTATE_FORK      3   // fork() has not completed
#define TSTATE_EXIT      4   // process has called exit()
#define TSTATE_WAITFOR   5   // process has called waitpid()
#define TSTATE_ZOMBIE    6   // wait for parent to retrieve exit value
#define TSTATE_WAITKEY   7   // wait for key press event
#define TSTATE_WAITFLP   8   // wait for floppy
#define TSTATE_LOCKED    9   // wait for lock
#define TSTATE_STOPPED  10   // stopped by SIGSTOP signal
#define TSTATE_WAITHD   11   // wait for hard disk
// old line comment removed
#define __NR_exit          1
#define __NR_fork          2
#define __NR_read          3
#define __NR_write         4
#define __NR_open          5
#define __NR_close         6
#define __NR_waitpid       7
#define __NR_link          9
#define __NR_unlink       10
#define __NR_execve       11
#define __NR_chdir        12
#define __NR_chmod        15
#define __NR_lseek        19
#define __NR_getpid       20
#define __NR_sync         36
#define __NR_kill         37
#define __NR_mkdir        39
#define __NR_rmdir        40
#define __NR_brk          45
#define __NR_signal       48
#define __NR_dup2         63
#define __NR_getppid      64
#define __NR_symlink      83
#define __NR_readlink     85
#define __NR_readdir      89
#define __NR_truncate     92
#define __NR_ftruncate    93
#define __NR_stat        106
#define __NR_chown       182
#define __NR_getcwd      183
#define __NR_setreuid32  203
#define __NR_setregid32  204
#define __NR_setuid32    213
#define __NR_setgid32    214
// old line comment removed
#define __NR_get_errno 501
#define __NR_set_errno 502
// old line comment removed
#define __NR_resign       66
// old line comment removed
#define __NR_gettid  21
// old line comment removed
#define __NR_getpsinfo 503
// old line comment removed
#define __NR_setpsname 504
// old line comment removed
#define __NR_pthread_create 506
// old line comment removed
#define __NR_pthread_exit 507
// old line comment removed
#define __NR_get_free_frames   509
#define __NR_free_a_frame      510
// old line comment removed
#define __NR_clrscr   512
#define __NR_get_xy   513
#define __NR_set_xy   514
// old line comment removed
#define __NR_read_screen   515
#define __NR_write_screen  516
// old line comment removed
#define __NR_pthread_mutex_init 517
// old line comment removed
#define __NR_pthread_mutex_lock    518
#define __NR_pthread_mutex_unlock  519
#define __NR_pthread_mutex_trylock 526
// old line comment removed
#define __NR_pthread_mutex_destroy 520
// old line comment removed
#define __NR_readchar  525
// old line comment removed
#define __NR_isatty  521
// old line comment removed
#define __NR_diskfree  522
// old line comment removed
#define EAGAIN 35
// old line comment removed
#define EBUSY           16          // device / resource busy
// old line comment removed
#define EPERM   1  // not permitted
#define ESRCH   3  // no such process
#define EINVAL 22  // invalid argument
// old line comment removed
#define ENOENT          2               // No such file or directory
#define EACCES          13              // Permission denied
// old line comment removed
#define CMDLINE_LENGTH 50   // how long can a process name be?
// old line comment removed
#define __NR_idle 505
// old line comment removed
#define __NR_page_out 508
// old line comment removed
#define KEY_ESC     27
#define KEY_UP     191
#define KEY_DOWN   192
#define KEY_LEFT   193
#define KEY_RIGHT  194
// old line comment removed
#define VT_NORMAL_BACKGROUND (0x0F << 8)
#define VT_BLUE_BACKGROUND   (0x1F << 8)
#define VT_RED_BACKGROUND    (0x4F << 8)
// old line comment removed
#define __NR_setterm  511
// old line comment removed
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
// old line comment removed
#define MAX_PFD 16   // up to 16 open_ files per process
// old line comment removed
#define S_IRWXU  0000700    // RWX mask for owner
#define S_IRUSR  0000400    // R for owner
#define S_IWUSR  0000200    // W for owner
#define S_IXUSR  0000100    // X for owner

#define S_IRWXG  0000070    // RWX mask for group
#define S_IRGRP  0000040    // R for group
#define S_IWGRP  0000020    // W for group
#define S_IXGRP  0000010    // X for group

#define S_IRWXO  0000007    // RWX mask for other
#define S_IROTH  0000004    // R for other
#define S_IWOTH  0000002    // W for other
#define S_IXOTH  0000001    // X for other

#define S_ISUID  0004000    // suid bit (set user ID)
#define S_ISGID  0002000    // sgid bit (set group ID)
#define S_ISVTX  0001000    // save swapped text even after use

#define S_IFMT   0170000    // mask the file type part
#define S_IFIFO  0010000    // named pipe (fifo)
#define S_IFCHR  0020000    // character special
#define S_IFDIR  0040000    // directory
#define S_IFBLK  0060000    // block special
#define S_IFREG  0100000    // regular
#define S_IFLNK  0120000    // symbolic link
#define S_IFSOCK 0140000    // socket
// old line comment removed
#define O_RDONLY        0x0000     // read only
#define O_WRONLY        0x0001     // write only
#define O_RDWR          0x0002     // read and write
#define O_APPEND        0x0008     // append mode
#define O_CREAT         0x0200     // create file
// old line comment removed
#define SEEK_SET 0    // absolute offset
#define SEEK_CUR 1    // relative offset
#define SEEK_END 2    // EOF plus offset
// old line comment removed
#define SIG_DFL ((sighandler_t)0)     // default signal handling
#define SIG_IGN ((sighandler_t)1)     // ignore signal
#define SIG_ERR ((sighandler_t)-1)    // error code
// old line comment removed
#define SIGHUP     1
#define SIGINT     2
#define SIGQUIT    3
#define SIGILL     4
#define SIGTRAP    5
#define SIGABRT    6
#define SIGFPE     8
#define SIGKILL    9
#define SIGBUS    10
#define SIGSEGV   11
#define SIGSYS    12
#define SIGPIPE   13
#define SIGALRM   14
#define SIGTERM   15
#define SIGURG    16
#define SIGSTOP   17
#define SIGTSTP   18
#define SIGCONT   19
#define SIGCHLD   20
#define SIGTTIN   21
#define SIGTTOU   22
#define SIGPOLL   23
#define SIGXCPU   24
#define SIGXFSZ   25
#define SIGVTALRM 26


#define SIGPROF   27
#define SIGUSR1   30
#define SIGUSR2   31
// old line comment removed
#define __NR_login 523
// old line comment removed
#define QUERY_UID  0
#define QUERY_EUID 1
#define QUERY_GID  2
#define QUERY_EGID 3
#define __NR_query_ids 524
// old line comment removed
#define UNAME "Ulix-i386 0.13"
#define BUILDDATE "Fr 20. Nov 13:35:58 CET 2015"
// old line comment removed
#define asm __asm__
// old line comment removed
#define KMAP(pd,frame) fill_page_desc (pd, true, true, false, false, frame)
#define UMAP(pd,frame) fill_page_desc (pd, true, true, true,  false, frame)
// old line comment removed
#define UMAPD(ptd, frame) fill_page_table_desc (ptd, true, true, true,  frame)
#define KMAPD(ptd, frame) fill_page_table_desc (ptd, true, true, false, frame)
// old line comment removed
#define INDEX_FROM_BIT(b) (b/32)   // 32 bits in an unsigned int
#define OFFSET_FROM_BIT(b) (b%32)
// old line comment removed
#define PHYSICAL(x) ((x)+0xd0000000)
// old line comment removed
#define textmemptr ((word*)VIDEORAM)
// old line comment removed
// Peek and Poke for virtual addresses
#define PEEK(addr)           (*(byte *)(addr))
#define POKE(addr, b)        (*(byte *)(addr) = (b))
// Peek and Poke for physical addresses 0..64 MB
#define PEEKPH(addr)         (*(byte *)(PHYSICAL(addr)))
#define POKEPH(addr, b)      (*(byte *)(PHYSICAL(addr)) = (b))

// Macros for accessing unsigned ints (instead of bytes)
#define PEEK_UINT(addr)      (*(uint *)(addr))
#define POKE_UINT(addr, b)   (*(uint *)(addr) = (b))
#define PEEKPH_UINT(addr)    (*(uint *)(PHYSICAL(addr)))
#define POKEPH_UINT(addr, b) (*(uint *)(PHYSICAL(addr)) = (b))
// old line comment removed
#define MAKE_MULTIPLE_OF_PAGESIZE(x)  x = ((x+PAGE_SIZE-1)/PAGE_SIZE)*PAGE_SIZE
// old line comment removed
#define eax_return(retval) { r->eax = (unsigned int)((retval)); return; }
// old line comment removed
#define phys_memcpy(target, source, size) \
  (unsigned int)memcpy ( (void*)PHYSICAL(target), (void*)PHYSICAL(source), size)
#define copy_frame(out, in)  phys_memcpy (out << 12, in << 12, PAGE_SIZE)
// old line comment removed
#define current_pid  (thread_table[current_task].pid)
#define current_ppid (thread_table[current_task].ppid)
// old line comment removed
#define COPY_VAR_TO_ESP(x)  asm volatile ("mov %0, %%esp" :         : "r"(x) )
#define COPY_VAR_TO_EBP(x)  asm volatile ("mov %0, %%ebp" :         : "r"(x) )
#define COPY_ESP_TO_VAR(x)  asm volatile ("mov %%esp, %0" : "=r"(x)          )
#define COPY_EBP_TO_VAR(x)  asm volatile ("mov %%ebp, %0" : "=r"(x)          )
#define WRITE_CR3(x)        asm volatile ("mov %0, %%cr3" :         : "r"(x) )
// old line comment removed
#define CONVERT_BCD(bcd) (((bcd >> 4) * 10) + (bcd & 0x0f))
// old line comment removed
#define MIN(a,b) ((a) <= (b) ? (a) : (b))
#define MAX(a,b) ((a) >= (b) ? (a) : (b))
// old line comment removed
#define memcpy_debug(dest, src, count) \
  debug_printf ("DEBUG: memcpy() called in line %d\n", __LINE__); \
  memcpy (dest, src, count);
// old line comment removed
// #define DEBUG
// old line comment removed
                       
// old line comment removed
#define strequal(s1,s2) (!strcmp((s1),(s2)))
#define strdiff(s1,s2)  (strcmp((s1),(s2)))
// old line comment removed
typedef unsigned char            byte;
typedef unsigned char         boolean;
typedef unsigned short           word;
// old line comment removed
typedef unsigned char         uint8_t;
typedef unsigned short       uint16_t;
typedef unsigned int         uint32_t;
typedef unsigned long long   uint64_t;

typedef int                    size_t;
typedef unsigned int             uint;   // short names for "unsigned int",
typedef unsigned long           ulong;   // "unsigned long" and
typedef unsigned long long  ulonglong;   // "unsigned long long" (64 bit)
// old line comment removed
typedef unsigned int       memaddress;
// old line comment removed
typedef unsigned int addr_space_id;
// old line comment removed
typedef unsigned int thread_id;
// old line comment removed
typedef void (*sighandler_t)(int);
// old line comment removed
struct gdt_entry {
  unsigned int limit_low   : 16;
  unsigned int base_low    : 16;
  unsigned int base_middle :  8;
  unsigned int access      :  8;
  unsigned int limit_high  :  4;
  unsigned int flags       :  4;
  unsigned int base_high   :  8;
};
// old line comment removed
struct gdt_ptr {
    unsigned int limit       : 16;
    unsigned int base        : 32;
} __attribute__((packed));
// old line comment removed
typedef struct {
  unsigned int present         :  1;  //  0
  unsigned int writeable       :  1;  //  1
  unsigned int user_accessible :  1;  //  2
  unsigned int pwt             :  1;  //  3
  unsigned int pcd             :  1;  //  4
  unsigned int accessed        :  1;  //  5
  unsigned int dirty           :  1;  //  6
  unsigned int zeroes          :  2;  //  8.. 7
  unsigned int unused_bits     :  3;  // 11.. 9
  unsigned int frame_addr      : 20;  // 31..12
} page_desc;
// old line comment removed
typedef struct {
   page_desc pds[1024];
} page_table;
// old line comment removed
typedef struct {
  unsigned int present         :  1;  //  0
  unsigned int writeable       :  1;  //  1
  unsigned int user_accessible :  1;  //  2
  unsigned int pwt             :  1;  //  3
  unsigned int pcd             :  1;  //  4
  unsigned int accessed        :  1;  //  5
  unsigned int undocumented    :  1;  //  6
  unsigned int zeroes          :  2;  //  8.. 7
  unsigned int unused_bits     :  3;  // 11.. 9
  unsigned int frame_addr      : 20;  // 31..12
} page_table_desc;
// old line comment removed
typedef struct {
   page_table_desc ptds[1024];
} page_directory;
// old line comment removed
struct idt_entry {
    unsigned int addr_low  : 16;   // lower 16 bits of address
    unsigned int gdtsel    : 16;   // use which GDT entry?
    unsigned int zeroes    :  8;   // must be set to 0
    unsigned int type      :  4;   // type of descriptor
    unsigned int flags     :  4;
    unsigned int addr_high : 16;   // higher 16 bits of address
} __attribute__((packed));
// old line comment removed
struct idt_ptr {
    unsigned int limit   : 16;
    unsigned int base    : 32;
} __attribute__((packed));
// old line comment removed
typedef struct {
  void         *pd;                // pointer to the page directory
  int          pid;                // process ID (if used by a process; -1 if not)
  short        status;             // are we using this address space?
  memaddress   memstart, memend;   // first/last address below 0xc000.0000
  unsigned int stacksize;          // size of user mode stack
  memaddress   kstack_pt;          // stack page table (for kernel stack)
  unsigned int refcount;           // how many threads use this address space?
  
// old line comment removed
byte extra_kstacks;
// old line comment removed
} address_space;
// old line comment removed
typedef struct {
  thread_id next;       // id of the ``next'' thread
  thread_id prev;       // id of the ``previous'' thread
} blocked_queue;
// old line comment removed
typedef struct {
  unsigned int prev_tss    : 32;  // unused: previous TSS
  unsigned int esp0, ss0   : 32;  // ESP and SS to load when we switch to ring 0
  long long u1, u2         : 64;  // unused: esp1, ss1, esp2, ss2 for rings 1 and 2
  unsigned int cr3         : 32;  // unused: page directory
  unsigned int eip, eflags : 32;
  unsigned int eax, ecx, edx, ebx, esp, ebp, esi, edi, es, cs, ss, ds, fs, gs : 32;
                                  // unused (dynamic, filled by CPU)
  long long u3             : 64;  // unused: ldt, trap, iomap
} __attribute__((packed)) tss_entry_struct;
// old line comment removed
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Word;
typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Off;

typedef struct {
  byte          e_ident[16];            // Magic number and other info
  Elf32_Half    e_type;                 // Object file type
  Elf32_Half    e_machine;              // Architecture
  Elf32_Word    e_version;              // Object file version
  Elf32_Addr    e_entry;                // Entry point virtual address
  Elf32_Off     e_phoff;                // Program header table file offset
  Elf32_Off     e_shoff;                // Section header table file offset
  Elf32_Word    e_flags;                // Processor-specific flags
  Elf32_Half    e_ehsize;               // ELF header size in bytes
  Elf32_Half    e_phentsize;            // Program header table entry size
  Elf32_Half    e_phnum;                // Program header table entry count
  Elf32_Half    e_shentsize;            // Section header table entry size
  Elf32_Half    e_shnum;                // Section header table entry count
  Elf32_Half    e_shstrndx;             // Section header string table index
} Elf32_Ehdr;

typedef struct {
  Elf32_Word    p_type;                 // Segment type
  Elf32_Off     p_offset;               // Segment file offset
  Elf32_Addr    p_vaddr;                // Segment virtual address
  Elf32_Addr    p_paddr;                // Segment physical address
  Elf32_Word    p_filesz;               // Segment size in file
  Elf32_Word    p_memsz;                // Segment size in memory
  Elf32_Word    p_flags;                // Segment flags
  Elf32_Word    p_align;                // Segment alignment
} Elf32_Phdr;
// old line comment removed
struct paging_entry {
  int as         : 10;    // 10 bits for address space, values from [0..1023]
  int pageno     : 20;    // 20 bits for the page number
  int used       :  1;    // 2 bits for two flags
  int reserved   :  1;
} __attribute__((packed));
// old line comment removed
typedef struct {
  unsigned int present         :  1;  //  0
  unsigned int writeable       :  1;  //  1
  unsigned int user_accessible :  1;  //  2
  unsigned int pwt             :  1;  //  3
  unsigned int pcd             :  1;  //  4
  unsigned int accessed        :  1;  //  5
  unsigned int dirty           :  1;  //  6
  unsigned int zeroes          :  2;  //  8.. 7
  unsigned int paged_out       :  1;  //  9       <- new
  unsigned int unused_bits     :  2;  // 11..10
  unsigned int frame_addr      : 20;  // 31..12
} new_page_desc;
// old line comment removed
typedef struct {
  char kbd[SYSTEM_KBD_BUFLEN+1];
  int kbd_pos;
  int kbd_lastread;
  int kbd_count;
} terminal_t;
// old line comment removed
typedef struct {
  char mem[VT_SIZE];
  int x,y;
} term_buffer;
// old line comment removed
typedef struct {
  int counter;
  blocked_queue bq;
  
// old line comment removed
boolean used; 
// old line comment removed
} kl_semaphore;
// old line comment removed
typedef int kl_semaphore_id;
// old line comment removed
typedef struct {
  short int     l;             // the lock
  boolean       used;          // are we using this lock?
  blocked_queue bq;            // queue for this lock
  char          lockname[20];  // name
} lock_t;
typedef lock_t *lock;
// old line comment removed
typedef struct {
  char mountpoint[256];
  short fstype;            // filesystem type, e. g. Minix, device filesystem
  short device;            // e. g. DEV_FD0, DEV_HDA
  short mount_flags;       // always 0; we will not use mount flags
} mount_table_entry;
// old line comment removed
struct minix_superblock { 
  uint16_t s_ninodes;        uint16_t s_nzones; 
  uint16_t s_imap_blocks;    uint16_t s_zmap_blocks; 
  uint16_t s_firstdatazone;  uint16_t s_log_zone_size; 
  uint32_t s_max_size;       uint16_t s_magic; 
  uint16_t s_state;          uint32_t s_zones;
};
// old line comment removed
struct minix2_inode { 
// old line comment removed
  uint16_t i_mode;           uint16_t i_nlinks;
  uint16_t i_uid;            uint16_t i_gid;
  uint32_t i_size;           uint32_t i_atime;
  uint32_t i_mtime;          uint32_t i_ctime;
  uint32_t i_zone[10];
// old line comment removed
                                                };
// old line comment removed
struct minix_dir_entry {
  uint16_t inode;
  char name[30];
};
// old line comment removed
struct int_minix2_inode {
  
// old line comment removed
  uint16_t i_mode;           uint16_t i_nlinks;
  uint16_t i_uid;            uint16_t i_gid;
  uint32_t i_size;           uint32_t i_atime;
  uint32_t i_mtime;          uint32_t i_ctime;
  uint32_t i_zone[10];
// old line comment removed
                             // fields from the external inode
  int ino;                    // inode number
  unsigned int    refcount;   // how many users?
  unsigned short  clean;      // 0: changed; 1: unchanged (as on disk)
  short           device;     // file resides on which device?
};
// old line comment removed
struct mx_filestat { 
  struct int_minix2_inode *int_inode; 
  int pos; 
  short mode;
};
// old line comment removed
struct dev_filestat { 
  short dev;
  int pos;
  short mode;
};
// old line comment removed
struct buffer_entry {
  char buf[BLOCK_SIZE];
  int dev;      // from what device?              (-1 if free)
  int blockno;  // block number of buffered block (-1 if free)
  byte count;   // how often was it read_?
  byte dirty;   // true if not written to disk
};
// old line comment removed
struct serial_disk_buffer_entry {
  int pid;                 // process ID; -1 if kernel
  short status;            // New, Transfer, Finished, see BUF_STAT_*
  short direction;         // 100 = read_, 101 = write_
  unsigned int secno;      // sector number
  memaddress address;      // memory address (in process' address space)
  byte sector[BLOCK_SIZE]; // 1024 bytes
};
// old line comment removed
typedef struct {
  int total_sectors, tracks, sectors, sectorsize, trackstep, rate, gap, spec1;
} struct_fdd_type;

typedef struct {
  int present, calibrated, motor, current_track, type;
} struct_fdd;
// old line comment removed
                      
// old line comment removed
typedef struct {
  unsigned int gs, fs, es, ds;
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned int int_no, err_code;
  unsigned int eip, cs, eflags, useresp, ss;
} context_t;
// old line comment removed
typedef struct {
  thread_id  pid;         // process id
  thread_id  tid;         // thread id
  thread_id  ppid;        // parent process
  int        state;       // state of the process
  context_t  regs;        // context
  memaddress esp0;        // kernel stack pointer
  memaddress eip;         // program counter
  memaddress ebp;         // base pointer
  
// old line comment removed
addr_space_id addr_space;
// old line comment removed
thread_id next;       // id of the ``next'' thread
thread_id prev;       // id of the ``previous'' thread
// old line comment removed
boolean used;
// old line comment removed
int error;
// old line comment removed
int exitcode;
int waitfor;    // pid of the child that this process waits for
// old line comment removed
char cmdline[CMDLINE_LENGTH];
// old line comment removed
boolean   new;                    // is this thread new?
void      *top_of_thread_kstack;  // extra kernel stack for this thread
// old line comment removed
int terminal;
// old line comment removed
int files[MAX_PFD];
// old line comment removed
char cwd[256];
// old line comment removed
  sighandler_t sighandlers[32];
  unsigned long sig_pending;
  unsigned long sig_blocked;
// old line comment removed
word uid;   // user ID
word gid;   // group ID
word euid;  // effective user ID
word egid;  // effective group ID
word ruid;  // real user ID
word rgid;  // real group ID
// old line comment removed
} TCB;
// old line comment removed
typedef void *pthread_t;
typedef void pthread_attr_t;   // attributes not implemented
// old line comment removed
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
// old line comment removed
struct stat {
  unsigned int   st_dev;     // ID of device containing file
  unsigned short st_ino;     // inode number
  unsigned short st_mode;    // protection
  unsigned short st_nlink;   // number of hard links
  unsigned short st_uid;     // user ID of owner
  unsigned short st_gid;     // group ID of owner
  unsigned short st_rdev;    // device ID (if special file)
  unsigned int   st_size;    // total size, in bytes
  unsigned int   st_atime;   // time of last access
  unsigned int   st_mtime;   // time of last modification
  unsigned int   st_ctime;   // time of last status change
};
// old line comment removed
struct dir_entry {
  word inode;              // inode number
  byte filename[64];       // filename
};
// old line comment removed
struct diskfree_query {
  int device;         // device ID (is set before calling mx_diskfree)
  int size;           // size of filesystem, in blocks
  int used;           // number of used blocks
  int free;           // number of free blocks (redundant; == size-used)
  char name[10];      // name (such as "/dev/hda")
  char mount[256];    // mount point
  char fstype[10];    // filesystem name, e.g. "minix"
};
// old line comment removed
extern void initialize_module ();
// old line comment removed
void fill_gdt_entry (int num, ulong base, ulong limit, byte access, byte gran);
extern void gdt_flush ();
// old line comment removed
unsigned int pageno_to_frameno (unsigned int pageno);
// old line comment removed
void *request_new_page  ();
void *request_new_pages (int number_of_pages);
// old line comment removed
byte inportb (word port);
word inportw (word port);
void outportb (word port, byte data);
void outportw (word port, word data);
// old line comment removed
void fill_idt_entry (byte num, unsigned long address, 
    word gdtsel, byte flags, byte type);
// old line comment removed
extern void irq0(), irq1(), irq2(),  irq3(),  irq4(),  irq5(),  irq6(),  irq7();
extern void irq8(), irq9(), irq10(), irq11(), irq12(), irq13(), irq14(), irq15();
// old line comment removed
static void set_irqmask (word mask);
// old line comment removed
static void enable_interrupt (int number);
// old line comment removed
word get_irqmask ();
// old line comment removed
void install_interrupt_handler (int irq, void (*handler)(context_t *r));
// old line comment removed
extern void idt_load ();
// old line comment removed
extern void 
  fault0(),  fault1(),  fault2(),  fault3(),  fault4(),  fault5(),  fault6(),  
  fault7(),  fault8(),  fault9(),  fault10(), fault11(), fault12(), fault13(), 
  fault14(), fault15(), fault16(), fault17(), fault18(), fault19(), fault20(), 
  fault21(), fault22(), fault23(), fault24(), fault25(), fault26(), fault27(),
  fault28(), fault29(), fault30(), fault31();
// old line comment removed
void fault_handler (context_t *r);
// old line comment removed
int get_free_address_space ();
// old line comment removed
int create_new_address_space (int initial_ram, int initial_stack);
// old line comment removed
int as_map_page_to_frame (int as, unsigned int pageno, unsigned int frameno);
// old line comment removed
void destroy_address_space (addr_space_id id);
// old line comment removed
void add_to_kstack_delete_list (addr_space_id id);
// old line comment removed
inline void activate_address_space (addr_space_id id)  __attribute__((always_inline));
// old line comment removed
void list_address_spaces ();
// old line comment removed
unsigned int mmu_p (addr_space_id id, unsigned int pageno); // pageno -> frameno
memaddress mmu (addr_space_id id, memaddress vaddress); // virtual -> phys. addr.
// old line comment removed
void *u_sbrk (int incr);
// old line comment removed
void add     (thread_id t);
void block   (blocked_queue *q, int new_state); 
void deblock (thread_id t, blocked_queue *q);
void retire  (thread_id t);
// old line comment removed
void initialize_blocked_queue (blocked_queue *q);
// old line comment removed
void add_to_ready_queue (thread_id t);
void remove_from_ready_queue (thread_id t);
// old line comment removed
void add_to_blocked_queue          (thread_id t, blocked_queue *bq);
void remove_from_blocked_queue     (thread_id t, blocked_queue *bq);
thread_id front_of_blocked_queue   (blocked_queue bq);
// old line comment removed
int register_new_tcb (addr_space_id as_id);
// old line comment removed
static void write_tss (int num, word ss0, void *esp0);
// old line comment removed
extern void tss_flush ();
// old line comment removed
extern void cpu_usermode (memaddress address, memaddress stack);   // assembler
// old line comment removed
void install_syscall_handler (int syscallno, void *syscall_handler);
// old line comment removed
void syscall_sbrk (context_t *r);
// old line comment removed
void syscall_get_errno (context_t *r);
void syscall_set_errno (context_t *r);
// old line comment removed
void syscall_fork (context_t *r);
// old line comment removed
void syscall_exit (context_t *r);
// old line comment removed
void syscall_waitpid (context_t *r);
// old line comment removed
void syscall_resign (context_t *r);
// old line comment removed
void syscall_gettid (context_t *r);   // get thread ID
void syscall_getpid (context_t *r);   // get process ID
void syscall_getppid (context_t *r);  // get parent process ID
// old line comment removed
void syscall_getpsinfo (context_t *r);
// old line comment removed
void syscall_setpsname (context_t *r);
// old line comment removed
void syscall_execv (context_t *r);
// old line comment removed
void syscall_pthread_create (context_t *r);
// old line comment removed
void syscall_idle (context_t *r);
// old line comment removed
void syscall_page_out (context_t *r);
// old line comment removed
void syscall_get_free_frames (context_t *r);
void syscall_free_a_frame (context_t *r);
// old line comment removed
void syscall_clrscr (context_t *r);
void syscall_get_xy (context_t *r);
void syscall_set_xy (context_t *r);
// old line comment removed
void syscall_pthread_mutex_init (context_t *r);
// old line comment removed
void syscall_pthread_mutex_lock    (context_t *r);
void syscall_pthread_mutex_trylock (context_t *r);
void syscall_pthread_mutex_unlock  (context_t *r);
// old line comment removed
void syscall_pthread_mutex_destroy (context_t *r);
// old line comment removed
void syscall_readchar (context_t *r);
// old line comment removed
void syscall_open      (context_t *r);
void syscall_stat      (context_t *r);
void syscall_close     (context_t *r);
void syscall_read      (context_t *r);
void syscall_write     (context_t *r);
void syscall_lseek     (context_t *r);
void syscall_isatty    (context_t *r);
void syscall_mkdir     (context_t *r);
void syscall_rmdir     (context_t *r);
void syscall_getdent   (context_t *r);
void syscall_truncate  (context_t *r);
void syscall_ftruncate (context_t *r);
void syscall_link      (context_t *r);
void syscall_unlink    (context_t *r);
void syscall_symlink   (context_t *r);
void syscall_readlink  (context_t *r);
// old line comment removed
void syscall_getcwd (context_t *r);
void syscall_chdir (context_t *r);
// old line comment removed
void syscall_diskfree (context_t *r);
// old line comment removed
void syscall_sync (context_t *r);
// old line comment removed
void syscall_kill (context_t *r);
// old line comment removed
void syscall_signal (context_t *r);
// old line comment removed
void syscall_setuid  (context_t *r);
void syscall_setgid  (context_t *r);
void syscall_seteuid (context_t *r);
void syscall_setegid (context_t *r);
void syscall_login   (context_t *r);
// old line comment removed
void syscall_query_ids (context_t *r);
// old line comment removed
void syscall_chown (context_t *r);
void syscall_chmod (context_t *r);
// old line comment removed
void syscall_print_inode (context_t *r);
// old line comment removed
extern void syscallh ();
// old line comment removed
int get_errno ();
void set_errno (int err);
// old line comment removed
int u_fork (context_t *r);
// old line comment removed
extern memaddress get_eip ();
// old line comment removed
void wake_waiting_parent_process (int pid);
// old line comment removed
int u_execv (char *filename, char *const argv[], memaddress *newstack);
// old line comment removed
int u_pthread_create (pthread_t *restrict thread, const pthread_attr_t *restrict attr,
                      memaddress start_address, void *restrict arg);
// old line comment removed
void syscall_pthread_exit (context_t *r);
// old line comment removed
void scheduler (context_t *r, int source);
// old line comment removed
void page_fault_handler (context_t *regs);
// old line comment removed
int write_swap_page (int as, int pageno, int frameno);
int read_swap_page  (int as, int pageno, int frameno);
// old line comment removed
int page_out (int as, int pageno);
int page_in  (int as, int pageno);
// old line comment removed
int hash (int val, int maxval);
// old line comment removed
int hash (int val, int maxval) {
  // return val % maxval;   // ridiculous hash
  return ((val >> 20)*32 + (val & 0b1111111111)) % maxval;
}
// old line comment removed
void keyboard_handler (context_t *r);
// old line comment removed
void keyboard_install ();
// old line comment removed
void kgetch    (char *c);
void kreadline (char *s, int maxlength);
// old line comment removed
int vt_activate (int i);
// old line comment removed
void vt_move_cursor ();
// old line comment removed
void vt_clrscr ();
void vt_get_xy (char *x, char *y);
void vt_set_xy (char x, char y);
// old line comment removed
void read_write_screen (char *buf, boolean read_flag);
void read_screen (char *buf);
void write_screen (char *buf);
// old line comment removed
void kputch (byte c);
void kputs (char *text);
// old line comment removed
void uartputc (int c);
// old line comment removed
void set_statusline (char *text);
void _set_statusline (char *text, int offset);
// old line comment removed
void timer_phase (int hz);
// old line comment removed
ulong unixtime (int year, int month, int day, int hour, int minute, int second);
void rev_unixtime (ulong unixtime, short *year, char *month, char *day,
                   char *hour, char *minute, char *second);
// old line comment removed
void timer_handler (context_t *r);
// old line comment removed
void uart2putc (int);
// old line comment removed
kl_semaphore_id get_new_semaphore (int k);
void release_semaphore (kl_semaphore_id s);
// old line comment removed
void wait_semaphore (kl_semaphore_id sid);
void signal_semaphore (kl_semaphore_id sid);
// old line comment removed
void    mutex_lock     (lock lockvar);
boolean mutex_try_lock (lock lockvar);
void    mutex_unlock   (lock lockvar);
// old line comment removed
lock get_new_lock (char *name);
void release_lock (lock l);
// old line comment removed
int u_pthread_mutex_init (pthread_mutex_t *restrict mutex,
         const pthread_mutexattr_t *restrict attr);
// old line comment removed
int u_pthread_mutex_lock    (pthread_mutex_t *mutex);
int u_pthread_mutex_trylock (pthread_mutex_t *mutex);
int u_pthread_mutex_unlock  (pthread_mutex_t *mutex);
// old line comment removed
int u_pthread_mutex_destroy (pthread_mutex_t *mutex);
// old line comment removed
void print_mount_table ();
// old line comment removed
int get_dev_and_path (char *path, short *dev, short *fs, char *localpath);
// old line comment removed
int string_starts_with (char *str, char *start);
void split_mountpoint (char *mountpoint, char *path, char *localpath);
// old line comment removed
int u_open (char *path, int oflag, int open_link);
// old line comment removed
void relpath_to_abspath (const char *relpath, char *abspath);
// old line comment removed
int u_read      (int fd, void *buf, int nbyte);
int u_write     (int fd, void *buf, int nbyte);
int u_close     (int fd);
int u_lseek     (int fd, int offset, int whence);
int u_unlink    (const char *path);
int u_link      (const char *path, const char *path2);
int u_symlink   (const char *path, const char *path2);
int u_truncate  (const char *path, int length);
int u_ftruncate (int fd, int length);
int u_readlink  (char *path, char *restrict buf, size_t bufsize);
// old line comment removed
boolean u_isatty (int fd);
// old line comment removed
int u_stat (const char *path, struct stat *buf);
// old line comment removed
int u_mkdir (const char *path, int mode);
int u_rmdir (const char *path);
// old line comment removed
int u_getdent (const char *path, int index, struct dir_entry *buf);
// old line comment removed
int gfd2pfd (int gfd);
int pfd2gfd (int pfd);
// old line comment removed
int u_reopen (int fd);
// old line comment removed
char *u_getcwd (char *buf, int size);
int u_chdir (const char *path);
// old line comment removed
int mx_query_superblock (int device, char index);
// old line comment removed
int findZeroBitAndSet (byte *block, int maxindex);
// old line comment removed
int mx_read_inode  (int device, int i, struct minix2_inode *inodeptr);
int mx_write_inode (int device, int i, struct minix2_inode *inodeptr);
// old line comment removed
int mx_read_write_inode (int device, int i, struct minix2_inode *inodeptr, 
                         int wr_flag);
// old line comment removed
int mx_read_dir_entry  (int device, int inodenr, int entrynr, 
                        struct minix_dir_entry *entry);
int mx_write_dir_entry (int device, int inodenr, int entrynr, 
                        struct minix_dir_entry *entry);
// old line comment removed
void mx_write_link (int device, int inodenr, const char *filename);
// old line comment removed
int mx_increase_link_count (int device, int inodenr);
// old line comment removed
int mx_pathname_to_ino (int device, const char *path);
// old line comment removed
int mx_get_free_inodes_entry ();
int mx_get_free_status_entry ();
// old line comment removed
int mx_open (int device, const char *path, int oflag);
// old line comment removed
int mx_close (int mfd);
// old line comment removed
int mx_reopen (int mfd);
// old line comment removed
int mx_lseek (int mfd, int offset, int whence);
// old line comment removed
int mx_read (int mfd, void *buf, int nbyte);
// old line comment removed
int fileblocktozone (int device, int blockno, struct int_minix2_inode *inode);
// old line comment removed
int mx_write (int mfd, void *buf, int nbyte);
// old line comment removed
int mx_create_new_zone (int device, int blockno, struct int_minix2_inode *inode);
// old line comment removed
int mx_creat_empty_file (int device, const char *path, int mode);
// old line comment removed
boolean mx_file_exists (int device, const char *path);
boolean mx_file_is_directory (int device, const char *path);
int mx_link (int device, const char *path1, const char *path2);
// old line comment removed
int mx_unlink (int device, const char *path);
// old line comment removed
int mx_symlink (int device, char *path1, char *path2);
// old line comment removed
int mx_ftruncate (int mfd, int length);
// old line comment removed
int mx_mkdir (int device, const char *path, int mode);
// old line comment removed
int mx_rmdir (int device, const char *fullpath, const char *path);
// old line comment removed
boolean mx_directory_is_empty (int device, const char *path);
// old line comment removed
int mx_stat (int device, const char *path, struct stat *buf);
// old line comment removed
int mx_getdent (int device, const char *path, int index, struct dir_entry *buf);
// old line comment removed
void mx_diskfree (struct diskfree_query *query);
// old line comment removed
int dev_open (const char *path, int oflag);
// old line comment removed
int dev_close (int fd);
// old line comment removed
int dev_read (int fd, char *buf, int nbyte);
int dev_write (int fd, char *buf, int nbyte);
int dev_lseek (int fd, int offset, int whence);
// old line comment removed
long dev_size (int dev);
// old line comment removed
int dev_stat (const char *path, struct stat *buf);
int dev_getdent (const char *path, int index, struct dir_entry *buf);
// old line comment removed
void readblock  (int device, int blockno, char *buffer);
void writeblock (int device, int blockno, char *buffer);
// old line comment removed
word makedev  (byte major, byte minor);
byte devmajor (word device);
byte devminor (word device);
// old line comment removed
int buffer_write (int dev, int blockno, char *block, char dirtyflag);
int buffer_read  (int dev, int blockno, char *block);
boolean buffer_contains (int dev, int blockno);
// old line comment removed
void buffer_sync (boolean lock_buffer);
// old line comment removed
void readblock_nb_serial  (int secno, char *buf);
void writeblock_nb_serial (int secno, char *buf);
// old line comment removed
int serial_disk_blocking_rw ();
// old line comment removed
void readblock_serial  (int secno, char *buf);
void writeblock_serial (int secno, char *buf);
// old line comment removed
static inline void repeat_inportsl (int port, void *addr, int cnt);
// old line comment removed
static inline void repeat_outportsl (int port, void *addr, int cnt);
// old line comment removed
void readblock_hd  (int hd, int blockno, char *buffer);
void writeblock_hd (int hd, int blockno, char *buffer);
// old line comment removed
void ide_handler (context_t *r);
// old line comment removed
int idewait (int checkerr);
// old line comment removed
void fdc_out (byte data);
int fdc_getresults ();
// old line comment removed
void outb_delay (word __port, byte __value);
byte inb_delay (word __port);
// old line comment removed
int fdc_command (int cmd, int drive, int track, int sector);
// old line comment removed
void fdc_mode ();
// old line comment removed
void fdc_sleep ();
// old line comment removed
void fdc_wakeup ();
// old line comment removed
void fdc_timer ();
// old line comment removed
int wait_fdc_interrupt ();
// old line comment removed
int fdc_seek ();
// old line comment removed
int fdc_read_sector  (int device, int block, char *buffer);
int fdc_write_sector (int device, int block, char *buffer);
// old line comment removed
void readblock_fd  (int device, int blockno, char *buffer);
void writeblock_fd (int device, int blockno, char *buffer);
// old line comment removed
void fdc_reset ();
int  fdc_recalibrate ();
// old line comment removed
void fdc_init ();
// old line comment removed
int fdc_map_type (int t);
// old line comment removed
int u_kill (int pid, int signo);
// old line comment removed
sighandler_t u_signal (int sig, sighandler_t func);
// old line comment removed
boolean fileexists (char *abspath);
// old line comment removed
boolean check_access (char *path, word euid, word egid, word mode);
// old line comment removed
boolean check_perms (short what, word req_mode, word perms);
// old line comment removed
int u_setuid  (word uid);    // set user ID
int u_setgid  (word gid);    // set group ID
int u_seteuid (word euid);   // set effective user ID
int u_setegid (word egid);   // set effective group ID
int u_login (word uid, char *pass);
// old line comment removed
int u_chown (const char *path, short owner, short group);
int u_chmod (const char *path, word mode);
// old line comment removed
int mx_chown (int device, const char *path, short owner, short group);
int mx_chmod (int device, const char *path, word mode);
// old line comment removed
int mx_chinode (int device, const char *path, short owner, 
                short group, short mode);
// old line comment removed
int debug_printf (const char *format, ...);
// old line comment removed
void kernel_shell ();
// old line comment removed
void printbitsandhex (uint i);
// old line comment removed
void hexdump (uint startval, uint endval);
// old line comment removed
void ksh_print_page_table ();
// old line comment removed
                         
// old line comment removed
void splitpath (const char *path, char *dirname, char *basename);
char *basename (char *path);
char *dirname  (char *path);
// old line comment removed
size_t strlen (const char *str);
int    strcmp (const char *str1, const char *str2);
int    strncmp (const char *str1, const char *str2, uint n);
char   *strncpy (char *dest, const char *src, size_t count);
char   *strcpy  (char *dest, const char *src);
int    atoi (char *s);
int    atoi8 (char *s);
// old line comment removed
void *memcpy  (void *dest, const void *src, size_t count);
void *memset  (void *dest, char val, size_t count);
word *memsetw (word *dest, word val, size_t count);
// old line comment removed
int printf  (const char *format, ...);
int sprintf (char *out, const char *format, ...);
// old line comment removed
struct gdt_entry gdt[6];
struct gdt_ptr gp;
// old line comment removed
page_directory kernel_pd  __attribute__ ((aligned (4096)));
page_table     kernel_pt  __attribute__ ((aligned (4096)));

// prefer to work with pointers
page_directory *current_pd = &kernel_pd;
page_table     *current_pt = &kernel_pt;
// old line comment removed
char *kernel_pd_address;      // address of kernel page directory
// old line comment removed
page_table video_pt __attribute__ ((aligned (4096)));  // must be aligned!
// old line comment removed
unsigned int free_frames = NUMBER_OF_FRAMES;
// old line comment removed
char place_for_ftable[NUMBER_OF_FRAMES/8];
unsigned int *ftable = (unsigned int*)(&place_for_ftable);
// old line comment removed
page_table kernel_pt_ram[16] __attribute__ ((aligned (4096)));
// old line comment removed
struct idt_entry idt[256] = { { 0 } };
struct idt_ptr idtp;
// old line comment removed
void (*irqs[16])() = { 
  irq0, irq1, irq2,  irq3,  irq4,  irq5,  irq6,  irq7,      // store them in
  irq8, irq9, irq10, irq11, irq12, irq13, irq14, irq15      // an array
};
// old line comment removed
void *interrupt_handlers[16] = { 0 };
// old line comment removed
void (*faults[32])() = {
  fault0,  fault1,  fault2,  fault3,  fault4,  fault5,  fault6,  fault7,
  fault8,  fault9,  fault10, fault11, fault12, fault13, fault14, fault15,
  fault16, fault17, fault18, fault19, fault20, fault21, fault22, fault23,
  fault24, fault25, fault26, fault27, fault28, fault29, fault30, fault31
};
// old line comment removed
char *exception_messages[] = {
    "Division By Zero",        "Debug",                          //  0,  1
    "Non Maskable Interrupt",  "Breakpoint",                     //  2,  3
    "Into Detected Overflow",  "Out of Bounds",                  //  4,  5
    "Invalid Opcode",          "No Coprocessor",                 //  6,  7
    "Double Fault",            "Coprocessor Segment Overrun",    //  8,  9
    "Bad TSS",                 "Segment Not Present",            // 10, 11
    "Stack Fault",             "General Protection Fault",       // 12, 13
    "Page Fault",              "Unknown Interrupt",              // 14, 15
    "Coprocessor Fault",       "Alignment Check",                // 16, 17
    "Machine Check",                                             // 18
    "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved"                           // 19..31
};
// old line comment removed
address_space address_spaces[MAX_ADDR_SPACES] = { { 0 } };
// old line comment removed
addr_space_id kstack_delete_list[KSTACK_DELETE_LIST_SIZE] = { 0 };
// old line comment removed
addr_space_id current_as = 0;  // global variable: current address space
// old line comment removed
TCB thread_table[MAX_THREADS];
// old line comment removed
char *state_names[12] = {
  "---",   "READY", "---",   "FORK", "EXIT", "WAIT4", "ZOMBY", "W_KEY",   // 0.. 7
  "W_FLP", "W_LCK", "STOPD", "W_IDE"                                      // 8..11
};
// old line comment removed
thread_id next_pid = 1;
// old line comment removed
thread_id current_task;
// old line comment removed
tss_entry_struct tss_entry;
// old line comment removed
void *syscall_table[MAX_SYSCALLS];
// old line comment removed
int startup_errno = 0;
// old line comment removed
blocked_queue waitpid_queue;
// old line comment removed
TCB *t_old, *t_new;
// old line comment removed
int scheduler_is_active = false;
// old line comment removed
struct paging_entry paging[MAX_SWAP_FRAMES] = { { 0 } };
// old line comment removed
int swap_fd;
// old line comment removed
struct { boolean used; int count; } counter_table[PG_MAX_COUNTERS] = { { 0 } };
lock paging_lock;
// old line comment removed
lock swapper_lock;
// old line comment removed
byte scancode_table[128] = {
  /*  0.. 9 */    0,  KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8',
  /* 10..19 */   '9', '0', '-', '=', '\b',	 /* Backspace */
                 '\t', /* Tab */   'q', 'w', 'e', 'r',
  /* 20..29 */   't', 'y', 'u', 'i', 'o', 'p', '[', ']', 
                 '\n', /* Enter */  0, /* Control */
  /* 30..39 */   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
  /* 40..49 */   '\'', '`', 0, /* Left shift */  '\\', 'z', 'x', 'c', 'v', 'b', 'n',
  /* 50..59 */   'm', ',', '.', '/', 0, /* Right shift */
                 '*', 0, /* Alt */  ' ', /* Space bar */
                 0, /* CapsLock */  0, /* F1 */
  /* 60..69 */   0, 0, 0, 0, 0, 0, 0, 0, 0, /* F2..F10 */  0, /* NumLock */
  /* 70..79 */   0, /* Scroll Lock */  0, /* Home */  KEY_UP, 0, /* Page Up */
                 '-', KEY_LEFT, 0, KEY_RIGHT,  '+', 0, /* End */
  /* 80..89 */   KEY_DOWN, 0, /* Page Down */  0, /* Insert */  0, /* Delete */
                 0, 0, 0, 0, /* F11 */  0, /* F12 */   0,
  /* 90..127     not defined */
};

byte scancode_up_table[128] = {
  /*  0.. 9 */    0,  KEY_ESC, '!', '@', '#', '$', '%', '^', '&', '*',
  /* 10..19 */   '(', ')', '_', '+', '\b',	 /* Backspace */
                 '\t', /* Tab */   'Q', 'W', 'E', 'R',
  /* 20..29 */   'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 
                 '\n', /* Enter */  0, /* Control */
  /* 30..39 */   'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
  /* 40..49 */   '"', '~', 0, /* Left shift */  '|', 'Z', 'X', 'C', 'V', 'B', 'N',
  /* 50..59 */   'M', '<', '>', '?', 0, /* Right shift */
                 '*', 0, /* Alt */  ' ', /* Space bar */
                 0, /* CapsLock */  0, /* F1 */
  /* 60..69 */   0, 0, 0, 0, 0, 0, 0, 0, 0, /* F2..F10 */  0, /* NumLock */
  /* 70..79 */   0, /* Scroll Lock */   0, /* Home */  KEY_UP, 0, /* Page Up */
                 '-', KEY_LEFT, 0, KEY_RIGHT, '+', 0, /* End */
  /* 80..89 */   KEY_DOWN, 0, /* Page Down */  0, /* Insert */  0, /* Delete */
                 0, 0, 0, 0, /* F11 */  0, /* F12 */   0,
  /* 90..127     not defined */
};
// old line comment removed
byte scancode_DE_table[128] = {
  /*  0.. 9 */   '^',  KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8',
  /* 10..19 */   '9', '0', '-', '\'', '\b',	 /* Backspace */
                 '\t', /* Tab */  'q', 'w', 'e', 'r',
  /* 20..29 */   't', 'z', 'u', 'i', 'o', 'p', '[', '+', 
                 '\n', /* Enter */  0, /* Control */
  /* 30..39 */   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
  /* 40..49 */   '\'', '<', 0, /* Left shift */  '#', 'y', 'x', 'c', 'v', 'b', 'n',
  /* 50..59 */   'm', ',', '.', '-', 0, /* Right shift */
                 '*', 0, /* Alt */  ' ', /* Space bar */
                 0, /* CapsLock */  0, /* F1 */
  /* 60..69 */   0, 0, 0, 0, 0, 0, 0, 0, 0, /* F2..F10 */  0, /* NumLock */
  /* 70..79 */   0, /* Scroll Lock */   0, /* Home */  KEY_UP, 0, /* Page Up */
                 '-', KEY_LEFT, 0, KEY_RIGHT, '+', 0, /* End */
  /* 80..89 */   KEY_DOWN, 0, /* Page Down */  0, /* Insert */    0, /* Delete */
                 0, 0, 0, 0, /* F11 */  0, /* F12 */   0,
  /* 90..127     not defined */
};

byte scancode_DE_up_table[128] = {
  /*  0.. 9 */   '^',  KEY_ESC, '!', '"', '#', '$', '%', '&', '/', '(',
  /* 10..19 */   ')', '=', '?', '`', '\b',	 /* Backspace */
                 '\t', /* Tab */   'Q', 'W', 'E', 'R',	
  /* 20..29 */   'T', 'Y', 'U', 'I', 'O', 'P', '{', '*', 
                 '\n', /* Enter */  0, /* Control */
  /* 30..39 */   'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
  /* 40..49 */   '"', '>', 0, /* Left shift */  '\'', 'Z', 'X', 'C', 'V', 'B', 'N',
  /* 50..59 */   'M', ';', ':', '_', 0, /* Right shift */
                 '*', 0, /* Alt */  ' ', /* Space bar */
                 0, /* CapsLock */  0, /* F1 */
  /* 60..69 */   0, 0, 0, 0, 0, 0, 0, 0, 0, /* F2..F10 */  0, /* NumLock */
  /* 70..79 */   0, /* Scroll Lock */   0, /* Home */  KEY_UP, 0, /* Page Up */
                 '-', KEY_LEFT, 0, KEY_RIGHT, '+', 0, /* End */
  /* 80..89 */   KEY_DOWN, 0, /* Page Down */  0, /* Insert */    0, /* Delete */
                 0, 0, 0, 0, /* F11 */  0, /* F12 */   0,
  /* 90..127     not defined */
};
// old line comment removed
terminal_t terminals[TERMINALS] = { { { 0 } } };
// old line comment removed
char *system_kbd = terminals[0].kbd;
int system_kbd_pos;
int system_kbd_lastread;
int system_kbd_count;
// old line comment removed
boolean LANG_GERMAN = 1;   // default: german keyboard
// old line comment removed
blocked_queue keyboard_queue;   // processes which wait for a keystroke
// old line comment removed
term_buffer vt[MAX_VT+1];
int cur_vt = 0;
// old line comment removed
uint VIDEORAM = 0xB8000;
byte csr_x = 0; byte csr_y = 0;   // Cursor position
// old line comment removed
short int KERNEL_VT = 0;
// old line comment removed
unsigned int system_ticks = 0; // updated 100 times a second
unsigned int system_time;      // unix time (in seconds)
// old line comment removed
unsigned long system_start_time = 0;
// old line comment removed
static int uart[2];    // do we have serial ports?
// old line comment removed
kl_semaphore kl_semaphore_table[MAX_SEMAPHORES];
// old line comment removed
kl_semaphore_id next_kl_semaphore = 0;
// old line comment removed
lock_t kernel_locks[MAX_LOCKS];
// old line comment removed
boolean if_state;   // state of the interrupt flag (IF)
// old line comment removed
mount_table_entry mount_table[16] = { 
  { "/",     FS_MINIX, DEV_HDA,  0 },
  { "/mnt/", FS_MINIX, DEV_FD1,  0 },
  { "/tmp/", FS_MINIX, DEV_HDB,  0 },
  { "/dev/", FS_DEV,   DEV_NONE, 0 },  
  { { 0 } }
};
short current_mounts = 4;   // how many FSs are mounted?
// old line comment removed
char *fs_names[] = { "ERROR", "minix", "fat", "dev" };
// old line comment removed
struct int_minix2_inode mx_inodes[MAX_INT_INODES] = {{ 0 }};
// old line comment removed
struct mx_filestat mx_status[MX_MAX_FILES] = { { 0 } };
// old line comment removed
int count_open_files = 0;  // number of open_ files
int count_int_inodes = 0;  // number of internal inodes in use
// old line comment removed
struct minix_dir_entry dev_directory[7] = {
  { 1, "." },          { 2, ".." },         { 3, DEV_FD0_NAME }, 
  { 4, DEV_FD1_NAME }, { 5, DEV_HDA_NAME }, { 6, DEV_HDB_NAME },
  { 7, DEV_KMEM_NAME } };  
// old line comment removed
struct dev_filestat dev_status[MAX_DEV_FILES] = { { 0 } };
// old line comment removed
struct buffer_entry buffer_cache[BUFFER_CACHE_SIZE];
lock buffer_lock;
// old line comment removed
struct serial_disk_buffer_entry serial_disk_buffer[SER_BUF_SIZE];
int serial_disk_buffer_start = 0;   // initialize start_ and end of buffer usage
int serial_disk_buffer_end   = 0;   // interval in use is [start_, end[, 
                                    // [0,0[ is empty
// old line comment removed
lock serial_disk_lock;
// old line comment removed
volatile int serial_disk_reader = 0;   // are we currently reading?
// old line comment removed
char    serial_hard_disk_buffer[1024];
int     serial_hard_disk_pos    = 0;
boolean serial_hard_disk_blocks = false;
// old line comment removed
blocked_queue serial_disk_queue;
// old line comment removed
blocked_queue harddisk_queue;   // processes which wait for the hard disk
// old line comment removed
char hd_buf[HD_SECSIZE];
lock hd_lock;
char hd_direction;
// old line comment removed
ulonglong hd_size[2] = {-1, -1};
// old line comment removed
static volatile int fdc_need_reset = 0;
// old line comment removed
byte fdc_results[MAX_FLOPPY_RESULTS];
// old line comment removed
static char *fdc_buf = (char *)0x9a800;
// old line comment removed
static int fdc_drive, fdc_track, fdc_head;
// old line comment removed
char *fdd_drive_name[6] = {
  "not installed", "360 KByte (not supported)",
  "1200 KByte",    "720 KByte (not supported)",
  "1440 KByte",    "2880 KByte (not supported)" };

struct_fdd_type fdd_type[2] = {
  { 80*15*2, 80, 15, 2, 0, 0, 0x1B, 0xDF },           /* 1.2M   */
  { 80*18*2, 80, 18, 2, 0, 0, 0x1B, 0xCF }      };    /* 1.44M  */
//  { 80*36*2, 80, 36, 2, 0, 3, 0x1B, 0xAF },           /* 2.88M  */  // REMOVE_DEBUGGING_CODE

struct_fdd_type *current_fdd_type;
struct_fdd fdd[2] = { { 0, 0, 0, INVALID_TRACK, 0 },  { 0, 0, 0, INVALID_TRACK, 0 } };
int fdds_in_use[2] = { 0, 0 };
struct_fdd *current_fdd;
// old line comment removed
blocked_queue floppy_queue;   // processes which wait for the floppy
// old line comment removed
short int fdc_is_busy = false;
// old line comment removed
int     fdc_ticks                  = 0;
int     fdc_ticks_till_motor_stops = 0;
boolean fdc_timeout                = false;
boolean fdc_waits_interrupt        = false;
// old line comment removed
lock fdc_lock;
// old line comment removed
extern memaddress stack_first_address, stack_last_address;
// old line comment removed
memaddress page_desc_2_frame_address (page_desc pd) {
  // pointer magic/cast: a page descriptor is not really an unsigned
  // int, but we want to treat it as one
  memaddress address = *(memaddress*)(&pd);
  return address & 0xFFFFF000;   // set lowest 12 bits to zero
}
// old line comment removed
page_desc *fill_page_desc (page_desc *pd, unsigned int present,
                           unsigned int writeable, unsigned int user_accessible,
                           unsigned int dirty, memaddress frame_addr) {

  memset (pd, 0, sizeof (page_desc));      // first fill the four bytes with zeros
  
  pd->present         = present;           // then enter the argument values in  
  pd->writeable       = writeable;         // the proper struct members
  pd->user_accessible = user_accessible;
  pd->dirty           = dirty;
  pd->frame_addr      = frame_addr >> 12;  // right shift, discard lower 12 bits
  return pd;
};
// old line comment removed
memaddress page_table_desc_2_frame_address (page_table_desc ptd) {
  memaddress address = *(memaddress*)(&ptd);
  return address & 0xFFFFF000;
}
// old line comment removed
page_table_desc *fill_page_table_desc (page_table_desc *ptd, unsigned int present,
                           unsigned int writeable, unsigned int user_accessible,
                           memaddress frame_addr) {

  memset (ptd, 0, sizeof (page_table_desc));  // fill the four bytes with zeros
  
  ptd->present         = present;             // then enter the argument values
  ptd->writeable       = writeable;
  ptd->user_accessible = user_accessible;
  ptd->frame_addr      = frame_addr >> 12;    // right shift, 12 bits
  return ptd;
};
// old line comment removed
void fill_gdt_entry (int num, ulong base, ulong limit, byte access, byte gran) {
  // base address; split in three parts
  gdt[num].base_low    = (base & 0xFFFF);         // 16 bits
  gdt[num].base_middle = (base >> 16) & 0xFF;     //  8 bits
  gdt[num].base_high   = (base >> 24) & 0xFF;     //  8 bits

  // limit address; split in two parts
  gdt[num].limit_low   = (limit & 0xFFFF);        // 16 bits
  gdt[num].limit_high  = (limit >> 16) & 0x0F;    //  4 bits

  // granularity and access flags
  gdt[num].flags       = gran & 0xF;
  gdt[num].access      = access;
}
// old line comment removed
static void set_frame (memaddress frame_addr) {
  unsigned int frame = frame_addr / PAGE_SIZE;
  unsigned int index = INDEX_FROM_BIT (frame);
  unsigned int offset = OFFSET_FROM_BIT (frame);
  ftable[index] |= (1 << offset);
}

static void clear_frame (memaddress frame_addr) {
  unsigned int frame = frame_addr / PAGE_SIZE;
  unsigned int index = INDEX_FROM_BIT (frame);
  unsigned int offset = OFFSET_FROM_BIT (frame);
  ftable[index] &= ~(1 << offset);
}
// old line comment removed
static boolean test_frame (unsigned int frame) {
  // returns true if frame is in use (false if frame is free)
  unsigned int index = INDEX_FROM_BIT (frame);
  unsigned int offset = OFFSET_FROM_BIT (frame);
  return ((ftable[index] & (1 << offset)) >> offset);
}
// old line comment removed
unsigned int pageno_to_frameno (unsigned int pageno) {
  unsigned int pdindex = pageno/1024;
  unsigned int ptindex = pageno%1024;
  if ( ! current_pd->ptds[pdindex].present ) {
    return -1;       // we don't have that page table
  } else {
    // get the page table
    page_table *pt = (page_table*)
                     ( PHYSICAL(current_pd->ptds[pdindex].frame_addr << 12) );
    if ( pt->pds[ptindex].present ) {
      return pt->pds[ptindex].frame_addr;
    } else {
      return -1;     // we don't have that page
    };
  };    
};
// old line comment removed
int request_new_frame () {
  
// old line comment removed
unsigned int frameid;
boolean found;
//inside_req_frame++;                                         // REMOVE_DEBUGGING_CODE
start_find_frame:
//if (inside_req_frame > 1)                                   // REMOVE_DEBUGGING_CODE
//  printf ("WARNING: request_new_frame() recursion (%d)!\n", // REMOVE_DEBUGGING_CODE
//  inside_req_frame);                                        // REMOVE_DEBUGGING_CODE
found = false;
for (frameid = 0;  frameid < NUMBER_OF_FRAMES;  frameid++) {
  if ( !test_frame (frameid) ) {
    found=true;
    break;   // frame found
  };
}
// old line comment removed
if (found) {
  // memset ((void*)PHYSICAL(frameid << 12), 0, PAGE_SIZE); // REMOVE_DEBUGGING_CODE
  set_frame (frameid*4096);
  free_frames--;
  // inside_req_frame--;                                    // REMOVE_DEBUGGING_CODE
  // printf ("NEW FRAME: 0x%0x\n", frameid);                // REMOVE_DEBUGGING_CODE
  return frameid;
} else {
  
// old line comment removed
/*                                                                    // REMOVE_DEBUGGING_CODE
printf ("DEBUG: COUNTER TABLE\n");                                    // REMOVE_DEBUGGING_CODE
for (int i = 0; i < PG_MAX_COUNTERS; i++) {                           // REMOVE_DEBUGGING_CODE
  if (counter_table[i].used && counter_table[i].count != 0) {         // REMOVE_DEBUGGING_CODE
    printf ("DEBUG: %8d: count = %3d\n", i, counter_table[i].count);  // REMOVE_DEBUGGING_CODE
  }                                                                   // REMOVE_DEBUGGING_CODE
}                                                                     // REMOVE_DEBUGGING_CODE
*/                                                                    // REMOVE_DEBUGGING_CODE
addr_space_id pick_as      = -1;
int           pick_pageno, themin;
// printf ("\nDEBUG:  starting search for page to evict\n");          // REMOVE_DEBUGGING_CODE
while (!mutex_try_lock (paging_lock)) ;    // active waiting for lock
for (int as = 1;  as < MAX_ADDR_SPACES;  as++) {
  if (address_spaces[as].status == AS_USED) {
    page_directory *pd = address_spaces[as].pd;
    for (int i = 0;  i < 768;  i++) {      // < 768: only work on process memory
      if (pd->ptds[i].present) {           // directory entry in use
        page_table *pt = (page_table*) (PHYSICAL ((pd->ptds[i].frame_addr) << 12));
        for (int j = 0;  j < 1024;  j++) {
          if (pt->pds[j].present) {        // table entry in use
            int pageno = i*1024 + j;
            int index = hash ((as << 20) | pageno, PG_MAX_COUNTERS);
            if (pick_as==-1 && counter_table[index].used) {
              // initialize minimum, pick
              pick_as     = as;
              pick_pageno = pageno;
              themin = counter_table[index].count;
              //printf ("INIT:   pick (%d,%d)\n", as, pageno);        // REMOVE_DEBUGGING_CODE
            } else {
              if (counter_table[index].count < themin) {
                  // && address_spaces[as].status == AS_USED) {       // REMOVE_DEBUGGING_CODE
                themin = counter_table[index].count;
                pick_as     = as;
                pick_pageno = pageno;
                // printf ("UPDATE: pick (%d,%d)\n", as, pageno);     // REMOVE_DEBUGGING_CODE
              }
            }
          }
        }
      }
    }
  }
}
mutex_unlock (paging_lock);

if (pick_as != -1) {
  debug_printf ("DEBUG: BEFORE calling page_out (as=%d, pageno=%d)\n", pick_as, pick_pageno);  // REMOVE_DEBUGGING_CODE
  mutex_lock (paging_lock);
  page_out (pick_as, pick_pageno);
  mutex_unlock (paging_lock);
  // debug_printf ("DEBUG: AFTER  calling page_out (as=%d, pageno=%d)\n", pick_as, pick_pageno);  // REMOVE_DEBUGGING_CODE
} else {
  printf ("\nERROR: cannot pick a page to evict!\n");
//  inside_req_frame--;   // for debugging, REMOVE ME!!!              // REMOVE_DEBUGGING_CODE   
}
// old line comment removed
                                          // will be explained later
  goto start_find_frame;
  // return -1;    // never fail
}
// old line comment removed
};
// old line comment removed
void release_frame (int frame) {
  if ( test_frame (frame) ) {
    // only do work if frame is marked as used
    clear_frame (frame << 12);
    free_frames++;
  };
};
// old line comment removed
void *request_new_page () { return request_new_pages (1); }
// old line comment removed
void *request_new_pages (int number_of_pages) {
  
// old line comment removed
unsigned int first_page = 0xc0000;  // first page
unsigned int count = 0;             // number of contiguous pages
while (count < number_of_pages && first_page+count <= 0xfffff) {
  if ( mmu_p (current_as, first_page + count) == -1 ) {
    count++;
  } else {
    // the block we just looked at is too small
    first_page += (count+1);        // restart search
    count = 0;
  }
}
if (count != number_of_pages)
  return NULL;   // could not find a sufficiently large area
// old line comment removed
  
// old line comment removed
for (int pageno = first_page;  pageno < first_page+count;  pageno++) {
  int newframeid = request_new_frame ();  // get a fresh frame for this page
  if (newframeid == -1) {                 // exit_ if no frame was found
    // this can only happen if the swap file is full
    return NULL; 
  }
  unsigned int pdindex = pageno/1024;
  unsigned int ptindex = pageno%1024;
  page_table *pt;
  if (ptindex == 0 && !current_pd->ptds[pdindex].present) {
    // new page table!
    
// old line comment removed
//page_table *                    // REMOVE_DEBUGGING_CODE
pt = (page_table*) PHYSICAL(newframeid<<12);
memset (pt, 0, PAGE_SIZE);
// old line comment removed
// KMAPD ( &(current_pd->ptds[pdindex]), newframeid << 12 );
// old line comment removed
for (addr_space_id asid=0; asid<1024; asid++) {
  if (address_spaces[asid].status == AS_USED) {  // is this address space in use?
    page_directory *tmp_pd = address_spaces[asid].pd;
    KMAPD ( &(tmp_pd->ptds[pdindex]), newframeid << 12 );
  }
}
// old line comment removed
    newframeid = request_new_frame ();    // get yet another frame
    if (newframeid == -1) {
      return NULL;                        // exit_ if no frame was found
      // again, this can only happen if the swap file is full
      // note: we're not removing the new page    // REMOVE_DEBUGGING_CODE
      // table since we assume                    // REMOVE_DEBUGGING_CODE
      // it will be used soon anyway              // REMOVE_DEBUGGING_CODE
    }
  };
// old line comment removed
  if ( !current_pd->ptds[pdindex].present ) {
    // we don't have that page table -- this should not happen!
    kputs ("FAIL! No page table entry\n");
    return NULL;
  } else {
    // get the page table
    pt = (page_table*)( PHYSICAL(current_pd->ptds[pdindex].frame_addr << 12) );
    // enter the frame address
    KMAP ( &(pt->pds[ptindex]), newframeid * PAGE_SIZE );
    // invalidate cache entry
    asm volatile ("invlpg %0" : : "m"(*(char*)(pageno<<12)) );
  };
// old line comment removed
  memset ((void*) (pageno*4096), 0, 4096);
}
return ((void*) (first_page*4096));
// old line comment removed
};
// old line comment removed
void release_page (unsigned int pageno) {
  
// old line comment removed
// int frameno = pageno_to_frameno (pageno);
int frameno = mmu_p (current_as, pageno);  // we will need this later
if ( frameno == -1 )  { return; }          // exit_ if no such page
// old line comment removed
unsigned int pdindex = pageno/1024;
unsigned int ptindex = pageno%1024;
page_table *pt;
pt = (page_table*)( PHYSICAL(current_pd->ptds[pdindex].frame_addr << 12) );

// write null page descriptor
fill_page_desc ( &(pt->pds[ptindex]), false, false, false, false, 0 );

// invalidate cache entry
asm volatile ("invlpg %0" : : "m"(*(char*)(pageno<<12)) );
// old line comment removed
  
// old line comment removed
release_frame (frameno);  // note: this increases free_frames
// old line comment removed
};
// old line comment removed
void release_page_range (unsigned int start_pageno, unsigned int end_pageno) {
  for (int i = start_pageno;  i < end_pageno+1;  i++)  release_page (i);    
};
// old line comment removed
byte inportb (word port) {
  byte retval;  asm volatile ("inb %%dx, %%al" : "=a"(retval) : "d"(port));
  return retval;
}

word inportw (word port) {
  word retval;  asm volatile ("inw %%dx, %%ax" : "=a" (retval) : "d" (port));
  return retval;
}

void outportb (word port, byte data) {
  asm volatile ("outb %%al, %%dx" : : "d" (port), "a" (data));
}

void outportw (word port, word data) {
  asm volatile ("outw %%ax, %%dx" : : "d" (port), "a" (data));
}
// old line comment removed
void fill_idt_entry (byte num, unsigned long address, 
    word gdtsel, byte flags, byte type) {
  if (num >= 0 && num < 256) {
    idt[num].addr_low  = address & 0xFFFF; // address is the handler address
    idt[num].addr_high = (address >> 16) & 0xFFFF;
    idt[num].gdtsel    = gdtsel;           // GDT sel.: user mode or kernel mode?
    idt[num].zeroes    = 0;
    idt[num].flags     = flags;
    idt[num].type      = type;
  }
}
// old line comment removed
static void set_irqmask (word mask) {
  outportb (IO_PIC_MASTER_DATA, (char)(mask % 256) );
  outportb (IO_PIC_SLAVE_DATA,  (char)(mask >> 8)  );
}
// old line comment removed
word get_irqmask () {
  return inportb (IO_PIC_MASTER_DATA) 
      + (inportb (IO_PIC_SLAVE_DATA) << 8);
}
// old line comment removed
static void enable_interrupt (int number) {
  set_irqmask ( 
    get_irqmask ()        // the current value
    & ~(1 << number)      // 16 one-bits, but bit "number" cleared
  );
}
// old line comment removed
void irq_handler (context_t *r) {
  int number = r->int_no - 32;                      // interrupt number
  void (*handler)(context_t *r);                    // type of handler functions

  if (number >= 8) { 
    outportb (IO_PIC_SLAVE_CMD, END_OF_INTERRUPT);  // notify slave  PIC
  }
  outportb (IO_PIC_MASTER_CMD, END_OF_INTERRUPT);   // notify master PIC (always)

  handler = interrupt_handlers[number];
  if (handler != NULL) {
    handler (r);
  }
}
// old line comment removed
void install_interrupt_handler (int irq, void (*handler)(context_t *r)) {
  if (irq >= 0 && irq < 16)
    interrupt_handlers[irq] = handler;
}
// old line comment removed
void fault_handler (context_t *r) {
  if (r->int_no == 14) {                             // fault 14 is a page fault
    page_fault_handler (r); return;
  }
  
  memaddress fault_address = (memaddress)(r->eip);
  
  if (r->int_no < 32) {
    
// old line comment removed
printf ("'%s' Exception at 0x%08x (task=%d, as=%d).\n", 
  exception_messages[r->int_no], r->eip, current_task, current_as);        
printf ("eflags: 0x%08x  errcode: 0x%08x\n", r->eflags, r->err_code);
printf ("eax: %08x  ebx: %08x  ecx: %08x  edx: %08x \n",
  r->eax, r->ebx, r->ecx, r->edx);
printf ("eip: %08x  esp: %08x  int: %8d  err: %8d \n", 
  r->eip, r->esp, r->int_no, r->err_code);
printf ("ebp: %08x  cs: 0x%02x ds: 0x%02x es: 0x%02x fs: 0x%02x ss: 0x%02x \n",
  r->ebp, r->cs, r->ds, r->es, r->fs, r->ss);
printf ("User mode stack: 0x%08x-0x%08x\n", TOP_OF_USER_MODE_STACK 
  - address_spaces[current_as].stacksize, TOP_OF_USER_MODE_STACK);
// old line comment removed
    
    if ( fault_address < 0xc0000000 ) {              // user mode 
      
// old line comment removed
thread_table[current_task].state = TSTATE_ZOMBIE;
remove_from_ready_queue (current_task);
r->ebx = -1;  // exit_ code for this process
syscall_exit (r);
// old line comment removed
    }
    
    
// old line comment removed
scheduler_is_active = false;  _set_statusline ("SCH:OFF", 16);
// old line comment removed
                                                     // error inside the kernel
    
// old line comment removed
asm ("sti");    // set interrupt flag
// old line comment removed
    printf ("\n");   
    asm ("jmp kernel_shell");
  }
}
// old line comment removed
int get_free_address_space () {
  addr_space_id id = 0;
  while ((address_spaces[id].status != AS_FREE) && (id < MAX_ADDR_SPACES)) id++;
  if (id == MAX_ADDR_SPACES) id = -1;
  return id;
}
// old line comment removed
int create_new_address_space (int initial_ram, int initial_stack) {
  MAKE_MULTIPLE_OF_PAGESIZE (initial_ram);
  MAKE_MULTIPLE_OF_PAGESIZE (initial_stack);
  // reserve address space table entry
  addr_space_id id;
  if ( (id = get_free_address_space ()) == -1 )  return -1;    // fail
  address_spaces[id].status    = AS_USED;
  address_spaces[id].memstart  = BINARY_LOAD_ADDRESS;
  address_spaces[id].memend    = BINARY_LOAD_ADDRESS + initial_ram;
  address_spaces[id].stacksize = initial_stack;
  address_spaces[id].refcount  = 1;  // default: used by one process
  
// old line comment removed
page_directory *new_pd = request_new_page ();
if (new_pd == NULL) {  // Error
  printf ("\nERROR: no free page, aborting create_new_address_space\n");
  return -1;
};
memset (new_pd, 0, sizeof (page_directory));
// old line comment removed
                                              // sets new_pd
  address_spaces[id].pd = new_pd;
  
// old line comment removed
*new_pd = kernel_pd;
memset ((char*)new_pd, 0, 4);    // clear first entry (kernel pd contains
                                 // old reference to some page table)

// old line comment removed
  int frameno, pageno;  // used in the following two code chunks
  if (initial_ram > 0)   {  
// old line comment removed
pageno = 0;
while (initial_ram > 0) {
  if ((frameno = request_new_frame ()) < 0) {
    printf ("\nERROR: no free frame, aborting create_new_address_space\n");
    return -1;
  };
  as_map_page_to_frame (id, pageno, frameno);
  pageno++;
  initial_ram -= PAGE_SIZE;
};
// old line comment removed
                                                                 }
  if (initial_stack > 0) {  
// old line comment removed
pageno = TOP_OF_USER_MODE_STACK / PAGE_SIZE;
while (initial_stack > 0) {
  if ((frameno = request_new_frame ()) < 0) {
    printf ("\nERROR: no free frame, aborting create_new_address_space\n");
    return -1;
  };
  pageno--;
  as_map_page_to_frame (id, pageno, frameno);
  initial_stack -= PAGE_SIZE;
}
// old line comment removed
                                                                   }
  return id;
};
// old line comment removed
int as_map_page_to_frame (int as, unsigned int pageno, unsigned int frameno) {
  // for address space as, map page #pageno to frame #frameno
  page_table *pt;
  page_directory *pd;

  pd = address_spaces[as].pd;           // use the right address space
  unsigned int pdindex = pageno/1024;   // calculuate pd entry
  unsigned int ptindex = pageno%1024;   // ... and pt entry

  if ( ! pd->ptds[pdindex].present ) {
    // page table is not present
    
// old line comment removed
int new_frame_id = request_new_frame ();
memaddress address = PHYSICAL (new_frame_id << 12);
pt = (page_table *) address;
memset (pt, 0, sizeof (page_table));
UMAPD ( &(pd->ptds[pdindex]), new_frame_id << 12);
// old line comment removed
                                                      // sets pt
  } else {
    // get the page table
    pt = (page_table*) PHYSICAL(pd->ptds[pdindex].frame_addr << 12);
  };
  if (pdindex < 704)   // address below 0xb0000000 -> user access
    UMAP ( &(pt->pds[ptindex]), frameno << 12 );
  else
    KMAP ( &(pt->pds[ptindex]), frameno << 12 );
  return 0;
};
// old line comment removed
void destroy_address_space (addr_space_id id) {
  // called only from syscall_exit(), with interrupts off
  if (--address_spaces[id].refcount > 0) return;
  addr_space_id as = current_as;          // remember current address space
  current_as = id;                        // set current_as: we call release_page()

  
// old line comment removed
for ( int i = address_spaces[id].memstart / PAGE_SIZE;
      i < address_spaces[id].memend / PAGE_SIZE;
      i++ ) {
  release_page (i);
};
// old line comment removed
                                          // all pages used by the process
  
// old line comment removed
for ( int i = TOP_OF_USER_MODE_STACK / PAGE_SIZE - 1;
      i > (TOP_OF_USER_MODE_STACK-address_spaces[id].stacksize) / PAGE_SIZE - 1;
      i-- ) {
  release_page (i);
};
// old line comment removed
                                           // all its user mode stack pages
  
// old line comment removed
page_directory *tmp_pd = address_spaces[id].pd;
for (int i = 0;  i < 704;  i++) {
  if (tmp_pd->ptds[i].present)
    release_frame (tmp_pd->ptds[i].frame_addr);
}
// old line comment removed
                                           // the page tables (0..703)
  
  current_as = as;                        // restore current_as
  address_spaces[id].status = AS_DELETE;  // change AS status
  
  // remove kernel stack (cannot do this here, this stack is in use right now)
  add_to_kstack_delete_list (id);
}
// old line comment removed
void add_to_kstack_delete_list (addr_space_id id) {
  
// old line comment removed
// do nothing
// old line comment removed
  int i;
  for (i = 0;  i < KSTACK_DELETE_LIST_SIZE;  i++) {
    // try to enter it here
    if (kstack_delete_list[i] == 0) {
      // found a free entry
      kstack_delete_list[i] = id;  break;
    }
  }
  
// old line comment removed
// do nothing
// old line comment removed
  if (i == KSTACK_DELETE_LIST_SIZE) 
    printf ("ERROR ADDING ADDRESS SPACE TO KSTACK DELETE LIST!\n");
}
// old line comment removed
inline void activate_address_space (addr_space_id id) {
  // NOTE: Do not call this from the scheduler_ - where needed, replicate the code
  memaddress virt = (memaddress)address_spaces[id].pd;  // get PD address
  memaddress phys = mmu (0, virt);              // and find its physical address
  asm volatile ("mov %0, %%cr3" : : "r"(phys)); // write CR3 register
  current_as = id;                              // set current address space
  current_pd = address_spaces[id].pd;           // set current page directory
};
// old line comment removed
void list_address_space (addr_space_id id) {
  int mem  = (memaddress) address_spaces[id].pd;
  int phys = mmu (id, (memaddress) address_spaces[id].pd);  // emulate MMU
  int memstart = address_spaces[id].memstart;
  int memend = address_spaces[id].memend;
  int stack = address_spaces[id].stacksize;
  printf ("ID: %d, MEM: %08x, PHYS: %08x  - USER: %08x, USTACK: %08x\n", 
    id, mem, phys, memend-memstart, stack); 
}
// old line comment removed
void list_address_spaces () {
  addr_space_id id;
  for (id = 0;  id < MAX_ADDR_SPACES;  id++) {
    if (address_spaces[id].status != AS_FREE) {
      list_address_space (id);
    }
  }
}
// old line comment removed
unsigned int mmu_p (addr_space_id id, unsigned int pageno) {
  unsigned int pdindex = pageno/1024;
  unsigned int ptindex = pageno%1024;
  page_directory *pd = address_spaces[id].pd;
  if ( ! pd->ptds[pdindex].present ) {
    return -1;
  } else {
    page_table *pt = (page_table*) PHYSICAL(pd->ptds[pdindex].frame_addr << 12);
    if ( pt->pds[ptindex].present ) {
      return pt->pds[ptindex].frame_addr;
    } else {
      return -1;
    };
  }
};
// old line comment removed
memaddress mmu (addr_space_id id, memaddress vaddress) {
  unsigned int tmp = mmu_p (id, (vaddress >> 12));
  if (tmp == -1)
    return -1;  // fail
  else
    return (tmp << 12) + (vaddress % PAGE_SIZE);
}
// old line comment removed
void *u_sbrk (int incr) {
  int pages = incr / PAGE_SIZE;
  address_space *aspace = &address_spaces[current_as];
  memaddress oldbrk = aspace->memend;
    
  for (int i = 0;  i < pages;  i++) {
    int frame = request_new_frame ();
    if (frame == -1) { return (void*)(-1); } // error!
    as_map_page_to_frame (current_as, aspace->memend/PAGE_SIZE, frame);
    aspace->memend += PAGE_SIZE;
  }
  return (void*) oldbrk;  
}
// old line comment removed
void initialize_blocked_queue (blocked_queue *q) { 
  q->prev = 0;
  q->next = 0; 
}
// old line comment removed
void add_to_ready_queue (thread_id t) {
  
// old line comment removed
// do nothing
// old line comment removed
  thread_id last = thread_table[0].prev;
  thread_table[0].prev = t;
  thread_table[t].next = 0;
  thread_table[t].prev = last;
  thread_table[last].next = t;
  thread_table[t].state = TSTATE_READY;  // set its state to ready
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
void remove_from_ready_queue (thread_id t) {
  
// old line comment removed
// do nothing
// old line comment removed
  thread_id prev_thread = thread_table[t].prev;
  thread_id next_thread = thread_table[t].next;
  thread_table[prev_thread].next = next_thread;
  thread_table[next_thread].prev = prev_thread;
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
thread_id front_of_blocked_queue (blocked_queue bq) {
  return bq.next;
}
// old line comment removed
void add_to_blocked_queue (thread_id t, blocked_queue *bq) {
  
// old line comment removed
// do nothing
// old line comment removed
  thread_id last = bq->prev;
  bq->prev = t;
  thread_table[t].next = 0;    // t is ``last'' thread
  thread_table[t].prev = last;
  if (last == 0) {
    bq->next = t;
  } else {
    thread_table[last].next = t;
  }
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
void remove_from_blocked_queue (thread_id t, blocked_queue *bq) {
  
// old line comment removed
// do nothing
// old line comment removed
  thread_id prev_thread = thread_table[t].prev;
  thread_id next_thread = thread_table[t].next;
  if (prev_thread == 0) {
    bq->next = next_thread;
  } else {
    thread_table[prev_thread].next = next_thread;
  }
  if (next_thread == 0) {
    bq->prev = prev_thread;
  } else {
    thread_table[next_thread].prev = prev_thread;
  }
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
void add (thread_id t) {
  add_to_ready_queue (t);
}

void retire (thread_id t) {
  remove_from_ready_queue (t);
}

void deblock (thread_id t, blocked_queue *q) {
  
// old line comment removed
// do nothing
// old line comment removed
  remove_from_blocked_queue (t, q);
  add_to_ready_queue (t);
  thread_table[t].state = TSTATE_READY;
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
void block (blocked_queue *q, int new_state) {
  if (current_task == 0) return;
  
// old line comment removed
// do nothing
// old line comment removed
  debug_printf ("[%d.%d] blocking\n",             // REMOVE_DEBUGGING_CODE
    current_task, system_ticks);                  // REMOVE_DEBUGGING_CODE
  thread_table[current_task].state = new_state;
  remove_from_ready_queue (current_task);
  add_to_blocked_queue (current_task, q);
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
int register_new_tcb (addr_space_id as_id) {
  // called by u_fork()
  
// old line comment removed
boolean tcbfound = false;
thread_id tcbid;
for (tcbid = next_pid;  ((tcbid<MAX_THREADS) && (!tcbfound));  tcbid++) {
  if (thread_table[tcbid].used == false) {
    tcbfound = true;
    break;   // leave for loop
  }
};
// old line comment removed
if (!tcbfound) {                                  // continue searching at 1
  for (tcbid = 1;  ((tcbid<next_pid) && (!tcbfound));  tcbid++) {
    if (thread_table[tcbid].used == false) {
      tcbfound = true;
      break;   // leave for loop
    }
  };
};

if (tcbfound) next_pid = tcbid+1;                 // update next_pid:
// either tcbfound == false or tcbid == index of first free TCB
// old line comment removed
  if (!tcbfound)  return -1;               // no free TCB!
  thread_table[tcbid].used       = true;   // mark as used
  thread_table[tcbid].addr_space = as_id;  // enter address space ID
  return tcbid;
}  
// old line comment removed
void start_program_from_disk (char *progname) {
  
// old line comment removed
// create new address space (64 KB + 4 KB stack) and register TCB entry
addr_space_id as   = create_new_address_space (64*1024, 4096);
thread_id     tid  = register_new_tcb (as);     // get a fresh TCB
TCB           *tcb = &thread_table[tid];

// fill TCB structure
tcb->tid = tcb->pid = tid;                      // identical thread/process ID
tcb->ppid = 0;                                  // parent: 0 (none)
tcb->terminal = 0;                              // default terminal: 0
memcpy (tcb->cwd,     "/",   2);                // set current directory
memcpy (tcb->cmdline, "new", 4);                // set temporary command line
thread_table[tid].files[0] = DEV_STDIN;         // initialize standard I/O
thread_table[tid].files[1] = DEV_STDOUT;        // file descriptors
thread_table[tid].files[2] = DEV_STDERR;
for (int i = 3;  i < MAX_PFD;  i++) tcb->files[i] = -1;
activate_address_space (as);                    // activate the new address space
// old line comment removed
  
// old line comment removed
int fd = u_open (progname, O_RDONLY, 0);            // open_ the file
u_read (fd, (char*)BINARY_LOAD_ADDRESS, PROGSIZE);  // load to virtual address 0
u_close (fd);                                       // close_ the file
// old line comment removed
  
// old line comment removed
unsigned int framenos[KERNEL_STACK_PAGES];        // frame numbers of kernel stack 
for (int i = 0;  i < KERNEL_STACK_PAGES;  i++) {  // pages
  framenos[i] = request_new_frame ();
  as_map_page_to_frame (current_as, 0xbffff - i, framenos[i]);
}
// old line comment removed
char *kstack = (char*) (TOP_OF_KERNEL_MODE_STACK-KERNEL_STACK_SIZE);
memaddress adr = (memaddress)kstack;             // one page for kernel stack
  
tcb->esp0 = (uint)kstack + KERNEL_STACK_SIZE;    // initialize top-of-stack and
tcb->ebp  = (uint)kstack + KERNEL_STACK_SIZE;    // ebp (base pointer) values
// old line comment removed
  
// old line comment removed
thread_table[tid].uid  = 0;  thread_table[tid].gid  = 0;
thread_table[tid].euid = 0;  thread_table[tid].egid = 0;
thread_table[tid].ruid = 0;  thread_table[tid].rgid = 0;
// old line comment removed
  
// old line comment removed
current_task = tid;                         // make this the current task  
add_to_ready_queue (tid);                   // add process to ready queue
// old line comment removed
scheduler_is_active = true;   _set_statusline ("SCH:ON ", 16);
// old line comment removed
cpu_usermode (BINARY_LOAD_ADDRESS, 
              TOP_OF_USER_MODE_STACK);      // jump to user mode
// old line comment removed
};
// old line comment removed
static void write_tss (int num, word ss0, void *esp0) {
   fill_gdt_entry (num, (uint) &tss_entry, sizeof (tss_entry) - 1, 
                   0b11101001, 0b0000);                // write_ TSS entry to GDT
   memset (&tss_entry, 0, sizeof (tss_entry));         // fill TSS with zeros
   tss_entry.ss0  = ss0;                               // kernel stack segment
   tss_entry.esp0 = (memaddress)esp0;                  // kernel stack pointer
} 
// old line comment removed
void install_syscall_handler (int syscallno, void *syscall_handler) {
  if (syscallno >= 0 && syscallno < MAX_SYSCALLS) 
    syscall_table[syscallno] = syscall_handler;
};
// old line comment removed
void syscall_handler (context_t *r) {
  void (*handler) (context_t*);   // handler is a function pointer
  int number = r->eax;
  if (number != __NR_get_errno) set_errno (0); // default: no error
  if (number >= 0 && number < MAX_SYSCALLS)
    handler = syscall_table[number];
  else
    handler = 0;   // illegal system call number, outside 0..1023
  if (handler != 0) {
    handler (r);
  }
  else 
    printf ("Unknown syscall no. eax=0x%x; ebx=0x%x. eip=0x%x, esp=0x%x. "
            "Continuing.\n", r->eax, r->ebx, r->eip, r->esp);
}
// old line comment removed
void syscall_sbrk (context_t *r) {
  // ebx: increment
  eax_return ( u_sbrk (r->ebx) );
}
// old line comment removed
void syscall_get_errno (context_t *r) { eax_return ( get_errno () ); };
void syscall_set_errno (context_t *r) { set_errno ((int)r->ebx); };
// old line comment removed
void syscall_fork (context_t *r) { eax_return ((unsigned int) u_fork (r)); }
// old line comment removed
void syscall_exit (context_t *r) {
  // printf ("DEBUG: syscall_exit. current_task = %d\n", current_task); // REMOVE_DEBUGGING_CODE
  // exit_ code is in ebx register:
  
// old line comment removed
// do nothing
// old line comment removed
                                        // access the thread table
  // close_ open_ files
  thread_id pid = thread_table[current_task].pid;
  int gfd;
  for (int pfd = 0;  pfd < MAX_PFD;  pfd++) {
    if ((gfd = thread_table[pid].files[pfd]) != -1)  u_close (gfd);
      // printf ("exit(): closing fd %d (gfd %d)\n", pfd, gfd);   // REMOVE_DEBUGGING_CODE
      // u_close (gfd);                                           // REMOVE_DEBUGGING_CODE
      // thread_table[pid].files[pfd] = -1;   // close (locally)  // REMOVE_DEBUGGING_CODE
    // }                                                          // REMOVE_DEBUGGING_CODE
  }

  // modify thread table
  thread_table[current_task].exitcode = r->ebx;   // store exit_ code
  thread_table[current_task].state = TSTATE_EXIT; // mark process as finished
  remove_from_ready_queue (current_task);         // remove it from ready queue
  wake_waiting_parent_process (current_task);     // wake parent
  destroy_address_space (current_as);             // return the memory
  
// old line comment removed
for (int pid = 0;  pid < MAX_THREADS;  pid++)
  if (thread_table[pid].ppid == current_task)
    thread_table[pid].ppid = 1;  // set parent to idle_ process
// old line comment removed
                                                  // notify children

  // finally: call scheduler to pick a different task
  
// old line comment removed
// do nothing
// old line comment removed
  scheduler (r, SCHED_SRC_RESIGN);    
};
// old line comment removed
void syscall_waitpid (context_t *r) {
  // ebx: pid of child to wait for
  // ecx: pointer to status
  // edx: options (ignored)
  
// old line comment removed
// do nothing
// old line comment removed
  int chpid = r->ebx;  // child we shall wait for
  
  // check errors
  if (chpid < 1 || chpid >= MAX_THREADS || thread_table[chpid].state == 0) {
    
// old line comment removed
// do nothing
// old line comment removed
    eax_return (-1);  // error
  }
  if (!thread_table[chpid].used) {
    
// old line comment removed
// do nothing
// old line comment removed
    eax_return (-1);  // no such process
  }
  if (thread_table[chpid].ppid != current_task) {
    
// old line comment removed
// do nothing
// old line comment removed
    eax_return (-1);  // not a child of mine
  }

  int *status = (int*)r->ecx;                       // address for the status  
  thread_table[current_task].waitfor = chpid;
  block (&waitpid_queue, TSTATE_WAITFOR);
  
// old line comment removed
// do nothing
// old line comment removed
  syscall_resign (r);                               // here we resign_
// old line comment removed
  *status = thread_table[chpid].exitcode;
  thread_table[chpid].used = false;  // finally remove child process
  eax_return (chpid);                // set the return value
}
// old line comment removed
void syscall_resign (context_t *r) {
  
// old line comment removed
// do nothing
// old line comment removed
  scheduler (r, SCHED_SRC_RESIGN);
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
void syscall_gettid (context_t *r)  { eax_return (current_task); }
void syscall_getpid (context_t *r)  { eax_return (current_pid); }
void syscall_getppid (context_t *r) { eax_return (current_ppid); }
// old line comment removed
void syscall_getpsinfo (context_t *r) {
  unsigned int retval, pid;
  // ebx: thread ID
  // ecx: address of TCB block
  pid = r->ebx;
  if (pid > MAX_THREADS || pid < 1) {      // legal argument?
    retval = 0; goto end;
  }
  if (thread_table[pid].used == false) {   // do we have this thread?
    retval = 0; goto end;
  }
  
  // found a process: copy its TCB  
  memcpy ((char*)r->ecx, &thread_table[pid], sizeof (TCB));
  retval = r->ecx;

  end: eax_return (retval);
};
// old line comment removed
void syscall_setpsname (context_t *r) {
  strncpy (thread_table[current_task].cmdline, (char*)r->ebx, CMDLINE_LENGTH-1);
};
// old line comment removed
void syscall_execv (context_t *r) {
  // generate command line in one string
  char *path  = (char*)r->ebx;            // path argument of execv_ () 
  char **argv = (char**)r->ecx;           // argv argument of execv_ ()
  int i = 0;  char cmdline[CMDLINE_LENGTH] = "";
  while (argv[i] != 0) {
    strncpy (cmdline + strlen(cmdline), argv[i], CMDLINE_LENGTH-strlen(cmdline)-1);
    strncpy (cmdline + strlen(cmdline), " ", CMDLINE_LENGTH-strlen(cmdline)-1);
    i++;
  }
  if (cmdline[strlen(cmdline)-1] == ' ')  
    cmdline[strlen(cmdline)-1] = '\0';    // remove trailing blank

  // call u_execv()
  memaddress stack;
  memaddress startaddr = (memaddress) u_execv (path, argv, &stack);  // sets stack
  if (startaddr == -1)  eax_return (-1);  // error

  // update context and process commandline
  r->eip     = startaddr;                 // start_ running at address e_entry
  r->useresp = (memaddress)stack;         // from ELF header
  r->ebp     = (memaddress)stack;
  strncpy (thread_table[current_task].cmdline, cmdline, CMDLINE_LENGTH); 
};
// old line comment removed
void syscall_pthread_create (context_t *r) {
  // ebx: address of thread function
  memaddress address = r->ebx;
  // printf ("DEBUG: syscall_pthread_create called; "    // REMOVE_DEBUGGING_CODE
  //         "start address = 0x%08x\n", address);       // REMOVE_DEBUGGING_CODE
  u_pthread_create (NULL, NULL, address, NULL);
  // printf ("returning from pthread_create syscall\n"); // REMOVE_DEBUGGING_CODE
};
// old line comment removed
void syscall_idle (context_t *r) {
  
// old line comment removed
asm ("sti");    // set interrupt flag
// old line comment removed
  asm ("hlt");
  
// old line comment removed
asm ("cli");    // clear interrupt flag
// old line comment removed
}
// old line comment removed
void syscall_page_out (context_t *r) {
  // ebx: page number
  eax_return (page_out (current_as, r->ebx) );
}
// old line comment removed
void syscall_get_free_frames (context_t *r) {
  // no parameters
  mutex_lock (swapper_lock);    // lock_, see below
  eax_return (free_frames);
}

void syscall_free_a_frame (context_t *r) {
  // no parameters
  
// old line comment removed
/*                                                                    // REMOVE_DEBUGGING_CODE
printf ("DEBUG: COUNTER TABLE\n");                                    // REMOVE_DEBUGGING_CODE
for (int i = 0; i < PG_MAX_COUNTERS; i++) {                           // REMOVE_DEBUGGING_CODE
  if (counter_table[i].used && counter_table[i].count != 0) {         // REMOVE_DEBUGGING_CODE
    printf ("DEBUG: %8d: count = %3d\n", i, counter_table[i].count);  // REMOVE_DEBUGGING_CODE
  }                                                                   // REMOVE_DEBUGGING_CODE
}                                                                     // REMOVE_DEBUGGING_CODE
*/                                                                    // REMOVE_DEBUGGING_CODE
addr_space_id pick_as      = -1;
int           pick_pageno, themin;
// printf ("\nDEBUG:  starting search for page to evict\n");          // REMOVE_DEBUGGING_CODE
while (!mutex_try_lock (paging_lock)) ;    // active waiting for lock
for (int as = 1;  as < MAX_ADDR_SPACES;  as++) {
  if (address_spaces[as].status == AS_USED) {
    page_directory *pd = address_spaces[as].pd;
    for (int i = 0;  i < 768;  i++) {      // < 768: only work on process memory
      if (pd->ptds[i].present) {           // directory entry in use
        page_table *pt = (page_table*) (PHYSICAL ((pd->ptds[i].frame_addr) << 12));
        for (int j = 0;  j < 1024;  j++) {
          if (pt->pds[j].present) {        // table entry in use
            int pageno = i*1024 + j;
            int index = hash ((as << 20) | pageno, PG_MAX_COUNTERS);
            if (pick_as==-1 && counter_table[index].used) {
              // initialize minimum, pick
              pick_as     = as;
              pick_pageno = pageno;
              themin = counter_table[index].count;
              //printf ("INIT:   pick (%d,%d)\n", as, pageno);        // REMOVE_DEBUGGING_CODE
            } else {
              if (counter_table[index].count < themin) {
                  // && address_spaces[as].status == AS_USED) {       // REMOVE_DEBUGGING_CODE
                themin = counter_table[index].count;
                pick_as     = as;
                pick_pageno = pageno;
                // printf ("UPDATE: pick (%d,%d)\n", as, pageno);     // REMOVE_DEBUGGING_CODE
              }
            }
          }
        }
      }
    }
  }
}
mutex_unlock (paging_lock);

if (pick_as != -1) {
  debug_printf ("DEBUG: BEFORE calling page_out (as=%d, pageno=%d)\n", pick_as, pick_pageno);  // REMOVE_DEBUGGING_CODE
  mutex_lock (paging_lock);
  page_out (pick_as, pick_pageno);
  mutex_unlock (paging_lock);
  // debug_printf ("DEBUG: AFTER  calling page_out (as=%d, pageno=%d)\n", pick_as, pick_pageno);  // REMOVE_DEBUGGING_CODE
} else {
  printf ("\nERROR: cannot pick a page to evict!\n");
//  inside_req_frame--;   // for debugging, REMOVE ME!!!              // REMOVE_DEBUGGING_CODE   
}
// old line comment removed
}
// old line comment removed
void syscall_clrscr (context_t *r) {
  // no parameters, no return value
  vt_clrscr ();
}

void syscall_get_xy (context_t *r) {
  // ebx: address of x position (char)
  // ecx: address of y position (char)
  vt_get_xy ((char*)r->ebx, (char*)r->ecx);
}

void syscall_set_xy (context_t *r) {
  // ebx: x position (char)
  // ecx: y position (char)
  vt_set_xy ((char)r->ebx, (char)r->ecx);
}
// old line comment removed
void syscall_read_screen (context_t *r) {
  // ebx: buffer address
  read_write_screen ((char *) r->ebx, true);
}

void syscall_write_screen (context_t *r) {
  // ebx: buffer address
  read_write_screen ((char *) r->ebx, false);
}
// old line comment removed
void syscall_pthread_mutex_init (context_t *r) {
  // ebx: mutex id
  // ecx: attributes, not implemented
  eax_return ( u_pthread_mutex_init ( (pthread_mutex_t*)r->ebx,
                                      (pthread_mutexattr_t*)r->ecx ) );
}
// old line comment removed
void syscall_pthread_mutex_lock (context_t *r) {
  // ebx: mutex id
  eax_return ( u_pthread_mutex_lock ((pthread_mutex_t*)r->ebx) );
}

void syscall_pthread_mutex_trylock (context_t *r) {
  // ebx: mutex id
  eax_return ( u_pthread_mutex_trylock ((pthread_mutex_t*)r->ebx) );
}

void syscall_pthread_mutex_unlock (context_t *r) {
  // ebx: mutex id
  eax_return ( u_pthread_mutex_unlock ((pthread_mutex_t*)r->ebx) );
}
// old line comment removed
void syscall_pthread_mutex_destroy (context_t *r) {
  // ebx: mutex id
  eax_return ( u_pthread_mutex_destroy ((pthread_mutex_t*)r->ebx) );
}
// old line comment removed
void syscall_readchar (context_t *r) {
  char c;
  int t = thread_table[current_task].terminal;
  terminal_t *term = &terminals[t];
  
  // get character, return 0 if there is no new character in the buffer
  
// old line comment removed
// do nothing
// old line comment removed
                                        // access the thread table
  if (term->kbd_count > 0) {
    term->kbd_count--;
    term->kbd_lastread = (term->kbd_lastread+1) % SYSTEM_KBD_BUFLEN;
    c = term->kbd[term->kbd_lastread];
  } else {
    c = 0;
    if ((current_task > 1) && scheduler_is_active) {
      block (&keyboard_queue, TSTATE_WAITKEY);
      
// old line comment removed
// do nothing
// old line comment removed
      
// old line comment removed
asm (".intel_syntax noprefix; \
  mov eax, 66;; \
  int 0x80;; \
  .att_syntax; ");
// old line comment removed
    }
  };
  r->ebx = c;     // return value in ebx
  
// old line comment removed
// do nothing
// old line comment removed
};
// old line comment removed
void syscall_open (context_t *r) {
  eax_return ( gfd2pfd (u_open ((char*) r->ebx, r->ecx, 0) ) ); };

void syscall_stat (context_t *r) {
  eax_return ( u_stat ((char*) r->ebx, (struct stat*) r->ecx) ); };

void syscall_getdent (context_t *r) {
  // ebx: path, ecx: index, edx: dir_entry buffer
  eax_return ( u_getdent ((char*) r->ebx, r->ecx, (struct dir_entry*) r->edx) ); };

void syscall_close (context_t *r) {
  // ebx: fd
  int pfd = r->ebx;
  thread_id pid = thread_table[current_task].pid;
  r->eax = u_close (pfd2gfd (pfd));        // close_ (globally)  
  if (pfd >= 0 && pfd < MAX_PFD)
    thread_table[pid].files[pfd] = -1; };  // close_ (locally) 

void syscall_read (context_t *r) {
  // ebx: fd, ecx: *buf, edx: nbytes
  eax_return ( u_read (pfd2gfd (r->ebx), (byte*) r->ecx, r->edx) ); };

void syscall_write (context_t *r) {
  // ebx: fd, ecx: *buf, edx: nbytes
  eax_return ( u_write (pfd2gfd (r->ebx), (byte*) r->ecx, r->edx) ); };
void syscall_lseek (context_t *r) {
  // ebx: fd, ecx: offset, edx: whence
  eax_return ( u_lseek (pfd2gfd (r->ebx), r->ecx, r->edx) ); };
  
void syscall_isatty (context_t *r) {
  // ebx: file descriptor
  eax_return ( pfd2gfd (u_isatty (r->ebx)) ); }

void syscall_mkdir (context_t *r) {
  // ebx: name of new directory, ecx: mode
  eax_return ( u_mkdir ((char*)r->ebx, r->ecx) ); }

void syscall_rmdir (context_t *r) {
  // ebx: name of directory that we want to delete
  eax_return ( u_rmdir ((char*)r->ebx) ); }
  
void syscall_truncate  (context_t *r) {
  // ebx: filename, ecx: length
  eax_return ( u_truncate ((char*)r->ebx, r->ecx) ); }

void syscall_ftruncate (context_t *r) {
  // ebx: file descriptor, ecx: length
  eax_return ( u_ftruncate ( pfd2gfd (r->ebx), r->ecx) ); }

void syscall_link (context_t *r) {
  // ebx: original name, ecx: new name
  // eax_return ( mx_link (ROOT_DISK, (char*)r->ebx, (char*)r->ecx) );  // REMOVE_DEBUGGING_CODE 
  eax_return ( u_link ((char*)r->ebx, (char*)r->ecx) ); }

void syscall_unlink (context_t *r) {
  // ebx: pathname
  eax_return ( u_unlink ((char*)r->ebx) );
}

void syscall_symlink (context_t *r) {
  // ebx: target file name, ecx: symbolic link name
  // eax_return ( mx_symlink (ROOT_DISK, (char*)r->ebx, (char*)r->ecx) ); // REMOVE_DEBUGGING_CODE
  eax_return ( u_symlink ((char*)r->ebx, (char*)r->ecx) ); }

void syscall_readlink (context_t *r) {
  // ebx: file name
  // ecx: buffer for link target
  // edx: buffer length
  eax_return ( u_readlink ((char*)r->ebx, (char*)r->ecx, r->edx) );
}
// old line comment removed
void syscall_getcwd (context_t *r) {
  // ebx: buffer for directory
  // ecx: maximum length of path
  eax_return ( u_getcwd ((char*)r->ebx, r->ecx) );
}

void syscall_chdir (context_t *r) {
  // ebx: new directory
  eax_return ( u_chdir ((char*)r->ebx) );
}
// old line comment removed
void syscall_diskfree (context_t *r) {
  // ebx: address of diskfree query structure
  mx_diskfree ((struct diskfree_query*)r->ebx);
}
// old line comment removed
void syscall_sync (context_t *r) {
  // this syscall takes no arguments
  buffer_sync (1);   // with lock_
}
// old line comment removed
void syscall_kill (context_t *r) {
  // ebx: pid of child to send a s signal,  ecx: signal number
  int retval; int target_pid = r->ebx; int signo = r->ecx;

  if (!thread_table[target_pid].used) {      // check if target process exists
    // target process does not exist
    set_errno (ESRCH);
    retval = -1; goto end;
  }
  
  if (signo < 0 || signo > 31) {             // check if signal is in range 0..31
    set_errno (EINVAL);
    retval = -1; goto end;
  }
  
  // check if current process may send a signal
  if ((thread_table[current_task].euid == 0) ||
      (thread_table[target_pid].euid == thread_table[current_task].euid)) {
    retval = u_kill (target_pid, signo);
  } else {
    set_errno (EPERM);
    retval = -1;
  }
  end: r->eax = retval;

  // run scheduler_ if this was a raise operation
  if (current_task == target_pid) {  
// old line comment removed
asm (".intel_syntax noprefix; \
  mov eax, 66;; \
  int 0x80;; \
  .att_syntax; ");
// old line comment removed
                                                 }
};
// old line comment removed
void syscall_signal (context_t *r) {
  // ebx: signal_ number
  // ecx: address of signal_ handler
  int signo         = r->ebx;
  sighandler_t func = (sighandler_t)r->ecx;
  func = u_signal (signo, func);
  eax_return (func);
};
// old line comment removed
void syscall_setuid (context_t *r) {
  // ebx: uid
  eax_return ( u_setuid (r->ebx) );
}

void syscall_setgid (context_t *r) {
  // ebx: gid
  eax_return ( u_setgid (r->ebx) );
}

void syscall_seteuid (context_t *r) {
  // ebx: euid
  eax_return ( u_seteuid (r->ebx) );
}

void syscall_setegid (context_t *r) {
  // ebx: egid
  eax_return ( u_setegid (r->ebx) );
}

void syscall_login (context_t *r) {
  // ebx: uid, ecx: password
  eax_return ( u_login (r->ebx, (char*)r->ecx) );
}
// old line comment removed
void syscall_query_ids (context_t *r) {
  // ebx: type of ID
  switch (r->ebx) {
    case QUERY_UID:  eax_return (thread_table[current_task].uid);
    case QUERY_EUID: eax_return (thread_table[current_task].euid);
    case QUERY_GID:  eax_return (thread_table[current_task].gid);
    case QUERY_EGID: eax_return (thread_table[current_task].egid); 
    default:         eax_return (-1);
  }
}
// old line comment removed
void syscall_chown (context_t *r) {
  // ebx: path, ecx: owner, edx: group
  eax_return ( u_chown ((char *)r->ebx, r->ecx, r->edx) );
}

void syscall_chmod (context_t *r) {
  // ebx: path, ecx: new mode
  eax_return ( u_chmod ((char *)r->ebx, r->ecx) );
}
// old line comment removed
void syscall_print_inode (context_t *r) {
  int ino = r->ebx;   // requested inode
  printf ("syscall; ino = %d\n", ino);
  
  struct minix2_inode in;
  mx_read_inode (DEV_HDA, ino, &in);
  printf ("i_mode:   0%o\n", in.i_mode);
  printf ("i_nlinks: %d\n", in.i_nlinks);
  printf ("i_size:   %d\n", in.i_size);
  printf ("i_zone:   [");
  for (int i = 0; i < 7; i++) printf ("%d, ", in.i_zone[i]);  printf ("]\n");
}
// old line comment removed
int get_errno () {
  if (scheduler_is_active)  return thread_table[current_task].error;
  else                      return startup_errno;
}

void set_errno (int err) {
  if (scheduler_is_active)  thread_table[current_task].error = err;
  else                      startup_errno = err;
}
// old line comment removed
int u_fork (context_t *r) {
  
// old line comment removed
// do nothing
// old line comment removed
  thread_id old_tid = current_task;
  thread_id ppid    = old_tid;
  
// old line comment removed
addr_space_id old_as = current_as;
// clone kernel part of PD; reserve user part of memory
addr_space_id new_as = create_new_address_space (
  address_spaces[old_as].memend - address_spaces[old_as].memstart,
  address_spaces[old_as].stacksize );
if (new_as == -1) return -1;    // error: cannot create address space

thread_id new_tid = register_new_tcb (new_as);
if (new_tid == -1) return -1;   // error: cannot create TCB entry
// old line comment removed
  
// old line comment removed
TCB *t_old = &thread_table[old_tid];   // prefer to use pointers
TCB *t_new = &thread_table[new_tid];
*t_new            = *t_old;            // copy the complete TCB
t_new->state      = TSTATE_FORK;
t_new->tid        = new_tid;
t_new->addr_space = new_as;
// t_new->new        = true;           // mark new process as new   // REMOVE_DEBUGGING_CODE
t_new->pid        = t_new->tid;        // new process; pid = tid
t_new->ppid       = old_tid;           // set parent process ID

// copy current registers to new thread, except EBX (= return value)
t_new->regs       = *r;
// t_new->regs.ebx   = 0;              // in the child fork() returns 0  // REMOVE_DEBUGGING_CODE

// copy current ESP, EBP
asm volatile ("mov %%esp, %0" : "=r"(t_new->esp0));  // get current ESP
asm volatile ("mov %%ebp, %0" : "=r"(t_new->ebp));   // get current EBP

// old line comment removed
if (t_new->pid != t_old->pid) {
  for (int pfd = 0;  pfd < MAX_PFD;  pfd++) {
    int gfd = t_old->files[pfd];
    if (gfd >= 0)
      t_new->files[pfd] = u_reopen (gfd);  // get new gfd
      // printf ("old proc: files[%d]=%d, "          // REMOVE_DEBUGGING_CODE
      //         "new proc: files[%d]=%d\n",         // REMOVE_DEBUGGING_CODE
      //         pfd, gfd, pfd, t_new->files[pfd]);  // REMOVE_DEBUGGING_CODE
    else
      t_new->files[pfd] = gfd;             // use old gfd (stdio)
  }
}
// old line comment removed
                                               // see filesystem chapter
// old line comment removed
  
// old line comment removed
page_table *stackpgtable = request_new_page ();
address_spaces[new_as].kstack_pt = (memaddress)stackpgtable;
memset (stackpgtable, 0, sizeof (page_table));
page_directory *tmp_pd = address_spaces[new_as].pd;
KMAPD ( &tmp_pd->ptds[767], mmu (0, (uint)stackpgtable) );
    
int i, j; // counters
for (i = 0;  i < KERNEL_STACK_PAGES;  i++)
  as_map_page_to_frame (new_as, 0xbffff - i, request_new_frame () );
// old line comment removed
// copy the physical frames
memaddress base = TOP_OF_KERNEL_MODE_STACK - KERNEL_STACK_SIZE;
for (i = 0;  i < KERNEL_STACK_PAGES;  i++)
  phys_memcpy ( mmu (new_as, base + i*PAGE_SIZE),
                mmu (old_as, base + i*PAGE_SIZE), PAGE_SIZE );
debug_printf ("u_fork: memcpy done\n");               // REMOVE_DEBUGGING_CODE
// old line comment removed
  
// old line comment removed
  // clone first 3 GB (minus last directory entry) of address space
  page_directory *old_pd = address_spaces[old_as].pd;
  page_directory *new_pd = address_spaces[new_as].pd;
  page_table     *old_pt, *new_pt;
  for (i = 0;  i < 767;  i++) {          // only 0..766, not 767 (= kstack)
    if (old_pd->ptds[i].present) {       // page table present?
      // walk through the entries of the page table
      old_pt = (page_table*)PHYSICAL (old_pd->ptds[i].frame_addr << 12);
      new_pt = (page_table*)PHYSICAL (new_pd->ptds[i].frame_addr << 12);
      for (j = 0;  j < 1024;  j++)
        if (old_pt->pds[j].present)      // page present?
          copy_frame ( new_pt->pds[j].frame_addr, old_pt->pds[j].frame_addr );
    };
  };
// old line comment removed
  
// old line comment removed
memaddress eip = get_eip ();        // get current EIP
// new process begins to live right here!
if (current_task == ppid) {
  // parent tasks
  t_new->eip  = eip;
  add_to_ready_queue (new_tid);
  debug_printf ("fork going to return %d\n", new_tid);    // REMOVE_DEBUGGING_CODE
  
// old line comment removed
// do nothing
// old line comment removed
                                      // must be done in parent
  return new_tid;                   // in parent, fork_ returns child's PID
} else {
  // child tasks
  debug_printf ("fork going to return 0 \n");             // REMOVE_DEBUGGING_CODE
  return 0;                         // in child, fork_ returns 0
}
// old line comment removed
}
// old line comment removed
void wake_waiting_parent_process (int pid) {
  // check if we need to wake up parent process
  int ppid = thread_table[pid].ppid;
  if ( (thread_table[ppid].state == TSTATE_WAITFOR) &&
       (thread_table[ppid].waitfor == pid) ) {
    // wake up parent process
    debug_printf ("exit: remove_from_"                // REMOVE_DEBUGGING_CODE
                  "blocked_queue (%d,%x)\n",          // REMOVE_DEBUGGING_CODE
                  ppid, &waitpid_queue);              // REMOVE_DEBUGGING_CODE
    deblock (ppid, &waitpid_queue);
    thread_table[pid].state = TSTATE_EXIT;
    // thread_table[pid].used = false;                // REMOVE_DEBUGGING_CODE
  } else {
    // parent is not waiting, make this process a zombie
    thread_table[pid].state = TSTATE_ZOMBIE;
  }
}
// old line comment removed
int u_execv (char *filename, char *const argv[], memaddress *newstack) {
  // returns start_ address of the loaded binary; or -1 if exec fails
  Elf32_Ehdr elf_header;  Elf32_Phdr program_header;
  
// old line comment removed
int fd = u_open (filename, 0, 0);
if (fd == -1)  return -1;   // error
int sz = u_read (fd, &elf_header, sizeof (elf_header));
// check for ELF header
if (sz != sizeof (elf_header) || strncmp (elf_header.e_ident, "\x7f" "ELF", 4) != 0) {
  u_close (fd);
  return -1;
}
// old line comment removed
  
// old line comment removed
// TO DO, see "Exercises" section.
// old line comment removed
                                       // see chapter on Users and Groups
  
// old line comment removed
uint *stack = (uint*) (TOP_OF_USER_MODE_STACK - 512);
// find number of arguments
word argc = 0;
while ( (memaddress)(argv+argc) < TOP_OF_USER_MODE_STACK && argv[argc] != 0 )
  argc++;
// old line comment removed
// copy arguments into the reserved 512 bytes
memaddress target = (memaddress)stack;
memaddress args_start = target;
target += argc*4;
for (int i = 0;  i < argc;  i++) {
  int size = strlen (argv[i])+1;           // string length plus terminator
  memcpy ((void*)target, argv[i], size);   // copy i-th argument
  *(stack + i) = target;                   // store its address
                                                                        // REMOVE_DEBUGGING_CODE
  // printf ("DEBUG: argv[%d] = %s (at 0x%08x) --> %s (at 0x%08x)\n",   // REMOVE_DEBUGGING_CODE
  //         i, argv[i], argv[i], (char*)target, target);               // REMOVE_DEBUGGING_CODE
  target += size;
}
                                                     // REMOVE_DEBUGGING_CODE
// unsigned int args_end = target;                   // REMOVE_DEBUGGING_CODE
// printf ("DEBUG: args_start = %x\n", args_start);  // REMOVE_DEBUGGING_CODE
// printf ("DEBUG: args_end   = %x\n", args_end);    // REMOVE_DEBUGGING_CODE
// old line comment removed
// finish stack preparation  
*(--stack) = args_start;  // push pointer to argument list
*(--stack) = argc;        // push number of arguments
*(--stack) = 0;           // push return address (set to 0)
*newstack = (memaddress)stack;
// old line comment removed
  
// old line comment removed
memset ((void*)address_spaces[current_as].memstart, 0, 
        address_spaces[current_as].memend - address_spaces[current_as].memstart);   
// old line comment removed
  
// old line comment removed
int phoffset = elf_header.e_phoff;
for (int i = 0;  i < elf_header.e_phnum;  i++) {
  u_lseek (fd, phoffset + i * elf_header.e_phentsize, SEEK_SET);
  u_read (fd, &program_header, sizeof (program_header));
  if (program_header.p_type == ELF_PT_LOAD) {
    
// old line comment removed
int needed_memsize = program_header.p_memsz;
int current_memsize = address_spaces[current_as].memend 
                    - address_spaces[current_as].memstart;
if (needed_memsize > current_memsize) {
  // printf ("u_exec: calling u_sbrk (%d)\n", needed_memsize-current_memsize);  // REMOVE_DEBUGGING_CODE
  u_sbrk (needed_memsize-current_memsize);
}
// old line comment removed
    u_lseek (fd, program_header.p_offset, SEEK_SET);
    u_read (fd, (char*)program_header.p_vaddr, program_header.p_filesz);
  }
}    
u_close (fd);
return elf_header.e_entry;  // success. when coming back, set EIP to entry address
// old line comment removed
}
// old line comment removed
int u_pthread_create (pthread_t *restrict thread, const pthread_attr_t *restrict attr,
                      memaddress start_address, void *restrict arg) {
  
// old line comment removed
// do nothing
// old line comment removed
                                        // access the thread table
    thread_id old_tid = current_task;
    
// old line comment removed
thread_id new_tid = register_new_tcb (current_as);
address_spaces[current_as].refcount++;
address_spaces[current_as].extra_kstacks++;   // see below
// old line comment removed
    
// old line comment removed
TCB *t_old = &thread_table[old_tid];
TCB *t_new = &thread_table[new_tid];
*t_new = *t_old;     // copy the complete TCB
                     // note: this destroys data set in register_new_tcb_ ()
memset (&t_new->regs, 0, sizeof (context_t));
t_new->state      = TSTATE_FORK;
t_new->tid        = new_tid;
t_new->addr_space = current_as;
t_new->new        = true;         // mark new thread as new
t_new->pid        = old_tid;      // thread; pid != tid
t_new->ppid       = t_old->ppid;  // new thread has same parent as caller
// old line comment removed
    
// old line comment removed
// create user stack
void *ustack = u_sbrk (PAGE_SIZE);
memset (ustack, 0, PAGE_SIZE);

// create kernel stack
int kstack_frame = request_new_frame ();                             // get a frame
uint kstack_start = 
// old line comment removed
TOP_OF_KERNEL_MODE_STACK 
- ( KERNEL_STACK_PAGES + 2 * (address_spaces[current_as].extra_kstacks) ) 
  * PAGE_SIZE
// old line comment removed
                                                  ;
// printf ("DEBUG: NEW THREAD STACK, frame = 0x%0x,"   // REMOVE_DEBUGGING_CODE
//         " VA = 0x%0x-0x%0x\n", kstack_frame,        // REMOVE_DEBUGGING_CODE
//         kstack_start, kstack_start+PAGE_SIZE);      // REMOVE_DEBUGGING_CODE
as_map_page_to_frame (current_as, kstack_start >> 12, kstack_frame); // map it

uint *STACK = (uint*) (kstack_start+PAGE_SIZE);     // top of new stack
t_new->top_of_thread_kstack = STACK;

*(--STACK) = 0x20 | 0x03;               // push ss (selector 0x20 | RPL3: 0x03)
*(--STACK) = (uint)ustack + PAGE_SIZE;  // push esp (for user mode)
*(--STACK) = t_old->regs.eflags;        // push eflags
*(--STACK) = 0x18 | 0x03;               // push cs (selector 0x18 | RPL3: 0x03)
*(--STACK) = start_address;             // push eip (for user mode)

t_new->esp0 = (memaddress)STACK;
add_to_ready_queue (new_tid);
// old line comment removed
  
// old line comment removed
// do nothing
// old line comment removed
  return 0;
}
// old line comment removed
void syscall_pthread_exit (context_t *r) {
  if (address_spaces[current_as].refcount == 1) {
    // last thread leaves: use normal exit_ mechanism
    r->ebx = 0;                                 // set process exit_ code to 0
    syscall_exit (r); return;                   // and leave
  }

  
// old line comment removed
// do nothing
// old line comment removed
                                        // access the thread table
  thread_table[current_task].state = TSTATE_EXIT;
  remove_from_ready_queue (current_task);
  address_spaces[current_as].refcount--;
  thread_table[current_task].used = false;    // release TCB
  
// old line comment removed
// do nothing
// old line comment removed
  
// old line comment removed
asm (".intel_syntax noprefix; \
  mov eax, 66;; \
  int 0x80;; \
  .att_syntax; ");
// old line comment removed
}
// old line comment removed
void scheduler (context_t *r, int source) {
  // debug_printf ("*");                    // REMOVE_DEBUGGING_CODE
  debug_printf ("ENTER scheduler\n");       // REMOVE_DEBUGGING_CODE
  
// old line comment removed
// do nothing
// old line comment removed
  
// old line comment removed
for (thread_id pid = 0;  pid < MAX_THREADS;  pid++) {
  if (thread_table[pid].state == TSTATE_ZOMBIE) {
    thread_id ppid = thread_table[pid].ppid;
    
    // case 1: parent is waiting
    if ( (thread_table[ppid].state == TSTATE_WAITFOR) &&
         (thread_table[ppid].waitfor == pid) ) {
      debug_printf ("exit: remove_from_blocked_"       // REMOVE_DEBUGGING_CODE
                    "queue (%d,%x)\n",                 // REMOVE_DEBUGGING_CODE
                    ppid, &waitpid_queue);             // REMOVE_DEBUGGING_CODE
      deblock (ppid, &waitpid_queue);
      thread_table[pid].state = TSTATE_EXIT;
      thread_table[pid].used = false;
    }
    
    // strange case                                     // REMOVE_DEBUGGING_CODE
    if ( (thread_table[ppid].state == TSTATE_WAITFOR) && // REMOVE_DEBUGGING_CODE
         (thread_table[ppid].waitfor != pid) ) {        // REMOVE_DEBUGGING_CODE
      // output debug message                           // REMOVE_DEBUGGING_CODE
      debug_printf ("Strange: process %d has "          // REMOVE_DEBUGGING_CODE
                    "parent %d, but parent waits "      // REMOVE_DEBUGGING_CODE
                    "for process %d\n", pid, ppid,      // REMOVE_DEBUGGING_CODE
                    thread_table[ppid].waitfor);        // REMOVE_DEBUGGING_CODE
    }                                                   // REMOVE_DEBUGGING_CODE
    // case 2: parent ID was set to 1 (idle_)
    if ( ppid == 1 ) {
      thread_table[pid].state = TSTATE_EXIT;
      thread_table[pid].used = false;
    }
  }
}
// old line comment removed
                                       // deal with zombies if we have any
if (!scheduler_is_active) {          // check if we want to run the scheduler_
  
// old line comment removed
// do nothing
// old line comment removed
  return;
}
// old line comment removed
t_old = &thread_table[current_task];
debug_printf ("SCHED: enter find next\n");
// old line comment removed
thread_id tid;
search:  // goto label
if (source == SCHED_SRC_RESIGN && t_old->state != TSTATE_READY) {
  // printf ("DEBUG: resigner not active; state=%d, "      // REMOVE_DEBUGGING_CODE
  //         "old->next.state = %d\n", t_old->state,       // REMOVE_DEBUGGING_CODE
  //         thread_table[t_old->next].state);             // REMOVE_DEBUGGING_CODE
  // we cannot use the ->next pointer
  debug_printf ("scheduler called from "                   // REMOVE_DEBUGGING_CODE
    "syscall_waitpid(). tid(old) = %d, ", tid);            // REMOVE_DEBUGGING_CODE
  tid = thread_table[0].next;   
  debug_printf ("tid(new) = %d\n", tid);                   // REMOVE_DEBUGGING_CODE
} else {
  tid = t_old->next;
}
if (tid == 1) tid = thread_table[1].next;    // ignore idle_ process
// old line comment removed
if (tid == 0)                    // end of queue reached
  tid = thread_table[1].next;
if (tid == 0)                    // still 0? run idle_ task
  tid = 1; // idle_
t_new = &thread_table[tid];
if (tid > 1 && (t_new->addr_space == 0 || t_new->state != TSTATE_READY)) {
  goto search; // continue searching
}
// found it
// old line comment removed
debug_printf ("SCHED: leave find next\n");
if (t_new != t_old) { 
  
// old line comment removed
t_old->regs = *r;                    // store old:   registers
COPY_ESP_TO_VAR (t_old->esp0);       //              esp (kernel)
COPY_EBP_TO_VAR (t_old->ebp);        //              ebp
current_task = t_new->tid;
if (current_as != t_new->addr_space) {
  // we need to change the address space (switching process, not thread)
  current_as   = t_new->addr_space;
  current_pd   = address_spaces[t_new->addr_space].pd;
  WRITE_CR3 ( mmu (0, (memaddress)current_pd) );   // activate address space
}
// else {                                                                  // REMOVE_DEBUGGING_CODE
// debug_printf ("thread switch, tid %d -> %d, esp: 0x%08x -> 0x%08x\n",   // REMOVE_DEBUGGING_CODE
// t_old->tid, current_task, t_old->esp0, t_new->esp0);                    // REMOVE_DEBUGGING_CODE
// }                                                                       // REMOVE_DEBUGGING_CODE
COPY_VAR_TO_ESP (t_new->esp0);       // restore new: esp
COPY_VAR_TO_EBP (t_new->ebp);        //              ebp       chunk continues ->
// old line comment removed
// set TSS entry esp0 to top of current kernel stack and flush TSS
if (t_new->pid != t_new->tid) {
  // thread kstack information is stored in the TCB
  write_tss (5, 0x10, t_new->top_of_thread_kstack);       // non-primary thread
} else {
  // process kstack is a fixed value
  write_tss (5, 0x10, (void*)TOP_OF_KERNEL_MODE_STACK);   // primary thread
}
tss_flush ();

// show thread ID in status line
if (t_new->tid != 1) {  // ignore switch to idle_
  char msg[4]; sprintf (msg, "%03x", t_new->tid);
  _set_statusline (msg, 20);
}

// old line comment removed
if (t_new->new && t_new->tid != t_new->pid) { 
  // new thread
  debug_printf ("DEBUG: new thread (not process), new ESP: 0x%08x\n", t_new->esp0);  // REMOVE_DEBUGGING_CODE
  t_new->new = false;
  
// old line comment removed
// do nothing
// old line comment removed
  asm ("iret");     // return from interrupt handler, do not update r
}
// old line comment removed
                                               // check special case
*r = t_new->regs;               // restore new: registers
// old line comment removed
                                
}
// old line comment removed
for (int signo = 0;  signo < 32;  signo++) {
  if ((t_new->sig_pending & (1<<signo)) != 0    // signal_ is pending
      && t_new->regs.eip < 0xc0000000) {        // and thread is in user mode
    if (t_new->sighandlers[signo] == SIG_DFL) {
      ;    // nop                               // default action, cannot happen
    } else if (t_new->sighandlers[signo] == SIG_IGN) {
      ;    // nop                               // ignored, should not happen
    } else {
      // handler exists
      
// old line comment removed
// Note: t_new->regs has already been copied to r
memaddress oldeip = r->eip;
r->eip = (memaddress)t_new->sighandlers[signo];
// push signal_ number and oldeip on user mode stack
// int xx = PEEK_UINT (r->useresp);                      // REMOVE_DEBUGGING_CODE
// printf ("\nDEBUG: OLD STACK CONTENT: 0x%x\n", xx);    // REMOVE_DEBUGGING_CODE
POKE_UINT (r->useresp, signo);   // overwrites old RET address
r->useresp -= 4;
POKE_UINT (r->useresp, oldeip);  // writes new RET address
// old line comment removed
    }
    t_new->sig_pending &= ~(1<<signo);          // remove bit
    break;                                      // only one handler at a time
  }
}
// old line comment removed
                                     // see chapter on signals
// old line comment removed
// check all entries in the to-be-freed list
// old line comment removed
// do nothing
// old line comment removed
for (int entry = 0;  entry < KSTACK_DELETE_LIST_SIZE;  entry++) {
  if (kstack_delete_list[entry] != 0 && kstack_delete_list[entry] != current_as) {
    // remove it
    addr_space_id id = kstack_delete_list[entry]; 
    page_directory *tmp_pd = address_spaces[id].pd;
    page_table     *tmp_pt = (page_table *) address_spaces[id].kstack_pt;
    // this is the page table which maps the last 4 MB below 0xC0000000
    for (int i = 0;  i < KERNEL_STACK_PAGES;  i++) {
      int frameno = tmp_pt->pds[1023-i].frame_addr;
      release_frame (frameno);
    }
    
// old line comment removed
if (address_spaces[id].extra_kstacks > 0)
//  printf ("DEBUG: remove extra kernel stacks, extra_kstacks = %d\n", // REMOVE_DEBUGGING_CODE
//          address_spaces[id].extra_kstacks);                         // REMOVE_DEBUGGING_CODE
while (address_spaces[id].extra_kstacks > 0) {
  uint stack = TOP_OF_KERNEL_MODE_STACK -
    (KERNEL_STACK_PAGES + 2 * (address_spaces[id].extra_kstacks)) * PAGE_SIZE;
  int frameno = mmu_p (id, stack/PAGE_SIZE);
  if (frameno != -1)  release_frame (frameno);
  address_spaces[id].extra_kstacks--;
}
// old line comment removed
                                           // see Chapter 7
    kstack_delete_list[entry] = 0;   // remove entry from kstack delete list
    release_page (((memaddress)tmp_pt) >> 12);  // free memory for page table
    release_page (((memaddress)tmp_pd) >> 12);  // ... and page directory
    address_spaces[id].status = AS_FREE;        // mark address space as free
  }
}
// old line comment removed
// do nothing
// old line comment removed
                                       // if there are any 
// old line comment removed
  debug_printf ("LEAVE scheduler\n");       // REMOVE_DEBUGGING_CODE
  
// old line comment removed
// do nothing
// old line comment removed
  return;
}
// old line comment removed
void page_fault_handler (context_t *r) {
  
// old line comment removed
memaddress faulting_address;
asm volatile ("mov %%cr2, %0" : "=r" (faulting_address));   // read_ address
int present   = !(r->err_code & 0x1);   // page present?
int rw = r->err_code & 0x2;             // attempted to write_?
int us = r->err_code & 0x4;             // CPU in user-mode (ring 3)?
int reserved = r->err_code & 0x8;       // overwritten CPU-reserved bits of 
                                        // page entry?
int id = r->err_code & 0x10;            // caused by an instruction fetch?

// old line comment removed
int pageno = faulting_address / PAGE_SIZE;
// printf ("DEBUG: trying to page in page 0x%x, AS %d\n", pageno, current_as);  // REMOVE_DEBUGGING_CODE
if (page_in (current_as, pageno) == 0) {
  return;           // success, leave fault handler
}
// old line comment removed
                                                      // see next section
// old line comment removed
if (faulting_address <= TOP_OF_USER_MODE_STACK && 
    faulting_address >= 
    TOP_OF_USER_MODE_STACK-address_spaces[current_as].stacksize - PAGE_SIZE) {
  
// old line comment removed
// printf ("DEBUG: enlarging stack, addr = 0x%x\n", faulting_address);  // REMOVE_DEBUGGING_CODE
memaddress new_stack = TOP_OF_USER_MODE_STACK;
new_stack -= address_spaces[current_as].stacksize;
int pageno = new_stack / PAGE_SIZE - 1;
int frameno;
if ((frameno = request_new_frame ()) < 0) {
  printf ("\nERROR: no free frame, cannot grow user mode stack\n");  // error
  
// old line comment removed
thread_table[current_task].state = TSTATE_ZOMBIE;
remove_from_ready_queue (current_task);
r->ebx = -1;  // exit_ code for this process
syscall_exit (r);
// old line comment removed
};

as_map_page_to_frame (current_as, pageno, frameno);   // update page table and
address_spaces[current_as].stacksize += PAGE_SIZE;    // TCB stack size entry
// old line comment removed
                                                   // user mode, stack
  return;
}
// old line comment removed
printf ("Page fault! ( ");              // write_ error message.
if (present) printf ("present ");    if (rw) printf ("re" "ad-only ");
if (us)      printf ("user-mode ");  if (id) printf ("instruction-fetch ");
printf (")\n");
// old line comment removed
printf ("'%s' Exception at 0x%08x (task=%d, as=%d).\n", 
  exception_messages[r->int_no], r->eip, current_task, current_as);        
printf ("eflags: 0x%08x  errcode: 0x%08x\n", r->eflags, r->err_code);
printf ("eax: %08x  ebx: %08x  ecx: %08x  edx: %08x \n",
  r->eax, r->ebx, r->ecx, r->edx);
printf ("eip: %08x  esp: %08x  int: %8d  err: %8d \n", 
  r->eip, r->esp, r->int_no, r->err_code);
printf ("ebp: %08x  cs: 0x%02x ds: 0x%02x es: 0x%02x fs: 0x%02x ss: 0x%02x \n",
  r->ebp, r->cs, r->ds, r->es, r->fs, r->ss);
printf ("User mode stack: 0x%08x-0x%08x\n", TOP_OF_USER_MODE_STACK 
  - address_spaces[current_as].stacksize, TOP_OF_USER_MODE_STACK);
// old line comment removed
printf ("address = 0x%08x. current_task = %d. current_as = %d.\n", 
        faulting_address, current_task, current_as);     
hexdump (r->eip & 0xFFFFFFF0, (r->eip & 0xFFFFFFF0)+128 );

if ((memaddress)(r->eip) < 0xc0000000) { 
// old line comment removed
thread_table[current_task].state = TSTATE_ZOMBIE;
remove_from_ready_queue (current_task);
r->ebx = -1;  // exit_ code for this process
syscall_exit (r);
// old line comment removed
                                                                              }
// old line comment removed
// error inside the kernel; cannot fix, leave user mode
// old line comment removed
scheduler_is_active = false;  _set_statusline ("SCH:OFF", 16);
// old line comment removed
                      
// old line comment removed
asm ("sti");    // set interrupt flag
// old line comment removed
printf ("\n"); asm ("jmp kernel_shell");   // jump to the kernel shell
// old line comment removed
}
// old line comment removed
int write_swap_page (int as, int pageno, int frameno) {
  // get frame number, if it was not supplied
  if (frameno == -1) frameno = mmu_p (as, pageno);
  if (frameno == -1) return -1;                    // error: page not available
  
  // get index
  int index      = -1;
  int free_index = -1;
  for (int i = 0;  i < MAX_SWAP_FRAMES;  i++) {
    if (free_index == -1 && !paging[i].used)  free_index = i;
    if (paging[i].used && paging[i].as == as && paging[i].pageno == pageno) {
      index = i;  // already on disk!
      break;      
    }
  }
  if (index == -1 && free_index == -1) return -1;  // not found + no free space
  if (index == -1 && free_index != -1) { 
    index = free_index;                            // create new entry
    paging[index].used   = true;
    paging[index].as     = as;
    paging[index].pageno = pageno;
  }
  // note: if (index != -1) we do not modify paging[]; this is an update
  
  // write_ to disk
  debug_printf ("DEBUG: [%d] write_swap_page: going to seek & write\n",  // REMOVE_DEBUGGING_CODE
          current_task);                                                 // REMOVE_DEBUGGING_CODE
  u_lseek (swap_fd, index*PAGE_SIZE, SEEK_SET);
  u_write (swap_fd, (char*)PHYSICAL(frameno*PAGE_SIZE), PAGE_SIZE);
  debug_printf ("DEBUG: [%d] write_swap_page: finished seek & write\n",  // REMOVE_DEBUGGING_CODE
          current_task);                                                 // REMOVE_DEBUGGING_CODE
  return 0;                                        // success
}
// old line comment removed
int read_swap_page (int as, int pageno, int frameno) {
  // get frame number, if it was not supplied
  if (frameno == -1) frameno = mmu_p (as, pageno);
  if (frameno == -1) return -1;       // error: page not available
  
  int index = -1;                                            // get index
  for (int i = 0;  i < MAX_SWAP_FRAMES;  i++) {
    if (paging[i].used && paging[i].as == as && paging[i].pageno == pageno) {
      index = i;  // found the entry!
      break;      
    }
  }

  u_lseek (swap_fd, index*PAGE_SIZE, SEEK_SET);              // read from disk
  u_read (swap_fd, (char*)PHYSICAL(frameno*PAGE_SIZE), PAGE_SIZE);
  return 0;                           // success
}
// old line comment removed
int page_out (int as, int pageno) {
  uint pdindex = pageno/1024; uint ptindex = pageno%1024;
  page_directory *pd = address_spaces[as].pd;
  if ( ! pd->ptds[pdindex].present ) {
    return -1;                                    // fail: page table not found
  } else {
    page_table *pt = (page_table*) PHYSICAL(pd->ptds[pdindex].frame_addr << 12);
    if ( pt->pds[ptindex].present ) {             // found the page
      new_page_desc *pdesc = (new_page_desc*) &pt->pds[ptindex];
      int frameno = pdesc->frame_addr;
      printf ("DEBUG: paging out page 0x%x, "                 // REMOVE_DEBUGGING_CODE
              "AS %d, frame 0x%x\n", pageno,                  // REMOVE_DEBUGGING_CODE
              as, frameno);                                   // REMOVE_DEBUGGING_CODE
      write_swap_page (as, pageno, frameno);      // write_ to swap file
      printf ("DEBUG: back from write_swap_page\n");          // REMOVE_DEBUGGING_CODE
      pdesc->present = false;                     // mark page non-present
      pdesc->paged_out = true;                    // mark page paged-out
      asm volatile ("invlpg %0" : : "m"(*(char*)(pageno<<12)) );
      release_frame (frameno);                    // mark phys. frame as free
      return 0;                                   // success
    } else {
      return -1;                                  // fail: page not found
    };
  }
}
// old line comment removed
int page_in (int as, int pageno) {
  uint pdindex = pageno/1024;
  uint ptindex = pageno%1024;
  page_directory *pd = address_spaces[as].pd;
  if ( ! pd->ptds[pdindex].present ) {
    printf ("DEBUG: page_in: page table not present\n");
    return -1;                                    // fail: page table not found
  } else {
    page_table *pt = (page_table*) PHYSICAL(pd->ptds[pdindex].frame_addr << 12);
    if ( !pt->pds[ptindex].present ) {
      // found the page descriptor
      new_page_desc *pdesc = (new_page_desc*) &pt->pds[ptindex];
      if (!pdesc->paged_out) {
        printf ("DEBUG: page_in: page 0x%0x not marked paged out!\n", pageno);
        return -1;                                // fail: page was not paged out
      }
      int frameno = request_new_frame ();         // reserve a phys. frame
      if (frameno == -1) return -1;               // fail: no free memory
      printf ("DEBUG: paging in page 0x%x, "      // REMOVE_DEBUGGING_CODE
              "AS %d, frame 0x%x\n",              // REMOVE_DEBUGGING_CODE
              pageno, as, frameno);               // REMOVE_DEBUGGING_CODE
      read_swap_page (as, pageno, frameno);       // read_ from swap file
      pdesc->present = true;                      // mark page present
      pdesc->paged_out = false;                   // mark page not paged-out
      pdesc->frame_addr = frameno;                // write_ new phys. frame number
      // asm volatile ("invlpg %0" : : "m"(*(char*)(pageno<<12)) );   // not needed
      return 0;                                   // success
    } else {
      printf ("DEBUG: page_in: page not found\n");
      return -1;                                  // fail: page not found
    };
  }
}
// old line comment removed
void keyboard_handler (context_t *r) {
  char *lower_table; char *upper_table;
  if (LANG_GERMAN) {  
    lower_table = scancode_DE_table; upper_table = scancode_DE_up_table;
  } else {
    lower_table = scancode_table;    upper_table = scancode_up_table;
  }
    
  static boolean shift_pressed = false;  static boolean left_shift_pressed  = false;
  static boolean alt_pressed   = false;  static boolean right_shift_pressed = false;
  static boolean ctrl_pressed  = false;
  
// old line comment removed
byte scancode = inportb (IO_KEYBOARD);   // read_ scan code from keyboard
// printf ("SCANCODE: %d = 0x%x\n", scancode, scancode);    // REMOVE_DEBUGGING_CODE
if (scancode & 0x80) {                   // release key event
  switch (scancode & ~0x80) {
    case KEY_CTRL:    ctrl_pressed        = false; break;
    case KEY_L_SHIFT: left_shift_pressed  = false; break;
    case KEY_R_SHIFT: right_shift_pressed = false; break;
    case KEY_ALT:     alt_pressed         = false; break;
  }
  shift_pressed = left_shift_pressed || right_shift_pressed;
  return;
}
// old line comment removed
// press key event
debug_printf ("KEYCODE: %d\n", scancode);             // REMOVE_DEBUGGING_CODE
switch (scancode) {
  case KEY_CTRL:    ctrl_pressed  = true;                       return;
  case KEY_L_SHIFT: shift_pressed = left_shift_pressed  = true; return;
  case KEY_R_SHIFT: shift_pressed = right_shift_pressed = true; return;
  case KEY_ALT:     alt_pressed   = true;                       return;
}

byte c = (shift_pressed ? upper_table[scancode] : lower_table[scancode]);
// old line comment removed
// Alt-0 to Alt-9: switch terminal
if (alt_pressed && '0' <= c && c <= '9') {
  vt_activate ((int)((c-'0')+9)%10);   // activate virtual console
  vt_move_cursor ();                   // update cursor on new terminal
  return;
};
    
// Ctrl-C: kill and reset input
if (ctrl_pressed && c == 'c') {
  
// old line comment removed
int target_pid = 0;
for (int i = 3;  i < MAX_THREADS;  i++) {
  if (thread_table[i].used && (thread_table[i].terminal == cur_vt)) {
    int is_candidate = true;
    for (int j = 3;  j < MAX_THREADS;  j++) {
      if (thread_table[j].used && (thread_table[j].ppid == i)) {
        // thread j has parent i - not a candidate
        is_candidate = false;
        break;   // leave inner loop
      }
    }
    if (is_candidate) {
      target_pid = i;
      goto end_of_search;
    }
  }
}
end_of_search:
;  // label needs a statement
// old line comment removed
  u_kill (target_pid, SIGKILL);        // kill the process
  return;
}

// Ctrl-L: change keyboard layout
if (ctrl_pressed && c == 'l') {
  switch (LANG_GERMAN) {
    case 0:  LANG_GERMAN = 1;  _set_statusline ("de", 44);  return;
    case 1:  LANG_GERMAN = 0;  _set_statusline ("en", 44);  return;
  }
}

// Shift-Escape: start_ kernel mode shell
if (shift_pressed && c == KEY_ESC && scheduler_is_active) {
  
// old line comment removed
scheduler_is_active = false;  _set_statusline ("SCH:OFF", 16);
// old line comment removed
  printf ("\nGoing to kernel shell\n");
  vt_activate (0);                     // must run on vt0
  kernel_shell ();
  printf ("returning from kernel shell\n");
  return;
};
// old line comment removed
terminal_t *term = &terminals[cur_vt];
if (term->kbd_count < SYSTEM_KBD_BUFLEN) {
  if (ctrl_pressed && c >= 'a' && c <= 'z') c -= 96;  // Ctrl
  term->kbd[term->kbd_pos] = c;
  term->kbd_pos = (term->kbd_pos + 1) % SYSTEM_KBD_BUFLEN;
  term->kbd_count++;
  if (scheduler_is_active) { 
// old line comment removed
thread_id start_pid = keyboard_queue.next;
if (start_pid != 0) {               // only if the queue is not empty
  thread_id search_pid = start_pid;
  do {
    if (thread_table[search_pid].terminal == cur_vt) {
      deblock (search_pid, &keyboard_queue);
      break;
    } else {
      search_pid = thread_table[search_pid].next;
    }
  } while (search_pid != start_pid && search_pid != 0);
}
// old line comment removed
                                                                         }
}
// old line comment removed
}
// old line comment removed
void keyboard_install () {
  install_interrupt_handler (IRQ_KBD, keyboard_handler);
  enable_interrupt (IRQ_KBD);
}
// old line comment removed
void kgetch (char *c) {
  int t = thread_table[current_task].terminal;
  if (t < 0 || t > TERMINALS-1) {
    t = 0;  printf ("ERROR: terminal not set! setting to 0\n");
  }
  terminal_t *term = &terminals[t];

  *c = 0; 
  while (*c == 0) {
    if (term->kbd_count > 0) {
      term->kbd_count--;
      term->kbd_lastread = (term->kbd_lastread+1) % SYSTEM_KBD_BUFLEN;
      *c = term->kbd[term->kbd_lastread];
    } else {
      *c = 0;
    };
  };
};
// old line comment removed
void kreadline (char *s, int maxlength) {
  char c;
  int pos = 0;
  for (;;) {
    
// old line comment removed
asm ("sti");    // set interrupt flag
// old line comment removed
    kgetch (&c);                                // read_ one character
    if (c == 0x08 && pos > 0) {                 // backspace
      pos--;
      kputch (c); kputch (' '); kputch (c);
    } else if ( c == '\n' ) {                   // newline: end of input
      kputch ('\n');
      s[pos] = (char) 0;
      return;
    } else if (c != 0x08 && pos < maxlength) {  // other character
      kputch (c);
      s[pos++] = c;
    };
  };
};
// old line comment removed
int vt_activate (int new_vt) {
  if (new_vt < 0 || new_vt > MAX_VT)  return -1;        // no such console
  else {
    memcpy (vt[cur_vt].mem, (void*)VIDEORAM, VT_SIZE);  // save old contents
    vt[cur_vt].x = csr_x; vt[cur_vt].y = csr_y; 
    memcpy ((void*)VIDEORAM, vt[new_vt].mem, VT_SIZE);  // load new contents
    cur_vt = new_vt;
    csr_x = vt[new_vt].x; csr_y = vt[new_vt].y;
    vt_move_cursor ();
    return 0;
  }
}
// old line comment removed
void vt_move_cursor () {
  unsigned position = csr_y * 80 + csr_x;
  // high byte:
  outportb (IO_VGA_TARGET, IO_VGA_CURSOR_LOC_HIGH);
  outportb (0x3D5, position >> 8);
  // low byte:
  outportb (IO_VGA_TARGET, IO_VGA_CURSOR_LOC_LOW);
  outportb (0x3D5, position & 0xff);  // low byte
}
// old line comment removed
void syscall_setterm (context_t *r) {
  int vt = r->ebx;                             // argument in ebx register
  if (vt<0 || vt>MAX_VT) { return; }           // check if proper number...
  thread_table[current_task].terminal = vt;
  debug_printf ("DEBUG: current_task = %d\n",              // REMOVE_DEBUGGING_CODE
                current_task);                             // REMOVE_DEBUGGING_CODE
  debug_printf ("DEBUG: terminal     = %d\n", vt);         // REMOVE_DEBUGGING_CODE
};
// old line comment removed
void vt_clrscr () {
  word blank    = 0x20 | VT_NORMAL_BACKGROUND;
  word blankrev = 0x20 | VT_BLUE_BACKGROUND;
  int process_term;
  if (scheduler_is_active) {
    process_term = thread_table[current_task].terminal;
    word *memptr = (word*)vt[process_term].mem;
    memsetw (memptr, blank, VT_SIZE/2);                     // lines 1-24
    vt_set_xy (0, 0);
  }
  
  // current terminal?
  if ((!scheduler_is_active) || (scheduler_is_active && process_term == cur_vt))
    memsetw (textmemptr, blank, VT_SIZE/2);                 // lines 1-24
    
  // kernel mode? clear status line, set cursor
  if (!scheduler_is_active) {
    memsetw (textmemptr + VT_SIZE/2, blankrev, VT_WIDTH);   // line  25
    csr_x = csr_y = 0;
    vt_move_cursor ();
  }
}
// old line comment removed
void vt_get_xy (char *x, char *y) {
  int process_term = thread_table[current_task].terminal;
  *x = vt[process_term].x;
  *y = vt[process_term].y;
}

void vt_set_xy (char x, char y) {
  int process_term = thread_table[current_task].terminal;
  vt[process_term].x = x;
  vt[process_term].y = y;
  
  // current terminal?
  if (process_term == cur_vt) {
    csr_x = x; csr_y = y;
    vt_move_cursor ();
  }
}
// old line comment removed
void read_write_screen (char *buf, boolean read_flag) {
  // if read_flag == true: read_ from screen, otherwise write_
  int process_term = thread_table[current_task].terminal;
  char *video_address = (char*) vt[process_term].mem;
  
  if (read_flag) {
    memcpy (buf, video_address, VT_SIZE);    // read_ the screen
  } else {
    memcpy (video_address, buf, VT_SIZE);    // write_ the screen
    // current terminal?
    if (process_term == cur_vt)
      memcpy ((char*)VIDEORAM, video_address, VT_SIZE);
  }
}

void read_screen (char *buf)  { read_write_screen (buf, true);  }
void write_screen (char *buf) { read_write_screen (buf, false); }
// old line comment removed
void vt_scroll_mem (word *address) {
  word blank = ' ' | VT_NORMAL_BACKGROUND;  // space + format
  memcpy  (address, address + VT_WIDTH, (VT_HEIGHT-1) * VT_WIDTH * 2);
  memsetw (address + (VT_HEIGHT-1) * VT_WIDTH, blank, VT_WIDTH);
}
// old line comment removed
void vt_scroll () {
  term_buffer *term;
  short int target_vt;
  if (scheduler_is_active) {
    target_vt = thread_table[current_task].terminal;
    term = &vt[target_vt];
  } else {
    target_vt = KERNEL_VT;   // kernel: default write_ to 0
  }

  if (cur_vt == target_vt && csr_y >= VT_HEIGHT) {
    vt_scroll_mem ((word*)VIDEORAM);
    csr_y = VT_HEIGHT-1;
  }

  if (scheduler_is_active && term->y >= VT_HEIGHT) {
    vt_scroll_mem ((word*)term->mem);
    term->y = VT_HEIGHT-1;
  }
}
// old line comment removed
void kputch (byte c) {
  // check if we're writing to current terminal
  term_buffer *term;
  short int target_vt;
  word *where;
  if (scheduler_is_active) {
    target_vt = thread_table[current_task].terminal;
    term = &vt[target_vt];
  } else {
    target_vt = KERNEL_VT;   // kernel: default write_ to 0
  }

  switch (c) {
    case '\b': // backspace, move cursor back
               if (cur_vt == target_vt) { if (csr_x   != 0) csr_x--;   }
               if (scheduler_is_active) { if (term->x != 0) term->x--; }
               break;

    case '\r': // carriage return, go back to first column
               if (cur_vt == target_vt) { csr_x = 0;   }
               if (scheduler_is_active) { term->x = 0; }
               break;

    case '\n': // newline, go to next line, first column
               if (cur_vt == target_vt) { csr_x = 0;    csr_y++;   }
               if (scheduler_is_active) { term->x = 0;  term->y++; }
               break;
  }

  if (c >= ' ') {   // normal character
    if (cur_vt == target_vt) {
      where = textmemptr + (csr_y * 80 + csr_x);
      *where = c | VT_NORMAL_BACKGROUND;
      csr_x++;
    }
    if (scheduler_is_active) {
      where = (word*)term->mem + (term->y * 80 + term->x);
      *where = c | VT_NORMAL_BACKGROUND;
      term->x++;
    }
  }

  if (csr_x >= 80) {   // end of line reached
    if (cur_vt == target_vt) { csr_x = 0;    csr_y++;   }
    if (scheduler_is_active) { term->x = 0;  term->y++; }
  }

  vt_scroll ();   // scroll if necessary
  if (cur_vt == target_vt) { vt_move_cursor (); };
    
  // write_ to serial console
  if (c == '\b') {  //  backspace
    uartputc ('\b'); uartputc (' '); uartputc ('\b');
  } else uartputc (c);
  // bochs_putch (c);   // also write_ on BOCHS terminal  // REMOVE_DEBUGGING_CODE
}

void kputs (char *text) {
  while (*text != 0) 
    kputch (*(text++));
}
// old line comment removed
void uartputc (int c) {
  // taken from the xv6 operating system [CKM12], uart.c
  if (!uart[0]) return;      // leave if we have no first serial port
  // wait until COM1 is ready to receive another byte
  for (int i = 0; i < 128 && !(inportb (IO_COM1+5) & 0x20); i++) ;
  outportb (IO_COM1+0, c);   // write_ the byte
}
// old line comment removed
void set_statusline (char *text) { _set_statusline (text, 0); }

void _set_statusline (char *text, int offset) {
  int i = 0;
  uint videoaddress = VIDEORAM + VT_SIZE+2*offset;  // last line of video
  while ((*text != 0) && (i < 80)) {
    POKE (videoaddress + 2*i, *text);
    i++; text++;
  }
}
// old line comment removed
void timer_phase (int hz) {
  // source: http://www.osdever.net/bkerndev/Docs/pit.htm
  int divisor = 1193180 / hz;                    // calculate divisor
  outportb (IO_CLOCK_COMMAND,  0x36);            // set command byte 0x36
  outportb (IO_CLOCK_CHANNEL0, divisor & 0xFF);  // set low byte of divisor
  outportb (IO_CLOCK_CHANNEL0, divisor >> 8);    // set high byte of divisor
};
// old line comment removed
ulong unixtime (int year, int month, int day, int hour, int minute, int second) {
  // Source code taken from http://de.wikipedia.org/wiki/Unixzeit,
  // variable and function names translated to english
  const short days_since_start_of_year[12] = 
    {0,31,59,90,120,151,181,212,243,273,304,334};
  unsigned long years=year-1970;
  int leapyears=((year-1)-1968)/4 - ((year-1)-1900)/100 + ((year-1)-1600)/400;
 
  ulong unix_time = second + 60*minute + 60*60*hour +
                    (days_since_start_of_year[month-1]+day-1)*60*60*24 +
                    (years*365+leapyears)*60*60*24; 
  if ( (month>2) && (year%4==0 && (year%100!=0 || year%400==0)) )
    unix_time+=60*60*24;   // leap day?
  return unix_time;
}
// old line comment removed
short yearlength (short year) {
  int res = 364;
  if ( ((year % 4 == 0) && ( year % 100 != 0)) || (year % 400 == 0) )  res++;
  return res;
}
 
void rev_unixtime (ulong utime, short *year, char *month, char *day,
                   char *hour, char *minute, char *second) {
  char days_per_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int days = utime / (60*60*24);    char sec = utime % 60;
  char min = (utime/60) % 60;       char hou  = (utime/(60*60)) % 24;
  
  int yy = 1970;
  if (days > 15706) {   // speed up calculation for 2013 or later
    days -= 15706;
    yy += 43;
  }

  for (;;) {
    int l = yearlength (yy);
    if (days >= l) {
      yy++;
      days -= (l+1);    // distance between two years is l+1, not l
    } else break;
  }
      
  int mon = 1;
  for (;;) {
    int l = days_per_month[mon];
    if ((l == 2) && (yearlength (yy) == 365)) l++;
    if (days >= l) {
      mon++;
      days -= l;
    } else break;
  }
  
  days++;
  *year = yy;   *month  = mon; *day    = days;   // return results
  *hour = hou;  *minute = min; *second = sec;
}
// old line comment removed
void timer_handler (context_t *r) {
  char buf[80];   // temporary buffer, can be used by all timer tasks
  
// old line comment removed
if (scheduler_is_active && ((system_ticks % 10) == 0)) {     
  
// old line comment removed
if (mutex_try_lock (paging_lock)) {
  for (int as = 1;  as < MAX_ADDR_SPACES;  as++) {
    if (address_spaces[as].status != AS_FREE) {
      page_directory *pd = address_spaces[as].pd;
      for (int i = 0;  i < 100;  i++) {      // < 768: only work on process memory
        if (pd->ptds[i].present) {           // directory entry in use
          page_table *pt = (page_table*)(PHYSICAL ((pd->ptds[i].frame_addr)<<12));
          for (int j = 0;  j < 1024;  j++) {
            if (pt->pds[j].present) {        // table entry in use
              
// old line comment removed
int pageno = i*1024 + j;
int n = pt->pds[j].accessed;   // get and ...
pt->pds[j].accessed = false;   // reset access flag
int index;
if (n == 1 && 
    (index = hash ((as << 20) | pageno, PG_MAX_COUNTERS)) < PG_MAX_COUNTERS) {
  counter_table[index].used = true;
  counter_table[index].count++;
}
// old line comment removed
            }
          }
        }
      }
    }
  }
  mutex_unlock (paging_lock);
}
// old line comment removed
                                          // Every 10 ticks (~ 0.1 seconds)
}
if (scheduler_is_active && ((system_ticks % 50) == 5)) {     
  
// old line comment removed
// get the maximum count
int themax = 0;
if (mutex_try_lock (paging_lock)) {
  for (int index = 0; index < PG_MAX_COUNTERS; index++) {
    if (counter_table[index].used) {
      int val = counter_table[index].count;
      if (val > themax) themax = val;
    }
  }

  if (themax > PG_COUNTER_THRESHOLD) {
    // rescale all counters
    for (int index = 0; index < PG_MAX_COUNTERS; index++) {
      if (counter_table[index].used) {
        counter_table[index].count /= 2;
        counter_table[index].count += 1;  // avoid 0 value
      }
    }
  }
  mutex_unlock (paging_lock);
}
// old line comment removed
                                           // Every 50 ticks (~ 0.5 seconds) 
}
// old line comment removed
if (scheduler_is_active && ((system_ticks % 10) == 0)) {     
  // Every   10 clocks (approx. 0.1 seconds) 
  if (swapper_lock->bq.next)
    mutex_unlock (swapper_lock);
}
// old line comment removed
system_ticks++;    // one more timer interrupt
system_time = (uint)(system_ticks/100) + system_start_time;  // frequency: 100 Hz
// old line comment removed
char sched_chars[] = "|/-\\";   // scheduler activity
static short sched_c = 0;       // next character to display

if (system_ticks % 5 == 0) {
  // cycle |/-\\- to show scheduler calls in upper right corner
  POKE (VIDEORAM + 79*2, sched_chars[sched_c]);
  sched_c++; sched_c %= 4;
  scheduler (r, SCHED_SRC_TIMER);
};
// old line comment removed
short int sec,min,hour;

if (system_ticks % 100 == 0) {          // Every 100 clocks (approx. 1 second) 
  hour = (system_time/60/60)%24;        // display the time
  min = (system_time/60)%60;
  sec = system_time%60;
  sprintf ((char*)&buf, "%02d:%02d:%02d", hour, min, sec);
  _set_statusline ((char*)&buf, 72);
}
// old line comment removed
fdc_timer ();
// old line comment removed
  
  // show current terminal, free frames, current_as
  sprintf ((char*)&buf, "tty%d  FF=%04x  AS=%04d", cur_vt, free_frames, current_as);
  _set_statusline ((char*)&buf, 48);  
}
// old line comment removed
void uartinit (int serport) {
  char *p;
  word io_com, irq;
  switch (serport) {
    case 1: io_com = IO_COM1; irq = IRQ_COM1; break;
    case 2: io_com = IO_COM2; irq = IRQ_COM2; break;
    default: return;
  }

  outportb (io_com+2, 0);       // Turn off the FIFO
  // set 9600 baud, 8 data bits, 1 stop bit, parity off.
  outportb (io_com+3, 0x80);    // Unlock divisor
  outportb (io_com+0, 115200/9600);
  outportb (io_com+1, 0);
  outportb (io_com+3, 0x03);    // Lock divisor, 8 data bits.
  outportb (io_com+4, 0);
  outportb (io_com+1, 0x01);    // Enable receive interrupts.

  // If status is 0xFF, no serial port.
  if (inportb (io_com+5) == 0xFF) { return; }
  uart[serport-1] = 1;

  // Acknowledge pre-existing interrupt conditions; enable interrupts.
  inportb (io_com+2);
  inportb (io_com+0);
  enable_interrupt (irq);
}
// old line comment removed
void uart2putc (int c) {
  // taken from the xv6 operating system [CKM12], uart.c
  if (!uart[1]) return;      // leave if we have no second serial port
  // wait until COM2 is ready to receive another byte
  for (int i = 0;  i < 128 && !(inportb (IO_COM2+5) & 0x20);  i++) ;
  outportb (IO_COM2+0, c);   // write_ the byte
}
// old line comment removed
void wait_semaphore (kl_semaphore_id sid) {
  kl_semaphore sem = 
// old line comment removed
kl_semaphore_table[sid]
// old line comment removed
                                                                    ;
  
// old line comment removed
// do nothing
// old line comment removed
  sem.counter--;
  if (sem.counter < 0) {
    block (&sem.bq, TSTATE_LOCKED);
    debug_printf ("sem_LOCK going to call resign()\n");  // REMOVE_DEBUGGING_CODE
    
// old line comment removed
asm (".intel_syntax noprefix; \
  mov eax, 66;; \
  int 0x80;; \
  .att_syntax; ");
// old line comment removed
  }
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
void signal_semaphore (kl_semaphore_id sid) {
  kl_semaphore sem = 
// old line comment removed
kl_semaphore_table[sid]
// old line comment removed
                                                                    ;
  
// old line comment removed
// do nothing
// old line comment removed
  sem.counter++;
  if (sem.counter < 1) {
    blocked_queue *bq = &(sem.bq);
    thread_id head = bq->next;
    if (head != 0) {
      deblock (head, bq);
    } 
  }
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
kl_semaphore_id get_new_semaphore (int k) {
  int check = MAX_SEMAPHORES;
  while (kl_semaphore_table[next_kl_semaphore].used == true) {
    next_kl_semaphore = (next_kl_semaphore + 1) % MAX_SEMAPHORES;
    check--;
    if (check <= 0)  return -1;
  }
  kl_semaphore_table[next_kl_semaphore].used    = true;
  kl_semaphore_table[next_kl_semaphore].counter = k;
  initialize_blocked_queue (&kl_semaphore_table[next_kl_semaphore].bq);
  return next_kl_semaphore;
}
// old line comment removed
void release_semaphore (kl_semaphore_id s) {
  kl_semaphore_table[s].used = false;
  while (front_of_blocked_queue (kl_semaphore_table[s].bq) != 0) {
    thread_id t = front_of_blocked_queue (kl_semaphore_table[s].bq);
    remove_from_blocked_queue (t, &kl_semaphore_table[s].bq);
    add_to_ready_queue (t);
  }
}
// old line comment removed
void mutex_lock (lock lockvar) {
  if ( //lockvar != kstack_delete_list_lock &&     // REMOVE_DEBUGGING_CODE
       lockvar != paging_lock)                     // REMOVE_DEBUGGING_CODE
    debug_printf ("[%d]   LOCK(%s)\n",             // REMOVE_DEBUGGING_CODE
                  current_task,                    // REMOVE_DEBUGGING_CODE
                  lockvar->lockname);              // REMOVE_DEBUGGING_CODE
  if (current_task == 0) { return; }        // no process
  
// old line comment removed
// do nothing
// old line comment removed
  // while ( tsl_test_and_set (lockvar) != 0 ) {   // REMOVE_DEBUGGING_CODE
  while ( lockvar->l == 1 ) {
    block (&(lockvar->bq), TSTATE_LOCKED);  // put process to sleep
    debug_printf ("LOCK going to call resign()\n");   // REMOVE_DEBUGGING_CODE
    
// old line comment removed
asm (".intel_syntax noprefix; \
  mov eax, 66;; \
  int 0x80;; \
  .att_syntax; ");
// old line comment removed
  }
  lockvar->l = 1;
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
boolean mutex_try_lock (lock lockvar) {
  if ( // lockvar != kstack_delete_list_lock &&        // REMOVE_DEBUGGING_CODE
      lockvar != paging_lock)                          // REMOVE_DEBUGGING_CODE
    debug_printf ("[%d] TRLOCK(%s)\n",                 // REMOVE_DEBUGGING_CODE
                  current_task, lockvar->lockname);    // REMOVE_DEBUGGING_CODE
//  int res = tsl_test_and_set (lockvar);              // REMOVE_DEBUGGING_CODE
//  return (res == 0);                                 // REMOVE_DEBUGGING_CODE
  
// old line comment removed
// do nothing
// old line comment removed
  int tmp = lockvar->l;  lockvar->l = 1;
  
// old line comment removed
// do nothing
// old line comment removed
  return (tmp == 0);
}
// old line comment removed
void mutex_unlock (lock lockvar) {
  if (current_task == 0) { return; }    // no process
  if (lockvar->l == 0) {
    debug_printf ("NOTICE: unlocking unlocked LOCK: %s\n", lockvar->lockname);
  }
//  tsl_reset (lockvar);                              // REMOVE_DEBUGGING_CODE
  
// old line comment removed
// do nothing
// old line comment removed
  lockvar->l = 0;
  // wake a process
  blocked_queue *bq = &(lockvar->bq);
  thread_id head = bq->next;
  if (head != 0) {            // If one thread is waiting, deblock and resign_
    deblock (head, bq);
    debug_printf ("UNLOCK going to call resign()\n");    // REMOVE_DEBUGGING_CODE
  } 
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
lock get_new_lock (char *name) {
  mutex_lock (kernel_locks);  // lock the list of kernel locks, we use kernel_locks[0]
    for (int i = 1;  i < MAX_LOCKS;  i++) {
      if (!kernel_locks[i].used) {
        kernel_locks[i].used = true;
        initialize_blocked_queue (&kernel_locks[i].bq); // initialize blocked queue
        strncpy (kernel_locks[i].lockname, name, 20);
        mutex_unlock (kernel_locks);                    // unlock access to  list
        return &kernel_locks[i];
      }
    }
  mutex_unlock (kernel_locks);
  return NULL;
}
// old line comment removed
void release_lock (lock l) {
  mutex_lock (kernel_locks);  // lock the list of kernel locks
    l->used = false;
    blocked_queue *bq = &(l->bq);
    thread_id head = bq->next;
    while (head != 0) {
      thread_id next = thread_table[head].next;
      deblock (head, bq);
      head = next;
    }
  mutex_unlock (kernel_locks);
}
// old line comment removed
int u_pthread_mutex_init (pthread_mutex_t *restrict mutex,
         const pthread_mutexattr_t *restrict attr) {
  char s[20];
  sprintf ((char*)s, "lock, pid=%d", thread_table[current_task].pid);
  lock tmp = get_new_lock (s);
  // printf ("LOCKNAME = '%s', address = %08x\n", s, tmp);  // REMOVE_DEBUGGING_CODE
  if (tmp != NULL) {
    *mutex = (pthread_mutex_t)tmp;
    return 0;        // success
  } else {
    thread_table[current_task].error = EAGAIN;
    return -1;       // error
  }
}
// old line comment removed
int u_pthread_mutex_lock (pthread_mutex_t *mutex) {
  lock l = (lock)*mutex;
  mutex_lock (l);
  return 0;
}

int u_pthread_mutex_trylock (pthread_mutex_t *mutex) {
  lock l = (lock)*mutex;
  if (mutex_try_lock (l))
    return 0;    // success
  else {
    thread_table[current_task].error = EBUSY;
    return -1;   // error
  }
}

int u_pthread_mutex_unlock (pthread_mutex_t *mutex) {
  lock l = (lock)*mutex;
  mutex_unlock (l);
  return 0;
}
// old line comment removed
int u_pthread_mutex_destroy (pthread_mutex_t *mutex) {
  lock l = (lock)*mutex;
  release_lock (l);
  return 0;
}
// old line comment removed
void print_mount_table () {
  int i, dev;
  for (i=0; i<current_mounts; i++) {
    dev = mount_table[i].device;
    if (dev != 0) {
      char *devname;
      switch (dev) {
        case DEV_HDA: devname = "hda"; break;
        case DEV_HDB: devname = "hdb"; break;
        case DEV_FD0: devname = "fd0"; break;
        case DEV_FD1: devname = "fd1"; break;
      }
      printf ("mount: dev[%02x:%02x] = /dev/%s on %-5s type %-5s (options %d)\n",
              devmajor (dev), devminor (dev), devname, mount_table[i].mountpoint, 
              fs_names[mount_table[i].fstype], mount_table[i].mount_flags);
    } else
      printf ("mount: none                  on %-5s type %-5s (options %d)\n",
              mount_table[i].mountpoint, 
              fs_names[mount_table[i].fstype], mount_table[i].mount_flags);
  }
}
// old line comment removed
int get_dev_and_path (char *path, short *dev, short *fs, char *localpath) {
  int i, mount_entry;
  for (i = current_mounts-1;  i >= 0;  i--) {
    // standard case: file; mount point (e.g. "/mnt/" is head of path)
    if (string_starts_with (path, mount_table[i].mountpoint)) {
      mount_entry = i;  break;
    }
    // second case: directory, path is mount point without /, e.g. "/mnt"
    if ( strlen (path) == strlen (mount_table[i].mountpoint)-1 &&
       string_starts_with (mount_table[i].mountpoint, path) ) {
      mount_entry = i;  break;
    }
  }
// old line comment removed
  split_mountpoint (mount_table[mount_entry].mountpoint, path, localpath);
  if (strlen (localpath) == 0) {
    // empty string
    localpath[0] = '/';  localpath[1] = 0;
  }
  *dev = mount_table[mount_entry].device;
  *fs  = mount_table[mount_entry].fstype;
  return 0;
}
// old line comment removed
int string_starts_with (char *str, char *prefix) {
  if (strlen (prefix) > strlen (str)) { return false; }  // cannot be a sub-string
  while (*prefix != '\0') {
    if (*prefix++ != *str++) { return false; }     // found different character
  };
  return true;                                     // parsed all of prefix; match!
}
// old line comment removed
void split_mountpoint (char *mountpoint, char *path, char *localpath) {
  // input:  mountpoint, e.g. /home/
  //         path,       e.g. /home/user/file.txt
  // output: localpath,  e.g. /user/file.txt
  int len = strlen (mountpoint);
  strncpy (localpath, path+len-1, 256);
}
// old line comment removed
void relpath_to_abspath (const char *relpath, char *abspath) {
  if (strlen (thread_table[current_task].cwd) > 1) {
    // combine cwd and relpath, add "/" in the middle
    strncpy (abspath, thread_table[current_task].cwd, 256);
  } else {
    strncpy (abspath, "", 256);
  }
  strncpy (abspath + strlen (abspath) + 1, relpath, 256 - strlen (abspath) - 1);
  abspath[strlen (abspath)] = '/';
  debug_printf ("absolute path: %s\n", abspath);    // REMOVE_DEBUGGING_CODE
}
// old line comment removed
int u_open (char *path, int oflag, int open_link) {
  
// old line comment removed
char  localpath[256], abspath[256];
short device, fs;
// old line comment removed
  
// old line comment removed
if (*path != '/') 
  relpath_to_abspath (path, abspath);
else
  strncpy (abspath, path, 256);
get_dev_and_path (abspath, &device, &fs, (char*)&localpath);
// old line comment removed
  
// old line comment removed
struct stat st;
char link[256];
u_stat (abspath, &st);
if (((st.st_mode & S_IFLNK) == S_IFLNK) && (open_link == FOLLOW_LINK)) {
  // open_ (how?), read_, then u_open (symlink)
  int link_fd = u_open (abspath, O_RDONLY, DONT_FOLLOW_LINK);  // open_ link file
  u_read (link_fd, link, 256);
  u_close (link_fd);
  return u_open (link, oflag, FOLLOW_LINK);                    // recursion
}
// old line comment removed
  if (scheduler_is_active) {
    
// old line comment removed
boolean access_ok = false;
word euid = thread_table[current_task].euid;
word egid = thread_table[current_task].egid;
struct stat st;

if (euid == 0) {
  access_ok = true;   // user root can do anything
} else {
  // loop over the directories
  char old_dirname[256]; char dirname[256]; char rest[256];
  strncpy (dirname, abspath, 256);
  for (;;) {
    strncpy (old_dirname, dirname, 256);
    splitpath (old_dirname, dirname, rest);   // ignore rest
    // printf ("DEBUG: checking access to directory %s\n", dirname);  // REMOVE_DEBUGGING_CODE
    u_stat (dirname, &st);
    access_ok = 
// old line comment removed
( // user may have access,                         r-x------ ?
  (((euid == st.st_uid) &&                        (st.st_mode & 0500) == 0500)) ||     
  // group may have access (if wrong user),        ---r-x--- ?
  (((euid != st.st_uid) && (egid == st.st_gid) && (st.st_mode & 0050) == 0050)) ||
  // others may have access (wrong user, group),   ------r-x ?
  (((euid != st.st_uid) && (egid != st.st_gid) && (st.st_mode & 0005) == 0005))  )
// old line comment removed
                                                         ;
    if (!access_ok) {
      // printf ("DEBUG: access denied at directory %s\n", dirname);  // REMOVE_DEBUGGING_CODE
      set_errno (EACCES);
      return -1;
    }
    if (strlen (dirname) == 1) break;         // reached root directory
  }
  // finally: check file permissions   
  access_ok = check_access (abspath, euid, egid, oflag);
}
if (!access_ok) {
  return -1;  // wrong permissions
}
// old line comment removed
                                                   // see user/group chapter
  }
  
  int fd;
  switch (fs) {
    case FS_MINIX: 
      fd = mx_open (device, localpath, oflag);
      if (fd == -1) return -1;                 // error (opening failed)
      else          return (fs << 8) + fd;
    case FS_FAT:    return -1;                 // not implemented
    case FS_DEV: 
      fd = dev_open (localpath, oflag);
      if (fd == -1) return -1;                 // error (opening failed)
      else          return (fs << 8) + fd;
    case FS_ERROR:  return -1;                 // error (wrong FS)
    default:        return -1;                 // error (wrong FS)
  }
}
// old line comment removed
int u_read (int fd, void *buf, int nbyte) {
  if (fd < -100) { 
// old line comment removed
byte c = 0;
unsigned int u;
switch (fd) {
  case DEV_STDIN: 
    for (int i = 0;  i < nbyte;  i++) {
      // read_ one character from the keyboard
      __asm__ ("\
        .intel_syntax noprefix; \
        mov eax, 525; \
        int 0x80; \
        mov %0, ebx; \
        .att_syntax"
        :
        "=r"(u)
      );
      c = (byte) u;
      ((byte*) buf)[i] = c;
    };
    break;

  case DEV_STDOUT:
  case DEV_STDERR:
    printf ("(ERROR: reading from stdout or stderr)\n");
    return (-1);         // error, cannot read_ from output

  default: return (-1);  // pipes not implemented yet
}
// old line comment removed
                                                    }
  
// old line comment removed
if (fd < 0) return -1;   // file not open
int fs      = fd >> 8;
int localfd = fd & 0xff;
// old line comment removed
                                                                      
  switch (fs) {
    case FS_MINIX: return mx_read  (localfd, buf, nbyte);
    case FS_FAT:   return -1;                               // not implemented
    case FS_DEV:   return dev_read (localfd, buf, nbyte);
    case FS_ERROR: return -1;                               // error
    default:       return -1;
  }
}
// old line comment removed
int u_write (int fd, void *buf, int nbyte) {
  if (fd < -100) { 
// old line comment removed
byte c;
switch (fd) {
  case DEV_STDIN: 
    printf ("(ERROR: writing to stdin)\n");
    return (-1);  // error, cannot write_ to input

  case DEV_STDOUT:
  case DEV_STDERR:
    for (int i = 0;  i < nbyte;  i++) {
      c = ((char*)buf)[i];
      if (c > 31 || c == '\n' || c == 0x08) {
        kputch (c);                    // regular characters: 32..255, \n, \b
      } else {
        kputch ('^'); kputch (c+64);   // control characters: <32
      }
    }
    
  default: return (-1);                // pipes not implemented yet
}
// old line comment removed
                                                      }
  
// old line comment removed
if (fd < 0) return -1;   // file not open
int fs      = fd >> 8;
int localfd = fd & 0xff;
// old line comment removed
                                                                      
  switch (fs) {
    case FS_MINIX: return mx_write  (localfd, buf, nbyte);
    case FS_FAT:   return -1;  // not implemented
    case FS_DEV:   return dev_write (localfd, buf, nbyte);
    case FS_ERROR: return -1;  // error
    default:       return -1;
  }
}
// old line comment removed
int u_close (int fd) {
  
// old line comment removed
if (fd < 0) return -1;   // file not open
int fs      = fd >> 8;
int localfd = fd & 0xff;
// old line comment removed
                                                                      
  switch (fs) {
    case FS_MINIX: return mx_close (localfd);
    case FS_FAT:   return -1;                                  // not implemented
    case FS_DEV:   return dev_close (localfd);
    case FS_ERROR: return -1;                                  // error
    default:       return -1;
  }
}

int u_lseek (int fd, int offset, int whence) {
  
// old line comment removed
if (fd < 0) return -1;   // file not open
int fs      = fd >> 8;
int localfd = fd & 0xff;
// old line comment removed
                                                                      
  switch (fs) {
    case FS_MINIX: return mx_lseek (localfd, offset, whence);
    case FS_FAT:   return -1;                                  // not implemented
    case FS_DEV:   return dev_lseek (localfd, offset, whence);
    case FS_ERROR: return -1;                                  // error
    default:       return -1;
  }
}
// old line comment removed
int u_unlink (const char *path) {
  
// old line comment removed
char  localpath[256], abspath[256];
short device, fs;
// old line comment removed
  
// old line comment removed
if (*path != '/') 
  relpath_to_abspath (path, abspath);
else
  strncpy (abspath, path, 256);
get_dev_and_path (abspath, &device, &fs, (char*)&localpath);
// old line comment removed
                                                                        
  switch (fs) {
    case FS_MINIX: return mx_unlink (device, localpath);
    case FS_FAT:   return -1;  // not implemented
    case FS_DEV:   return -1;  // no unlink_ support in device FS
    case FS_ERROR: return -1;  // error
    default:       return -1;
  }
}
// old line comment removed
int u_link (const char *path, const char *path2) {
  char localpath[256],  abspath[256];  short device,  fs;
  char localpath2[256], abspath2[256]; short device2, fs2;
  char dir2[256], base2[256], localdir2[256];
  
  if (*path != '/')  relpath_to_abspath (path, abspath);       // source
  else               strncpy (abspath, path, 256);
  get_dev_and_path (abspath, &device, &fs, (char*)&localpath);
  
  if (*path2 != '/') relpath_to_abspath (path2, abspath2);     // target
  else               strncpy (abspath2, path2, 256);
  splitpath (abspath2, dir2, base2);            // get dirname
  get_dev_and_path (dir2, &device2, &fs2, (char*)&localdir2);

  if (device != device2) return -1;             // error: link across volumes
  if (fs != FS_MINIX)    return -1;             // error: not Minix

  strncpy (localpath2, localdir2, 256);         // localpath2 = localdir2
  int len = strlen(localpath2); 
  if (len == 1) len = 0;  // special case "/"
  localpath2[len] = '/';                        // localpath2 += "/"
  strncpy (localpath2 + len + 1, base2, 256);   // localpath2 += base2
  // printf ("DEBUG: u_link, fs = %d, fs2 = %d, dev = %d, "    // REMOVE_DEBUGGING_CODE
  //         "dev2 = %d,\nlocalpath = %s, localpath2 = %s\n",  // REMOVE_DEBUGGING_CODE
  //         fs, fs2, device, device2, localpath, localpath2); // REMOVE_DEBUGGING_CODE
  return mx_link (device, localpath, localpath2);
}
// old line comment removed
int u_symlink (const char *path, const char *path2) {
  char localpath2[256], abspath2[256]; short device2, fs2;
  if (*path2 != '/') relpath_to_abspath (path2, abspath2);     // target
  else               strncpy (abspath2, path2, 256);
  get_dev_and_path (abspath2, &device2, &fs2, (char*)&localpath2);
  if (fs2 != FS_MINIX)  return -1;              // error: not Minix
  return mx_symlink (device2, (char*)path, localpath2);
}
// old line comment removed
int u_truncate  (const char *path, int length) {
  printf ("DEBUG: u_truncate entered\n");  // REMOVE_DEBUGGING_CODE
  int fd = u_open ((char*)path, O_WRONLY, FOLLOW_LINK);
  int retval = u_ftruncate (fd, length);
  u_close (fd);
  return retval;
}
// old line comment removed
int u_ftruncate (int fd, int length) {
  printf ("DEBUG: u_ftruncate (%d,%d) entered\n", fd, length);  // REMOVE_DEBUGGING_CODE
  
// old line comment removed
if (fd < 0) return -1;   // file not open
int fs      = fd >> 8;
int localfd = fd & 0xff;
// old line comment removed
                                                                      
  switch (fs) {
    case FS_MINIX: return mx_ftruncate (localfd, length);
    case FS_FAT:   return -1;                                  // not implemented
    case FS_DEV:   return -1;                                  // forbidden
    case FS_ERROR: return -1;                                  // error
    default:       return -1;
  }
}
// old line comment removed
boolean u_isatty (int fd) {
  return ((fd == DEV_STDIN) || (fd == DEV_STDOUT) || (fd == DEV_STDERR));
}
// old line comment removed
int u_stat (const char *path, struct stat *buf) {
  
// old line comment removed
char  localpath[256], abspath[256];
short device, fs;
// old line comment removed
  
// old line comment removed
if (*path != '/') 
  relpath_to_abspath (path, abspath);
else
  strncpy (abspath, path, 256);
get_dev_and_path (abspath, &device, &fs, (char*)&localpath);
// old line comment removed
  switch (fs) {
    case FS_MINIX: return mx_stat (device, localpath, buf);
    case FS_FAT:   return -1;  // not implemented
    case FS_DEV:   return dev_stat (localpath, buf);
    case FS_ERROR: return -1;  // error
    default:       return -1;
  }
}
// old line comment removed
int u_mkdir (const char *path, int mode) {
  
// old line comment removed
char  localpath[256], abspath[256];
short device, fs;
// old line comment removed
  
// old line comment removed
if (*path != '/') 
  relpath_to_abspath (path, abspath);
else
  strncpy (abspath, path, 256);
get_dev_and_path (abspath, &device, &fs, (char*)&localpath);
// old line comment removed
  switch (fs) {
    case FS_MINIX: return mx_mkdir (device, localpath, mode);
    case FS_FAT:   return -1;  // not implemented
    case FS_DEV:   return -1;  // not allowed
    case FS_ERROR: return -1;  // error
    default:       return -1;
  }
}

int u_rmdir (const char *path) {
  
// old line comment removed
char  localpath[256], abspath[256];
short device, fs;
// old line comment removed
  
// old line comment removed
if (*path != '/') 
  relpath_to_abspath (path, abspath);
else
  strncpy (abspath, path, 256);
get_dev_and_path (abspath, &device, &fs, (char*)&localpath);
// old line comment removed
  switch (fs) {
    case FS_MINIX: return mx_rmdir (device, abspath, localpath);  // two path args
    case FS_FAT:   return -1;  // not implemented
    case FS_DEV:   return -1;  // no rmdir_ support in device FS
    case FS_ERROR: return -1;  // error
    default:       return -1;
  }
}
// old line comment removed
int u_getdent (const char *path, int index, struct dir_entry *buf) {
  
// old line comment removed
char  localpath[256], abspath[256];
short device, fs;
// old line comment removed
  
// old line comment removed
if (*path != '/') 
  relpath_to_abspath (path, abspath);
else
  strncpy (abspath, path, 256);
get_dev_and_path (abspath, &device, &fs, (char*)&localpath);
// old line comment removed
  switch (fs) {
    case FS_MINIX: return mx_getdent (device, localpath, index, buf);
    case FS_FAT:   return -1;  // not implemented
    case FS_DEV:   return dev_getdent (localpath, index, buf);
    case FS_ERROR: return -1;  // error
    default:       return -1;
  }
}
// old line comment removed
int pfd2gfd (int pfd) {
  if (pfd == -1) return -1;  
  thread_id pid = thread_table[current_task].pid;
  if (pfd >= 0 && pfd < MAX_PFD)
    return thread_table[pid].files[pfd];
  else return -1;
}
// old line comment removed
int gfd2pfd (int gfd) {
  int pfd;
  if (gfd == -1) return -1;
  thread_id pid = thread_table[current_task].pid;
  for (pfd = 0;  pfd < MAX_PFD;  pfd++) {
    if (thread_table[pid].files[pfd] == gfd)
      return pfd;
  }
  // found none, create it
  for (pfd = 0;  pfd < MAX_PFD;  pfd++) {
    if (thread_table[pid].files[pfd] == -1) {
      thread_table[pid].files[pfd] = gfd;
      return pfd;
    }
  }
  // no free entry
  return -1;  // error
}
// old line comment removed
int u_reopen (int fd) {
  
// old line comment removed
if (fd < 0) return -1;   // file not open
int fs      = fd >> 8;
int localfd = fd & 0xff;
// old line comment removed
  switch (fs) {
    case FS_MINIX: return (fs << 8) + mx_reopen (localfd);
    case FS_FAT:   return -1;                   // not implemented
    case FS_DEV:   return -1;
    case FS_ERROR: return -1;                   // error
    default:       return -1;
  }
}
// old line comment removed
char *u_getcwd (char *buf, int size) {
  strncpy (buf, thread_table[current_task].cwd, size);
  return buf;
}

int u_chdir (const char *path) {
  char abspath[256], dir[256], base[256], localpath[256];
  if (strequal (path, "..")) {        // special case ".."
    if (strequal (thread_table[current_task].cwd, "/"))
      return 0;  // already at root directory
    // change to ..
    strncpy (abspath, thread_table[current_task].cwd, 256);
    splitpath (abspath, dir, base);
    strncpy (thread_table[current_task].cwd, dir, 256);
    return 0;
  }

  // check relative/absolute path
  if (*path != '/')  relpath_to_abspath (path, abspath);
  else               strncpy (abspath, path, 256);
  // printf ("chdir: abspath   = '%s'\n", abspath);    // REMOVE_DEBUGGING_CODE
  // get_dev_and_path (abspath, &device, &fs, (char*)&localpath);  // OLD!!    // REMOVE_DEBUGGING_CODE

  // check if abspath is directory
  struct stat st;
  u_stat (abspath, &st);
  // if (mx_file_is_directory (device, localpath)) {   // REMOVE_DEBUGGING_CODE
  if ((st.st_mode & S_IFDIR) == S_IFDIR) {
    strncpy (thread_table[current_task].cwd, abspath, 256);
    return 0;
  } else {
    return -1;  // error
  }
}
// old line comment removed
int u_readlink (char *path, char *restrict buf, size_t bufsize) {
  struct stat st;
  u_stat (path, &st);
  if ((st.st_mode & S_IFLNK) != S_IFLNK) {
    return -1;  // error: no symlink_
  }
  int link_fd = u_open (path, O_RDONLY, DONT_FOLLOW_LINK);  // open_ the link file
  u_read (link_fd, buf, bufsize);
  u_close (link_fd);
  return 0;     // success
}
// old line comment removed
int mx_query_superblock (int device, char index) {
  byte block[1024];
  struct minix_superblock *sblock;
  readblock (device, 1, (byte*)block);                    // superblock = block 1
  sblock = (struct minix_superblock*) &block;
  switch (index) {
    case MX_SB_NINODES:       return sblock->s_ninodes;
    case MX_SB_NZONES:        return sblock->s_nzones;
    case MX_SB_IMAP_BLOCKS:   return sblock->s_imap_blocks;
    case MX_SB_ZMAP_BLOCKS:   return sblock->s_zmap_blocks;
    case MX_SB_FIRSTDATAZONE: return sblock->s_firstdatazone;
    case MX_SB_LOG_ZONE_SIZE: return sblock->s_log_zone_size;
    case MX_SB_MAX_SIZE:      return sblock->s_max_size;
    case MX_SB_MAGIC:         return sblock->s_magic;
    case MX_SB_STATE:         return sblock->s_state;
    case MX_SB_ZONES:         return sblock->s_zones;
    default:                  return -1;  // error
  }
}
// old line comment removed
byte mx_get_imap_bit (int device, int i) {
  byte block[1024];
  byte thebyte;
  readblock (device, 2 + i/8192, (byte*)&block);
  thebyte = block[(i%8192)/8];
  return (thebyte >> (i%8)) % 2;
};
// old line comment removed
byte mx_get_zmap_bit (int device, int i) {
  byte block[1024];
  byte thebyte;
  unsigned int zmap_start = 2 + mx_query_superblock (device, MX_SB_IMAP_BLOCKS);
  readblock (device, zmap_start + i/8192, (byte*)&block);
  thebyte = block[(i%8192)/8];
  return (thebyte >> (i%8)) % 2;
};
// old line comment removed
void mx_set_clear_imap_bit (int device, int i, int value) {
  byte block[1024];
  byte thebyte;
  readblock (device, 2 + i/8192, (byte*)&block);
  
// old line comment removed
  thebyte = block[(i%8192)/8];
  if (value==0) {
    thebyte = thebyte & ~(1<<(i%8));            // Clear bit
  } else {
    thebyte = thebyte | 1<<(i%8);               // Set bit
  }; 
  block[(i%8192)/8] = thebyte;
// old line comment removed
  writeblock (device, 2 + i/8192, (byte*)&block);  
};

void mx_set_clear_zmap_bit (int device, int i, int value) {
  byte block[1024];
  byte thebyte;
  unsigned int zmap_start = 2 + mx_query_superblock (device, MX_SB_IMAP_BLOCKS);
  readblock (device, zmap_start + i/8192, (byte*)&block);
  
// old line comment removed
  thebyte = block[(i%8192)/8];
  if (value==0) {
    thebyte = thebyte & ~(1<<(i%8));            // Clear bit
  } else {
    thebyte = thebyte | 1<<(i%8);               // Set bit
  }; 
  block[(i%8192)/8] = thebyte;
// old line comment removed
  writeblock (device, zmap_start + i/8192, (byte*)&block);  
};
// old line comment removed
void mx_set_imap_bit (int device, int i)   { mx_set_clear_imap_bit (device, i, 1); };
void mx_clear_imap_bit (int device, int i) { mx_set_clear_imap_bit (device, i, 0); };
void mx_set_zmap_bit (int device, int i)   { mx_set_clear_zmap_bit (device, i, 1); };
void mx_clear_zmap_bit (int device, int i) { mx_set_clear_zmap_bit (device, i, 0); };
// old line comment removed
int findZeroBitAndSet (byte *block, int maxindex) {
  int i, j;
  byte b;
  for (i = 0;  i < 1024;  i++) {
    b = block[i];
    if (b != 0xFF) {
      // at least one bit in this byte is 0, find the first one
      for (j = 0;  j < 8;  j++) {
        if ( ((b >> j) % 2 == 0)       // bit is 0
             && (i*8 + j < maxindex) ) // bit position is ok
        {
          block[i] = b | (1 << j);     // set bit
          return i*8 + j;
        }
      }
    }
  }
  return -1;   // not found
}
// old line comment removed
int mx_request_inode (int device) {
  byte block[1024];
  struct minix_superblock *sblock;
  readblock (device, 1, (byte*)block);               // superblock = block 1
  sblock = (struct minix_superblock*) &block;

  int no_inodes  = sblock->s_ninodes;                // floppy: 480  
  int imap_start = 2;

  int i, index;
  for (i = 0;  i < sblock->s_imap_blocks;  i++) {    // all IMAP blocks
    readblock (device, imap_start + i, (byte*)&block);
    index = findZeroBitAndSet ((byte*)&block, no_inodes);
    if (index != -1) {                               // found one!
      writeblock (device, imap_start + i, (byte*)&block);
      return i*8192 + index;
    }
  }
  return -1;                                         // found nothing
};

int mx_request_block (int device) {
  byte block[1024];
  struct minix_superblock *sblock;
  readblock (device, 1, (byte*)block);               // superblock = block 1
  sblock = (struct minix_superblock*) &block;

  int no_zones    = sblock->s_zones;                 // floppy: 1440
  int zmap_start  = 2 + sblock->s_imap_blocks;
  int zmap_blocks = sblock->s_zmap_blocks;
  int data_start  = sblock->s_firstdatazone;
  int i, index;
  for (i = 0;  i < zmap_blocks;  i++) {              // all ZMAP blocks
    readblock (device, zmap_start + i, (byte*)&block);
    index = findZeroBitAndSet ((byte*)&block, no_zones);
    if (index != -1) {                               // found one!
      writeblock (device, zmap_start + i, (byte*)&block);
      return i*8192 + index + data_start - 1;        // convert to zone number
    }
  }
  return -1;                                         // found nothing
};
// old line comment removed
int mx_read_write_inode (int device, int i, struct minix2_inode *inodeptr, 
                         int wr_flag) {
  debug_printf ("mx_read_write_inode: entered\n"); // REMOVE_DEBUGGING_CODE
                                                   // REMOVE_DEBUGGING_CODE
  i--;         // first inode is No. 1, but has position 0 in table
  if ((i < 0) || (i >= mx_query_superblock (device, MX_SB_NINODES))) {
    return 0;  // illegal inode number
  }
  if (mx_get_imap_bit (device, i+1) == 0) {
    debug_printf ("DEBUG: mx_get_imap_bit(%d) = %d "  // REMOVE_DEBUGGING_CODE
                  "in mx_read_inode\n", i+1,          // REMOVE_DEBUGGING_CODE
                  mx_get_imap_bit (device, i));       // REMOVE_DEBUGGING_CODE
    return 0;  // attempt to read_ unused inode; forbidden
  }
  debug_printf ("mx_read_write_inode: after "      // REMOVE_DEBUGGING_CODE
                "mx_get_imap_bit()\n");            // REMOVE_DEBUGGING_CODE  
  const int inodesize      = sizeof (struct minix2_inode);
  const int inodesperblock = BLOCK_SIZE / inodesize;  
  int       blockno        = i / inodesperblock + 2 
                             + mx_query_superblock (device, MX_SB_IMAP_BLOCKS)
                             + mx_query_superblock (device, MX_SB_ZMAP_BLOCKS);
  int       blockoffset    = i % inodesperblock;  
  // we need to read_ the block, even if this is a write_ operation
  byte block[1024];
  readblock (device, blockno, (byte*)&block);
  byte *addr = (byte*)&block;      // add offset, beware of pointer arithmetic
  addr += blockoffset * inodesize;
  if (!wr_flag) {                  // read_ or write_?
    memcpy (inodeptr, addr, inodesize);
  } else {
    memcpy (addr, inodeptr, inodesize);
    writeblock (device, blockno, (byte*)&block);  // write_ whole block to disk
  };
  return (i+1);                    // return original number
};
// old line comment removed
int mx_read_inode (int device, int i, struct minix2_inode *inodeptr) {
  return mx_read_write_inode (device, i, inodeptr, 0);  // 0 = false
}
// old line comment removed
int mx_write_inode (int device, int i, struct minix2_inode *inodeptr) {
  return mx_read_write_inode (device, i, inodeptr, 1);  // 1 = true
}
// old line comment removed
int mx_read_write_dir_entry (int device, int inodenr, int entrynr, 
                             struct minix_dir_entry *entry, int wr_flag) {
  debug_printf ("mx_read_write_dir_entry: entered\n");    // REMOVE_DEBUGGING_CODE
                                                          // REMOVE_DEBUGGING_CODE
  if (entrynr >= 32 * 7) {  // 7 direct blocks, 32 entries per block
    debug_printf ("directory too big!\n");             // REMOVE_DEBUGGING_CODE
    return false;
  }
  
  struct minix2_inode inode;
  debug_printf ("mx_read_write_dir_entry: before mx_read_inode()\n"); // REMOVE_DEBUGGING_CODE
  mx_read_inode (device, inodenr, &inode);            // read_ directory inode
  debug_printf ("mx_read_write_dir_entry: after mx_read_inode()\n");  // REMOVE_DEBUGGING_CODE
  int blockno;
  blockno = inode.i_zone[entrynr/32];    // number of block that holds the entry
  if (blockno == 0) {
    if (wr_flag) { 
// old line comment removed
blockno = mx_request_block (device);
char empty_block[1024] = { 0 };
writeblock (device, blockno, (byte*)&empty_block);
inode.i_zone[entrynr/32] = blockno;
// printf ("DEBUG: entrynr = %d, entrynr/32 = %d, "          // REMOVE_DEBUGGING_CODE
//         "blockno = %d\n", entrynr, entrynr/32, blockno);  // REMOVE_DEBUGGING_CODE
// printf ("DEBUG: i_zone[] = [");                           // REMOVE_DEBUGGING_CODE
// for (int i = 0; i < 7; i++)                               // REMOVE_DEBUGGING_CODE
//   printf ("%d, ", inode.i_zone[i]);  printf ("]\n");      // REMOVE_DEBUGGING_CODE
// int ret =                                                 // REMOVE_DEBUGGING_CODE
mx_write_inode (device, inodenr, &inode);        // update directory inode
// printf ("DEBUG: updating inode %d, mx_write_inode() "     // REMOVE_DEBUGGING_CODE
//   "returns %d\n", inodenr, ret);                          // REMOVE_DEBUGGING_CODE
// old line comment removed
                                                                         } 
    else         return false;
  }
  
  char block[1024];
  readblock (device, blockno, (byte*)&block);
  
  int offset = (32*entrynr) % BLOCK_SIZE;
  if (!wr_flag) {
    memcpy (entry, ((char*)&block)+offset, 32);       // reading
    return (entry->inode != 0);                       // true if entry non-empty
  } else {
    memcpy (((byte*)&block)+offset, entry, 32);       // writing
    writeblock (device, blockno, (byte*)&block);
    return true;
  };
};

int mx_read_dir_entry (int device, int inodenr, int entrynr, 
                       struct minix_dir_entry *entry) {
  return mx_read_write_dir_entry (device, inodenr, entrynr, entry, false);
};

int mx_write_dir_entry (int device, int inodenr, int entrynr, 
                        struct minix_dir_entry *entry) {
  return mx_read_write_dir_entry (device, inodenr, entrynr, entry, true);
};
// old line comment removed
void mx_write_link (int device, int inodenr, const char *path) {
  if (mx_file_exists (device, path)) {   // check if filename already exists
      printf ("ERROR: filename %s exists!\n", path);  return;
  };
  struct minix_dir_entry dentry;  struct minix2_inode inode;
  char dirname[256];  char filename[30];
  splitpath (path, dirname, filename);
  int dir_inode_no = mx_pathname_to_ino (device, dirname);
  debug_printf ("DEBUG: dirname='%s' (ino: %d), "    // REMOVE_DEBUGGING_CODE
                "filename='%s'\n", dirname,          // REMOVE_DEBUGGING_CODE
                dir_inode_no, filename);             // REMOVE_DEBUGGING_CODE
                                                     // REMOVE_DEBUGGING_CODE
  // find free location and enter it
  mx_read_inode (device, dir_inode_no, &inode);   // read_ directory inode
  for (int i = 0;  i < 32 * 7;  i++) {
    mx_read_dir_entry (device, dir_inode_no, i, &dentry);
    if (dentry.inode==0 || i * 32 >= inode.i_size) {
      dentry.inode = inodenr;                     // found an empty entry
      memcpy ((char*)dentry.name, filename, 30);
      mx_write_dir_entry (device, dir_inode_no, i, &dentry);
      mx_increase_link_count (device, inodenr);   // link count for file
      if (inode.i_size < 32*(i+1)) {              // modify dir. inode size
        mx_read_inode (device, dir_inode_no, &inode);   // must read again
        inode.i_size = 32*(i+1);
        mx_write_inode (device, dir_inode_no, &inode);
      };
      return;                                     // success
    };
  };
  printf ("ERROR: no free entry in directory\n"); // search failed
};
// old line comment removed
int mx_increase_link_count (int device, int inodenr) {
  struct minix2_inode inode;
  mx_read_inode (device, inodenr, &inode);
  inode.i_nlinks++;
  mx_write_inode (device, inodenr, &inode);
  return inode.i_nlinks;
};
// old line comment removed
int mx_pathname_to_ino (int device, const char *path) {
  debug_printf ("mx_pathname_to_ino: entered\n");    // REMOVE_DEBUGGING_CODE
  struct minix2_inode dirinode, inode;
  struct minix_dir_entry dentry;
  char subpath[31];                         // maximum name length: 30
  char searchbuf[256];
  char *search = (char*)searchbuf;
  strncpy (search, path, 256);              // do not modify original path
  int dirinode_no = 1;                      // inode number of / directory
  int next_dirinode_no;
  short final = 0;                          // final = 1 if looking at final part
  
  search++;
  if (*search == '\0') { return 1; }        // searching for / : inode 1
  while (*search != '\0') {                 // work until end of path reached
    
// old line comment removed
int i = 0;
while (*search != '\0' && *search != '/') {
  subpath[i] = *search;
  search++; i++;
}
subpath[i] = '\0';                      // terminate subpath string

if (*search == '\0') final = 1;         // looking at final part of path

debug_printf ("DEBUG: searching for subpath "    // REMOVE_DEBUGGING_CODE
              "%s in inode %d\n", subpath,       // REMOVE_DEBUGGING_CODE
              dirinode_no);                      // REMOVE_DEBUGGING_CODE
next_dirinode_no = -1;                  // look up subpath
for (i = 0;  i < 32*7;  i++) {          // max. 32 * 7 entries
  if (dirinode_no == -1)                         // REMOVE_DEBUGGING_CODE
    printf ("FAIL: calling mx_read_dir_entry"    // REMOVE_DEBUGGING_CODE
            " (%d); i = %d, subpath = %s\n",     // REMOVE_DEBUGGING_CODE
            dirinode_no, i, subpath);            // REMOVE_DEBUGGING_CODE
                                                 // REMOVE_DEBUGGING_CODE
  mx_read_dir_entry (device, dirinode_no, i, &dentry);
  debug_printf ("mx_pathname_to_ino: "           // REMOVE_DEBUGGING_CODE
                "after mx_read_dir_entry()\n");  // REMOVE_DEBUGGING_CODE
  if (dentry.inode != 0) {
    if (strequal (dentry.name, subpath)) {
      next_dirinode_no = dentry.inode;  // found it!
      break;                            // leave for loop
    }
  }
}
    
// now next_dirinode_no is either -1 (not found) or points to next step
if (next_dirinode_no == -1) { return -1; }   // not found!
    
dirinode_no = next_dirinode_no;
debug_printf ("DEBUG: subpath = %s, "           // REMOVE_DEBUGGING_CODE
              "inode = %d\n",                   // REMOVE_DEBUGGING_CODE
              subpath, dirinode_no);            // REMOVE_DEBUGGING_CODE
if (*search != '\0')  search++;
else                  break;            // finished, leave while loop
// old line comment removed
  } 
  debug_printf ("DEBUG: returning inode no %d\n",   // REMOVE_DEBUGGING_CODE
                next_dirinode_no);                  // REMOVE_DEBUGGING_CODE
  return next_dirinode_no;
};
// old line comment removed
int mx_get_free_inodes_entry () {
  for (int i = 0;  i < MAX_INT_INODES;  i++) {      // returns internal inode no.
    if (mx_inodes[i].refcount == 0)  return i;
  }
  return -1;
}
// old line comment removed
int mx_get_free_status_entry () {
  for (int i = 0;  i < MX_MAX_FILES;  i++) {        // returns an MFD
    if (mx_status[i].int_inode == NULL)  return i;
  }
  return -1;
}
// old line comment removed
int mx_open (int device, const char *path, int oflag) {
  
// old line comment removed
debug_printf ("mx_open: entered\n");                     // REMOVE_DEBUGGING_CODE
int ext_ino = mx_pathname_to_ino (device, path);
debug_printf ("DEBUG: ext_ino = %d\n", ext_ino);         // REMOVE_DEBUGGING_CODE
debug_printf ("mx_open: after mx_pathname_to_ino()\n");  // REMOVE_DEBUGGING_CODE
if (ext_ino == -1) {
  // file not found
  if ((oflag & O_CREAT) != 0) {
    // REENABLE: printf ("DEBUG: mx_open calls mx_creat_empty_file\n");  // REMOVE_DEBUGGING_CODE
    ext_ino = mx_creat_empty_file (device, path, 0644);
  }
  else {
    return (-1);  // file not found and no O_CREAT
  }
}
// old line comment removed
short file_already_open = false;
int mfd = mx_get_free_status_entry ();

int int_ino = -1;   // number of internal inode for this file
int i;
if (count_open_files == 0) {
  int_ino = 0;      // first file to be opened
} else {
  for (i = 0; i < MAX_INT_INODES; i++) {
    if (mx_inodes[i].ino == ext_ino && mx_inodes[i].device == device) {
      // same inode number and same device: this is the same file!
      file_already_open = true;
      int_ino = i;
      break;
    }
  }
  // reached end of the loop: file is not open_
  if (int_ino == -1) int_ino = mx_get_free_inodes_entry ();
}

if (int_ino == -1) {
  return -1;      // error: no free internal inode available
}

struct int_minix2_inode *inode = &(mx_inodes[int_ino]);
// old line comment removed
mx_status[mfd].int_inode = inode;
mx_status[mfd].pos       = 0;
mx_status[mfd].mode      = oflag;

if (file_already_open) { 
// old line comment removed
inode->refcount++;       // file is opened once more
// old line comment removed
                                                                 } 
else                   { 
// old line comment removed
// copy diskinode[ext_ino] to mx_inodes[int_ino]
mx_read_inode (device, ext_ino, (struct minix2_inode*) inode);
inode->ino = ext_ino;    // number of external inode
inode->device = device;  // what device is the file on?
inode->refcount = 1;     // one user
inode->clean = true;     // inode is clean (just copied from disk)
// old line comment removed
                                                             }

if ((oflag & O_APPEND) != 0)
  mx_status[mfd].pos = inode->i_size;   // append: set pos to end of file
// old line comment removed
count_open_files++;
if (!file_already_open) count_int_inodes++;
return mfd;
// old line comment removed
}
// old line comment removed
int mx_close (int mfd) {
  // REENABLE: printf ("DEBUG: mx_close(%d)\n", mfd);  // REMOVE_DEBUGGING_CODE
  if (mfd < 0 || mfd >= MX_MAX_FILES)  return -1;   // wrong mfd number
  struct mx_filestat      *st    = &mx_status[mfd];
  struct int_minix2_inode *inode = st->int_inode;
  // printf ("DEBUG: &inode = %x\n", inode);                            // REMOVE_DEBUGGING_CODE
  if (inode == NULL)  return -1;                   // no open file
    // REENABLE: printf ("DEBUG: mx_close(%d): file not open\n", mfd);  // REMOVE_DEBUGGING_CODE
  short device = inode->device;
  
  // close file
  inode->refcount--;
  // REENABLE: printf ("DEBUG: refcount(mfd=%d,%x) is now %d\n", mfd, inode, inode->refcount); // REMOVE_DEBUGGING_CODE
  st->int_inode = NULL;
  // REENABLE: printf ("DEBUG: I have set mx_status[%d].inode = NULL !\n", mfd);  // REMOVE_DEBUGGING_CODE
  
  if (inode->refcount == 0) {  // usage count down to 0? Then synchronize inode
    if (inode->clean == 0) {
      int ext_ino = inode->ino;
      mx_write_inode (device, ext_ino, (struct minix2_inode*) inode);
    }
    count_int_inodes--;
  }
  
  count_open_files--;
  return 0;
}
// old line comment removed
int mx_reopen (int mfd) {
  if (mfd < 0 || mfd >= MX_MAX_FILES)  return -1;   // wrong mfd number
  struct mx_filestat      *st    = &mx_status[mfd];
  struct int_minix2_inode *inode = st->int_inode;
  inode->refcount++;                               // increase reference count
 
  int new_mfd = mx_get_free_status_entry ();
  memcpy (&mx_status[new_mfd], &mx_status[mfd], sizeof (struct mx_filestat));

  // printf ("DEBUG: mx_reopen(%d) = %d\n", mfd, new_mfd);   // REMOVE_DEBUGGING_CODE
  // REENABLE: printf ("DEBUG: refcount(mfd=%d,mfd2=%d,%x) is now %d\n", mfd, new_mfd, inode, inode->refcount);   // REMOVE_DEBUGGING_CODE
  return new_mfd;
}
// old line comment removed
int mx_sync (int device, int mfd) {
  if (mfd < 0 || mfd >= MX_MAX_FILES)  return -1;    // wrong mfd number
  struct mx_filestat      *st    = &mx_status[mfd];
  struct int_minix2_inode *inode = st->int_inode;
  if (inode == NULL)  return -1;                    // no open_ file
  
  if (inode->clean == 0) {
    int ext_ino = inode->ino;
    mx_write_inode (device, ext_ino, (struct minix2_inode*) inode);
    inode->clean = 1;   // now it is clean
  }
  return 0;
}
// old line comment removed
int mx_lseek (int mfd, int offset, int whence) {
  if (mfd < 0 || mfd >= MX_MAX_FILES)  return -1;      // wrong mfd number
  struct mx_filestat *st = &mx_status[mfd];
  struct int_minix2_inode *inode = st->int_inode;
  if (inode == NULL)              return -1;          // no open_ file
  if (whence < 0 || whence > 2)   return -1;          // wrong lseek_ option
  if ((st->mode & O_APPEND) != 0) return st->pos;     // append mode, ignore lseek_
  
  switch (whence) {
    case SEEK_SET: st->pos = offset;  break;          // set absolute
    case SEEK_CUR: st->pos += offset; break;          // relative to current loc.
    case SEEK_END: st->pos = inode->i_size + offset;  // relative to EOF
  };
  
  if (st->pos < 0)  st->pos = 0;                      // sanity check
  return st->pos;
}
// old line comment removed
int mx_read (int mfd, void *buf, int nbyte) {
  
// old line comment removed
debug_printf ("DEBUG: mx_read: %d bytes\n", nbyte);    // REMOVE_DEBUGGING_CODE
if (mfd < 0 || mfd >= MX_MAX_FILES)  return -1;    // wrong mfd number
  
struct mx_filestat *st = &mx_status[mfd];
struct int_minix2_inode *inode = st->int_inode;
short device = inode->device;

if (inode == NULL)  return -1;                    // no open_ file
if (st->mode == O_WRONLY || st->mode == O_APPEND)
  return -1;                                      // reading is forbbiden
// old line comment removed
int startbyte = st->pos;
if (startbyte >= inode->i_size) { return 0; }   // nothing to read_
int endbyte = st->pos + nbyte - 1;
if (endbyte >= inode->i_size) {
  nbyte -= (endbyte - inode->i_size + 1);
  endbyte = inode->i_size - 1;
}
// old line comment removed
int startblock = startbyte / BLOCK_SIZE;
int endblock   = endbyte / BLOCK_SIZE;
int curblock = startblock;
// old line comment removed
int read_bytes = 0;
while (nbyte > 0) {
  int zone = fileblocktozone (device, curblock, inode);  // where is the block?
  if (zone == -1) {
    printf ("ERROR, fileblocktozone() = -1\n");
    return -1;
  };

  byte block[BLOCK_SIZE];  readblock (device, zone, (byte*) block);
  int offset, length;
  if (curblock == startblock) {
    offset = startbyte % BLOCK_SIZE;
    length = MIN (nbyte, BLOCK_SIZE - offset);
  } else {
    offset = 0;
    length = MIN (nbyte, BLOCK_SIZE);
  }
  memcpy (buf, block+offset, length);
    
  nbyte -= length;        buf   += length;
  read_bytes += length;   curblock++;
  st->pos += length;       // update current location in inode
}

return read_bytes;         // return the read_ bytes, might be != nbyte
// old line comment removed
}
// old line comment removed
int fileblocktozone (int device, int blockno, struct int_minix2_inode *inode) {
  int zone;  int *zone_ptr;  byte indirect_block[BLOCK_SIZE];
  if (blockno < 7) {
    // the first 7 zone numbers (0..6) are in the inode:
    zone = inode->i_zone[blockno];
    debug_printf ("\nDIRECT: zone(blockno=%d) "    // REMOVE_DEBUGGING_CODE
                  "= %d\n", blockno, zone);        // REMOVE_DEBUGGING_CODE
  } else if (blockno >= 7 && blockno < 7+BLOCKADDRESSES_PER_BLOCK) {
    // inode holds the address of an indirection block
    
// old line comment removed
int indirect_zone = inode->i_zone[7];
if (indirect_zone == 0) {
  return -2;   // no indirection block found
}
debug_printf ("\nINDIRECTIONS IN: %d, ", indirect_zone);    // REMOVE_DEBUGGING_CODE
readblock (device, indirect_zone, (byte *) indirect_block);
zone_ptr = (int *) indirect_block;
zone_ptr += (blockno - 7);    
zone = *zone_ptr;
debug_printf ("INDIRECT: zone(blockno=%d) "    // REMOVE_DEBUGGING_CODE
              "= %d\n", blockno, zone);        // REMOVE_DEBUGGING_CODE
// old line comment removed
  } else {
    // inode holds the address of a double indirection block
    
// old line comment removed
int double_indirect_zone = inode->i_zone[8];
if (double_indirect_zone == 0) {
  return -2;  // no double indirection block found
}
debug_printf ("\nINDIRECTIONS IN: %d, ",       // REMOVE_DEBUGGING_CODE
              double_indirect_zone);           // REMOVE_DEBUGGING_CODE
readblock (device, double_indirect_zone, (byte *) indirect_block);
zone_ptr = (int *) indirect_block;
zone_ptr += (blockno - 7 - BLOCKADDRESSES_PER_BLOCK) / BLOCKADDRESSES_PER_BLOCK;
int indirect_zone = *zone_ptr;

readblock (device, indirect_zone, (byte *) indirect_block);
zone_ptr = (int *) indirect_block;
zone_ptr += (blockno - 7) % BLOCKADDRESSES_PER_BLOCK;    
zone = *zone_ptr;
debug_printf ("INDIRECT: zone(blockno=%d, "               // REMOVE_DEBUGGING_CODE
              "level1=%d, index=%d) = %d\n",              // REMOVE_DEBUGGING_CODE
              blockno, indirect_zone, (blockno - 7) %     // REMOVE_DEBUGGING_CODE
              BLOCKADDRESSES_PER_BLOCK, zone);            // REMOVE_DEBUGGING_CODE
// old line comment removed
  }
  return zone;
}
// old line comment removed
int mx_write (int mfd, void *buf, int nbyte) {
  
// old line comment removed
if (mfd < 0 || mfd >= MX_MAX_FILES)   return -1;  // wrong mfd number
struct mx_filestat      *st    = &mx_status[mfd];
struct int_minix2_inode *inode = st->int_inode;
short device = inode->device;
if (inode == NULL)         return -1;            // no open file
if (st->mode == O_RDONLY)  return -1;            // cannot write to read-only file
// old line comment removed
int startbyte  = st->pos;
int endbyte    = st->pos + nbyte - 1;
int startblock = startbyte / BLOCK_SIZE;
int endblock   = endbyte / BLOCK_SIZE;
int curblock   = startblock;
// old line comment removed
byte block[BLOCK_SIZE];
int offset, length;
int written_bytes = 0;
while (nbyte > 0) {
  int zone = fileblocktozone (device, curblock, inode);
  // printf ("DEBUG: mx_write, fileblocktozone (%d) = %d\n", curblock, zone);  // REMOVE_DEBUGGING_CODE
  if (zone == -2 || zone == 0) {
    zone = mx_create_new_zone (device, curblock, inode); // block doesn't yet exist
  };
  if (zone == -1)  return -1;

  if (curblock == startblock) {
    offset = startbyte % BLOCK_SIZE;
    length = MIN (nbyte, BLOCK_SIZE - offset);
    // printf ("DEBUG: WRITE, FIRST BLOCK, curblock = %d, offset = %d, length = %d\n", curblock, offset, length);  // REMOVE_DEBUGGING_CODE
  } else {
    offset = 0;
    length = MIN (nbyte, BLOCK_SIZE);
  }

  if (offset != 0 || length != BLOCK_SIZE) {
    // writing a partial block -- read_ first!
    readblock (device, zone, (byte*) block);
  }
  memcpy (block+offset, buf, length);
  writeblock (device, zone, (byte*) block);
  nbyte -= length;          buf   += length;
  written_bytes += length;  curblock++;

  st->pos += length;
  if (st->pos > inode->i_size)  inode->i_size = st->pos;  // update size
}
  
inode->i_mtime = system_time;                             // update mtime
mx_write_inode (device, inode->ino, (struct minix2_inode*) inode);
return written_bytes;
// old line comment removed
}
// old line comment removed
int mx_create_new_zone (int device, int blockno, struct int_minix2_inode *inode) {
  int zone = mx_request_block (device);  // new data block
  if (zone == -1) {
    printf ("ERROR: cannot reserve data block; disk full\n");
    return -1;
  }
  int indirect_zone, double_indirect_zone;
  int *zone_ptr;
  byte indirect_block[BLOCK_SIZE] = { 0 };
  byte double_indirect_block[BLOCK_SIZE] = { 0 };
  if (blockno < 7) {
    
// old line comment removed
// the first 7 zone numbers (0..6) are in the inode:
inode->i_zone[blockno] = zone;
debug_printf ("\nADD DIRECT: %d\n", zone);    // REMOVE_DEBUGGING_CODE
// old line comment removed
  } else if (blockno >= 7 && blockno < 7+BLOCKADDRESSES_PER_BLOCK) {
    
// old line comment removed
indirect_zone = inode->i_zone[7];

// if there is no indirection block yet, create it
if (indirect_zone == 0) {
  // no indirection block found
  indirect_zone = mx_request_block (device);  // data block for indirections
  if (indirect_zone == -1) {
    debug_printf ("cannot reserve indirection "    // REMOVE_DEBUGGING_CODE
                  "block; disk full\n");           // REMOVE_DEBUGGING_CODE
    mx_clear_zmap_bit (device, zone);         // undo reservation of data block
    return -1;
  }
  inode->i_zone[7] = indirect_zone;
} else {
  // indirection block exists: read it
  readblock (device, indirect_zone, (byte *) indirect_block);
}
debug_printf ("\nINDIRECTIONS IN: %d, ", indirect_zone);    // REMOVE_DEBUGGING_CODE

zone_ptr = (int *) indirect_block;
zone_ptr += (blockno - 7);
*zone_ptr = zone;   // write_ information about new data block
// printf ("DEBUG: writeblock, indirect_zone = %d\n", indirect_zone);  // REMOVE_DEBUGGING_CODE
writeblock (device, indirect_zone, (byte *) indirect_block);
debug_printf ("ADD INDIRECT: %d\n", zone);    // REMOVE_DEBUGGING_CODE
// old line comment removed
  } else {
    
// old line comment removed
double_indirect_zone = inode->i_zone[8];

// if there is no double indirection block yet, create it
if (double_indirect_zone == 0) {
  // no double indirection block found
  double_indirect_zone = mx_request_block (device);  // data block for 2x indir.
  if (double_indirect_zone == -1) {
    debug_printf ("cannot reserve double "              // REMOVE_DEBUGGING_CODE
                  "indirection block; disk full\n");    // REMOVE_DEBUGGING_CODE
    mx_clear_zmap_bit (device, zone);    // undo reservation of data block
    return -1;
  }
  inode->i_zone[8] = double_indirect_zone;
} else {
  // indirection block exists: read_ it
  readblock (device, double_indirect_zone, (byte *) double_indirect_block);
}

zone_ptr = (int *) double_indirect_block;
zone_ptr += (blockno - 7 - BLOCKADDRESSES_PER_BLOCK) / BLOCKADDRESSES_PER_BLOCK;
indirect_zone = *zone_ptr;

// if there is no indirection block yet, create it
if (indirect_zone == 0) {
  // no indirection block found
  indirect_zone = mx_request_block (device);  // data block for indirections
  if (indirect_zone == -1) {
    debug_printf ("cannot reserve indirection "    // REMOVE_DEBUGGING_CODE
                  "block; disk full\n");           // REMOVE_DEBUGGING_CODE
    mx_clear_zmap_bit (device, zone);   // undo reservation of data block
    return -1;
  }
  
  // write_ to first level indirection block
  *zone_ptr = indirect_zone;
  writeblock (device, double_indirect_zone, (byte *) double_indirect_block);
} else {
  // indirection block exists: read_ it
  readblock (device, indirect_zone, (byte *) indirect_block);
}

zone_ptr = (int *) indirect_block;
zone_ptr += (blockno - 7) % BLOCKADDRESSES_PER_BLOCK;

*zone_ptr = zone;   // write_ information about new data block
// printf ("DEBUG: writeblock, indirect_zone = %d\n", indirect_zone);  // REMOVE_DEBUGGING_CODE
writeblock (device, indirect_zone, (byte *) indirect_block);
debug_printf ("ADD DOUBLE INDIRECT: %d\n", zone);    // REMOVE_DEBUGGING_CODE
// old line comment removed
  }
  return zone;
}
// old line comment removed
int mx_creat_empty_file (int device, const char *path, int mode) {
  int inodenr = mx_request_inode (device);
  struct minix2_inode inode = { 0 };
  inode.i_size = 0;
  inode.i_atime = inode.i_ctime = inode.i_mtime = system_time;
  inode.i_uid = thread_table[current_task].uid;
  inode.i_gid = thread_table[current_task].gid;
  inode.i_nlinks = 0;
  inode.i_mode = S_IFREG | mode;
  mx_write_inode (device, inodenr, &inode);
  mx_write_link (device, inodenr, path);  // create directory entry
  return inodenr;
}
// old line comment removed
boolean mx_file_exists (int device, const char *path) {
  if (mx_pathname_to_ino (device, path) == -1)  return false;
  return true;
}

boolean mx_file_is_directory (int device, const char *path) {
  int ino = mx_pathname_to_ino (device, path);
  if (ino == -1)  return false;                      // does not exist
  struct minix2_inode inode;
  mx_read_inode (device, ino, &inode);
  if ((inode.i_mode & S_IFDIR) == 0)  return false;  // no directory
  return true;
}
// old line comment removed
int mx_link (int device, const char *path1, const char *path2) {
  // check path1 exists
  if (!mx_file_exists (device, path1))  return -1;  // does not exist
  
  // check path1 is not a directory
  if (mx_file_is_directory (device, path1)) {
    printf ("ln: warning: %s is a directory. This option will be removed.\n");
  }
  
  // check path2 does NOT exist
  if (mx_file_exists (device, path2)) {
    return -1;   // path2 already exists; no forced linking
  }
  
  // everything ok now
  int ino = mx_pathname_to_ino (device, path1);
  mx_write_link (device, ino, path2);   // updates link count
  return 0;
}
// old line comment removed
int mx_unlink (int device, const char *path) {
  char ind_block[BLOCK_SIZE], double_ind_block[BLOCK_SIZE];
  struct minix_dir_entry dentry;

  // check if path exists
  if (!mx_file_exists (device, path)) {
    printf ("rm: file does not exist\n");
    return -1;                             // error: path does not exist
  }
  
  // get inodes of file and directory
  int inodenr = mx_pathname_to_ino (device, path);
  struct minix2_inode inode;
  mx_read_inode (device, inodenr, &inode);
  char dir[256], base[30];
  splitpath (path, dir, base);            // split path into dir and base
  int dir_inodenr = mx_pathname_to_ino (device, dir);
  // printf ("dir_inodenr is %d\n", dir_inodenr);   // REMOVE_DEBUGGING_CODE

  // delete entry in directory
  boolean found = false;
  for (int i = 0;  i < 32*7;  i++) {
    mx_read_dir_entry (device, dir_inodenr, i, &dentry);
    if ( dentry.inode==inodenr && strequal (dentry.name, base) ) {
      dentry.inode = 0;
      memset (dentry.name, 0, 30);
      found = true;
      mx_write_dir_entry (device, dir_inodenr, i, &dentry);
      break;  // search finished
    }
  }
  if (found==false) { return -1; }  // error: not found in directory
  
  inode.i_nlinks--;   // one name less
  if (inode.i_nlinks == 0) { 
// old line comment removed
for (int i = 0;  i < 7;  i++) {
  if (inode.i_zone[i] != 0) {
    mx_clear_zmap_bit (device, inode.i_zone[i] - 33);  // mark data block as free
    inode.i_zone[i] = 0;
  }
}
// old line comment removed
if (inode.i_zone[7] != 0) {
  readblock (device, inode.i_zone[7], ind_block);
  unsigned int *zoneno;
  zoneno = (unsigned int*)ind_block;      // cast to uint*
  int count = 0;
  while (*zoneno != 0 && count < 256) {
    mx_clear_zmap_bit (device, *zoneno - 33);        // mark data block as free
    zoneno++;
    count++;
  }
  mx_clear_zmap_bit (device, inode.i_zone[7] - 33);  // mark indir. block as free
  inode.i_zone[7] = 0;
}
// old line comment removed
if (inode.i_zone[8] != 0) {
  readblock (device, inode.i_zone[8], double_ind_block);

  unsigned int *ind_zoneno;
  ind_zoneno = (unsigned int*)double_ind_block;     // cast to uint*
  
  int count1 = 0;
  int count2;
  while (*ind_zoneno != 0 && count1 < 256) {
    // printf ("re" "ad block %d\n", *ind_zoneno);   // REMOVE_DEBUGGING_CODE
    readblock (device, *ind_zoneno, ind_block);
    unsigned int *zoneno;
    zoneno = (unsigned int*)ind_block;              // cast to uint*
    count2 = 0;
    while (*zoneno != 0 && count2 < 256) {
      mx_clear_zmap_bit (device, *zoneno - 33);     // mark data block as free
      zoneno++;
      count2++;
    }
    mx_clear_zmap_bit (device, *ind_zoneno - 33);   // mark indir. block as free
    ind_zoneno++;
    count1++;
  }

  mx_clear_zmap_bit (device, inode.i_zone[8] - 33); // mark double ind. block free
  inode.i_zone[8] = 0;
}
// old line comment removed
// printf ("Freeing inode %d\n", inodenr);   // REMOVE_DEBUGGING_CODE
mx_clear_imap_bit (device, inodenr);
// old line comment removed
                                                 }
  mx_write_inode (device, inodenr, &inode);
  return 0;
}
// old line comment removed
int mx_symlink (int device, char *path1, char *path2) {
  int fd = mx_open (device, path2, O_WRONLY | O_CREAT);
  if (fd == -1)  return -1;    // error: cannot create file
  mx_write (fd, path1, strlen (path1));
  mx_close (fd);
// old line comment removed
  int inode_nr = mx_pathname_to_ino (device, path2);
  struct minix2_inode inode;
  mx_read_inode (device, inode_nr, &inode);
  inode.i_mode = S_IFLNK | 0777;
  mx_write_inode (device, inode_nr, &inode);
  return 0;  // OK.
}
// old line comment removed
int mx_ftruncate (int mfd, int length) {
  // printf ("DEBUG: mx_ftruncate entered\n");            // REMOVE_DEBUGGING_CODE
  if (mfd < 0 || mfd >= MX_MAX_FILES)  return -1;    // wrong mfd number
  struct mx_filestat      *st    = &mx_status[mfd];
  struct int_minix2_inode *inode = st->int_inode;
  if (inode == NULL)  return -1;                    // no open_ file
  short device = inode->device;
  
  if (inode->i_size <= length)  return -1;           // attempt to grow the file

  // calculate blocks to delete
  int last_kept_byte = length - 1;
  int firstblock;
  if (length == 0)  firstblock = 0;
  else              firstblock = last_kept_byte / BLOCK_SIZE + 1;
  int lastblock  = inode->i_size / BLOCK_SIZE - 1;
  
  if (lastblock >= firstblock) {    // any blocks to delete?
    for (int i = firstblock;  i <= lastblock; i++) {
      // delete block
      int zone = fileblocktozone (device, i, inode);
      printf ("DELETE ZONE %d\n", zone);               // REMOVE_DEBUGGING_CODE
      mx_clear_zmap_bit (device, zone);
    }
  }

  // check indirection blocks
  if (lastblock > 6   && inode->i_zone[7] != 0) { 
     
  }
  if (lastblock > 262 && inode->i_zone[8] != 0) {
    
  }  
  
  // reset size and write_ changed inode
  inode->i_size = length;
  inode->clean  = false;    // inode was changed
  // mx_write_inode (device, inode->ino, (struct minix2_inode*)inode); // REMOVE_DEBUGGING_CODE
  // printf ("DEBUG: mx_ftruncate finished\n");                        // REMOVE_DEBUGGING_CODE
  return 0;
}
// old line comment removed
int mx_mkdir (int device, const char *path, int mode) {
  struct minix_dir_entry entry = { 0 };
  char dir[256]; char base[256];
  int dir_inodenr, new_inodenr;
  struct minix2_inode inode;

  splitpath (path, dir, base);                     // split path into dir and base
  dir_inodenr = mx_pathname_to_ino (device, dir);

  // create new file
  int fd = mx_open (device, path, O_CREAT | O_WRONLY); mx_close (fd);
  new_inodenr = mx_pathname_to_ino (device, path);

  // enter "." and ".." inode numbers
  fd = mx_open (device, path, O_WRONLY);
  memset (&entry, 0, 32); memcpy (entry.name, ".", 2);  entry.inode = new_inodenr;
  mx_write (fd, &entry, 32);
  memset (&entry, 0, 32); memcpy (entry.name, "..", 3); entry.inode = dir_inodenr;
  mx_write (fd, &entry, 32);
  mx_close (fd);

  // fix inode (make it type directory, set nlinks to 2)
  mx_read_inode (device, new_inodenr, &inode);
  inode.i_mode = S_IFDIR | (mode & 0777);          // set mode
  inode.i_uid = thread_table[current_task].euid;   // set UID
  inode.i_gid = thread_table[current_task].egid;   // set GID
  inode.i_nlinks = 2;
  mx_write_inode (device, new_inodenr, &inode);
  
  // update link count of directory above
  mx_read_inode (device, dir_inodenr, &inode);
  inode.i_nlinks++;
  mx_write_inode (device, dir_inodenr, &inode);
  return 0;
}
// old line comment removed
int mx_rmdir (int device, const char *fullpath, const char *path) {
  struct minix_dir_entry entry;
  char abspath[256]; char dir[256]; char base[256]; char cwd[256];
  int dir_inodenr, new_inodenr;
  struct minix2_inode inode;

  // check relative/absolute path
  if (*path != '/')  relpath_to_abspath (fullpath, abspath);
  else               strncpy (abspath, fullpath, 256);
  
  // check if directory exists
  int fd = u_open ((char*)fullpath, O_RDONLY, 0);
  if (fd == -1) { return -1; }
  u_close (fd);
  
  // split path into dir and base
  splitpath (abspath, dir, base);
  
  // save current working directory
  u_getcwd ((char*)cwd, 256);
  
  if (mx_directory_is_empty (device, path)) {
    if (u_chdir (dir) == -1) { return -1; }
    if (u_unlink (".")      == -1) { u_chdir (cwd); return -1; }
    if (u_unlink ("..")     == -1) { u_chdir (cwd); return -1; }
    if (u_unlink (fullpath) == -1) { u_chdir (cwd); return -1; }
    
    u_chdir (cwd);   // restore old current working directory
    return 0;
  }
  printf ("Directory not empty\n");
  return -1;   // not empty
}
// old line comment removed
boolean mx_directory_is_empty (int device, const char *path) {
  int count = 0;  // number of entries
  struct dir_entry d = { 0 };
  for (int i = 0;  i < 32 * 7;  i++) {
    if (mx_getdent (device, path, i, &d) == 0 && d.inode != 0) count++;
  }
  return (count == 2);
}
// old line comment removed
int mx_stat (int device, const char *path, struct stat *buf) {
  struct minix2_inode inode;
  int ino = mx_pathname_to_ino (device, path);
  if (ino == -1) return -1;                              // error
  buf->st_dev   = device;            buf->st_rdev  = 0;
  buf->st_ino   = ino;
  mx_read_inode (device, ino, &inode);                   // read the inode
  buf->st_mode  = inode.i_mode;      buf->st_nlink = inode.i_nlinks;
  buf->st_uid   = inode.i_uid;       buf->st_gid   = inode.i_gid;
  buf->st_size  = inode.i_size;      buf->st_atime = inode.i_atime;
  buf->st_ctime = inode.i_ctime;     buf->st_mtime = inode.i_mtime;
  return 0;  
}
// old line comment removed
int mx_getdent (int device, const char *path, int index, struct dir_entry *buf) {
  struct minix_dir_entry d;
  struct stat s;

  int ret = mx_stat (device, path, &s);
  if (ret == -1) return -1;             // error does not exist

  if (index*32 >= s.st_size) return -1; //  index out of bounds

  int ino = mx_pathname_to_ino (device, path);
  if (ino == -1) return -1;             // error: not a directory

  ret = mx_read_dir_entry (device, ino, index, &d);
  if (ret == -1) return -1;             // error: no such entry in directory
  buf->inode = d.inode;
  strncpy ((char*)(buf->filename), d.name, 30);
  d.name[30] = 0;                       // terminate string
  return 0;                             // success
}
// old line comment removed
int count_zeros (byte *block, int maxcount) {
  int count = 0; 
  for (int i = 0;  i < (maxcount+7)/8;  i++) {
    if (block[i] == 0) { count += 8; } 
    else {
      for (int j = 0;  j < 8;  j++) {
        if (i*8 + j < maxcount && (block[i] >> j) % 2 == 0) count++;
      }
    }
  }
  return count;
}
// old line comment removed
void mx_diskfree (struct diskfree_query *query) {
  int device = query->device;
  struct minix_superblock sblock;
  char block[1024];
  query->size = mx_query_superblock (device, MX_SB_ZONES);
  unsigned int nblocks = mx_query_superblock (device, MX_SB_ZONES);
  unsigned int zmap_start = 2 + mx_query_superblock (device, MX_SB_IMAP_BLOCKS);
  unsigned int free_blocks = 0;
  for (int i = 0; i < mx_query_superblock (device, MX_SB_ZMAP_BLOCKS); i++) {
    readblock (device, zmap_start + i, (byte*)&block);
    if ((i+1)*8192 < query->size)
      free_blocks += count_zeros ((byte*)&block, 8192);
    else
      free_blocks += count_zeros ((byte*)&block, query->size - i*8192);
  }
  query->free = free_blocks;
  query->used = query->size - free_blocks;

  // find device name  
  switch (device) {
    case DEV_HDA: strncpy (query->name, "/dev/hda", 10); break;
    case DEV_HDB: strncpy (query->name, "/dev/hdb", 10); break;
    case DEV_FD0: strncpy (query->name, "/dev/fd0", 10); break;
    case DEV_FD1: strncpy (query->name, "/dev/fd1", 10); break;
    default:      strncpy (query->name, "unknown",  10); break;
  }
  
  // find mount point
  boolean mounted = false;
  for (int i=0; i<current_mounts; i++) {
    if (mount_table[i].device == device) {
      strncpy (query->fstype, fs_names[mount_table[i].fstype], 10);
      strncpy (query->mount,  mount_table[i].mountpoint, 255);
      mounted = true;
      break;
    }
  }
  if (!mounted) {
    strncpy (query->fstype, "none", 10);
    strncpy (query->mount,  "none", 10);
  }
}
// old line comment removed
int dev_open (const char *path, int oflag) {
  if ((oflag & O_CREAT) != 0)  return -1;   // cannot create
  int i, dev_inode = -1;
  
  // get the inode number
  for (i = 0;  i < 7;  i++) {
    if (strequal (path+1, dev_directory[i].name)) {
      // found!
      dev_inode = dev_directory[i].inode;  // which is always i...
      break;
    }
  }
  if (dev_inode == -1) return -1;   // not found
  
  // find free file descriptor
  int fd = -1;
  for (i = 0;  i < MAX_DEV_FILES;  i++) {
    if (dev_status[i].dev == 0) { fd = i; break; }
  }
  if (fd == -1) return -1;          // no free file descriptor  

  switch (dev_inode) {
    case DEV_FD0_INODE : dev_status[fd].dev = DEV_FD0;  break;
    case DEV_FD1_INODE : dev_status[fd].dev = DEV_FD1;  break;
    case DEV_HDA_INODE : dev_status[fd].dev = DEV_HDA;  break;
    case DEV_HDB_INODE : dev_status[fd].dev = DEV_HDB;  break;
    case DEV_KMEM_INODE: dev_status[fd].dev = DEV_KMEM; break; 
    default: dev_status[fd].dev = -1;
  }
  dev_status[fd].pos  = 0;
  dev_status[fd].mode = oflag;     
  // REENABLE: printf ("DEBUG: dev_open, dev_inode = %d, device = %d\n", dev_inode, dev_status[fd].dev);    // REMOVE_DEBUGGING_CODE
  return fd;
}
// old line comment removed
int dev_close (int fd) {
  if (fd >= 0 && fd < MAX_DEV_FILES && dev_status[fd].dev != 0) {
    dev_status[fd].dev = 0;
    return 0;  // success
  } else {
    return -1; // fail
  }
}
// old line comment removed
int dev_read (int fd, char *buf, int nbyte) {
  
// old line comment removed
if (fd < 0 || fd >= MAX_DEV_FILES)  return -1;  // bad file descriptor
if (dev_status[fd].dev == 0)       return -1;  // file not open_
// old line comment removed
  int startbyte = dev_status[fd].pos;
  int devsize = dev_size (dev_status[fd].dev);
  if (startbyte >= devsize) { return 0; }  // nothing to read_
  int endbyte = dev_status[fd].pos + nbyte - 1;
  if (endbyte >= devsize) {
    nbyte -= (endbyte - devsize + 1);  endbyte = devsize - 1;
  }

  // special case /dev/kmem: direct memcpy()
  if (dev_status[fd].dev == DEV_KMEM) {
    memcpy (buf, (char*)(PHYSICAL(startbyte)), nbyte);
    dev_status[fd].pos += nbyte;
    return nbyte;
  }

  int readbytes = 0;  int offset, length;
  int startblock = startbyte / BLOCK_SIZE;  int curblock = startblock;  
  while (nbyte > 0) {
    byte block[BLOCK_SIZE];
    readblock (dev_status[fd].dev, curblock, (byte*) block);
    if (curblock == startblock) {
      offset = startbyte % BLOCK_SIZE;  length = MIN (nbyte, BLOCK_SIZE - offset);
    } else {
      offset = 0;                       length = MIN (nbyte, BLOCK_SIZE);
    }
    memcpy (buf, block + offset, length);
    
    nbyte -= length;      buf   += length;
    readbytes += length;  curblock++;
    dev_status[fd].pos += length;
  }
  return readbytes;
}
// old line comment removed
int dev_write (int fd, char *buf, int nbyte) {
  
// old line comment removed
if (fd < 0 || fd >= MAX_DEV_FILES)  return -1;  // bad file descriptor
if (dev_status[fd].dev == 0)       return -1;  // file not open_
// old line comment removed
  int startbyte = dev_status[fd].pos;
  int devsize = dev_size (dev_status[fd].dev);
  if (startbyte >= devsize) { return 0; }  // nothing to write_
  int endbyte = dev_status[fd].pos + nbyte - 1;
  if (endbyte >= devsize) {
    nbyte -= (endbyte - devsize + 1);  endbyte = devsize - 1;
  }

  // special case /dev/kmem: direct memcpy()
  if (dev_status[fd].dev == DEV_KMEM) {
    memcpy ((char*)(PHYSICAL(startbyte)), buf, nbyte);
    dev_status[fd].pos += nbyte;
    return nbyte;
  }

  int written_bytes = 0;  int offset, length;
  int startblock = startbyte / BLOCK_SIZE;  int curblock = startblock;  
  while (nbyte > 0) {
    byte block[BLOCK_SIZE];
    if (curblock == startblock) {
      offset = startbyte % BLOCK_SIZE;  length = MIN (nbyte, BLOCK_SIZE - offset);
    } else {
      offset = 0;                       length = MIN (nbyte, BLOCK_SIZE);
    }
    
    if (offset != 0 || length != BLOCK_SIZE) {
      // writing a partial block -- read_ it first!
      readblock (dev_status[fd].dev, curblock, (byte*) block);
    }
    memcpy (block + offset, buf, length);
    writeblock (dev_status[fd].dev, curblock, (byte*) block);
    
    nbyte -= length;          buf   += length;
    written_bytes += length;  curblock++;
    dev_status[fd].pos += length;
  }
  return written_bytes;
}
// old line comment removed
int dev_lseek (int fd, int offset, int whence) {
  
// old line comment removed
if (fd < 0 || fd >= MAX_DEV_FILES)  return -1;  // bad file descriptor
if (dev_status[fd].dev == 0)       return -1;  // file not open_
// old line comment removed
  if (whence < 0 || whence > 2)
    return -1;                           // wrong lseek option
  if (whence == SEEK_END && offset > 0)
    return -1;                           // cannot seek beyond end of device
  switch (whence) {
    case SEEK_SET: dev_status[fd].pos = offset; break;
    case SEEK_CUR: dev_status[fd].pos += offset; break;
    case SEEK_END: dev_status[fd].pos = dev_size (dev_status[fd].dev) + offset;
  };
  return dev_status[fd].pos;
}
// old line comment removed
long dev_size (int dev) {
  switch (dev) {
    case DEV_FD0  : return fdd_type[fdd[0].type].total_sectors * 512;  // fd0
    case DEV_FD1  : return fdd_type[fdd[1].type].total_sectors * 512;  // fd1
    case DEV_HDA  : return hd_size[0] * 512;                           // hda
    case DEV_HDB  : return hd_size[1] * 512;                           // hdb
    case DEV_KMEM : return MEM_SIZE;                                   // kmem
    default       : return -1;                                         // error
  }
}
// old line comment removed
int dev_stat (const char *path, struct stat *buf) {
  int devices[] = { -1, 0, 0, DEV_FD0, DEV_FD1, DEV_HDA, DEV_HDB, DEV_KMEM };
  int dev_inode;

  for (int i = 0;  i < 7;  i++) {                      // get the inode number
    if (strequal (path+1, dev_directory[i].name)) {
      // found!
      dev_inode = dev_directory[i].inode;              // which is always i...
      break;
    }
  }
  if (dev_inode == -1) return -1;                      // not found

  // buf->st_dev   = 0;  // no device, /dev is a virtual FS
  buf->st_dev   = devices[dev_inode];
  buf->st_rdev  = 0;
  buf->st_ino   = dev_inode;
  if (dev_inode > 2)
    buf->st_mode  = S_IFBLK | 0600;   // block device; we have no char. devices
  else
    buf->st_mode  = S_IFDIR | 0600;   // directory
  buf->st_nlink = 1;    buf->st_uid   = 0;
  buf->st_gid   = 0;    buf->st_size  = dev_size (devices[dev_inode]);
  buf->st_atime = 0;    buf->st_ctime = 0;
  buf->st_mtime = 0;
  return 0;  
}
// old line comment removed
int dev_getdent (const char *path, int index, struct dir_entry *buf) {
  if (index < 0 || index > 6) return -1;   // no such entry

  buf->inode = dev_directory[index].inode;
  strncpy (buf->filename, dev_directory[index].name, 5);
  return 0;  
}
// old line comment removed
word makedev  (byte major, byte minor) { return ((major << 8) + minor); }
byte devmajor (word device)            { return (device >> 8); }
byte devminor (word device)            { return (device & 0xff); }
// old line comment removed
void readblock (int device, int blockno, char *buffer) {
  // check buffer
  if (buffer_read (device, blockno, buffer) == 0) { return; }

  // read_ from disk
  byte major = devmajor (device);
  byte minor = devminor (device);
  switch (major) {
    case MAJOR_HD:     readblock_hd (minor/64, blockno, buffer); break;
    case MAJOR_FD:     readblock_fd (minor,    blockno, buffer); break;
    case MAJOR_SERIAL: readblock_serial (      blockno, buffer); break;
    default: return;
  }
  
  // update buffer
  buffer_write (device, blockno, buffer, BUFFER_CLEAN);
}
// old line comment removed
void writeblock_raw (int device, int blockno, char *buffer, char flag) {
  byte major = devmajor (device);
  byte minor = devminor (device);
  switch (major) {
    case MAJOR_HD:     writeblock_hd (minor/64, blockno, buffer); break;
    case MAJOR_FD:     writeblock_fd (minor,    blockno, buffer); break;
    case MAJOR_SERIAL: writeblock_serial (      blockno, buffer); break;
    default: break;
  }
  
  // update buffer cache (if it is in the cache)
  if ( (flag == UPDATE_BUF) && (buffer_contains (device, blockno)) )
    buffer_write (device, blockno, buffer, BUFFER_CLEAN);
}
// old line comment removed
void writeblock (int device, int blockno, char *buffer) {
  buffer_write (device, blockno, buffer, BUFFER_DIRTY);
}
// old line comment removed
int buffer_read (int dev, int blockno, char *block) {
  // don't use the buffer before the scheduler_ is up
  if (!scheduler_is_active) { return -1; }  // -1 signals: must be read_ from disk
  mutex_lock (buffer_lock);
    debug_printf ("DEBUG: buffer_read (%d,%d,%x) entered\n",  // REMOVE_DEBUGGING_CODE
                  dev, blockno, block);                       // REMOVE_DEBUGGING_CODE

    // check if buffer cache holds the requested block
    int pos = -1;  // position in the cache
    for (int i = 0;  i < BUFFER_CACHE_SIZE;  i++) {
      if ((buffer_cache[i].dev == dev) && (buffer_cache[i].blockno == blockno)) {
        // found it!
        pos = i;
        debug_printf ("DEBUG: in buffer_read, found "         // REMOVE_DEBUGGING_CODE
                      "entry pos = %d\n", pos);               // REMOVE_DEBUGGING_CODE
        break;
      }
    }
    if (pos == -1) { mutex_unlock (buffer_lock); return -1; }  // not found
    
    // we found it: copy the contents, update the counter
    memcpy (block, buffer_cache[pos].buf, BLOCK_SIZE);
    if ((int)buffer_cache[pos].count < 254) { buffer_cache[pos].count++; }
  mutex_unlock (buffer_lock); return 0;    // success
}
// old line comment removed
int buffer_write (int dev, int blockno, char *block, char dirtyflag) {
  // don't use the buffer before the scheduler_ is up
  if (!scheduler_is_active) { return 0; }
  mutex_lock (buffer_lock);
    debug_printf ("DEBUG: buffer_write (%d,%d,%x) "     // REMOVE_DEBUGGING_CODE
                  "entered\n", dev, blockno, block);    // REMOVE_DEBUGGING_CODE
    // check if buffer cache already holds the requested block
    int pos = -1;              // position in the cache
    for (int i = 0;  i < BUFFER_CACHE_SIZE;  i++) {
      if ((buffer_cache[i].dev == dev) && (buffer_cache[i].blockno == blockno)) {
        pos = i; break;        // found it!
      }
    }
  
    // if not found, create it
    if (pos == -1) { 
// old line comment removed
pos = -1;  // new search
for (int i = 0;  i < BUFFER_CACHE_SIZE;  i++) {
  if (buffer_cache[i].dev == -1) {
    pos = i;  break;     // this one is free
  }
}

if (pos == -1) {         // we found no free entry
  
// old line comment removed
begin_buffer_search:              // find first clean entry
pos = -1;
for (int i = 0;  i < BUFFER_CACHE_SIZE;  i++) {
  if (buffer_cache[i].dirty == false) {
    pos = i;  break;              // end loop
  }
}
if (pos == -1) {
  buffer_sync (0);                // all buffers are dirty
  goto begin_buffer_search;
}

int least_used_val = buffer_cache[pos].count;

for (int i = pos+1;  i < BUFFER_CACHE_SIZE;  i++) {
  if (buffer_cache[i].count < least_used_val && buffer_cache[i].dirty == false) {
    // this entry is clean and was accessed less often
    least_used_val = buffer_cache[i].count;
    pos = i;  // update candidate
  }
}
// old line comment removed
}

// memset (0, buffer_cache[pos], sizeof (struct buffer_entry));  // REMOVE_DEBUGGING_CODE
buffer_cache[pos].dev = dev;
buffer_cache[pos].blockno = blockno;
buffer_cache[pos].count = 0;
// old line comment removed
                                                                               }
  
    // copy the contents, update the counter
    debug_printf ("DEBUG: in buffer_write, pos = %d, "  // REMOVE_DEBUGGING_CODE
                  "memcpy (%x,%x,%x)\n", pos,           // REMOVE_DEBUGGING_CODE
                  buffer_cache[pos].buf, block,         // REMOVE_DEBUGGING_CODE
                  BLOCK_SIZE);                          // REMOVE_DEBUGGING_CODE
    if ((pos >= 0) && (pos < BUFFER_CACHE_SIZE)) {
      memcpy (buffer_cache[pos].buf, block, BLOCK_SIZE);
      if ((int)buffer_cache[pos].count < 254)
        buffer_cache[pos].count++;
        buffer_cache[pos].dirty = dirtyflag;      
    } else {                                            // REMOVE_DEBUGGING_CODE
      debug_printf ("ERROR in buffer_write; index pos " // REMOVE_DEBUGGING_CODE
                    "= %d out of range\n", pos);        // REMOVE_DEBUGGING_CODE
    }
  mutex_unlock (buffer_lock);
  return 0;    // success
}
// old line comment removed
void buffer_sync (boolean lock_buffer) {
  _set_statusline ("[B]", 34);
  if (lock_buffer) mutex_lock (buffer_lock);
    for (int i = 0;  i < BUFFER_CACHE_SIZE;  i++) {
      if (buffer_cache[i].dirty == true) {
        writeblock_raw (buffer_cache[i].dev, buffer_cache[i].blockno, 
                        (char*)buffer_cache[i].buf, DONT_UPDATE_BUF);
        buffer_cache[i].dirty = false;
      }
    }
  if (lock_buffer) mutex_unlock (buffer_lock);
  _set_statusline ("[ ]", 34);
}
// old line comment removed
boolean buffer_contains (int dev, int blockno) {
  // don't use the buffer before the scheduler_ is up
  if (!scheduler_is_active) { return false; }
  
  // check if buffer cache holds this block
  for (int i = 0;  i < BUFFER_CACHE_SIZE;  i++) {
    if ((buffer_cache[i].dev == dev) && (buffer_cache[i].blockno == blockno)) {
      return true;  // found it!
    }
  }
  return false;
}
// old line comment removed
int serial_disk_enter (int pid, short direction, uint secno, uint address) {
  mutex_lock (serial_disk_lock);
    // check if buffer is full
    if ( (serial_disk_buffer_end+1) % SER_BUF_SIZE == serial_disk_buffer_start ) {
      mutex_unlock (serial_disk_lock);
      return -1;   // fail
    }
    struct serial_disk_buffer_entry *entry;
    entry = &serial_disk_buffer[serial_disk_buffer_end];
    entry->status = BUF_STAT_NEW;  entry->pid = pid;
    entry->direction = direction;  entry->secno = secno;
    entry->address = address;  
    short tmp = serial_disk_buffer_end;
    serial_disk_buffer_end = (serial_disk_buffer_end+1) % SER_BUF_SIZE;
  mutex_unlock (serial_disk_lock);
  return tmp;   // tell the caller what entry number we used
}
// old line comment removed
void serial_disk_send_sector_number (uint secno) {
  /* send... */  uart2putc ((byte)(secno % 256));  // lowest byte
  secno /= 256;  uart2putc ((byte)(secno % 256));  // 2nd lowest byte
  secno /= 256;  uart2putc ((byte)(secno % 256));  // 3rd lowest byte
  secno /= 256;  uart2putc ((byte)(secno % 256));  // highest byte
}
// old line comment removed
int serial_disk_non_blocking_rw () {
  mutex_lock (serial_disk_lock);
    serial_hard_disk_blocks = false;                 // we don't block
    if (serial_disk_buffer_start == serial_disk_buffer_end) {
      mutex_unlock (serial_disk_lock);  return -1;   // buffer is empty
    }  
    struct serial_disk_buffer_entry *entry;
    entry = &serial_disk_buffer[serial_disk_buffer_start];
    switch (entry->direction) {
      case BUF_WRITE: 
// old line comment removed
uart2putc (CMD_PUT);  serial_disk_send_sector_number (entry->secno);
byte *addressptr = (byte*)(entry->address);
for (int i = 0;  i < 1024;  i++) {
  uart2putc (*addressptr); addressptr++;
}
entry->status = BUF_STAT_FINISHED;
serial_disk_buffer_start++; 
serial_disk_buffer_start %= SER_BUF_SIZE;
// old line comment removed
                                                     ; break;
      case BUF_READ:  
// old line comment removed
uart2putc (CMD_GET);  serial_disk_send_sector_number (entry->secno);
serial_disk_reader = 1;                         // we're in read_ mode,
   // this value will be changed in the IRQ handler
while (serial_disk_reader == 1)  asm ("hlt");   // wait for data
entry->status = BUF_STAT_FINISHED;
serial_disk_buffer_start++;
serial_disk_buffer_start %= SER_BUF_SIZE;
// copy buffer to target memory location
memcpy ((char*)(entry->address), (char*)&(entry->sector), BLOCK_SIZE);
// old line comment removed
                                                    ;  break;
      default:        mutex_unlock (serial_disk_lock); return -1; 
    }
  mutex_unlock (serial_disk_lock);
  return 0;
}
// old line comment removed
void readblock_nb_serial (int secno, char *buf) {
  int pid; if (scheduler_is_active) pid = current_task; else pid = -1;
  serial_disk_enter (pid, BUF_READ, secno, (uint)buf);
  serial_disk_non_blocking_rw ();
}

void writeblock_nb_serial (int secno, char *buf) {
  int pid; if (scheduler_is_active) pid = current_task; else pid = -1;
  serial_disk_enter (pid, BUF_WRITE, secno, (uint)buf);
  serial_disk_non_blocking_rw ();
}
// old line comment removed
static int uart2getc () { 
  if (!uart[1]) { return -1; }
  if (!(inportb (IO_COM2+5) & 0x01)) { return -1; }
  return inportb (IO_COM2+0);
}

void serial_hard_disk_handler (context_t *r) {
  char c = uart2getc ();
  serial_hard_disk_buffer[serial_hard_disk_pos++] = c;
  if (serial_hard_disk_pos == 1024) {
    serial_hard_disk_pos = 0;
    // copy buffer to proper serial hard disk buffer
    memcpy ( &(serial_disk_buffer[serial_disk_buffer_start].sector), 
             &serial_hard_disk_buffer, 1024 );
    serial_disk_reader = 0;  // reading a sector is finished
    if (serial_hard_disk_blocks) { 
// old line comment removed
if (scheduler_is_active) {
  int tid;
  if ((tid = serial_disk_queue.next) != 0)
    deblock (tid, &serial_disk_queue); 
}
// old line comment removed
                                                                      }
  }
}
// old line comment removed
int serial_disk_blocking_rw () {
  mutex_lock (serial_disk_lock);
    serial_hard_disk_blocks = true;                  // we block
    if (serial_disk_buffer_start == serial_disk_buffer_end) {
      mutex_unlock (serial_disk_lock);  return -1;   // buffer is empty
    }  
    struct serial_disk_buffer_entry *entry;
    entry = &serial_disk_buffer[serial_disk_buffer_start];
    switch (entry->direction) {
      case BUF_WRITE: 
// old line comment removed
uart2putc (CMD_PUT);  serial_disk_send_sector_number (entry->secno);
byte *addressptr = (byte*)(entry->address);
for (int i = 0;  i < 1024;  i++) {
  uart2putc (*addressptr); addressptr++;
}
entry->status = BUF_STAT_FINISHED;
serial_disk_buffer_start++; 
serial_disk_buffer_start %= SER_BUF_SIZE;
// old line comment removed
                                                     ; break;
      case BUF_READ:  
// old line comment removed
uart2putc (CMD_GET);
// old line comment removed
// do nothing
// old line comment removed
serial_disk_send_sector_number (entry->secno);
serial_disk_reader = 1;                         // we're in read_ mode,
   // this value will be changed in the IRQ handler
while (serial_disk_reader == 1)  { 
// old line comment removed
if (scheduler_is_active) {
  // we access thread table; interrupts are off
  block (&serial_disk_queue, TSTATE_WAITSD);
  
// old line comment removed
// do nothing
// old line comment removed
  
// old line comment removed
asm (".intel_syntax noprefix; \
  mov eax, 66;; \
  int 0x80;; \
  .att_syntax; ");
// old line comment removed
} else {
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
                                                                         }  // [*]
entry->status = BUF_STAT_FINISHED;
serial_disk_buffer_start++;
serial_disk_buffer_start %= SER_BUF_SIZE;
// copy buffer to target memory location
memcpy ((char*)(entry->address), (char*)&(entry->sector), BLOCK_SIZE);
// old line comment removed
                                                              ;  break;
      default:        mutex_unlock (serial_disk_lock); return -1; 
    }
  mutex_unlock (serial_disk_lock);
  return 0;
}
// old line comment removed
void readblock_serial (int secno, char *buf) {
  int pid; if (scheduler_is_active) pid = current_task; else pid = -1;
  serial_disk_enter (pid, BUF_READ, secno, (uint)buf);
  serial_disk_blocking_rw ();
}

void writeblock_serial (int secno, char *buf) {
  int pid; if (scheduler_is_active) pid = current_task; else pid = -1;
  serial_disk_enter (pid, BUF_WRITE, secno, (uint)buf);
  serial_disk_blocking_rw ();
}
// old line comment removed
static inline void repeat_inportsl (int port, void *addr, int cnt) {
  asm volatile ("cld \n"
                "rep insl" :
                "=D" (addr), "=c" (cnt) :
                "d" (port), "0" (addr), "1" (cnt) :
                "memory", "cc");
}
// old line comment removed
static inline void repeat_outportsl (int port, void *addr, int cnt) {
  asm volatile ("cld \n"
                "rep outsl" :
                "=S" (addr), "=c" (cnt) :
                "d" (port), "0" (addr), "1" (cnt) :
                "cc");
}
// old line comment removed
void readsector_hd (int hd, int sector, char *buffer) {
  mutex_lock (hd_lock);
    hd_direction = HD_OP_READ;
    
// old line comment removed
// do nothing
// old line comment removed
    
// old line comment removed
idewait (0);
outportb (IO_IDE_DISKSEL,   0xe0 | (hd<<4));   // select disk
outportb (IO_IDE_DEVCTRL,   0);                // generate interrupt
outportb (IO_IDE_SEC_COUNT, 1);                // one sector
// old line comment removed
outportb (IO_IDE_SECTOR,     sector        & 0xff);
outportb (IO_IDE_SECTOR+1,  (sector >> 8)  & 0xff);
outportb (IO_IDE_SECTOR+2,  (sector >> 16) & 0xff);
outportb (IO_IDE_SECTOR+3, ((sector >> 24) & 0x0f) | ((0xe + hd) << 4) );
// old line comment removed
outportb (IO_IDE_COMMAND, IDE_CMD_READ);
// old line comment removed
    while (hd_direction == HD_OP_READ) { 
// old line comment removed
if (scheduler_is_active) {
  // interrupts are off; we access the thread table
  block (&harddisk_queue, TSTATE_WAITHD);
  // debug_printf ("[%d.%d] hd_sleep going "       // REMOVE_DEBUGGING_CODE
  //               "to call resign()\n",           // REMOVE_DEBUGGING_CODE
  //               current_task, system_ticks);    // REMOVE_DEBUGGING_CODE
  
// old line comment removed
// do nothing
// old line comment removed
  
// old line comment removed
asm (".intel_syntax noprefix; \
  mov eax, 66;; \
  int 0x80;; \
  .att_syntax; ");
// old line comment removed
  // debug_printf ("[%d.%d] hd_sleep returned "    // REMOVE_DEBUGGING_CODE
  //               "from resign()\n",              // REMOVE_DEBUGGING_CODE
  //               current_task, system_ticks);    // REMOVE_DEBUGGING_CODE
} else {
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
                                                                       }
    
// old line comment removed
idewait (0);
inportb (IO_IDE_STATUS);  // read_ status, ack irq
// old line comment removed
    // idewait (0);  // wait for interrupt   // REMOVE_DEBUGGING_CODE
    memcpy (buffer, hd_buf, HD_SECSIZE);
    hd_direction = HD_OP_NONE;
  mutex_unlock (hd_lock);
}
// old line comment removed
void writesector_hd (int hd, int sector, char *buffer) {
  mutex_lock (hd_lock);
    hd_direction = HD_OP_WRITE;
    memcpy (hd_buf, buffer, HD_SECSIZE);
    
// old line comment removed
// do nothing
// old line comment removed
    
// old line comment removed
idewait (0);
outportb (IO_IDE_DISKSEL,   0xe0 | (hd<<4));   // select disk
outportb (IO_IDE_DEVCTRL,   0);                // generate interrupt
outportb (IO_IDE_SEC_COUNT, 1);                // one sector
// old line comment removed
outportb (IO_IDE_SECTOR,     sector        & 0xff);
outportb (IO_IDE_SECTOR+1,  (sector >> 8)  & 0xff);
outportb (IO_IDE_SECTOR+2,  (sector >> 16) & 0xff);
outportb (IO_IDE_SECTOR+3, ((sector >> 24) & 0x0f) | ((0xe + hd) << 4) );
// old line comment removed
outportb (IO_IDE_COMMAND, IDE_CMD_WRITE);
// old line comment removed
    
// old line comment removed
inportb          (IO_IDE_STATUS);                         // read_ status, ack irq
repeat_outportsl (IO_IDE_DATA, hd_buf, HD_SECSIZE / 4);
inportb          (IO_IDE_STATUS);                         // read_ status, ack irq
// old line comment removed
    while (hd_direction == HD_OP_WRITE) { 
// old line comment removed
if (scheduler_is_active) {
  // interrupts are off; we access the thread table
  block (&harddisk_queue, TSTATE_WAITHD);
  // debug_printf ("[%d.%d] hd_sleep going "       // REMOVE_DEBUGGING_CODE
  //               "to call resign()\n",           // REMOVE_DEBUGGING_CODE
  //               current_task, system_ticks);    // REMOVE_DEBUGGING_CODE
  
// old line comment removed
// do nothing
// old line comment removed
  
// old line comment removed
asm (".intel_syntax noprefix; \
  mov eax, 66;; \
  int 0x80;; \
  .att_syntax; ");
// old line comment removed
  // debug_printf ("[%d.%d] hd_sleep returned "    // REMOVE_DEBUGGING_CODE
  //               "from resign()\n",              // REMOVE_DEBUGGING_CODE
  //               current_task, system_ticks);    // REMOVE_DEBUGGING_CODE
} else {
  
// old line comment removed
// do nothing
// old line comment removed
}
// old line comment removed
                                                                        }
    hd_direction = HD_OP_NONE;
  mutex_unlock (hd_lock);
}
// old line comment removed
void readblock_hd (int hd, int blockno, char *buffer) {
  readsector_hd (hd, blockno*2,   buffer);
  readsector_hd (hd, blockno*2+1, buffer + HD_SECSIZE);
}

void writeblock_hd (int hd, int blockno, char *buffer) {
  writesector_hd (hd, blockno*2,   buffer);
  writesector_hd (hd, blockno*2+1, buffer + HD_SECSIZE);
}
// old line comment removed
void ide_handler (context_t *r) {
  switch (hd_direction) {
    case HD_OP_READ:  repeat_inportsl (IO_IDE_DATA, hd_buf, HD_SECSIZE / 4);
                      hd_direction = HD_OP_NONE;
                      break;

    case HD_OP_WRITE: hd_direction = HD_OP_NONE;
                      break;

    case HD_OP_NONE:  printf ("Funny IDE interrupt -- no request waiting\n");
                      return; 
  }

  if (scheduler_is_active) {
    int tid;
    if ((tid = harddisk_queue.next) != 0)
      deblock (tid, &harddisk_queue);     // wake up process
    else                                          // REMOVE_DEBUGGING_CODE
      debug_printf ("WARNING: IDE HANDLER, "      // REMOVE_DEBUGGING_CODE
                    "no thread waiting\n");       // REMOVE_DEBUGGING_CODE
  }
}
// old line comment removed
int idewait (int checkerr) {
  
// old line comment removed
asm ("sti");    // set interrupt flag
// old line comment removed
  int r;
  for (;;) {
    r = inportb (IO_IDE_STATUS);
    if ((r & (IDE_BSY | IDE_DRDY)) == IDE_DRDY)  break;  // ready, not busy
  }
  if (checkerr && (r & (IDE_DF|IDE_ERR)) != 0) {
    
// old line comment removed
asm ("cli");    // clear interrupt flag
// old line comment removed
    return -1;
  } else {
    if (current_task > 1) { 
// old line comment removed
asm ("cli");    // clear interrupt flag
// old line comment removed
                                                   }  // see comment
    return 0;
  }
// OLD CODE:                                                        // REMOVE_DEBUGGING_CODE
// while (((r = inportb (IO_IDE_STATUS)) & (IDE_BSY|IDE_DRDY)) != IDE_DRDY) // REMOVE_DEBUGGING_CODE
//   printf ("=");                                                  // REMOVE_DEBUGGING_CODE
}
// old line comment removed
void ata_init () {
  // detect installed hard disks
  word buf[512]; short drivecount = 0;
  char *names[2] = { "hda", "hdb" };
  printf ("ATA: ");
  for (int disk = 0;  disk < 2;  disk++) {
    outportb (IO_IDE_DISKSEL, 0xe0 | (disk<<4));         // select disk
    for (int i = 0;  i < 1000;  i++) {
      if (inportb (IO_IDE_STATUS) != 0) {
        drivecount++;
        outportb (IO_IDE_COMMAND, IDE_CMD_IDENT);        // identify!
        repeat_inportsl (IO_IDE_DATA, buf, 256);         // 512 bytes = 256 words
        hd_size[disk] =   (ulonglong)buf[100]       + (((ulonglong)buf[101])<<16)
                      + (((ulonglong)buf[102])<<32) + (((ulonglong)buf[103])<<48);
        if (drivecount > 1) printf (", ");
        printf ("%s (%d KByte)", names[disk], 
                hd_size[disk]/2);                        // 512-byte sectors!
        break;
      }
    }
  }
  printf ("\n");
  outportb (IO_IDE_DISKSEL, 0xe0 | (0<<4));              // select disk 0
  
  // install the interrupt handler
  install_interrupt_handler (IRQ_IDE, ide_handler);
  enable_interrupt (IRQ_IDE);
}
// old line comment removed
void fdc_out (byte data) {
  for (int i = 0;  i < 10000;  i++) {
    byte status = inb_delay (IO_FLOPPY_STATUS) & (FLOPPY_MASTER | FLOPPY_DIRECTION);
    if (status != FLOPPY_MASTER) continue;
    outb_delay (IO_FLOPPY_COMMAND, data);
    return;
  }
  fdc_need_reset = true;  printf ("FDC: can't send byte %w to controller\n", data);
}
// old line comment removed
int fdc_getresults () {
  int i, results = 0;
  if (fdc_need_reset) { printf ("exit_\n"); return 0; } ;

  for (i = 0; i < 30000; i++) {
    byte status = inb_delay (IO_FLOPPY_STATUS) & FLOPPY_NEW_BYTE;
    if (status == FLOPPY_MASTER)  return true;   // results are complete
    if (status != FLOPPY_NEW_BYTE) continue;
    if (results == MAX_FLOPPY_RESULTS) break;
    fdc_results[results++] = inb_delay (IO_FLOPPY_COMMAND);
  }

  fdc_need_reset = true;  printf ("FDC: reply error\n");
  return false;
}
// old line comment removed
/**** FROM proc/i386.h *********/
void outb_delay (word __port, byte __value) {
  asm volatile ("outb %0,%1; \
                 outb %%al,$0xE0"      :
                /* no output */        :
                "a" (__value),
                "dN" (__port)           
                /* "eax","edx" */ );
}

byte inb_delay (word __port) {
  byte data;
  asm volatile ("inb %1,%0; \
                 outb %%al,$0xE0"      :
                "=a" (data)            :
                "dN" (__port)           
                /* "eax","edx" */ );
  return data;
}
// old line comment removed
int fdc_command (int cmd, int drive, int track, int sector) {
  fdc_drive  = drive;
  fdc_track  = track;
  fdc_head   = sector / current_fdd_type->sectors;
  int fdc_sector = sector % current_fdd_type->sectors + 1;

  fdc_ticks_till_motor_stops = 3 * HZ;

  
// old line comment removed
// do nothing
// old line comment removed
                                        
  // will be re-enabled in fdc_read_/write_sector
  for (int err = 0;  err < MAX_FLOPPY_ERRORS;  err++) {
    if (fdc_need_reset)  fdc_reset ();
    
// old line comment removed
if (!current_fdd->motor) {
  outb_delay (IO_FLOPPY_OUTPUT, FLOPPY_CONTROLLER_ENABLE | FLOPPY_DMAINT_ENABLE |
                                fdc_drive | (16 << fdc_drive));
  current_fdd->motor = 1;
  fdd[!fdc_drive].motor = 0;
  for (int i = 0;  i < 500000;  i++);  // delay
}
// old line comment removed
    if (!fdc_seek ())  continue;
    
// old line comment removed
int transfer_status = 0;  // will be set to 1 when successful
int sectors;              // number of transmitted sectors
// old line comment removed
// do nothing

// old line comment removed
if (!fdc_need_reset && current_fdd->motor && current_fdd->calibrated) {
  
// old line comment removed
// old version used a larger buffer array with several entries // REMOVE_DEBUGGING_CODE
// replaced with fdc_buf                                       // REMOVE_DEBUGGING_CODE
// char *address = fdc_buf                                     // REMOVE_DEBUGGING_CODE 
//               + ((fdc_head * current_fdd_type->sectors      // REMOVE_DEBUGGING_CODE
//                  + fdc_sector - 1) << 9);                   // REMOVE_DEBUGGING_CODE        
int count = 1 << (current_fdd_type->sectorsize + 7);    // = 512
int mode;
if (cmd == FLOPPY_READ) 
  mode = DMA_READ_MODE;                                 // prepare read operation
else 
  mode = DMA_WRITE_MODE;                                // prepare write operation

outb_delay (IO_DMA0_INIT,     FLOPPY_CHANNEL | 4);      // disable DMA channel
outb_delay (IO_DMA0_FLIPFLOP, 0);                       // clear DMA ch. flipflop
outb_delay (IO_DMA0_MODE,     mode | FLOPPY_CHANNEL);   // set DMA ch. mode (r/w)
// set count, address and page registers
outb_delay (IO_DMA_COUNT_2,   (byte)(count-1));         // count
outb_delay (IO_DMA_COUNT_2,   (byte)((count-1) >> 8));
outb_delay (IO_DMA_ADDR_2,    (byte)(unsigned)fdc_buf); // address,    bits  0.. 7
outb_delay (IO_DMA_ADDR_2,    (byte)((unsigned)fdc_buf >> 8));      // bits  8..15
outb_delay (IO_DMA_PAGE_2,    (unsigned)fdc_buf >> 16); // page,       bits 16..23
outb_delay (IO_DMA0_INIT,     FLOPPY_CHANNEL);          // enable DMA channel
// old line comment removed
  fdc_mode ();
  fdc_out (cmd);   fdc_out (fdc_head << 2 | fdc_drive);
  fdc_out (fdc_track); fdc_out (fdc_head); fdc_out (fdc_sector);
  fdc_out (current_fdd_type->sectorsize);      // 2: 512 bytes/sector
  fdc_out (current_fdd_type->sectors);         // end of track
  fdc_out (current_fdd_type->gap);             // gap length
  fdc_out (FLOPPY_DTL);                        // data length
// old line comment removed
  if (!fdc_need_reset && !wait_fdc_interrupt () && fdc_getresults ()) { 
    if (cmd == FLOPPY_WRITE && fdc_results[1] & WRITE_PROTECTED) {
      fdc_out (FLOPPY_SENSE);
      fdc_getresults ();
      transfer_status = -1;
    } else if ((fdc_results[0] & TEST_BITS) != TRANSFER_OK ||
        fdc_results[1] || fdc_results[2]) {
      current_fdd->calibrated = 0;
      transfer_status = 0;
    } else {
      sectors = (fdc_results[3] - fdc_track) * current_fdd_type->sectors * 2
              + (fdc_results[4] - fdc_head)  * current_fdd_type->sectors
              +  fdc_results[5] - fdc_sector;
      // printf ("DEBUG: fdc_results = [%d,%d,%d], expr = [%d,%d,%d], sectors = %d\n", fdc_results[3], fdc_results[4], fdc_results[5], fdc_results[3] - fdc_track, fdc_results[4] - fdc_head, fdc_results[5] - fdc_sector, sectors);   // REMOVE_DEBUGGING_CODE
      if (sectors == 1)  transfer_status = 1;   // success
    }
  }
}
// old line comment removed
    switch (transfer_status) {
      case -1: printf ("FDC: disk in drive %d is write protected\n", fdc_drive);
               return 0;
      case  0: continue;
      case  1: return 1;
    }
  }
  return 0;
}
// old line comment removed
void fdc_mode () {
  fdc_out (FLOPPY_SPECIFY);
  fdc_out (current_fdd_type->spec1);
  fdc_out (FLOPPY_SPEC2);
  outb_delay (IO_FLOPPY_RATE, current_fdd_type->rate & ~0x40);
}
// old line comment removed
void fdc_sleep () {
  if ((current_task > 1) && scheduler_is_active) {
    // block process
    fdc_is_busy = true;
    
// old line comment removed
// do nothing
// old line comment removed
                                          // access thread table
    block (&floppy_queue, TSTATE_WAITFLP);
    debug_printf ("fdc_sleep going to call resign()\n");    // REMOVE_DEBUGGING_CODE
    
// old line comment removed
// do nothing
// old line comment removed
    
// old line comment removed
asm (".intel_syntax noprefix; \
  mov eax, 66;; \
  int 0x80;; \
  .att_syntax; ");
// old line comment removed
  }
  fdc_is_busy = false;
};
// old line comment removed
void fdc_wakeup () {
  thread_id tid = floppy_queue.next;
  if (tid != 0)  deblock (tid, &floppy_queue);
}
// old line comment removed
void floppy_handler (context_t *r) {
  fdc_timeout = false;
  debug_printf ("FDC: interrupt\n");              // REMOVE_DEBUGGING_CODE
  if (!fdc_waits_interrupt)
    fdc_need_reset = 1;  // unexpected floppy interrupt, reset controller
  fdc_waits_interrupt = false;
  fdc_wakeup ();
}
// old line comment removed
void fdc_timer () {
  if (fdc_waits_interrupt && ++fdc_ticks > HZ * 2) {
    fdc_waits_interrupt = false;
    fdc_timeout = true;
    fdc_wakeup ();
  } else if ((fdd[0].motor | fdd[1].motor) && 
             ~(fdc_lock->l) && !--fdc_ticks_till_motor_stops) {
    
// old line comment removed
outb_delay (IO_FLOPPY_OUTPUT,
            FLOPPY_CONTROLLER_ENABLE | FLOPPY_DMAINT_ENABLE | fdc_drive);
fdd[0].motor = fdd[1].motor = 0;
// old line comment removed
  }
}
// old line comment removed
int wait_fdc_interrupt () {
  fdc_ticks = 0;                  // reset the wait time
  fdc_waits_interrupt = true;     // yes, we wait
  fdc_sleep ();
  if (fdc_timeout) {              // a timeout occurred
    fdc_need_reset = 1;
    printf ("FDC: drive %d timeout\n", fdc_drive);
  }
  return fdc_timeout;
}
// old line comment removed
int fdc_seek () {
  if (fdc_need_reset || 
      (!current_fdd->calibrated && !fdc_recalibrate ()))  return false;
  if (fdc_track == current_fdd->current_track)  return true;

  
// old line comment removed
// do nothing
// old line comment removed
  if (!current_fdd->motor)  return false;

  fdc_out (FLOPPY_SEEK);
  fdc_out (fdc_head << 2 | fdc_drive);
  fdc_out (fdc_track);
  
  if (fdc_need_reset || wait_fdc_interrupt ())  return false;

  current_fdd->current_track = fdc_track;
  fdc_out (FLOPPY_SENSE);

  if (!fdc_getresults ())  return false;
  if ((fdc_results[0] & TEST_BITS) != SEEK_OK ||
      fdc_results[1] != fdc_track * (current_fdd_type->trackstep + 1))
    return false;
  return true;
}
// old line comment removed
int fdc_read_sector (int device, int block, char *buffer) {
  // 1.4MB: 80 tracks, 18 sectors, sectorsize=2. 80x18x2=2880  // REMOVE_DEBUGGING_CODE
  
// old line comment removed
int spt;                            // sectors per track
int ctrack, csector;
int result;

mutex_lock (fdc_lock);
  current_fdd      = &fdd[device];
  current_fdd_type = &fdd_type[current_fdd->type];

  spt = current_fdd_type->sectors * 2;  // 36 ??
  ctrack   = block / spt;
  csector  = block % spt;
// old line comment removed
  result = fdc_command (FLOPPY_READ, device, ctrack, csector);  // will sleep
  if (result) {
    debug_printf ("DEBUG: fdc_read_sector: "    // REMOVE_DEBUGGING_CODE
                  "accessing FDC buffer\n");    // REMOVE_DEBUGGING_CODE
    // old version used a larger buffer array with several entries // REMOVE_DEBUGGING_CODE
    // memcpy ((void *)buffer, PHYSICAL(&fdc_buf[csector << 9]), FD_SECSIZE);  // REMOVE_DEBUGGING_CODE
    memcpy ((void *)buffer, PHYSICAL(fdc_buf), FD_SECSIZE);
  }
  
// old line comment removed
mutex_unlock (fdc_lock);
if (result) return FD_SECSIZE;
else        return 0;
// old line comment removed
}
// old line comment removed
int fdc_write_sector (int device, int block, char *buffer) {
  // 1.4MB: 80 tracks, 18 sectors, sectorsize=2. 80x18x2=2880   // REMOVE_DEBUGGING_CODE
  
// old line comment removed
int spt;                            // sectors per track
int ctrack, csector;
int result;

mutex_lock (fdc_lock);
  current_fdd      = &fdd[device];
  current_fdd_type = &fdd_type[current_fdd->type];

  spt = current_fdd_type->sectors * 2;  // 36 ??
  ctrack   = block / spt;
  csector  = block % spt;
// old line comment removed
  // memcpy (PHYSICAL(&fdc_buf[csector << 9]), (void *)buffer, FD_SECSIZE);  // REMOVE_DEBUGGING_CODE
  memcpy (PHYSICAL(fdc_buf), (void *)buffer, FD_SECSIZE);
  result = fdc_command (FLOPPY_WRITE, device, ctrack, csector);  // will sleep
  
// old line comment removed
mutex_unlock (fdc_lock);
if (result) return FD_SECSIZE;
else        return 0;
// old line comment removed
}
// old line comment removed
void readblock_fd  (int device, int blockno, char *buffer) {
  fdc_read_sector  (device, blockno*2,     buffer);
  fdc_read_sector  (device, blockno*2 + 1, buffer + FD_SECSIZE);
};

void writeblock_fd (int device, int blockno, char *buffer) {
  fdc_write_sector (device, blockno*2,     buffer);
  fdc_write_sector (device, blockno*2 + 1, buffer + FD_SECSIZE);
};
// old line comment removed
void fdc_reset () {
  // debug_printf ("DEBUG: cli, in fdc_reset\n");    // REMOVE_DEBUGGING_CODE
  
// old line comment removed
// do nothing
// old line comment removed
  outb_delay (IO_FLOPPY_OUTPUT, FLOPPY_DMAINT_ENABLE);
  for (int i = 0;  i < 10000;  i++)  asm ("nop");   // wait a bit
  outb_delay (IO_FLOPPY_OUTPUT, FLOPPY_CONTROLLER_ENABLE | FLOPPY_DMAINT_ENABLE);

  fdc_need_reset = 0;
  fdd[0].calibrated = fdd[1].calibrated = 0;
  fdd[0].motor      = fdd[1].motor      = 0;

  if (wait_fdc_interrupt ())  printf ("FDC: can't reset controller (timeout)\n");
  fdc_out (FLOPPY_SENSE);
  if (!fdc_getresults ())  printf ("FDC: can't reset controller\n");
}
// old line comment removed
int fdc_recalibrate () {
  if (fdc_need_reset)  return 0;
  //! DEBUG(1, "FDC: recalibrating drive %d...\n", fdc_drive); // REMOVE_DEBUGGING_CODE
  
// old line comment removed
// do nothing
// old line comment removed
  
// old line comment removed
if (!current_fdd->motor) {
  outb_delay (IO_FLOPPY_OUTPUT, FLOPPY_CONTROLLER_ENABLE | FLOPPY_DMAINT_ENABLE |
                                fdc_drive | (16 << fdc_drive));
  current_fdd->motor = 1;
  fdd[!fdc_drive].motor = 0;
  for (int i = 0;  i < 500000;  i++);  // delay
}
// old line comment removed
  fdc_out (FLOPPY_RECALIBRATE);
  fdc_out (fdc_drive);
  if (fdc_need_reset || wait_fdc_interrupt ())  return 0;
  fdc_out (FLOPPY_SENSE);
  if (!fdc_getresults () || (fdc_results[0] & TEST_BITS) != SEEK_OK || fdc_results[1])
    goto bad_recalibration;

  current_fdd->current_track = INVALID_TRACK;
  return current_fdd->calibrated = 1;

  bad_recalibration:
  printf ("FDC: can't recalibrate\n");
  fdc_need_reset = 1;
  return 0;
}
// old line comment removed
void fdc_init () {
  fdc_lock = get_new_lock ("fdc");                  // initialize lock

  outb_delay (IO_CMOS_CMD, 0x10);                   // read floppy status from CMOS
  int fdd_type_byte = inb_delay (IO_CMOS_DATA);

  int type; printf ("FDC: ");                       // enter and display data
  for (int i = 0;  i < 2;  i++) {
    // check floppy drive i
    if (i == 0) type = fdd_type_byte >> 4;    // upper 4 bits
    else        type = fdd_type_byte & 0x0F;  // lower 4 bits
    if ((fdd[i].present = (type == 2 || type == 4 || type == 5 )))
      fdd[i].type = fdc_map_type (type);
    printf ("fd%d (%s)%s", i, fdd_drive_name[type], (i==0) ? ", " : "\n");
  }

  if (fdd[0].present || fdd[1].present) {           // enable floppy handler
    install_interrupt_handler (IRQ_FDC, floppy_handler);
    enable_interrupt (IRQ_FDC);
    outportb (IO_FLOPPY_RATE,    0); // FDC Reset
    outportb (IO_FLOPPY_OUTPUT, 12); // enable DMA, disable Reset
  }
}
// old line comment removed
int fdc_map_type (int t) {
  switch (t) {
    case 2:  return 0;   // 1.2  MByte drive
    case 4:  return 1;   // 1.44 MByte drive
    // case 5:  return 2;   // 2.88 MByte drive   // REMOVE_DEBUGGING_CODE
    default: return -1;
  }
}
// old line comment removed
int u_kill (int pid, int signo) {
  TCB *tcb = &thread_table[pid];
  if (signo < 0 || signo > 31) { set_errno (EINVAL); return -1; }
  if (!tcb->used)              { set_errno (ESRCH);  return -1; }
  if ( (pid < 3) || (strncmp (tcb->cmdline, "login", 5) == 0) ) 
                               { set_errno (EPERM);  return -1; }
  
  if (tcb->sighandlers[signo] == SIG_DFL) {           // default action
    if (signo == SIGABRT || signo == SIGALRM  || signo == SIGBUS  ||
        signo == SIGFPE  || signo == SIGHUP   || signo == SIGILL  ||
        signo == SIGINT  || signo == SIGPIPE  || signo == SIGTERM ||
        signo == SIGUSR1 || signo == SIGUSR2  || signo == SIGPROF ||
        signo == SIGSYS  || signo == SIGTRAP  || signo == SIGVTALRM ||
        signo == SIGXCPU || signo == SIGXFSZ) {
      // default: abort, send SIGKILL
      printf ("Replacing signal %d with kill signal (9)\n", signo);
      signo = SIGKILL;    // no handler? kill it
    } else if (signo == SIGTTIN || signo == SIGTTOU || signo == SIGTSTP) {
      // default: stop, send SIGSTOP
      printf ("Replacing signal %d with kill signal (9)\n", signo);
      signo = SIGSTOP;    // no handler? kill it
    }
  }
  
  switch (signo) {  
// old line comment removed
case SIGSTOP:   
// old line comment removed
switch (tcb->state) {
  case TSTATE_READY:   remove_from_ready_queue (pid);                       break;
  case TSTATE_WAITFOR: remove_from_blocked_queue (pid, &waitpid_queue);     break;
  case TSTATE_WAITKEY: remove_from_blocked_queue (pid, &keyboard_queue);    break;
  case TSTATE_WAITFLP: remove_from_blocked_queue (pid, &floppy_queue);      break;
  case TSTATE_WAITHD:  remove_from_blocked_queue (pid, &harddisk_queue);    break;
  case TSTATE_WAITSD:  remove_from_blocked_queue (pid, &serial_disk_queue); break;
  default:             printf ("cannot remove process %d (state: %d) from blocked"
                               " queue, probably failure!\n", pid, tcb->state);
}
// old line comment removed
                tcb->state = TSTATE_STOPPED;
                if (pid == current_task) {
                  
// old line comment removed
asm (".intel_syntax noprefix; \
  mov eax, 66;; \
  int 0x80;; \
  .att_syntax; ");
// old line comment removed
                              // enter scheduler_
                }
                return 0;
// old line comment removed
case SIGCONT:   if (tcb->state == TSTATE_STOPPED) {
                  add_to_ready_queue (pid);  // sets TSTATE_READY
                }  // else ignore
                return 0;
// old line comment removed
case SIGKILL:   
// old line comment removed
switch (tcb->state) {
  case TSTATE_READY:   remove_from_ready_queue (pid);                       break;
  case TSTATE_WAITFOR: remove_from_blocked_queue (pid, &waitpid_queue);     break;
  case TSTATE_WAITKEY: remove_from_blocked_queue (pid, &keyboard_queue);    break;
  case TSTATE_WAITFLP: remove_from_blocked_queue (pid, &floppy_queue);      break;
  case TSTATE_WAITHD:  remove_from_blocked_queue (pid, &harddisk_queue);    break;
  case TSTATE_WAITSD:  remove_from_blocked_queue (pid, &serial_disk_queue); break;
  default:             printf ("cannot remove process %d (state: %d) from blocked"
                               " queue, probably failure!\n", pid, tcb->state);
}
// old line comment removed
                tcb->used = false;
                tcb->state = TSTATE_EXIT;
                
// old line comment removed
int tmp_term = thread_table[current_task].terminal;
thread_table[current_task].terminal = thread_table[pid].terminal;
printf ("\nKilled\n");
thread_table[current_task].terminal = tmp_term;
// old line comment removed
                wake_waiting_parent_process (pid);
                
// old line comment removed
scheduler_is_active = true;   _set_statusline ("SCH:ON ", 16);
// old line comment removed
                if (pid == current_task) {
                  
// old line comment removed
asm (".intel_syntax noprefix; \
  mov eax, 66;; \
  int 0x80;; \
  .att_syntax; ");
// old line comment removed
                              // enter scheduler_
                }
                return 0;
// old line comment removed
                                                   };     // cannot ignore/block
  
  if (tcb->sighandlers[signo] == SIG_IGN) return 0;   // ignore signal
  int blocked = tcb->sig_blocked & (1<<signo);
  if (!blocked && signo >= 0 && signo < 32) {
    tcb->sig_pending |= (1<<signo);                   // set the pending bit
  }
  return 0;
}
// old line comment removed
sighandler_t u_signal (int sig, sighandler_t func) {
  sighandler_t old_func;
  if (sig >= 0 && sig < 32 && 
      sig != SIGKILL && sig != SIGSTOP && sig != SIGCONT) {
    old_func = thread_table[current_task].sighandlers[sig];
    thread_table[current_task].sighandlers[sig] = func;
  } else {
    old_func = SIG_ERR;   // wrong signal number
  }
  return old_func;
}
// old line comment removed
boolean fileexists (char *abspath) {
  struct stat tmp;                        // stat info will not be used
  return (u_stat (abspath, &tmp) != -1);  // -1 means: does not exist
}
// old line comment removed
boolean check_access (char *path, word euid, word egid, word mode) {
  struct stat st; 
  int res = u_stat (path, &st);   // get file permissions
  if (res == -1 && (mode & O_CREAT) == 0) {
    set_errno (ENOENT); // file not found
    return false;
  }

  if (res == -1 && (mode & O_CREAT) != 0) {
    
// old line comment removed
char dirname[256], basename[256];
splitpath (path, dirname, basename);
res = u_stat (dirname, &st);   // get directory permissions
if (res == -1) {
  set_errno (ENOENT);          // directory not found
  return false;
}
if (euid == st.st_uid) {
  // case 1: user owns the directory
  res = (((st.st_mode >> CHECK_USER)  & 0x7) == 0x7);   // 7: rwx
} else if (egid == st.st_gid) {
  // case 2: group matches owner group
  res = (((st.st_mode >> CHECK_GROUP) & 0x7) == 0x7);
} else {
  // case 3: world access?
  res = (((st.st_mode >> CHECK_WORLD) & 0x7) == 0x7);
}
if (!res) set_errno (EACCES);
return res;
// old line comment removed
  }

  if (euid == st.st_uid) {
    // case 1: user owns the file
    res = check_perms (CHECK_USER,  mode, st.st_mode);
  } else if (egid == st.st_gid) {
    // case 2: group matches owner group
    res = check_perms (CHECK_GROUP, mode, st.st_mode);
  } else {
    // case 3: world access?
    res = check_perms (CHECK_WORLD, mode, st.st_mode);
  }
  if (!res) set_errno (EACCES);
  return res;
}
// old line comment removed
boolean check_perms (short what, word req_mode, word perms) {
  // printf ("DEBUG: check_perms (%d, 0o%o, 0o%o)\n", what, req_mode, perms);  // REMOVE_DEBUGGING_CODE
  boolean req_read  = ((req_mode & 0x3) == O_RDONLY) | ((req_mode & 0x3) == O_RDWR);
  boolean req_write = ((req_mode & 0x3) == O_WRONLY) | ((req_mode & 0x3) == O_RDWR);
  word check = (perms >> what) & 0x7;
  if (req_read  && ((check & 0x4) != 0x4)) return false;  // read_  perm. failure
  if (req_write && ((check & 0x2) != 0x2)) return false;  // write_ perm. failure
  set_errno (0);
  return true;  // both are ok
}
// old line comment removed
int u_setuid (word uid) {
  TCB *t = &thread_table[current_task];
  
// old line comment removed
// do nothing
// old line comment removed
                                        // access thread table
  if (t->uid == 0 || uid == t->uid || uid == t->euid) {
    t->uid = uid;                 // set UID
    t->euid = uid;                // and also EUID
    
// old line comment removed
// do nothing
// old line comment removed
    return 0;                     // success
  } else {
    
// old line comment removed
// do nothing
// old line comment removed
    return -1;                    // failure
  }
}

int u_setgid (word gid) {
  TCB *t = &thread_table[current_task];
  
// old line comment removed
// do nothing
// old line comment removed
                                        // access thread table
  if (t->uid == 0 || gid == t->gid || gid == t->egid) {
    t->gid = gid;                 // set GID
    t->egid = gid;                // and also EGID
    
// old line comment removed
// do nothing
// old line comment removed
    return 0;                     // success
  } else {
    
// old line comment removed
// do nothing
// old line comment removed
    return -1;                    // failure
  }
}
// old line comment removed
int u_seteuid (word uid) {
  TCB *t = &thread_table[current_task];
  
// old line comment removed
// do nothing
// old line comment removed
                                        // access thread table
  if (t->uid == 0 || uid == t->uid || uid == t->euid) {
    t->euid = uid;                // set the EUID (only!)
    
// old line comment removed
// do nothing
// old line comment removed
    return 0;                     // success
  } else {
    
// old line comment removed
// do nothing
// old line comment removed
    return -1;                    // failure
  }
}

int u_setegid (word gid) {
  TCB *t = &thread_table[current_task];
  
// old line comment removed
// do nothing
// old line comment removed
                                        // access thread table
  if (t->uid == 0 || gid == t->gid || gid == t->egid) {
    t->egid = gid;                // set the EGID (only!)
    
// old line comment removed
// do nothing
// old line comment removed
    return 0;                     // success
  } else {
    
// old line comment removed
// do nothing
// old line comment removed
    return -1;                    // failure
  }
}
// old line comment removed
int u_login (word uid, char *pass) {
  TCB *t = &thread_table[current_task];
  char passwords[BLOCK_SIZE];
  char *words[128];
  int fd = u_open ("/etc/passwd", O_RDONLY, 0);
  if (fd == -1) return -1;                        // fail: no password database
  int size = u_read (fd, &passwords, BLOCK_SIZE);
  u_close (fd);
  int pos;  int index = 0;                        // position in words array

  words[index++] = (char*)&passwords;             // split 
  for (pos = 1;  pos < size;  pos++) {
    if (passwords[pos] == ':' || passwords[pos] == '\n') {
      passwords[pos] = 0;                         // terminate string
      words[index++] = ((char*)&passwords)+pos+1;
    }
  }
 
  for (int i = 0;  i < index/5;  i++) {           // search
    if ( (atoi (words[5*i+2]) == uid)             // found right entry
          && strequal (words[5*i+1], pass) ) {    // password matches
      // printf ("DEBUG: User %s(%s) authenticated.\n", words[5*i], words[5*i+2]);  // REMOVE_DEBUGGING_CODE
      int gid = atoi (words[5*i+3]);              // get group ID
      u_chdir (words[5*i+4]);                     // make home directory the cwd
      t->uid = t->euid = t->ruid = uid;
      t->gid = t->egid = t->rgid = gid;
      return 0;                                   // success
    }
  }
  
  // printf ("DEBUG: User ID %d, Password: %s, fail!\n", uid, pass);  // REMOVE_DEBUGGING_CODE
  return -1;                                      // fail
}
// old line comment removed
int u_chown (const char *path, short owner, short group) {
  char localpath[256], abspath[256];
  short device, fs;

  // only root may change file ownership / group
  if (scheduler_is_active && thread_table[current_task].euid != 0)  return -1;   

  // check relative/absolute path
  if (*path != '/')  relpath_to_abspath (path, abspath);
  else               strncpy (abspath, path, 256);
  get_dev_and_path (abspath, &device, &fs, (char*)&localpath);
  switch (fs) {
    case FS_MINIX: return mx_chown (device, localpath, owner, group);
    case FS_FAT:   return -1;  // not possible (and FAT is not implemented)
    case FS_DEV:   return -1;  // not allowed
    case FS_ERROR: return -1;  // error
    default:       return -1;
  }
}
// old line comment removed
int u_chmod (const char *path, word mode) {
  char localpath[256], abspath[256];
  short device, fs;

  // check relative/absolute path
  if (*path != '/')  relpath_to_abspath (path, abspath);
  else               strncpy (abspath, path, 256);

  if (scheduler_is_active) {
    
// old line comment removed
// TO DO
// old line comment removed
                                         // see user/group chapter
  }
    
  get_dev_and_path (abspath, &device, &fs, (char*)&localpath);
  switch (fs) {
    case FS_MINIX: return mx_chmod (device, localpath, mode);
    case FS_FAT:   return -1;  // not possible, no FAT implementation
    case FS_DEV:   return -1;  // not allowed
    case FS_ERROR: return -1;  // error
    default:       return -1;
  }
}
// old line comment removed
int mx_chown (int device, const char *path, short owner, short group) {
  return mx_chinode (device, path, owner, group, -1);  // change UID or GID, not mode
}

int mx_chmod (int device, const char *path, word mode) {
  return mx_chinode (device, path, -1, -1, mode);      // change mode, not UID or GID
}

int mx_chinode (int device, const char *path, short owner, 
                short group, short mode) {
  int ext_ino = mx_pathname_to_ino (device, path);
  if (ext_ino == -1) {
    printf ("file not found: %s\n", path);
    return -1;   // file not found
  }
  
  struct minix2_inode inode;
  mx_read_inode (device, ext_ino, &inode);
  if (owner != -1) inode.i_uid  = owner;  // change owner (if != -1)
  if (group != -1) inode.i_gid  = group;  // change group (if != -1)
  if (mode  != -1) 
    // change mode  (if != -1)
    inode.i_mode = (inode.i_mode & ~07777) | (mode & 07777);  
  mx_write_inode (device, ext_ino, &inode);
  return 0;
}
// old line comment removed
#define putchar(c) kputch (c)

static void printchar (char **str, int c) {
  if ((int)str == -1) {
    // debug output: goes to qemu serial console via uartputc
    if (c == 0x100) {  //  backspace
      uartputc ('\b'); uartputc (' '); uartputc ('\b');
    } else {
      uartputc (c);
    }
  } else if (str) {
    **str = c; ++(*str);
  } else {
    (void)putchar (c);
  }
}
// old line comment removed
#define PAD_RIGHT 1
#define PAD_ZERO 2

static int prints (char **out, const char *string, int width, int pad) {
  register int pc = 0, padchar = ' ';
  if (width > 0) {
    register int len = 0; register const char *ptr;
    for (ptr = string; *ptr; ++ptr) ++len;
    if (len >= width) width = 0;
    else width -= len;
    if (pad & PAD_ZERO) padchar = '0';
  }
  if (!(pad & PAD_RIGHT)) {
    for ( ; width > 0; --width) { printchar (out, padchar); ++pc; }
  }
  for ( ; *string ; ++string) { printchar (out, *string); ++pc; }
  for ( ; width > 0; --width) { printchar (out, padchar); ++pc; }
  return pc;
}
// old line comment removed
#define PRINT_BUF_LEN 34

static int printi (char **out, int i, int b, int sg, int width, int pad, int letbase) {
  char print_buf[PRINT_BUF_LEN];
  register char *s; register int t, neg = 0, pc = 0; register unsigned int u = i;
  if (i == 0) {
    print_buf[0] = '0';  print_buf[1] = '\0'; 
    return prints (out, print_buf, width, pad);
  }
  if (sg && b == 10 && i < 0) { neg = 1; u = -i; }
  s = print_buf + PRINT_BUF_LEN-1;  *s = '\0';
  while (u) {
    t = u % b;        if ( t >= 10 )  t += letbase - '0' - 10;
    *--s = t + '0';   u /= b;
  }
  if (neg) {
    if ( width && (pad & PAD_ZERO) ) { printchar (out, '-'); ++pc; --width; } 
    else                             { *--s = '-'; }
  }
  return pc + prints (out, s, width, pad);
}
// old line comment removed
static int print (char **out, int *varg) {
  register int width, pad; register int pc = 0;
  register char *format = (char *)(*varg++); register char *s; char scr[2];
  for (; *format != 0; ++format) {
    if (*format == '%') {
      ++format; width = pad = 0;
      if (*format == '\0') break;
      if (*format == '%')  goto outlabel;
      if (*format == '-')  { ++format; pad = PAD_RIGHT; }
      while (*format == '0') { ++format; pad |= PAD_ZERO; }
      for ( ; *format >= '0' && *format <= '9'; ++format) {
        width *= 10;  width += *format - '0';
      }
      switch (*format) {
        case 's': s = *((char **)varg++);
                  pc += prints (out, s?s:"(null)", width, pad);         continue;
        case 'd': pc += printi (out, *varg++, 10, 1, width, pad, 'a');  continue;
        case 'o': pc += printi (out, *varg++,  8, 0, width, pad, 'a');  continue;
        case 'b': pc += printi (out, *varg++,  2, 0, width, pad, 'a');  continue;
        case 'x': pc += printi (out, *varg++, 16, 0, width, pad, 'a');  continue;
        case 'X': pc += printi (out, *varg++, 16, 0, width, pad, 'A');  continue;
        case 'u': pc += printi (out, *varg++, 10, 0, width, pad, 'a');  continue;
        case 'c': // char are converted to int then pushed on the stack
                  scr[0] = *varg++;  scr[1] = '\0';
                  pc += prints (out, scr, width, pad);                  continue;
      }      
    } else {
      outlabel:
      printchar (out, *format);  ++pc;
    }
  }
  if ( (int)out != -1 && out )  **out = '\0';
  return pc;
}
// old line comment removed
int printf (const char *format, ...) {
  register int *varg = (int *)(&format); return print (0, varg);
}

int sprintf (char *out, const char *format, ...) {
  register int *varg = (int *)(&format); return print (&out, varg);
}
// old line comment removed
#ifdef DEBUG
  int debug_printf (const char *format, ...) {
    register int *varg = (int *)(&format); return print ((char**)-1, varg);
  }
#else
  inline int debug_printf (const char *format, ...) { return 0; }  // do nothing
#endif
// old line comment removed
void ksh_command_test () {
  kputs ("current_pd as INT:              "); 
    printbitsandhex (*(uint*)(current_pd)); kputs ("\n");
  kputs ("current_pd->ptds[0].frame_addr.:"); 
    printbitsandhex (current_pd->ptds[0].frame_addr<<12); kputs ("\n");  
  kputs ("current_pt as INT:              "); 
    printbitsandhex (*(uint*)(current_pt)); kputs ("\n");
  kputs ("address of current_pd:          "); printf ("%08x\n",(uint)current_pd);
  kputs ("address of current_pt:          "); printf ("%08x\n",(uint)current_pt);
  kputs ("size of current_pd:             "); 
    printf ("%08x\n", sizeof (*current_pd));
  kputs ("size of current_pt:             "); 
    printf ("%08x\n", sizeof (*current_pt));
  kputs ("address of frame table:         "); printf ("%08x\n", (uint)ftable);
  kputs ("hexdump ftable\n");
  hexdump ((uint)&place_for_ftable, ((uint)&place_for_ftable) + 1);
};
// old line comment removed
void ksh_command_mem () {
  kputs ("kernel_pd as INT:               "); 
    printbitsandhex (*(int*)(&kernel_pd)); kputs ("\n");
  kputs ("kernel_pd.ptds[0].frame_addr:   "); 
    printbitsandhex (kernel_pd.ptds[0].frame_addr<<12); kputs ("\n");  
  kputs ("kernel_pd.ptds[768].frame_addr: "); 
    printbitsandhex (kernel_pd.ptds[768].frame_addr<<12); kputs ("\n");  
  kputs ("kernel_pd.ptds[831].frame_addr: "); 
    printbitsandhex (kernel_pd.ptds[831].frame_addr<<12); kputs ("\n");  
  kputs ("kernel_pd.ptds[832].frame_addr: "); 
    printbitsandhex (kernel_pd.ptds[832].frame_addr<<12); kputs ("\n");  
  kputs ("kernel_pd.ptds[833].frame_addr: "); 
    printbitsandhex (kernel_pd.ptds[833].frame_addr<<12); kputs ("\n");  
  kputs ("kernel_pt as INT:               "); 
    printbitsandhex (*(int*)(&kernel_pt)); kputs ("\n");
  kputs ("address of kernel_pd:           "); 
    printf ("%08x\n", (uint)&kernel_pd);
  kputs ("address of kernel_pt:           "); 
    printf ("%08x\n", (uint)&kernel_pt);
  kputs ("stack_first_address:            "); 
    printf ("%08x\n", (uint)&stack_first_address);
  kputs ("stack_last_address:             "); 
    printf ("%08x\n", (uint)&stack_last_address);
  kputs ("free_frames:                    "); printf ("%d\n", free_frames);
  uint esp; asm volatile ("mov %%esp, %0": "=r"(esp));
  kputs ("ESP:                            "); printf ("%08x\n", esp);
};
// old line comment removed
void ksh_command_time () {
  short int hour, min, sec;
    hour = (system_time/60/60)%24; min = (system_time/60)%60; sec = system_time%60;
    printf ("The time is %02d:%02d:%02d.\n", hour, min, sec);
};

void ksh_command_uname () { printf ("%s; Build: %s \n", UNAME, BUILDDATE); };
// old line comment removed
void ksh_command_div0 () {
  int zero = 0; int i = 10 / zero; kputch (i);  // Test for exception
}
// old line comment removed
void ksh_command_hexdump () {
  int as = current_as;
  activate_address_space (10);
  hexdump (0xaffffdf8, 0xaffffdf8 + 128);   // modify this to show other regions
  activate_address_space (as);
};
// old line comment removed
void ksh_command_ps () {  
  int i;
  printf (" TID  PID PPID ESP      EIP      EBP      ESP0     AS  State "
          "Exi Cmdline\n");
  for (i=0;i<MAX_THREADS; i++) {
    if (thread_table[i].used) {
      printf ("%4d %4d %4d %08x %08x %08x %08x %2d  %-5s %3d %s\n",
        thread_table[i].tid,                thread_table[i].pid,
        thread_table[i].ppid,               thread_table[i].regs.esp,
        thread_table[i].regs.eip,           thread_table[i].regs.ebp,
        thread_table[i].esp0,               thread_table[i].addr_space,
        state_names[thread_table[i].state], thread_table[i].exitcode,
        thread_table[i].cmdline);
    }
  }
}
// old line comment removed
void ksh_print_queue (char *name, blocked_queue *bq) {
  printf ("%s: ", name);
  int pid = bq->next;
  while (pid != 0) {
    printf ("%d, ", pid);
    pid = thread_table[pid].next;
  }
  printf ("\n");
}

void ksh_command_queues () {
  printf ("Queues: \n");
  printf ("ready: ");
  int pid = 0;
  while ((pid = thread_table[pid].next) != 0)  printf ("%d, ", pid);
  printf ("\n");
  ksh_print_queue ("keyboard", &keyboard_queue);
  ksh_print_queue ("harddisk", &harddisk_queue);
  ksh_print_queue ("floppy",   &floppy_queue);
  ksh_print_queue ("waitpid",  &waitpid_queue);
  ksh_print_queue ("buffer",   &(buffer_lock->bq));
}

void ksh_command_locks () {
  for (int i = 1;  i < MAX_LOCKS;  i++) {
    if (kernel_locks[i].used) {
      ksh_print_queue (kernel_locks[i].lockname, &kernel_locks[i].bq);
    }
  }
}
// old line comment removed
void ksh_command_inode () {
  struct minix2_inode in;
  int dev = DEV_HDA;
  int ino = 79;
  int res = mx_read_inode (dev, ino, &in);
  printf ("mx_read_inode(%d, %d) returns %d\n", dev, ino, res);
  if (res != 0) {
    hexdump ((uint)&in, (uint)&in+sizeof(struct minix2_inode));
    printf ("size: %d, blocks: ", in.i_size);
    for (int i = 0; i < 10; i++) printf ("%d, ", in.i_zone[i]); printf ("\n");
  }
}
// old line comment removed
void ksh_command_lsof () {
  for (int i = 0;  i < MX_MAX_FILES;  i++) {
    struct int_minix2_inode *inode = mx_status[i].int_inode;
    if (inode != NULL) {
      printf ("mfd=%d inode-addr=%08x size=%d\n", 
              i, (unsigned int)inode, inode->i_size);
    }
  }
}
// old line comment removed
void ksh_command_longhelp () {
  printf ("ex" "it         return to user mode\n"
          "te" "st\n"
          "pfault, div0 test faults\n"
          "mem          show memory (frames, pages) info\n"
          "st" "at\n"
          "uname        show Ulix version\n"
          "hex" "dump      show hex" "dump of some memory area\n"
          "clear        clear the screen\n"
          "gf, g" "p, gp1k get a frame, a page, 1000 pages\n"
          "rp           release page\n"
          "bdump\n"
          "malloc       test kernel malloc\n"
          "time         show time\n"
          "cloneas <n>  clone address space (argument: size)\n"
          "listas       show address spaces\n"
          "ps           process list\n"
          "disable      disable sche" "duler\n"
          "enable       (re-)enable sche" "duler\n"
  );          
}
// old line comment removed
void ksh_run_command (char *s) {
  if      ( strequal (s, "help") )     { printf ("Commands: %s \n", 
                                                 SHELL_COMMANDS); }
  else if ( strequal (s, "uname") )    { ksh_command_uname (); }
  else if ( strequal (s, "test") )     { ksh_command_test (); }
  else if ( strequal (s, "div0") )     { ksh_command_div0 (); }
  else if ( strequal (s, "hexdump") )  { ksh_command_hexdump (); }
  else if ( strequal (s, "clear") )    { vt_clrscr (); }
  else if ( strequal (s, "mem") )      { ksh_print_page_table (); }
  else if ( strequal (s, "mem2") )     { ksh_command_mem (); }
  else if ( strequal (s, "ps") )       { ksh_command_ps (); }
  else if ( strequal (s, "queues") )   { ksh_command_queues (); }
  else if ( strequal (s, "locks") )    { ksh_command_locks (); }
  else if ( strequal (s, "longhelp") ) { ksh_command_longhelp (); }
  else if ( strequal (s, "enable") )   { 
// old line comment removed
scheduler_is_active = true;   _set_statusline ("SCH:ON ", 16);
// old line comment removed
                                                              }
  else if ( strequal (s, "disable") )  { 
// old line comment removed
scheduler_is_active = false;  _set_statusline ("SCH:OFF", 16);
// old line comment removed
                                                               }
  else if ( strequal (s, "listas") )   { list_address_spaces (); }
  else if ( strequal (s, "time") )     { ksh_command_time (); }
  else if ( strequal (s, "lsof") )     { ksh_command_lsof (); }
  else if ( strequal (s, "inode") )    { ksh_command_inode ();    
  } else if ( strequal (s, "gf") ) {
    uint newframeid = request_new_frame ();
    printf ("New frame ID: %d\n", newframeid);
  } else if ( strequal (s, "gp") ) {
    /* uint* page = */ request_new_page ();
    // kputs (", Page @ "); printf ("%08x\n", (uint)page);
  } else if ( strequal (s, "rp") ) {
    printf ("releasing page range 0xc03fe..0xc07e6 \n");
    release_page_range (0xc03fe,0xc07e6);
  } else if ( strequal (s, "gp1k") ) {
    char buf[20]; uint *page;
    for (int i = 0;  i < 1024;  i++) {
      sprintf ((char*)&buf, "Create: %d   ", i); set_statusline ((char*)&buf);
      page = request_new_page ();
    }
  } else if ( strequal (s, "gp10k") ) {
    char buf[20]; uint *page;
    for (int i = 0;  i < 10;  i++) {
      sprintf ((char*)&buf, "Create: %d   ", i); set_statusline ((char*)&buf);
      page = request_new_pages (1024);
    }
  } 
  else if ( strequal (s, "") ) { return; } // no command
  else { printf ("Error: >%s< - no such command\n", s); }
}
// old line comment removed
void statusline_red () {
  // make status line red
  memsetw (textmemptr + 24 * 80, 0x20 | VT_RED_BACKGROUND, 80);
}

void statusline_blue () {
  // make status line blue
  memsetw (textmemptr + 24 * 80, 0x20 | VT_BLUE_BACKGROUND, 80);
  set_statusline (UNAME);
}
// old line comment removed
void kernel_shell () {
  
// old line comment removed
asm ("sti");    // set interrupt flag
// old line comment removed
  statusline_red ();
  char s[101];

  system_kbd_pos = 0;
  system_kbd_lastread = -1;
  system_kbd_count = 0;

  printf ("\nUlix Kernel Shell. Commands: %s\n", SHELL_COMMANDS);
  printf ("Type 'ex" "it' to enter user mode.\n");
  for (;;) {
    set_statusline (UNAME);
    kputs ("kernel@ulix# ");
    kreadline ((char*)&s,sizeof (s)-1);
    if ( strequal ((char*)&s, "ex" "it") ) { 
      statusline_blue ();  // restore normal color
      
// old line comment removed
scheduler_is_active = true;   _set_statusline ("SCH:ON ", 16);
// old line comment removed
      return; 
    }
    ksh_run_command ((char*)&s);
  };
};
// old line comment removed
void print_page_directory () {
  int i;
  kputs ("The Page Directory:\n");
  for ( i = 700 ; i<800 ; i++ ) {
    if ( current_pd->ptds[i].present ) {
      printf ("%04d ", i);
      printf ("%08x\n", current_pd->ptds[i].frame_addr);
    };
  };
  
  unsigned int z=(unsigned int)current_pd;
  printf ("hexdump for %08x\n", z);
  hexdump (z,z+128);
  kputch ('\n');
};
// old line comment removed
void printbitsandhex (uint i) { printf ("%032b %08X", i, i); };
// old line comment removed
void hexdump (uint startval, uint endval) {
  for (uint i=startval; i < endval; i+=16) {
    printf ("%08x  ", i);                   // address
    for (int j = i;  j < i+16;  j++) {      // hex values
      printf ("%02x ", (byte)PEEK(j));
      if (j==i+7) printf (" ");
    };
    printf (" ");
    for (int j = i;  j < i+16;  j++) {      // characters
      char z = PEEK(j);
      if ((z>=32) && (z<127)) {
        printf ("%c", PEEK(j));
      } else {
        printf (".");
      };
    };    
    printf ("\n");
  };
};
// old line comment removed
void ksh_print_page_table_helper (unsigned sta, unsigned end, unsigned used) {
  if (used) { kputs ("Used: "); } 
  else      { kputs ("Free: "); }
  printf ("%05x-%05x    %5d-%5d   (%5d frames)\n", 
          sta, end, sta, end, end-sta+1);
};
// old line comment removed
void ksh_print_page_table () {
  unsigned int cr3;
  
// old line comment removed
kputs ("Current Frame Info:\n");
// set_frame (2047*4096);  // use page 2047, TESTING   // REMOVE_DEBUGGING_CODE
unsigned int frameno = 0;
unsigned int totalfree = NUMBER_OF_FRAMES;  // total number of free frames
unsigned int test = test_frame (frameno);   // check first frame
  
for (unsigned int i = 1;  i < NUMBER_OF_FRAMES;  i++) {
  if (test_frame (i) != test) { 
    ksh_print_page_table_helper (frameno, i-1, test);
    if (test) totalfree -= (i-frameno);
    test = 1-test;
    frameno = i;
  };
};
ksh_print_page_table_helper (frameno, NUMBER_OF_FRAMES-1, test);
if (test) totalfree -= (NUMBER_OF_FRAMES-frameno);
printf ("Total free frames:    %6d\n", totalfree);
printf ("Value of free_frames: %6d\n", free_frames);
// old line comment removed
  kputch ('\n');
  
// old line comment removed
printf ("Current Paging Info: Address Space #%d\n", current_as);

boolean started=false;
int save_i=0; int save_f=0; 
unsigned int start_i=0; unsigned int start_f=0;
for (unsigned int i = 0;  i < 1024*1024;  i++) {
  frameno = mmu_p (current_as, i);  // get frameno with respect to current AS
  if (frameno == -1) {
    if (started) {                            // frame NOT found
      
// old line comment removed
printf ("PTEs 0x%05x..0x%05x -> frames 0x%05x..0x%05x  (%5d pages)\n",
  start_i, save_i, start_f, save_f, save_i-start_i+1);
// old line comment removed
      started = false;
    }
    continue;  // dont act on non-mapped pages
  } else {                                    // frame found
    if (!started) {
      start_i = i; start_f = frameno;
      save_i  = i; save_f  = frameno;
      started = true;
    } else {
      if (i-start_i != frameno-start_f) {
        // pages continue, but frames are elsewhere
        
// old line comment removed
printf ("PTEs 0x%05x..0x%05x -> frames 0x%05x..0x%05x  (%5d pages)\n",
  start_i, save_i, start_f, save_f, save_i-start_i+1);
// old line comment removed
        start_i=i; start_f=frameno;
      };

      save_i = i; save_f = frameno;
    };
  };    
};
if (started) {  
// old line comment removed
printf ("PTEs 0x%05x..0x%05x -> frames 0x%05x..0x%05x  (%5d pages)\n",
  start_i, save_i, start_f, save_f, save_i-start_i+1);
// old line comment removed
                                                }
// old line comment removed
  __asm__ __volatile__("mov %%cr3, %0": "=r"(cr3));
  printf ("cr3: %08x\n", cr3);
}
// old line comment removed
                              
// old line comment removed
void splitpath (const char *path, char *dirname, char *basename) {
  if (strlen (path) == 1 && path[0] == '/') { // special case "/"
    strncpy (dirname, "/", 1);  strncpy (basename, "/", 1);  return;
  }
  char p[256]; strncpy (p, path, 256);        // work on copy
  int pos = strlen (p) - 1;
  if (p[pos] == '/') { p[pos] = 0; pos--; }   // strip trailing '/'
  
  for (;;) {                                  // search for / (from back to front)
    pos--;
    if (pos == -1) {                          // no single slash found
      strncpy (dirname, ".", 2);  strncpy (basename, p, 256);  return;
    }
    if (p[pos] == '/') {                      // slash found
      if (pos==0)
        strncpy (dirname, "/", 2);            // special case /
      else {
        memcpy (dirname, p, pos);
        dirname[pos] = 0;                     // remove trailing '/'
      }
      strncpy (basename, p + pos + 1, 30);
      return;
    }
  }
}
// old line comment removed
char *basename (char *path) {
  static char bname[30];  static char dname[256];
  splitpath (path, dname, bname);  return (char *)bname;
}

char *dirname (char *path) {
  static char bname[30];  static char dname[256];
  splitpath (path, dname, bname);  return (char *)dname;
}
// old line comment removed
size_t strlen (const char *str) {
    size_t retval;
    for (retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

int strcmp (const char *s1, const char *s2) {
  // source: http://en.wikibooks.org/wiki/C_Programming/Strings
  while (*s1 != '\0' && *s1 == *s2) {
    s1++;  s2++;
  }
  byte b1 = (*(byte *) s1);
  byte b2 = (*(byte *) s2);
  return ((b1 < b2) ? -1 : (b1 > b2));
}

int strncmp (const char *s1, const char *s2, uint n) {
  // source: http://en.wikibooks.org/wiki/C_Programming/Strings
  if (n == 0) { return 0; }                   // nothing to compare? return 0
  while (n-- > 0 && *s1 == *s2) {
    if (n == 0 || *s1 == '\0') { return 0; }  // equality
    s1++;  s2++;
  }
  byte b1 = (*(byte *) s1); 
  byte b2 = (*(byte *) s2);
  return ((b1 < b2) ? -1 : (b1 > b2));
}
// old line comment removed
char *strcpy (char *dest, const char *src) {
  char *ret = dest;
  while ((*dest++ = *src++) != '\0') ;
  return ret;
}

char *strncpy (char *dest, const char *src, size_t count) {
  // like memcpy_ (see next section), but copies only until first \0 character
  const char *sp = (const char *)src;
  char *dp = (char *)dest;
  for (; count != 0; count--) {
    *dp = *sp;
    if (*dp == 0) break;
    dp++; sp++;
  }
  return dest;
}
// old line comment removed
int atoi (char *s) {
  int res = 0;
  while ( ('0' <= *s) && (*s <= '9') ) {
    res = res*10 + (*s-'0');
    s++;
  }
  return res;
};

int atoi8 (char *s) {   // same as atoi, but with octal numbers
  int res = 0;
  while ( ('0' <= *s) && (*s <= '7') ) {
    res = res*8 + (*s-'0');
    s++;
  }
  return res;
};
// old line comment removed
void *memcpy (void *dest, const void *src, size_t count) {
  // debug_printf ("DEBUG: memcpy (%x,%x,%x)\n", dest, src, count);    // REMOVE_DEBUGGING_CODE
  const char *sp = (const char *)src;
  char *dp = (char *)dest;
  for (; count != 0; count--) 
    *dp++ = *sp++;
  return dest;
}

void *memset (void *dest, char val, size_t count) {
  char *temp = (char *)dest;
  for ( ; count != 0; count--) *temp++ = val;
  return dest;
}

word *memsetw (word *dest, word val, size_t count) {
  word *temp = (word *)dest;
  for ( ; count != 0; count--) *temp++ = val;
  return dest;
}
// old line comment removed
void main () {
  
// old line comment removed
thread_table[0].prev = 0;
thread_table[0].next = 0;
// old line comment removed
paging_lock = get_new_lock ("paging");
// old line comment removed
swapper_lock = get_new_lock ("swapper");
// old line comment removed
for (int i = 0;  i < MAX_SEMAPHORES;  i++) {
  kl_semaphore_table[i].counter = 0;
  initialize_blocked_queue (&kl_semaphore_table[i].bq);
  kl_semaphore_table[i].used = false;
}
// old line comment removed
serial_disk_lock = get_new_lock ("serial disk");
// old line comment removed
  
// old line comment removed
uartinit (1);
// old line comment removed
                         // for debugging
  
// old line comment removed
// file page directory with null entries
for (int i = 0;  i < 1024;  i++) {
  fill_page_table_desc (&(current_pd->ptds[i]), false, false, false, 0);
};

// make page table kernel_pt      the first entry of page directory kernel_pd
// maps: 0x00000000..0x003FFFFF -> 0x00000000..0x003FFFFF  (4 MB)
KMAPD ( &(current_pd->ptds[  0]), (memaddress)(current_pt)-0xC0000000 );

// make page table kernel_pt also the 768th entry of page directory kernel_pd
// maps: 0xC0000000..0xC03FFFFF -> 0x00000000..0x003FFFFF  (4 MB)
KMAPD ( &(current_pd->ptds[768]), (memaddress)(current_pt)-0xC0000000 );

// map 1023 pages (4 MB minus 1 page)
for (int i = 0;  i < 1023;  i++) {
  
// old line comment removed
KMAP ( &(current_pt->pds[i]), i*4096 );
// old line comment removed
};

kputs ("Kernel page directory set up.\n");
// old line comment removed
kernel_pd_address = (char*)(current_pd) - 0xC0000000;
asm volatile ("mov %0, %%cr3" : : "r"(kernel_pd_address) ); // write_ CR3
uint cr0; asm volatile ("mov %%cr0, %0" : "=r"(cr0) : );    // read_  CR0
cr0 |= (1<<31);             // Enable paging_ by setting PG bit 31 of CR0
asm volatile ("mov %0, %%cr0" : : "r"(cr0) );               // write_ CR0
// old line comment removed
address_spaces[0].status   = AS_USED;
address_spaces[0].pd       = &kernel_pd;
address_spaces[0].pid      = -1;         // not a process
// old line comment removed
// We'll have six GDT entries; only three are defined now
gp.limit = (sizeof (struct gdt_entry) * 6) - 1;  // must be -1
gp.base = (int) &gdt;

fill_gdt_entry (0, 0, 0, 0, 0);    // null descriptor

// code segment: base = 0, limit = 0xFFFFF
fill_gdt_entry (1, 0, 0xFFFFF, 0b10011010, 0b1100);

// data segment: base = 0, limit = 0xFFFFF
fill_gdt_entry (2, 0, 0xFFFFF, 0b10010010, 0b1100);

// old line comment removed
fill_gdt_entry (3, 0, 0xFFFFFFFF, 0b11111010, 0b1100);
fill_gdt_entry (4, 0, 0xFFFFFFFF, 0b11110010, 0b1100);
// old line comment removed
write_tss (5, 0x10, (void*)TOP_OF_KERNEL_MODE_STACK);   // gdt no., ss0, esp0
// old line comment removed
                                // explained later
gdt_flush ();   // Notify the CPU of changes
tss_flush ();   // explained later
// old line comment removed
  
// old line comment removed
vt_clrscr ();
set_statusline (UNAME);
printf ("%s                           Build: %s\n", UNAME, BUILDDATE); 
// old line comment removed
  
// old line comment removed
system_kbd_pos = 0;
system_kbd_lastread = -1;
system_kbd_count = 0;
for (int i = 0;  i < 10;  i++) 
  terminals[i].kbd_lastread = -1;
// old line comment removed
  
// old line comment removed
idtp.limit = (sizeof (struct idt_entry) * 256) - 1;   // must do -1
idtp.base  = (int) &idt;
idt_load ();
// old line comment removed
for (int i = 0; i < 32; i++) {
  fill_idt_entry (i,
                  (unsigned int)faults[i],
                  0x08,
                  0b1110,   // flags: 1 (present), 11 (DPL 3), 0
                  0b1110);  // type: 1110 (32 bit interrupt gate)
}
// old line comment removed
fill_idt_entry (128, 
                (unsigned int)syscallh, 
                0x08, 
                0b1110,   // flags: 1 (present), 11 (DPL 3), 0
                0b1110);  // type: 1110 (32 bit interrupt gate)
// old line comment removed
outportb (IO_PIC_MASTER_CMD,  0x11);  // ICW1: initialize; begin programming
outportb (IO_PIC_SLAVE_CMD,   0x11);  // ICW1: dito, for PIC2
// old line comment removed
outportb (IO_PIC_MASTER_DATA, 0x20);  // ICW2 for PIC1: offset 0x20 
                                      // (remaps 0x00..0x07 -> 0x20..0x27)
outportb (IO_PIC_SLAVE_DATA,  0x28);  // ICW2 for PIC2: offset 0x28 
                                      // (remaps 0x08..0x0f -> 0x28..0x2f)
// old line comment removed
outportb (IO_PIC_MASTER_DATA, 0x04);  // ICW3 for PIC1: there's a slave on IRQ 2 
                                      // (0b00000100 = 0x04)
outportb (IO_PIC_SLAVE_DATA,  0x02);  // ICW3 for PIC2: your slave ID is 2
// old line comment removed
outportb (IO_PIC_MASTER_DATA, 0x01);  // ICW4 for PIC1 and PIC2: 8086 mode
outportb (IO_PIC_SLAVE_DATA,  0x01);
// old line comment removed
set_irqmask (0xFFFF);           // initialize IRQ mask
enable_interrupt (IRQ_SLAVE);   // IRQ slave

for (int i = 0;  i < 16;  i++) {
  fill_idt_entry (32 + i, 
                  (unsigned int)irqs[i],  
                  0x08, 
                  0b1110,     // flags: 1 (present), 11 (DPL 3), 0
                  0b1110);    // type:  1110 (32 bit interrupt gate)
}
// old line comment removed
keyboard_install ();
// old line comment removed
timer_phase (100);   // set timer to 100 Hz (100 interrupts/second)
install_interrupt_handler (IRQ_TIMER, timer_handler);
enable_interrupt (IRQ_TIMER);
// old line comment removed
// code adapted from http://wiki.osdev.org/CMOS
outportb (IO_CMOS_CMD,    0); byte second =  inportb (IO_CMOS_DATA);
outportb (IO_CMOS_CMD,    2); byte minute =  inportb (IO_CMOS_DATA);
outportb (IO_CMOS_CMD,    4); byte hour =    inportb (IO_CMOS_DATA);
outportb (IO_CMOS_CMD,    7); byte day =     inportb (IO_CMOS_DATA);
outportb (IO_CMOS_CMD,    8); byte month =   inportb (IO_CMOS_DATA);
outportb (IO_CMOS_CMD,    9); word year =    inportb (IO_CMOS_DATA);
outportb (IO_CMOS_CMD, 0x32); word century = inportb (IO_CMOS_DATA);
// old line comment removed
second = CONVERT_BCD (second);  minute  = CONVERT_BCD (minute);
hour   = CONVERT_BCD (hour);    day     = CONVERT_BCD (day);
month  = CONVERT_BCD (month);   century = CONVERT_BCD (century);
year   = CONVERT_BCD (year) + 100 * century;
system_start_time = unixtime (year, month, day, hour, minute, second);
printf ("Current time: %4d/%02d/%02d %02d:%02d:%02d\n", 
        year, month, day, hour, minute, second);
// old line comment removed
asm ("sti");    // set interrupt flag
// old line comment removed
for (int i = 0;  i < 1024;  i++) { 
  // null entries:
  fill_page_desc ( &(video_pt.pds[i]), false,false,false,false,0 );
};
  
KMAP ( &(video_pt.pds[0xB8]), 0xB8*4096 );   // one page of video RAM

// enter new table in page directory
KMAPD ( &(current_pd->ptds[0]), (memaddress) (&video_pt) - 0xC0000000 );

gdt_flush ();
// old line comment removed
memset (ftable, 0, NUMBER_OF_FRAMES/8);  // all frames are free
// old line comment removed
memset (ftable, 0xff, 128);
free_frames -= 1024;
// old line comment removed
for (uint fid = 0;  fid < NUMBER_OF_FRAMES;  fid++) {
  
// old line comment removed
KMAP ( &(kernel_pt_ram[fid/1024].pds[fid%1024]), fid*PAGE_SIZE );
// old line comment removed
}
// old line comment removed
for (int i = 0;  i < 16;  i++) {
  // get physical address of kernel_pt_ram[i]
  memaddress physaddr = (memaddress)(&(kernel_pt_ram[i])) - 0xc0000000;
  KMAPD ( &(current_pd->ptds[832+i]), physaddr );
};
kputs ("RAM: 64 MByte, mapped to 0xD0000000-0xD3FFFFFF\n");
// old line comment removed
VIDEORAM = 0xD00B8000;
// remove first page table (including the old video mapping)
fill_page_table_desc (&current_pd->ptds[0], 0, 0, 0, 0);
gdt_flush ();
// old line comment removed
initialize_blocked_queue (&waitpid_queue);
// old line comment removed
initialize_blocked_queue (&keyboard_queue);
// old line comment removed
int vtno;
word *memptr;
unsigned blank = 0x20 | VT_NORMAL_BACKGROUND;  // blank character
for (vtno = 1;  vtno < 10;  vtno++) {
  memptr = (word*)vt[vtno].mem;
  memsetw (memptr, blank, VT_SIZE/2);
}
printf ("VT:  Initialized ten terminals (press [Alt-1] to [Alt-0])\n");
// old line comment removed
memset (buffer_cache, 0, sizeof (buffer_cache));
debug_printf ("nulled buffer cache; size: %d\n",     // REMOVE_DEBUGGING_CODE
              sizeof (buffer_cache));                // REMOVE_DEBUGGING_CODE
for (int i = 0;  i < BUFFER_CACHE_SIZE;  i++) {
  buffer_cache[i].blockno = 
  buffer_cache[i].dev     = -1;
  buffer_cache[i].dirty   = 0;
}
buffer_lock = get_new_lock ("disk buffer");
// old line comment removed
initialize_blocked_queue (&serial_disk_queue);
// old line comment removed
initialize_blocked_queue (&harddisk_queue);
// old line comment removed
hd_lock = get_new_lock ("hard disk");
// old line comment removed
initialize_blocked_queue (&floppy_queue);
// old line comment removed
  
// old line comment removed
install_syscall_handler (__NR_brk, syscall_sbrk);
// old line comment removed
install_syscall_handler (__NR_get_errno, syscall_get_errno);
install_syscall_handler (__NR_set_errno, syscall_set_errno);
// old line comment removed
install_syscall_handler (__NR_fork, syscall_fork);
// old line comment removed
install_syscall_handler (__NR_exit, syscall_exit);
// old line comment removed
install_syscall_handler (__NR_waitpid, syscall_waitpid);
// old line comment removed
install_syscall_handler (__NR_resign, syscall_resign);
// old line comment removed
install_syscall_handler (__NR_gettid,  syscall_gettid);
install_syscall_handler (__NR_getpid,  syscall_getpid);
install_syscall_handler (__NR_getppid, syscall_getppid);
// old line comment removed
install_syscall_handler (__NR_getpsinfo, syscall_getpsinfo);
// old line comment removed
install_syscall_handler (__NR_setpsname, syscall_setpsname);
// old line comment removed
install_syscall_handler (__NR_execve, syscall_execv);
// old line comment removed
install_syscall_handler (__NR_pthread_create, syscall_pthread_create);
// old line comment removed
install_syscall_handler (__NR_pthread_exit, syscall_pthread_exit);
// old line comment removed
install_syscall_handler (__NR_idle, syscall_idle);
// old line comment removed
install_syscall_handler (__NR_page_out, syscall_page_out);
// old line comment removed
install_syscall_handler (__NR_get_free_frames, syscall_get_free_frames);
install_syscall_handler (__NR_free_a_frame,    syscall_free_a_frame);
// old line comment removed
install_syscall_handler (__NR_setterm, syscall_setterm);
// old line comment removed
install_syscall_handler (__NR_clrscr, syscall_clrscr);
install_syscall_handler (__NR_get_xy, syscall_get_xy);
install_syscall_handler (__NR_set_xy, syscall_set_xy);
// old line comment removed
install_syscall_handler (__NR_read_screen,  syscall_read_screen);
install_syscall_handler (__NR_write_screen, syscall_write_screen);
// old line comment removed
install_syscall_handler (__NR_pthread_mutex_init, syscall_pthread_mutex_init);
// old line comment removed
install_syscall_handler (__NR_pthread_mutex_lock,   syscall_pthread_mutex_lock);
install_syscall_handler (__NR_pthread_mutex_trylock,syscall_pthread_mutex_trylock);
install_syscall_handler (__NR_pthread_mutex_unlock, syscall_pthread_mutex_unlock);
// old line comment removed
install_syscall_handler (__NR_pthread_mutex_destroy, syscall_pthread_mutex_destroy);
// old line comment removed
install_syscall_handler (__NR_readchar, syscall_readchar);
// old line comment removed
install_syscall_handler (__NR_open,      syscall_open);
install_syscall_handler (__NR_stat,      syscall_stat);
install_syscall_handler (__NR_close,     syscall_close);
install_syscall_handler (__NR_read,      syscall_read);
install_syscall_handler (__NR_write,     syscall_write);
install_syscall_handler (__NR_lseek,     syscall_lseek);
install_syscall_handler (__NR_isatty,    syscall_isatty);
install_syscall_handler (__NR_mkdir,     syscall_mkdir);
install_syscall_handler (__NR_rmdir,     syscall_rmdir);
install_syscall_handler (__NR_readdir,   syscall_getdent);
install_syscall_handler (__NR_truncate,  syscall_truncate);
install_syscall_handler (__NR_ftruncate, syscall_ftruncate);
install_syscall_handler (__NR_link,      syscall_link);
install_syscall_handler (__NR_unlink,    syscall_unlink);
install_syscall_handler (__NR_symlink,   syscall_symlink);
install_syscall_handler (__NR_readlink,  syscall_readlink);
// old line comment removed
install_syscall_handler (__NR_getcwd, syscall_getcwd);
install_syscall_handler (__NR_chdir, syscall_chdir);
// old line comment removed
install_syscall_handler (__NR_diskfree, syscall_diskfree);
// old line comment removed
install_syscall_handler (__NR_sync, syscall_sync);
// old line comment removed
install_syscall_handler (__NR_kill, syscall_kill);
// old line comment removed
install_syscall_handler (__NR_signal, syscall_signal);
// old line comment removed
install_syscall_handler (__NR_setuid32, syscall_setuid);
install_syscall_handler (__NR_setgid32, syscall_setgid);
install_syscall_handler (__NR_setreuid32, syscall_seteuid);
install_syscall_handler (__NR_setregid32, syscall_setegid);
install_syscall_handler (__NR_login, syscall_login);
// old line comment removed
install_syscall_handler (__NR_query_ids, syscall_query_ids);
// old line comment removed
install_syscall_handler (__NR_chown, syscall_chown);
install_syscall_handler (__NR_chmod, syscall_chmod);
// old line comment removed
install_syscall_handler (777, syscall_print_inode);
// old line comment removed
  
// old line comment removed
uartinit (2);
// old line comment removed
install_interrupt_handler (IRQ_COM2, serial_hard_disk_handler);
enable_interrupt (IRQ_COM2);
// old line comment removed
fdc_init ();  ata_init ();     // register floppy and hard disks
print_mount_table ();
// old line comment removed
                             
  
// old line comment removed
swap_fd = u_open ("/tmp/swap", O_RDWR, 0);
if (swap_fd != -1) {
  int size = u_lseek (swap_fd, 0, SEEK_END);
  printf ("swapon: enabling /tmp/swap (%d MByte)\n", size/1024/1024);
  u_lseek (swap_fd, 0, SEEK_SET);
} else
  printf ("swapon: error opening /tmp/swap!\n");
// old line comment removed
  initialize_module ();  // external code
  
// old line comment removed
asm ("sti");    // set interrupt flag
// old line comment removed
#ifdef START_KERNEL_SHELL    // REMOVE_DEBUGGING_CODE
  kernel_shell ();           // REMOVE_DEBUGGING_CODE
#endif                       // REMOVE_DEBUGGING_CODE
printf ("Starting five shells on tty0..tty4. Press [Ctrl-L] for de/en keyboard.\n");
start_program_from_disk ("/init");   // load flat binary of init
// never reach this line!
// old line comment removed
}
