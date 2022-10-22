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
	int time_remaining;
	int waiting_time;
	int turn_around_time;
	enum Status status;
};

int finished_check(struct Process *processes, int len)
{
	for (int i=0; i < len; ++i)
	{
		if (processes[i].status == PENDING)
		{
			return 1;
		}
	}
	
	return 0;
}

void round_robin(struct Process *processes, int len, int time_slice)
{
	int temp_tat = 0;
	printf("Gaantt Chart:\n");

	while (finished_check(processes, len))
	{
		for (int i=0; i < len; ++i)
		{
			if (processes[i].status == PENDING)
			{
				if (processes[i].time_remaining >= time_slice)
				{
					processes[i].time_remaining -= time_slice;
					for (int j=0; j < len; ++j)
					{
						if (j != i && processes[j].status == PENDING)
						{
							processes[j].waiting_time += time_slice;
						}
					}
					printf("%d P%d ", temp_tat, processes[i].p_id);
					temp_tat += time_slice;	
				}
				else
				{
					for (int j=0; j < len; ++j)
					{
						if (j != i && processes[j].status == PENDING)
						{
							processes[j].waiting_time += processes[i].time_remaining;
						}
					}
					printf("%d P%d ", temp_tat, processes[i].p_id);
					temp_tat += processes[i].time_remaining;
					processes[i].time_remaining = 0;
				}
				if (processes[i].time_remaining == 0)
				{
					processes[i].turn_around_time = temp_tat;
					processes[i].status = FINISHED;
				}
			}
		}
	}
	printf("%d\n\n", temp_tat);
}

void display_results(struct Process *processes, int len)
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
	for(int i=0; i < len; ++i)
	{
		printf("%d\t\t", processes[i].p_id);
		printf("%d\t\t", processes[i].burst_time);
		printf("%d\t\t", processes[i].waiting_time);
		printf("%d\n", processes[i].turn_around_time);
		avg_waiting_time += processes[i].waiting_time;
		avg_turn_around_time += processes[i].turn_around_time;
	}
	avg_waiting_time /= len;
	avg_turn_around_time /= len;

	printf("Average Waiting Time is %f\n", avg_waiting_time);
	printf("Average Turn Around Time is %f\n", avg_turn_around_time);
}

int main()
{
	int len;
	printf("Enter the number of processes: ");
	scanf("%d", &len);
	
	struct Process *processes = (struct Process *)calloc(len, sizeof(struct Process));
	
	for (int i=0; i < len; ++i)
	{
		processes[i].p_id = i + 1;
		printf("Enter the burst time of Process %d: ", i + 1);
		scanf("%d", &processes[i].burst_time);
		processes[i].time_remaining = processes[i].burst_time;
		processes[i].waiting_time = 0;
		processes[i].turn_around_time = 0;
		processes[i].status = PENDING;
	}

	printf("\nEnter the value of time slice: ");
	int time_slice;
	scanf("%d", &time_slice);
	
	round_robin(processes, len, time_slice);
	display_results(processes, len);
	free(processes);
	return 0;
}
