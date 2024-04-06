#pragma once
#include "NodoUsuarios.h"

enum roles {administrador, usuario, vuelo, pasajero};

class ListaUsuarios
{
private:
	NodoUsuarios* primero, * ultimo;
public:
	ListaUsuarios();

	void agregandoUsuario(Usuario* usuario);
	void mostrandolistaCompleta(HWND lista, roles roles_);

	NodoUsuarios* buscandoUsuario(string nombreUsuario);
	NodoUsuarios* buscandoVuelo(int numeroVuelo);
	// Set y Get

	NodoUsuarios* getPrimero();
};