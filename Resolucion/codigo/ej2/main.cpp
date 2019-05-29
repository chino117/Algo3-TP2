#include <iostream>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include "tipos_aux.h"
#include "dijkstra.hpp"
#include "floyd.hpp"
#include "bellmanFord.hpp"

using namespace std;

void prueba() {
    /* cantidad total de nodos */
   int numNodos = 8;
 
   /* Definiendo la matriz de adyacencia */
   Matriz A;
   int i, j;

   resizeMatriz(A, numNodos, numNodos);

   /* por simplicidad, completamos solo los pares de nodos conectados */
   A[0][1] = 16;
   A[0][2] = 10;
   A[0][3] = 5;
 
   A[1][0] = 16;
   A[1][2] = 2;
   A[1][5] = 4;
   A[1][6] = 6;
 
   A[2][0] = 10;
   A[2][1] = 2;
   A[2][3] = 4;
   A[2][4] = 10;
   A[2][5] = 12;
 
   A[3][0] = 5;
   A[3][2] = 4;
   A[3][4] = 15;
 
   A[4][2] = 10;
   A[4][3] = 15;
   A[4][5] = 3;
   A[4][7] = 5;
 
   A[5][1] = 4;
   A[5][2] = 12;
   A[5][4] = 3;
   A[5][6] = 8;
   A[5][7] = 16;
 
   A[6][1] = 6;
   A[6][5] = 8;
   A[6][7] = 7;
 
   A[7][4] = 5;
   A[7][5] = 16;
   A[7][6] = 7;
 
   /* Imprimir la matriz de adyacencia */
   cout << "Matriz de adyacencia:" << endl << endl;
   for ( i = 0; i < 8; i++ ) {
      for ( j = 0; j < 8; j++ )
         cout << setw(2) << A[i][j] << "  ";
      cout << endl;
   }
   cout << endl;
 
   /* calcular dijkstra a partir del nodo 0, a partir del nofo 7 */
   dijkstraAuxEjemplo( numNodos, A, 0, 7 ); 
}

// Por como esta armado dijsktra, los indices de las filas se corresponden con indices de vertices de G
// Mientras que en Floyd se corresponden con indices de vertices de H
// Por eso hace falta el flag de mapeo_en_ambos
void mostrar_output(int n, const Matriz& costos, const vector<int>& mapeo, bool mapeo_en_ambos=false)
{
    // TODO: Como esta ahora muestra segun el orden de los vertices en G, no segun el orden del input
    // Falta hacer un mapeo de G al orden del input y usarlo para mostrar bien las cosas
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

void camMinimo(int n, int metodo, const Matriz& H, const vector<int>& mapeoGH){
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
                cout<<"Djikstra-Arreglo"<<endl;
                break;
            }
        case 1:
            {
                auto start_time = chrono::steady_clock::now();
                res = dijkstra_2(n, H, mapeoGH);
                auto end_time = chrono::steady_clock::now();
                tiempo = chrono::duration<double, milli>(end_time - start_time);
                cout<<"Djikstra-cola"<<endl;
                break;
            }
        case 2:
            {
                auto start_time = chrono::steady_clock::now();
                res = bellmanFord(n, H, mapeoGH);
                auto end_time = chrono::steady_clock::now();
                tiempo = chrono::duration<double, milli>(end_time - start_time);
                cout<<"Bellman-Ford"<<endl;
                break;
            }
        case 3:
            {
                auto start_time = chrono::steady_clock::now();
                res = floyd(H);
                auto end_time = chrono::steady_clock::now();
                tiempo = chrono::duration<double, milli>(end_time - start_time);
                cout<<"Floyd-Warshall"<<endl;
                mapeo_en_ambos = true;
                break;
            }
        case 4:
            {
                res = dijkstra_1(n, H, mapeoGH);
                cout<<"Djikstra-Arreglo"<<endl;
                mostrar_output(n, res, mapeoGH);

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

    if(argc >= 2){
        ifstream input (argv[1]);
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

    camMinimo(r.n, metodo, H, mapeoGH);

    /* auto nuevo_grafo = armar_nuevo_grafo(r); */
    /* Matriz nueva_matriz = get<2>(nuevo_grafo); */
    /* int nuevo_n = get<0>(nuevo_grafo); */
    /* int destino_nodo_inicial = get<1>(nuevo_grafo) ; */
    /* int origen_nodo_inicial = 0; */


    /* auto matriz_distancias = dijkstraAuxEjemplo(nuevo_n, nueva_matriz, origen_nodo_inicial, destino_nodo_inicial); */ 

    /* /1* Ruta desde el nodo 'a' hasta el nodo 'b' *1/ */
    /* int longitud = 2; */
    /* int nodo_final = -1; */
    /* int min= infty; */
    /* for(int res = destino_nodo_inicial; res < nuevo_n; res++){ */
    /*     if(matriz_distancias[res].coste < min){ */
    /*         min = matriz_distancias[res].coste; */
    /*         nodo_final = res; */
    /*     } */
    /* } */
    /* while ( ( nodo_final = matriz_distancias[nodo_final].prev ) != origen_nodo_inicial ){ */
    /*     longitud++;    /1* primero estimamos la longitud de la ruta *1/ */
    /* } */ 	
    /* vector<int> ruta(longitud, 0);      /1* array de nodos de la ruta minima *1/ */
    /* ruta[longitud - 1] = destino_nodo_inicial;      		/1* luego rellenamos *1/ */
    /* int i = destino_nodo_inicial; */
    /* for (int j = 1; j < longitud; j++ ) { */
    /*     i = matriz_distancias[i].prev; */
    /*     ruta[longitud - j - 1] = i; */
    /* } */

   
    /* cout << "================================================================" << endl; */
    /* cout << "Ruta mas economica entre nodo " << origen_nodo_inicial / r.capacidad << " con " << origen_nodo_inicial % r.capacidad << " litros" << " y nodo " << destino_nodo_inicial / r.capacidad << " con " << destino_nodo_inicial % r.capacidad << " litros:" << endl; */
    /* for ( i = 0; i < longitud; i++ ) { */
    /*     cout << ruta[i] / r.capacidad << "(" << ruta[i] % r.capacidad << " lts)"; */
    /*     if ( i < longitud - 1 ) cout << " - "; */
    /* } */
    /* cout << " Costo total: " << matriz_distancias[destino_nodo_inicial].coste << endl; */

    return 0;
}
