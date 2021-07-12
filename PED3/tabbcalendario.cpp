#include <iostream>
#include <string.h>
#include <string>
#include "tcalendario.h"
#include "tabbcalendario.h"
#include <queue>

using namespace std;

//TNodoABB:

TNodoABB::TNodoABB() {
	item = TCalendario();
}
//Constructor copia
TNodoABB::TNodoABB(TNodoABB&) {

}
//Destructor
TNodoABB::~TNodoABB() {


}
// Sobrecarga del operador asignación
TNodoABB& TNodoABB::operator=(TNodoABB& tn) {
	item = tn.item;
	iz = tn.iz;
	de = tn.de;

	return *this;
}



//TabbCalendario:


// Constructor por defecto
TABBCalendario::TABBCalendario() {
	raiz = NULL;
}
// Constructor de copia
TABBCalendario::TABBCalendario(const TABBCalendario& tabb) {
	if(tabb.raiz!=NULL) {
		raiz = new TNodoABB();
		raiz->item = tabb.raiz->item;
		raiz->iz = tabb.raiz->iz;
		raiz->de = tabb.raiz->de;
	}
	else {
		raiz = NULL;
	}
}
// Destructor
TABBCalendario::~TABBCalendario() {
	if (raiz != NULL) {
		delete raiz;
		raiz = NULL;
	}

}
// Sobrecarga del operador asignación
TABBCalendario& TABBCalendario::operator=(const TABBCalendario& tabb) {
	if (tabb.raiz != NULL) {
		this->~TABBCalendario();
		raiz = new TNodoABB();
		raiz->item = tabb.raiz->item;
		raiz->iz = tabb.raiz->iz;
		raiz->de = tabb.raiz->de;
	}
	return *this;
}


// AUXILIAR: devuelve el recorrido en INORDEN
void TABBCalendario::InordenAux(TVectorCalendario& vecc, int& pos) const {
	if (raiz != NULL) {
		raiz->iz.InordenAux(vecc, pos);
		vecc[pos] = raiz->item;
		pos++;
		raiz->de.InordenAux(vecc, pos);
	}
}
// AUXILIAR: devuelve el recorrido en PREORDEN
void TABBCalendario::PreordenAux(TVectorCalendario& vecc, int& pos)const {
	if (raiz != NULL) {
		vecc[pos] = raiz->item;
		pos++;
		raiz->iz.PreordenAux(vecc, pos);
		raiz->de.PreordenAux(vecc, pos);
	}
}
// AUXILIAR: devuelve el recorrido en POSTORDEN
void TABBCalendario::PostordenAux(TVectorCalendario& vecc, int& pos) const {
	if(raiz != NULL) {
		raiz->iz.PostordenAux(vecc, pos);
		raiz->de.PostordenAux(vecc, pos);
		vecc[pos] = raiz->item;
		pos++;
	}
}

TCalendario TABBCalendario::Mayor() const{
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

//Metodos

// Sobrecarga del operador igualdad
bool TABBCalendario::operator==(const TABBCalendario& tabb)const {
	bool iguales = false;
	if (tabb.raiz == NULL && raiz != NULL || raiz == NULL && tabb.raiz != NULL) {
		iguales = false;
	}
	else {
		if (tabb.raiz == NULL && raiz == NULL)
			iguales = true;
		else {
			TVectorCalendario vectThis, vectAbb;
			vectThis = Inorden();
			vectAbb = tabb.Inorden();
			if (vectThis == vectAbb)
				iguales = true;
		}
	
	}

	return iguales;
}
// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TABBCalendario::EsVacio() {
	if (raiz == NULL)
		return true;
	return false;
}
// Inserta el elemento en el árbol
bool TABBCalendario::Insertar(const TCalendario& cal) {
	bool insertado = false;

	if (raiz == NULL) {
		raiz = new TNodoABB;
		raiz->item = cal;
		insertado = true;
	}
	else {
		if (raiz->item < cal) {
			insertado = raiz->de.Insertar(cal);
		}
		else if (raiz->item > cal) {
			insertado = raiz->iz.Insertar(cal);
		}
		else
			insertado = false;

	}

	return insertado;
}
// Borra el elemento en el árbol
bool TABBCalendario::Borrar(const TCalendario& cal) {
	TNodoABB* aux;
	bool borrado = false;
	TCalendario mayor;
	if (raiz != NULL && Buscar(cal)) {
		if (raiz->item > cal) 
			borrado = raiz->iz.Borrar(cal);
		else if (raiz->item < cal)
			borrado = raiz->de.Borrar(cal);
		else {
			
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
			return borrado;
			
		}
	}
	else {
		return borrado;
	}

}
// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TABBCalendario::Buscar(const TCalendario& cal) const{ //REVISAR
	bool encontrado = false;

	if (raiz != NULL) {
		if (raiz->item == cal)
			encontrado=true;
		else { 
			if (raiz->item > cal) {
				encontrado =raiz->iz.Buscar(cal);
			}
			else
				encontrado = raiz->de.Buscar(cal);
		
		}
			
	}
	
	return encontrado;
}
// Devuelve el elemento de la raíz del árbol
TCalendario TABBCalendario::Raiz() const {
	TCalendario c;
	if (raiz != NULL) {
		c = raiz->item;
	}
	return c;
}
// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int TABBCalendario::Altura()const { //REVISAR
	int alturaIzq = 0, alturaDer=0;
	if (raiz != NULL) {
		alturaIzq = raiz->iz.Altura();
		alturaDer = raiz->de.Altura();
		alturaIzq = max(alturaIzq, alturaDer)+1;
	}
	return alturaIzq;
}
// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int TABBCalendario::Nodos()const {
	int nodos = 0;

	if (raiz != NULL) {
		nodos = 1;
		nodos = raiz->iz.Nodos() + raiz->de.Nodos()+1;
	}
	return nodos;
}
// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int TABBCalendario::NodosHoja()const {
	int nodosH=-1;
	if (raiz != NULL){
		nodosH = 0;
		if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL) {
			nodosH = 1;
		}
		
		else { //REVISAR
			nodosH = nodosH + raiz->iz.NodosHoja() + raiz->de.NodosHoja();
		}
	}
	else if (raiz == NULL)
		nodosH = 0;
	
	return nodosH;
}

// Devuelve el recorrido en INORDEN sobre un vector
TVectorCalendario TABBCalendario::Inorden() const {
	TVectorCalendario vector(Nodos());
	int pos = 1;
	InordenAux(vector, pos);
	return vector;
}
// Devuelve el recorrido en PREORDEN sobre un vector
TVectorCalendario TABBCalendario::Preorden() const{
	TVectorCalendario vector(Nodos());
	int pos = 1;
	PreordenAux(vector, pos);
	return vector;
}
// Devuelve el recorrido en POSTORDEN sobre un vector
TVectorCalendario TABBCalendario::Postorden() const{
	TVectorCalendario vector(Nodos());
	int pos = 1;
	PostordenAux(vector, pos);
	return vector;
}
// Devuelve el recorrido en NIVELES sobre un vector
TVectorCalendario TABBCalendario::Niveles() const{
	queue<TNodoABB*> cola;
	TVectorCalendario vect(Nodos());
	TNodoABB* aux;
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

// Suma de dos ABB
TABBCalendario TABBCalendario::operator+(const TABBCalendario& tabb) const {
	TABBCalendario temp(*this);
	TVectorCalendario vect;
	vect = tabb.Inorden();
	for (int i = 1; i <= vect.Tamano(); i++) {
		temp.Insertar(vect[i]);
	}
	return temp;
}
// Resta de dos ABB
TABBCalendario TABBCalendario::operator-( const TABBCalendario& tabb) const{
	TABBCalendario temp;
	TVectorCalendario vect;
	vect = this->Inorden();
	for (int i = 1; i <= vect.Tamano(); i++) {
		if (!tabb.Buscar(vect[i]))
			temp.Insertar(vect[i]);

	}
	return temp;
}


//Examen

TVectorCalendario TABBCalendario::ABBCamino(const TListaCalendario& lista) {
	TVectorCalendario vect(0);
	TListaPos pos= lista.Primera();
	TNodoABB *aux = raiz;
	TCalendario cal;
	int numItems = 1;
	
	if (lista.EsVacia() || this->EsVacio() || lista.Obtener(pos).EsVacio())
		return vect;

	for (TListaPos i = lista.Primera(); !i.EsVacia(); i = i.Siguiente()) {
		int contador = 1;
		raiz = aux;
		if (!this->Buscar(lista.Obtener(i))) {
			cal = lista.Obtener(i);
			this->Insertar(lista.Obtener(i));
			while (raiz->item != cal) {
				if (vect.Tamano() == numItems - 1)
					vect.Redimensionar(numItems);
				vect[numItems] = raiz->item;
				if (raiz->item > cal)
					raiz = raiz->iz.raiz;
				else
					raiz = raiz->de.raiz;
				numItems++;
				if (vect.Tamano() == numItems - 1)
					vect.Redimensionar(numItems);
				contador++;
			}
			
			vect[numItems] = raiz->item;
			numItems++;
			
			//cout << vect << endl;
		}
	}


	return vect;
}

// Sobrecarga del operador salida
ostream& operator<<(ostream& os, TABBCalendario& tabb) {
	os << tabb.Niveles() << endl;
	return os;
}
