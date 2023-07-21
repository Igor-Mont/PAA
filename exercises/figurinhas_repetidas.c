#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
	int n;
	int * elements;
} t_vector;

t_vector repetidas(t_vector album, t_vector novas) {
  t_vector figurinhas_repetidas;
  figurinhas_repetidas.n = 0;
  int menor = album.n < novas.n ? album.n : novas.n;
  int maior = album.n > novas.n ? album.n : novas.n;
  figurinhas_repetidas.elements = (int *)malloc(menor * sizeof(int));
  
  for (int i = 0; i < menor; i++) {
    for (int j = 0; j < maior; j++) {
      if(menor == novas.n) {
        if(novas.elements[i] == album.elements[j]) {
          figurinhas_repetidas.elements[figurinhas_repetidas.n++] = novas.elements[i];
        } 
      } else {
        if(album.elements[i] == novas.elements[j]) {
          figurinhas_repetidas.elements[figurinhas_repetidas.n++] = album.elements[i];
        } 
      }
    }
  }

  return figurinhas_repetidas;
} 

int main() {
	int i, j, k;
	t_vector album, novas, reps;
	scanf("%d", &album.n);
	album.elements = (int*)malloc((album.n+1)*sizeof(int));
	for(i = 0; i < album.n; i++){
		scanf("%d", &(album.elements[i]));
	}
	album.elements[i] = INT_MAX;
	
	scanf("%d", &novas.n);
	novas.elements = (int*)malloc((novas.n+1)*sizeof(int));
	for(i = 0; i < novas.n; i++){
		scanf("%d", &(novas.elements[i]));
	}
	novas.elements[i] = INT_MAX;
	
	reps = repetidas(album, novas);
	
	for(k = 0; k < reps.n-1; k++)
	  printf("%d ", reps.elements[k]);
	printf("%d\n", reps.elements[k]);
	
	free(reps.elements);
	free(album.elements);
	free(novas.elements);
	
	return 0;
}