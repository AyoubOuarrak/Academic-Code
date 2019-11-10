/* Nome Cognome  - data - versione */
/* gcc thread_utils.c -o thread_utils -pthread  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // usleep
#include <sys/time.h>  // gettimeofday
#include <pthread.h>

void options_management(int, char **) ;  // options management       
void usage(char * argv[]);    // print usage ( option -h) 
double  get_current_time();   // return current time (prec. us) 
int rnd (float prob);         // return 1 if rand > prob (prob tra 0 e 1)
void * threaded(void *p);     // 

double  ta, tb;        // ta=tempo iniziale, tb=tempo finale
int N=0,  MAX=10 ; 
int sleeptime = 1;        // secondi per sleep 
float prob = 0.8;         // succcess probabity (tra 0 e 1)

pthread_t mythread;


/////////////////////// main() //////////////////////////

int main(int argc, char **argv)
 {


 options_management(argc, argv);         /* optarg management */

 ta=get_current_time();

 while(N<MAX)   { 
      N=N+1;
     pthread_create(&mythread, NULL, threaded, (void *)&N); 
     sleep(1);  // attendi 1 secondo
   }

 tb=get_current_time();

fprintf(stdout,"# COMPLETED in %f sec  \n" ,  tb-ta);

return (0);

}

//////////////////////////////////////////////////////////////

void * threaded(void *p) {
int n = *(int *)p; 
printf ("thr%d start \n", n);
if (rnd(prob)) 
            {printf ("thr%d going to sleep .. \n",n);
             sleep(sleeptime ); 
            } 
            else printf("thr%d  don't sleep! \n",n);
printf ("thr%d stop \n", n);

}

////////////////////////// usage //////////////////////////////////////

void usage(char * argv[])  {

  printf ("\n%s [-s sleeptime] [-p prob] [-h]",argv[0]);
  printf ("\n -s <int>   : sleep time (sec) -  default = %d" , sleeptime);
  printf ("\n -p <int>   : prob (0 - 1 ) -  default = %f" , prob);
  printf ("\n -h   : help ");
  printf ("\n");

}

////////////////////////// options //////////////////////////////////////

void options_management(int argc, char * argv[]) {

  int i;
   while ( (i = getopt(argc, argv, "s:p:h")) != -1) {
        switch (i) {

        case 's':  sleeptime  = strtol(optarg, NULL, 10);  break;
		case 'p':  prob       = atof(optarg);  break;
        case 'h':  usage(argv); exit(1);
        case '?':  usage(argv); exit(1);
        default:   usage(argv); exit(1);
        }
    }
}

//////// get_current_time ()   /////////////////

double  get_current_time()
{
struct timeval tempo;

 gettimeofday(&tempo,0);              
 return tempo.tv_sec+(tempo.tv_usec/1000000.0);
}

///////////////////// rnd() ///////////////
//
// Torna 1 con probabilita' prob (tra 0 e 1 ) altrimenti 0
//

int rnd (float prob)
{
  double now=get_current_time();
  int  seed= (now-(int)now)*1000000;
  srand48 ( seed );
  float r = drand48();   
//  printf(" r=%f p=%f \n", r, prob);
  return (r < prob) ; 
}

