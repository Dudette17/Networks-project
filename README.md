# OS project

The sleeping teacher assistant problem is a classical example for inter process communication and process synchronization. 
There is a teaching assistant (TA) that holds office hours where they provide help to undergraduate students with their programming assignments.
The TA's office is rather small, and only has room for one desk with a chair and a computer. There are three chairs outside the office where students may sit and wait if the TA is currently helping another student. 
If there are no available chairs in the waiting area, the student shows up at a later time. 
When the TA has finished helping a student, she goes outside to the waiting area to see if there are waiting students.
If so, she takes the next student and begins to help them.
If there are no waiting students, she returns to her chair in he office and takes a nap. 
If a student shows up and sees the TA sleeping, they sit in her chair and wake her up.

A semaphore solution:
A simple solution is by the use of following:
- The mutex lock for controlling access to the chairs. (This of course can be simplified by keeping track of the number of waiting students which roughly resembles the number of students sitting in chairs.) 
- A semaphore for signalling the sleeping TA that a student has shown up. 
- A semaphore for signalling a waiting student that the TA can now help them. 
