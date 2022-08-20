#include <string>
#include "grafo.hpp"

// Funcao principal que calcula o caminho minimo de um vertice inicial s ate os outros vertices
// Se nao tiver erros, ela retorna True e preenche os vetores de precedencia e de distancia
// Caso contrario, ele retorna False e preenche a string mensagem com o motivo de ter dado erro
bool arvore_precedencia(int n, int m, int W, Grafo g, string *mensagem, int *RA, int dist[], int pred[]);

// Funcao que verifica se os pesos estao no intervalo (0, W)
// Se estiverem, retorna true, senao, retorna false
bool pesos_validos(int W, Grafo g);

// Funcao que verifica se os pesos sao todos inteiros
// Se forem, retorna true, senao, retorna false
bool pesos_inteiros(Grafo g);

// Funcao que inicializa as distancias com infinito e os predecessores como -1, e a distancia do vertice s como 0
// Baseada na funcao dos slides das aulas
void initialize_single_source(Grafo g, int s, int dist[], int pred[]);

// Funcao que verifica se eh possivel diminuir o caminho ate um determinado vertice, e diminui se for possivel
// Baseada na funcao dos slides das aulas
void relax(int u, int v, int w, int dist[], int pred[], list<int>::iterator iterators[], list<int> Q[]);

// Funcao que percorre os vertices e as arestas em busca do caminho minimo, e preenche os vetores de distancia e de precedencia
void dijkstra(Grafo g, int pred[], int dist[]);