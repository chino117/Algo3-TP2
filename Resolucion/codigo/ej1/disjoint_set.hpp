#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <vector>

using namespace std;

// Unite(i, j): une ambas componentes bajo el identificador i

class disjoint_set{
    public:
        virtual ~disjoint_set(){};
        virtual void create(unsigned int n) = 0;
        virtual void unite(unsigned int i, unsigned int j) = 0;
        virtual unsigned int find(unsigned int i) = 0;
        virtual unsigned int size(unsigned int c) = 0;
};

class disjoint_set_arreglo : public disjoint_set{
    public:
        virtual void create(unsigned int n){
            componentes.resize(n);
            for(unsigned int i = 0;i < n;i++)
                componentes[i] = i;

            tam_comps.resize(n, 1);
        }
        virtual void unite(unsigned int i, unsigned int j){
            unsigned int comp_j = componentes[j];
            unsigned int comp_i = componentes[i];
            for(unsigned int k = 0;k < componentes.size();k++){
                if(componentes[k] == comp_j){
                    componentes[k] = comp_i;
                    tam_comps[comp_i]++;
                }
            }
        }
        virtual unsigned int find(unsigned int i){
            return componentes[i];
        }
        virtual unsigned int size(unsigned int c){
            return tam_comps[c];
        }
    private:
        vector<unsigned int> componentes;
        vector<unsigned int> tam_comps;
};

class disjoint_set_arbol : public disjoint_set{
    public:
        virtual void create(unsigned int n){
            arboles.resize(n);
            for(unsigned int i = 0;i < n;i++)
                arboles[i] = i;
            tam_arbs.resize(n, 1);
            ranks.resize(n, 0);
        }
        virtual void unite(unsigned int i, unsigned int j){
            unsigned int root_i = find(i);
            unsigned int root_j = find(j);
			
            if(root_i != root_j){
                if(ranks[root_i] < ranks[root_j]){
                    arboles[root_i] = root_j;
                    tam_arbs[root_j] += tam_arbs[root_i];
                }else if(ranks[root_i] > ranks[root_j]){
                    arboles[root_j] = root_i;
                    tam_arbs[root_i] += tam_arbs[root_j];
                }else{
                    arboles[root_j] = root_i;
                    tam_arbs[root_i] += tam_arbs[root_j];
                    ranks[root_i] += 1;
                }
            }
        }
        virtual unsigned int find(unsigned int i){
            while(arboles[i] != i)
                i = arboles[i];
            return i;
        }
        virtual unsigned int size(unsigned int c){
            return tam_arbs[c];
        }
    private:
        //En la i-esima posicion de arboles hay un valor j, significa que el padre de i es j
        //La raiz de un arbol se identifica cuando dado i entre 1 y n, i es padre de si mismo
        //Tanto tam_arbs como ranks, en la posiciones donde hay una raiz, estan la cantidad de nodos del arbol y rank de dicha raiz
        vector<unsigned int> arboles;
        vector<unsigned int> tam_arbs;
        vector<unsigned int> ranks;
};

class disjoint_set_arbol_optimizado : public disjoint_set{
    public:
        virtual void create(unsigned int n){
            arboles.resize(n);
            for(unsigned int i = 0;i < n;i++)
                arboles[i] = i;
            tam_arbs.resize(n, 1);
            ranks.resize(n, 0);
        }
        virtual void unite(unsigned int i, unsigned int j){
            unsigned int root_i = find(i);
            unsigned int root_j = find(j);
			
            if(root_i != root_j){
                if(ranks[root_i] < ranks[root_j]){
                    arboles[root_i] = root_j;
                    tam_arbs[root_j] += tam_arbs[root_i];
                }else if(ranks[root_i] > ranks[root_j]){
                    arboles[root_j] = root_i;
                    tam_arbs[root_i] += tam_arbs[root_j];
                }else{
                    arboles[root_j] = root_i;
                    tam_arbs[root_i] += tam_arbs[root_j];
                    ranks[root_i] += 1;
                }
            }
        }
        virtual unsigned int find(unsigned int i){
            unsigned int nodo = i;
            while(arboles[nodo] != nodo)
				nodo = arboles[nodo];
			unsigned int it = i;
			while(arboles[it] != nodo){
				unsigned int it_sig = arboles[it];
				arboles[it] = nodo;
				it = it_sig;
			}
			return nodo;
        }
        virtual unsigned int size(unsigned int c){
            return tam_arbs[c];
        }
    private:
        //En la i-esima posicion de arboles hay un valor j, significa que el padre de i es j
        //La raiz de un arbol se identifica cuando dado i entre 1 y n, i es padre de si mismo
        //Tanto tam_arbs como ranks, en la posiciones donde hay una raiz, estan la cantidad de nodos del arbol y rank de dicha raiz
        vector<unsigned int> arboles;
        vector<unsigned int> tam_arbs;
        vector<unsigned int> ranks;
};

#endif
