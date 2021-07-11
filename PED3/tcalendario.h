﻿#pragma once
#include <iostream>
#include <string.h>
#include <string>



using namespace std;




class TCalendario {
	private:
		int dia;
		int mes;
		int anyo;
		char* mensaje;
		bool ComprobacionFecha(int dia, int mes, int anyo);
		bool AnyoBisiesto(int anyo);

	public:
		//Constructor por defecto: inicializa dia, mes y anyo a 1/1/1900 y mensaje a NULL
		TCalendario();
		//Constructor que inicializa calendario con parámetros pasados
		TCalendario(int dia, int mes, int anyo,const char* mens);
		//Constructor copia
		TCalendario(TCalendario&);
		//Destructor
		~TCalendario();
		// Sobrecarga del operador asignación
		TCalendario& operator=(const TCalendario&);


		//Metodos


		// Sobrecarga del operador: SUMA de fecha + un número de dias;
		TCalendario operator+(int);
		// Sobrecarga del operador: RESTA de fecha - un número de dias;
		TCalendario operator-(int);
		// Modifica la fecha incrementándola en un dia (con postincremento);
		TCalendario operator++(int);
		// Modifica la fecha incrementándola en un dia (con preincremento);
		TCalendario& operator++();
		// Modifica la fecha decrementándola en un dia (con postdecremento);
		TCalendario operator--(int);
		// Modifica la fecha decrementándola en un día (con predecremento);
		TCalendario& operator--();
		// Modifica la fecha
		bool ModFecha(int, int, int);
		// Modifica el mensaje
		bool ModMensaje(char*);
		// Sobrecarga del operador igualdad;
		bool operator ==(const TCalendario&)const;
		// Sobrecarga del operador desigualdad;
		bool operator !=(const TCalendario&)const;

		// Sobrecarga del operador >; (ver ACLARACIÓN sobre ORDENACIÓN)
		bool operator>(const TCalendario&)const;
		// Sobrecarga del operador <; (ver ACLARACIÓN sobre ORDENACIÓN)
		bool operator<(const TCalendario&) const;
		//TCalendario vacío
		bool EsVacio();
		// Devuelve el día del calendario;
		int Dia();
		// Devuelve el mes del calendario;
		int Mes();
		// Devuelve el año del calendario;
		int Anyo();
		// Devuelve el mensaje del calendario;
		char* Mensaje() const;

		// Sobrecarga del operador salida
		friend ostream& operator<<(ostream&, const TCalendario&);


};