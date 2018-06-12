#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>

#define FLSH gets(l)

int d, o, v = 0;
int custo, *c = NULL;

void dijkstra(int v,int o,int d,int *c)
{
    int i,v, cont = 0;
    int *ant, *tmp;
    int *z;     /* v para os quais se conhece o caminho minimo */
    double min;
    double dist[v]; /* vetor com os c dos caminhos */


    /* aloca as linhas da matriz */
    ant = (int *)calloc (v, sizeof(int));
    tmp = (int *)calloc (v, sizeof(int));
    if (ant == NULL)
    {
        printf ("** Erro: Memoria Insuficiente **");
        exit(-1);
    }

    z = (int *)calloc (v, sizeof(int));
    if (z == NULL)
    {
        printf ("** Erro: Memoria Insuficiente **");
        exit(-1);
    }

    for (i = 0; i < v; i++)
    {
        if (c[(o - 1) * v + i] !=- 1)
        {
            ant[i] = o - 1;
            dist[i] = c[(o-1)*v+i];
        }
        else
        {
            ant[i]= -1;
            dist[i] = HUGE_VAL;
        }
        z[i]=0;
    }
    z[o-1] = 1;
    dist[o-1] = 0;

    /* Laco principal */
    do
    {

        /* Encontrando o vertice que deve entrar em z */
        min = HUGE_VAL;
        for (i=0; i<v; i++)
            if (!z[i])
                if (dist[i]>=0 && dist[i]<min)
                {
                    min=dist[i];
                    v=i;
                }

        /* Calculando as distancias dos novos vizinhos de z */
        if (min != HUGE_VAL && v != d - 1)
        {
            z[v] = 1;
            for (i = 0; i < v; i++)
                if (!z[i])
                {
                    if (c[v*v+i] != -1 && dist[v] + c[v*v+i] < dist[i])
                    {
                        dist[i] = dist[v] + c[v*v+i];
                        ant[i] =v;
                    }
                }
        }
    }
    while (v != d - 1 && min != HUGE_VAL);

    /* Mostra o Resultado da busca */
    printf("\tDe %d para %d: \t", o, d);
    if (min == HUGE_VAL)
    {
        printf("Nao Existe\n");
        printf("\tCusto: \t- \n");
    }
    else
    {
        i = d;
        i = ant[i-1];
        while (i != -1)
        {
            //   printf("<-%d",i+1);
            tmp[cont] = i+1;
            cont++;
            i = ant[i];
        }

        for (i = cont; i > 0 ; i--)
        {
            printf("%d -> ", tmp[i-1]);
        }
        printf("%d", d);

        printf("\n\tCusto:  %d\n",(int) dist[d-1]);
    }
}

void limpar(void)
{
  
}

void cabecalho(void)
{
    limpar();
    printf("Implementacao do Algoritmo de Dijasktra\n");
    printf("Comandos:\n");
    printf("\t d - Adicionar um Grafo\n"
           "\t r - Procura Os Menores Caminhos no Grafo\n"
           "\t CTRL+c - Sair do programa\n");
    printf(">>> ");
}

void add(void)
{
    int i, j;

    do
    {
        printf("\nInforme o numero de v (no minimo 2 ): ");
        scanf("%d",&v);
    }
    while (v < 2 );

    if (!c)
        free(c);
    c = (int *) malloc(sizeof(int)*v*v);
    for (i = 0; i <= v * v; i++)
        c[i] = -1;

    printf("Entre com as Arestas:\n");
    do
    {
        do
        {
            printf("o da aresta (entre 1 e %d ou '0' para sair): ", v);
            scanf("%d",&o);
        }
        while (o < 0 || o > v);

        if (o)
        {
            do
            {
                printf("D da aresta (entre 1 e %d, menos %d): ", v, o);
                scanf("%d", &d);
            }
            while (d < 1 || d > v || d == o);

            do
            {
                printf("Custo (positivo) da aresta do vertice %d para o vertice %d: ",
                       o, d);
                scanf("%d",&custo);
            }
            while (custo < 0);

            c[(o-1) * v + d - 1] = custo;
        }

    }
    while (o);
}

void procurar(void)
{
    int i, j;

    /* Azul */
  
    printf("Lista dos Menores Caminhos no Grafo Dado: \n");

    for (i = 1; i <= v; i++)
    {
        for (j = 1; j <= v; j++)
            dijkstra(v, i,j, c);
        printf("\n");
    }

    printf("<Pressione ENTER para retornar ao menu principal>\n");
    /* Volta cor nornal */
   
}

int main(int argc, char **argv)
{
    int i, j;
    char opcao[3], l[50];

    do
    {

        cabecalho();
        scanf("%s", &opcao);

        if ((strcmp(opcao, "d")) == 0)
        {
            add();
        }
        FLSH;

        if ((strcmp(opcao, "r") == 0) && (v > 0) )
        {
            procurar();
            FLSH;
        }

    }
    while (opcao != "x");

    printf("\nAte a proxima...\n\n");

    return 0;
}
