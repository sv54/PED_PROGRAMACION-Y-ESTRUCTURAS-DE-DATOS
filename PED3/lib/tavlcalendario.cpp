#include <iostream>
#include <string.h>
#include <string>
#include "../include/tcalendario.h"
#include "../include/tavlcalendario.h"
#include <queue>

using namespace std;


//Constructor por defecto
TNodoAVL::TNodoAVL() {
	fe = 0;
}
//Constructor copia
TNodoAVL::TNodoAVL(const TNodoAVL& tnodo) {
	item = tnodo.item;
	fe = tnodo.fe;
	iz = tnodo.iz;
	de = tnodo.de;
}
//Destructor
TNodoAVL::~TNodoAVL() {
	fe = 0;
}
// Sobrecarga del operador asignación
TNodoAVL& TNodoAVL::operator=(const TNodoAVL& tnodo) {
	if (this != &tnodo) {
		item = tnodo.item;
		fe = tnodo.fe;
		iz = tnodo.iz;
		de = tnodo.de;
	}
	return *this;
}

void TAVLCalendario::InordenAux(TVectorCalendario& vecc, int& pos)const {
	if (raiz != NULL) {
		raiz->iz.InordenAux(vecc, pos);
		vecc[pos] = raiz->item;
		pos++;
		raiz->de.InordenAux(vecc, pos);
	}
}
// AUXILIAR: devuelve el recorrido en PREORDEN
void TAVLCalendario::PreordenAux(TVectorCalendario& vecc, int& pos)const {
	if (raiz != NULL) {
		vecc[pos] = raiz->item;
		pos++;
		raiz->iz.PreordenAux(vecc, pos);
		raiz->de.PreordenAux(vecc, pos);
	}
}
// AUXILIAR: devuelve el recorrido en POSTORDEN
void TAVLCalendario::PostordenAux(TVectorCalendario& vecc, int& pos)const {
	if (raiz != NULL) {
		raiz->iz.PostordenAux(vecc, pos);
		raiz->de.PostordenAux(vecc, pos);
		vecc[pos] = raiz->item;
		pos++;
	}
}

// Constructor por defecto
TAVLCalendario::TAVLCalendario() {
	raiz = NULL;
}
// Constructor de copia
TAVLCalendario::TAVLCalendario(const TAVLCalendario& tavl) {
	if (tavl.raiz != NULL) {
		raiz = new TNodoAVL();
		raiz->fe = tavl.raiz->fe;
		raiz->item = tavl.raiz->item;
		raiz->de = tavl.raiz->de;
		raiz->iz = tavl.raiz->iz;
	}
	else
		raiz = NULL;
}
// Destructor
TAVLCalendario::~TAVLCalendario() {
	raiz = NULL;
}

// Sobrecarga del operador asignación
TAVLCalendario& TAVLCalendario::operator=(const TAVLCalendario& tavl) {
	/*if (raiz != NULL) {
		delete raiz;
		raiz = NULL;
	}*/
	if (tavl.raiz != NULL) {
		raiz = new TNodoAVL();
		raiz->item = tavl.raiz->item;
		raiz->fe = tavl.raiz->fe;
		raiz->iz = tavl.raiz->iz;
		raiz->de = tavl.raiz->de;
	}
	return *this;
}

//Metodos


	// Sobrecarga del operador igualdad
bool TAVLCalendario::operator==(const TAVLCalendario& tavl)const {
	bool iguales = false;
	if (tavl.raiz == NULL && raiz != NULL || raiz == NULL && tavl.raiz != NULL) {
		iguales = false;
	}
	else {
		if (tavl.raiz == NULL && raiz == NULL)
			iguales = true;
		else {
			TVectorCalendario vectThis, vectAVL;
			vectThis = Inorden();
			vectAVL = tavl.Inorden();
			if (vectThis == vectAVL)
				iguales = true;
		}

	}

	return iguales;
}
// Sobrecarga del operador desigualdad
bool TAVLCalendario::operator!=(const TAVLCalendario& tavl)const {
	if (*this == tavl)
		return false;
	return true;
}
// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TAVLCalendario::EsVacio()const {
	if (raiz == NULL)
		return true;
	else
		return false;
}


/*
VAR I, J, K: Iterador; E2: int;
si ( FE (HijoIzq (I) = -1 entonces
 //ROTACIÓN II
 Mover (J, HijoIzq (I));
 Mover (HijoIzq (I), HijoDer(J));
 Mover (HijoDer (J), I);
 FE (J) = 0; FE (HijoDer (J))=0;
 Mover (I,J);
sino
 //ROTACIÓN ID
 Mover (J, HijoIzq (I));
 Mover (K, HijoDer (J));
 E2 = FE (K);
 Mover (HijoIzq (I), HijoDer(K));
 Mover (HijoDer (J), HijoIzq(K));
 Mover (HijoIzq (K), J);
 Mover (HijoDer (K), I);
 FE (K) = 0;
 caso de E2
 -1: FE (HijoIzq (K)) = 0; FE (HijoDer (K)) = 1;
 +1: FE (HijoIzq (K)) = -1; FE (HijoDer (K)) = 0;
 0: FE (HijoIzq (K)) = 0; FE (HijoDer (K)) = 0;
 fcaso
 Mover (I, K);
fsi
*/

void TAVLCalendario::Mover(TAVLCalendario& tavl1, TAVLCalendario& tavl2) {
	tavl1.~TAVLCalendario();
	tavl1 = tavl2;
	tavl2.~TAVLCalendario();
}

void TAVLCalendario::Mover(TAVLCalendario& tavl1, TAVLCalendario*& tavl2) {
	tavl1.~TAVLCalendario();
	tavl1.raiz = tavl2->raiz;
	tavl2->raiz = NULL;

}

bool TAVLCalendario::EquilibrarDe() {
	TAVLCalendario J, K, * aux = this;
	int feAux = 0;
	if (raiz->de.raiz->fe == 1 || raiz->de.raiz->fe == 0) {//DD
		Mover(J, raiz->de);
		Mover(raiz->de, J.raiz->iz);
		Mover(J.raiz->iz, aux);
		J.raiz->fe = J.raiz->de.Altura() - J.raiz->iz.Altura();
		J.raiz->iz.raiz->fe = J.raiz->iz.raiz->de.Altura() - J.raiz->iz.raiz->iz.Altura();
		Mover(*this, J);
	}
	else {//DI
		Mover(J, raiz->de);
		Mover(K, J.raiz->iz);
		feAux = K.raiz->fe;
		Mover(raiz->de, K.raiz->iz);
		Mover(J.raiz->iz, K.raiz->de);
		Mover(K.raiz->de, J);
		Mover(K.raiz->iz, aux);
		K.raiz->fe = K.raiz->de.Altura() - K.raiz->iz.Altura();
		if (feAux == 0) {
			K.raiz->de.raiz->fe = 0;
			K.raiz->iz.raiz->fe = 0;
		}
		else if (feAux == 1) {
			K.raiz->de.raiz->fe = 1;
			K.raiz->iz.raiz->fe = 0;
		}
		else if (feAux == -1) {
			K.raiz->de.raiz->fe = 0;
			K.raiz->iz.raiz->fe = -1;
		}
		Mover(*this, K);
	}
	return false;
}

bool TAVLCalendario::EquilibrarIz() {
	TAVLCalendario J, K, * aux = this;
	int feAux = 0;

	if (raiz->iz.raiz->fe == -1|| raiz->iz.raiz->fe == 0) {		//II
		Mover(J, raiz->iz);
		Mover(raiz->iz, J.raiz->de);
		Mover(J.raiz->de, aux);
		J.raiz->fe = J.raiz->de.Altura() - J.raiz->iz.Altura();
		J.raiz->de.raiz->fe = J.raiz->de.Altura() - J.raiz->iz.Altura();
		Mover(*this, J);
	}
	else {//ID
		Mover(J, raiz->iz);
		Mover(K, J.raiz->de);
		feAux = K.raiz->fe;
		Mover(raiz->iz, K.raiz->de);
		Mover(J.raiz->de, K.raiz->iz);
		Mover(K.raiz->iz, J);
		Mover(K.raiz->de, aux);
		K.raiz->fe = K.raiz->de.Altura() - K.raiz->iz.Altura();
		if (feAux == 0) {
			K.raiz->iz.raiz->fe = 0;
			K.raiz->de.raiz->fe = 0;
		}
		else if (feAux == 1) {
			K.raiz->iz.raiz->fe = -1;
			K.raiz->de.raiz->fe = 0;
		}
		else if (feAux == -1) {
			K.raiz->iz.raiz->fe = 0;
			K.raiz->de.raiz->fe = 1;
		}
		Mover(*this, K);
	}
	return false;
}


// Inserta el elemento en el árbol
/*bool TAVLCalendario::Insertar(const TCalendario&cal){
	bool crece = false;
	return InsertarAux(cal, crece);
}*/

bool TAVLCalendario::Insertar(const TCalendario& c) {
	bool insertado = false, creceHijoIz = false, creceHijoDe = false;

	if (Buscar(c) == false) {
		if (raiz == NULL) {
			raiz = new TNodoAVL;
			raiz->item = c;
			insertado = true;
		}
		else {
			if (Raiz() > c) {
				insertado =creceHijoIz = raiz->iz.Insertar(c);
			}
			else if (Raiz() < c) {
				insertado = creceHijoDe = raiz->de.Insertar(c);
			}

			if (insertado) {
				if (creceHijoIz && raiz->fe == -1) 
					insertado = EquilibrarIz();
				
				else if (creceHijoDe && raiz->fe == 1) 
					insertado = EquilibrarDe();
				
				else if (creceHijoIz && raiz->fe == 0) 
					raiz->fe = -1;
				
				else if (creceHijoDe && raiz->fe == 0) 
					raiz->fe = 1;
				
				else if ((creceHijoIz && raiz->fe == 1) || (creceHijoDe && raiz->fe == -1)) {
					raiz->fe = 0;
					return false;
				}
			}
		}
	}
	else
		insertado = false;
	return insertado;
}

// Borra un TCalendario del árbol AVL
/*bool TAVLCalendario::Borrar(const TCalendario& cal) {
	bool crece = false;
	return BorrarAux(cal, crece);
}*/

bool TAVLCalendario::Borrar(const TCalendario& cal) {
	TNodoAVL* aux;
	int auxFe = -3;
	bool borrado = false;
	TCalendario mayor;
	if (raiz != NULL && Buscar(cal)) {
		if (raiz->item > cal)
			borrado = raiz->iz.Borrar(cal);
		else if (raiz->item < cal)
			borrado = raiz->de.Borrar(cal);
		else if (raiz->item == cal) {

			if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL) {
				delete raiz;
				raiz = NULL;
			}
			else if (raiz->iz.raiz != NULL && raiz->de.raiz == NULL) {
				aux = raiz;
				raiz = raiz->iz.raiz;
				aux->iz.raiz = NULL;
				delete aux;
			}
			else if (raiz->iz.raiz == NULL && raiz->de.raiz != NULL) {
				aux = raiz;
				raiz = raiz->de.raiz;
				aux->de.raiz = NULL;
				delete aux;
			}
			else if (raiz->iz.raiz != NULL && raiz->de.raiz != NULL) {
				mayor = raiz->iz.Mayor();
				raiz->item = mayor;
				raiz->iz.Borrar(mayor);

			}

			borrado = true;
		}
		int auxFe = 0;
		if (raiz != NULL && borrado) {
				auxFe = raiz->de.Altura() - raiz->iz.Altura();
			if (auxFe == 0 || auxFe == -1 || auxFe == 1) {
				raiz->fe = auxFe;
			}
			else {
				if (auxFe == -2) {
					EquilibrarIz();
				}
				else if (auxFe == 2) {
					EquilibrarDe();
				}
			}
		}
	}

	return borrado;

}

TCalendario TAVLCalendario::Mayor() const {
	TCalendario cal;
	if (raiz != NULL) {
		if (raiz->de.raiz == NULL) {
			cal = raiz->item;
		}
		else {
			cal = raiz->de.Mayor();
		}
	}
	return cal;
}


// Devuelve TRUE si el elemento está en el árbol, false en caso contrario
bool TAVLCalendario::Buscar(const TCalendario& cal)const {

	bool encontrado = false;

	if (raiz != NULL) {
		if (raiz->item == cal)
			encontrado = true;
		else {
			if (raiz->item > cal) {
				encontrado = raiz->iz.Buscar(cal);
			}
			else
				encontrado = raiz->de.Buscar(cal);

		}

	}

	return encontrado;
}
// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int TAVLCalendario::Altura()const {
	int alturaIzq = 0, alturaDer = 0;
	if (raiz != NULL) {
		alturaIzq = raiz->iz.Altura();
		alturaDer = raiz->de.Altura();
		alturaIzq = max(alturaIzq, alturaDer) + 1;
	}
	return alturaIzq;
}
// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int TAVLCalendario::Nodos()const {
	int nodos = 0;

	if (raiz != NULL) {
		nodos = 1;
		nodos = raiz->iz.Nodos() + raiz->de.Nodos() + 1;
	}
	return nodos;
}
// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int TAVLCalendario::NodosHoja()const {
	int nodosH = -1;
	if (raiz != NULL) {
		nodosH = 0;
		if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL) {
			nodosH = 1;
		}

		else {
			nodosH = nodosH + raiz->iz.NodosHoja() + raiz->de.NodosHoja();
		}
	}
	else {
		nodosH = 0;
	}
	return nodosH;

}
// Devuelve el recorrido en INORDEN sobre un vector
TVectorCalendario TAVLCalendario::Inorden()const {
	TVectorCalendario vector(Nodos());
	int pos = 1;
	InordenAux(vector, pos);
	return vector;
}
// Devuelve el recorrido en PREORDEN sobre un vector
TVectorCalendario TAVLCalendario::Preorden()const {
	TVectorCalendario vector(Nodos());
	int pos = 1;
	PreordenAux(vector, pos);
	return vector;
}
// Devuelve el recorrido en POSTORDEN sobre un vector
TVectorCalendario TAVLCalendario::Postorden()const {
	TVectorCalendario vector(Nodos());
	int pos = 1;
	PostordenAux(vector, pos);
	return vector;
}

// Recorrido por NIVELES 
TVectorCalendario TAVLCalendario::Niveles() const {
	queue<TNodoAVL*> cola;
	TVectorCalendario vect(Nodos());
	TNodoAVL* aux;
	int pos = 1;
	cola.push(raiz);
	while (cola.empty() == false) {
		aux = cola.front();
		cola.pop();
		if (aux != NULL) {
			cola.push(aux->iz.raiz);
			cola.push(aux->de.raiz);
			vect[pos++] = aux->item;
		}
	}
	return vect;

}

// Devuelve el elemento TCalendario raíz del árbol AVL
TCalendario TAVLCalendario::Raiz()const {
	TCalendario cal;
	if (raiz != NULL) {
		return raiz->item;
	}
	return cal;
}




// Sobrecarga del operador salida
ostream& operator<<(ostream& os,const TAVLCalendario& tavl) {
	os << tavl.Inorden() << endl;
	return os;
}


