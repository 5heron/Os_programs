#include <stdio.h>
#define MAX 100
int temp, pid_of_allocated[MAX];

void display(int memory_blocks[], int number_of_blocks, int process_blocks[], int number_of_allocatedp) {
  //Initialise total fragmentation
  int j, totalfrag = 0, fragmentation; 
  //Print box Outline
  for (j = 0; j < number_of_blocks + number_of_allocatedp; j++)
    printf("_____");
  printf("\n");
  //Go through all memory blocks
  for (j = 0; j < number_of_blocks; j++) {
    //For allocated blocks (allocated region) store process size to calculate fragmentation
    //For unallocated blocks store size of memory block
    temp = (j < number_of_allocatedp) ? process_blocks[pid_of_allocated[j] - 1] : memory_blocks[j];
    //Print the stored value
    printf("|%3d ", temp);
    //Calculate internal fragmentation (will be zero for unallocated memory blocks) 
    fragmentation = memory_blocks[j] - temp;
    //Add it with total fragmentation
    totalfrag += fragmentation;
    //Display the fragmentation if any
    if (fragmentation != 0)
      printf("+%3d ", fragmentation);
  }
  printf("|\n");
  //Print box Outline
  for (j = 0; j < number_of_blocks + number_of_allocatedp; j++)
    printf("-----");
  printf("\n");
  //Print allocated process
  //Unallocated process can be found from the array used here
  for (j = 0; j < number_of_allocatedp; j++)
    printf("  P%d\t  ", pid_of_allocated[j]);
  printf("\n");
  //Display total fragmentation
  printf("Total internal fragmentation = %d\n", totalfrag);
}

void firstfit(int memory_blocks[], int number_of_blocks, int process_blocks[], int number_of_processes) {
  //Initialise number of allocated process
  int i, j, number_of_allocatedp = 0;
  //Go through all processes
  for (i = 0; i < number_of_processes; i++) {
    //Go through all memory blocks
    for (j = number_of_allocatedp; j < number_of_blocks; j++) {
      //Find first memory block in which process block fits
      //If memory blocks are sorted then the first memory block will be the smallest(bestfit) or largest(worstfit) in which process can fit
      if (memory_blocks[j] >= process_blocks[i]) {
        //SAVE the memory block as allocated by swapping it to allocated region in array
        //End of Allocated region index = no of allocated processes 
        temp = memory_blocks[j];
        memory_blocks[j] = memory_blocks[number_of_allocatedp];
        memory_blocks[number_of_allocatedp] = temp;
        //Strore pid of allocated processes(for output)
        pid_of_allocated[number_of_allocatedp] = i + 1;
        //Grow allocated region
        number_of_allocatedp++;
        break;
      }
    }
  }
  display(memory_blocks, number_of_blocks, process_blocks, number_of_allocatedp);
}

void bestfit(int memory_blocks[], int number_of_blocks, int process_blocks[], int number_of_processes) {
  int j, number_of_allocatedp = 0, i;
  // sort memory blocks in ASC order
  for (int i = 0; i < number_of_blocks - 1; i++) {
    for (int j = 0; j < number_of_blocks - 1; j++) {
      if (memory_blocks[j] > memory_blocks[j + 1]) {
        temp = memory_blocks[j];
        memory_blocks[j] = memory_blocks[j + 1];
        memory_blocks[j + 1] = temp;
      }
    }
  }
  //Call first fit on sorted array of mem blocks
  firstfit(memory_blocks, number_of_blocks, process_blocks, number_of_processes);
}

void worstfit(int memory_blocks[], int number_of_blocks, int process_blocks[], int number_of_processes) {
  int j, number_of_allocatedp = 0, i;
  // sort memory blocks in DESC order
  for (int i = 0; i < number_of_blocks - 1; i++) {
    for (int j = 0; j < number_of_blocks - 1; j++) {
      if (memory_blocks[j] < memory_blocks[j + 1]) {
        temp = memory_blocks[j];
        memory_blocks[j] = memory_blocks[j + 1];
        memory_blocks[j + 1] = temp;
      }
    }
  }
  //Call first fit on sorted array of mem blocks
  firstfit(memory_blocks, number_of_blocks, process_blocks, number_of_processes);
}

int main() {
  int i, number_of_blocks, choice, process_blocks[MAX], number_of_processes, memory_blocks[MAX];
  //Read the memory blocks
  printf("Enter the number of memory blocks : ");
  scanf("%d", &number_of_blocks);
  printf("Enter the memory blocks : ");
  for (i = 0; i < number_of_blocks; i++)
    scanf("%d", &memory_blocks[i]);
  //Read the process blocks
  printf("Enter the number of processes :");
  scanf("%d", &number_of_processes);
  printf("Enter the size of processes : ");
  for (i = 0; i < number_of_processes; i++)
    scanf("%d", &process_blocks[i]);
  do {
    //Read the choice of allocation algorithm 
    printf("Enter 1:Firstfit 2:Bestfit 3:Worstfit 4:Exit : ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      firstfit(memory_blocks, number_of_blocks, process_blocks, number_of_processes);
      break;
    case 2:
      bestfit(memory_blocks, number_of_blocks, process_blocks, number_of_processes);
      break;
    case 3:
      worstfit(memory_blocks, number_of_blocks, process_blocks, number_of_processes);
    case 4:
      break;
    default:
      printf("Invalid input\n");
    }
  } while (choice != 4);
  return 0;
}