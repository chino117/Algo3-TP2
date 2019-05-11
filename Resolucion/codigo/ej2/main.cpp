#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matriz;

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

    // Leemos datos de entrada
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    int i = 3;
    vector<int> costoXciudad(n, -1);
    for(;i < n+3; i++)
        costoXciudad[i-3] = atoi(argv[i]);

    Matriz litrosXeje(n, vector<int>(n, 0));
    for(;i < 3+n+(3*m);i+=3){
        int a_i = atoi(argv[i]);
        int b_i = atoi(argv[i+1]);
        int l_i = atoi(argv[i+2]);

        litrosXeje[a_i-1][b_i-1] = l_i;
        litrosXeje[b_i-1][a_i-1] = l_i;
    }
    // Terminamos de leer

    return 0;
}
