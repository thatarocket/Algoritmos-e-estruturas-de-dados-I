/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Seugndo Semestre de 2020                           **/
/**   <2020294> - Prof. Luciano Antonio Digiampietri                **/
/**                                                                 **/
/**   EP2 - Fila Preferencial                                       **/
/**                                                                 **/
/**   <Thais de Souza Rodrigues>                   <11796941>       **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
  res->inicioPref = NULL;
  res->fimPref = NULL;
  res->inicioGeral = NULL;
  res->fimGeral = NULL;
  return res;
}

int tamanho(PFILA f){
  PONT atual = f->inicioGeral;
  int tam = 0;
  while (atual) {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

int tamanhoFilaPreferencial(PFILA f){
  PONT atual = f->inicioPref;
  int tam = 0;
  while (atual) {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

PONT buscarID(PFILA f, int id){ //Para fila geral
  PONT atual = f->inicioGeral;
   while (atual) {
    if (atual->id == id) return atual;
    atual = atual->prox;
  }
  return NULL;
}

PONT buscarID2(PFILA f, int id){ //Para fila preferencial
  PONT atual = f->inicioPref;
   while (atual) {
    if (atual->id == id) return atual;
    atual = atual->prox;
  }
  return NULL;
}

void exibirLog(PFILA f){
  int numElementos = tamanho(f);
  printf("\nLog fila geral [elementos: %i] - Inicio:", numElementos);
  PONT atual = f->inicioGeral;
  while (atual){
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n");
  numElementos = tamanhoFilaPreferencial(f);
  printf("\nLog fila preferencial [elementos: %i] - Inicio:", numElementos);
  atual = f->inicioPref;
  while (atual){
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n\n");
}


bool inserirPessoaNaFila(PFILA f, int id, int ehPreferencial){
  bool resposta = false;
  if(id < 0) {
    return resposta;
  }

  if(buscarID(f,id)) {
    return resposta;
  }
  
  PONT novo1 = (PONT) malloc(sizeof(ELEMENTO));
  novo1->id = id;
  novo1->ehPreferencial = ehPreferencial;
  novo1->prox = NULL;

  

    if(tamanho(f) == 0) { //Se a fila estiver vazia

        if(novo1->ehPreferencial) { //Se for preferencial
            PONT novo2 = (PONT) malloc(sizeof(ELEMENTO));
            novo2->id = id;
            novo2->ehPreferencial = ehPreferencial;
            novo2->prox = NULL;

            f->inicioGeral = novo1;
            f->fimGeral = novo1;
            f->inicioPref = novo2;
            f->fimPref = novo2;
          
        }

        else {
          f->fimGeral = novo1;
          f->inicioGeral = novo1;
        }
    }

    else { //Se a fila geral não estiver vazia

      if(novo1->ehPreferencial) {
        PONT novo2 = (PONT) malloc(sizeof(ELEMENTO));
        novo2->id = id;
        novo2->ehPreferencial = ehPreferencial;
        novo2->prox = NULL;

          if(tamanhoFilaPreferencial(f) != 0) { //Se a fila pref nao ta vazia
            f->fimGeral->prox = novo1;
            f->fimGeral = novo1;
            f->fimPref->prox = novo2;
            f->fimPref = novo2;
          }

          else { //Se a fila pref ta vazia
            f->fimGeral->prox = novo1;
            f->fimGeral = novo1;
            f->fimPref = novo2;
            f->inicioPref = novo2;
          }
      }
      else {
        f->fimGeral->prox = novo1;
        f->fimGeral = novo1;
      }

    }

  resposta = true;
  return resposta;
}

bool atenderPrimeiraDaFilaPreferencial(PFILA f, int* id){
  bool resposta = false;

    if(f->inicioGeral == NULL) {
      return resposta;
    }

    int idexclusao = -1; //Utilizar para buscar posteriormente

    if(f->inicioPref != NULL) { //A fila pref nao esta vazia
      *id = f->inicioPref->id;
      idexclusao = f->inicioPref->id;

      PONT apagar = f->inicioPref;
      f->inicioPref = f->inicioPref->prox;
      free(apagar); //Apagar da memoria na fila pref

      apagar = buscarID(f,idexclusao); //Procurar a posic, do atual, no geral atraves do id
      PONT ant = f->inicioGeral;

      if(f->inicioGeral->id != idexclusao ) {  //Se o id não for o primeiro da lista
        while (ant->prox != apagar) { //Procurar o anterior a ele para organizar os ponteiros
          //if (ant->id == id) break;
          ant = ant->prox;
        }

        ant->prox = apagar->prox; //Organizando os ponteiros
        free(apagar); //Liberando memoria da fila geral
      }

      else { //Se o id for o primeiro da lista
        f->inicioGeral = f->inicioGeral->prox;
        free(apagar); //Apagar da memoria na fila geral
      }
      
    }
    
    else { //A fila pref estar vazia
      *id = f->inicioGeral->id;
      PONT apagar = f->inicioGeral;
      f->inicioGeral = f->inicioGeral->prox;
      free(apagar);
      
    }
  resposta = true;
  return resposta;
}



bool atenderPrimeiraDaFilaGeral(PFILA f, int* id){
  bool resposta = false;

  if(f->inicioGeral == NULL) { 
    return resposta;
  }

  if(f->inicioGeral->ehPreferencial == true) {
    *id = f->inicioGeral->id;
    PONT apagar = f->inicioGeral;
    f->inicioGeral = f->inicioGeral->prox;

    int idexclusao = apagar->id;
    free(apagar);

    apagar = buscarID2(f,idexclusao);
    PONT ant = f->inicioPref;

    if (f->inicioPref->id != idexclusao ) {  //Se o id não for o primeiro da lista
        while (ant->prox != apagar) { //Procurar o anterior a ele para organizar os ponteiros
          //if (ant->id == id) break;
          ant = ant->prox;
        }

        ant->prox = apagar->prox; //Organizando os ponteiros
        free(apagar); //Liberando memoria da fila geral
        
    }

    else { //Se o id for o primeiro da lista
      f->inicioPref = f->inicioPref->prox;
      free(apagar); //Apagar da memoria na fila geral
    }
  }

  else { //Se nao for preferencial
    *id = f->inicioGeral->id;
    PONT apagar = f->inicioGeral;
    f->inicioGeral = f->inicioGeral->prox;
    free(apagar);
  }
    resposta = true;
    return resposta;
}

bool desistirDaFila(PFILA f, int id){
  bool resposta = false;

  if(!buscarID(f,id)) { //Se for nulo, retorna null
    return resposta;
  }

  PONT apagar = buscarID(f,id);
  PONT apagar2 = buscarID2(f,id);
  
  if(apagar->ehPreferencial) { //Se for preferencial

      PONT ant = f->inicioPref;
      if(f->inicioPref->id != id) {
          while (ant->prox->id != apagar->id) { //Procurar o anterior a ele para organizar os ponteiros
                ant = ant->prox;
          }
          ant->prox = apagar2->prox;
          free(apagar2);
      }

      else {
          apagar = f->inicioPref;
          f->inicioPref = f->inicioPref->prox;
          free(apagar);
      }

      apagar = buscarID(f,id);
      ant = f->inicioGeral;

      if(f->inicioGeral->id != id) {

          while (ant->prox != apagar) { //Procurar o anterior a ele para organizar os ponteiros
              ant = ant->prox;
          }
          ant->prox = apagar->prox;
          free(apagar);
      }

      else {
          apagar = f->inicioGeral;
          f->inicioGeral = f->inicioGeral->prox;
          free(apagar);
      }
  }
  else {

      PONT apagar = buscarID(f,id);
      PONT ant = f->inicioGeral;

        if(f->inicioGeral->id != id) {
            while (ant->prox != apagar) { //Procurar o anterior a ele para organizar os ponteiros
                ant = ant->prox;
            }
            ant->prox = apagar->prox;
            free(apagar);
        }

        else {
            apagar = f->inicioGeral;
            f->inicioGeral = f->inicioGeral->prox;
            free(apagar);
        }

  } 
  resposta = true;
  return resposta;
}
