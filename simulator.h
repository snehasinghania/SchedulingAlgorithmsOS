#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

struct Process
{
	char pro_id ;
	int arrival_time ;
	int service_time;
	int priority ;
	int waiting_time;
	int TAT_time ;
	int start_time;
	int finish_time;
	int start_flag; 
	int fin_flag ;
	int queue_flag;
	
};
#endif
