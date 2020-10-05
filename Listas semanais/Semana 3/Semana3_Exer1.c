#include <stdio.h>
#define MAX 50
#define ERRO -1
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct{
  TIPOCHAVE chave;
} REGISTRO;

typedef struct {
  REGISTRO A[MAX+1];
  int nroElem;
} LISTA;

void inicializarLista(LISTA* l) {
  l->nroElem = 0;
}

void exibirLista(LISTA* l) {
  int i;
  printf("Lista: \" ");
  for (i=0; i < l->nroElem; i++)
  printf("%i ", l->A[i].chave);
  printf("\"\n");
}

void ordenar(LISTA* l) {
  int pos = l->nroElem; //Bubble Sort
  
  for(int i = pos; i > 0; i--) {
   
    for(int j = 0; j < i; j++) {
    
      if(l->A[j].chave > l->A[j+1].chave) {
      
        TIPOCHAVE aux = l->A[j].chave;
        l->A[j].chave = l->A[j+1].chave;
        l->A[j+1].chave = aux;
        
      }
    }
  }
  printf("Os elementos foram ordenados! \n");
}
