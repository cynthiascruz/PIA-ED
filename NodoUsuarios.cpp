#include"NodoUsuarios.h"

NodoUsuarios::NodoUsuarios(Usuario* usuario_) 
{
	usuario = usuario_;
	siguiente = nullptr;
	anterior = nullptr;
}