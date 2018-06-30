#include<stdio.h>
#include<stdlib.h>
#include"simulator.h"
#include"limits.h"

int* checkh(int time , struct Process* process, int num_pro) // checks if a process has arrived at the given time
{
	int li[num_pro];
	li[0] = 0;
	int i = 1 ;
	for (i = 1; i <= num_pro; i++)
	{
	
		//printf("%d %d \n",process[i].arrival_time, process[i].fin_flag);
		if(process[i].arrival_time <= time && process[i].fin_flag != 1)
		{
			li[i] = i;
			//printf("Li here %d\n" , li[i]);
		}
		else
			li[i] = 0;
	}
	
	int* ptr = li;
	return ptr;
	
}

int compute_rr(struct Process* process, int* li , int count , int time) // returns the process with highest rr and if rr is same then the process with minimum arrival time is returned
{

	int min_st_pro = 0, min_st_time = 0, i=1 , index = 0;
	float min = INT_MIN;
	float rr_new = 0;
	
	for(i=1 ; i <= count ; i++)
	{
		rr_new = (float)((time-process[i].arrival_time)+process[i].service_time)/process[i].service_time;
		//printf("li is %d  %d\n" , i, li[i]);
		if(li[i] != 0)
		{
			if(rr_new > min)
			{
				min_st_pro = i;
				min = rr_new;
				
			}
		}
	}
	
	int min_arr = process[min_st_pro].arrival_time;
	 
	for(i = 1 ; i <= count ; i++)
	{
		rr_new = (float)((time-process[i].arrival_time)+process[i].service_time)/process[i].service_time;
		if(li[i] != 0)
		{
			if(rr_new == min && process[i].arrival_time < min_arr)
			{
				min_st_pro = i;
				//printf("hello %c\n" ,process[i].pro_id);
			}
		}	
	}	
	
	//printf("st min %d\n" , min);	
	return min_st_pro;
}

void HRRN(struct Process* process , int count)
{
	printf("HRRN\n");
	int time = 0 , index = 1 , li = 0;
	while(index <= count)
	{
		int *liss;
		liss  = checkh(time, process, count);
		li = compute_rr(process,liss,count,time);
		if(li != 0) // if the process has arrived then it is executed and various parameters are recorded
		{
			//printf("hii\n");
			process[li].start_time = time;
			process[li].finish_time = time + process[li].service_time;
			process[li].waiting_time = process[li].start_time - process[li].arrival_time;
			
			process[li].TAT_time = process[li].finish_time - process[li].arrival_time;
			    
			process[li].fin_flag = 1;
			time = process[li].finish_time;
			//printf("time2 here %d\n" , time);
			index += 1;
			printf("%c\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n" , process[li].pro_id, process[li].arrival_time, process[li].service_time, process[li].priority, process[li].waiting_time, process[li].TAT_time, process[li].start_time, process[li].finish_time, process[li].fin_flag);
		}
		else
			time += 1;
		
	}
	float tat  = 0, wt = 0;
	int i = 0;
	for(i = 1 ; i <= count ; i++) // calculating the average TAT and WT
	{
		tat += process[i].TAT_time;
		wt += process[i].waiting_time;
	}
	tat = tat/(float)count;
	wt = wt/(float)count;
	printf("\nThe average TAT and average WT is %f %f \n", tat , wt);	
}
