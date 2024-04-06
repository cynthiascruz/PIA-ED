#include "Vuelos.h"
#include "ListaUsuarios.h"

int Vuelos::generarNumeroDeVuelo = 1000;
Vuelos::Vuelos(string nombreUsuario_, origenvuelo origen_, destinovuelo destino_, int precioTurista_, int precioEjecutivo_, int dia_, int mes_, int ano_, tipodeavion tipoAvion_, estatusdevuelo tipoEstatus_) : Usuario(nombreUsuario_)
{
	origen = origen_;
	destino = destino_;
	precioTurista = precioTurista_;
	precioEjecutiva = precioEjecutivo_;
	dia = dia_;
	mes = mes_;
	ano = ano_;
	tipoAvion = tipoAvion_;
	tipoEstatus = tipoEstatus_;
	generarNumeroDeVuelo++;
	numeroVuelo = generarNumeroDeVuelo;
	listaDePasajerosXVuelo = new ListaUsuarios();
}

void Vuelos::mostrandoDatos(HWND hwnd)
{
	MessageBox(NULL, "Vuelo agendado", "Registro exitoso", MB_OK);
}

void Vuelos::llenandoDatos(HWND hwnd)
{
	HWND hcomboOrigen = GetDlgItem(hwnd, IDC_COMBOORIGEN);
	HWND hcomboDestino = GetDlgItem(hwnd, IDC_COMBODESTINO);
	HWND hcomboTipoAvion = GetDlgItem(hwnd, IDC_COMBOTIPOAVION);
	HWND hcomboEstatusVuelo = GetDlgItem(hwnd, IDC_COMBOESTATUSVUELO);
	HWND hstaticTurista = GetDlgItem(hwnd, IDC_STATICTURISTA);
	HWND hstaticEjecutiva = GetDlgItem(hwnd, IDC_STATICEJECUTIVA);
	HWND hprecioTurista = GetDlgItem(hwnd, IDC_EDITPRECIOEJE);
	HWND hprecioEjecutiva = GetDlgItem(hwnd, IDC_EDITPRECIOTURI);
	HWND hnumeroVuelo = GetDlgItem(hwnd, IDC_STATICNUMVUELO);

	char cantidadTurista[10], cantidadEjecutiva[10], costoTurista[10], costoEjecutivo[10], numVuelo[10];

	_itoa_s(asientosTurista, cantidadTurista, 10);
	_itoa_s(asientosEjecutiva, cantidadEjecutiva, 10);
	_itoa_s(precioTurista, costoTurista, 10);
	_itoa_s(precioEjecutiva, costoEjecutivo, 10);
	_itoa_s(numeroVuelo, numVuelo, 10);

	
	SetWindowText(hstaticTurista, cantidadTurista);
	SetWindowText(hstaticEjecutiva, cantidadEjecutiva);
	SetWindowText(hprecioTurista, costoTurista);
	SetWindowText(hprecioEjecutiva, costoEjecutivo);
	SetWindowText(hnumeroVuelo, numVuelo);

	SendMessage(hcomboOrigen, CB_SETCURSEL, (WPARAM)origen, NULL);
	SendMessage(hcomboDestino, CB_SETCURSEL, (WPARAM)destino, NULL);
	SendMessage(hcomboTipoAvion, CB_SETCURSEL, (WPARAM)tipoAvion, NULL);
	SendMessage(hcomboEstatusVuelo, CB_SETCURSEL, (WPARAM)tipoEstatus, NULL);
}

void Vuelos::setOrigen(origenvuelo origen_)
{
	origen = origen_;
}
origenvuelo Vuelos::getOrigen()
{
	return origen;
}

void Vuelos::setDestino(destinovuelo destino_)
{
	destino = destino_;
}
destinovuelo Vuelos::getDestino()
{
	return destino;
}

void Vuelos::setprecioTurista(int precioTurista_)
{
	precioTurista = precioTurista_;
}
int Vuelos::getprecioTurista()
{
	return precioTurista;
}

void Vuelos::setprecioEjecutivo(int precioEjecutivo_)
{
	precioEjecutiva = precioEjecutivo_;
}
int Vuelos::getprecioEjecutivo()
{
	return precioEjecutiva;
}

void Vuelos::settipoAvion(tipodeavion tipoAvion_)
{
	tipoAvion = tipoAvion_;
}
tipodeavion Vuelos::getipoAvion()
{
	return tipoAvion;
}

void Vuelos::setEstatus(estatusdevuelo tipoEstatus_)
{
	tipoEstatus = tipoEstatus_;
}
estatusdevuelo Vuelos::getEstatus()
{
	return tipoEstatus;
}

void Vuelos::setasientosTurista(int asientosTurista_)
{
	asientosTurista = asientosTurista_;
}
int Vuelos::getasientosTurista()
{
	return asientosTurista;
}

void Vuelos::setasientosEjecutiva(int asientosEjecutiva_)
{
	asientosEjecutiva = asientosEjecutiva_;
}
int Vuelos::getasientosEjecutiva()
{
	return asientosEjecutiva;
}

void Vuelos::setnumeroVuelo(int numeroVuelo_)
{
	numeroVuelo = numeroVuelo_;
}
int Vuelos::getnumeroVuelo()
{
	return numeroVuelo;
}

void Vuelos::setFecha(tipofecha tipoFecha, int fecha)
{
	switch (tipoFecha)
	{
	case day: 
		dia = fecha;
		break;
	case month: 
		mes = fecha;
		break;
	case year: 
		ano = fecha;
		break;
	}
}
int Vuelos::getFecha(tipofecha tipoFecha)
{
	switch (tipoFecha)
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

ListaUsuarios* Vuelos::getlistapasajerosdevuelo()
{
	return listaDePasajerosXVuelo;
}