#include <stdio.h>
#include <stdlib.h> 
#include "rand55.h" 

long Seed=161803398L;

Lnk_List_Ptr Ran, n1, n2;

#ifdef INLINE
inline
#endif

double rand55() {
    n1 = n1->next; 
    n2 = n2->next;
    n1->Y += n2->Y;

    return  (double)n1->Y * Norm_Factor ;
}

void rand_init(long idum) {
    int i, j;
    long tmp, aux;
    double null;

    if((Ran = (Lnk_List_Ptr)calloc(55, sizeof(struct Lnk_List))) == NULL)
	   exit(1);
    
    for(i = 0;i < 54; ++i) {
	   (Ran + i)->next = Ran + i + 1;
    }

    (Ran+54)->next = Ran;
    tmp = Seed + idum;
    Ran[54].Y = tmp;
    aux = 1;
    j = 20;
    for(i = 0; i < 54; ++i, j += 21) {
    	j %= 55;
    	Ran[j].Y = aux;
    	aux += tmp;
    	tmp = Ran[j].Y;
    }

    n1 = Ran;
    n2 = Ran + 31;

    for(j = 0; j < 55*4; ++j) {
	   null += rand55();
    }
    fprintf(stderr,"Rand55 initialized - chksum=%f\n", null);
}


