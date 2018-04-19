#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
void *fun1();
void *fun2();
void *fun3();
void *teacher();
int question_paper=1;//shared Resource
int paper=1;//shared Resource
sem_t s;
int main()
{
	sem_init(&s,0,1);
	pthread_t th;
    printf("\nTeacher process is assigne work to student prosess in such a way 2 resource are shared Question_paper and paper");

    pthread_create(&th,NULL,teacher,NULL);
    pthread_join(th,NULL);
 
    printf("\n After Successfully compeleted All process value of shared Resources Question_papaer and Paper is\t%d\t%d\n",question_paper,paper);
	return 0;	
}

void *teacher()
{   
    pthread_t th1,th2,th3;
    printf("\nStudent_1 process created Successfully:thread1");
	printf("\nStudent_2 process created Succesfully:thread2");
	printf("\nStudent_3 process create  Successfully:thread3\n");
	pthread_create(&th1,NULL,fun1,NULL);
	pthread_create(&th2,NULL,fun2,NULL);
	pthread_create(&th3,NULL,fun3,NULL);
	
	pthread_join(th1,NULL);
       
	pthread_join(th2,NULL);
       
	pthread_join(th3,NULL);
   

}




void *fun1()
{
	sem_wait(&s); // locking semphore variable so  thread1 can enter in critical Sction
	printf("\nStudent_1 is entring in Crictial section:\n");
	int pen=1;//not shared resource
	int a=question_paper;
	a=a+1;
	int b=paper;
	b=b+1;
	printf("\nStudent_1 has 3 things Question_Paper,Paper and pen:\n");
	printf("\ndoing work....\n");
	sleep(10);
	question_paper=a;
	paper=b;
        printf("\nStudent_1 has done Successfully His Assigment and transfering Question_paper and paper to Next Student:\n");
        printf("\njust Exiting...\n");
        sleep(5);
	sem_post(&s);//unlock semphore varible for use other process
}
 void *fun2()
 {
 	sem_wait(&s);//locking semphore varible
 	printf("\nStudent_2 is Entering in Crictial Section Others Need To Wait:\n");
 	int pen=1; //pen resource is already avialiable
 	int a=question_paper;
 	a=a+1;
 	int b=paper;
 	b=b+1;
 	printf("\nStudent_2 has 3 things Question_paper,paper and pen:");
 	printf("\ndoing work...\n");
 	sleep(8);
 	question_paper=a;
 	paper=b;
        printf("\nStudent_2 has done Successfully his Assigment and transfering his Resources to next Student:\n");
        printf("\njust Exiting...\n");
        sleep(5);
 	sem_post(&s);
 	
 	
 }
 void *fun3()
 {
 	sem_wait(&s);
 	printf("\nStudent_3 is Entering in Crictial Section:\n");
 	int pen=1;
 	int a=question_paper;
 	a=a-2;
 	int b=paper;
 	b=b-2;
 	printf("\nStudent_3 has 3 things Question_paper,Paper and pen:");
        printf("\ndoing work...\n");
 	sleep(10);
 	question_paper=a;
 	paper=b;
        printf("\nStudent_3 is compeleted his Assigment  Successfully:\n");
        printf("\njust Exiting...\n");
        sleep(5); 
 	sem_post(&s);
 }









