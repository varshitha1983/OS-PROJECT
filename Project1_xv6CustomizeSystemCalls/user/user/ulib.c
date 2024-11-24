#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "fcntl.h" // For file descriptor constants if needed


//
// wrapper so that it's OK if main() does not call exit().
//
void start(){
  extern int main();
  main();
  exit(0);
}

char* strcpy(char *s, const char *t){
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int strcmp(const char *p, const char *q){
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint strlen(const char *s){
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void* memset(void *dst, int c, uint n){
  char *cdst = (char *) dst;
  int i;
  for(i = 0; i < n; i++){
    cdst[i] = c;
  }
  return dst;
}

char* strchr(const char *s, char c){
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char* gets(char *buf, int max){
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int stat(const char *n, struct stat *st){
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int atoi(const char *s){
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void* memmove(void *vdst, const void *vsrc, int n){
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  if (src > dst) {
    while(n-- > 0)
      *dst++ = *src++;
  } else {
    dst += n;
    src += n;
    while(n-- > 0)
      *--dst = *--src;
  }
  return vdst;
}

int memcmp(const void *s1, const void *s2, uint n){
  const char *p1 = s1, *p2 = s2;
  while (n-- > 0) {
    if (*p1 != *p2) {
      return *p1 - *p2;
    }
    p1++;
    p2++;
  }
  return 0;
}

void *memcpy(void *dst, const void *src, uint n){
  return memmove(dst, src, n);
}

/*// Wrapper for the sys_priority_pipes system call
int priority_pipes(int fd, uint64 data, int n, int priority) {
    // Perform a system call to interact with the priority pipe
    return syscall(priority_pipes, fd, data, n, priority);
}/*
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

// Declare syscall function
extern int syscall(int num, ...);
extern int stat(const char *path, struct stat *st);


// System call IDs
#define SYS_priority_pipes 26

// Alias for struct stat to avoid conflicts
struct xv6_stat {
    uint dev;   // Device number
    uint ino;   // Inode number
    short type; // File type
    short nlink; // Number of links
    uint size;   // Size of file in bytes
};

// Function prototypes
int xv6_open(const char *path, int flags);
int xv6_stat(const char *path, struct xv6_stat *st);

//
// Wrapper so that it's OK if main() does not call exit().
//
void start() {
    extern int main();
    main();
    exit(0);
}

char *strcpy(char *s, const char *t) {
    char *os = s;
    while ((*s++ = *t++) != 0)
        ;
    return os;
}

int strcmp(const char *p, const char *q) {
    while (*p && *p == *q)
        p++, q++;
    return (uchar)*p - (uchar)*q;
}

uint strlen(const char *s) {
    uint n = 0;
    while (s[n])
        n++;
    return n;
}

void *memset(void *dst, int c, uint n) {
    char *cdst = (char *)dst;
    for (uint i = 0; i < n; i++) {
        cdst[i] = c;
    }
    return dst;
}

char *strchr(const char *s, char c) {
    while (*s) {
        if (*s == c)
            return (char *)s;
        s++;
    }
    return 0;
}

char *gets(char *buf, int max) {
    int i = 0, cc;
    char c;

    while (i + 1 < max) {
        cc = read(0, &c, 1);
        if (cc < 1)
            break;
        buf[i++] = c;
        if (c == '\n' || c == '\r')
            break;
    }
    buf[i] = '\0';
    return buf;
}

int xv6_stat(const char *n, struct xv6_stat *st) {
    int fd = xv6_open(n, O_RDONLY);
    if (fd < 0)
        return -1;
    int r = fstat(fd, (struct stat *)st); // Cast to appropriate struct type
    close(fd);
    return r;
}

int xv6_open(const char *path, int flags) {
    return open(path, flags);
}

int atoi(const char *s) {
    int n = 0;
    while ('0' <= *s && *s <= '9') {
        n = n * 10 + *s++ - '0';
    }
    return n;
}

void *memmove(void *vdst, const void *vsrc, int n) {
    char *dst = vdst;
    const char *src = vsrc;

    if (src > dst) {
        while (n-- > 0)
            *dst++ = *src++;
    } else {
        dst += n;
        src += n;
        while (n-- > 0)
            *--dst = *--src;
    }
    return vdst;
}

int memcmp(const void *s1, const void *s2, uint n) {
    const char *p1 = s1, *p2 = s2;
    while (n-- > 0) {
        if (*p1 != *p2)
            return *p1 - *p2;
        p1++;
        p2++;
    }
    return 0;
}

void *memcpy(void *dst, const void *src, uint n) {
    return memmove(dst, src, n);
}*/


