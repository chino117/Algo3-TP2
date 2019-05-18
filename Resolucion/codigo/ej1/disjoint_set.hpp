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
        virtual void create(unsigned int n);
        virtual void unite(unsigned int i, unsigned int j);
        virtual unsigned int find(unsigned int i);
        virtual unsigned int size(unsigned int c);
    private:
        // Completar con la representacion
};

class disjoint_set_arbol_optimizado : public disjoint_set{
    public:
        virtual void create(unsigned int n);
        virtual void unite(unsigned int i, unsigned int j);
        virtual unsigned int find(unsigned int i);
        virtual unsigned int size(unsigned int c);
    private:
        // Completar con la representacion
};
#endif
