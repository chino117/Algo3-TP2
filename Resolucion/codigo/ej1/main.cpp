#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <tuple>
#include <algorithm>
#include <memory>
#include <limits>
#include <chrono>
#include <fstream>
#include "disjoint_set.hpp"
#include <iterator>
#include <sstream>

using namespace std;

using matriz = vector<vector<int>>;
using eje = tuple<unsigned int, unsigned int, unsigned int>;
using milisegundos = chrono::duration<double, milli>;

unsigned int w(const eje& e){return get<0>(e);}
unsigned int v(const eje& e){return get<1>(e);}
unsigned int u(const eje& e){return get<2>(e);}

string nombres_metodos[3] = {
                             "DisjointSet con Arreglo",
                             "DisjointSet con arbol",
                             "DisjointSet con arbol y Path Compression"
                            };

void escribir_tiempo(const string& filename, milisegundos medicion, int k, int metodo){
    string path = "ej1_tiempos_sin_outliers.csv";
    fstream f;
    f.open(path, fstream::out | fstream::app);

    if(f.fail()){
        cerr<<"ERROR: No se pudo abrir el archivo de mediciones";
        return;
    }
    f<<filename<<","<<nombres_metodos[metodo]<<","<<k<<","<<medicion.count()<<endl;
    f.close();
}

void mostrar_matriz(const matriz& m){
    for(auto& i : m){
        for(auto& j : i)
            cout<<setw(3)<<j<<" ";
        cout<<endl;
    }
}


// Como es un grafo, no un digrafo, podemos asumir en cada paso que ciertas aristas ya fueron agregadas
vector<eje> crear_aristas_vecinos(int i, int j, const matriz& m){
    vector<eje> res;

    int ancho = m[0].size();
    if(i+1 < int(m.size())){
        if(j-1 >= 0)
            res.push_back({abs(m[i][j] - m[i+1][j-1]), i*ancho + j, (i+1)*ancho + (j-1)});
        if(j+1 < ancho)
            res.push_back({abs(m[i][j] - m[i+1][j+1]), i*ancho + j, (i+1)*ancho + (j+1)});

        res.push_back({abs(m[i][j] - m[i+1][j]), i*ancho + j, (i+1)*ancho + j});
    }

    if(j+1 < ancho)
        res.push_back({abs(m[i][j] - m[i][j+1]), i*ancho + j, i*ancho + (j+1)});

    return res;
}

unsigned int internal_diff(unsigned int i, unsigned int j, const vector<unsigned int>& w_c, unsigned int t_i, unsigned int t_j){
    return min(w_c[i] + t_i, w_c[j] + t_j);
}

// Esto vendria a ser el ciclo del algoritmo
// Por cada componente necesitamos (ademas de lo provisto por disjoint_set) la
// cantidad de elementos dentro de la componente(agregado a disjoint_set) y la
// arista de peso maximo contenida en la componente (eso se mantiene aca)
void segmentar_aux(vector<eje>& E, shared_ptr<disjoint_set> U, int n, int k){
    vector<unsigned int> w_max_x_comp(n, 0);

    for(unsigned int i = 0;i < E.size();i++){
        auto o_q = E[i];
        auto componente_v = U->find(v(o_q));
        auto componente_u = U->find(u(o_q));

        // No me queda claro si la division deberia ser entre enteros o 
        // hay que castear a float, hacer la division y castearla a entero
        auto t_v = static_cast<unsigned int>((float)k/(float)U->size(componente_v));
        auto t_u = static_cast<unsigned int>((float)k/float(U->size(componente_u)));

        if(componente_v != componente_u && w(o_q) <= internal_diff(componente_v, componente_u, w_max_x_comp, t_v, t_u)){
            U->unite(componente_v, componente_u);

            // Actualizo el peso mas grande de la componente de v
            if(w(o_q) > w_max_x_comp[componente_v])
                w_max_x_comp[componente_v] = w(o_q);
        }
    }
}

milisegundos segmentar(const matriz& m, int k, int metodo){
    int alto = m.size();
    int ancho = m[0].size();
    unsigned int n = m.size() * m[0].size();

    // Armamos lista de aristas
    vector<eje> E;
    for(int i = 0;i < alto; i++){
        for(int j = 0;j < ancho;j++){
            vector<eje> vecinos(crear_aristas_vecinos(i, j, m));
            for(auto & k : vecinos)
                E.push_back(k);
        }
    }

    // Ordenamos lista de aristas por peso
    sort(E.begin(), E.end());
    
    // Creamos el disjoint_set aca para que el algoritmo sea igual sin importar la implementacion
    shared_ptr<disjoint_set> U;
    switch(metodo){
        case 0:
            U.reset(new disjoint_set_arreglo());
            break;
        case 1:
            U.reset(new disjoint_set_arbol());
            break;
        case 2:
            U.reset(new disjoint_set_arbol_optimizado());
            break;
        default:
            cout<<"ERROR: Parametro de metodo incorrecto"<<endl;
            exit(-1);
            break;
    }

    auto start_time = chrono::steady_clock::now();
    U->create(n);
    segmentar_aux(E, U, n, k);

    matriz res(alto, vector<int>(ancho, 0));
    for(int i = 0;i < alto; i++)
        for(int j = 0;j < ancho;j++)
            res[i][j] = U->find(i*ancho + j); 

    auto end_time = chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    mostrar_matriz(res);

    return milisegundos(diff_time);
}

int main(int argc, char** argv){

    int metodo, k;
    string filename("");
    if(argc > 2){ // Si pasan los parametros adicionales
        metodo = atoi(argv[1]);
        k = atoi(argv[2]);
        if(argc > 3)
            filename = string(argv[3]);
    }
    else{
        metodo = 0;
        k = 10;
    }

    int alto, ancho;
    cin >> alto >> ancho;
    
    matriz m(alto, vector<int>(ancho, 0));

    string row = "";
    getline(cin,row); //NO BORRAR: agarra el newline extra que queda por el cin >> alto >> ancho
    for(int i = 0; i < alto;i++){
        getline( std::cin, row );
        istringstream is( row );
        vector<int> v( ( istream_iterator<int>( is ) ), istream_iterator<int>() );
        int j = 0;
        for ( int x : v) {
            m[i][j] = x;
            j++;
        }
    }


    escribir_tiempo(filename, segmentar(m, k, metodo), k, metodo);
        
    return 0;
}
