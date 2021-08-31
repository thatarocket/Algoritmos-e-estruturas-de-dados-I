/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   <2020294> - Prof. Luciano Antonio Digiampietri                **/
/**                                                                 **/
/**   EP1 - Fila de Prioridade                                      **/
/**                                                                 **/
/**   <Thais de Souza Rodrigues>                <11796941>          **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"

PFILA criarFila(int max){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->maxElementos = max;
  res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
  int i;
  for (i=0;i<max;i++) res->arranjo[i] = NULL;
  PONT cabeca = (PONT) malloc(sizeof(ELEMENTO));
  res->fila = cabeca;
  cabeca->ant = cabeca;
  cabeca->prox = cabeca;
  cabeca->id = -1;
  cabeca->prioridade = 1000000;
  return res;
}

void exibirLog(PFILA f){
  printf("Log [elementos: %i (alem do no cabeca)]\n", tamanho(f));
  PONT atual = f->fila;
  printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
  atual = atual->prox;
  while (atual != f->fila){
    printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
    atual = atual->prox;
  }
  printf("\nElementos validos: ");
  atual = atual->prox;
  while (atual != f->fila){
    printf("[%i;%f;%p] ", atual->id, atual->prioridade, atual);
    atual = atual->prox;
  }

  printf("\nValores do arrajo:\n\[ ");
  int x;
  for (x=0;x<f->maxElementos;x++) printf("%p ",f->arranjo[x]);
  printf("]\n\n");
}



int tamanho(PFILA f){
  int tam = 0;
  PONT end = f->fila->prox;
  
  while(end != f->fila) {
      tam++;
      end = end->prox;
  }
  
  return tam;
}

bool inserirElemento(PFILA f, int id, float prioridade){
    bool resposta = false;

    if (id < 0 || id >= f->maxElementos) { //verif do primeiro caso possivel de falso
        resposta = false;
        return resposta;
    }

    PONT verif = f->fila->prox;

    while (verif != f->fila) { //verif do segundo caso possivel de falso
        
        if(verif->id == id) { //Verificar se tem algum id igual
            resposta = false;
            return resposta;
        }
        
        else{
            verif = verif->prox;
        }
    }

    PONT inserir = (PONT) malloc(sizeof(ELEMENTO)); //Acrescenta espaço na memoria p/ o digitado pelo usuário
    inserir->prioridade = prioridade;  
    inserir->id = id;
    

    f->arranjo[id] = inserir; //Colocar na posicao do arranjo
    PONT priori = f->fila->prox; //Usar o prox do cabeca como comparacao
    
    if (priori == f->fila) { //apenas contem o no cabeca
        f->fila->prox = inserir;
        f->fila->ant = inserir;
        inserir->prox = f->fila;
        inserir->ant = f->fila;
        resposta = true;
        return resposta;
    }

    PONT posic = f->fila; 

    while(posic->prox->prioridade >= prioridade && posic->prox != f->fila) {  //Enquanto nao voltar no cabeca
        
        posic = posic->prox;

    } 

    f->arranjo[id]->ant = posic;
    f->arranjo[id]->prox = posic->prox;
    posic->prox->ant = f->arranjo[id];
    posic->prox = f->arranjo[id];

    resposta = true;
    return resposta;
}



bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
    bool resposta = false;
    
    if(id < 0 || id >= f->maxElementos) {
        return resposta;
    }

    if(f->arranjo[id] == NULL) {
        return resposta;
    }

    if(f->arranjo[id]->prioridade >= novaPrioridade) {
        return resposta;
    }

    f->arranjo[id]->prioridade = novaPrioridade;
    
    PONT posic = f->fila; //posicao da maior prioridade
    

    while(posic->prox->prioridade >= novaPrioridade && posic->prox != f->fila) {  //Enquanto nao voltar no cabeca
        
        posic = posic->prox;

    } 

    if(posic->id != id) { //Evitar comparações consigo mesmo
        f->arranjo[id]->prox->ant = f->arranjo[id]->ant; //Arrumando onde ele estava antes
        f->arranjo[id]->ant->prox = f->arranjo[id]->prox; //Arrumando onde ele estava antes
    
        f->arranjo[id]->ant = posic; //Arrumando o ant atual
        f->arranjo[id]->prox = posic->prox; //Arrumando o prox atual

        posic->prox->ant = f->arranjo[id]; //Arrumando o anterior do prox do posic
        posic->prox = f->arranjo[id]; //Arrumando o prox do posic
    
    }
    

    resposta = true;

  return resposta;
}



bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
    bool resposta = false;

    if (id < 0 || id >= f->maxElementos) {
        resposta = false;
        return resposta;
    }

    if (f->arranjo[id] == NULL) {
        resposta = false;
        return resposta;
    }

    if (f->arranjo[id]->prioridade <= novaPrioridade) {
        resposta = false;
        return resposta;
    }

    f->arranjo[id]->prioridade = novaPrioridade;
    PONT posic = f->fila; //posicao da menor prioridade
    

    while(posic->ant->prioridade <= novaPrioridade && posic->ant != f->fila) {  //Enquanto nao voltar no cabeca
        
        posic = posic->ant;

    } 
    
    if(posic->id != id) { //Evitar comparações consigo mesmo
        f->arranjo[id]->prox->ant = f->arranjo[id]->ant; //Arrumando onde ele estava antes
        f->arranjo[id]->ant->prox = f->arranjo[id]->prox; //Arrumando onde ele estava antes

        f->arranjo[id]->prox = posic; //Arrumando o ant atual
        f->arranjo[id]->ant = posic->prox; //Arrumando o prox atual

        posic->ant->prox = f->arranjo[id]; //Arrumando o anterior do prox do posic
        posic->ant = f->arranjo[id]; //Arrumando o prox do posic
    }
    resposta = true;

  return resposta;
}

PONT removerElemento(PFILA f){
    PONT resposta = NULL;
    
    int tam = tamanho(f);
    if(tam == 0) {
        return resposta;
    }

    resposta = f->fila->prox; //Devolvendo o ponteiro para quem solicitou
    int local = resposta->id;
    f->fila->prox->prox->ant = f->fila; //Arrumando o ant do prox do elemento removido
    f->fila->prox = resposta->prox;
    f->arranjo[local] = NULL;

  return resposta;
}



bool consultarPrioridade(PFILA f, int id, float* resposta){
    bool resp = false;

    if(id < 0 || id >= f->maxElementos) {
        return resp;
    }

    if(f->arranjo[id] == NULL) {
        return resp;
    }

    *resposta = f->arranjo[id]->prioridade; //Se eu coloco "&" fica errado também
    
    resp = true;

    return resp;
}

