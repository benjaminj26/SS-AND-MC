#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum Status
{
	FINISHED,
	PENDING
};

struct Process
{
	unsigned p_id;
	unsigned burst_time;
	unsigned priority;
	unsigned waiting_time;
	unsigned turn_around_time;
	unsigned time_remaining;
	enum Status status;
};

void display_results(struct Process *processes, size_t size)
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
	for(size_t i = 0; i < size; ++i)
	{
		printf("%u\t\t",processes[i].p_id);
		printf("%u\t\t",processes[i].burst_time);
		printf("%u\t\t",processes[i].waiting_time);
		printf("%u\n",processes[i].turn_around_time);
		avg_waiting_time += processes[i].waiting_time;
		avg_turn_around_time += processes[i].turn_around_time;
	}
	avg_waiting_time /= size;
	avg_turn_around_time /= size;

	printf("Average Waiting Time is %f\n", avg_waiting_time);
	printf("Average Turn Around Time is %f\n", avg_turn_around_time);
}

void fcfs_scheduling (struct Process *processes, size_t proc_len)
{
	printf("\nGantt Chart:\n");
	unsigned time = 0;
	for (size_t i = 0; i < proc_len; ++i)
	{
		printf("%u ", time);
		for(size_t j = i + 1; j < proc_len; ++j)
		{
			processes[j].waiting_time += processes[i].burst_time;
			processes[i].status = FINISHED;
		}
		processes[i].turn_around_time = processes[i].waiting_time + processes[i].burst_time;
		
		printf("P%u ", processes[i].p_id);
		time += processes[i].burst_time;
	}
	printf("%u\n\n", time);
	display_results(processes, proc_len);
}

void sjf_scheduling (struct Process *processes, size_t proc_len)
{
	printf("Gaantt Chart:\n");
	unsigned temp_tat = 0;
	for (size_t i = 0; i < proc_len; ++i)
	{
		printf("%u ", temp_tat);
		size_t shortest = 0;
		for (size_t j = 1; j < proc_len; ++j)
		{
			if (
				processes[j].burst_time < processes[shortest].burst_time && 
				processes[j].status == PENDING
			)
			{
				shortest = j;
			}		
		}
		
		while (processes[shortest].status == FINISHED && shortest < proc_len - 1)
		{
			shortest += 1;
			for (size_t j = shortest + 1; j < proc_len; ++j)
			{
				if (
					processes[j].burst_time < processes[shortest].burst_time
					&& processes[j].status == PENDING
				)
				{
					shortest = j;
				}
			}
		}	
		
		for (size_t j = 0; j < proc_len; ++j)
		{
			if (j != shortest && processes[j].status == PENDING)
			{
				processes[j].waiting_time += processes[shortest].burst_time;
			}
		}
		printf("P%u ", processes[shortest].p_id);
		temp_tat += processes[shortest].burst_time;
		processes[shortest].turn_around_time = temp_tat;
		processes[shortest].status = FINISHED;
	}
	printf("%u\n\n", temp_tat);
	display_results(processes, proc_len);
}

void priority_scheduling (struct Process *processes, size_t proc_len)
{
	printf ("Gaantt Chart:\n");
	unsigned current_turn_around_time = 0;
	for (size_t i = 0; i < proc_len; ++i)
	{
		printf ("%d ", current_turn_around_time);
		unsigned highest = 0;
		for (size_t j = highest + 1; j < proc_len; ++j)
		{
			if (
				processes[j].priority < processes[highest].priority && 
				processes[j].status == PENDING
			)
			{
				highest = j;
			}
		}
		while (processes[highest].status == FINISHED)
		{
			highest += 1;
			for (size_t j = highest + 1; j < proc_len; ++j)
			{
				if (
					processes[j].priority < processes[highest].priority && 
					processes[j].status == PENDING
				)
				{
					highest = j;
				}
			}
		}
		for(size_t j = 0; j < proc_len; ++j)
		{
			if(j != highest && processes[j].status == PENDING)
			{
				processes[j].waiting_time += processes[highest].burst_time;
			}
		}
		printf("P%u ", processes[highest].p_id);
		current_turn_around_time += processes[highest].burst_time;
		processes[highest].status = FINISHED;
		processes[highest].turn_around_time = current_turn_around_time;
	}
	printf("%u\n\n", current_turn_around_time);
	display_results(processes, proc_len);
}

int finished_check(struct Process *processes, size_t len)
{
	for (size_t i=0; i < len; ++i)
	{
		if (processes[i].status == PENDING)
		{
			return 1;
		}
	}
	
	return 0;
}

void round_robin_scheduling(struct Process *processes, size_t proc_len, unsigned time_slice)
{
	unsigned temp_tat = 0;
	printf("Gaantt Chart:\n");

	while (finished_check(processes, proc_len))
	{
		for (size_t i = 0; i < proc_len; ++i)
		{
			if (processes[i].status == PENDING)
			{
				if (processes[i].time_remaining >= time_slice)
				{
					processes[i].time_remaining -= time_slice;
					for (size_t j = 0; j < proc_len; ++j)
					{
						if (j != i && processes[j].status == PENDING)
						{
							processes[j].waiting_time += time_slice;
						}
					}
					printf("%u P%u ", temp_tat, processes[i].p_id);
					temp_tat += time_slice;	
				}
				else
				{
					for (size_t j = 0; j < proc_len; ++j)
					{
						if (j != i && processes[j].status == PENDING)
						{
							processes[j].waiting_time += processes[i].time_remaining;
						}
					}
					printf("%u P%u ", temp_tat, processes[i].p_id);
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
	printf("%u\n\n", temp_tat);
	display_results(processes, proc_len);
}

int main ()
{
	printf ("Enter the number of processes: ");
	size_t proc_len;
	scanf ("%lu", &proc_len);

	struct Process *processes = (struct Process*) calloc (
		proc_len, 
		sizeof (struct Process)
	);

	printf("Enter the details of %lu processes\n", proc_len);
	for (size_t i = 0; i < proc_len; ++i)
	{
		processes[i].p_id = i + 1;
		printf ("\nProcess%d\n", processes[i].p_id);
		printf ("Burst Time -> ");
		scanf ("%u", &processes[i].burst_time);

		printf("Priority -> ");
		scanf("%u", &processes[i].priority);
	}

	unsigned exit_status = 1;
	while (exit_status)
	{
		printf(
			"1.FCFS Scheduling\n"
			"2.SJF Scheduling\n"
			"3.Priority Scheduling\n"
			"4.Round Robin Scheduling\n"
			"5.Exit\n"
			"Enter your choice: "
		);
		int choice;
		scanf ("%d", &choice);

		switch (choice)
		{
			case 1:
			{
				for (size_t i = 0; i < proc_len; ++i)
				{
					processes[i].waiting_time = 0;
					processes[i].turn_around_time = 0;
					processes[i].status = PENDING;
				}
				fcfs_scheduling(processes, proc_len);
				break;
			}

			case 2:
			{
				for (size_t i = 0; i < proc_len; ++i)
				{
					processes[i].waiting_time = 0;
					processes[i].turn_around_time = 0;
					processes[i].status = PENDING;
				}
				sjf_scheduling(processes, proc_len);
				break;
			}

			case 3:
			{
				for (size_t i = 0; i < proc_len; ++i)
				{
					processes[i].waiting_time = 0;
					processes[i].turn_around_time = 0;
					processes[i].status = PENDING;
				}
				priority_scheduling(processes, proc_len);
				break;
			}

			case 4:
			{
				for (size_t i = 0; i < proc_len; ++i)
				{
					processes[i].waiting_time = 0;
					processes[i].turn_around_time = 0;
					processes[i].time_remaining = processes[i].burst_time;
					processes[i].status = PENDING;
				}
				printf("Enter the value of time slice: ");
				unsigned time_slice;
				scanf("%u", &time_slice);
				round_robin_scheduling(processes, proc_len, time_slice);
				break;
			}

			case 5:
			{
				exit_status = 0;
				break;
			}

			default:
			{
				printf("Invalid Input\n");
			}
		}
	}
	free (processes);

	return 0;
}