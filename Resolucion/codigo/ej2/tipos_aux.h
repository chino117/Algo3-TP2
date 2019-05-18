#ifndef TIPOS_AUX_H
#define TIPOS_AUX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include <chrono>

using namespace std;

typedef vector<vector<int>> Matriz;

void resizeMatriz( Matriz &m , const int fils , const int cols )
{
	m.resize(fils);
	for(auto &it : m){
		it.resize(cols);
	}
}
// Estructura que contiene los datos de entrada del problema

struct DatosProblema
{
	int n; //Cantidad de ciudades
	int m; //Cantidad de rutas
	vector<int> costoXciudad;
	Matriz litrosXeje;
};

// Operaciones de DatosProblema

istream& operator>>(istream& is, DatosProblema& d)
{
	is>>d.n;
	is>>d.m;

	if (d.n < 0 || d.m < 0)
	{
		cout<<"ERROR: Valores asignados a DatosProblema invalidos"<<endl;
		return is;
	}

	d.costoXciudad.resize(d.n);
	resizeMatriz(d.litrosXeje, d.n, d.n);

	for(unsigned int i = 0;i < d.n; i++)
		is>>d.costoXciudad[i];

	int a_i;
	int b_i;
	int l_i;
	for(unsigned int i = 0;i < d.m;i++){
		is>>a_i;
		is>>b_i;
		is>>l_i;
		d.litrosXeje[a_i-1][b_i-1] = l_i;
		d.litrosXeje[b_i-1][a_i-1] = l_i;
	}

	return is;
}

ostream& operator<<(ostream& os, const DatosProblema& d)
{
	os<<d.n<<" "<<d.m<<endl;
	os<<"\n"<<endl;
	for(unsigned int i = 0;i < d.n;i++)
		os<<d.costoXciudad[i]<<"\n"<<endl;

	for(unsigned int i = 0;i < d.n;i++){
		for(unsigned int j = 0;j < d.n;j++){
			os<<d.litrosXeje[i][j]<<" "<<endl;
		}
		os<<"\n"<<endl;
	}
	return os;
}

DatosProblema leer_datos(istream& is)
{
	DatosProblema res;
	is>>res;
	return res;
}







#endif
