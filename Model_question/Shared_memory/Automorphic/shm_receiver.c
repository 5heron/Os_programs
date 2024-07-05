#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
int main() {
  //syntax : shmget(key,size,flag) [get the shared memory]
  int shmid = shmget(1127, 1024, 0666);
  //syntax : shmat(id,address,flag) [attaches shared memory] 
  void *shmem = shmat(shmid, NULL, 0);
  int num = atoi(shmem); //Converts string to integer
  printf("Data read is %d\n", num);
  int square = num * num;
  int digit = square % 10;
  if(digit == num)
    printf("%d is an Automorphic number\n",num);
  else
    printf("%d is not an Automorphic number\n",num);
  return 0;
}
