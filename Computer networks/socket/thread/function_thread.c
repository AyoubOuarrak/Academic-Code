// Nome Cognome  - data - versione
// Il programma e' suddiviso in diverse unita' funzionali gestite da diversi thread.
// In questo esempio abbiamo un processo  interattivo e 2  unita' f1, f2.
// gcc function_thread.c -o function_thread -pthread  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // usleep
#include <sys/time.h>  // gettimeofday
#include <pthread.h>

void * f1(void *p);     // Thread f1
void * f2(void *p);     // Thread f2

pthread_t mythread1;
pthread_t mythread2;

/////////////////////// main() //////////////////////////

int main(int argc, char **argv) {
   int S1 = 12;
   int S2 = 20;

   pthread_create(&mythread1, NULL, f1, (void *)&S1); 
   pthread_create(&mythread2, NULL, f2, (void *)&S2); 

   char answ[20]; 

   do {
      printf("Prompt> ");
      fgets(answ,20,stdin);
   } while (answ[0]!='Q' && answ[0]!='q');

   printf("Wait for threads..\n");
   pthread_join(mythread1, NULL); 
   pthread_join(mythread2, NULL); 
   printf("Threads finished. Exiting\n");

   return (0);
}

//////////////////////////////////////////////////////////////

void * f1(void *p) {
   int n = *(int *)p; 
   printf ("F1  start. Going to sleep for %d seconds \n", n);
   sleep(n); 
   printf ("F1 stop. \n", n);
   return (0); 
}

//////////////////////////////////////////////////////////////

void * f2(void *p) {
   int n = *(int *)p;
   printf ("F2  start. Going to sleep for %d seconds \n", n);
   sleep(n);
   printf ("F2 stop. \n", n);
   return (0);
}

