// borrowed from https://github.com/wky/simulator/blob/master/uc-inc/stdlib.h
#ifndef STDLIB_H
#define STDLIB_H
#include "syscall.h"
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef int          int32_t;
typedef unsigned int size_t;
typedef unsigned int ssize_t;
typedef int          off_t;

#define syscall1(num, name, ret_type, arg1_type, arg1_name) \
static volatile __attribute__ ((noinline, naked)) ret_type\
 name(\
arg1_type arg1_name){\
        asm volatile ("jepriv #"#num ";jump lr; nop; nop; nop;");}

#define syscall2(num, name, ret_type, arg1_type, arg1_name, arg2_type, arg2_name) \
static volatile __attribute__ ((noinline, naked)) ret_type\
 name(\
arg1_type arg1_name, \
arg2_type arg2_name){\
        asm volatile ("jepriv #"#num ";jump lr; nop; nop; nop;");}

#define syscall3(num, name, ret_type, arg1_type, arg1_name, arg2_type, arg2_name, arg3_type, arg3_name) \
static volatile __attribute__ ((noinline, naked)) ret_type\
 name(\
arg1_type arg1_name, \
arg2_type arg2_name, \
arg3_type arg3_name){\
         asm volatile ("jepriv #"#num ";jump lr; nop; nop; nop;");}

// void exit(int status);
syscall1(0x900001, sys_exit, int, int, status);

// int read(int fd, void *buf, uint count);
syscall3(0x900003, sys_read, int, int, fd, void *, buf, uint, count);

// ssize_t write(int fd, const void *buf, size_t count);
syscall3(0x900004, sys_write, ssize_t, int, fd, const void*, buf, size_t, count);

// int open(const char *pathname, int flags);
syscall2(0x900005, sys_open, int, const char *, pathname, int, flags);

// int close(int fd);
syscall1(0x900006, sys_close, int, int, fd);

// off_t lseek(int fd, off_t offset, int whence);
syscall3(0x900013, sys_lseek, off_t, int, fd, off_t, offset, int, whence);

syscall2(0x9000f0, sys_div, int, int, a, int, b);
syscall2(0x9000f1, sys_udiv, uint32_t, uint32_t, a, uint32_t, b);
syscall2(0x9000f2, sys_mod, int, int, a, int, b);
syscall2(0x9000f3, sys_umod, uint32_t, uint32_t, a, uint32_t, b);
syscall1(0x9000f4, sys_putint, int, int, num);
syscall1(0x9000f5, sys_putuint, int, uint32_t, num);
syscall1(0x9000f6, sys_prints, int, uint32_t, num);

// void sys_putint(int num);

extern int main();

__attribute__ ((noinline, naked)) void
_start(){
        int status = main();
        sys_exit(status);
}

inline volatile int __divsi3(int a, int b){
        return sys_div(a, b);
}
inline volatile int __modsi3(int a, int b){
        return sys_mod(a, b);
}
inline volatile uint32_t __udivsi3(uint32_t a, uint32_t b){
        return sys_udiv(a, b);
}
inline volatile uint32_t __umodsi3(uint32_t a, uint32_t b){
        return sys_umod(a, b);
}

#endif