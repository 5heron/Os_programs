#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
int main() {
  int shmid;
  char string[25];
  //syntax : shmget(key,size,flag)
  shmid = shmget(1127, 1024, 0666 | IPC_CREAT);
  //syntax : shmat(id,address,flag)
  void *mem = shmat(shmid, NULL, 0);
  printf("Enter the Number : ");
  gets(string);
  //Copy string to memory
  strcpy(mem, string);
  return 0;
}
