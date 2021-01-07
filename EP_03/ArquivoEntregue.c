#include "filaDePrioridade.h"
#include <math.h>

PFILA criarFila(int max){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->maxElementos = max;
  res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
  res->heap = (PONT*) malloc(sizeof(PONT)*max);
  int i;
  for (i=0;i<max;i++) {
    res->arranjo[i] = NULL;
    res->heap[i] = NULL;
  }
  res->elementosNoHeap = 0;
  return res;
}

void exibirLog(PFILA f){
  printf("Log [elementos: %i]\n", f->elementosNoHeap);
  PONT atual;
  int i;
  for (i=0;i<f->elementosNoHeap;i++){
    atual = f->heap[i];
    printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
  }
  printf("\n\n");
}

int tamanho(PFILA f) {
  int tam = f->elementosNoHeap;
  return tam;
}

void FuncaoAux1(PFILA f,PONT elemento) { 
  int posicpai = floor((elemento->posicao - 1) / 2); //Encontrando a posic do pai
    PONT pai = f->heap[posicpai];
    PONT raiz = f->heap[0];

    if(raiz == elemento) {
      return;
    } 
    
    if(elemento->prioridade <= pai->prioridade) {
      return;
    }
     
    f->heap[posicpai] = elemento; //Colocar o filho na posic do pai
    f->heap[elemento->posicao] = pai; //Colocar o pai na posic anterior do filho
    pai->posicao = elemento->posicao;
    elemento->posicao = posicpai;
      
    FuncaoAux1(f,elemento); 
    
}

void FuncaoAux2(PFILA f, PONT atual) {
    
  int posicesq = (2 * atual->posicao) + 1;
  int posicdir = (2 * atual->posicao) + 2;
  PONT aux = atual;
  int posicinicial = atual->posicao;
  
  if(posicesq < f->elementosNoHeap && posicdir < f->elementosNoHeap) {
    if(atual->prioridade >= f->heap[posicesq]->prioridade && atual->prioridade >= f->heap[posicdir]->prioridade ) {
      return;
    }  
  }

  if(posicesq < f->elementosNoHeap) {
    PONT filhoesq = f->heap[posicesq];
    if(filhoesq->prioridade > atual->prioridade && (posicdir >= f->elementosNoHeap || (posicdir < f->elementosNoHeap && f->heap[posicdir]->prioridade <= filhoesq->prioridade))) {
      filhoesq->posicao = atual->posicao;
      atual->posicao = posicesq; 
      f->heap[posicesq] = aux; 
      f->heap[filhoesq->posicao] = filhoesq; 
      FuncaoAux2(f,atual); 
    } 

    else {
      
      if(posicdir < f->elementosNoHeap) {
        PONT filhodir = f->heap[posicdir];
        if(filhodir->prioridade > atual->prioridade) {
          filhodir->posicao = atual->posicao;
          atual->posicao = posicdir;
          f->heap[posicdir] = aux;
          f->heap[filhodir->posicao] = filhodir;
          FuncaoAux2(f,atual); 
        }
      } 
    }
  }
}

bool inserirElemento(PFILA f, int id, float prioridade){
  bool res = false;

  if(id < 0 || id >= f->maxElementos) { //Verificar se o id e valido
    return res;
  }
  
  if(f->arranjo[id]) { //Verificar se tem algum elemento repetido
    return res;
  }
 
  PONT elemento = (PONT) malloc(sizeof(ELEMENTO));
  elemento->id = id;
  elemento->prioridade = prioridade;
  elemento->posicao = f->elementosNoHeap;
  
  f->arranjo[id] = elemento; //Inserir no array
  f->heap[f->elementosNoHeap] = elemento; //Inserir no heap
  FuncaoAux1(f,elemento);
  f->elementosNoHeap++;

  res = true;
  return res;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  bool res = false;
  
  if(id < 0 || id >= f->maxElementos){
    return res;
  }

  if(!f->arranjo[id]) {
    return res;
  }

  if(f->arranjo[id]->prioridade >= novaPrioridade) {
    return res;
  }

  f->arranjo[id]->prioridade = novaPrioridade;
  PONT PrioridadeAumenta = f->arranjo[id];
  FuncaoAux1(f,PrioridadeAumenta);
  res = true;
  return res;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  bool res = false;
  
  if(id < 0 || id >= f->maxElementos) {
    return res;
  }
  
  if(!f->arranjo[id]) {
    return res;
  }

  if(f->arranjo[id]->prioridade <= novaPrioridade) {
    return res;
  }

  f->arranjo[id]->prioridade = novaPrioridade;
  
  PONT PrioridadeDiminui = f->arranjo[id];
  FuncaoAux2(f,PrioridadeDiminui);
  res = true;
  return res;
}

PONT removerElemento(PFILA f){
  PONT res = NULL;
  if(f->elementosNoHeap == 0) {
    return res;
  }
  int id = f->heap[0]->id;
  f->arranjo[id] = NULL;
  res = f->heap[0];

  if(f->elementosNoHeap > 1) {
    f->heap[0] = f->heap[f->elementosNoHeap-1];
    f->heap[f->elementosNoHeap-1] = NULL;
    f->heap[0]->posicao = 0;
  }
  else {
    f->heap[0] = NULL;
    f->heap[1] = NULL;
  }
  f->elementosNoHeap--;
  if(f->elementosNoHeap > 1) {
    FuncaoAux2(f,f->heap[0]);
  }
  return res;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  bool res = false;
  
  if(id < 0 || id >= f->maxElementos) {
    return res;
  }

  if(!f->arranjo[id]) {
    return res;
  }

  *resposta = f->arranjo[id]->prioridade;
  res = true;
  return res;
}
