#include <iostream>
#include <stdlib.h>
#include <vector>
#include "tipos_aux.h"

using namespace std;

// Ejecutar dijkstra sobre el grafo completo de n vértices con pesos en las aristas peso(i,j).
// Empezar desde el vértice s.
// Devolver en distancias la distancia de s al resto de los vértices.
void dijkstra(int n, int s, const function<double(int i, int j)>& peso, vector<double>& distancias)
{
    priority_queue<tuple<double, int, int>> S;
	for(int i = 0;i < n; i++)
		if(i != s)
			S.push({-peso(s, i), s, i});

    while(!S.empty()){
		auto t = S.top();
		S.pop();
		double c = get<0>(t);
		int u = get<2>(t);
		int v = get<1>(t);
		
		if(distancias[u] == 10e9)
		{
			distancias[u] = -c;
			for(int j = 0;j < n; j++)
				if(distancias[j] == 10e9)
					S.push({c-peso(u, j), u, j});		
		}
	}
}

vector<int> camMinimo(const DatosProblema &datos, const int metodo){
	// vector<int> res;
	switch(metodo){
		case 0:
			ResultadoProblema res;
			res.metodo = 0;
			res.g = dijkstra(datos.n, datos.m, datos.costoXciudad, datos.litrosXeje);
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

    return 0;
}
