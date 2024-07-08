#include <stdio.h>
#define MAX 100
struct mem{
  int pId,isAlloc,size,frag;
};
void display(struct mem memory_blocks[], int number_of_blocks) {
    int total_frag = 0;
    printf("Memory :\n");
    for(int i = 0; i < number_of_blocks; i++)
        printf("__________");
    printf("\n");
    for (int j = 0; j < number_of_blocks; j++) {
      if (memory_blocks[j].isAlloc == 1){ 
        printf("|%3d + %3d",memory_blocks[j].size - memory_blocks[j].frag,memory_blocks[j].frag);
        total_frag += memory_blocks[j].frag; 
      }else
        printf("|   %3d   ",memory_blocks[j].size);
    }
    printf("|\n");
    for(int i = 0; i < number_of_blocks; i++)
        printf("----------");
    printf("\n");
    for(int i = 0; i < number_of_blocks; i++)
        (memory_blocks[i].isAlloc) ? printf("|   P%d    ",memory_blocks[i].pId):printf("|         ");
    printf("|\nTotal fragmentation : %d\n",total_frag);
}

void firstfit(struct mem memory_blocks[], int number_of_blocks, int process_blocks[], int number_of_processes) {
  int i, j, number_of_allocatedp = 0, flag;
  printf("Unallocated processes : ");
  for (i = 0; i < number_of_processes; i++) {
    flag = 0;
    for (j = number_of_allocatedp; j < number_of_blocks; j++) {
      if (memory_blocks[j].size >= process_blocks[i] && memory_blocks[j].isAlloc == 0) {
        memory_blocks[j].frag = memory_blocks[j].size - process_blocks[i];
        memory_blocks[j].pId = i;
        memory_blocks[j].isAlloc = 1;
        flag = 1;
        break;
      }
    }
    if(flag == 0)
        printf("P%d ",i);
  }
  printf("\n");
  display(memory_blocks, number_of_blocks);
}

void bestfit(struct mem memory_blocks[], int number_of_blocks, int process_blocks[], int number_of_processes) {
  int j, number_of_allocatedp = 0, i;
  for (int i = 0; i < number_of_blocks - 1; i++) {
    for (int j = 0; j < number_of_blocks - 1; j++) {
      if (memory_blocks[j].size > memory_blocks[j + 1].size) {
        struct mem temp = memory_blocks[j];
        memory_blocks[j] = memory_blocks[j + 1];
        memory_blocks[j + 1] = temp;
      }
    }
  }
  firstfit(memory_blocks, number_of_blocks, process_blocks, number_of_processes);
}

void worstfit(struct mem memory_blocks[], int number_of_blocks, int process_blocks[], int number_of_processes) {
  int j, number_of_allocatedp = 0, i;
  for (int i = 0; i < number_of_blocks - 1; i++) {
    for (int j = 0; j < number_of_blocks - 1; j++) {
      if (memory_blocks[j].size < memory_blocks[j + 1].size) {
        struct mem temp = memory_blocks[j];
        memory_blocks[j] = memory_blocks[j + 1];
        memory_blocks[j + 1] = temp;
      }
    }
  }
  firstfit(memory_blocks, number_of_blocks, process_blocks, number_of_processes);
}

int main() {
  int i, number_of_blocks, choice, process_blocks[MAX], number_of_processes;
  struct mem memory_blocks[MAX];
  printf("Enter the number of memory blocks : ");
  scanf("%d", &number_of_blocks);
  printf("Enter the memory blocks : ");
  for (i = 0; i < number_of_blocks; i++)
    scanf("%d", &memory_blocks[i].size);
  printf("Enter the number of processes :");
  scanf("%d", &number_of_processes);
  printf("Enter the size of processes : ");
  for (i = 0; i < number_of_processes; i++)
    scanf("%d", &process_blocks[i]);
  do {
    printf("Enter 1:Firstfit 2:Bestfit 3:Worstfit 4:Exit : ");
    scanf("%d", &choice);
    for (i = 0; i < number_of_blocks; i++)
        memory_blocks[i].isAlloc = 0;
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