#include <Windows.h>
#include <CommCtrl.h>
#include <cstring>
#include "Resource.h"
#include "Vuelos.h"
#include "ListaUsuarios.h"

HINSTANCE hInstance;
ListaUsuarios listaAdministrador;
ListaUsuarios listaUsuario;
ListaUsuarios listaVuelo;
ListaUsuarios listaPasajero;

bool modificarNodo = true;
bool iniciarSesionComoUsuario = false;

NodoUsuarios* nodoAdministrador = nullptr;
NodoUsuarios* nodoAModificar = nullptr;
NodoUsuarios* nodoDeVuelo = nullptr;
NodoUsuarios* nodoDePasajero = nullptr;


LRESULT CALLBACK vInicioSesionGeneral(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK vInicioSesionAdministrador(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK vRegistroAdministrador(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK vMenuPrincipal(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK vRegistroVuelos(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK vAltaPasajeros(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK vRegistroUsuarios(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


enum tipoLogin {registro, inicioDeSesion};

void funcionalidadMenu(HWND hwnd, WPARAM wParam)
{
    switch (LOWORD(wParam))
    {
    case ID_MENUINICIO:
    {
        EndDialog(hwnd, 0);
        HWND hwndVInicio = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_VMENUPRINCIPAL), hwnd, vMenuPrincipal);
        ShowWindow(hwndVInicio, SW_SHOW);
    }
    break;
    case ID_REGISTRODEVUELOS:
    {
        EndDialog(hwnd, 0);
        HWND hwndVRegistroVuelo = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_VREGISTROVUELO), hwnd, vRegistroVuelos);
        ShowWindow(hwndVRegistroVuelo, SW_SHOW);
    }
    break;
    case ID_ALTAPASAJEROS:
    {
        EndDialog(hwnd, 0);
        HWND hwndVAltaPasajeros = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_VREGISTROPASAJERO), hwnd, vAltaPasajeros);
        ShowWindow(hwndVAltaPasajeros, SW_SHOW);
    }
    break;
    case ID_REGISTRODEEMPLEADOS:
    {
        EndDialog(hwnd, 0);
        HWND hwndVRegistroUsuario = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_VREGIUSERADMIN), hwnd, vRegistroUsuarios);
        ShowWindow(hwndVRegistroUsuario, SW_SHOW);
    }
    break;
    case ID_SALIR:
    {
        EndDialog(hwnd, 0);
        HWND hwndPrincipal = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_VINICIOSESIONGENERAL), hwnd, vInicioSesionGeneral);
        ShowWindow(hwndPrincipal, SW_SHOW);
    }
    break;
    }
}

// REVISAR ESTAS DOS 

void validarNombreContrasena(HWND hwnd, const char* nombre, const char* apellidoM, const char* apellidoP, const char* nombreUsuario, const char* contrasena, tipoLogin login) {

    // VALIDAR SI EL CAMPO DE USUARIO ESTÁ VACIO
    if (strlen(nombreUsuario) == 0) {
        MessageBox(hwnd, "Por favor, ingrese un nombre de usuario.", "Advertencia", MB_OK | MB_ICONWARNING);
        return; // Salir de la función si el nombre de usuario está vacío
    }

    // VALIDACIÓN POR SI EL CAMPO DE CONTRASEÑA ESTÁ VACIO
    if (strlen(contrasena) == 0) {
        MessageBox(hwnd, "Por favor, ingrese una contraseña.", "Advertencia", MB_OK | MB_ICONWARNING);
        return; // Salir de la función si la contraseña está vacía
    }

    // VALIDACIÓN PARA QUE EL NOMBRE DE USUARIO SOLO CONTENGA LETRAS
    for (int i = 0; nombreUsuario[i] != '\0'; i++) {
        if (!isalpha(nombreUsuario[i])) {
            MessageBox(hwnd, "El nombre de usuario solo puede contener letras.", "Advertencia", MB_OK | MB_ICONWARNING);
            return; // Salir de la función si se encuentra un carácter que no es una letra
        }
    }

    if (nodoAdministrador != nullptr)
    {
        Administrador* admin = dynamic_cast<Administrador*>(nodoAdministrador->usuario);
        admin->setnombreUsuario(nombreUsuario);
        admin->setContrasena(contrasena);
    }

    if (login == registro)
    {
        Usuario* tipoUsuario;
        tipoUsuario = new Administrador(nombreUsuario, nombre, apellidoM, apellidoP, contrasena);
        listaAdministrador.agregandoUsuario(tipoUsuario);

        MessageBox(NULL, "Administrador registrado correctamente.", "Registro exitoso", MB_OK | MB_ICONINFORMATION);
        EndDialog(hwnd, 0);
        HWND hwndPrincipal = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_VINICIOSESIONGENERAL), hwnd, vInicioSesionGeneral);
        ShowWindow(hwndPrincipal, SW_SHOW);
        return; 
    }

    NodoUsuarios* nodoSelecc = listaAdministrador.buscandoUsuario(nombreUsuario);

    if (nodoSelecc == nullptr) 
    {
        MessageBox(NULL, "Usuario no encontrado.", "Advertencia", MB_OK | MB_ICONWARNING);
    } 

    else 
    {
        if (login == inicioDeSesion)
        {
            nodoAdministrador = listaAdministrador.buscandoUsuario(nombreUsuario);
        
            if (nodoAdministrador != nullptr) // se encontró
            {
            EndDialog(hwnd, 0);
            HWND hwndVInicio = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_VMENUPRINCIPAL), hwnd, vMenuPrincipal);
            ShowWindow(hwndVInicio, SW_SHOW);
            }
        }
    }
}

LRESULT CALLBACK vInicioSesionGeneral(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {

    // BOTÓN INGRESAR DE LA VENTANA DE INICIO SESIÓN GENERAL
        case IDC_BOTONINGGENERAL: 
        {
            char buscandoUsuario[MAX_PATH];
            HWND hnombreUsuario = GetDlgItem(hwnd, IDC_USERNAMEG);
            GetWindowText(hnombreUsuario, buscandoUsuario, MAX_PATH);
            nodoAModificar = listaUsuario.buscandoUsuario(buscandoUsuario);

            if(nodoAModificar == nullptr)
            {
                MessageBox(NULL, "No se encontró al usuario", "Advertencia", MB_OK | MB_ICONWARNING);
            }
            else
            {
                EndDialog(hwnd, 0);
                iniciarSesionComoUsuario = true;
                HWND hwndVInicio = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_VMENUPRINCIPAL), hwnd, vMenuPrincipal);
                ShowWindow(hwndVInicio, SW_SHOW);
            }
        }
        break;
    // BOTÓN INGRESAR AL INICIO DE SESIÓN DEL PANEL DE ADMINISTRADOR
        case IDC_BOTONPANELADMIN: 
        {
            EndDialog(hwnd, 0);
            HWND hwndPrincipal = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_VINICIOSESIONPA), NULL, vInicioSesionAdministrador);
            ShowWindow(hwndPrincipal, SW_SHOW);
            break;
        }

        case IDC_REGISTRARADMIN: 
        {
            EndDialog(hwnd, 0);
            HWND hwndPrincipal = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_VREGISTROADMIN), NULL, vRegistroAdministrador);
            ShowWindow(hwndPrincipal, SW_SHOW);
            break;
        }
        }
        break;

    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;

    default:
        return (INT_PTR)FALSE; // SI QUITO ESTO, SE BLOQUEAN LOS MENSAJES EMERGENTES
    }
    return 0;
}

LRESULT CALLBACK vInicioSesionAdministrador(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {

            // BOTÓN INGRESAR DE LA VENTANA DE INICIO SESIÓN ADMINISTRADOR
        case IDC_INGRESARADMIN:
        {

            HWND hnombreUsuario = GetDlgItem(hwnd, IDC_USERNAMEAD);
            HWND hcontrasena = GetDlgItem(hwnd, IDC_PASSWORDAD);

            int inombreUsuario = GetWindowTextLength(hnombreUsuario);
            int iContrasena = GetWindowTextLength(hcontrasena);

            char nombreUsuario[50], contrasena[50];
            
            GetWindowText(hnombreUsuario, nombreUsuario, inombreUsuario + 1);
            GetWindowText(hcontrasena, contrasena, iContrasena + 1);


            validarNombreContrasena(hwnd, "", "","", nombreUsuario,  contrasena, inicioDeSesion);
           
            break;
        }

        // BOTÓN VOLVER AL INICIO DE SESIÓN GENERAL
        case IDC_VOLVERADMIN:
        {
            EndDialog(hwnd, 0);
            HWND hwndPrincipal = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_VINICIOSESIONGENERAL), hwnd, vInicioSesionGeneral);
            ShowWindow(hwndPrincipal, SW_SHOW);
            break;
        }
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;
    
    default:
        return (INT_PTR)FALSE; // SI QUITO ESTO, SE BLOQUEAN LOS MENSAJES EMERGENTES
    }
    return 0;
}

LRESULT CALLBACK vMenuPrincipal(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    
    case WM_INITDIALOG:
    {
        NodoUsuarios* usuarioActual;

        if (nodoAdministrador != nullptr)
        {
            usuarioActual = nodoAdministrador;
        }
        else
        {
            usuarioActual = nodoAModificar;
        }

        HWND hnombreUsuario = GetDlgItem(hwnd, IDC_STATICNOMUSERAGENDA);
        SetWindowText(hnombreUsuario, usuarioActual->usuario->getnombreUsuario().c_str());

        HWND hlistaVuelos = GetDlgItem(hwnd, IDC_LISTAVUELOS);

        if (listaVuelo.getPrimero() == nullptr)
        {
            SendMessage(hlistaVuelos, LB_ADDSTRING, NULL, (LPARAM)"No se han registado vuelos");
        }
        else
        {
            listaVuelo.mostrandolistaCompleta(hlistaVuelos, vuelo);
        }
    }break;
    case WM_COMMAND:
        funcionalidadMenu(hwnd, wParam);
        switch (LOWORD(wParam))
        {

        }break;

    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;


    default:
        return (INT_PTR)FALSE; // SI QUITO ESTO, SE BLOQUEAN LOS MENSAJES EMERGENTES
    }
    return 0;
}

LRESULT CALLBACK vRegistroVuelos(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int asientosExpress = 50;
    static int asientosExpressPlus = 80;
    static int asientosExpressExclusive = 120;

    switch (msg) {
    case WM_INITDIALOG:
    {
        // Obtener el handle del combo box de origen y llenarlo
        HWND hComboOrigen = GetDlgItem(hwnd, IDC_COMBOORIGEN);
        SendMessage(hComboOrigen, CB_ADDSTRING, 0, (LPARAM)" ");
        SendMessage(hComboOrigen, CB_ADDSTRING, 0, (LPARAM)"México");
        SendMessage(hComboOrigen, CB_ADDSTRING, 0, (LPARAM)"Canadá");
        SendMessage(hComboOrigen, CB_ADDSTRING, 0, (LPARAM)"Madrid");
        SendMessage(hComboOrigen, CB_ADDSTRING, 0, (LPARAM)"Colombia");
        SendMessage(hComboOrigen, CB_ADDSTRING, 0, (LPARAM)"Argentina");

        // Obtener el handle del combo box de destino y llenarlo
        HWND hComboDestino = GetDlgItem(hwnd, IDC_COMBODESTINO);
        SendMessage(hComboDestino, CB_ADDSTRING, 0, (LPARAM)" ");
        SendMessage(hComboDestino, CB_ADDSTRING, 0, (LPARAM)"México");
        SendMessage(hComboDestino, CB_ADDSTRING, 0, (LPARAM)"Canadá");
        SendMessage(hComboDestino, CB_ADDSTRING, 0, (LPARAM)"Madrid");
        SendMessage(hComboDestino, CB_ADDSTRING, 0, (LPARAM)"Colombia");
        SendMessage(hComboDestino, CB_ADDSTRING, 0, (LPARAM)"Argentina");
       
        // Obtener el handle del combo box del tipo de avión y llenarlo
        HWND hTipoAvion = GetDlgItem(hwnd, IDC_COMBOTIPOAVION);
        SendMessage(hTipoAvion, CB_ADDSTRING, 0, (LPARAM)" ");
        SendMessage(hTipoAvion, CB_ADDSTRING, 0, (LPARAM)"Express");
        SendMessage(hTipoAvion, CB_ADDSTRING, 0, (LPARAM)"Express Plus");
        SendMessage(hTipoAvion, CB_ADDSTRING, 0, (LPARAM)"Express Exclusive");

        // Obtener el handle del combo box del estatus de vuelo y llenarlo
        HWND hComboEstatusVuelo = GetDlgItem(hwnd, IDC_COMBOESTATUSVUELO);
        SendMessage(hComboEstatusVuelo, CB_ADDSTRING, 0, (LPARAM)" ");
        SendMessage(hComboEstatusVuelo, CB_ADDSTRING, 0, (LPARAM)"Programado");
        SendMessage(hComboEstatusVuelo, CB_ADDSTRING, 0, (LPARAM)"Efectuado");
        SendMessage(hComboEstatusVuelo, CB_ADDSTRING, 0, (LPARAM)"Cancelado");
        
    }break;
    case WM_COMMAND:
        funcionalidadMenu(hwnd, wParam);        
        switch (LOWORD(wParam))
        {

            char asientosTurista[5], asientosEjecutiva[5];

        case IDC_COMBOTIPOAVION:
            if (HIWORD(wParam) == CBN_SELCHANGE) // VERIFICACIÓN CAMBIANDO EL TIPO DE AVIÓN
            {
                HWND hTipoAvion = GetDlgItem(hwnd, IDC_COMBOTIPOAVION);
                char ctipoAvion[30];

                char dispTurista[5], dispEjecutiva[5];

                int iTipoAvion = SendMessage(hTipoAvion, CB_GETCURSEL, 0, 0);

                SendMessage(hTipoAvion, CB_GETLBTEXT, iTipoAvion, (LPARAM)ctipoAvion); // guarda lo seleccionado en un char}

                if (nodoDeVuelo != nullptr) // Hay un vuelo ya registrado
                {

                    Vuelos* infoVuelo = dynamic_cast<Vuelos*>(nodoDeVuelo->usuario);
                    char numTurista[5], numEjecutivo[5];

                    _itoa(infoVuelo->getasientosTurista(), numTurista, 10);
                    _itoa(infoVuelo->getasientosEjecutiva(), numEjecutivo, 10);

                    strcpy(dispTurista, numTurista);
                    strcpy(dispEjecutiva, numEjecutivo);
                }
                else 
                {
                    if (strcmp(ctipoAvion, "Express") == 0)
                    {
                        strcpy(dispTurista, "30");
                        strcpy(dispTurista, "20");
                    }
                    if (strcmp(ctipoAvion, "Express Plus") == 0)
                    {
                        strcpy(dispTurista, "50");
                        strcpy(dispTurista, "30");
                    }
                    if (strcmp(ctipoAvion, "Express Exclusive") == 0)
                    {
                        strcpy(dispTurista, "80");
                        strcpy(dispTurista, "40");
                    }
                }
                strcpy(asientosTurista, dispTurista);
                strcpy(asientosEjecutiva, dispEjecutiva);

                HWND hstaticTurista = GetDlgItem(hwnd, IDC_STATICTURISTA);
                HWND hstaticEjecutiva = GetDlgItem(hwnd, IDC_STATICEJECUTIVA);

                SetWindowText(hstaticTurista, asientosTurista);
                SetWindowText(hstaticEjecutiva, asientosEjecutiva);
            }
            break;

        case IDC_BOTONREGISTRARVUELO:
        {
        // COMBOBOX
            HWND hcomboOrigen= GetDlgItem(hwnd, IDC_COMBOORIGEN);
            HWND hcomboDestino = GetDlgItem(hwnd, IDC_COMBODESTINO);
            HWND hcomboTipoAvion = GetDlgItem(hwnd, IDC_COMBOTIPOAVION);
            HWND hcomboEstatusVuelo = GetDlgItem(hwnd, IDC_COMBOESTATUSVUELO);

            int iOrigen = SendMessage(hcomboOrigen, CB_GETCURSEL, 0, 0);
            int iDestino = SendMessage(hcomboDestino, CB_GETCURSEL, 0, 0);
            int iTipoAvion = SendMessage(hcomboTipoAvion, CB_GETCURSEL, 0, 0);
            int iEstatusVuelo = SendMessage(hcomboEstatusVuelo, CB_GETCURSEL, 0, 0);

            origenvuelo origen;
            switch (iOrigen)
            {
            case 0:
                origen = mexico;
                break;
            case 1:
                origen = canada;
                break;
            case 2:
                origen = madrid;
                break;
            case 3:
                origen = colombia;
                break;
            case 4:
                origen = argentina;
            }

            destinovuelo destino;
            switch (iDestino)
            {
            case 0:
                destino = mexico_;
                break;
            case 1:
                destino = canada_;
                break;
            case 2:
                destino = madrid_;
                break;
            case 3:
                destino = colombia_;
                break;
            case 4:
                destino = argentina_;
            }

            tipodeavion avion;
            switch (iTipoAvion)
            {
            case 0: 
                avion = express;
                break;
            case 1:
                avion = expressplus;
                break;
            case 2:
                avion = expressexclusive;
                break;
            }

            estatusdevuelo tipoEstatus;
            switch (iEstatusVuelo)
            {
            case 0:
                tipoEstatus = cancelado;
                break;
            case 1:
                tipoEstatus = pendiente;
                break;
            case 2:
                tipoEstatus = programado;
                break;
            }

        // PRECIOS EDITS CONTROLS
            char precioTurista[30], precioEjecutiva[30];

            HWND hprecioTurista = GetDlgItem(hwnd, IDC_EDITPRECIOEJE);
            HWND hprecioEjecutiva = GetDlgItem(hwnd, IDC_EDITPRECIOTURI);

            int iprecioTurista = GetWindowTextLength(hprecioTurista);
            int iprecioEjecutiva = GetWindowTextLength(hprecioEjecutiva);

            GetWindowText(hprecioTurista, precioTurista, iprecioTurista + 1);
            GetWindowText(hprecioEjecutiva, precioEjecutiva, iprecioEjecutiva + 1);

        // FECHA Y HORA

            int fecha;
            int hora;

            SYSTEMTIME fechaSelecc, horaSelecc;

            fecha = SendDlgItemMessage(hwnd, IDC_FECHAVUELO, DTM_GETSYSTEMTIME, (WPARAM)GDT_VALID, (LPARAM)&fechaSelecc);
            hora = SendDlgItemMessage(hwnd, IDC_HORAVUELO, DTM_GETSYSTEMTIME, (WPARAM)GDT_VALID, (LPARAM)&horaSelecc);

        // VALIDACIONES PARA EL TIPO DE AVION Y DESTINOS

            if(iOrigen==0 || iDestino==0 || iOrigen==iDestino)
            {
                MessageBox(hwnd,"Seleccione un origen y un destino validos.","Error.", MB_OK | MB_ICONERROR);
                break;
            }

            if ((iOrigen == 0 && iDestino != 0) || (iOrigen != 0 && iDestino == 0))
            {
                MessageBox(hwnd, "Seleccione tanto un origen como un destino válidos.", "Error.", MB_OK | MB_ICONERROR);
                break;
            }

            if (iTipoAvion == 0)
            {
                MessageBox(hwnd, "Seleccione un tipo de avión.", "Error.", MB_OK | MB_ICONERROR);
                break;
            }


        // VALIDACIONES PARA PRECIOS, NUMEROS ENTEROS Y NO ESPACIOS EN BLANCO

            bool preciosValidos = true;

            for (int i = 0; precioEjecutiva[i] != '\0'; ++i) {
                if (!isdigit(precioEjecutiva[i])) {
                    preciosValidos = false;
                    break;
                }
            }

            for (int i = 0; precioTurista[i] != '\0'; ++i) {
                if (!isdigit(precioTurista[i])) {
                    preciosValidos = false;
                    break;
                }
            }
            
            if (strlen(precioEjecutiva) == 0 || strlen(precioTurista) == 0) {
                MessageBox(hwnd, "Por favor, ingrese ambos precios.", "Error.", MB_OK | MB_ICONERROR);
                break;
            }

            if (!preciosValidos) 
            {
                MessageBox(hwnd, "Ingrese el precio en formato de número entero.", "Error.", MB_OK | MB_ICONERROR);
                break;
            }
            else // GUARDAMOS VUELO OMG YEA
            {
                int claseTurista = atoi(precioTurista);
                int claseEjecutiva = atoi(precioEjecutiva);
                int cAsientosTurista = atoi(asientosTurista);
                int cAsientosEjecutiva = atoi(asientosEjecutiva);

                if (nodoDeVuelo == nullptr) // Si no modificamos el nodo, quiere decir que estamos creando uno
                {
                    Usuario* vuelo;
                    NodoUsuarios* usuarioActual;

                    if (nodoAdministrador != nullptr)
                    {
                        usuarioActual = nodoAdministrador;
                    }
                    else
                    {
                        usuarioActual = nodoAModificar;
                    }

                    vuelo = new Vuelos(usuarioActual->usuario->getnombreUsuario(), origen, destino, claseTurista, claseEjecutiva, fechaSelecc.wDay,
                        fechaSelecc.wMonth, fechaSelecc.wYear, avion, pendiente);

                    Vuelos* getVuelo = dynamic_cast<Vuelos*>(vuelo);
                    getVuelo->setasientosTurista(cAsientosTurista);
                    getVuelo->setasientosEjecutiva(cAsientosEjecutiva);

                    listaVuelo.agregandoUsuario(vuelo);


                    NodoUsuarios* nodoSeleccionadoDeVuelo = listaVuelo.buscandoVuelo(getVuelo->getnumeroVuelo()); // Verificando que el vuelo se haya agregado correctamente

                    if (nodoSeleccionadoDeVuelo != nullptr)
                        getVuelo->mostrandoDatos(hwnd);
                }
                else
                {
                    nodoDeVuelo->usuario->setnombreUsuario(nodoDeVuelo->usuario->getnombreUsuario());

                    Vuelos* vuelo = dynamic_cast<Vuelos*>(nodoDeVuelo->usuario);
                    vuelo->setOrigen(origen);
                    vuelo->setDestino(destino);
                    vuelo->setprecioTurista(claseTurista);
                    vuelo->setprecioEjecutivo(claseEjecutiva);
                    vuelo->setasientosTurista(cAsientosTurista);
                    vuelo->setasientosEjecutiva(cAsientosEjecutiva);
                    vuelo->setFecha(day, fechaSelecc.wDay);
                    vuelo->setFecha(day, fechaSelecc.wMonth);
                    vuelo->setFecha(day, fechaSelecc.wYear);
                    // pendiente cambiar hora
                    vuelo->settipoAvion(avion);
                    vuelo->setEstatus(tipoEstatus);
                }
            }
        }
        break;
    } 
    break;
    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;

    default:
        return (INT_PTR)FALSE;
    }
    return 0;
}

LRESULT CALLBACK vAltaPasajeros(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg) {
    case WM_INITDIALOG:
    {
        // Obtener el handle del combo box de origen y llenarlo
        HWND hwndComboPasajeros = GetDlgItem(hwnd, IDC_COMBOGENEROPASA);
        SendMessage(hwndComboPasajeros, CB_ADDSTRING, 0, (LPARAM)" ");
        SendMessage(hwndComboPasajeros, CB_ADDSTRING, 0, (LPARAM)"Femenino");
        SendMessage(hwndComboPasajeros, CB_ADDSTRING, 0, (LPARAM)"Masculino");
        break;
    }
    case WM_COMMAND:
        funcionalidadMenu(hwnd, wParam);
        break;

    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;

    

    default:
        return (INT_PTR)FALSE; // SI QUITO ESTO, SE BLOQUEAN LOS MENSAJES EMERGENTES
    }
    return 0;
}

LRESULT CALLBACK vRegistroAdministrador(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {

        case IDC_BOTONREGISTRARAD:
        {
            char nombreUsuario[50], contrasena[50];

            HWND hnombreUsuario = GetDlgItem(hwnd, IDC_USERNAMEREGA);
            HWND hcontrasena = GetDlgItem(hwnd, IDC_PASSWORDREGAD);

            int inombreUsuario = GetWindowTextLength(hnombreUsuario);
            int icontrasena = GetWindowTextLength(hcontrasena);

            GetWindowText(hnombreUsuario, nombreUsuario, inombreUsuario + 1);
            GetWindowText(hcontrasena, contrasena, icontrasena + 1);

            if (inombreUsuario < 1 || icontrasena < 1)
            {
                MessageBox(NULL, "Debe rellenar todos los campos", "Advertencia", MB_OK | MB_ICONWARNING);
                break;
            }
            else
            {
                validarNombreContrasena(hwnd, "", "", "", nombreUsuario, contrasena, registro);
            }

        }break;
        case IDC_VOLVERADMINREG:
        {
            EndDialog(hwnd, 0);
            HWND hwndPrincipal = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_VINICIOSESIONGENERAL), hwnd, vInicioSesionGeneral);
            ShowWindow(hwndPrincipal, SW_SHOW);
            break;
        }
        }
    break;

    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;

    default:
        return (INT_PTR)FALSE; // SI QUITO ESTO, SE BLOQUEAN LOS MENSAJES EMERGENTES
    }
return 0;
}

LRESULT CALLBACK vRegistroUsuarios(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg) {
    case WM_INITDIALOG:
    {
        HWND hcomboGenero = GetDlgItem(hwnd, IDC_COMBOGENEREGIUSER);

        SendMessage(hcomboGenero, CB_ADDSTRING, 0, (LPARAM)" ");
        SendMessage(hcomboGenero, CB_ADDSTRING, 0, (LPARAM)"Masculino");
        SendMessage(hcomboGenero, CB_ADDSTRING, 0, (LPARAM)"Femenino");
    }
    break;
    case WM_COMMAND:
        funcionalidadMenu(hwnd, wParam);
        switch (LOWORD(wParam))
        {
        case IDC_REGISTRARUSUARIO:
        {
            char nombre[50], apellidoM[50], apellidoP[50], nombreusuario[50], correo[50], contrasena[50], genero[50];
            

            HWND hNombre = GetDlgItem(hwnd, IDC_NOMBRECOMRUSER);
            HWND hapellidoM = GetDlgItem(hwnd, IDC_APEMATERREGIUSER);
            HWND hapellidoP = GetDlgItem(hwnd, IDC_APEPATERREGIUSER);
            HWND hcorreo = GetDlgItem(hwnd, IDC_CORRREGIUSER);
            HWND hnombreUsuario = GetDlgItem(hwnd, IDC_USERNAMEREGI);
            HWND hcontrasena = GetDlgItem(hwnd, IDC_CONTRASENAREGUSER);
            HWND hcomboGenero = GetDlgItem(hwnd, IDC_COMBOGENEREGIUSER);

            int iNombre = GetWindowTextLength(hNombre);
            int iApellidoM = GetWindowTextLength(hapellidoM);
            int iApellidoP = GetWindowTextLength(hapellidoP);
            int iCorreo = GetWindowTextLength(hcorreo);
            int iNombreUsuario = GetWindowTextLength(hnombreUsuario);
            int iContrasena = GetWindowTextLength(hcontrasena);
            int iGenero = SendMessage(hcomboGenero, CB_GETCURSEL, 0, 0);

            GetWindowText(hNombre, nombre, iNombre + 1);
            GetWindowText(hapellidoM, apellidoM, iApellidoM + 1);
            GetWindowText(hapellidoP, apellidoP, iApellidoP + 1);
            GetWindowText(hnombreUsuario, nombreusuario, iNombreUsuario + 1);
            GetWindowText(hcorreo, correo, iCorreo + 1);
            GetWindowText(hcontrasena, contrasena, iContrasena + 1);


            if (iGenero != CB_ERR)
            {
                SendMessage(hcomboGenero, CB_GETLBTEXT, iGenero, (LPARAM)genero);
            }

            SYSTEMTIME fechaSeleccionada;
            int fecha;

            fecha = SendMessage(GetDlgItem(hwnd, IDC_FECHANACIREGIUSER), DTM_GETSYSTEMTIME, 0, (LPARAM)&fechaSeleccionada);

            if (iNombre < 1 || iApellidoM < 1 || iApellidoP < 1 || iNombreUsuario < 1 || iContrasena < 1 || iGenero == CB_ERR || genero[0] == '\0')
            {
                MessageBox(NULL, "Debe de rellenar todos los campos.", "Advertencia", MB_OK | MB_ICONWARNING);
            }
            else
            {
                char cGenero;
                if (strcmp(genero, "Masculino") == 0)
                {
                    cGenero = 'M';
                }
                else
                {
                    cGenero = 'F';
                }

                if (nodoAModificar == nullptr)
                {
                    Usuario* empleado;
                    empleado = new Empleado(nombreusuario, nombre, apellidoM, apellidoP, contrasena, correo,cGenero, fechaSeleccionada.wDay, fechaSeleccionada.wMonth, fechaSeleccionada.wYear);
                    listaUsuario.agregandoUsuario(empleado);
                }
                else
                {
                    nodoAModificar->usuario->setnombreUsuario(nombreusuario);
                    

                    Empleado* empleado=dynamic_cast<Empleado*>(nodoAModificar->usuario);
                    empleado->setNombre(nombre);
                    empleado->setapellidoM(apellidoM);
                    empleado->setapellidoP(apellidoP);
                    empleado->setnombreUsuario(nombreusuario);
                    empleado->setContrasena(contrasena);
                    empleado->setCorreo(correo);
                    empleado->setGenero(cGenero);
                    empleado->setFecha(day, fechaSeleccionada.wDay);
                    empleado->setFecha(month, fechaSeleccionada.wMonth);
                    empleado->setFecha(year, fechaSeleccionada.wYear);
                }

                NodoUsuarios* nodoSelecc = listaUsuario.buscandoUsuario(nombreusuario);

                if (nodoSelecc == nullptr)
                {
                    MessageBox(NULL, "No encontrado", "Advertencia", MB_OK | MB_ICONWARNING);
                }
                else
                {
                    
                }
            }

        }   
        }
        break;

    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;

    default:
        return (INT_PTR)FALSE; // SI QUITO ESTO, SE BLOQUEAN LOS MENSAJES EMERGENTES
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmdLine, int cShow)
{

    HWND hwndPrincipal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_VINICIOSESIONGENERAL), NULL, vInicioSesionGeneral);
    ShowWindow(hwndPrincipal, cShow);

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

