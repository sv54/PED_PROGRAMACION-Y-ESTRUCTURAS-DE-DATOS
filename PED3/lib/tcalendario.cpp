#include <iostream>
#include <string.h>
#include <string>
#include "../include/tcalendario.h"

using namespace std;

#pragma warning(disable:4996)


	//Constructor por defecto: inicializa dia, mes y anyo a 1/1/1900 y mensaje a NULL
	TCalendario::TCalendario() {
		dia = 1;
		mes = 1;
		anyo = 1900;
		mensaje = NULL;
	}

	TCalendario::TCalendario(int dia, int mes, int anyo,const char* mens) {
		if (ComprobacionFecha(dia, mes, anyo)) {
			this->dia = dia;
			this->mes = mes;
			this->anyo = anyo;
			
			if (mens != NULL) {
				mensaje = new char[strlen(mens) + 1];
				strcpy(mensaje, mens);
			}
			else
				mensaje = NULL;
		}
		else {
			this->dia = 1;
			this->mes = 1;
			this->anyo = 1900;
			mensaje = NULL;
		}
	}

	//Constructor copia
	TCalendario::TCalendario(TCalendario& cal) {
		dia = cal.dia;
		mes = cal.mes;
		anyo = cal.anyo;
		mensaje = cal.mensaje;
		ModMensaje(cal.mensaje);
	}

	//Destructor
	TCalendario::~TCalendario() {
		dia = 1;
		mes = 1;
		anyo = 1900;
		mensaje = NULL;
	}

	// Sobrecarga del operador asignación
	TCalendario& TCalendario::operator=(const TCalendario& c) {
		if (ComprobacionFecha(c.dia, c.mes, c.anyo)) {
			dia = 1;
			mes = 1;
			anyo = 1900;
			mensaje = NULL;
			dia = c.dia;
			mes = c.mes;
			anyo = c.anyo;
			ModMensaje(c.mensaje);


			return *this;
		}
		else {
			TCalendario temp;
			return temp;
		}
	}



	//Metodos


	// Sobrecarga del operador: SUMA de fecha + un número de dias;
	TCalendario TCalendario::operator+(int cantDias) { //Revisar
		TCalendario temp;
		temp.dia = dia;
		temp.mes = mes;
		temp.anyo = anyo;
		temp.mensaje = new char[strlen(mensaje) + 1];
		strcpy(temp.mensaje, mensaje);
		if (cantDias > 0) {
			for (cantDias > 0;cantDias--;) {
				if (ComprobacionFecha(temp.dia+1, temp.mes, temp.anyo)) {
					temp.dia++;
				}
				else {
					if (ComprobacionFecha(1, temp.mes+1, temp.anyo)) {
						temp.dia = 1;
						temp.mes++;
					}
					else {
						if (ComprobacionFecha(1, 1, temp.anyo+1)) {
							temp.dia = 1;
							temp.mes = 1;
							temp.anyo++;
						}
					}
				}
			}

			
		}
		return temp;
	
	}

	// Sobrecarga del operador: RESTA de fecha - un número de dias;
	TCalendario TCalendario::operator-(int cantDias) {
		TCalendario temp(*this);
		
		if (cantDias > 0) {
			for (cantDias > 0;cantDias--;) {
				if (ComprobacionFecha(temp.dia - 1, temp.mes, temp.anyo)) {
					temp.dia--;
				}
				else {
					if (ComprobacionFecha(31, temp.mes - 1, temp.anyo)) {
						temp.dia = 31;
						temp.mes--;
					}
					else if (ComprobacionFecha(30, temp.mes - 1, temp.anyo)) {
						temp.dia = 30;
						temp.mes--;
					}
					else if (ComprobacionFecha(29, temp.mes - 1, temp.anyo)) {
						temp.dia = 29;
						temp.mes--;
					}
					else if (ComprobacionFecha(28, temp.mes - 1, temp.anyo)) {
						temp.dia = 28;
						temp.mes--;
					}
					else {
						if (ComprobacionFecha(31, 12, temp.anyo - 1)) {
							temp.dia = 31;
							temp.mes = 12;
							temp.anyo--;
						}
						else {
							TCalendario vacio;
							return vacio;
						}
					}
				}
			}

		}
		return temp;
	}
	
	// Modifica la fecha incrementándola en un dia (con postincremento);
	TCalendario TCalendario::operator++(int i) { //Revisado!
		TCalendario temp(*this);
		++(*this);
		/*
		if(ComprobacionFecha(dia + 1, mes, anyo))
			temp.dia++;
		else {
			if (ComprobacionFecha(1, mes + 1, anyo)) {
				temp.dia = 1;
				temp.mes = mes++;
			}
			else {
				if (ComprobacionFecha(1, 1, anyo+1)) {
					temp.dia = 1;
					temp.mes = 1;
					temp.anyo++;
				}
			}
		}
		*/
		return temp;
	}
	
	// Modifica la fecha incrementándola en un dia (con preincremento);
	TCalendario& TCalendario::operator++() { //Revisado!
		if (ComprobacionFecha(dia + 1, mes, anyo))
			dia++;
		else {
			if (ComprobacionFecha(1, mes + 1, anyo)) {
				dia = 1;
				mes = mes++;
			}
			else {
				if (ComprobacionFecha(1, 1, anyo + 1)) {
					dia = 1;
					mes = 1;
					anyo++;
				}
			}
		}
		return *this;
	}
	
	// Modifica la fecha decrementándola en un dia (con postdecremento);
	TCalendario TCalendario::operator--(int) {
		TCalendario temp(*this);
		--(*this);
		return temp;
		/*
		if (ComprobacionFecha(temp.dia - 1, temp.mes, temp.anyo)) {
			temp.dia--;
		}
		else {
			if (ComprobacionFecha(31, temp.mes - 1, temp.anyo)) {
				temp.dia = 31;
				temp.mes--;
			}
			else if (ComprobacionFecha(30, temp.mes - 1, temp.anyo)) {
				temp.dia = 30;
				temp.mes--;
			}
			else if (ComprobacionFecha(29, temp.mes - 1, temp.anyo)) {
				temp.dia = 29;
				temp.mes--;
			}
			else if (ComprobacionFecha(28, temp.mes - 1, temp.anyo)) {
				temp.dia = 28;
				temp.mes--;
			}
			else {
				if (ComprobacionFecha(31, 12, temp.anyo - 1)) {
					temp.dia = 31;
					temp.mes = 12;
					temp.anyo--;
				}
			}
		}
		
		return temp;
		*/
	}

	// Modifica la fecha decrementándola en un día (con predecremento);
	TCalendario& TCalendario::operator--() {
		if (ComprobacionFecha(dia - 1, mes, anyo)) {
			dia--;
		}
		else {
			if (ComprobacionFecha(31, mes - 1, anyo)) {
				dia = 31;
				mes--;
			}
			else if (ComprobacionFecha(30, mes - 1, anyo)) {
				dia = 30;
				mes--;
			}
			else if (ComprobacionFecha(29, mes - 1, anyo)) {
				dia = 29;
				mes--;
			}
			else if (ComprobacionFecha(28, mes - 1, anyo)) {
				dia = 28;
				mes--;
			}
			else {
				if (ComprobacionFecha(31, 12, anyo - 1)) {
					dia = 31;
					mes = 12;
					anyo--;
				}
				else {
					mensaje = NULL;
				}
			}
		}
		return *this;
	}

	// Modifica la fecha
	bool TCalendario::ModFecha(int d, int m, int a) {
		if (ComprobacionFecha(d, m, a)) {
			dia = d;
			mes = m;
			anyo = a;
			return true;
		}
		return false;
	}

	// Modifica el mensaje
	bool TCalendario::ModMensaje(char* m) {
		if (m != NULL) {
			mensaje = new char[strlen(m) + 1];
			strcpy(mensaje, m);
			return true;
		}
		else
			mensaje = NULL;
		return false;
	}
	
	// Sobrecarga del operador igualdad;
	bool TCalendario::operator ==(const TCalendario&  c)const  {
		if (dia == c.dia && mes == c.mes && anyo == c.anyo) {
			if (mensaje == NULL && c.mensaje == NULL)
				return true;
			else if (mensaje != NULL && c.mensaje != NULL)
				if (strcmp(mensaje, c.mensaje) == 0)
					return true;
			
		}
		return false;

	}
	
	// Sobrecarga del operador desigualdad;
	bool TCalendario::operator !=(const TCalendario& c)const { //REESCRIBIR
		if (*this == c)
			return false;
		return true;
	}

	
	// Sobrecarga del operador >
	bool TCalendario::operator>(const TCalendario& c)const {
		if (anyo > c.anyo)
			return true;
		else if (anyo < c.anyo)
			return false;
		else {
			if (mes > c.mes)
				return true;
			else if (mes < c.mes)
				return false;
			else {
				if (dia > c.dia)
					return true;
				else if (dia < c.dia)
					return false;
				else
					if (mensaje == NULL && c.mensaje == NULL)
						return false;
					else if (mensaje == NULL && c.mensaje != NULL)
						return false;
					else if (mensaje != NULL && c.mensaje == NULL)
						return true;
					else if (strlen(mensaje) > strlen(c.mensaje))
						return true;
					else
						return false;

			}
		}
	}
	
	// Sobrecarga del operador <; (ver ACLARACIÓN sobre ORDENACIÓN)
	bool TCalendario::operator<(const TCalendario& c)const {
		if (anyo < c.anyo)
			return true;
		else if (anyo > c.anyo)
			return false;
		else {
			if (mes < c.mes)
				return true;
			else if (mes > c.mes)
				return false;
			else {
				if (dia < c.dia)
					return true;
				else if (dia > c.dia)
					return false;
				else
					if (mensaje == NULL && c.mensaje == NULL)
						return false;
					else if (mensaje == NULL && c.mensaje != NULL)
						return false;
					else if (mensaje != NULL && c.mensaje == NULL)
						return true;
					else if (strlen(mensaje) < strlen(c.mensaje))
						return true;
					else
						return false;

			}
		}
	}
	

	

	//TCalendario vacío
	bool TCalendario::EsVacio() {
		if (dia == 1 && mes == 1 && anyo == 1900 && mensaje == NULL)
			return true;
		return false;
	}

	// Devuelve el día del calendario;
	int TCalendario::Dia() {
		return dia;
	}
	
	// Devuelve el mes del calendario;
	int TCalendario::Mes() {
		return mes;
	}

	// Devuelve el año del calendario;
	int TCalendario::Anyo() {
		return anyo;
	}

	// Devuelve el mensaje del calendario;
	char* TCalendario::Mensaje() const {
		return mensaje;
	}


	//Metodos Auxiliares

	bool TCalendario::ComprobacionFecha(int dia, int mes, int anyo) {
		bool b = AnyoBisiesto(anyo);
		if (dia < 1 || dia>31 || mes < 1 || mes>12 || anyo < 1900) {
			return false;
		}
			
		else if (dia > 30 && (mes == 4 || mes == 6 || mes == 11 || mes == 9))
			return false;
		else if ((mes == 2 && dia > 28 && b == false) || (mes == 2 && dia > 29 && b == true))
			return false;
		else
			return true;
	}

	bool TCalendario::AnyoBisiesto(int anyo) {
		if (anyo % 4 == 0 && (anyo % 100 != 0 || anyo % 400 == 0))
			return true;
		else
			return false;

	}
	ostream& operator<<(ostream& os, const TCalendario& c) {
		if (c.dia < 10)
			os << "0" << c.dia << "/";
		else
			os << c.dia<<"/";

		if (c.mes < 10)
			os << "0" << c.mes<< "/";
		else
			os << c.mes<<"/";

		os << c.anyo;

		if (c.Mensaje() == NULL)
			os << " \"\"";
		else
			os <<" \"" <<c.Mensaje()<<"\"";
		return os;
	
	}

