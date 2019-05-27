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

tuple<int,int,Matriz> armar_nuevo_grafo (DatosProblema data){
   Matriz res;
   resizeMatriz(res, data.n * data.capacidad, data.n * data.capacidad);
   for (int i = 0; i < data.n; i++){
      int costoSrc = data.costoXciudad[i];

      for(int litrosSrc = 0; litrosSrc < data.capacidad; litrosSrc++){         
         int indexSrc = i * data.capacidad + litrosSrc;

         for(int j = 0; j < data.n; j++){
            int distancia = data.litrosXeje[i][j];

            for(int litrosDst = 0; litrosDst < data.capacidad; litrosDst++ ){
               int indexDst = j * data.capacidad + litrosDst;
               int costo = infty;
               if(distancia > 0){
                  if(litrosSrc - distancia <= litrosDst){
                     costo = (litrosDst + distancia - litrosSrc) * costoSrc;
                  }
               }
               res[indexSrc][indexDst] = costo;
            }
         }
         
      }
   }
   int nodos_nuevos = data.n*data.capacidad;
   int ultimo_nodo = (data.n-1)*data.capacidad;
   return tuple<int,int,Matriz>(nodos_nuevos,ultimo_nodo,res);
}
int main(int argc, char** argv){
   // prueba();
   DatosProblema r;
   if(argc < 4)
      if(argc != 2)
         cout<<"ERROR: Faltan argumentos"<<endl;
      else{
         ifstream input (argv[1]);
         r = leer_datos(input);
      }
   else
      r = leer_datos(cin);
   
	int metodo;
	if(argc > 4){ // Si pasan los parametros adicionales
		metodo = atoi(argv[argc-4]);
	}else{
		metodo = 0;
	}
   

   auto nuevo_grafo = armar_nuevo_grafo(r);
   
   auto nueva_matriz = get<2>(nuevo_grafo);
   auto nuevo_n = get<0>(nuevo_grafo);
   auto destino_nodo_inicial = get<1>(nuevo_grafo) ;
   auto origen_nodo_inicial = 0;
   auto matriz_distancias =  dijkstraAuxEjemplo(nuevo_n, nueva_matriz, origen_nodo_inicial, destino_nodo_inicial); 

	/* Ruta desde el nodo 'a' hasta el nodo 'b' */
	int longitud = 2;
	int nodo_final = -1;
	int min= infty;
	for(int res = destino_nodo_inicial; res < nuevo_n; res++){
		if(matriz_distancias[res].coste < min){
			min = matriz_distancias[res].coste;
			nodo_final = res;
		}
	}
	while ( ( nodo_final = matriz_distancias[nodo_final].prev ) != origen_nodo_inicial ){
		longitud++;    /* primero estimamos la longitud de la ruta */
	} 	
	vector<int> ruta(longitud, 0);      /* array de nodos de la ruta minima */
	ruta[longitud - 1] = destino_nodo_inicial;      		/* luego rellenamos */
	int i = destino_nodo_inicial;
	for (int j = 1; j < longitud; j++ ) {
		i = matriz_distancias[i].prev;
		ruta[longitud - j - 1] = i;
	}

   
	cout << "================================================================" << endl;
	cout << "Ruta mas economica entre nodo " << origen_nodo_inicial / r.capacidad << " con " << origen_nodo_inicial % r.capacidad << " litros" << " y nodo " << destino_nodo_inicial / r.capacidad << " con " << destino_nodo_inicial % r.capacidad << " litros:" << endl;
	for ( i = 0; i < longitud; i++ ) {
		cout << ruta[i] / r.capacidad << "(" << ruta[i] % r.capacidad << " lts)";
		if ( i < longitud - 1 ) cout << " - ";
	}
	cout << " Costo total: " << matriz_distancias[destino_nodo_inicial].coste << endl;
   return 0;
}
