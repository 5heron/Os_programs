#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
//Palindrome : reverse == number
//Perfect : sum(divisors < number) == number
//Armstrong : 
int palindrome(int num){
  int numcopy = num, multiplier = 10, reverse = 0;
  while(numcopy != 0){
    int digit = numcopy % 10;
    numcopy = numcopy / 10;
    //Raise the decimal places in reverse and add digit to the unit decimal place    
    reverse = (reverse * multiplier) + digit; 
  }
  if(num == reverse)
    return 1;
  else
   return 0;
}
int perfect(int num){
  int sum = 0;
  for(int i = 1;i < num;i++){
      //if i is a divisor, then add it to sum
      if(num % i == 0)
        sum = sum + i;
  }
  if(sum == num)
    return 1;
  else
    return 0;
}
int armstrong(int num){
  int numcopy = num, sum = 0;
  while(numcopy != 0){
    int digit = numcopy % 10;
    numcopy = numcopy / 10;
    //add cube of digit to sum    
    sum = sum + (digit * digit * digit); 
  }
  if(sum == num)
    return 1;
  else 
    return 0;
}
int main() {
  //syntax : shmget(key,size,flag) [get the shared memory]
  int shmid = shmget(1127, 1024, 0666);
  //syntax : shmat(id,address,flag) [attaches shared memory] 
  void *shmem = shmat(shmid, NULL, 0);
  int num = atoi(shmem); //Converts string to integer
  printf("Data read is %d\n", num);
  int palindrome_flag = palindrome(num);
  int perfect_flag = perfect(num);
  int armstrong_flag = armstrong(num);
  if(armstrong_flag)
    printf("%d is an Armstrong number\n",num);
  if(palindrome_flag)
    printf("%d is a Palindrome number\n",num);
  if(perfect_flag)
    printf("%d is a Perfect number\n",num);
  return 0;
}