#include <iostream>
#include <iomanip>
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
   int coste;    /* coste o coste total de la trayectoria que conduce al nodo, i.e., 
                el coste total desde el nodo inicial hasta el actual. Un valor de -1 
                denota el infinito */
   int marca;   /* si el nodo ha sido marcado o no */
};


/* Calcula el coste minimo de alcanzar un nodo final 'b'
* grafo no dirigido con N nodos, a partir del nodo inicial 'a',
* dada su matriz de adyacencia A */
vector<label_t> dijkstraAuxEjemplo(int N, const Matriz &A, int a, int b){
	int i, i0, j, coste;

	/* Crea el arreglo de etiquetas de nodo */
	vector<label_t> Labels(N);
	/* nodo inicial 'a' entre 0 y N - 1 */
	if ( a < 0 || a > N - 1 ) return Labels;
	/* nodo final 'b' entre 0 y N - 1 */
	if ( b < 0 || b > N - 1 ) return Labels;

	/* inicializar las etiquetas de nodo */
	for ( i = 0; i < N; i++ ) {
		Labels[i].nro = i;
		if ( i != a ) {
			Labels[i].prev = -1;   /* aun no se ha definido predecesor */
			Labels[i].coste = infty;   /* infinito */
			Labels[i].marca = 0;
		} else {
			Labels[i].prev = -1;   /* aun no se ha definido predecesor */
			Labels[i].coste = 0;    /* coste del nodo inicial a si mismo es cero */
			Labels[i].marca = 0;
		}
	}

	/* continuamos este ciclo mientras existan nodos no marcados */
	while ( 1 ) {
		/* busca entre todos los nodos no marcados el de menor coste, descartando los
		* de coste infinito (-1) */
		coste = infty;
		i0 = -1;
		for ( i = 0; i < N; i++ ) {
			if ( Labels[i].marca == 0 && Labels[i].coste < infty ) {
				// if ( coste >= infty ) {
				// 	coste = Labels[i].coste;
				// 	i0 = i;
				// }
				//  else if ( Labels[i].coste <= coste ) {
				 if ( Labels[i].coste <= coste ) {
					coste = Labels[i].coste;
					i0 = i;
				}
			}
		}
		if ( i0 == -1 ) { /* termina si no encuentra */
			cout << "Ya no quedan nodos por analizar." << endl;
			break;
		}

		cout << "*** Analizando nodo " << i0 << " ***" << endl;

		/* actualiza el coste de todos los sucesores (si los hay) del nodo
		* encontrado y luego senala dicho nodo como marcado */
		for ( i = 0; i < N; i++ ) {
			if ( A[i0][i] > 0 ) {
				/* si el coste acumulado sumado al coste del enlace del nodo i0 al nodo i
				* es menor al coste del nodo i (o si el coste del nodo i es infinito),
				* debemos actualizar */
				if ( Labels[i].coste >= infty || Labels[i0].coste + A[i0][i] < Labels[i].coste ) {
					if ( Labels[i0].coste + A[i0][i] < Labels[i].coste )
						cout << "   [ mejorando coste de nodo " << i << " ]" << endl;
					Labels[i].coste = Labels[i0].coste + A[i0][i];
					Labels[i].prev = i0;
					cout << "   coste de nodo " << i << " desde nodo " << i0 << ": " << Labels[i].coste << endl;
				}
			}
		}
		Labels[i0].marca = 1;
		cout << "   [ nodo " << i0 << " marcado ]" << endl;

		/* para verificar, imprime los costes calculados hasta el momento */
		for ( i = 0; i < N; i++ ) {
			cout << i << ": [";
			if ( Labels[i].coste >= infty ) cout << "Inf";
			else cout << Labels[i].coste;
			cout << ", " << Labels[i].prev ;
			if ( Labels[i].marca == 1 ) cout <<  ", x]" << endl;
			else cout << "]" << endl;
		}
		cout << endl;
	}





	return Labels;
}

// falta aplicar logica del problema al algoritmo
MatrizRes dijkstra(int n, const Matriz &A){
	int i, i0, j, coste;
	MatrizRes res;
	/* Crea el arreglo de etiquetas de nodo */
	vector<label_t> Labels(n);
	int a = 0;

	/* inicializar las etiquetas de nodo */
	for ( i = 0; i < n; i++ ) {
		Labels[i].nro = i;
		if ( i != a ) {
			Labels[i].prev = -1;   /* aun no se ha definido predecesor */
			Labels[i].coste = infty;   /* infinito */
			Labels[i].marca = 0;
		} else {
			Labels[i].prev = -1;   /* aun no se ha definido predecesor */
			Labels[i].coste = 0;    /* coste del nodo inicial a si mismo es cero */
			Labels[i].marca = 0;
		}
	}

	/* continuamos este ciclo mientras existan nodos no marcados */
	while ( 1 ) {
		/* busca entre todos los nodos no marcados el de menor coste, descartando los
		* de coste infinito (-1) */
		coste = infty;
		i0 = -1;
		for ( i = 0; i < n; i++ ) {
			if ( Labels[i].marca == 0 && Labels[i].coste != infty ) {
				if ( coste == infty ) {
					coste = Labels[i].coste;
					i0 = i;
				} else if ( Labels[i].coste <= coste ) {
					coste = Labels[i].coste;
					i0 = i;
				}
			}
		}
		if ( i0 == -1 ) { /* termina si no encuentra */
			break;
		}
		/* actualiza el coste de todos los sucesores (si los hay) del nodo
		* encontrado y luego senala dicho nodo como marcado */
		for ( i = 0; i < n; i++ ) {
			if ( A[i0][i] > 0 ) {
				/* si el coste acumulado sumado al coste del enlace del nodo i0 al nodo i
				* es menor al coste del nodo i (o si el coste del nodo i es infinito),
				* debemos actualizar */
				if ( Labels[i].coste == infty || Labels[i0].coste + A[i0][i] < Labels[i].coste ) {
					Labels[i].coste = Labels[i0].coste + A[i0][i];
					Labels[i].prev = i0;
				}
			}
		}
		Labels[i0].marca = 1;
	}
	// ARMAR TODAS LAS RUTAS, no tegno en cuenta nodos con costes negativos
	int si;
	tuple<int,int,int> tripla;
	resizeMatrizRes(res, n, n-1);
	for (i = 0; i < n; ++i) {
		j = (i + 1) % n;
		while (j != i) {
			/* Ruta desde el nodo 'i' hasta el nodo 'j' */			
			si = abs(Labels[i].coste - Labels[j].coste);

			get<0>(tripla) = i;
			get<1>(tripla) = j;
			get<2>(tripla) = si;
			res[i][j] = tripla;

			get<0>(tripla) = j;
			get<1>(tripla) = i;
			get<2>(tripla) = si;
			res[j][i] = tripla;

			j++;
		}
	}
}

// vector<vector<int>> dijkstra(int n, int m, const vector<int> &costoXciudad, const Matriz &litrosXeje) {
	
// 	return res;
// }


