#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include "tipos_aux.h"

using namespace std;

/* Definiendo la estructura etiqueta de nodo. Sus campos incluyen
 * el número de nodo, el coste total del nodo, y su precedente. */
struct label_t{
   int nro;     /* numero del nodo */
   int prev;    /* nodo precedente (-1 para el nodo inicial )*/
   int peso;    /* peso o coste total de la trayectoria que conduce al nodo, i.e., 
                el coste total desde el nodo inicial hasta el actual. Un valor de -1 
                denota el infinito */
   int marca;   /* si el nodo ha sido marcado o no */
};


/* Calcula el coste minimo de alcanzar un nodo final 'b'
* grafo no dirigido con N nodos, a partir del nodo inicial 'a',
* dada su matriz de adyacencia A */
void dijkstraAux(int N, const Matriz &A, int a, int b){
	int i, i0, j, peso;

	/* Crea el arreglo de etiquetas de nodo */
	vector<label_t> Labels(N, -1);
	/* nodo inicial 'a' entre 0 y N - 1 */
	if ( a < 0 || a > N - 1 ) return;
	/* nodo final 'a' entre 0 y N - 1 */
	if ( b < 0 || b > N - 1 ) return;

	/* inicializar las etiquetas de nodo */
	for ( i = 0; i < N; i++ ) {
		Labels[i].nro = i;
		if ( i != a ) {
			Labels[i].prev = -1;   /* aun no se ha definido predecesor */
			Labels[i].peso = -1;   /* infinito */
			Labels[i].marca = 0;
	} else {
			Labels[i].prev = -1;   /* aun no se ha definido predecesor */
			Labels[i].peso = 0;    /* coste del nodo inicial a si mismo es cero */
			Labels[i].marca = 0;
		}
	}

	/* continuamos este ciclo mientras existan nodos no marcados */
	while ( 1 ) {
		/* busca entre todos los nodos no marcados el de menor peso, descartando los
		* de peso infinito (-1) */
		peso = -1;
		i0 = -1;
		for ( i = 0; i < N; i++ ) {
			if ( Labels[i].marca == 0 && Labels[i].peso >= 0 )
			if ( peso == -1 ) {
				peso = Labels[i].peso;
				i0 = i;
			} else if ( Labels[i].peso <= peso ) {
				peso = Labels[i].peso;
				i0 = i;
			}
		}
		if ( i0 == -1 ) { /* termina si no encuentra */
			cout << "Ya no quedan nodos por analizar." << endl;
			break;
		}

		cout << "*** Analizando nodo " << i0 << " ***" << endl;

		/* actualiza el peso de todos los sucesores (si los hay) del nodo
		* encontrado y luego senala dicho nodo como marcado */
		for ( i = 0; i < N; i++ ) {
			if ( A[i0][i] > 0 ) {
				/* si el coste acumulado sumado al coste del enlace del nodo i0 al nodo i
				* es menor al coste del nodo i (o si el coste del nodo i es infinito),
				* debemos actualizar */
				if ( Labels[i].peso == -1 || Labels[i0].peso + A[i0][i] < Labels[i].peso ) {
					if ( Labels[i0].peso + A[i0][i] < Labels[i].peso )
						cout << "   [ mejorando coste de nodo " << i << " ]" << endl;
					Labels[i].peso = Labels[i0].peso + A[i0][i];
					Labels[i].prev = i0;
					cout << "   coste de nodo " << i << " desde nodo " << i0 << ": " << Labels[i].peso << endl;
				}
			}
		}
		Labels[i0].marca = 1;
		cout << "   [ nodo " << i0 << " marcado ]" << endl;

		/* para verificar, imprime los costes calculados hasta el momento */
		for ( i = 0; i < N; i++ ) {
			cout << i << ": [";
			if ( Labels[i].peso == -1 ) cout << "Inf";
			else cout << Labels[i].peso;
			cout << ", " << Labels[i].prev ;
			if ( Labels[i].marca == 1 ) cout <<  ", x]" << endl;
			else cout << "]" << endl;
		}
		cout << endl;
	}

	/* Ruta desde el nodo 'a' hasta el nodo 'b' */
	int longitud = 2;
	i = b;
	while ( ( i = Labels[i].prev ) != a ) longitud++;    /* primero estimamos la longitud de la ruta */

	vector<int> ruta(longitud, 0);      /* array de nodos de la ruta minima */
	ruta[longitud - 1] = b;      		/* luego rellenamos */
	i = b;
	j = 0;
	for ( j = 1; j < longitud; j++ ) {
		i = Labels[i].prev;
		ruta[longitud - j - 1] = i;
	}

	cout << "================================================================" << endl;
	cout << "Ruta mas economica entre nodo " << a << " y nodo " << b << ":" << endl;
	for ( i = 0; i < longitud; i++ ) {
		cout << ruta[i];
		if ( i < longitud - 1 ) cout << " - ";
	}
	cout << "Costo total: " << Labels[b].peso << endl;
}

Matriz dijkstra(int n, int m, const vector<int> &costoXciudad, const Matriz &litrosXeje) {
	Matriz res;
	resizeMatriz(res, n, n-1);
	// res = dijkstraAux(n, costoXciudad, litrosXeje);
}


