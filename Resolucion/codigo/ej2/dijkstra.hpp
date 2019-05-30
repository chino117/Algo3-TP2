#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <tuple>
#include "tipos_aux.h"

using namespace std;

struct vector_element_t{
	int peso;
	int origen;
	int destino;
};

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

vector<int> dijkstra_aux_arreglo(int s, const Matriz& W)
{
    int n = W.size();
    vector<int> res(n+1, infty);

    vector<vector_element_t> S;
    for(int i = 0;i < n; i++)
        if(i != s && W[s][i] != infty)
            S.push_back({W[s][i], s, i});
	
    while(!S.empty()){
        auto top_index = vector_top_index(S);
        auto t = S[top_index];
        if(top_index != (int)S.size()-1)
                swap(S[top_index],S.back());
		
        S.pop_back();
        int c = t.peso;
        int u = t.destino;
        if(res[u] == infty){
            res[u] = c;
            for(int j = 0;j < n; j++)
                if(res[j] == infty)
                    S.push_back({c+W[u][j], u, j});
        }
    }
    return res;
}

Matriz dijkstra_arreglo(int n, const Matriz& W, const vector<int>& mapeo){
    Matriz res;
    resizeMatriz(res, n, W.size()+1);
    for(int i = 0;i < n;i++)
        res[i] = dijkstra_aux_arreglo(mapeo[i], W);
    return res;
}

vector<int> dijkstra_aux_prioridad(int s, const Matriz& W)
{
    int n = W.size();
    vector<int> res(n+1, infty);

    priority_queue<tuple<int, int, int>> S;
    for(int i = 0;i < n; i++)
        if(i != s && W[s][i] != infty)
            S.push({-W[s][i], s, i});

    while(!S.empty()){
        auto t = S.top();
        S.pop();
        int c = get<0>(t);
        int u = get<2>(t);
        // int v = get<1>(t); // no se usa

        if(res[u] == infty){
            res[u] = -c;
            for(int j = 0;j < n; j++)
                if(res[j] == infty)
                    S.push({c-W[u][j], u, j});
        }
    }
    return res;
}

Matriz dijkstra_prioridad(int n, const Matriz& W, const vector<int>& mapeo){
    Matriz res;
    resizeMatriz(res, n, W.size()+1);
    for(int i = 0;i < n;i++)
        res[i] = dijkstra_aux_prioridad(mapeo[i], W);
    return res;
}

