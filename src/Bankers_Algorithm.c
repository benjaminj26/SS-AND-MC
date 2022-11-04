#include <stdio.h>
#include <stdlib.h>

struct Process
{
	int p_id;
	int *allocated;
	int *max;
	int *need;
	int finished;
};

int finished_check (struct Process *processes, int proc_len)
{
	for (int i = 0; i < proc_len; ++i)
	{
		if (! processes[i].finished)
		{
			return 1;
		}
	}
	
	return 0;
}

int need_check (struct Process *process, int *available, int res_len)
{
	for (int i = 0; i < res_len; ++i)
	{
		if (process->need[i] > available[i])
		{
			return 0;
		}
	}
	
	return 1;
}

void add_to_available (struct Process *process, int *available, int res_len)
{
	for (int i = 0; i < res_len; ++i)
	{
		available [i] += process -> allocated [i];
	}
}

int main()
{
	printf ("Enter the number of processes: ");
	int proc_len;
	scanf ("%d", &proc_len);
	struct Process *processes = (struct Process*) calloc (proc_len, sizeof (struct Process));
	
	printf("Enter the number of resources: ");
	int res_len;
	scanf ("%d", &res_len);
	
	printf ("\nAllocation Matrix\n");
	for (int i = 0; i < proc_len; ++i)
	{
		processes[i].p_id = i + 1;
		processes[i].allocated = (int *) calloc (res_len, sizeof (int));
		processes[i].max = (int *) calloc (res_len, sizeof (int));
		processes[i].need = (int *) calloc (res_len, sizeof (int));
		processes[i].finished = 0;
		
		printf ("Process P%d\n", processes[i].p_id);
		
		for (int j = 0; j < res_len; ++j)
		{
			printf ("Resource %d: ", j + 1);
			scanf ("%d", &processes[i].allocated[j]);
		}
		
		printf ("\n");
	}
	
	printf ("Maximum Requirement Matrix\n");
	for (int i = 0; i < proc_len; ++i)
	{
		printf ("Process P%d\n", processes[i].p_id);
		
		for (int j = 0; j < res_len; ++j)
		{
			printf ("Resource %d: ", j + 1);
			scanf ("%d", &processes[i].max[j]);
		}
		
		printf ("\n");
	}
	
	for (int i = 0; i < proc_len; ++i)
	{
		for (int j = 0; j < res_len; ++j)
		{
			processes[i].need[j] = processes[i].max[j] - processes[i].allocated[j];
		}
	}
	
	printf ("\nNeed Matrix\n");
	
	for (int i = 0; i < proc_len; ++i)
	{
		printf ("P%d ", processes[i].p_id);
		
		for (int j = 0; j < res_len; ++j)
		{
			printf ("%d ", processes[i].need[j]);
		}
		printf ("\n");
	}
	
	printf ("\nEnter the number of instances available for each resource\n");
	int available [res_len];
	
	for (int i = 0; i < proc_len; ++i)
	{
		printf ("Resource %d: ", i + 1);
		scanf ("%d", &available[i]);
	}
	
	int *safe_sequence = (int*) calloc (proc_len, sizeof (int));
	for (int i = 0; i < proc_len; ++i)
	{
		safe_sequence [i] = -1;
	}
	int iterator = 0;
	int safe_status = 1;
	
	int flag;
	while (finished_check (processes, proc_len))
	{
		flag = 0;
		for (int i = 0; i < proc_len; ++i)
		{
			if ((! processes [i].finished) && need_check (&processes[i], available, res_len))
			{
				flag = 1;
				add_to_available (&processes [i], available, res_len);
				processes [i].finished = 1;
				safe_sequence [iterator++] = processes[i].p_id;
			}
		}
		
		if (flag == 0)
		{
			printf ("\nSafe Sequence does not exist\n");
			safe_status = 0;
			break;
		}
	}
	
	if (safe_status)
	{
		printf ("\nThe safe sequence is\n");
		for (int i = 0; i < proc_len; ++i)
		{
			if (i != proc_len - 1)
			{
				printf ("P%d -> ", safe_sequence [i]);
			}
			else
			{
				printf ("P%d\n", safe_sequence [i]);
			}
		}
	}
	
	
	for (int i = 0; i < proc_len; ++i)
	{
		free (processes[i].allocated);
		free (processes[i].max);
		free (processes[i].need);
	}

	free (processes); 
	free (safe_sequence);
	
	return 0;
}
