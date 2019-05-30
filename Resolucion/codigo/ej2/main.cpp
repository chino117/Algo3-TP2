#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include "tipos_aux.h"
#include "dijkstra.hpp"
#include "floyd.hpp"
#include "bellmanFord.hpp"

using namespace std;

string nombres_metodos[4] = {
                                "Dijkstra",
                                "Dijkstra con cola de prioridad",
                                "Bellman-Ford",
                                "Floyd-Warshall"
                            };

void escribir_tiempo(int metodo, int n, int m, chrono::duration<double, milli> tiempo, string path){
    fstream f("ej2_tiempos.csv", fstream::app | fstream::out);
    if(f.good())
        f<<path.substr(path.rfind("/")+1, path.length())<<","<<n<<","<<m<<","<<nombres_metodos[metodo]<<","<<tiempo.count()<<endl;
    f.close();
}

// Por como esta armado dijsktra, los indices de las filas se corresponden con indices de vertices de G
// Mientras que en Floyd se corresponden con indices de vertices de H
// Por eso hace falta el flag de mapeo_en_ambos
void mostrar_output(int n, const Matriz& costos, const vector<int>& mapeo, bool mapeo_en_ambos=false)
{
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(i != j){
                if(mapeo_en_ambos)
                    cout<<i<<" "<<j<<" "<<costos[mapeo[i]][mapeo[j]]<<endl;
                else
                    cout<<i<<" "<<j<<" "<<costos[i][mapeo[j]]<<endl;
            }
        }
    }
}

chrono::duration<double, milli> camMinimo(int n, int metodo, const Matriz& H, const vector<int>& mapeoGH){
    Matriz res;
    bool mapeo_en_ambos = false;
    chrono::duration<double, milli> tiempo;

    switch(metodo){
        case 0:
            {
                auto start_time = chrono::steady_clock::now();
                res = dijkstra_1(n, H, mapeoGH);
                auto end_time = chrono::steady_clock::now();
                tiempo = chrono::duration<double, milli>(end_time - start_time);
                break;
            }
        case 1:
            {
                auto start_time = chrono::steady_clock::now();
                res = dijkstra_2(n, H, mapeoGH);
                auto end_time = chrono::steady_clock::now();
                tiempo = chrono::duration<double, milli>(end_time - start_time);
                break;
            }
        case 2:
            {
                auto start_time = chrono::steady_clock::now();
                res = bellmanFord(n, H, mapeoGH);
                auto end_time = chrono::steady_clock::now();
                tiempo = chrono::duration<double, milli>(end_time - start_time);
                break;
            }
        case 3:
            {
                auto start_time = chrono::steady_clock::now();
                res = floyd(H);
                auto end_time = chrono::steady_clock::now();
                tiempo = chrono::duration<double, milli>(end_time - start_time);
                mapeo_en_ambos = true;
                break;
            }
        case 4:
            {
               //  res = dijkstra_1(n, H, mapeoGH);
               //  cout<<"Djikstra-Arreglo"<<endl;
               //  mostrar_output(n, res, mapeoGH);

                res = dijkstra_2(n, H, mapeoGH);
                cout<<"Djikstra-cola"<<endl;
                mostrar_output(n, res, mapeoGH);

                res = bellmanFord(n, H, mapeoGH);
                cout<<"Bellman-Ford"<<endl;
                mostrar_output(n, res, mapeoGH);

                res = floyd(H);
                cout<<"Floyd-Warshall"<<endl;
                mostrar_output(n, res, mapeoGH, true);
                exit(0);
                break;
            }
        default:
                cout<<"ERROR: Parametro de metodo incorrecto"<<endl;
                exit(-1);
                break;
    }
    //escribir_tiempo(metodo, tiempo, filename);
    mostrar_output(n, res, mapeoGH, mapeo_en_ambos);
    return tiempo;
}

Matriz armar_nuevo_grafo (DatosProblema data){
    int capacidad = data.capacidad + 1; 
    Matriz res;
    resizeMatriz(res, data.n * capacidad, data.n * capacidad);
    for (int i = 0; i < data.n; i++){
        int costoSrc = data.costoXciudad[i];

        for(int litrosSrc = 0; litrosSrc < capacidad; litrosSrc++){         
            int indexSrc = i * capacidad + litrosSrc;

            for(int j = 0; j < data.n; j++){
                int distancia = data.litrosXeje[i][j];

                for(int litrosDst = 0; litrosDst < capacidad; litrosDst++ ){
                    int indexDst = j * capacidad + litrosDst;
                    int costo = infty;
                    if(distancia > 0 && litrosSrc - distancia <= litrosDst)
                        costo = (litrosDst + distancia - litrosSrc) * costoSrc;
                    res[indexSrc][indexDst] = costo;
                }
            }
        }
    }
    return res;
}



int main(int argc, char** argv){
    DatosProblema r;
    int metodo;
    string path("");

    if(argc >= 2){
        path = argv[1];
        ifstream input (path);
        r = leer_datos(input);
    }
    else
        r = leer_datos(cin);
   
    if(argc > 2) 
        metodo = atoi(argv[argc-1]);
    else
        metodo = 0;

    Matriz H = armar_nuevo_grafo(r);
    // Armo mapeo de vertices de G a los de H que sean iniciales. Ej: de 1 a (1, 0), de 2 a (2, 0), etc
    vector<int> mapeoGH(r.n, 0);
    for(int i = 0;i < r.n;i++)
        mapeoGH[i] = i*(r.capacidad+1);

    auto tiempo = camMinimo(r.n, metodo, H, mapeoGH);
    escribir_tiempo(metodo, r.n, r.m, tiempo, path);

    return 0;
}
