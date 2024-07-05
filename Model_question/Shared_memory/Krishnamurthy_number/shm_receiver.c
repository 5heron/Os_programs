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
  int numcopy = num;
  int sum = 0;
  while(numcopy != 0){
    int digit = numcopy % 10;
    numcopy = numcopy / 10;
    int factorial = 1;
    //calculate factorial of digit
    for (int i = 1; i <= digit; i++)
      factorial = factorial * i;
    //calculate sum of factorials
    sum = sum + factorial; 
  }
  if(sum == num)
    printf("%d is a Krishnamurthy number\n",num);
  else
    printf("%d is not a Krishnamurthy number\n",num);
  return 0;
}
