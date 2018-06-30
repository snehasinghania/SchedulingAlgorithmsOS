#include<stdio.h>
#include <stdlib.h>
#include"simulator.h"
#include"limits.h"

int SRTN(struct Process* process , int count)
{
	printf("SRTN\n");
	int i = 0 , j = 0 , time = 0 , service_time[count+1];
	
	service_time[0] = 0;
	
	struct Process temp;
	
	for( i = 1 ; i <= count ; i++) // sorting the main process array based on arrival time
	{ 
		for( j = i+1 ; j <= count ; j++)
		{		
			if(process[i].arrival_time > process[j].arrival_time)
			{
				temp = process[i];
				process[i] = process[j];
				process[j] = temp;
			}
		}
	}	

	for( i = 1 ; i <= count ; i++)
	{
		service_time[i] = process[i].service_time;
	}	
	
	int procs[100000] , pro_flag = 0 , index = 0;
	
	while(index < count) // runs till all the process have been executed
	{
		int max = INT_MAX;
		
		pro_flag = 0;
		for(i = 1 ; i <= count; i++) // stores the process in the queue which has arrived and still requires service
		{
			if( (process[i].service_time != 0) && (process[i].arrival_time <= time) && process[i].service_time < max)
			{	
				max = process[i].service_time;
				pro_flag = i;
				if(process[i].start_flag == 0)
				{
					process[i].start_flag = 1;
					process[i].start_time = time;	
				}	
			}
			
		}
		if(pro_flag != 0)
		{
			process[pro_flag].service_time -= 1; // this basically means that this process has been executed for one time slot
			procs[time] = pro_flag;  // stores the index of the process which was executed
		}
		time += 1;
		
		if(process[pro_flag].service_time == 0)
		{
			process[pro_flag].finish_time = time;
			index += 1;
		
		}
	}
	
	printf("total time for execution is %d \n" , time);
	
	for(i = 0 ; i < time ; i++)
	{ 
		for(j = 1 ; j <= count ; j++)
		{
			if( procs[i]== j ) //this checks if tha e process i was executed at time i
			{ 
				process[j].finish_time = i+1; // this will get updated every time the process got executed and the final value will be when it got finished 
				process[j].waiting_time = process[j].finish_time - service_time[j] - process[j].arrival_time; // this will have starting waiting and intermediate waiting time
				
				
				process[j].TAT_time = (process[j].finish_time - process[j].arrival_time) + 1 ;
			}
		}
	}
	
	
	
	for(i = 1 ; i <= count; i++)
	{
		printf("%c\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n" , process[i].pro_id, process[i].arrival_time, service_time[i], process[i].priority, process[i].waiting_time, process[i].TAT_time, process[i].start_time,process[i].finish_time, process[i].fin_flag);
	}
		
	printf("schedule\n");
	for(i = 0 ; i < time ; i++)
	{
		if(procs[i] > 0)
			printf("%c ",process[procs[i]].pro_id);
	}
	printf("\n");

	float tat  = 0, wt = 0;
	int su = 0;
	for(su = 1 ; su <= count ; su++) // calculating the average TAT and WT
	{
		tat += process[su].TAT_time;
		wt += process[su].waiting_time;
	}
	tat = tat/(float)count;
	wt = wt/(float)count;
	printf("\nThe average TAT and average WT is %f %f \n", tat , wt);
}
