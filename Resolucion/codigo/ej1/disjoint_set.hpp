#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

class disjoint_set{
    public:
        virtual ~disjoint_set(){};
        virtual void create(unsigned int n) = 0;
        virtual void unite(unsigned int i, unsigned int j) = 0;
        virtual unsigned int find(unsigned int i) = 0;
};

class disjoint_set_arreglo : public disjoint_set{
    public:
        virtual void create(unsigned int n);
        virtual void unite(unsigned int i, unsigned int j);
        virtual unsigned int find(unsigned int i);
    private:
        // Completar con la representacion
};

class disjoint_set_arbol : public disjoint_set{
    public:
        virtual void create(unsigned int n);
        virtual void unite(unsigned int i, unsigned int j);
        virtual unsigned int find(unsigned int i);
    private:
        // Completar con la representacion
};

class disjoint_set_arbol_optimizado : public disjoint_set{
    public:
        virtual void create(unsigned int n);
        virtual void unite(unsigned int i, unsigned int j);
        virtual unsigned int find(unsigned int i);
    private:
        // Completar con la representacion
};
#endif
