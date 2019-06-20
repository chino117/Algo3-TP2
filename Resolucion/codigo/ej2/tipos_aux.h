#ifndef TIPOS_AUX_H
#define TIPOS_AUX_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <tuple>

using namespace std;

typedef vector<vector<int>> Matriz;
typedef vector<vector<tuple<int,int,int>>> MatrizRes;
const int infty = 10e5;

struct vector_element_t{
    int peso;
    int origen;
    int destino;
};

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

typedef vector<vector<tuple<int, int>>> listaAdyacencia;

listaAdyacencia convertirAListaAdyacencia(const Matriz& m, int default_val = infty){
    vector<tuple<int, int>> vacio;
    listaAdyacencia res(m.size(), vacio);
    for(unsigned int i = 0;i < m.size();i++)
        for(unsigned int j = 0;j < m.size();j++)
            if(i != j && m[i][j] != default_val)
                res[i].push_back({j, m[i][j]});
    return res;
}

void mostrarListaAdyacencia(const listaAdyacencia& a){
    int f = 0;
    for(auto& i : a){
        cout<<f<<": ";
        for(auto& j : i)
            cout<<"("<<get<0>(j)<<", "<<get<1>(j)<<")"<<" ";
        cout<<endl;
        f++;
    }
}

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

/* class Costos{ */
/*     public: */
/*         int& operator[](unsigned int i){ */
/*             if(usa_matriz) */
/*                 return (*m)[i]; */
/*             else */
/*                 return get<1>((*adj)[i]); */
/*         }; */
/*         int& operator[](unsigned int i){} const{ */
/*             if(usa_matriz) */
/*                 return (*m)[i]; */
/*             else */
/*                 return get<1>((*adj)[i]); */
/*         }; */
/*     private: */
/*         Costos(vector<int>* v):usa_matriz(true),m(v),adj(nullptr){}; */
/*         Costos(vector<tuple<int, int>>* v):usa_matriz(false),m(nullptr),adj(v){}; */
/*         bool usa_matriz; */
/*         vector<int>* m; */
/*         vector<tuple<int, int>>* adj; */
/*         friend class Grafo; */
/* } */

/* class Grafo{ */
/*     public: */
/*         Grafo(unsigned int n); */
/*         vector<int> vecindario(unsigned int i) const; */
/*         Costos operator[](unsigned int i){ */
/*         }; */
/*         Costos operator[](unsigned int i) const; */
/*     private: */
/*         unsigned int n; */
/*         unsigned int m; */
/*         unique_ptr<Matriz> m; */
/*         unique_ptr<listaAdyacencia> adj; */
/* }; */

#endif
