#include "Administrador.h"

Administrador::Administrador(){} // Constructor para setters y getters

Administrador::Administrador(string nombreUsuario_, string nombre_, string apellidoM_, string apellidoP_, string contrasena_) : Usuario (nombreUsuario_)
{
	nombre = nombre_;
	apellidoM = apellidoM_;
	apellidoP = apellidoP_;
	contrasena = contrasena_;
}

void Administrador::llenandoDatos(HWND hwnd)
{
	Usuario::llenandoDatos(hwnd);

	HWND hNombre = GetDlgItem(hwnd, IDC_NOMBRECOMRUSER);
	HWND hapellidoM = GetDlgItem(hwnd, IDC_APEMATERREGIUSER);
	HWND hapellidoP = GetDlgItem(hwnd, IDC_APEPATERREGIUSER);
	HWND hcorreo = GetDlgItem(hwnd, IDC_CORRREGIUSER);
	HWND hnombreUsuario = GetDlgItem(hwnd, IDC_USERNAMEREGI);
	HWND hcontrasena = GetDlgItem(hwnd, IDC_CONTRASENAREGUSER);
	HWND hcomboGenero = GetDlgItem(hwnd, IDC_COMBOGENEREGIUSER);

	// Modificar
	SetWindowText(hNombre, nombre.c_str());
	SetWindowText(hapellidoM, apellidoM.c_str());
	SetWindowText(hapellidoP, apellidoP.c_str());
	SetWindowText(hcontrasena, contrasena.c_str());

}

void Administrador::mostrandoDatos(HWND hwnd)
{

}

void Administrador::setNombre(string nombre_)
{
	nombre = nombre_;
}

string Administrador::getNombre()
{
	return nombre;
}

void Administrador::setapellidoM(string apellidoM_)
{
	apellidoM = apellidoM_;
}

string Administrador::getapellidoM()
{
	return apellidoM;
}

void Administrador::setapellidoP(string apellidoP_)
{
	apellidoP = apellidoP_;
}

string Administrador::getapellidoP()
{
	return apellidoP;
}

void Administrador::setContrasena(string contrasena_) // Set: Establecemos valores a los atributos
{
	contrasena = contrasena_;
}

string Administrador::getContrasena() // Get: Mostramos valores de mis atributos
{
	return contrasena;
}