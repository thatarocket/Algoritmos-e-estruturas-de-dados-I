typedef struct aux {
  struct aux* mae;
  struct aux* pai;
} PESSOA;

void registrar(PESSOA* filho, PESSOA* mae, PESSOA* pai){
  filho->mae = mae;
  filho->pai = pai;
}

int main() {
  PESSOA filho;
  PESSOA mae;
  PESSOA pai;
  registrar(&filho, &mae, &pai);
  return 0;
}
