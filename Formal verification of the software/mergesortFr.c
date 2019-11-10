/*
   Author: Ayoub Ouarrak

   Si scriva una funzione:

      int f(unsigned v[], unsigned v_size, unsigned t) =  1 se m <= t
                                                          0 altrimenti

      m = min { |v[h] - v[k]| | h != k sono due posizioni di v }.

*/
#include <stdio.h>
/*@ predicate sorted{L}(unsigned* a, integer l, integer h) =
      \forall unsigned i; l <= i < h ==> a[i] <= a[i+1];
*/

/*@
   logic integer counter{L}(unsigned* v, int lower, int upper, unsigned toCount) =
      lower > upper ?
         0 :
         v[lower] == toCount ?
            counter(v, (int)(lower + 1), upper, toCount) + 1:
            counter(v, (int)(lower + 1), upper, toCount);
*/


/*@
   ensures \result == x || \result == y;
   ensures \result <= x && \result <= y;
*/
int min(int x, int y) {
   return (x < y) ? x : y;
}

/*@
   requires 0 <= l <= m < r;
   requires \valid_range(arr, l, m);
   requires \valid_range(arr, m + 1, r);

   ensures sorted{Here}(arr, l, r);
   ensures \forall unsigned x; \exists unsigned y; x == y && counter(\old(arr), (int)l, (int)r, x) == counter(arr, (int)l, (int)r, y);
*/
void merge(unsigned arr[], int l, int m, int r) {
   unsigned i, j, k;
   unsigned n1 = m - l + 1;
   unsigned n2 =  r - m;
   unsigned* L = (unsigned*)malloc(n1 * sizeof(unsigned));
   unsigned* R = (unsigned*)malloc(n2 * sizeof(unsigned));
   //unsigned L[n1], R[n2];

   /*@
      loop invariant 0 <= i < n1;
      loop invariant l + i <= m;
      loop invariant (m == l) ==> L[0] == arr[l];
      loop invariant n1 > 0 ==>
            \forall unsigned x; \exists unsigned y; x == y && counter(L, (int)0, (int)(n1-1), arr[l+i]) == counter(arr, (int)l, (int)(l+n1-1), arr[l+i]);
      loop assigns L[i];
      loop assigns i;
   */
   for (i = 0; i < n1; i++)
      L[i] = arr[l + i];

   /*@
      loop invariant 0 <= j < n2;
      loop invariant m + 1 + j < r;
      loop invariant n2 > 0 ==>
            \forall unsigned x; \exists unsigned y; x == y && counter(R, (int)0, (int)(n2-1), arr[m+1+j]) == counter(arr, (int)(m+1), (int)(m+n2), arr[m+1+j]);
      loop assigns R[j];
      loop assigns j;
   */
   for (j = 0; j < n2; j++)
      R[j] = arr[m + 1 + j];


   i = 0;
   j = 0;
   k = l;
   /*@
      loop assigns i, j, k, arr[k];
      loop invariant i < n1 && j < n2;
      loop invariant L[i] <= R[j] || L[i] > R[j];
   */
   while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
         arr[k] = L[i];
         i++;
      } else {
         arr[k] = R[j];
         j++;
      }
      k++;
   }

   /*@
      loop invariant i < n1 && j >= n2;
      loop invariant k < m;
      loop assigns j, k, arr[k];
   */
   while (i < n1) {
      arr[k] = L[i];
      i++;
      k++;
   }

   /*@
      loop invariant j < n2 && i >= n1;
      loop invariant k < r;
      loop assigns j, k, arr[k];
   */
   while (j < n2) {
      arr[k] = R[j];
      j++;
      k++;
   }

   //free(L);
   //free(R);
}

/*@
   ensures n >= 0;

   ensures sorted{Here}(arr, 0, n-1);
   ensures \forall unsigned x; \exists unsigned y; x == y && counter(\old(arr), (int)0, (int)(n - 1), x) == counter(arr, (int)0, (int)(n - 1), y);
*/
void mergeSort(unsigned arr[], int n) {
   int mid = 0, right_end = 0;
   /*@
      loop invariant 1 <= curr_size <= n -1;
      loop assigns curr_size;
   */
   for (int curr_size = 1; curr_size <= n - 1; curr_size = 2*curr_size) {
      /*@
         loop invariant 0 <= left_start < n - 1 && left_start > curr_size;
         loop assigns left_start;
         loop invariant left_start <= mid < right_end;
      */
      for (int left_start = 0; left_start < n - 1; left_start += 2*curr_size) {
         mid = left_start + curr_size - 1;
         right_end = min(left_start + 2*curr_size - 1, n-1);
         merge(arr, left_start, mid, right_end);
      }
   }
}

/*@
   requires \valid_range(v, 0, v_size-1);

   behavior one:
      assumes \exists int m,  i,  j;
                  (m == \abs(v[i] - v[j]) ==>
                  \forall int h, k;
                      \abs(v[i] - v[j]) >= m) ==> (m <= t);
      ensures \result == 1;

   behavior zero:
      assumes !(\exists int m, i, j;
                  (m == \abs(v[i] - v[j]) ==>
                  \forall int h, k;
                     \abs(v[i] - v[j]) >= m) ==> (m <= t));
      ensures \result == 0;

   complete behaviors one, zero;
   disjoint behaviors one, zero;
*/
int f(unsigned v[], unsigned v_size, unsigned t) {
   mergeSort(v, v_size);

   /*@
      loop assigns i;
   */
   for(unsigned i = 1; i < v_size; ++i) {
      if(v[i] - v[i-1] <= t)
         return 1;
   }
   return 0;
}

