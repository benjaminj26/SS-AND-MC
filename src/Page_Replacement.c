#include <stdio.h>
#include <stdlib.h>

//FIFO Page Replacement Algorithm
void fifo(int *pages, int page_len, int *buffer, int buff_len)
{
	int page_hit = 0;
	int page_miss = 0;
	int first = 0;
	int current = 0;

	printf("Buffer Contents:\n");
	
	for (int i = 0; i < page_len; ++i)
	{
		int flag = 0;
		for (int j = 0; j < buff_len; ++j)
		{
			if (buffer[j] == pages[i])
			{
				page_hit++;
				flag = 1;
				break;
			}
		}
		
		if (flag == 0)
		{
			page_miss++;
			buffer[first] = pages[i];
			if (first == buff_len - 1)
			{
				first = 0;
			}
			else
			{
				first++;
			}
		}
		
		//Printing the contents of the frame buffer
		for (int j = 0; j < buff_len; ++j)
		{
			if (buffer[j] != -1)
			{
				printf("%d ", buffer[j]);
			}
		}
		printf("\n");
	}

	printf("Page Hits => %d\n", page_hit);
	printf("Page Misses => %d\n", page_miss);
}


//LRU Page Replacement Algorithm
void lru(int *pages, int page_len, int *buffer, int buff_len)
{
	int recency[buff_len];
	for (int i = 0; i < buff_len; ++i)
	{
		recency[i] = 0;
	}
	int page_hit = 0;
	int page_miss = 0;
	int least_recent;
	
	printf("Buffer Contents:\n");
	for (int i = 0; i < page_len; ++i)
	{
		least_recent = 0;
		int flag = 0;
		for (int j = 0; j < buff_len; ++j)
		{
			if (buffer[j] == pages[i])
			{
				page_hit++;
				flag = 1;
				break;
			}
		}
		
		if (flag == 0)
		{
			page_miss++;
			
			for (int j = 0; j < buff_len; ++j)
			{
				if (buffer[j] == -1)
				{
					buffer[j] = pages[i];
					flag = 1;
					break;
				}
			}
			//Finding the recency of each page in the frame buffer
			for (int j = 0; j < buff_len && flag == 0; ++j)
			{
				for (int k = i - 1; k >= 0; --k)
				{
					if (buffer[j] == pages[k])
					{
						recency[j] = k;
						break;
					}
				}
			}

			//Finding the least recently used page
			for (int j = 0; j < buff_len && flag == 0; ++j)
			{
				if (recency[least_recent] > recency[j])
				{
					least_recent = j;
				}
			}

			//Replacing the least recently used page
			if (flag == 0)
			{
				buffer[least_recent] = pages[i];
			}
		}

		//Printing the contents of the frame buffer
		for (int j = 0; j < buff_len; ++j)
		{
			if (buffer[j] != -1)
			{
				printf("%d ", buffer[j]);
			}
		}
		printf("\n");
	}

	printf("Page Hits => %d\n", page_hit);
	printf("Page Misses => %d\n", page_miss);
}


//LFU Page Replacement Algorithm
void lfu(int *pages, int page_len, int *buffer, int buff_len)
{
	int frequency[buff_len];
	for (int i = 0; i < buff_len; ++i)
	{
		frequency[i] = 0;
	}
	
	int page_hit = 0;
	int page_miss = 0;
	int least_frequent;
	
	printf("Buffer Contents:\n");
	for (int i = 0; i < page_len; ++i)
	{
		least_frequent = 0;
		int flag = 0;
		
		for (int j = 0; j < buff_len; ++j)
		{
			if (buffer[j] == pages[i])
			{
				page_hit++;
				flag = 1;
				break;
			}
		}
		
		if (flag == 0)
		{
			page_miss++;
			
			for (int j = 0; j < buff_len; ++j)
			{
				if (buffer[j] == -1)
				{
					buffer[j] = pages[i];
					flag = 1;
					break;
				}
			}
			
			for (int j = 0; j < buff_len && flag == 0; ++j)
			{
				for (int k = 0; k < i; ++k)
				{
					if (pages[k] == buffer[j])
					{
						frequency[j] += 1;
					}
				}
			}
			
			for (int j = 0; j < buff_len; ++j)
			{
				if (frequency[least_frequent] > frequency[j])
				{
					least_frequent = j;
				}
			}
			
			if (flag == 0)
			{
				buffer[least_frequent] = pages[i];
			}
		}
		
		for (int j = 0; j < buff_len; ++j)
		{
			if (buffer[j] != -1)
			{
				printf("%d ", buffer[j]);
			} 
		}
		printf("\n");
	}
	
	printf("Page Hits => %d\n", page_hit);
	printf("Page Misses => %d\n", page_miss);
}

int main()
{
	printf("Enter the number of Pages: ");	
	int page_len;
	scanf("%d", &page_len);

	int *pages = (int *)calloc(page_len, sizeof(int));
	printf("Enter %d pages:\n", page_len);
	for (int i=0; i < page_len; ++i)
	{
		scanf("%d", &pages[i]);
	}

	printf("Enter the size of page buffer: ");
	int buffer_len;
	scanf("%d", &buffer_len);
	int *buffer = (int *)calloc(buffer_len, sizeof(int));
	
	int exit_condition = 1;
	do
	{
		printf (
			"1.FIFO\n"
			"2.LRU\n"
			"3.LFU\n"
			"4.Exit\n"
			"Enter your choice: "
		);
		int choice;
		scanf("%d", &choice);
		
		switch (choice)
		{
			case 1:
			{
				for (int i=0; i < buffer_len; ++i)
				{
					buffer[i] = -1;
				}
				fifo (pages, page_len, buffer, buffer_len);
				break;
			}
			
			case 2:
			{
				for (int i=0; i < buffer_len; ++i)
				{
					buffer[i] = -1;
				}
				lru (pages, page_len, buffer, buffer_len);
				break;
			}
			
			case 3:
			{
				for (int i=0; i < buffer_len; ++i)
				{
					buffer[i] = -1;
				}
				lfu (pages, page_len, buffer, buffer_len);	
				break;
			}
			
			case 4:
			{
				exit_condition = 0;
				break;
			}
			
			default:
			{
				printf("Invalid Input\n");
			}
		}
		printf("\n");
	}while(exit_condition);
	printf("Exiting\n");
	free(pages);
	free(buffer);
	return 0;
}
