#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <tuple>
#include "tipos_aux.h"

using namespace std;

vector<int> bellmanFord_aux_adyacencia(int s, const listaAdyacencia& W)
{
    int n = W.size();
    vector<int> dist(n+1, infty);
    vector<vector_element_t> S;

    for(int i = 0;i < n; i++)
        for(unsigned int j = 0;j < W[i].size(); j++) 
            S.push_back({get<1>(W[i][j]), i,(int) get<0>(W[i][j])});

    dist[s] = 0;
    vector<vector_element_t>::iterator it;
    for(int i=1;i<n;i++){
        for(it = S.begin();it!=S.end();++it){
            int c = (*it).peso;
            int u = (*it).destino;
            int v = (*it).origen;

            if(dist[v] + c < dist[u])
                dist[u] = dist[v] + c;
        }
    }

    // for(it = S.begin();it!=S.end();++it){
    //     int c = get<0>(*it);
    //     int v = get<1>(*it);
    //     int u = get<2>(*it);
    //     if(dist[v] + c < dist[u]){
    //         cout << "ERROR: TIENE CICLO NEGATIVO" << endl;
    //         break;
    //     }
    // }

    return dist;
}

/*
vector<int> bellmanFord_aux(int s, const Matriz& W) {
    int n = W.size();
    vector<int> dist(n+1, infty);
    vector<tuple<int, int, int>> S;
    S.resize(n);

    for(int i = 0;i < n; i++)
        for(int j = 0;j < n; j++) 
            S.push_back({W[i][j], i, j});

    dist[s] = 0;
    vector<tuple<int, int, int>>::iterator it;
    for(int i=1;i<n;i++){
        for(it = S.begin();it!=S.end();++it){
            int c = get<0>(*it);
            int u = get<1>(*it);
            int v = get<2>(*it);

            if(dist[u] + c < dist[v])
                dist[v] = dist[u] + c;
        }
    }

    for(it = S.begin();it!=S.end();++it){
        int c = get<0>(*it);
        int u = get<1>(*it);
        int v = get<2>(*it);
        if(dist[u] + c < dist[v]){
            cout << "ERROR: TIENE CICLO NEGATIVO" << endl;
            break;
        }
    }

    return dist;
}
*/

Matriz bellmanFord(int n, int m, const listaAdyacencia& W, const vector<int>& mapeo)
{
    Matriz res;
    resizeMatriz(res, n, m+1);
    for(int i = 0;i < n;i++)
        res[i] = bellmanFord_aux_adyacencia(mapeo[i], W);
    return res;
}

vector<int> bellmanFord_opt_aux_adyacencia(int s, const listaAdyacencia& W)
{
    int n = W.size();
    vector<int> res(n+1, infty);

    queue<tuple<int, int, int>> S;
    for(unsigned int i = 0;i <  W[s].size(); i++)
        if((int)i != s && get<1>(W[s][i]) != infty)
            S.push({-get<1>(W[s][i]), s, get<0>(W[s][i])});

    while(!S.empty()){
        auto t = S.front();
        S.pop();
        int c = get<0>(t);
        int u = get<2>(t);

        if(res[u] == infty){
            res[u] = -c;
            for(unsigned int j = 0;j < W[u].size(); j++)
                if(res[j] == infty)
                    S.push({c-get<1>(W[u][j]), u, get<0>(W[u][j])});
        }
    }
    return res;
}

/*
vector<int> bellmanFord_opt_aux(int s, const Matriz& W)
{
    int n = W.size();
    vector<int> res(n+1, infty);

    queue<tuple<int, int, int>> S;
    for(int i = 0;i < n; i++)
        if(i != s && W[s][i] != infty)
            S.push({-W[s][i], s, i});

    while(!S.empty()){
        auto t = S.front();
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
*/

Matriz bellmanFord_opt(int n, int m, const listaAdyacencia& W, const vector<int>& mapeo)
{
    Matriz res;
    resizeMatriz(res, n, m+1);
    for(int i = 0;i < n;i++)
        res[i] = bellmanFord_opt_aux_adyacencia(mapeo[i], W);
    return res;
}
