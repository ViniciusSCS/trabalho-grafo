#include <stdio.h>
#include <math.h>
#define MAX 10000
 
typedef struct {
  float x,y;
  int used;
} Point;
 
Point p[MAX];
int V;
 
int prim(){
  int i,j;
  /* tot é a quantidade de vértices presentes na árvore a ser construída */
  int tot;
  /* Índice do ponto candidato a compor o próximo menor lado */
  int smallp;
  /* Tamanho do lado candidato a mínimo */
  float small;
  /* Tamanho do lado a ser avaliado, potencial candidato a mínimo. */
  float len;
  /* Tamanho da árvore geradora mínima */
  float minLen;
  /* Começamos com p[0], mas poderia ser qqlr vértice */
  tot=p[0].used=1;
  while(tot<V){
    small=-1.0;
    /* Loop dos vértices pertencentes à árvore. */
    for(i=0;i<V;i++) if(p[i].used)
      /* Loop dos vértices que ainda não foram adicionados à árvore. */
      for(j=0;j<V;j++) if(!p[j].used){
        len=sqrt(pow(p[i].x-p[j].x,2) + pow(p[i].y-p[j].y,2));
        printf("(%d) -> (%d) = %.2f\n", (i+1),(j+1),len);
        if(small==-1.0 || len < small){
          small=len;
          smallp=j;
        }
      }
    minLen+=small;
    printf("borda minima: %.2f at (%.2f, %.2f)\n", small,p[smallp].x, p[smallp].y);
    p[smallp].used=1;
    tot++;
  }
  printf("\nminLen = %f\n", minLen);
}

int main(){
  int i;
  scanf("%d",&V);
  for(i=0;i<V;i++)
    scanf("%f%f", &p[i].x, &p[i].y);
  printf("Arvore de Abrangencia Minima\n");
  prim();
  return 0;
}
