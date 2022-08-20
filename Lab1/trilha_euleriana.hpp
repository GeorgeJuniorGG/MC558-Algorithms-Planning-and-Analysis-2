#include <string>
#include "grafo.hpp"

// Funcao principal que verifica se o grafo possui trilha euleriana
// Se tiver, ela retorna True e preenche os vetores origem, destino e trilha com a trilha
// Caso contrario, ele retorna False e preenche a string mensagem com o motivo de nao ter trilha
bool trilha_euleriana(int n, int m, Grafo grafo, int origem[], int destino[], int trilha[], string *mensagem, int *RA);

// Funcao que, assumindo que o grafo possui trilha euleriana, constroi a trilha euleriana e guarda nos vetores origem, destino e trilha
void constroiTrilhaEuleriana(Grafo grafo, int trilha[], int origem[], int destino[]);

// Funcao que verifica se o grafo eh fortemente conexo
bool ehFortementeConexo(int n, Grafo grafo);

// Funcao que recebe um grafo G e retorna um grafo G' que corresponde ao grafo G com sentido das arestas invertido
Grafo inverterGrafo(Grafo grafo);

// Funcao que realiza a busca por profundidade, baseada na funcao dos slides da aula
void DFS(Grafo grafo, bool visitado[]);

// Funcao auxiliar para DFS que realiza as visitas nos vertices
void DFS_visit(int vertice, Grafo grafo, bool visitado[]);

// Funcao que verifica se existe algum vertice com grau de entrada diferente do grau de saida
bool existe_vertice_inviavel(int n, int grauEntrada[], int grauSaida[], Grafo grafo);