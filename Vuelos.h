#pragma once
#include "Empleados.h"


class ListaUsuarios;

enum origenvuelo { mexico, canada, madrid, colombia, argentina};
enum destinovuelo { mexico_, canada_, madrid_, colombia_, argentina_};
enum tipodeavion {express, expressplus, expressexclusive};
enum estatusdevuelo {cancelado, pendiente, programado};

class Vuelos : public Usuario
{
private:
	origenvuelo origen;
	destinovuelo destino;
	int precioTurista;
	int precioEjecutiva;
	int dia;
	int mes;
	int ano;
	int asientosTurista;
	int asientosEjecutiva;
	static int generarNumeroDeVuelo;
	int numeroVuelo;
	tipodeavion tipoAvion;
	estatusdevuelo tipoEstatus;

	ListaUsuarios* listaDePasajerosXVuelo;

public:																																	
	Vuelos(string nombreUsuario_, origenvuelo origen_, destinovuelo destino_, int precioTurista_, int precioEjecutivo_, int dia_, int mes_, int ano_, tipodeavion tipoAvion_, estatusdevuelo tipoEstatus_);

	void mostrandoDatos(HWND) override;
	void llenandoDatos(HWND) override;

	void setOrigen(origenvuelo origen_);
	origenvuelo getOrigen();

	void setDestino(destinovuelo destino_);
	destinovuelo getDestino();

	void setprecioTurista(int precioTurista_);
	int getprecioTurista();

	void setprecioEjecutivo(int precioEjecutivo);
	int getprecioEjecutivo();

	void settipoAvion(tipodeavion tipoAvion_);
	tipodeavion getipoAvion();

	void setEstatus(estatusdevuelo tipoEstatus_);
	estatusdevuelo getEstatus();

	void setasientosTurista(int asientosTurista_);
	int getasientosTurista();

	void setasientosEjecutiva(int asientosEjecutiva_);
	int getasientosEjecutiva();

	void setnumeroVuelo(int numeroVuelo_);
	int getnumeroVuelo();

	void setFecha(tipofecha tipoFecha, int fecha);
	int getFecha(tipofecha tipoFecha);

	ListaUsuarios* getlistapasajerosdevuelo();
};