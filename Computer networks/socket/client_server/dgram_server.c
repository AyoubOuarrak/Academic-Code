// Ayoub Ouarrak - 26/11/2014
// Summary: The Server wait for datagrams from the clients
// gcc dgram_server.c -o dgram_server 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // usleep
#include <signal.h>    // signal
#include <sys/time.h>  // gettimeofday

// net
#include <netdb.h>     //inaddr
#include <arpa/inet.h>
#include <sys/socket.h>
#include <strings.h>   // bzero

void options (int, char**) ;   // options management       
void usage (char* argv[]);     // print usage ( option -h) 
void handler_int (int sig);    // signal ctrl/C  handler   
void handler_alrm (int sig);   // signal ALARM handler     
double get_current_time ();    // return current time (prec. us) 
int rnd (float prob);           // return 1 if rand > prob (prob tra 0 e 1)
// Net
int net_open_srv ();               //
int net_close_srv ();              //
int net_open_cli ();               //
int net_close_cli ();              //
int net_send (int sockfd, void* msg, int N) ; 
int net_recv (int sockfd, void* msg) ;  

double  ta, tb;          // ta=tempo iniziale, tb=tempo finale
int sleeptime = 500000;  // microsecondi per usleep 
int timeout = 2;         // 2 secondi
float prob = 0.8;          // succcess probabity (tra 0 e 1)

// Net
int port = 25028 ;
char  server[20] = "localhost"; 
int bufsize = 1000; 

/////////////////////// main() //////////////////////////

int main (int argc, char **argv) {
   int ReturnLen; 
   int socket; 

   signal (SIGALRM, handler_alrm); // Timeout
   signal (SIGINT,  handler_int);  // ctrl/c
   options (argc, argv);         /* optarg management */
 
   char* DataBuf = (char*)malloc (bufsize);
   socket = net_open_srv (); 

   ta = get_current_time ();

   while (1) { 
      ReturnLen = net_recv (socket, DataBuf); 
      ReturnLen = net_send (socket, DataBuf, bufsize);
      printf ("-------------------------------------"); 
   }

   tb = get_current_time ();
   fprintf (stdout,"# COMPLETED in %f sec  \n",  tb-ta);
   net_close_srv ();

   return (0);
}

////////////////////////// usage //////////////////////////////////////

void usage (char * argv[])  {
   printf ("\n -p <int>   : port -  default = %d" , port);
   printf ("\n -b <int>   : bufsize - default = %d" , bufsize);
   printf ("\n -h   : help ");
   printf ("\n");
}

////////////////////////// options //////////////////////////////////////

void options (int argc, char * argv[]) {
   int i;
   while ((i = getopt (argc, argv, "n:p:h")) != -1) {
      switch (i) {		
         case 'p':  port  = strtol (optarg, NULL, 10);  break;
         case 'b':  bufsize  = strtol (optarg, NULL, 10);  break;
         case 'h':  usage (argv); exit (1);
         case '?':  usage (argv); exit (1);
         default:   usage (argv); exit (1);
      }
   }
   printf ("Options list: port=%d, bufsize=%d\n ", port, bufsize);
}

///////////////// signal handlers  ///////////////////

void handler_int (int sig) {
   printf ("\nSIGINT\n");  //ctrl/C
   exit (-1);
 }

 void handler_alrm (int sig) {
    printf ("\nSIGALRM\n");  //Time_out
   //N=0;
   //alarm(timeout);   // setta nuovamente il timer
   return;
  }

//////// get_current_time ()   /////////////////

double  get_current_time () {
   struct timeval tempo;
   gettimeofday (&tempo, 0);              
   return tempo.tv_sec + (tempo.tv_usec/1000000.0);
}

///////////////////// rnd() ///////////////
//
// Torna 1 con probabilita' prob (tra 0 e 1 ) altrimenti 0
//

int rnd(float prob) {
   double now = get_current_time();
   int seed = (now - (int)now) * 1000000;
   srand48(seed);
   float r = drand48();   
   //printf(" r=%f p=%f \n", r, prob);
   return (r < prob) ; 
}

///////// network  ////////////////////////

int sockd;
struct sockaddr_in servaddr;
int socklen;
struct hostent* myhostent;

int net_open_cli() {
   myhostent = gethostbyname(server);
   if(myhostent == 0) { 
      fprintf(stdout,"%s: host sconosciuto\n", server); 
      return(-1);
   }

   int sockfd; 
   if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
      printf("errore in socket");

   socklen=sizeof(servaddr);
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(port);
   servaddr.sin_addr = *(struct in_addr *) myhostent->h_addr;
   printf("SERVER %s:%d \n ", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));
   return sockfd; 
}

int net_open_srv()  {
    int sockfd; 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) printf("errore in socket");
    socklen=sizeof(servaddr);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr))==-1) printf("bind error\n");
    printf("SERVER %s:%d \n ", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port)); 
    return sockfd; 
  }


  int net_close_cli () {
   return (0); 
 }


 int net_close_srv() {
   return (0);
 }



 int net_send(int sockfd, void * msg, int N) {
  return sendto(sockfd, msg, N , 0, (struct sockaddr *)&servaddr, socklen);
}

int net_recv(int sockfd, void * msg) {
  int MaxBytes=2000; 
  int Len= recvfrom(sockfd, msg, MaxBytes, 0, (struct sockaddr *)&servaddr, (socklen_t *)&socklen);
  printf("Ricevuti %d byte da %s:%d: %s\n ",Len,  inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port), msg); 
  return Len; 
}


////////////////////////////////////////////////////////////////////
