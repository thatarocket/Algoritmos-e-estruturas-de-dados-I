bool encontrarMinMax(DEQUE* d, int* min, int* max) { 

  if(d->cabeca == d->cabeca->prox) {
    bool resposta = false; 
    return resposta; 
  } 
  
  PONT verif = d->cabeca->prox; 
  int maior = verif->reg.chave; 
  int menor = verif->reg.chave; 
  
  while(verif != d->cabeca) {
  
    if(maior <= verif->reg.chave) { 
      maior = verif->reg.chave; 
    } 
    
    if(menor > verif->reg.chave) { 
      menor = verif->reg.chave;
    } 
    
    verif = verif->prox; 
  } 
  
  *min = menor; 
  *max = maior; 
  bool resposta = true; 
  return resposta; 
} /* encontrarMinMax */
