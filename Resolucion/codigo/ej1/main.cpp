#include <iostream>
#include <vector>
#include <stdlib.h>
#include <tuple>
#include <algorithm>
#include "disjoint_set.hpp"

using namespace std;

using matriz = vector<vector<int>>;
using eje = tuple<unsigned int, unsigned int, unsigned int>;

unsigned int w(const eje& e){return get<0>(e);}
unsigned int v(const eje& e){return get<1>(e);}
unsigned int u(const eje& e){return get<2>(e);}

void mostrar_matriz(const matriz& m){
    for(auto& i : m){
        for(auto& j : i)
            cout<<j<<" ";
        cout<<endl;
    }
}

// Como es un grafo, no un digrafo, podemos asumir en cada paso que ciertas aristas ya fueron agregadas
vector<eje> crear_aristas_vecinos(int i, int j, const matriz& m){
    vector<eje> res;

    int ancho = m[0].size();
    if(i+1 < int(m.size())){
        if(j-1 >= 0)
            res.push_back({abs(m[i][j] - m[i+1][j-1]), i*ancho + j, (i+1)*ancho + (j-1)});
        if(j+1 < ancho)
            res.push_back({abs(m[i][j] - m[i+1][j+1]), i*ancho + j, (i+1)*ancho + (j+1)});

        res.push_back({abs(m[i][j] - m[i+1][j]), i*ancho + j, (i+1)*ancho + j});
    }

    if(j+1 < ancho)
        res.push_back({abs(m[i][j] - m[i][j+1]), i*ancho + j, i*ancho + (j+1)});

    return res;
}

int main(int argc, char** argv){

    if (argc < 3){
        cout<<"ERROR: Faltan argumentos"<<endl;
    }

    // Leemos datos entrada
    int ancho = atoi(argv[1]);
    int alto = atoi(argv[2]);

    matriz m(alto, vector<int>(ancho, 0));

    for(int i = 0; i < alto;i++)
        for(int j = 0; j < ancho;j++)
            m[i][j] = atoi(argv[3 + i*alto + j]);

    /* mostrar_matriz(m); */

    // Terminamos de leer

    // Armamos lista de aristas
    vector<eje> E;
    for(int i = 0;i < alto; i++){
        for(int j = 0;j < ancho;j++){
            vector<eje> vecinos(crear_aristas_vecinos(i, j, m));
            for(auto & k : vecinos)
                E.push_back(k);
        }
    }

    // Ordenamos lista de aristas por peso
    sort(E.begin(), E.end());
    
    /* Mostramos lista de aristas */
    /* for(auto& i : E) */
    /*     cout<<"("<<v(i)<<", "<<u(i)<<", "<<w(i)<<") "; */
    /* cout<<endl; */
    
    return 0;
}
