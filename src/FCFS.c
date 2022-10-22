#include <stdio.h>
#include <stdlib.h>

struct Process
{
	int p_id;
	int burst_time;
	int waiting_time;
	int turn_around_time;
};

void display_results(struct Process *processes, int size)
{
	float avg_waiting_time=0;
	float avg_turn_around_time=0;
	printf
	(
		"Process ID\t"
		"Burst Time\t"
		"Waiting Time\t"
		"Turn Around Time\n"
	);
	for(int i=0; i<size; ++i)
	{
		printf("%d\t\t",processes[i].p_id);
		printf("%d\t\t",processes[i].burst_time);
		printf("%d\t\t",processes[i].waiting_time);
		printf("%d\n",processes[i].turn_around_time);
		avg_waiting_time += processes[i].waiting_time;
		avg_turn_around_time += processes[i].turn_around_time;
	}
	avg_waiting_time /= size;
	avg_turn_around_time /= size;

	printf("Average Waiting Time is %f\n", avg_waiting_time);
	printf("Average Turn Around Time is %f\n", avg_turn_around_time);
}

void fcfs (struct Process *processes, int len)
{
	printf("\nGantt Chart:\n");
	int time = 0;
	for (int i=0; i < len; ++i)
	{
		printf("%d ", time);
		for(int j=i+1; j < len; ++j)
		{
			processes[j].waiting_time += processes[i].burst_time;
		}
		processes[i].turn_around_time = processes[i].waiting_time + processes[i].burst_time;
		
		printf("P%d ", processes[i].p_id);
		time += processes[i].burst_time;
	}
	printf("%d\n\n", time);
	display_results(processes, len);
	
}

int main()
{
	int proc_len;
	printf("Enter the number of processes: ");
	scanf("%d", &proc_len);
	
	struct Process *processes = (struct Process *)calloc(proc_len, sizeof(struct Process));
	printf("Enter the details of %d processes:\n", proc_len);
	
	for (int i=0; i < proc_len; ++i)
	{
		processes[i].p_id = i+1;
		printf("Enter the Burst Time of process%d\n=>", i+1);
		scanf("%d", &processes[i].burst_time);
		processes[i].waiting_time = 0;
		processes[i].turn_around_time = 0;
	}
	fcfs(processes, proc_len);
	
	return 0;
}
