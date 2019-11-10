#define Norm_Factor   2.328306437080797e-10

#ifdef MACRO
#define Ranf()  (((n1=n1->next)->Y += (n2=n2->next)->Y), (double)n1->Y * Norm_Factor)
#else
#define Ranf() rand55()
double rand55();
#endif

void rand_init();

typedef struct Lnk_List *Lnk_List_Ptr;
struct Lnk_List {
	unsigned long Y;
	Lnk_List_Ptr next;
} ;


