#include <stdio.h>
#include <stdlib.h>

typedef struct aux {
  int id;
  struct aux* mae;
  struct aux* pai;
} PESSOA;

PESSOA* inicializar(int id) {
  PESSOA* pessoa1 = (PESSOA*) malloc(sizeof(PESSOA));
  pessoa1->id = id;
  pessoa1->mae = NULL;
  pessoa1->pai = NULL;
  return pessoa1;
}

int main() {
  printf("ENDERECO: %p", (inicializar(2)));
  return 0;
}
