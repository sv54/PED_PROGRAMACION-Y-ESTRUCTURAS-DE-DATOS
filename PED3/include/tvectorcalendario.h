#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include "tcalendario.h"



using namespace std;

class TVectorCalendario {

private:
	TCalendario* c;
	int tamano;
	TCalendario error;
	bool ComprobacionFecha(int, int, int);
	bool AnyoBisiesto(int);

public:
	// Constructor por defecto
	TVectorCalendario();
	// Constructor a partir de un tama�o
	TVectorCalendario(int);
	// Constructor de copia
	TVectorCalendario(TVectorCalendario&);
	// Destructor
	~TVectorCalendario();
	// Sobrecarga del operador asignaci�n
	TVectorCalendario& operator=(const TVectorCalendario&);
	// Sobrecarga del operador igualdad
	bool operator==(const TVectorCalendario&)const;
	// Sobrecarga del operador desigualdad
	bool operator!=(const TVectorCalendario&)const;
	// Sobrecarga del operador corchete (parte IZQUIERDA)
	TCalendario& operator[](int);
	// Sobrecarga del operador corchete (parte DERECHA)
	TCalendario operator[](int) const;
	// Tama�o del vector (posiciones TOTALES)
	int Tamano();
	// Cantidad de posiciones OCUPADAS (no vac�as) en el vector
	int Ocupadas();
	// Devuelve TRUE si existe el calendario en el vector
	bool ExisteCal(TCalendario&);

	void MostrarMensajes(int, int, int);

	bool Redimensionar(int);

	// Sobrecarga del operador salida
	friend ostream& operator<<(ostream&,const TVectorCalendario&);

};