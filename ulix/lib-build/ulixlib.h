#line 1957 ""
// ulixlib.h
// To compile a Ulix program, include "ulixlib.h"
#line 887 ""
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
#line 1845 ""
#define true  1
#define false 0
#define NULL ((void*) 0)
#line 5042 ""
#define MEM_SIZE 1024*1024*64       // 64 MByte
#line 8619 ""
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
#line 9964 ""
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
#line 10095 ""
#define __NR_get_errno 501
#define __NR_set_errno 502
#line 10817 ""
#define __NR_resign       66
#line 10892 ""
#define __NR_gettid  21
#line 10932 ""
#define __NR_getpsinfo 503
#line 10984 ""
#define __NR_setpsname 504
#line 12637 ""
#define __NR_pthread_create 506
#line 12715 ""
#define __NR_pthread_exit 507
#line 14756 ""
#define __NR_get_free_frames   509
#define __NR_free_a_frame      510
#line 15634 ""
#define __NR_clrscr   512
#define __NR_get_xy   513
#define __NR_set_xy   514
#line 15727 ""
#define __NR_read_screen   515
#define __NR_write_screen  516
#line 17603 ""
#define __NR_pthread_mutex_init 517
#line 17673 ""
#define __NR_pthread_mutex_lock    518
#define __NR_pthread_mutex_unlock  519
#define __NR_pthread_mutex_trylock 526
#line 17735 ""
#define __NR_pthread_mutex_destroy 520
#line 19643 ""
#define __NR_readchar  525
#line 20244 ""
#define __NR_isatty  521
#line 23286 ""
#define __NR_diskfree  522
#line 17597 ""
#define EAGAIN 35
#line 17666 ""
#define EBUSY           16          // device / resource busy
#line 26725 ""
#define EPERM   1  // not permitted
#define ESRCH   3  // no such process
#define EINVAL 22  // invalid argument
#line 27321 ""
#define ENOENT          2               // No such file or directory
#define EACCES          13              // Permission denied
#line 11467 ""
#define CMDLINE_LENGTH 50   // how long can a process name be?
#line 13609 ""
#define __NR_idle 505
#line 14263 ""
#define __NR_page_out 508
#line 14913 ""
#define KEY_ESC     27
#define KEY_UP     191
#define KEY_DOWN   192
#define KEY_LEFT   193
#define KEY_RIGHT  194
#line 15426 ""
#define VT_NORMAL_BACKGROUND (0x0F << 8)
#define VT_BLUE_BACKGROUND   (0x1F << 8)
#define VT_RED_BACKGROUND    (0x4F << 8)
#line 15543 ""
#define __NR_setterm  511
#line 19630 ""
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#line 20034 ""
#define MAX_PFD 16   // up to 16 open_ files per process
#line 21557 ""
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
#line 21659 ""
#define O_RDONLY        0x0000     // read only
#define O_WRONLY        0x0001     // write only
#define O_RDWR          0x0002     // read and write
#define O_APPEND        0x0008     // append mode
#define O_CREAT         0x0200     // create file
#line 22071 ""
#define SEEK_SET 0    // absolute offset
#define SEEK_CUR 1    // relative offset
#define SEEK_END 2    // EOF plus offset
#line 26700 ""
#define SIG_DFL ((sighandler_t)0)     // default signal handling
#define SIG_IGN ((sighandler_t)1)     // ignore signal
#define SIG_ERR ((sighandler_t)-1)    // error code
#line 26737 ""
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
#line 27628 ""
#define __NR_login 523
#line 27782 ""
#define QUERY_UID  0
#define QUERY_EUID 1
#define QUERY_GID  2
#define QUERY_EGID 3
#define __NR_query_ids 524
#line 1960 ""
                      
#line 10116 ""
#define errno (syscall1(__NR_get_errno))
#line 28130 ""
#define strequal(s1,s2) (!strcmp((s1),(s2)))
#define strdiff(s1,s2)  (strcmp((s1),(s2)))
#line 1961 ""
                              
#line 20389 ""
#define gets(s) ((ureadline(s,9999,true)), s)
#line 1837 ""
typedef unsigned char            byte;
typedef unsigned char         boolean;
typedef unsigned short           word;
#line 1855 ""
typedef unsigned char         uint8_t;
typedef unsigned short       uint16_t;
typedef unsigned int         uint32_t;
typedef unsigned long long   uint64_t;

typedef int                    size_t;
typedef unsigned int             uint;   // short names for "unsigned int",
typedef unsigned long           ulong;   // "unsigned long" and
typedef unsigned long long  ulonglong;   // "unsigned long long" (64 bit)
#line 1870 ""
typedef unsigned int       memaddress;
#line 7434 ""
typedef unsigned int addr_space_id;
#line 8529 ""
typedef unsigned int thread_id;
#line 26661 ""
typedef void (*sighandler_t)(int);
#line 6603 ""
typedef struct {
  unsigned int gs, fs, es, ds;
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned int int_no, err_code;
  unsigned int eip, cs, eflags, useresp, ss;
} context_t;
#line 8352 ""
typedef struct {
  thread_id  pid;         // process id
  thread_id  tid;         // thread id
  thread_id  ppid;        // parent process
  int        state;       // state of the process
  context_t  regs;        // context
  memaddress esp0;        // kernel stack pointer
  memaddress eip;         // program counter
  memaddress ebp;         // base pointer
  
#line 7447 ""
addr_space_id addr_space;
#line 8695 ""
thread_id next;       // id of the ``next'' thread
thread_id prev;       // id of the ``previous'' thread
#line 8998 ""
boolean used;
#line 10038 ""
int error;
#line 10708 ""
int exitcode;
int waitfor;    // pid of the child that this process waits for
#line 11471 ""
char cmdline[CMDLINE_LENGTH];
#line 12500 ""
boolean   new;                    // is this thread new?
void      *top_of_thread_kstack;  // extra kernel stack for this thread
#line 15448 ""
int terminal;
#line 20040 ""
int files[MAX_PFD];
#line 20414 ""
char cwd[256];
#line 26669 ""
  sighandler_t sighandlers[32];
  unsigned long sig_pending;
  unsigned long sig_blocked;
#line 27178 ""
word uid;   // user ID
word gid;   // group ID
word euid;  // effective user ID
word egid;  // effective group ID
word ruid;  // real user ID
word rgid;  // real group ID
#line 8362 ""
} TCB;
#line 12429 ""
typedef void *pthread_t;
typedef void pthread_attr_t;   // attributes not implemented
#line 17554 ""
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
#line 23079 ""
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
#line 23133 ""
struct dir_entry {
  word inode;              // inode number
  byte filename[64];       // filename
};
#line 23184 ""
struct diskfree_query {
  int device;         // device ID (is set before calling mx_diskfree)
  int size;           // size of filesystem, in blocks
  int used;           // number of used blocks
  int free;           // number of free blocks (redundant; == size-used)
  char name[10];      // name (such as "/dev/hda")
  char mount[256];    // mount point
  char fstype[10];    // filesystem name, e.g. "minix"
};
#line 1963 ""
                             
#line 27654 ""
struct passwd {
  char pw_name[32];    // user name
  char pw_passwd[32];  // password
  word pw_uid;         // user ID
  word pw_gid;         // group ID
  char *pw_gecos;      // long name        (ULIX: unused)
  char pw_dir[32];     // home directory
  char *pw_shell;      // shell            (ULIX: unused)
};
#line 21434 ""
void splitpath (const char *path, char *dirname, char *basename);
char *basename (char *path);
char *dirname  (char *path);
#line 28038 ""
size_t strlen (const char *str);
int    strcmp (const char *str1, const char *str2);
int    strncmp (const char *str1, const char *str2, uint n);
char   *strncpy (char *dest, const char *src, size_t count);
char   *strcpy  (char *dest, const char *src);
int    atoi (char *s);
int    atoi8 (char *s);
#line 28143 ""
void *memcpy  (void *dest, const void *src, size_t count);
void *memset  (void *dest, char val, size_t count);
word *memsetw (word *dest, word val, size_t count);
#line 28233 ""
int printf  (const char *format, ...);
int sprintf (char *out, const char *format, ...);
#line 1964 ""
                                
#line 8269 ""
void *sbrk (int incr);
#line 9896 ""
inline int syscall4 (int eax, int ebx, int ecx, int edx);
inline int syscall3 (int eax, int ebx, int ecx);
inline int syscall2 (int eax, int ebx);
inline int syscall1 (int eax);
#line 10459 ""
int fork ();
#line 10632 ""
void exit (int exitcode);
#line 10778 ""
int waitpid (int pid, int *status, int options);
#line 10835 ""
inline void resign ();
#line 10905 ""
int gettid ();
int getpid ();
int getppid ();
#line 11482 ""
int execv (const char *path, char *const argv[]);
#line 12651 ""
int pthread_create (pthread_t *thread, const pthread_attr_t *attr,
                    void *address, void *arg);
#line 12724 ""
void pthread_exit ();
#line 13628 ""
inline void idle ();
#line 14288 ""
int lib_page_out (int pageno);
#line 14769 ""
int get_free_frames ();
void free_a_frame ();
#line 15554 ""
void setterm (int vt);
#line 15674 ""
void clrscr ();
void get_xy (char *x, char *y);
void set_xy (char x, char y);
#line 15752 ""
void read_screen (char *buf);
void write_screen (char *buf);
#line 15770 ""
void scroll_up ();
void scroll_down ();
#line 17764 ""
int pthread_mutex_init    (pthread_mutex_t *mutex,
                           const pthread_mutexattr_t *attr);
int pthread_mutex_lock    (pthread_mutex_t *mutex);
int pthread_mutex_unlock  (pthread_mutex_t *mutex);
int pthread_mutex_destroy (pthread_mutex_t *mutex);
#line 20258 ""
int open       (const char *path, int oflag, ...);
int stat       (const char *path, struct stat *buf);
int close      (int fildes);
int read       (int fildes, void *buf, size_t nbyte);
int write      (int fildes, const void *buf, size_t nbyte);
int lseek      (int fildes, int offset, int whence);
boolean isatty (int fd);
int mkdir      (const char *path, int mode);
int rmdir      (const char *path);
int getdent    (const char *path, int index, struct dir_entry *buf);
int ftruncate  (int fd, int length);
int truncate   (const char *path, int length);
int link       (const char *path1, const char *path2);
int unlink     (const char *path);
int symlink    (const char *path1, const char *path2);
int readlink   (char *path, char *buf, int bufsize);
#line 20330 ""
int  ureadline (char *s, int maxlength, boolean echo);
byte ureadchar ();
#line 20494 ""
char *getcwd (char *buf, int size);
int chdir (const char *path);
#line 23297 ""
void diskfree (struct diskfree_query *query);
#line 24308 ""
void sync ();
#line 27058 ""
int kill (int pid, int signo);
int raise (int signo);
sighandler_t signal (int sig, sighandler_t func);
#line 27635 ""
int setuid  (word uid);    // set user ID
int setgid  (word gid);    // set group ID
int seteuid (word euid);   // set effective user ID
int setegid (word egid);   // set effective group ID
int login   (word uid, char *pass);
#line 27669 ""
int getpwnam_r (const char *name,   struct passwd *pwd, 
                char *buffer, int bufsize, struct passwd **result);
int getpwuid_r (word uid, struct passwd *pwd, 
                char *buffer, int bufsize, struct passwd **result);                
#line 27770 ""
word getuid  ();
word geteuid ();
word getgid  ();
word getegid ();
#line 27969 ""
int chown (const char *path, short owner, short group);
int chmod (const char *path, short mode);
#line 28274 ""
int ulixlib_printchar (byte c);
