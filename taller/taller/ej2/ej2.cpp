#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <math.h>
#include <functional>

using namespace std;

struct Point
{
    long x, y;
    Point(long x, long y) : x(x), y(y) {}
    double distancia(Point p) { return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y)); }
};

int N; // Cantidad de catapultas.
Point P(0,0), L(0,0); // P es el punto de salida, L el punto de llegada.
vector<Point> C; // Ci es la ubicación de la catapulta i.
vector<double> F; // Fi es la fuerza de la catapulta i.

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

// Esta función debe resolver el problema.
// Devuelve la mínima distancia que debe caminar Humberto para llegar desde P hasta L,
// teniendo en cuenta las catapultas C.
double resolver_problema()
{
    // Me creo un grafo con N+2 puntos, donde el punto 0 es P, el n+1 es L, y 1..n son las catapultas.
    // Asumo que en 0 y n+1 hay catapultas con fuerza 0.
    int V = N+2;
    vector<Point> Pv(V, Point(-1,-1));
    Pv[0] = P;
    Pv[V-1] = L;
    for (int i = 1; i <= N; ++i) Pv[i] = C[i-1];
    vector<double> Fv(V, 0.0);
    for (int i = 1; i <= N; ++i) Fv[i] = F[i-1];

    // Resuelvo camino mínimo para el grafo completo de V vértices con distancias D.
    vector<double> distancias(V+1, 10e9);
    dijkstra(V, 0, [&] (int i, int j) { return fabs(Pv[i].distancia(Pv[j]) - Fv[i]); }, distancias);
    return distancias[V-1];
}

// Lee la instancia si es que hay más instancias en is.
// Devuelve true si pudo leer una instancia con éxito, false en caso contrario.
bool leer_instancia(istream& is)
{
    cin >> N;
    if (N == -1) return false; // Si leo -1, se terminó el input.
    cin >> P.x >> P.y >> L.x >> L.y;
    C = vector<Point>(N, Point(-1, -1));
    F = vector<double>(N, 0.0);
    for (int i = 0; i < N; ++i) cin >> C[i].x >> C[i].y >> F[i];
    return true;
}

int main(int argc, char** argv)
{
    while (leer_instancia(cin)) printf("%.2f\n",resolver_problema());
    return 0;
}
