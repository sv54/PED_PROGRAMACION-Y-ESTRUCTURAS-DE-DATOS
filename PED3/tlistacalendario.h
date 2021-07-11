#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include "tcalendario.h"
#include "tvectorcalendario.h"
using namespace std;

class TListaPos;
class TlistaCalendario;



class TNodoCalendario {
	
	friend class TListaPos;
	friend class TListaCalendario;
	//friend ostream& operator<<(ostream&,const TListaCalendario&);

private:
	TCalendario c; // Uso de LAYERING sobre la clase
	TNodoCalendario* siguiente;

public:
	// Constructor por defecto
	TNodoCalendario();
	// Constructor de copia
	TNodoCalendario(const TNodoCalendario&);
	// Destructor
	~TNodoCalendario();
	// Sobrecarga del operador asignación
	TNodoCalendario& operator=(const TNodoCalendario&);

	
};

class TListaPos {
	friend class TListaCalendario;
	friend class TNodoCalendario;

private:
	// Para implementar la POSICIÓN a NODO de la LISTA de TCalendario
	TNodoCalendario* pos;

public:
	// Constructor por defecto
	TListaPos();
	// Constructor de copia
	TListaPos(const TListaPos&);
	// Destructor
	~TListaPos();
	// Sobrecarga del operador asignación
	TListaPos& operator=(const TListaPos&);
	// Sobrecarga del operador igualdad
	bool operator==(const TListaPos&);
	// Sobrecarga del operador desigualdad
	bool operator!=(const TListaPos&);
	// Devuelve la posición siguiente
	TListaPos Siguiente() const;
	// Posición vacía
	bool EsVacia() const;

};

class TListaCalendario {

	friend class TNodoCalendario;
	friend class TListaPos;
	//Sobrecarga del operador salida
	friend ostream& operator<<(ostream&, const TListaCalendario&);

private:
	// Primer item de la lista
	TNodoCalendario* primero;

public:
	// Constructor por defecto
	TListaCalendario();
	// Constructor de copia
	TListaCalendario(TListaCalendario&);
	//Destructor
	~TListaCalendario();
	// Sobrecarga del operador asignación
	TListaCalendario& operator=(const TListaCalendario&);
	// Sobrecarga del operador igualdad
	bool operator==(const TListaCalendario&) const;
	//Sobrecarga del operador suma
	TListaCalendario operator+ (const TListaCalendario&) const;
	//Sobrecarga del operador resta
	TListaCalendario operator- (const TListaCalendario&)const;
	// Inserta el elemento en la posición que le corresponda dentro de la lista
	bool Insertar(const TCalendario&);
	// Busca y borra el elemento
	bool Borrar(const TCalendario&);
	// Borra el elemento que ocupa la posición indicada
	bool Borrar(const TListaPos&);
	//Borra todos los Calendarios con fecha ANTERIOR a la pasada.
	bool Borrar(int, int, int);
	// Devuelve true si la lista está vacía, false en caso contrario
	bool EsVacia()const;

	// Obtiene el elemento que ocupa la posición indicada
	TCalendario Obtener(const TListaPos&) const;
	// Devuelve true si el Calendario está en la lista.
	bool Buscar(const TCalendario&) const;
	// Devuelve la longitud de la lista
	int Longitud()const;
	// Devuelve la primera posición en la lista
	TListaPos Primera()const;
	// Devuelve la última posición en la lista
	TListaPos Ultima()const;
	// Suma de dos sublistas en una nueva lista
	TListaCalendario SumarSubl(int I_L1, int F_L1, const TListaCalendario& L2, int I_L2,
		int F_L2)const;
	// Extraer un rango de nodos de la lista
	TListaCalendario ExtraerRango(int n1, int n2);

};


