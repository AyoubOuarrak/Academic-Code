/* Nome Cognome   -   data  - versione  */
/* gcc timeout_utils.c -o timeout_utils */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // usleep
#include <signal.h>    // signal
#include <sys/time.h>  // gettimeofday

void options_management(int, char **) ;  // options management       
void usage(char * argv[]);    // print usage ( option -h) 
void handler_int(int sig);    // signal ctrl/C  handler   
void handler_alrm(int sig);   // signal ALARM handler     
double  get_current_time();   // return current time (prec. us) 

double  ta, tb;        // ta=tempo iniziale, tb=tempo finale
int N=0,  MAX=10 ; 
int sleeptime = 1;       // sleep 
int timeout = 2;         // 2 secondi


/////////////////////// main() //////////////////////////

int main(int argc, char **argv)
 {

 signal(SIGALRM, handler_alrm); // Timeout
 signal(SIGINT,  handler_int);  // ctrl/c

 options_management(argc, argv);         /* optarg management */

 alarm(timeout);   // setta il timer (1 secondo)

 ta=get_current_time();

 while(N<MAX)   { 
            printf ("%d going to sleep .. \n ",N++);
            sleep(sleeptime); 
            } 
  
 tb=get_current_time();

fprintf(stdout,"# COMPLETED in %f sec  \n" ,  tb-ta);

return (0);

}

//////////////////////////////////////////////////////////////

////////////////////////// usage //////////////////////////////////////

void usage(char * argv[])  {

  printf ("\n%s [-s sleeptime] [-t timeout]  [-r] [-h]",argv[0]);
  printf ("\n -s <int>   : sleep time (sec) -  default = %d" , sleeptime);
  printf ("\n -t <int>   : timeout (sec) -  default = %d", timeout );
  printf ("\n -h   : help ");
  printf ("\n");

}

////////////////////////// options //////////////////////////////////////

void options_management(int argc, char * argv[]) {

  int i;
   while ( (i = getopt(argc, argv, "s:t:h")) != -1) {
        switch (i) {

        case 's':  sleeptime  = strtol(optarg, NULL, 10);  break;
        case 't':  timeout    = strtol(optarg, NULL, 10);  break;
        case 'h':  usage(argv); exit(1);
        case '?':  usage(argv); exit(1);
        default:   usage(argv); exit(1);
        }
    }
}

///////////////// signal handlers  ///////////////////

void handler_int(int sig) {
   printf("\nSIGINT\n");  //ctrl/C
   exit (-1);
 }

 void handler_alrm(int sig) {
    printf("\nSIGALRM\n");  //Time_out
//  N=0;
//  alarm(timeout);   // setta nuovamente il timer
    return;
 }

//////// get_current_time ()   /////////////////

double  get_current_time()
{
struct timeval tempo;

 gettimeofday(&tempo,0);              
 return tempo.tv_sec+(tempo.tv_usec/1000000.0);
}


