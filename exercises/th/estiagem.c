#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void bubbleSort(int * averages_per_house, int * amount_people, int tamanho) {
  int i, j;
  
  for (i = 0; i < tamanho-1; i++) {
    for (j = 0; j < tamanho-i-1; j++) {
      if (averages_per_house[j] > averages_per_house[j+1]) {
        int temp = averages_per_house[j];
        averages_per_house[j] = averages_per_house[j+1];
        averages_per_house[j+1] = temp;

        int temp2 = amount_people[j];
        amount_people[j] = amount_people[j+1];
        amount_people[j+1] = temp2;
      }
    }
  }
}

void get_city_consumption(
  int id, 
  int amount,
  int * averages_per_house,
  int * amount_people,
  double overall_average
) {
  bubbleSort(averages_per_house, amount_people, amount);

  printf("Cidade# %d:\n", id);
  for (int i = 0; i < amount; i++) {
    if(i == amount - 1) {
      printf("%d-%d\n", amount_people[i], averages_per_house[i]);
      continue;
    }
    printf("%d-%d ", amount_people[i], averages_per_house[i]);
  }
  printf("Consumo medio: %.2lf m3.\n\n", overall_average);
}

double average(int total, int amount_people) {
  return (double) total / amount_people;
}

int busca(int * vector, int len, int value) {
  for (int i = 0; i < len; i++) {
    if (vector[i] == value) return i;
  }
  
  return -1;
}

int main() {
  int id = 1;
  int amount_houses;
  scanf("%d", &amount_houses);

  while(amount_houses != 0) {
    int amount_people = 0;
    int amount_consumption = 0;
    int max_index = 0;
    int * averages_per_house = (int*)malloc(amount_houses * sizeof(int));
    int * amount_people_per_house = (int*)malloc(amount_houses * sizeof(int));

    for (int i = 0; i < amount_houses; i++) {
      int people;
      int consumption;
      scanf("%d %d", &people, &consumption);

      int average_house = consumption / people;
      int index_average = busca(averages_per_house, max_index, average_house);
      if(index_average == -1) {
        averages_per_house[max_index] = average(consumption, people);
        amount_people_per_house[max_index] = people;
        amount_people += people;
        amount_consumption += consumption;
        max_index++;
      } else {
        amount_people_per_house[index_average] += people;
        amount_people += people;
        amount_consumption += consumption;
      }
    }

    get_city_consumption(id, max_index, averages_per_house, amount_people_per_house, average(amount_consumption, amount_people));

    free(averages_per_house);
    free(amount_people_per_house);
    id++;
    scanf("%d", &amount_houses);
  }

  return 0;
}