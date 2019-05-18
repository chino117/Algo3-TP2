#include <iostream>
#include <stdlib.h>
#include <vector>
#include "tipos_aux.h"

using namespace std;

// Emi: Este es el dijkstra que hicimos en el taller, lo pongo aca de ejemplo
/*void dijkstra(int n, int s, const function<double(int i, int j)>& peso, vector<double>& distancias)
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
*/

int main(int argc, char** argv){
    if(argc < 4)
        cout<<"ERROR: Faltan argumentos"<<endl;

    DatosProblema r = leer_datos(cin);

    return 0;
}
