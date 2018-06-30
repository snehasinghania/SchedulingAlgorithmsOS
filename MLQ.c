#include<stdio.h>
#include"simulator.h"
#include"limits.h"

int MLQ(struct Process* process , int count)
{
	printf("enter the number of queues\n");
	
	int num;
	scanf("%d",&num);
	
	struct Process queue[num][count*2], temp_pro , orig_pro[count+1];
	
	int q_func[num] , up_st[num], low_st[num] ,i = 0 , j = 0, time = 0, service_time[count+1];
	
	for(i = 0 ; i < num ; i++)
	{
		printf("enter the quantum for %d queue\n" , i+1);
		scanf("%d",&q_func[i]);
	} 

	printf("enter the bound for queues such that the criteria(ST) holds for all the process\n");
	for(i = 0 ; i < num ; i++)
	{
		printf("enter the up and low service time for %d queue\n" , i+1);
		scanf("%d %d",&low_st[i] , &up_st[i]);
	} 
	
	for( i = 1 ; i <= count ; i++)
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
		//printf("hi\n");
	}	
	
	for( i = 1 ; i <= count ; i++)
	{
		service_time[i] = process[i].service_time;
	}	
	
	struct Process procs[100000], exe;
	
	int pro_flag = 0 , index[num] , rear[num] , not_flag = 0 , fflag = 0 , go_q = 0 , time_slot , k = 0 , exe_queue = 0 , pos = 1 , startted = 1;
	
	
	for(i = 0; i<num; i++)
	{
		index[i] = 0;
		rear[i] = 0;
	}
	
	for(i = 1 ; i <= count ; i++) // initializes the queue flag for each process according to the q function
	{
		for(j = 0; j < num ; j++)
		{
			if( process[i].service_time <= up_st[j] && process[i].service_time > low_st[j])
			{
				process[i].queue_flag = j;
			}
		}
	}
	int ii =1;
	
	while(ii < count) // runs till all the process have been executed
	{
		//printf("hi");
		for(i = pos ; i <= count ; i++) // this checks all the process next to the previous executed process
		{
			startted = pos;
			not_flag = 0, fflag = 0;
			
			
			if( (process[i].service_time != 0) && (process[i].arrival_time <= time) && (exe.pro_id != process[i].pro_id))
			{
				
				//printf(" process got %c\n", process[i].pro_id);
				go_q = process[i].queue_flag;
				
				
				for(j = 0 ; j < index[go_q] ; j++)
				{
					if(queue[go_q][j].pro_id == process[i].pro_id)
						not_flag = 1;
				
				}
				
				if(not_flag == 0)
				{
					queue[go_q][index[go_q]] = process[i];
					rear[go_q] = index[go_q];
					index[go_q] += 1;

				}
			
			}
			else if((process[i].service_time != 0) && (process[i].arrival_time <= time) && (exe.pro_id == process[i].pro_id))
				fflag = 1;
		
		}
		if(startted > 1) // this checks all the process previous to the previous executed process
		{
			for(i = 1 ; i < startted ; i++)
			{
				not_flag = 0, fflag = 0;
			
			
				if( (process[i].service_time != 0) && (process[i].arrival_time <= time) && (exe.pro_id != process[i].pro_id))
				{
				
					//printf(" process got %c\n", process[i].pro_id);
					go_q = process[i].queue_flag;
				
				
					for(j = 0 ; j < index[go_q] ; j++)
					{
						if(queue[go_q][j].pro_id == process[i].pro_id)
							not_flag = 1;
				
					}
				
					if(not_flag == 0)
					{
						queue[go_q][index[go_q]] = process[i];
						rear[go_q] = index[go_q];
						index[go_q] += 1;

					}
			
				}
				else if((process[i].service_time != 0) && (process[i].arrival_time <= time) && (exe.pro_id == process[i].pro_id))				fflag = 1;
			}
		}
		
		if(fflag == 1) // stores the previously executed process if it requires more service
		{
			go_q = exe.queue_flag;
			
			
			queue[go_q][index[go_q]] = exe;
			rear[go_q] = index[go_q];
			index[go_q] += 1;
		}

		for(i = 0 ; i < num ; i++) // executes the process in the highest priority queue
		{
			if(index[i] != 0)
			{
				for(j = 1 ; j <= count ; j++)
				{
					if(queue[i][0].pro_id == process[j].pro_id)
						pro_flag = j;
				}
				
				if(process[pro_flag].fin_flag == 0)
				{
					process[pro_flag].fin_flag = 1;
					process[pro_flag].start_time = time;
				}
			
				if (process[pro_flag].service_time != 0)
				{	
				
					go_q = process[pro_flag].queue_flag;
									
					if(process[pro_flag].service_time >= q_func[go_q])
						time_slot = q_func[go_q];
					else
						time_slot = process[pro_flag].service_time;
						
					//procs[time] = process[pro_flag];
					
					process[pro_flag].service_time -= time_slot;		
					
					//if(process[pro_flag].service_time == 0)
					//	ii += 1;
					
					for(k = time ; k < (time+time_slot) ; k++)
						procs[k] = process[pro_flag];
					
					time += time_slot;
					
					exe_queue = i;
					exe = queue[exe_queue][0];
					
					if(process[pro_flag].service_time == 0)
					{
						process[pro_flag].finish_time = time;
						ii += 1;
					}
					
					for(k = 1 ; k <= count ; k++)
					{
						if(process[k].pro_id == exe.pro_id)
							pos = (k%count) + 1;
											
						
					}
					
					break;
				}
				
				
			}
		}		
		
		
		
		
		
		for( j = 1 ; j <= rear[exe_queue] ;  j++) // delete the first element from queue from which the process was exexuted
			queue[exe_queue][j-1] = queue[exe_queue][j];
		
		index[exe_queue] = rear[exe_queue];
		rear[exe_queue] -= 1;
		
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
