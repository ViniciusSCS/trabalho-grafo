#include <stdio.h>
#include <math.h>
#define MAX 10000

typedef struct
{
  float x, y;
  int used;
} Point;

Point p[MAX];
int V;

int prim()
{
  int i, j;

  int qtdVert;

  int pontoCandidatoP;

  float pontoCandidatoMin;

  float len;

  float minLen;

  qtdVert = p[0].used = 1;
  while (qtdVert<V)
    {
      pontoCandidatoMin = -1.0;

      for (i = 0; i < V; i++)
        if (p[i].used)

          for (j = 0; j < V; j++)
            if (!p[j].used)
            {
              len = sqrt(pow(p[i].x - p[j].x, 2) + pow(p[i].y - p[j].y, 2));
              printf("(%d) -> (%d) = %.2f\n", (i + 1), (j + 1), len);
              if (pontoCandidatoMin == -1.0 || len < pontoCandidatoMin)
              {
                pontoCandidatoMin = len;
                pontoCandidatoP = j;
              }
            }
      minLen += pontoCandidatoMin;
      printf("borda minima: %.2f at (%.2f, %.2f)\n", pontoCandidatoMin, p[pontoCandidatoP].x, p[pontoCandidatoP].y);
      p[pontoCandidatoP].used = 1;
      qtdVert++;
    }
  printf("\nminLen = %f\n", minLen);
}

int main()
{
  int i;
  scanf("%d", &V);
  for (i = 0; i < V; i++)
    scanf("%f%f", &p[i].x, &p[i].y);
  printf("Arvore de Abrangencia Minima\n");
  prim();
  return 0;
}
