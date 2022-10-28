#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort (int *array, int len)
{
	for (int i = 1; i < len; ++i)
	{
		int value = array[i];
		int j;
		for (j = i - 1; j >= 0 && array[j] > value; --j)
		{
			array[j + 1] = array[j];
		}
		array[j + 1] = value;
	}
}

void fcfs (int *requests, int req_len)
{
	int total_distance = 0;
	
	printf ("\nEnter the initial position: ");
	int initial_position;
	scanf ("%d", &initial_position);
	
	for (int i = 0; i < req_len; ++i)
	{
		total_distance += abs (initial_position - requests[i]);
		initial_position = requests[i];
	}
	
	printf ("Total Distance Covered => %d Cylinders\n\n", total_distance);
}

void scan (int *requests, int req_len)
{
	int total_distance = 0;
	
	printf ("\nEnter the initial position: ");
	int initial_position;
	scanf ("%d", &initial_position);
	
	printf("Enter the total number of cylinders: ");
	int total_cylinders;
	scanf("%d", &total_cylinders);
	
	int *sorted = (int *) calloc (req_len, sizeof (int));
	
	memmove (sorted, requests, (req_len * sizeof (int)) );
	sort (sorted, req_len);
	
	if (initial_position <= sorted[0])
	{
		total_distance += abs (initial_position - requests[req_len - 1]);
	}
	else
	{
		total_distance += abs ( initial_position - (total_cylinders - 1) );
		total_distance += abs (sorted[0] - (total_cylinders - 1) );
	}
	
	printf ("\nTotal Distance Covered => %d Cylinders\n\n", total_distance);
	
	free (sorted);
}

void c_scan (int *requests, int req_len)
{
	int total_distance = 0;
	
	printf ("\nEnter the initial position: ");
	int initial_position;
	scanf ("%d", &initial_position);
	
	printf("Enter the total number of cylinders: ");
	int total_cylinders;
	scanf("%d", &total_cylinders);
	
	int *sorted = (int *) calloc (req_len, sizeof (int));
	memmove (sorted, requests, (req_len * sizeof (int)) );
	sort (sorted, req_len);
	
	if (initial_position <= sorted[0])
	{
		total_distance += abs (initial_position - requests[req_len - 1]);
	}
	else
	{
		int final_position;
		for (int i = 0; i < req_len; ++i)
		{
			if (sorted[i] < initial_position)
			{
				final_position = sorted[i];
			}
			else
			{
				break;
			}
		}
	
		total_distance += abs ( initial_position - (total_cylinders - 1) );
		total_distance += abs (total_cylinders - 1);
		total_distance += abs (final_position);
	}
	
	printf("Total Distance Covered => %d Cylinders\n\n", total_distance);
	
	free (sorted);
}

int main()
{
	int req_len;
	printf ("Enter the number of requests: ");
	scanf ("%d", &req_len);
	
	int *requests = (int *) calloc (req_len, sizeof (int));
	
	printf ("Enter %d request positions:\n", req_len);
	
	for (int i = 0; i < req_len; ++i)
	{
		scanf ("%d", &requests[i]);
	}
	
	int exit = 1;
	
	while (exit)
	{
		printf(
			"1.FCFS\n"
			"2.SCAN\n"
			"3.C-SCAN\n"
			"4.Exit\n"
			"Enter your choice: "
		);
		
		int choice;
		scanf("%d", &choice);
		
		switch (choice)
		{
			case 1:
			{
				fcfs (requests, req_len);
				break;
			}
			
			case 2:
			{
				scan (requests, req_len);
				break;
			}
			
			case 3:
			{
				c_scan (requests, req_len);
				break;
			}
			
			case 4:
			{
				exit = 0;
				break;
			}
			
			default:
			{
				printf("Invalid Input\n");
			}
		}
	}
	free (requests);
	
	return 0;
}
