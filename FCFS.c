#include<stdio.h>
#include"simulator.h"
#include"limits.h"

int* checkarr(int time , struct Process* process, int num_pro) // checks if a process has arrived at the given time
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

int min_arr(struct Process* process, int* li , int count) // finds the process with minimum arrival time among the arrived processes
{
	int min_st_pro = 0, min_st_time = 0, i=1;
	int min = INT_MAX;
	for(i=1 ; i <= count ; i++)
	{
		//printf("li is %d  %d\n" , i, li[i]);
		if(li[i] != 0)
		{
			if(process[i].arrival_time < min)
			{
				min_st_pro = i;
				min = process[i].arrival_time;
				//printf("st min %d\n" , min_st_pro);
			}
		}
	}
	//printf("st min %d\n" , min_st_pro);	
	return min_st_pro;
}


void FCFS(struct Process* process , int count)
{
	
	printf("FCFS\n");
	int time = 0, index  = 1,li = 0 ;
	while(index <= count)
	{
		int *liss;
		//li  = check(time, process, count);
		liss  = checkarr(time, process, count);
		li = min_arr(process,liss,count);
		if(li != 0) // if the process has arrived then it is executed and various parameters are recorded
		{
			
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
		//index += 1;
	}
	float tat  = 0, wt = 0;
	int i = 0;
	for(i = 1 ; i <= count ; i++)  // calculating the average TAT and WT
	{
		tat += process[i].TAT_time;
		wt += process[i].waiting_time;
	}
	 tat = tat/(float)count;
	 wt = wt/(float)count;
	 printf("\nThe average TAT and average WT is %f %f \n", tat , wt);
	 

}

