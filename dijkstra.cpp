#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>

#define FLSH gets(l)

int d, o, vert = 0;
int custo, *c = NULL;

void dijkstra(int vert,int o,int d,int *c)
{
    int i, v, cont = 0;
    int *ant, *tmp;
    int *z;
    double min;
    double dist[vert];


    
    ant = (int *)calloc (vert, sizeof(int));
    tmp = (int *)calloc (vert, sizeof(int));
    if (ant == NULL)
    {
        printf ("** Erro: Memoria Insuficiente **");
        exit(-1);
    }

    z = (int *)calloc (vert, sizeof(int));
    if (z == NULL)
    {
        printf ("** Erro: Memoria Insuficiente **");
        exit(-1);
    }

    for (i = 0; i < vert; i++)
    {
        if (c[(o - 1) * vert + i] !=- 1)
        {
            ant[i] = o - 1;
            dist[i] = c[(o-1)*vert+i];
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

    
    do
    {

        
        min = HUGE_VAL;
        for (i=0; i<vert; i++)
            if (!z[i])
                if (dist[i]>=0 && dist[i]<min)
                {
                    min=dist[i];
                    v=i;
                }

        
        if (min != HUGE_VAL && v != d - 1)
        {
            z[v] = 1;
            for (i = 0; i < vert; i++)
                if (!z[i])
                {
                    if (c[v*vert+i] != -1 && dist[v] + c[v*vert+i] < dist[i])
                    {
                        dist[i] = dist[v] + c[v*vert+i];
                        ant[i] =v;
                    }
                }
        }
    }
    while (v != d - 1 && min != HUGE_VAL);

    
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
        printf("\nInforme o numero de vert (no minimo 2 ): ");
        scanf("%d",&vert);
    }
    while (vert < 2 );

    if (!c)
        free(c);
    c = (int *) malloc(sizeof(int)*vert*vert);
    for (i = 0; i <= vert * vert; i++)
        c[i] = -1;

    printf("Entre com as Arestas:\n");
    do
    {
        do
        {
            printf("o da aresta (entre 1 e %d ou '0' para sair): ", vert);
            scanf("%d",&o);
        }
        while (o < 0 || o > vert);

        if (o)
        {
            do
            {
                printf("d da aresta (entre 1 e %d, menos %d): ", vert, o);
                scanf("%d", &d);
            }
            while (d < 1 || d > vert || d == o);

            do
            {
                printf("Custo (positivo) da aresta do vertice %d para o vertice %d: ",
                       o, d);
                scanf("%d",&custo);
            }
            while (custo < 0);

            c[(o-1) * vert + d - 1] = custo;
        }

    }
    while (o);
}

void procurar(void)
{
    int i, j;

    /* Azul */
  
    printf("Lista dos Menores Caminhos no Grafo Dado: \n");

    for (i = 1; i <= vert; i++)
    {
        for (j = 1; j <= vert; j++)
            dijkstra(vert, i,j, c);
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

        if ((strcmp(opcao, "r") == 0) && (vert > 0) )
        {
            procurar();
            FLSH;
        }

    }
    while (opcao != "x");

    printf("\nAte a proxima...\n\n");

    return 0;
}
