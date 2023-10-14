#include <stdio.h>
#include <limits.h>
#include <math.h>

#define MAX_TICKETS 10005
#define MAX_DAYS 10005

// gcc pedagio_espacial.c -o ./out/pedagio_espacial
// ./out/pedagio_espacial.exe < ./in/pedagio_espacial.txt

typedef struct {
  int first_day;
  int last_day;
  int price;
} Ticket;

int pedagio(int n, int m, Ticket tickets[]) {
  int custos[MAX_DAYS];
  custos[0] = 0;

  for (int i = 1; i <= m; i++) {
    custos[i] = INT_MAX;
    for (int j = 0; j < n; j++) {
      if (i >= tickets[j].first_day && i <= tickets[j].last_day) {
        if (custos[i - 1] != INT_MAX) {
          int custo_atual = custos[tickets[j].first_day - 1] + tickets[j].price;
          custos[i] = (custos[i] < custo_atual) ? custos[i] : custo_atual;
        }
      }
    }
  }

  if (custos[m] == INT_MAX) {
    return INT_MAX;
  } else {
    return custos[m];
  }
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  Ticket tickets[MAX_TICKETS];
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &tickets[i].first_day, &tickets[i].last_day, &tickets[i].price);
  }

  int custo = pedagio(n, m, tickets);
  if (custo == INT_MAX) {
    printf("Vias lotadas.\n");
  } else {
    printf("%d\n", custo);
  }

  return 0;
}
