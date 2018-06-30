#include <stdio.h>
#include"simulator.h"
#include"FCFS.c"
#include"SJF.c"
#include"Priority.c"
#include"HRRN.c"
#include"SRTN.c"
#include"RR.c"
#include"MLQ.c"
#include"MLFQ.c"

int main()
{

	FILE * fp;
	char c;
	size_t len = 0;
	ssize_t read;
	int no_of_process,index=0;
	
	int i = 0,j = 0,k=0;
	
	fp = fopen("input.txt", "r");
	printf("enter the number of process\n");
	scanf("%d",&no_of_process);
	char a[8];
	
	int input;
	//char* arr[8]  = {"FCFS\n" , "SJF" , "PRIORITY" , "HRRN" ,"SRTN" , "RR" , "MLQ", "MLFQ"};
	char line[100];
	
	struct Process pro_ar[no_of_process+1];
	
	printf("Enter the process_id , arrival_time , service_time and priority for each process\n");

	for(k = 0 ; k < no_of_process ; k++)
	{
		//scanf("%c%d%d%d",&pro_ar[k+1].pro_id, &pro_ar[k+1].arrival_time, &pro_ar[k+1].service_time, &pro_ar[k+1].priority);

		fgets(line, 80, fp);	
		sscanf (line, "%c%d%d%d", &pro_ar[k+1].pro_id, &pro_ar[k+1].arrival_time, &pro_ar[k+1].service_time, &pro_ar[k+1].priority);
		pro_ar[k+1].waiting_time = 0;
		pro_ar[k+1].TAT_time  = 0;
		pro_ar[k+1].start_time = 0;
		pro_ar[k+1].finish_time = 0; 
		pro_ar[k+1].fin_flag  = 0;
		pro_ar[k+1].start_flag = 0;
		pro_ar[k+1].queue_flag = -1;
	
	}
	printf("PID\tAT\tST\tP\tWT\tTAT\tStT\tFT\n");
	for(k = 0 ; k < no_of_process ; k++)
	{
		printf("%c\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n" , pro_ar[k+1].pro_id, pro_ar[k+1].arrival_time, pro_ar[k+1].service_time,pro_ar[k+1].priority,pro_ar[k+1].waiting_time, pro_ar[k+1].TAT_time, pro_ar[k+1].start_time, pro_ar[k+1].finish_time,pro_ar[k+1].fin_flag);
	
	}
	
	fclose(fp);
	i = 0;
	
	char* policy;
	printf("Choose the policy: FCFS , SJF , PRIORITY , HHRN , SRTN , RR , MLF , MLFQ\n");
	printf("enter 1,2,3,4,5,6,7,8 for the corresponding policies\n");
	
	scanf("%d", &input);
	//printf("%s\n",arr[0]);
	
	if(input == 1)
		FCFS(pro_ar ,no_of_process);	
	else if(input == 2)	
		SJF(pro_ar ,no_of_process);
	
	else if(input == 3)	
		Priority(pro_ar ,no_of_process);
		
	else if(input == 4)	
		HRRN(pro_ar ,no_of_process);
		
	else if(input == 5)	
		SRTN(pro_ar ,no_of_process);
		
	else if(input == 6)	
		RR(pro_ar ,no_of_process);
	
	else if(input == 7)	
		MLQ(pro_ar ,no_of_process);
			
	else 
		MLFQ(pro_ar ,no_of_process);
	return 0;
}
