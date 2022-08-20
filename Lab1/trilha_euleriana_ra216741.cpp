/*
trilha_euleriana_ra216741

George Gigilas Junior - 216741

Arquivo auxiliar que contém minha solução para o primeiro trabalho prático de MC558.
*/

#include <list>
#include <string>
#include <stack>
#include "grafo.hpp"
#include "trilha_euleriana.hpp"

using namespace std;

bool existe_vertice_inviavel(int n, int grauEntrada[], int grauSaida[], Grafo grafo)
{
    for (int i = 0; i < n; i++)
    {
        grauEntrada[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        grauSaida[i] = grafo.vizinhos[i].size(); // O calculo do grau de saida eh direto da lista de adjacencias

        list<int>::iterator iteracoes;

        for (iteracoes = grafo.vizinhos[i].begin(); iteracoes != grafo.vizinhos[i].end(); ++iteracoes)
        // Percorre todas as arestas acessiveis a partir de cada vertice
        {
            grauEntrada[*iteracoes]++; // Aumenta em 1 o grau de entrada do vertice alcancavel pelo vertice i
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (grauEntrada[i] != grauSaida[i]) // Retorna true se algum vertice tiver grau de entrada diferente do de saida
        {
            return true;
        }
    }

    return false; // Retorna false se nenhum vertice for inviavel
}

void DFS_visit(int vertice, Grafo grafo, bool visitado[])
// Algoritmo DFS_visit fortemente baseado no algoritmo DFS-visit visto em aula (implementado a partir dos slides)
{
    visitado[vertice] = true; // Marca o vertice como visitado

    list<int>::iterator iteracoes;

    for (iteracoes = grafo.vizinhos[vertice].begin(); iteracoes != grafo.vizinhos[vertice].end(); iteracoes++) // Percorre as arestas do vertice
    {
        if (visitado[*iteracoes] == false) // Verifica se o vertice ja foi visitado
        {
            DFS_visit(*iteracoes, grafo, visitado); // Visita o vertice
        }
    }
}

void DFS(Grafo grafo, bool visitado[])
// Algoritmo DFS fortemente baseado no algoritmo DFS visto em aula (implementado a partir dos slides)
// A principal diferenca eh que essa versao visita apenas os vertices alcancaveis pelo vertice escolhido (vertice 0, no caso)
{
    for (int i = 0; i < grafo.V; i++) // Seta todos os vertices como nao visitados, preparando para a busca
    {
        visitado[i] = false;
    }

    DFS_visit(0, grafo, visitado); // Visita o vertice 0 e faz um DFS a partir dele
}

Grafo inverterGrafo(Grafo grafo)
// Essa funcao eh responsavel por retornar um grafo de saida com os sentidos das arestas opostos aos do grafo de entrada
{
    Grafo invertido = Grafo(grafo.V, grafo.M); // Cria uma nova instancia de grafo, com os mesmos numeros de vertices e arestas

    for (int i = 0; i < grafo.V; i++) // Percorre os vertices
    {

        list<int>::iterator iteracoes;

        for (iteracoes = grafo.vizinhos[i].begin(); iteracoes != grafo.vizinhos[i].end(); ++iteracoes) // Percorre as arestas
        // Percorre todas as arestas acessiveis a partir de cada vertice
        {
            invertido.vizinhos[*iteracoes].push_back(i); // Adiciona a aresta ao grafo novo, com o sentido oposto ao do grafo original
        }
    }

    return invertido; // Retorna o grafo invertido
}

bool ehFortementeConexo(int n, Grafo grafo)
// Para o grafo ser fortemente conexo, deve haver uma unica componente conexa
// Uma forma de verificar se a componente eh fortemente conexa eh checar se a partir de um vertice pode-se atingir todos os vertices,
// tanto no grafo com ordem original quanto no grafo com os sentidos das arestas invertidos
{
    bool visitado[n]; // Vetor que guarda se o vertice foi ou nao foi visitado

    DFS(grafo, visitado); // Realiza DFS a partir de um UNICO VERTICE para checar os vertices alcancaveis a partir dele

    for (int i = 0; i < n; i++) // Caso algum vertice nao tenha sido visitado, o grafo nao eh fortemente conexo
    {
        if (visitado[i] == false)
        {
            return false;
        }
    }

    Grafo invertido = inverterGrafo(grafo); // Gera um grafo com sentidos das arestas invertidos

    DFS(invertido, visitado); // Realiza DFS a partir de um UNICO VERTICE para checar os vertices alcancaveis a partir dele, no grafo invertido

    for (int i = 0; i < n; i++) // Caso algum vertice nao tenha sido visitado, o grafo nao eh fortemente conexo
    {
        if (visitado[i] == false)
        {
            return false;
        }
    }

    return true; // Caso nao tenha retornado false, ele eh fortemente conexo
}

void constroiTrilhaEuleriana(Grafo grafo, int trilha[], int origem[], int destino[])
{
    int numeroVizinhos[grafo.V];                // Indica o numero de arestas que saem desse vertice
    list<int>::iterator proximaAresta[grafo.V]; // Indica a proxima aresta a ser visitada

    for (int i = 0; i < grafo.V; i++)
    {
        numeroVizinhos[i] = grafo.vizinhos[i].size(); // Preenche corretamente o vetor numeroVizinhos
        proximaAresta[i] = grafo.vizinhos[i].begin(); // Faz com que cada posicao do vetor proximaAresta aponte para o primeiro elemento da lista
    }

    stack<int> percorrendo;     // Pilha que armazenara o caminho percorrido
    percorrendo.push(0);        // Comeca no vertice 0, arbitrario
    int verticeAtual = 0;       // Guarda o vertice que esta sendo percorrido
    int contador = grafo.M - 1; // Guarda a posicao em que o vertice sera visitado

    while (!percorrendo.empty()) // Itera por novas arestas e pelos vertices
    {
        if (numeroVizinhos[verticeAtual] > 0) // Confere se pode chegar em uma nova aresta a partir dessa
        {
            percorrendo.push(verticeAtual);             // Empilha o vertice visitado
            numeroVizinhos[verticeAtual]--;             // Diminui o numero de arestas novas obtiveis a partir desse vertice
            int proximo = *proximaAresta[verticeAtual]; // Novo vertice que esta sendo percorrido eh o vertice obtido pela aresta

            if (numeroVizinhos[verticeAtual] > 0) // Caso haja mais arestas obtiveis, atualiza a proxima aresta, caso contrario, eh indiferente
            {
                proximaAresta[verticeAtual]++; // Atualiza a proxima aresta
            }

            verticeAtual = proximo; // Atualiza o vertice atual
        }

        else
        {
            trilha[contador + 1] = verticeAtual; // Adiciona o vertice atual no fim da trilha
            destino[contador] = verticeAtual;    // O vertice atual eh o destino da aresta q foi percorrida
            verticeAtual = percorrendo.top();    // Volta para o elemento que chegou nesse vertice
            origem[contador] = verticeAtual;     // O vertice desempilhado eh a origem da aresta que foi percorrida
            percorrendo.pop();                   // Remove o elemento que chegou nesse vertice da pilha
            contador--;
        }
    }
    trilha[0] = 0; // Seta a primeira posicao como 0, como foi definido anteriormente
}

bool trilha_euleriana(int n, int m, Grafo grafo, int origem[], int destino[], int trilha[], string *mensagem, int *RA)
{
    (*RA) = 216741; // Atualiza o RA

    int grauEntrada[n]; // Vetor que guarda os graus de entrada de cada vertice
    int grauSaida[n];   // Vetor que guarda os graus de saida de cada vertice

    if (existe_vertice_inviavel(n, grauEntrada, grauSaida, grafo)) // Verifica se existe vertice inviavel
    {
        (*mensagem) = "Erro: Existe vértice inviável."; // Salva a mensagem de erro
        return false;                                   // Interrompe a execucao do programa e retorna que nao achou trilha euleriana
    }
    else if (!ehFortementeConexo(n, grafo)) // Verifica se o grafo eh fortemente conexo
    {
        (*mensagem) = "Erro: Grafo não é fortemente conexo."; // Salva a mensagem de erro
        return false;                                         // Interrompe a execucao do programa e retorna que nao achou trilha euleriana
    }

    constroiTrilhaEuleriana(grafo, trilha, origem, destino); // Constroi a trilha euleriana

    return true; // Retorna true pois encontrou trilha euleriana
}