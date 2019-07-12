#include <stdio.h>  
#include<iostream>
#include <unistd.h>
#include<fstream> 
#include <stdlib.h> 
#include <pthread.h> 
#include<iomanip>
#include <semaphore.h>  
#define MAX_STUDENTS 25		//no. of student threads 
using namespace std;
// FUNCTION DEFINITIONS
void *Students(void *num); 
void *TA(void *); 
void randwait(int secs);
//SEMAPHORE DEFINITIONS 
sem_t waitingRoom; 			// Limits no. of Studentss allowed  to enter the waiting room 
sem_t TAChair; 				// teacherChair ensures mutually exclusive access to the TA.
sem_t  TAPillow;			// teacherPillow is used to allow the TA to sleep until a student arrives.
sem_t  end;					// end is used to make the student to wait until the TA finishes helping student 
int allDone = 0; 			// Flag to stop the TA thread when all Studentss have been serviced.
ofstream out_data("filenew.txt");
int main(int argc, char *argv[]) 
{
	ofstream out_data("filenew.txt");
	cout<<"\n\t---THE SLEEPING TEACHER ASSISTANT PROBLEM------\n\n";
	out_data<<"\n\t---THE SLEEPING TEACHER ASSISTANT PROBLEM------\n\n";
	pthread_t btid; 
    pthread_t tid[MAX_STUDENTS]; 
    int i, x, numStudents, numChairs; int Number[MAX_STUDENTS]; 
    printf("\nEnter number of students and chairs(Max students is 25):\n");
    scanf("%d",&x);
    numStudents = x; 
    scanf("%d",&x);
    numChairs = x;
    if (numStudents > MAX_STUDENTS) { 
       printf("The maximum number of Students is %d.\n", MAX_STUDENTS); 
       system("PAUSE");    
       return 0;
    } 
    printf("\n-----A solution to the sleeping TA problem using semaphores.------\n"); 
    out_data<<"\n-----A solution to the sleeping TA problem using semaphores.------\n";
    for (i = 0; i < MAX_STUDENTS; i++) 
	{ 
        Number[i] = i; 
    } 
    // Initialize the semaphores with initial values... 
    sem_init(&waitingRoom, 0, numChairs); 
    sem_init(&TAChair, 0, 1);
    sem_init(&TAPillow, 0, 0); 
    sem_init(&end, 0, 0); 
    
    // Create the TA. 
    pthread_create(&btid, NULL, TA, NULL); 
    
    // Create the Students. 
    for (i = 0; i < numStudents; i++) 
	{
        pthread_create(&tid[i], NULL, Students, (void *)&Number[i]); 
    } 
    // Join each of the threads to wait for them to finish. 
    for (i = 0; i < numStudents; i++) { 
        pthread_join(tid[i],NULL); 
    } 
    // When all of the Studentss are finished, kill the TA thread. 
    allDone = 1; 
    sem_post(&TAPillow); // Wake the TA so he will exit. 
    pthread_join(btid,NULL); 
    system("PAUSE");    
    return 0;
} 

void *Students(void *number) 
{ 
     ofstream out_data("filenew.txt");
	 int num = *(int *)number; 					// Leave for the shop and take some random amount of  time to arrive. 
     printf("Students %d leaving for TA cabin.\n", num+1); 
     out_data<<"Students"<<num+1<<"leaving for TA cabin.\n";
     randwait(5); 
     printf("Students %d arrived at TA cabin.\n", num+1);	 // Wait for space to open up in the waiting room... 
     out_data<<"Students"<<num+1<< "arrived at TA cabin.\n";
     sem_wait(&waitingRoom); 
     printf("Students %d entering waiting room.\n", num+1); // Wait for the TA chair to become free. 
     out_data<<"Students"<<num+1<<"entering waiting room.\n";
     sem_wait(&TAChair); 			  // The chair is free so give up your spot in the  waiting room. 
     sem_post(&waitingRoom);		 // Wake up the TA... 
     printf("Students %d waking the TA.\n", num+1); 
     out_data<<"Students"<<num+1<<"waking the TA\n";
     sem_post(&TAPillow); 			// Wait for the TA to finish teaching 
     sem_wait(&end); 				// Give up the chair. 
     sem_post(&TAChair); 
     printf("Students %d leaving TA room.\n", num+1);
     out_data<<"Students"<<num+1<<" leaving TA room.\n";
} 

void *TA(void *junk) 
{    
	ofstream out_data("filenew.txt");
 	while (!allDone)
    { 						
	  printf("The TA is sleeping\n");
	  out_data<<"The TA is sleeping";  // Sleep until someone arrives and wakes you.. 
  	  sem_wait(&TAPillow); 				// Skip this stuff at the end... 
  	  if (!allDone) 
  	  { // Take a random amount of time to teach the student.
  	   printf("The TA is teaching\n"); 
  	   out_data<<"The TA is teaching\n";
  	   randwait(3);
  	   printf("The TA has finished teaching.\n"); // Release the Students when done teaching... 
  	   out_data<<"The TA has finished teaching\n";
  	   sem_post(&end); 
  	  } 
  	  else
	  { 
       printf("The TA is going home for the day.\n");
       out_data<<"The TA is going home for the day\n";
    } 
   }
}
void randwait(int secs)
{ 
     int len = 1; // Generate an arbit number...
     sleep(len); 
}
