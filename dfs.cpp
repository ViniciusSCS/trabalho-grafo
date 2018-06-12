// Grafos - DFS (busca em profundidade)

#include <iostream>
#include <list>
#include <algorithm>
#include <stack>

using namespace std;

class Grafo
{
	int V;
	list<int> *adj;

  public:
	Grafo(int V);
	void addAresta(int v1, int v2);

	void dfs(int v);
};

Grafo::Grafo(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Grafo::addAresta(int v1, int v2)
{

	adj[v1].push_back(v2);
}

void Grafo::dfs(int v)
{
	stack<int> pilha;
	bool vetorVisitado[V];

	for (int i = 0; i < V; i++)
		vetorVisitado[i] = false;

	while (true)
	{
		if (!vetorVisitado[v])
		{
			cout << "Visitando vertice " << v << " ...\n";
			vetorVisitado[v] = true;
			pilha.push(v);
		}

		bool a = false;
		list<int>::iterator it;

		for (it = adj[v].begin(); it != adj[v].end(); it++)
		{
			if (!vetorVisitado[*it])
			{
				a = true;
				break;
			}
		}

		if (a)
			v = *it;
		else
		{

			pilha.pop();

			if (pilha.empty())
				break;

			v = pilha.top();
		}
	}
}

int main()
{
	int V = 8;

	Grafo grafo(V);

	grafo.addAresta(0, 1);
	grafo.addAresta(0, 2);
	grafo.addAresta(1, 3);
	grafo.addAresta(1, 4);
	grafo.addAresta(2, 5);
	grafo.addAresta(2, 6);
	grafo.addAresta(6, 7);

	grafo.dfs(0);

	return 0;
}
