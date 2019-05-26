#include <iostream>
#include <stdlib.h>
#include <vector>
#include "tipos_aux.h"
#include "dijkstra.hpp"

using namespace std;

// Ejecutar dijkstra sobre el grafo completo de n vértices con pesos en las aristas peso(i,j).
// Empezar desde el vértice s.
// Devolver en distancias la distancia de s al resto de los vértices.
// void dijkstra(int n, int s, const function<double(int i, int j)>& peso, vector<double>& distancias)
// {
//     priority_queue<tuple<double, int, int>> S;
// 	for(int i = 0;i < n; i++)
// 		if(i != s)
// 			S.push({-peso(s, i), s, i});

//     while(!S.empty()){
// 		auto t = S.top();
// 		S.pop();
// 		double c = get<0>(t);
// 		int u = get<2>(t);
// 		int v = get<1>(t);
		
// 		if(distancias[u] == 10e9)
// 		{
// 			distancias[u] = -c;
// 			for(int j = 0;j < n; j++)
// 				if(distancias[j] == 10e9)
// 					S.push({c-peso(u, j), u, j});		
// 		}
// 	}
// }

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

MatrizRes camMinimo(const DatosProblema &datos, const int metodo){
	MatrizRes res;
	switch(metodo){
		case 0:
			// res = dijkstra(datos.n, datos.m, datos.costoXciudad, datos.litrosXeje);
			break;
		case 1:
			// return dijkstraCol();
			break;
		case 2:
			// return bellmanFord();
			break;
		case 3:
			// return floydWarshall();
			break;
		default:
			cout<<"ERROR: Parametro de metodo incorrecto"<<endl;
			exit(-1);
			break;
	}
}


int main(int argc, char** argv){
    if(argc < 4)
        cout<<"ERROR: Faltan argumentos"<<endl;

    DatosProblema r = leer_datos(cin);
	int metodo;
	if(argc > 4){ // Si pasan los parametros adicionales
		metodo = atoi(argv[argc-4]);
	}else{
		metodo = 0;
	}
	MatrizRes res = camMinimo(r, metodo);
	// vector<vector<int>> gv;
	// for(int i = 0; i < r.n; i++){
	// 	auto g = gv[i];
	// 	for(int e = 0; e < r.m; e++){
	// 		auto litros = r.litrosXeje[e][i];
	// 		if(r.costoXciudad[e] < r.costoXciudad[i] && litros <= r.capacidad){
	// 			g[e] = (r.capacidad - r.litrosXeje[e][i]);
	// 		}
	// 	}
	// }
    return 0;
}
