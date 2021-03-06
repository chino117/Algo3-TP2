#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <tuple>
#include "tipos_aux.h"

using namespace std;

int vector_top_index(vector<vector_element_t> values){
    int result = -1;
    int min;
    bool first = true;
    for(int i=0;i< (int)values.size();i++){
        if(first || values[i].peso < min){
            first = false;
            min = values[i].peso;
            result = i;
        }
    }
    return result;
}

vector<int> dijkstra_aux_arreglo_adyacencia(int s, const listaAdyacencia& W)
{
    int n = W.size();
    vector<int> res(n+1, infty);

    vector<vector_element_t> S;
    for(unsigned int i = 0;i < W[s].size();i++)
        S.push_back({get<1>(W[s][i]), s, get<0>(W[s][i])});
	
    while(!S.empty()){
        auto top_index = vector_top_index(S);
        auto t = S[top_index];
        if(top_index != (int)S.size()-1)
                swap(S[top_index], S.back());
		
        S.pop_back();
        int c = t.peso;
        int u = t.destino;
        if(res[u] == infty){
            res[u] = c;
            for(unsigned int j = 0;j < W[u].size();j++)
                S.push_back({c+get<1>(W[u][j]), u, get<0>(W[u][j])});
        }
    }
    return res;
}

Matriz dijkstra_arreglo(int n, int m, const listaAdyacencia& W, const vector<int>& mapeo){
    Matriz res;
    resizeMatriz(res, n, m+1);
    for(int i = 0;i < n;i++)
        res[i] = dijkstra_aux_arreglo_adyacencia(mapeo[i], W);
    return res;
}

vector<int> dijkstra_aux_prioridad_adyacencia(int s, const listaAdyacencia& W)
{
    int n = W.size();
    vector<int> res(n+1, infty);

    priority_queue<tuple<int, int, int>> S;
    for(unsigned int i = 0;i < W[s].size(); i++)
        S.push({-get<1>(W[s][i]), s, get<0>(W[s][i])});

    while(!S.empty()){
        auto t = S.top();
        S.pop();
        int c = get<0>(t);
        int u = get<2>(t);

        if(res[u] == infty){
            res[u] = -c;
            for(unsigned int j = 0;j < W[u].size();j++)
                S.push({c-get<1>(W[u][j]), u, get<0>(W[u][j])});
        }
    }

    return res;
}

Matriz dijkstra_prioridad(int n, int m, const listaAdyacencia& W, const vector<int>& mapeo){
    Matriz res;
    resizeMatriz(res, n, m+1);
    for(int i = 0;i < n;i++)
        res[i] = dijkstra_aux_prioridad_adyacencia(mapeo[i], W);
    return res;
}

