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
	// Sobrecarga del operador asignaci�n
	TNodoCalendario& operator=(const TNodoCalendario&);

	
};

class TListaPos {
	friend class TListaCalendario;
	friend class TNodoCalendario;

private:
	// Para implementar la POSICI�N a NODO de la LISTA de TCalendario
	TNodoCalendario* pos;

public:
	// Constructor por defecto
	TListaPos();
	// Constructor de copia
	TListaPos(const TListaPos&);
	// Destructor
	~TListaPos();
	// Sobrecarga del operador asignaci�n
	TListaPos& operator=(const TListaPos&);
	// Sobrecarga del operador igualdad
	bool operator==(const TListaPos&);
	// Sobrecarga del operador desigualdad
	bool operator!=(const TListaPos&);
	// Devuelve la posici�n siguiente
	TListaPos Siguiente() const;
	// Posici�n vac�a
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
	// Sobrecarga del operador asignaci�n
	TListaCalendario& operator=(const TListaCalendario&);
	// Sobrecarga del operador igualdad
	bool operator==(const TListaCalendario&) const;
	//Sobrecarga del operador suma
	TListaCalendario operator+ (const TListaCalendario&) const;
	//Sobrecarga del operador resta
	TListaCalendario operator- (const TListaCalendario&)const;
	// Inserta el elemento en la posici�n que le corresponda dentro de la lista
	bool Insertar(const TCalendario&);
	// Busca y borra el elemento
	bool Borrar(const TCalendario&);
	// Borra el elemento que ocupa la posici�n indicada
	bool Borrar(const TListaPos&);
	//Borra todos los Calendarios con fecha ANTERIOR a la pasada.
	bool Borrar(int, int, int);
	// Devuelve true si la lista est� vac�a, false en caso contrario
	bool EsVacia()const;

	// Obtiene el elemento que ocupa la posici�n indicada
	TCalendario Obtener(const TListaPos&) const;
	// Devuelve true si el Calendario est� en la lista.
	bool Buscar(const TCalendario&) const;
	// Devuelve la longitud de la lista
	int Longitud()const;
	// Devuelve la primera posici�n en la lista
	TListaPos Primera()const;
	// Devuelve la �ltima posici�n en la lista
	TListaPos Ultima()const;
	// Suma de dos sublistas en una nueva lista
	TListaCalendario SumarSubl(int I_L1, int F_L1, const TListaCalendario& L2, int I_L2,
		int F_L2)const;
	// Extraer un rango de nodos de la lista
	TListaCalendario ExtraerRango(int n1, int n2);

};


