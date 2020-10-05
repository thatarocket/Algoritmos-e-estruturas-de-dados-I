/* Inserção no fim da fila */ 
bool inserirNaFila(FILA* f,REGISTRO reg) {
  PONT novo = (PONT) malloc(sizeof(ELEMENTO)); 
  novo->reg = reg; novo->prox = NULL; 
  
  if (f->cabeca->prox == NULL){ 
    f->cabeca->prox = novo; 
  } 
  else { 
    f->fim->prox = novo; 
  } 
  
  f->fim = novo; 
  return true; 
} /* inserir */ 

/* Excluir */ 
bool excluirDaFila(FILA* f, REGISTRO* reg) {
  if (f->cabeca->prox==NULL){ 
    return false;
  } 
  
  *reg = f->cabeca->prox->reg; 
  PONT apagar = f->cabeca->prox; 
  f->cabeca->prox = f->cabeca->prox->prox; 
  free(apagar); 
  
  if (f->cabeca->prox == NULL){ 
    f->fim = NULL;
  } 
  
  return true;
} /* excluirDaFila */
