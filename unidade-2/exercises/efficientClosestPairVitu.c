#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>

typedef struct
{
  int x;
  int y;
} Point;

void print(Point *P, int n) {
  for (int i = 0; i < n; i++) {
    printf("(%d %d)\n", P[i].x, P[i].y);
  }
}

void merge(Point *B, int b, Point *C, int c, Point *A, bool orderByX) {
  int i = 0, j = 0, k = 0;
  while (i < b && j < c) {
    //printf("i: %d, j: %d,k: %d\n", i, j, k);
    if(orderByX) {
      if(B[i].x <= C[j].x) A[k++] = B[i++];
      else A[k++] = C[j++];
    } else {
      if(B[i].y <= C[j].y) A[k++] = B[i++];
      else A[k++] = C[j++];
    }
  }


  if(i == b)
    memcpy(A+k, C+j, sizeof(Point)*(c-j));
  else
    memcpy(A+k, B+i, sizeof(Point)*(b-i));
}


void mergeSort(Point *A, int n, bool orderByX) {
  int lHalf = n / 2;
  int rHalf = n - lHalf;

  Point B[lHalf];
  Point C[rHalf];

  if (n > 1) {
    memcpy(B, A,sizeof(Point)*lHalf);
    memcpy(C, &A[lHalf], sizeof(Point)*rHalf);
    mergeSort(B, lHalf, orderByX);
    mergeSort(C, rHalf, orderByX);
    merge(B, lHalf, C, rHalf, A, orderByX);
  }
}

double efficientClosestPair(Point *P, Point *Q, int n) {
  double dminsq = INFINITY;
  if(n <= 3) {
    for(int i = 0; i < n-1; i++) {
      for(int j = i+1; j < n; j++) {
        double distanceSquared = pow(P[i].x - P[j].x, 2) + pow(P[i].y - P[j].y, 2);
        dminsq = fmin(dminsq, distanceSquared); // Use fmin to find the minimum of 'd' and 'distanceSquared'
      }
    }
  } else {
    int lHalf = n / 2;
    int rHalf = n-lHalf;
    Point pL[lHalf];
    Point qL[lHalf];

    Point pR[rHalf];
    Point qR[rHalf];

    memcpy(pL, P, sizeof(Point)*lHalf);
    memcpy(pR, &P[lHalf], sizeof(Point)*rHalf);
    int midPoint = P[lHalf - 1].x;

    int i = 0, j = 0;
    for (int k = 0; k < n; k++) {
      if((Q[k].x <= midPoint) && (i < lHalf)) {
        qL[i++] = Q[k];
      }
      else {
        qR[j++] = Q[k];
      }
    }

    double dL = efficientClosestPair(pL, qL, lHalf);
    double dR = efficientClosestPair(pR, qR, rHalf);
    double d = fmin(dL, dR);

    //create array S
    Point S[n];
    int num = 0;
    for (int i = 0; i < n; i++)
      if(abs(Q[i].x - midPoint) < d) S[num++] = Q[i];

    int k = 0;
    dminsq = d * d;
    for (int i = 0 ; i < num-2; i++) {
      k = i+1;
      while ((k <= num-1) && (pow(S[k].y - S[i].y, 2) < dminsq)) {
        dminsq = fmin(pow(S[k].x - S[i].x, 2) + pow(S[k].y - S[i].y, 2), dminsq);
        k++;
      }
    }

  }
  return dminsq;
}

void swap(Point *x, Point *y) {
    Point temp = *x;
    *x = *y;
    *y = temp;
}

int HoarePartition(Point *list, int l, int r, bool orderByX) {
    int p = orderByX ? list[l].x : list[l].y;

    int i = l;
    int j = r + 1;
    do {
      if (orderByX) {
        while (list[++i].x < p);
        while (list[--j].x > p);
      } else {
        while (list[++i].y < p);
        while (list[--j].y > p);
      }

      swap(&list[i], &list[j]);
    } while (i < j);
    swap(&list[i], &list[j]);
    swap(&list[l], &list[j]);
    return j;
}

void quickSort(Point *list, int l, int r, bool orderByX) {
  int s;
  if(l < r) {
    s = HoarePartition(list, l, r, orderByX);
    quickSort(list, l, s-1, orderByX);
    quickSort(list, s+1, r, orderByX);
  }
}

int main() {
  int n = 0;
  Point P[10];
  Point Q[10];

  while(scanf("%d %d", &P[n].x, &P[n].y) != EOF) {
    n++;
  }
  memcpy(Q, P, sizeof(Point)*n);

  //mergeSort(P, n, true);
  //mergeSort(Q, n, false);
  quickSort(P, 0, n, true);
  quickSort(Q, 0, n, false);
  double result = efficientClosestPair(P, Q, n);
  printf("%lf", sqrt(result));

  return 0;
}
