#ifndef FLOYD_HPP
#define FLOYD_HPP

#include "tipos_aux.h"
using namespace std;

Matriz floyd(const Matriz& W){
    int n = W.size();
    Matriz D;
    resizeMatriz(D, n, n);
    for(int i = 0;i < n;i++)D[i][i] = 0;
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            if(i != j)D[i][j] = W[i][j];
    for(int k = 0;k < n;k++)
        for(int i = 0;i < n;i++)
            for(int j = 0;j < n;j++)
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
    return D;
}
#endif
