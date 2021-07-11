
#include <iostream>
#include <string.h>
#include <string>
#include "tcalendario.h"
#include "tvectorcalendario.h"
using namespace std;

// Constructor por defecto
TVectorCalendario::TVectorCalendario() {
	c = NULL;
	tamano = 0;
	
}
// Constructor a partir de un tamaño
TVectorCalendario::TVectorCalendario(int n) {
	if (n < 0) {
		tamano = 0;
		c = NULL;
	}
	else {
		tamano = n;
		c = new TCalendario[n];
	}
}
// Constructor de copia

TVectorCalendario::TVectorCalendario(TVectorCalendario& vecc) {
	tamano = vecc.tamano;
	c = new TCalendario[tamano];
	for (int i = 0; i < tamano; i++) {
		c[i] = vecc.c[i];
	}
}

// Destructor
TVectorCalendario::~TVectorCalendario() {
	if (c != NULL) {
		delete[] c;
		tamano = 0;
		c = NULL;
	}
}

// Sobrecarga del operador asignación
TVectorCalendario& TVectorCalendario::operator=(const TVectorCalendario& vecc) {
	delete[] c;
	tamano = vecc.tamano;
	c = new TCalendario[tamano];
		for (int i = 0;i < tamano;i++)
			c[i] = vecc.c[i];
		if (c == NULL)
			tamano = 0;
		return *this;
}

// Sobrecarga del operador igualdad
bool TVectorCalendario::operator==(const TVectorCalendario& vecc) const{
	if (vecc.tamano != tamano)
		return false;
	else {
		for (int i = 0; i < tamano;i++) {
			if (c[i] != vecc.c[i])
				return false;
		}
		return true;
	}
}

// Sobrecarga del operador desigualdad
bool TVectorCalendario::operator!=(const TVectorCalendario& vecc) const {
	if (*this == vecc)
		return false;
	return true;
}

// Sobrecarga del operador corchete (parte IZQUIERDA)
TCalendario& TVectorCalendario::operator[](int i) {
	if (i >= 1 && i <= tamano)
		return c[i - 1];

	//TCalendario error;
	return error;

}

// Sobrecarga del operador corchete (parte DERECHA)
TCalendario TVectorCalendario::operator[](int i) const {
	if (i >= 1 && i <= tamano)
		return c[i - 1];

	TCalendario error;
	return error;

}

// Tamaño del vector (posiciones TOTALES)
int TVectorCalendario::Tamano() {
	return tamano;
}

// Cantidad de posiciones OCUPADAS (no vacías) en el vector
int TVectorCalendario::Ocupadas() {
	int contador=0;
	for (int i = 0; i < tamano;i++) {
		if (!c[i].EsVacio()) {
			contador++;
		}
	}
	return contador;
}

// Devuelve TRUE si existe el calendario en el vector
bool TVectorCalendario::ExisteCal(TCalendario& cal) {
	for (int i = 0;i < tamano;i++) {
		if (c[i] == cal)
			return true;
	}
	return false;

}

void TVectorCalendario::MostrarMensajes(int dia, int mes, int anyo) {
	TVectorCalendario temp(*this);
	TCalendario tempCal(dia,mes,anyo, NULL);
	if (ComprobacionFecha(dia, mes, anyo)) {
		cout << "[";
		for (int i = 0; i < temp.tamano;i++) {
			if (temp.c[i] > tempCal || temp.c[i] == tempCal)
				cout << tempCal<<", ";
		}
		cout << "]";
	}
}


bool TVectorCalendario::Redimensionar(int n) {
	int tempTamano = tamano;
	TCalendario* tempC = new TCalendario[n];
	TCalendario vacio;
	if(n<=0 || n==tamano)
		return false;
	else if (n > tamano) {
		tamano = n;
		
		for (int j = 0;j < tempTamano;j++) {
			tempC[j] = c[j];
		}
		for (int i = tempTamano;i < n;i++) {
			tempC[i] =vacio;
		}
		c = new TCalendario[n];
		c = tempC;
		return true;
	}
	else {
		tamano = n;
		for (int j = 0;j < n;j++) {
			tempC[j] = c[j];
		}

		delete[] c;
		c = NULL;
		c = tempC;
		tamano = n;
		return true;
		
	}

}

// Sobrecarga del operador salida
ostream& operator<<(ostream& os, const TVectorCalendario& vecc) {
	int i = 1;
	os << "[";
	for (int j = 0;j < vecc.tamano;j++) {
		if (j == vecc.tamano-1) {
			os << "(" << i << ") " << vecc.c[j] ;
		}
		else {
			os << "(" << i << ") " << vecc.c[j] << ", ";
		}
		i++;
	}
	os << "]";
	return os;
}


bool TVectorCalendario::ComprobacionFecha(int dia, int mes, int anyo) {
	bool b = AnyoBisiesto(anyo);
	if (dia < 1 || dia>31 || mes < 1 || mes>12 || anyo < 1900) {
		return false;
	}

	if (dia > 30 && (mes == 4 || mes == 6 || mes == 11 || mes == 9))
		return false;
	if ((mes == 2 && dia > 28 && b == false) || (mes == 2 && dia > 29 && b == true))
		return false;
	else
		return true;
}

bool TVectorCalendario::AnyoBisiesto(int anyo) {
	if (anyo % 4 == 0 && (anyo % 100 != 0 || anyo % 400 == 0))
		return true;
	else
		return false;

}
