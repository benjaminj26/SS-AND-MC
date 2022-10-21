#include <stdio.h>
#include <stdlib.h>

enum Status
{
	FINISHED,
	PENDING
};

struct Process
{
	int p_id;
	int burst_time;
	int waiting_time;
	int turn_around_time;
	enum Status status;
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

void sjf(struct Process *processes, int len)
{
	printf("Gaantt Chart:\n");
	int temp_tat = 0;
	for (int i=0; i < len; ++i)
	{
		printf("%d ", temp_tat);
		int shortest = 0;
		for (int j=1; j < len; ++j)
		{
			if (processes[j].burst_time < processes[shortest].burst_time && processes[j].status == PENDING)
			{
				shortest = j;
			}		
		}
		
		while (processes[shortest].status == FINISHED && shortest < len)
		{
			shortest += 1;
			for (int j = shortest + 1; j < len; ++j)
			{
				if (processes[j].burst_time < processes[shortest].burst_time)
				{
					shortest = j;
				}
			}
		}
		
		for (int j=0; j < len; ++j)
		{
			if (j != shortest && processes[j].status == PENDING)
			{
				processes[j].waiting_time += processes[shortest].burst_time;
			}
		}
		printf("P%d ", processes[shortest].p_id);
		temp_tat += processes[shortest].burst_time;
		processes[shortest].turn_around_time = temp_tat;
		processes[shortest].status = FINISHED;
	}
	printf("%d\n\n", temp_tat);
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
		processes[i].status = PENDING;
	}
	sjf(processes, proc_len);
	display_results(processes, proc_len);
	free(processes);
	return 0;
}
