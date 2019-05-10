#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <math.h>
#include <tuple>

using namespace std;

int n; // cantidad de puntos en el mapa.
vector<vector<int>> G; // lista de adyacencia: G[i] = { j \in V(G) : (i,j) \in E(G) }.
vector<vector<double>> w; // mariz de pesos de las aristas.

// Calcular el AGM de (G, w).
// agm: variable de salida, se devuelve el AGM como un diccionario de parents.
//  - importante: agm[root] = -1.
void kruskal(vector<int>& agm)
{
    throw "Implementar";
    // Implementar.
}

// Calcular el AGM de (G, peso).
// agm: variable de salida, se devuelve el AGM como un diccionario de parents.
//  - importante: agm[root] = -1.
void prim(vector<int>& agm)
{
	agm.resize(n, -2);
    agm[0] = -1;
	priority_queue<tuple<double, int, int>> S;
	for(auto i : G[0])
		S.push({-1 * w[0][i], 0, i});

    while(!S.empty()){
		auto t = S.top();
		S.pop();
		int u = get<2>(t);
		int v = get<1>(t);
		if(agm[u] == -2)
		{
			agm[u] = v;
			for(auto j : G[u]){
				if(agm[j] == -2)
					S.push({-1 * w[u][j], u, j});
			}		
		}
	}
}

// Devuelve el promedio de pesos del conjunto de aristas a distancia 2 de (k, agm[k]).
// agm: arbol a considerar.
// k: arista a la cual se le quiere calcular el promedio de la vecindad.
double promedio_aristas_vecinas(const vector<int>& agm, int k)
{
    // representamos las aristas (v_1, v_2) como el indice i tal que (i, agm[i]) == (v_1, v_2).
    // la arista k tiene como aristas vecinas a todas las aristas distintas i tales que
    // comparten un extremo o existe j que comparte un extremo con k y otro con i.
    int cantidad = 0;
    double pesos = 0.0;
    
    auto comparte_extremo = [&](int i, int j) -> bool { return i == j || agm[i] == j || agm[i] == agm[j] || i == agm[j]; };
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == k || i == j || j == k) continue;
            if (comparte_extremo(i, k) || (comparte_extremo(i, j) && comparte_extremo(j, k)))
            {
                cantidad++;
                pesos += w[i][agm[i]];
                break;
            }
        }
    }
    return pesos / (double)cantidad;
}

// Leo la instancia del stream is.
void leer_instancia(istream& is)
{
    is >> n;
    G = vector<vector<int>>(n);
    w = vector<vector<double>>(n, vector<double>(n, 0));
    // Leo los puntos.
    vector<pair<double, double>> puntos(n);
    for (int i = 0; i < n; ++i)
        is >> puntos[i].first >> puntos[i].second;
    // Inicializo el grafo y los pesos.
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j) continue;
            // Agrego la arista al grafo.
            G[i].push_back(j);
            // Calculo peso de i a j.
            w[i][j] = sqrt(pow(puntos[i].first-puntos[j].first,2)+pow(puntos[i].second-puntos[j].second,2));
        }
    }
}

int main(int argc, char** argv)
{
    leer_instancia(cin);
    clog << "Tamaño de la instancia: " << n << " puntos." << endl;

    // Parametro de experimentación F, que indica cuán estricto hay que ser para sacar aristas.
    double K = argc < 2 ? 2.0 : atof(argv[1]);
    clog << "Parámetro K = " << K << endl;

    // Calculo el AGM (comentar segun la implementación que se quiera).
    vector<int> agm;
    prim(agm);
    // kruskal(agm);

    // componentes va a tener el agm menos las aristas inconsistentes.
    vector<int> componentes(n, -1);
    for (int k = 0; k < n; ++k)
    {
        if (agm[k] == -1) continue;
        if (w[k][agm[k]] / promedio_aristas_vecinas(agm, k) < K) componentes[k] = agm[k];
    }

    // Asigno un numero a cada componente conexa.
    vector<int> clusters(n, 0);
    for (int k = 0; k < n; ++k) clusters[k] = k;
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            if (componentes[i] == -1) continue;
            clusters[i] = min(clusters[i], clusters[componentes[i]]);
            clusters[componentes[i]] = min(clusters[i], clusters[componentes[i]]);
        }
    }

    // Asigno clusters consecutivos.
    vector<int> cluster_ids(n, -1);
    int num_clusters = 0;
    for (int k = 0; k < n; ++k)
    {
        if (cluster_ids[clusters[k]] == -1) cluster_ids[clusters[k]] = num_clusters++;
        cout << cluster_ids[clusters[k]] << endl;
    }
    
    clog << "#Clusters: " << num_clusters << endl;

    return 0;
}
