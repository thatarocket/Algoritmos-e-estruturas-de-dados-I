bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {
  TIPOCHAVE ch = reg.chave;
  PONT ant, i;
  i = buscaSeqExc(l,ch,&ant);
  
  if (i != NULL) return false;
  i = (PONT) malloc(sizeof(ELEMENTO));
  i->reg = reg;
  if (ant == NULL) {
    i->prox = l->inicio;
    l->inicio = i;
    i->ant = NULL;
      if(i->prox) {
        i->prox->ant = i;
      }
   } 
   else {
    i->prox = ant->prox;
    ant->prox = i;
    i->ant = ant;
      if(i->prox) {
        i->prox->ant = i;
      }
   }
 return true;
}
