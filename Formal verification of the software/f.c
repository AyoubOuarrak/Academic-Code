
/*@
    axiomatic ParentChildAxioms {
        predicate ParentChild(integer i, integer j);

        axiom A1:
            \forall integer i, j; ParentChild(i, j) <==> 0 <= i < j && (j == 2*i+1 || j == 2*i+2);

        axiom A2:
            \forall integer i, j; ParentChild(i, j) <==> 0 < j && i == (j-1)/2;
    }

    lemma A3:
        \forall integer i; 0 < i ==> ParentChild((i-1)/2, i) && 0 <= (i-1)/2 < i;

    predicate IsHeap{L} (unsigned* c, integer n) =
        \forall integer i, j; j <n && ParentChild(i, j) ==> c[i] >= c[j];

    predicate is_valid_range (unsigned* p, unsigned n) =
        (0 <= n) && \valid_range(p, 0, n - 1);
*/

/*@
    requires 0 < n && is_valid_range(c, n);
    requires IsHeap(c, n);
    assigns \nothing;
    ensures \forall integer i; 0 <= i < n ==> c[0] >= c[i];
*/
void pop_heap_induction(const unsigned* c, unsigned n) {
    /*@
        loop invariant 0 <= i <= n;
        loop invariant \forall integer j; 0 <= j < i <= n ==> c[0] >= c[j];
        loop variant n - i;
    */
    for(unsigned i = 1; i < n; ++i) {
        //@ assert 0 < i ==> ParentChild((i-1)/2, i);
    }
}

/*@
    requires n > 0;
    requires is_valid_range(c, n);
    requires IsHeap(c, n-1);
    assigns c[0..(n-1)];
    ensures IsHeap(c, n);
*/
void push_heap(unsigned* c, unsigned n) {
    const int tmp = c[n-1];
    int hole = n-1;
    /*@
        loop invariant 0 <= hole < n;
        loop invariant hole < n-1 ==> IsHeap(c, n);
        loop invariant \forall integer i, j; j < n && j != hole && ParentChild(i, j) ==> c[i] >= c[j];
        loop invariant \forall integer i; i < n && ParentChild(hole, i) ==> c[i] <= tmp;
        loop variant hole;
    */
    while (hole > 0) {
        const int parent = (hole - 1)/2;
        if(c[parent] < tmp)
            c[hole] = c[parent];
        else
            break;

        hole = parent;
    }
    c[hole] = tmp;
}

/*@
    //requires 0 < n < (INT_MAX-2)/2;
    requires is_valid_range(c, n);
    requires IsHeap(c, n);

    ensures IsHeap(c, n-1);
    ensures c[n-1] == \old(c[0]);
    ensures \forall integer i; 0 <= i < n ==> c[n-1] >= c[i];
*/
void pop_heap(unsigned* c, unsigned n) {
    //@ ghost pop_heap_induction(c, n);
    //@ assert \forall integer i; 0 < i < n ==> c[0] >= c[i];
    int tmp = c[n-1];
    int max = c[0];
    int hole = 0;

    /*@
        loop invariant 0 <= hole < n;
        loop assigns c[0..hole];
        loop invariant IsHeap(c, n-1);
        loop invariant \forall integer i; 0 <= i < n ==> c[i] <= max;
        loop invariant \forall integer i; hole < n-1 && ParentChild(i, hole) ==> c[i] >= tmp;
        loop variant n - hole;
    */
    while(1) {
        int child = 2*hole + 2;
        if(child < n-1) {
            if(c[child] < c[child-1])
                child--;
            //@ assert ParentChild(hole, child);
            if(c[child] > tmp) {
                c[hole] = c[child];
                hole = child;
            } else
                break;
        } else {
            child = 2*hole + 1;
            if(child == n-2 && c[child] > tmp) {
                c[hole] = c[child];
                hole = child;
            }
            break;
        }
    }

    //@ assert \forall integer i; hole < n-1 && ParentChild(i, hole) ==> c[i] >= tmp;
    c[hole] = tmp;
    c[n-1] = max;
}

/*@
    //requires n < INT_MAX;
    requires is_valid_range(c, n);
    //assigns c[0..(n-1)];
    ensures IsHeap(c, n);
*/
void make_heap(unsigned* c, unsigned n) {
    if(n == 0)
        return;
    /*@
        loop invariant IsHeap(c, i-1);
        loop invariant 2 <= i <= n + 1;
        loop variant n - i;
    */
    for (unsigned i = 2; i <= n; ++i) {
        push_heap(c, i);
    }
}

/*@
    requires is_valid_range(c, n);
    requires IsHeap(c, n);
    assigns c[0..(n-1)];
    ensures \forall integer i; 0 <= i < n-1 ==> c[i] <= c[i+1];
*/
void sort_heap(unsigned* c, unsigned n) {
    /*@
        loop invariant 0 <= i <= n;
        loop invariant IsHeap(c, i);
        loop invariant i < n ==> c[0] <= c[i];
        loop invariant \forall integer j; i <= j < n-1 ==> c[j] <= c[j+1];
        loop variant i;
    */
    for (unsigned i = n; i > 0; --i) {
        pop_heap(c, i);
    }
}

/*@
    requires is_valid_range(c, n);
    assigns c[0..(n-1)];
    ensures \forall integer i; 0 <= i < n-1 ==> c[i] <= c[i+1];
*/
void heap_sort(unsigned* c, unsigned n) {
    make_heap(c, n);
    sort_heap(c, n);
}


/*@
   requires \valid_range(v, 0, v_size-1);

   behavior one:
      assumes \exists int m,  i,  j;
                  (m == \abs(v[i] - v[j]) ==>
                  \forall int h, k;
                      \abs(v[h] - v[k]) >= m) ==> (m <= t);
      ensures \result == 1;

   behavior zero:
      assumes !(\exists int m, i, j;
                  (m == \abs(v[i] - v[j]) ==>
                  \forall int h, k;
                     \abs(v[h] - v[k]) >= m) ==> (m <= t));
      ensures \result == 0;

   complete behaviors one, zero;
   disjoint behaviors one, zero;
*/
int f(unsigned v[], unsigned v_size, unsigned t) {
   heap_sort(v, v_size);

   /*@
      loop assigns i;
   */
   for(unsigned i = 1; i < v_size; ++i) {
      if(v[i] - v[i-1] <= t)
         return 1;
   }
   return 0;
}