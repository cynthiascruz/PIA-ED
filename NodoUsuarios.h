#pragma once
#include "Usuarios.h"
#include "Administrador.h"
#include "Empleados.h"
#include "Vuelos.h"


class NodoUsuarios
{
public:
	Usuario* usuario;
	NodoUsuarios* siguiente, * anterior;

	NodoUsuarios(Usuario* usuario_);
};