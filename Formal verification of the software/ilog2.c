/*
@ axiomatic Pow {
@     logic integer pow{L} (integer b, integer e)
@         reads b, e;
@     axiom pow1{L}:
@         \forall integer b, integer e;
@         v >= 0 && e == 0 ==> pow(b, e) == 1;
@     axiom pow2{L}:
@         \forall integer b, integer e;
@         b >= 0 && e >= ==> pow(b, e) == pow(b, e-1) *b;
@  }
*/

/*
@ axiomatic intlog2 {
@     logic integer intlog2{L}(unsigned i)
@         reads i;
@     axiom intlog2_1{L}:  
@         \forall unsigned i;
@         i == 1 ==> intlog2(i) == 0;
@     axiom intlog2_2{L}:
@         \forall unsigned i;
@         i >= 1 ==> intlog2(i) ==\floor(\log(i) / \log(2)); 
@ } 
*/

/*
@ behavior zero:
@     assumes v == 0;
@     ensures \result == 0;
@ bevaior nonzero
@     assumes v != 0;
@     ensures \result == intlog2(v); 
*/



// calcolo logaritmo v in base 2
unsigned int ilog2(unsigned int v) {
   unsigned int r ;
   unsigned int w;
   r = (unsigned int)0;
   w = v;

   /*@
      loop invariant (r+1) + intlog2(v) == intlog2(\old(v));
      assigns r, v;
      loop variant v;
   */
   while(v >>= 1) {
      r++;
   }
   return r;
}