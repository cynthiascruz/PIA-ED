#include "Usuarios.h"

Usuario::Usuario() {} // Constructor para setters y getters
Usuario::~Usuario() {} // Destructor para liberar memoria
Usuario::Usuario(string nombreUsuario_) // Constructor: nos sirve para inicializar los atributos
{
	nombreUsuario = nombreUsuario_;
}

void Usuario::llenandoDatos(HWND hwnd) 
{
	HWND hnombreUsuario = GetDlgItem(hwnd, IDC_USERNAMEREGI);

	SetWindowText(hnombreUsuario, nombreUsuario.c_str());
}

void Usuario::mostrandoDatos(HWND hwnd) // Creo que esto no lo necesito
{
	
}

void Usuario::setnombreUsuario(string nombreUsuario_) // Set: Establecemos valores a los atributos
{
	nombreUsuario = nombreUsuario_;
}

string Usuario::getnombreUsuario() // Get: Mostramos valores de mis atributos
{
	return nombreUsuario;
}
