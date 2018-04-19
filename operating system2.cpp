#include<stdio.h>
#include<unistd.h>
int wat1=0,total_teacher=0,wat2=0; //wat=waiting time, totalteacher process brust time
int tat1=0,tat2=0;
int main()
{
    int brust_time1[10],brust_time2[10];
    int arrival_time1[20],arrival_time2[20];
    int n,n1;
    int i,j;
    printf("\nEnter no of student process");
    scanf("%d",&n);
    printf("\nEnter no of teacher process");
    scanf("%d",&n1);
    printf("\nEnter arrival time of student");
    for(i=0;i<n;i++)
	{
		scanf("%d",&arrival_time1[i]);
	}
	printf("\nEnter arrival time of teacher(arrival Time of teacher<student)");
	for(i=0;i<n1;i++)
	{
		scanf("%d",&arrival_time2[i]);
	}
         
    printf("\nEnter brust time for student process");
    for(i=0;i<n;i++)
    {
    	scanf("%d",&brust_time1[i]);
	}
	printf("\nEnter teacher process brust time");
	for(i=0;i<n1;i++)
	{
		scanf("%d",&brust_time2[i]);
	}
	int priority_student[20],priority_teacher[20];
	printf("\nEnter priority of student(priority of student(all student haave same prioirty)< priority of teacher(All teacher have same priority))");
	for(i=0;i<n;i++)
	{
		scanf("%d",&priority_student[i]);
	}
	printf("\nEnter teacher priority of teacher");
	for(i=0;i<n;i++)
	{
		scanf("%d",&priority_teacher[i]);
	}
	
	int wait_time1[20],wait_time2[20];
	int turn_time1[20],turn_time2[20];//tuenaround time for student and teacher deleceration

	printf("\nStudent1 is in process and next person has to wait because he is in runing Queue");
	sleep(4);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n1;j++)
		{
			if(priority_teacher[j]<priority_student[i])//heigher number has low priority
			{
				printf("\nAll Teacher have heigher priority rather than Student");
			}
		}
	}
	printf("\nTeacher is in process and next teachare and student have to wait\n");
	sleep(4);
	printf("\nFrist teacher is compeleted process successfuly and now next Teacher is in process(teacher priority>student)\n");
	/* for teacher process we calculate turnariund time and waiting time because teachr has heigher priority*/
	int t=brust_time1[0];
	for(i=0;i<n1;i++)
	{  
	 t+=brust_time2[i-1];
	 wait_time2[i]=t;	//student1 is already on counter so he will frist server after that all teacher serve
	 turn_time2[i]=brust_time2[i]+wait_time2[i];// wait_time=tat-brust_time ->tat=wait_time+brust_time
	 tat2=tat2+turn_time2[i];
	 total_teacher=total_teacher+brust_time2[i];    // calculating total time taken by all teacher
	 wat2+=wait_time2[i]; 
	 
	}
	/* after finish all teacher next studnet has to serve on book counter*/
	//calculation for student process turnaround time and waiting time
	//student1 is already processed
	wait_time1[0]=0;//student0 is arrived frist at libary counter

	for(i=1;i<n;i++)
	{
		total_teacher+=brust_time1[i-1];
		wait_time1[i]=total_teacher;
	    wat1=wat1+wait_time1[i];
	}
	
	turn_time1[0]=brust_time1[0];//truntime=bruttime+waiting  waittime for student0 is 0
	for(i=1;i<n;i++)
	{
		turn_time1[i]=brust_time1[i]+wait_time1[i];
	    tat1=tat1+turn_time1[i];
	}		
     
	printf("\nTeachers\tArrivaltime2\tBrust_time2\tWait_time2\tTurnAtime2");
	for(i=0;i<n;i++)
	 printf("\nT[%d]\t\t%d\t\t%d\t\t%d\t\t%d",i+1,arrival_time2[i],brust_time2[i],wait_time2[i],turn_time2[i]);	
	
	
	
	printf("\nStudents\tArrivaltime1\tBrust_time1\tWait_time1\tTurnAtime");
	for(i=0;i<n;i++)
	 printf("\nS[%d]\t\t%d\t\t%d\t\t%d\t\t%d",i+1,arrival_time1[i],brust_time1[i],wait_time1[i],turn_time1[i]);
	 
   
    printf("\nAverage waiting time for Teacher is:%d",wat2/n1);
    printf("\nAverage TurnAroundTime for Teacheris:%d",tat2/n1);
    printf("\nAverage time of student wait is:%d",wat1/n);
    printf("\nAverage turnAroundTime for Student is:%d",tat1/n);
    
}
