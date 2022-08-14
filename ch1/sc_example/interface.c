#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/module.h>

/*After git src main df38ada2931f, sys/module.h SHALL be included AFTER sys/param.h.
Attached patch moves sys/param.h just before sys/modules.h. 
(Because of some constants (ex. MAXMODLEN))*/

/*complie with gcc, gcc interface.c -o interface 
(Since it is used on userland not in kernel module)*/


int main(int argc, char *argv[]){
  int syscall_num;
  struct module_stat stat;
  if (argc != 2){
    printf("Usage:\n%s <string>\n", argv[0]);
    exit(0);
  }
  stat.version = sizeof(data);
  modstat(modfind("sc_example"), &stat);
  syscall_num = stat.data.intval;
  
  return (syscall(syscall_num, argv[1]));
}

/*
$ ./interface Hello,\ kernel!
$ dmesg | tail -n 1
Hello, kernel!
*/

/*
Without using this C code
$ sudo kldload ./sc_example.ko
System call loaded at offset 210
$ perl -e '$str = "Hello, kernel!";' -e 'syscall(210, $str);'
$ dmesg | tail -n 1
Hello, kernel!

*/
