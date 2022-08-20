/*
trilha_euleriana_ra216741

George Gigilas Junior - 216741

Arquivo auxiliar que contém minha solução para o primeiro trabalho prático de MC558.
*/

#include <list>
#include <string>
#include <cmath>
#include <bits/stdc++.h>
#include "grafo.hpp"
#include "arvore_precedencia.hpp"

using namespace std;

bool pesos_validos(int W, Grafo g)
{
    for (int i = 0; i < g.V; i++)
    {
        list<std::pair<int, int>>::iterator iteracoes;

        for (iteracoes = g.adj[i].begin(); iteracoes != g.adj[i].end(); ++iteracoes)
        // Percorre todas as arestas acessiveis a partir de cada vertice
        {
            pair<int, int> itr = *iteracoes;
            if (itr.second < 0 || itr.second > W) // Verifica se os valores de peso estao dentro do intervalo (0, W)
            {
                return false;
            }
        }
    }

    return true;
}

bool pesos_inteiros(Grafo g)
{
    for (int i = 0; i < g.V; i++)
    {
        list<std::pair<int, int>>::iterator iteracoes;

        for (iteracoes = g.adj[i].begin(); iteracoes != g.adj[i].end(); ++iteracoes)
        // Percorre todas as arestas acessiveis a partir de cada vertice
        {
            pair<int, int> itr = *iteracoes;
            if (std::floor(itr.second) != itr.second) // Verifica se os valores de peso sao inteiros
            {
                return false;
            }
        }
    }

    return true;
}

void initialize_single_source(Grafo g, int s, int dist[], int pred[])
{
    for (int i = 0; i < g.V; i++) // Inicializa as distancias dos vertices como infinito, e os predecessores como -1
    {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[s] = 0; // Inicializa a distancia do vertice s como 0
}

void relax(int u, int v, int w, int dist[], int pred[], list<int> Q[])
{
    if (dist[v] > dist[u] + w) // Verifica se a distancia pode ser diminuida
    {
        dist[v] = dist[u] + w;    // Atualiza a distancia de v
        pred[v] = u;              // Atualiza o predecessor de v
        Q[dist[v]].push_front(v); // Adiciona v no inicio de sua lista correspondente do vetor de listas
    }
}

void dijkstra(Grafo g, int pred[], int dist[])
{
    int u, v, w;

    // Inicializando igual visto nas aulas
    initialize_single_source(g, 0, dist, pred);

    // Vetor de listas que armazenam as distancias relativas, cada lista do vetor corresponde a um vertice
    list<int> Q[g.W * g.V + 1];

    // Adicionando o vertice de origem a primeira lista de Q
    Q[0].push_back(0);

    int indice = 0;

    while (true)
    {

        while (Q[indice].empty() && indice < g.V * g.W) // Percorre as listas de cada vertice até encontrar uma lista nao vazia
        {
            indice++;
        }

        if (indice == g.V * g.W)
        { // Quando verificarmos a lista correspondente ao ultimo vertice, o algoritmo acabou
            break;
        }

        u = Q[indice].front(); // u eh o vertice ao qual a lista do vetor de listas corresponde
        Q[indice].pop_front(); // remove o u de sua lista correspondente do vetor, para indicar que ja foi processado

        list<std::pair<int, int>>::iterator iteracoes;

        for (iteracoes = g.adj[u].begin(); iteracoes != g.adj[u].end(); ++iteracoes)
        // Percorre todas as arestas acessiveis a partir do vertice u
        {
            pair<int, int> itr = *iteracoes;
            v = itr.first;                 // Encontra um v
            w = itr.second;                // Encontra o peso para ir de u a v
            relax(u, v, w, dist, pred, Q); // Faz o relax de u para v
        }
    }
}

bool arvore_precedencia(int n, int m, int W, Grafo g, string *mensagem, int *RA, int dist[], int pred[])
{
    (*RA) = 216741; // Atualiza o RA

    if (!pesos_validos(W, g))
    {
        (*mensagem) = "Erro: Existe peso fora do intervalo."; // Salva a mensagem de erro
        return false;                                         // Interrompe a execucao do programa e retorna falso
    }

    else if (!pesos_inteiros(g))
    {
        (*mensagem) = "Erro: Existe peso não inteiro."; // Salva a mensagem de erro
        return false;                                   // Interrompe a execucao do programa e retorna falso
    }

    dijkstra(g, pred, dist);

    return true;
}