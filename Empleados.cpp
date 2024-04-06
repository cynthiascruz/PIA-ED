#include "Empleados.h"

Empleado::Empleado(string nombreUsuario_, string nombre_, string apellidoM_, string apellidoP_, string contrasena_,
	string correo_, char genero_, int dia_, int mes_, int ano_) : Administrador(nombreUsuario_, nombre_, apellidoM_, apellidoP_, contrasena_)
{
	correo = correo_;
	genero = genero_;
	dia = dia_;
	mes = mes_;
	ano = ano_;
}

void Empleado::llenandoDatos(HWND hwnd)
{
	HWND hcomboGenero = GetDlgItem(hwnd, IDC_COMBOGENEREGIUSER);
	int iGenero = SendMessage(hcomboGenero, CB_GETCURSEL, 0, 0);

	if (iGenero != CB_ERR)
	{
		SendMessage(hcomboGenero, CB_GETLBTEXT, iGenero, (LPARAM)genero);
	}

	HWND hcorreo = GetDlgItem(hwnd, IDC_CORRREGIUSER);

	SYSTEMTIME fecha;
	fecha.wYear = ano;
	fecha.wMonth = mes;
	fecha.wDay = dia;
}

void Empleado::mostrandoDatos(HWND hwnd)
{
	


}

void Empleado::setCorreo(string correo_)
{
	correo = correo_;
}

string Empleado::getCorreo()
{
	return correo;
}

void Empleado::setGenero(char genero_)
{
	genero = genero_;
}

char Empleado::getGenero()
{
	return genero;
}

void Empleado::setFecha(tipofecha fecha, int tipofecha)
{
	switch (fecha)
	{
	case day:
		dia = fecha;
	case month:
		mes = fecha;
	case year:
		ano = fecha;
	}
}

int Empleado::getFecha(tipofecha fecha)
{
	switch (fecha)
	{
	case day:
		return dia;
		break;
	case month:
		return mes;
		break;
	case year:
		return ano;
		break;
	}
}