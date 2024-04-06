#include "ListaUsuarios.h"

ListaUsuarios::ListaUsuarios()
{
    primero = nullptr;
    ultimo = nullptr;
}

void ListaUsuarios::agregandoUsuario(Usuario* usuario_)
{
    NodoUsuarios* nuevoUsuario = new NodoUsuarios(usuario_);
    if (primero == nullptr)
    {
        primero = nuevoUsuario;
        ultimo = nuevoUsuario;
    }
    else
    {
        ultimo->siguiente = nuevoUsuario;
        nuevoUsuario->anterior = ultimo;
        ultimo = nuevoUsuario;
    }
}

NodoUsuarios* ListaUsuarios::buscandoUsuario(string nombreUsuario)
{
    NodoUsuarios* aux = primero;
    while (aux != nullptr)
    {
        if (aux->usuario->getnombreUsuario() == nombreUsuario)
            return aux;
        aux = aux->siguiente;
    }
    return nullptr;
}

void ListaUsuarios::mostrandolistaCompleta(HWND lista, roles roles_)
{
    NodoUsuarios* aux = primero;
    char cadena[80];

    while (aux != nullptr)
    {
        switch (roles_)
        {
            case administrador:
                strcpy(cadena, aux->usuario->getnombreUsuario().c_str());
                break;
            case usuario:
                strcpy(cadena, aux->usuario->getnombreUsuario().c_str());
                break;
            case vuelo: 
            {
                Vuelos* vuelo = dynamic_cast<Vuelos*>(aux->usuario);

                // Utiliza las enumeraciones directamente
                switch (vuelo->getOrigen()) 
                {
                case mexico:
                    strcpy(cadena, "Mexico");
                    break;
                case canada:
                    strcpy(cadena, "Canada");
                    break;
                case madrid:
                    strcpy(cadena, "Madrid");
                    break;
                case colombia:
                    strcpy(cadena, "Colombia");
                    break;
                case argentina:
                    strcpy(cadena, "Argentina");
                    break;
                }
                strcat(cadena, " - ");

                switch (vuelo->getDestino()) 
                {
                case mexico_:
                    strcat(cadena, "Mexico");
                    break;
                case canada_:
                    strcat(cadena, "Canada");
                    break;
                case madrid_:
                    strcat(cadena, "Madrid");
                    break;
                case colombia_:
                    strcat(cadena, "Colombia");
                    break;
                case argentina_:
                    strcat(cadena, "Argentina");
                    break;
                }
                // Convertir el número de vuelo a cadena y agregarlo a la cadena
                char numVuelo[10];
                _itoa(vuelo->getnumeroVuelo(), numVuelo, 10);
                strcat(cadena, numVuelo);
            }
            break;
        }       
    }
}

NodoUsuarios* ListaUsuarios::buscandoVuelo(int numeroVuelo)
{
    NodoUsuarios* aux = primero;
    while (aux != nullptr)
    {
        Vuelos* vuelo = dynamic_cast<Vuelos*>(aux->usuario);
        if (vuelo->getnumeroVuelo() == numeroVuelo)
            return aux;
        aux = aux->siguiente;
    }
    return nullptr;
}

NodoUsuarios* ListaUsuarios::getPrimero()
{
    return primero;
}
