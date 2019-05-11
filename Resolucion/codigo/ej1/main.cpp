#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

typedef vector<vector<int>> Matriz;

void mostrar_matriz(const& Matriz m){
    for(auto& i : m){
        for(auto& j : i)
            cout<<j<<" ";
        cout<<endl;
    }
}

int main(int argc, char** argv){

    if (argc < 3){
        cout<<"ERROR: Faltan argumentos"<<endl;
    }

    // Leemos datos entrada
    int ancho = atoi(argv[1]);
    int alto = atoi(argv[2]);

    Matriz m(alto, vector<int>(ancho, 0));

    for(int i = 0; i < alto;i++)
        for(int j = 0; j < ancho;j++)
            m[i][j] = atoi(argv[3 + i*alto + j]);

    //mostrar_matriz(m);
    // Terminamos de leer
    
    return 0;
}
