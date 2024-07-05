#include <stdio.h>
#define MAX 300
//based on srtf
int queue[MAX], front = -1, rear = -1;

typedef struct process {
  int arrival_time, burst_time, completion_time, turn_around_time, waiting_time,
      remaining_burst, pid, priority;
} process_t;

void enqueue(int item) {
  if (front == -1)
    front = 0;
  queue[++rear] = item;
}
//least priority number == highest priority job
int dequeuemin(process_t *processes) {
  int loc = front, pid = -1;
  if (front != -1) {
    // Assume first process as the highest priority job
    pid = queue[front];
    for (int i = front; i <= rear; i++) {
      if (processes[pid].priority >
          processes[queue[i]].priority) {
        // If the job at queue[i] has highest priority
        // hpj = queue[i]
        pid = queue[i];
        loc = i;
      }
    }
    // pid holds the hpj & loc holds it's location in queue[]
    if (loc != front) {
      // Swap the current queue[front] with the srtj
      queue[loc] = queue[front];
      queue[front] = pid;
    }
    // dequeue()
    pid = queue[front];
    if (front == rear)
      front = rear = -1;
    else
      front = front + 1;
  }
  return pid;
}

void sort_processes(process_t *processes, int num_of_processes) {
  for (int i = 0; i < num_of_processes - 1; i++) {
    int swap = 0;
    for (int j = 0; j < num_of_processes - i - 1; j++) {
      if (processes[j].arrival_time > processes[j + 1].arrival_time) {
        process_t temp = processes[j];
        processes[j] = processes[j + 1];
        processes[j + 1] = temp;
        swap = 1;
      }
    }
    if (!swap)
      return;
  }
}

void round_robin(process_t *processes, int num_of_processes) {
  int cpu_time = 0, time_unit = 1;
  process_t idle, gantt[MAX];
  idle.burst_time = 0;

  int i = 0, preemp_proc = -1, g_index = 0;

  while (front > -1 || i < num_of_processes) {
    // !queue.is_empty() || not allocated for all processes.
    while (i < num_of_processes && processes[i].arrival_time <= cpu_time) {
      // arrived processes
      enqueue(i);
      i++;
    }

    if (front >= 0) {
      preemp_proc = dequeuemin(processes);
      cpu_time += time_unit;
      processes[preemp_proc].completion_time = cpu_time;
      gantt[g_index++] = processes[preemp_proc];
      processes[preemp_proc].remaining_burst -= time_unit;
      if (preemp_proc != -1 && processes[preemp_proc].remaining_burst != 0)
        // add the preempted process back to the ready queue
        enqueue(preemp_proc);
    } else {
      gantt[g_index] = idle;
      gantt[g_index++].completion_time = cpu_time = processes[i].arrival_time;
    }
  }
  double tat = 0, twt = 0;
  for (i = 0; i < num_of_processes; i++) {
    processes[i].turn_around_time =
        processes[i].completion_time - processes[i].arrival_time;
    processes[i].waiting_time =
        processes[i].turn_around_time - processes[i].burst_time;
    twt = twt + processes[i].waiting_time;
    tat = tat + processes[i].turn_around_time;
  }
  printf("Gantt chart:\n");
  for (i = 0; i < g_index - 1; i++) {
    if (gantt[i].burst_time == 0)
      printf("| Idle   ");
    else if (gantt[i].pid != gantt[i + 1].pid)
      printf("| p%d    ", gantt[i].pid);
  }
  printf("| p%d    |\n", gantt[i].pid);
  printf("0\t");
  for (i = 0; i < g_index - 1; i++) {
    if (gantt[i].pid != gantt[i + 1].pid)
      printf("%2d\t", gantt[i].completion_time);
  }
  printf("%2d\t", gantt[i].completion_time);
  printf("\nTable :\n");
  printf(" _________________________________\n");
  printf("|Process| AT | BT | CT | TT | WT |\n");
  printf("|--------------------------------|\n");
  for (i = 0; i < num_of_processes; i++) {
    printf("|p%d \t| %2d | %2d | %2d | %2d | %2d |\n", processes[i].pid,
           processes[i].arrival_time, processes[i].burst_time,
           processes[i].completion_time, processes[i].turn_around_time,
           processes[i].waiting_time);
  }
  printf(" _________________________________\n");
  twt = twt / num_of_processes;
  tat = tat / num_of_processes;
  printf("\nAverage WT:%f\n", twt);
  printf("Average TT:%f\n", tat);
}

int main() {
  int num_of_processes;
  process_t processes[MAX];
  printf("Enter the number of processes: ");
  scanf("%d", &num_of_processes);
  for (int i = 0; i < num_of_processes; i++) {
    printf("Enter Arrival time ,Burst Time, Priority of process %d: \n", i + 1);
    scanf("%d%d%d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    processes[i].pid = i + 1;
    // rbt = bt
    processes[i].remaining_burst = processes[i].burst_time;
  }
  // sort process based on arrival time
  sort_processes(processes, num_of_processes);

  round_robin(processes, num_of_processes);
  return 0;
}