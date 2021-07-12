#include <iostream>
#include <string.h>
#include "../include/tcalendario.h"
#include "../include/tlistacalendario.h"

using namespace std;



// Constructor por defecto
TNodoCalendario::TNodoCalendario() {
	siguiente = NULL;
}

// Constructor de copia
TNodoCalendario::TNodoCalendario(const TNodoCalendario& nodo){
	siguiente = nodo.siguiente;
	c = nodo.c;
}

// Destructor
TNodoCalendario::~TNodoCalendario(){
	siguiente = NULL;
}

// Sobrecarga del operador asignación
TNodoCalendario& TNodoCalendario::operator=(const TNodoCalendario& nodo){
	siguiente = nodo.siguiente;
	c = nodo.c;
	return *this;
}



//TListaPos:

// Constructor por defecto
TListaPos::TListaPos(){
	pos = NULL;
}
// Constructor de copia
TListaPos::TListaPos(const TListaPos& lp){
	pos = lp.pos;
}

// Destructor
TListaPos::~TListaPos(){
	//pos = NULL;
}

// Sobrecarga del operador asignación
TListaPos& TListaPos::operator=(const TListaPos& lp){
	pos = lp.pos;
	return *this;
}
// Sobrecarga del operador igualdad
bool TListaPos::operator==(const TListaPos& lp){
	if (lp.pos == pos)
		return true;
	return false;
}
// Sobrecarga del operador desigualdad
bool TListaPos::operator!=(const TListaPos& lp){
	if (lp.pos != pos)
		return true;
	return false;
}
// Devuelve la posición siguiente
TListaPos TListaPos::Siguiente() const{
	TListaPos lp;

	if (pos == NULL)
		lp.pos = NULL;
	else
		lp.pos = pos->siguiente;
	return lp;
}
// Posición vacía
bool TListaPos::EsVacia()const {
	if (pos == NULL)
		return true;
	return false;
}



//TListaCalendario:


// Constructor por defecto
TListaCalendario::TListaCalendario(){
	primero = NULL;
}

// Constructor de copia
TListaCalendario::TListaCalendario(TListaCalendario& list){
	primero = NULL;
	*this = list;
}
//Destructor
TListaCalendario::~TListaCalendario(){
	TNodoCalendario *temp; //Creamos nodo temporal para guardar pointer
	temp = primero;
	while (temp!=NULL) {
		primero = primero->siguiente;
		delete temp;
		temp=primero;
	}
}

// Sobrecarga del operador asignación
TListaCalendario& TListaCalendario::operator=(const TListaCalendario& lista){
	TNodoCalendario *nodoCopia, *nodoIterator, *nodoPosicion = NULL;
	nodoCopia = new TNodoCalendario();
	nodoIterator = lista.primero;

	if (this != &lista && nodoIterator!=NULL) {
		this->~TListaCalendario();
		if (&lista != NULL) {
			while (nodoIterator != NULL) {
				if (primero != NULL) {
					nodoPosicion->siguiente = nodoCopia;
				}
				else {
					primero = nodoCopia;
				}
				// Mover los datos
				nodoCopia->c = nodoIterator->c; 
				nodoPosicion = nodoCopia; 
				nodoCopia = new TNodoCalendario();
				//siguiente de dato
				nodoIterator = nodoIterator->siguiente;
			}
		}
	}
	return *this;
}

// Sobrecarga del operador igualdad
bool TListaCalendario::operator==(const TListaCalendario& lista)const{
	TNodoCalendario *nodo1, *nodo2;
	nodo1 = primero;
	nodo2 = lista.primero;
	while (nodo1 != NULL && nodo2 != NULL) {
		if (nodo1->c != nodo2->c)
			return false;
	}
	return true;
}

//Sobrecarga del operador suma
TListaCalendario TListaCalendario::operator+ (const TListaCalendario& lista)const {
	TListaCalendario temp; //lista que devolveremos
	TNodoCalendario *tempNodo;
	tempNodo = lista.primero;
	temp = *this;
	while (tempNodo != NULL) {
		temp.Insertar(tempNodo->c);
		tempNodo = tempNodo->siguiente;
	}
	return temp;
}

//Sobrecarga del operador resta
TListaCalendario TListaCalendario::operator- (const TListaCalendario& lista)const {
	TListaCalendario copia;
	copia = *this;
	TNodoCalendario *iterator;
	iterator = lista.primero;
	
	while (iterator != NULL) {
		copia.Borrar(iterator->c); //Usamos funcion borrar
		iterator=iterator->siguiente;
	}
	return copia;
}

// Inserta el elemento en la posición que le corresponda dentro de la lista
bool TListaCalendario::Insertar(const TCalendario& calendario){

	bool insertado = false;
	TNodoCalendario *nodoCopia, *nodoIterator, *nodoPosicion=NULL;
	nodoCopia = new TNodoCalendario();
	nodoCopia->c = calendario;
	nodoIterator=primero;

	//buscamos posicion para insertar
	while (nodoIterator != NULL && nodoIterator->c < calendario && nodoIterator->c != calendario){
		nodoPosicion = nodoIterator;
		nodoIterator = nodoIterator->siguiente;
	}

	//Insertamos:
	//Al principio si nodoPosicion se ha quedado en NULL
	if (nodoPosicion == NULL) {
		nodoCopia->siguiente = nodoIterator;
		primero = nodoCopia;
		insertado = true;
	}
	//En medio si iteratro es distinto de NULL
	else if (nodoIterator != NULL && nodoPosicion != NULL) {
		nodoPosicion->siguiente = nodoCopia;
		nodoCopia->siguiente = nodoIterator;
		insertado = true;
	}
	//Al final si iterator es null y posicion no
	else if (nodoIterator ==NULL && nodoPosicion!=NULL) {
		nodoPosicion->siguiente = nodoCopia;
		nodoCopia->siguiente = nodoIterator;
		insertado = true;
	}

	return insertado;
}

// Busca y borra el elemento
// La implementacion es parecida a Insertar(TCalendario&)
bool TListaCalendario::Borrar(const TCalendario& calendario){
	bool borrado = false;
	TNodoCalendario* nodoCopia, * nodoIterator, * nodoPosicion = NULL;
	nodoCopia = new TNodoCalendario();
	nodoCopia->c = calendario;
	nodoIterator = primero;

	//buscamos posicion para borrar
	while (nodoIterator != NULL && nodoIterator->c < calendario) {
		nodoPosicion = nodoIterator;
		nodoIterator = nodoIterator->siguiente;
	}

	//Borramos si los calendarios son iguales
	//nodoPosicion != NULL &&
	if ( /*nodoPosicion*/nodoIterator->c == calendario) {
		if (primero == nodoIterator) {
			primero=primero->siguiente;
		}
		else {
			nodoPosicion->siguiente = nodoIterator->siguiente;
		}
		delete nodoIterator;
		borrado = true;
	}
	return borrado;
}

// Borra el elemento que ocupa la posición indicada
bool TListaCalendario::Borrar(const TListaPos& posicion){
	TListaCalendario copia;
	copia = *this;
	return this->Borrar(this->Obtener(posicion));
}

//Borra todos los Calendarios con fecha ANTERIOR a la pasada.
bool TListaCalendario::Borrar(int dia, int mes, int anyo){ //REVISAR
	bool borrado = false;
	TCalendario cal(dia,mes,anyo,NULL);
	TListaCalendario copia;
	copia = *this;
	TNodoCalendario *copiaNodo;
	copiaNodo = copia.primero;
	while (copiaNodo->c < cal) {
		copia.Borrar(copiaNodo->c);
		copiaNodo = copiaNodo->siguiente;
		borrado = true;
	}
	return borrado;
}
// Devuelve true si la lista está vacía, false en caso contrario
bool TListaCalendario::EsVacia()const {
	if (primero == NULL)
		return true;
	return false;
}

// Obtiene el elemento que ocupa la posición indicada
TCalendario TListaCalendario::Obtener(const TListaPos& posicion)const {
	bool encontrado = false;

	TNodoCalendario *iterator;
	iterator = primero;
	TCalendario cal; //calendario Vacio

	while (iterator!=NULL && !encontrado) {
		if (iterator == posicion.pos) {
			encontrado = true;
		}
		else {
			iterator = iterator->siguiente;
		}
	}
	if (encontrado)
		return iterator->c;
	return cal;

}
// Devuelve true si el Calendario está en la lista.
bool TListaCalendario::Buscar(const TCalendario& cal)const{
	bool encontrado = false;
	TNodoCalendario *iterator;
	TListaCalendario copia;
	copia = *this;
	iterator = copia.primero;

	while (!encontrado && iterator!=NULL) {
		if (iterator->c == cal)
			encontrado = true;
		iterator = iterator->siguiente;
	}
	return encontrado;
}
// Devuelve la longitud de la lista
int TListaCalendario::Longitud()const{
	TNodoCalendario *iterator;
	iterator = primero;
	int longitud=0;
	while (iterator != NULL) {
		iterator = iterator->siguiente;
		longitud++;
	}
	return longitud;
}

// Devuelve la primera posición en la lista
TListaPos TListaCalendario::Primera()const{
	TListaPos prim;
	TNodoCalendario *nodo;
	nodo = primero;
	prim.pos= nodo;
	return prim;
}
// Devuelve la última posición en la lista
TListaPos TListaCalendario::Ultima()const {
	TListaPos ultima;
	TNodoCalendario *iterator;
	iterator= primero;
	while (iterator !=NULL && iterator->siguiente!=NULL){
		iterator = iterator->siguiente;
	}
	ultima.pos = iterator;
	return ultima;
}
// Suma de dos sublistas en una nueva lista
TListaCalendario TListaCalendario::SumarSubl(int I_L1, int F_L1,const TListaCalendario& L2, int I_L2,
	int F_L2)const{
	TListaCalendario lista1, lista2, lista3;//copias para no borrar elementos
	lista1 = *this;
	lista2 = L2;
	
	lista3= lista1.ExtraerRango(I_L1,F_L2)+ lista2.ExtraerRango(I_L2, F_L2);
	return lista3;
	}
// Extraer un rango de nodos de la lista
TListaCalendario TListaCalendario::ExtraerRango(int n1, int n2){
	TListaCalendario lista;

	TNodoCalendario *iterator;
	iterator = primero;

	if (n2 > lista.Longitud())
		n2 = lista.Longitud();
	if (n1 <= 0)
		n1 = 1;
	if (n1 > n2)
		return lista; //lista vacia;
	lista = *this;
	
	for (int i = 1;i < n1;i++) 
		iterator = iterator->siguiente; //vamos hasta posicion de n1

	for (int i = n1;i <= n2;i++) {
		lista.Insertar(iterator->c); //insertamos en la lista nueva
		this->Borrar(iterator->c);	//borramos de la lista antigua
		iterator = iterator->siguiente;
	}
	return lista;
	
}

//Sobrecarga del operador salida
ostream& operator<<(ostream& os, const TListaCalendario& lista) {
	TListaPos posicion,ultimo;
	posicion=lista.Primera();
	ultimo = lista.Ultima();
	os << "<";
	if (posicion == lista.Ultima()  && lista.Longitud()==1)
		os << lista.Obtener(posicion);

	else {
		while (posicion != lista.Ultima()) {
			os << lista.Obtener(posicion) << " ";
			posicion = posicion.Siguiente();
			if (posicion == lista.Ultima())
				os << lista.Obtener(posicion);
		}
	}
	os << ">";
	return os;

}
