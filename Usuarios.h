#pragma once
#include<iostream>
#include<Windows.h>
#include<CommCtrl.h>
#include "Resource.h"
using namespace std;

class Usuario
{
private: // Atributos = características
	string nombreUsuario;
	

public: // Metodos

	Usuario(); // Constructor para setters y getters
	Usuario(string nombreUsuario_); // Constructor
	virtual ~Usuario(); // Destructor para liberar memoria
	

	virtual void llenandoDatos(HWND) = 0;
	virtual void mostrandoDatos(HWND) = 0;

// Get y set para un usuario

	void setnombreUsuario(string nombreUsuario_); // Set: Establecer valores de mis atributos
	string getnombreUsuario(); // Get: Mostrando valores de mis atributos}
	
};