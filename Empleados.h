#pragma once
#include "Administrador.h"

enum tipofecha { day, month, year};

class Empleado : public Administrador
{
private:
	string correo;
	char genero;
	int dia;
	int mes;
	int ano;

public:
	Empleado(string nombreUsuario_, string nombre_, string apellidoM_, string apellidoP_, string contrasena_, string correo_, char genero_,
		int dia_, int mes_, int ano_);

	void llenandoDatos(HWND) override;
	void mostrandoDatos(HWND) override;

	// Get y set

	void setCorreo(string correo_);
	string getCorreo();

	void setGenero(char genero_);
	char getGenero();

	void setFecha(tipofecha fecha, int tipofecha);
	int getFecha(tipofecha fecha);
};