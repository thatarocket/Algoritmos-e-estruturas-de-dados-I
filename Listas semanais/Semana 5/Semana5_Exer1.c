void exibirPilhaInvertida(PILHA* p){

  printf("Pilha (da base para o topo): \" ");
  for (int i = 0; i <= p->topo; i++) {
    printf(" %i ", p->A[i].chave);
  }
  printf("\"\n");
  
}
