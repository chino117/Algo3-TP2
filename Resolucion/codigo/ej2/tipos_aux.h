#ifndef TIPOS_AUX_H
#define TIPOS_AUX_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef vector<vector<int>> Matriz;
typedef vector<vector<tuple<int,int,int>>> MatrizRes;
const int infty = 10e5;


void resizeMatriz( Matriz &m , const int fils , const int cols )
{
    m.resize(fils);
    for(auto &it : m)
        it.resize(cols, infty);
}

void resizeMatrizRes( MatrizRes &m , const int fils , const int cols )
{
    m.resize(fils);
    for(auto &it : m)
        it.resize(cols);
}

// Estructura que devuelven los algoritmos pedidos
// Contiene los caminos minimos y metodo utilizado
struct ResultadoProblema{
    unsigned int metodo;
    Matriz g;
};

// Estructura que contiene los datos de entrada del problema
struct DatosProblema
{
	int capacidad = 60;
	int n; //Cantidad de ciudades
	int m; //Cantidad de rutas
	vector<int> costoXciudad;
	Matriz litrosXeje;
};

// Operaciones de DatosProblema
istream& operator>>(istream& is, DatosProblema& d)
{

    is>>d.n >> d.m;
    if (d.n < 0 || d.m < 0)
    {
        cout<<"ERROR: Valores asignados a DatosProblema invalidos"<<endl;
        return is;
    }

    d.costoXciudad.resize(d.n);
    resizeMatriz(d.litrosXeje, d.n, d.n);

    for(int i = 0;i < d.n; i++)
        is>>d.costoXciudad[i];

    int a_i,b_i,l_i;
    for(int i = 0;i < d.m;i++){
        is>>a_i>>b_i>>l_i;
        d.litrosXeje[a_i-1][b_i-1] = l_i;
        d.litrosXeje[b_i-1][a_i-1] = l_i;
    }

    return is;
}

ostream& operator<<(ostream& os, const DatosProblema& d)
{
    os<<d.n<<" "<<d.m<<endl;
    os<<"\n"<<endl;
    for(int i = 0;i < d.n;i++)
        os<<d.costoXciudad[i]<<"\n"<<endl;

    for(int i = 0;i < d.n;i++){
        for(int j = 0;j < d.n;j++){
            os<<d.litrosXeje[i][j]<<" "<<endl;
        }
        os<<"\n"<<endl;
    }

    return os;
}

DatosProblema leer_datos(istream& is)
{
    DatosProblema res;
    is>>res;
    return res;
}


#endif
