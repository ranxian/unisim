#ifndef SYSCALL_H
#define SYSCALL_H

#define O_RDONLY        0
#define O_WRONLY        1
#define O_RDWR          2
#define O_APPEND        8
#define O_CREAT         512
#define O_TRUNC         1024
#define SEEK_SET        0
#define SEEK_CUR        1
#define SEEK_END        2

#define SYSCALL_BASE    0x900000
#define SYS_exit        0x900001
#define SYS_read        0x900003
#define SYS_write       0x900004
#define SYS_open        0x900005
#define SYS_close       0x900006
#define SYS_lseek       0x900013
#define SYS_div         0x9000f0
#define SYS_udiv        0x9000f1
#define SYS_mod         0x9000f2
#define SYS_umod        0x9000f3
#define SYS_putint      0x9000f4
#define SYS_putuint     0x9000f5
#define SYS_prints		0x9000f6

extern int halted;
int syscall(int callnum);
#endif
