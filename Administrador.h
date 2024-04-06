#pragma once
#include "Usuarios.h"

class Administrador : public Usuario
{
private:
	string nombre;
	string apellidoM;
	string apellidoP;
	string contrasena;

public:
	Administrador(); // Constructor para setters y getters
	Administrador(string nombre_, string apellidoM_, string apellidoP_, string nombreUsuario_, string contrasena_);

	void llenandoDatos(HWND)override;
	void mostrandoDatos(HWND)override;

	// Get y set

	void setNombre(string nombre_);
	string getNombre();

	void setapellidoM(string apellidoM_);
	string getapellidoM();

	void setapellidoP(string apellidoP_);
	string getapellidoP();

	void setContrasena(string contrasena);
	string getContrasena();
};