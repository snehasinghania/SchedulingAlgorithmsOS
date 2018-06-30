#include<stdio.h>
#include <stdlib.h>
#include"simulator.h"
#include"limits.h"

int RR(struct Process* process , int count)
{
	printf("RR policy\n");
	int q = 0;
	printf("enter the quantum : ");
	scanf("%d",&q);
	

	struct Process queue[count*2+1], temp_pro, orig_pro[count+1];
	
	int rear = 0 , i = 0 , j = 0 , time = 0 , service_time[count+1]; 
	
	for( i = 1 ; i <= count ; i++) // sorting the main process array based on arrival time
	{ 
		for( j = i+1 ; j <= count ; j++)
		{		
			if(process[i].arrival_time > process[j].arrival_time)
			{
				temp_pro = process[i];
				process[i] = process[j];
				process[j] = temp_pro;
			}
		}
		orig_pro[i] = process[i];
	}	

	for( i = 1 ; i <= count ; i++)
	{
		service_time[i] = process[i].service_time;
	}	
	
	struct Process procs[100000], exe;
	
	int pro_flag = 0 , index = 0 , not_flag = 0 , fflag = 0, inin = 0;
	
	while(inin < count) // runs till all the process have been executed
	{
		for(i = 1 ; i <= count; i++) // stores the process in the queue which has arrived and still requires service
		{
			not_flag = 0; fflag = 0;
			
			if( (process[i].service_time != 0) && (process[i].arrival_time <= time) && (exe.pro_id != process[i].pro_id))
			{
				
				for(j = 0 ; j < index ; j++)
				{
					if(queue[j].pro_id == process[i].pro_id)
						not_flag = 1;
				}
				
				if(not_flag == 0)
				{
					queue[index] = process[i];
					rear = index;
					index += 1;
				}
				else
				{
					continue;
				}
				
			}
			else if((process[i].service_time != 0) && (process[i].arrival_time <= time) && (exe.pro_id == process[i].pro_id))
				fflag = 1;
		}
		
		if(fflag == 1)
		{
			queue[index] = exe;
			rear = index;
			index += 1; 
		}
		
		//printf("in queue 0 %c\n" , queue[0].pro_id);
		
		for(j = 1 ; j <= count ; j++)
		{
			if(queue[0].pro_id == process[j].pro_id)
				pro_flag = j;
			else
				pro_flag = 0;
		}
		
		for( j = 1 ; j <= q ; j++) // executes the process for q time slot
		{
			if(pro_flag != 0)
			{
				if(process[pro_flag].fin_flag == 0)
				{
					process[pro_flag].fin_flag = 1;
					process[pro_flag].start_time = time;
				}
				if (process[pro_flag].service_time != 0)
				{	
					procs[time] = process[pro_flag];
					process[pro_flag].service_time -= 1;		
					time += 1;
					//printf("servie %c %d\n", process[pro_flag].pro_id , process[pro_flag].service_time);
					if(process[pro_flag].service_time == 0)
					{
						inin += 1;
						process[pro_flag].finish_time = time;
					}
				}
				else
				{
					break;
				}
			}
		}
		
		if(rear == 0) 
		{
			index = 0;
		}	
		else
		{
			exe = queue[0];
			
			for( j = 1 ; j <= rear; j++) //this basically rearranges the queue removing the first ele which was executed
				queue[j-1] = queue[j]; 
			
			
			index = rear;
			rear -= 1;
			//printf("\n%d\n",index);
			
		}
		
		temp_pro = process[1];
		
		for(j = 2 ; j <= count ; j++)
			process[j-1] = process[j];
		
		process[count] = temp_pro;
		//printf("111hi\n");
	}
	
	printf("total time for execution is %d \n" , time);
	
	for(i = 0 ; i < time ; i++)
	{ 
		for(j = 1 ; j <= count ; j++)
		{
			if( procs[i].pro_id == orig_pro[j].pro_id ) //this checks if tha e process i was executed at time i
			{ 
				orig_pro[j].finish_time = i+1; // this will get updated every time the process got executed and the final value will be when it got finished 
				orig_pro[j].waiting_time = orig_pro[j].finish_time - orig_pro[j].service_time- orig_pro[j].arrival_time; // this will have starting waiting and intermediate waiting time
				
				//printf("wt %c  %d %d\n" ,process[j].pro_id , process[j].waiting_time, process[j].finish_time);
				
				orig_pro[j].TAT_time = (orig_pro[j].finish_time - orig_pro[j].arrival_time);
			}
		}
	}
	
	for(i = 1 ; i <= count ; i++)
	{
		for(j = 1 ; j<=count ; j++)
		{
			if(process[i].pro_id == orig_pro[j].pro_id)
				orig_pro[j].start_time = process[i].start_time;
		}
	}
	
	
	for(i = 1 ; i <= count; i++)
	{
		
	
		printf("%c\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n" , orig_pro[i].pro_id, orig_pro[i].arrival_time, orig_pro[i].service_time, orig_pro[i].priority, orig_pro[i].waiting_time, orig_pro[i].TAT_time, orig_pro[i].start_time, orig_pro[i].finish_time, orig_pro[i].fin_flag);
	}
	
	printf("schedule\n");
	for(i = 0 ; i < time ; i++)
		printf("%c ",procs[i].pro_id);
	printf("\n");
	
	float tat  = 0, wt = 0;
	int su = 0;
	for(su = 1 ; su <= count ; su++) // calculating average TAT and WT
	{
		tat += orig_pro[su].TAT_time;
		wt += orig_pro[su].waiting_time;
	}
	tat = tat/(float)count;
	wt = wt/(float)count;
	printf("\nThe average TAT and average WT is %f %f \n", tat , wt);		
}
