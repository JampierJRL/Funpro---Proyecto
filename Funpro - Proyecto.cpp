/*INTEGRANTES
* 1. Alfaro Quise Pablo
* 2. Cueva Sanchez Brahyan Adrian
* 3. Piedra Aguirre Luis Enrique
* 4. Rodriguez Laureano Janpier Ruben
*/

/*ENUNCIADO DEL PROBLEMA
Se creara un programa permita registrar jugadores utilizando:

* Estructuras Simples(Datos del Jugador)
* Estructuras Aninadas(Datos de Liga)
* Punteros
* Funciones(Declaracion de Funciones tanto como el Main como los Prototipos)
* Punteros a estructuras
* Arreglos dinamicos(Cantidad de jugadores)
* Aleatorio(Ganador del Balon de oro)
* Recursividad(Busqueda Binaria del jugador)

Los datos a presentar de cada jugador será los siguientes: DNI, Nombre, Edad, Nacionalidad, Altura, Peso, Puesto.
El programa permitirá realizar las siguientes operaciones:

1. Modificar datos por DNI
2. Buscar Jugador por DNI
3. Ordenar y Mostrar por Edad
4. Ordenar y Mostrar por Equipos
5. Mostra Jugadores de la misma Nacionalidad
6. Mostrar Jugadores en Ranking de Copas(personales)
7. Eliminar Jugador
8. Salir

*/

//RESOLUCION DEL PROBLEMA

//Bibliotecas
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <cstring>
using namespace std;

struct Equipo {
	char nombreLiga[30];
	char nombreEquipo[20];
	int copas;
};

struct Jugador {
	int DNI;
	int edad;
	char nombre[30], nacionalidad[20], puesto[20];
	float altura, peso;
	struct Equipo equipo;
};


//Prototipos de Utils
int leerEntero();
float leerReal();
void leerLetrasYNumeros(char dato[]);


//Propotipo de funciones
void menuPrincipal1();
void numJugadores(int* n);
void ingresoDatos(Jugador* ptr_jugador, int n);
void mostrarJugador(Jugador* ptr_jugador, int numDeJugador);
void ordenarDni(Jugador* ptr_jugador, int n);

//CASE 1
void buscarJugador(Jugador* j, int n);
int busquedaBinaria(Jugador*& j, int datobuscado, int inicio, int fin);
void modificarDatos(Jugador* j, int z);
//case 2
void buscarDNI(Jugador* j, int n);
//case 3
void ordenarEdad(Jugador* ptr_jugador, int n);
void mostrarEdad(Jugador* j, int n);
//case 4
void ordenEquipo(Jugador* j, int n);
void mostrarEquipo(Jugador* j, int n);

//case 5
int buscarNacionalidad(Jugador* j, int n, char nacionalidad[]);
void mostrarNacionalidad(Jugador* j, int n);

//case 6
void mostrarCopas(Jugador* j, int n);
void ganaBalon(Jugador* j, int n);


//case 7
int busquedasecuencial(Jugador* j, int n);
void eliminarJugador(Jugador* j, int& n);

void reporteJugadores(Jugador* ptr_jugador, int n);

int main() {
	setlocale(LC_ALL, "spanish");

	int cantJugadores, opcion;

	numJugadores(&cantJugadores);
	Jugador* jugadores = new Jugador[cantJugadores];

	ingresoDatos(jugadores, cantJugadores);

	do {
		menuPrincipal1();
		opcion = leerEntero();
		fflush(stdin);
		switch (opcion) {

		case 1:
			buscarJugador(jugadores, cantJugadores);
			break;

		case 2:

			buscarDNI(jugadores, cantJugadores);
			break;
		case 3:
			system("cls");
			ordenarEdad(jugadores, cantJugadores);
			cout << "Jugadores ordenados por edad: \n";
			mostrarEdad(jugadores, cantJugadores);
			break;
		case 4:
			system("cls");
			ordenEquipo(jugadores, cantJugadores);
			cout << "Jugadores ordenados por Equipo: \n";
			mostrarEquipo(jugadores, cantJugadores);
			break;
		case 5:
			system("cls");
			mostrarNacionalidad(jugadores, cantJugadores);
			break;
		case 6:
			system("cls");
			mostrarCopas(jugadores, cantJugadores);
			break;
		case 7:
			system("cls");
			eliminarJugador(jugadores, cantJugadores);
			break;
		case 8: 
			system("cls");
			reporteJugadores(jugadores, cantJugadores);
		}
		system("pause");

	} while (opcion != 9);
	delete[] jugadores;

	return 0;
}
int leerEntero() {
	char car, dato[100];
	int n = 0;
	do {
		car = _getch();
		if (car >= '0' && car <= '9') {
			cout << car;
			dato[n] = car;
			n++;
		}
		else
			if (car == 8 && n > 0) {
				cout << car;
				cout << " ";
				cout << car;
				n--;
			}
			else if (car == 13) cout << endl;
	} while (car != 13);
	dato[n] = 0;
	return atoi(dato);
}
float leerReal() {
	char car, dato[100];
	int n = 0, punto = 0;
	do {
		car = _getch();
		if (car >= '0' && car <= '9') {
			cout << car;
			dato[n] = car;
			n++;
		}
		else if (car == '.' && punto == 0) {
			cout << car;
			dato[n] = car;
			n++;
			punto++;
		}
		if (car == 8 && n > 0) {
			cout << car;
			cout << " ";
			cout << car;
			if (dato[n - 1] == '.') punto--;
			n--;
		}
		else if (car == 13) cout << endl;
	} while (car != 13);
	dato[n] = 0;
	return atof(dato);
}
void leerLetrasYNumeros(char dato[]) {
	char car;
	int n = 0;
	do {
		car = _getch();
		if (car == ' ' || (car >= 'a' && car <= 'z') || (car >= 'A' && car <= 'Z')) {
			cout << car;
			dato[n] = car;
			n++;
		}
		else if (car == 8 && n > 0) {
			cout << car;
			cout << " ";
			cout << car;
			n--;
		}
		else if (car == 13) cout << endl;
	} while (car != 13);
	dato[n] = 0;
}
void menuPrincipal1() {
	system("cls");
	cout << "\n\t|-----------------------------------------------------------------------------------|";
	cout << "\n\t|                       ° Menú de Opciones °                                        |";
	cout << "\n\t|---------------------------------|-------------------------------------------------|";
	cout << "\n\t| 1. Modificar Datos por DNI      | 5. Mostrar Jugadores de la misma Nacionalidad   |";
	cout << "\n\t| 2. Buscar Jugador por DNI       | 6. Mostrar Jugadores en Ranking de Copas        |";
	cout << "\n\t| 3. Ordenar y Mostrar por Edad   | 7. Eliminar Jugador                             |";
	cout << "\n\t| 4. Ordenar y Mostrar por Equipo | 8. Reportar todos los jugadores                 |";
	cout << "\n\t| 9. Salir                        |                                                 |";
	cout << "\n\t|---------------------------------|-------------------------------------------------|";
	cout << "\t\t\nIngrese una opcion: ";
}
//Funcion que permite el ingreso de una cantidad para crear el arreglo dinamico de jugadores
void numJugadores(int* cant) {
	do {
		cout << "\n\n\tIngrese la cantidad de jugadores: ";
		*cant = leerEntero();

	} while (*cant <= 0);
	cout << "--------------------------------" << endl;
}

//Funcion que permite el ingreso de datos de los jugadores
void ingresoDatos(Jugador* ptr_jugador, int n) {
	for (int i = 0; i < n; i++) {
		fflush(stdin);
		cout << endl;
		cout << "\tJugador N° " << i + 1 << endl;
		cout << "\t\tIngrese el Dni: ";
		do {
			(ptr_jugador + i)->DNI = leerEntero();
			if ((ptr_jugador + i)->DNI < 10000000 || (ptr_jugador + i)->DNI>99999999) {
				cout << "\t\tEl Dni debe tener 8 digitos, ingrese nuevamente: ";
			}
		}while ((ptr_jugador + i)->DNI < 10000000 || (ptr_jugador + i)->DNI>99999999);
		fflush(stdin);
		cout << "\t\tIngrese su Nombre: ";
		cin.getline((ptr_jugador + i)->nombre, 30);
		fflush(stdin);
		cout << "\t\tIngrese su Edad en years: ";
		(ptr_jugador + i)->edad = leerEntero();
		fflush(stdin);
		cout << "\t\tIngrese su Altura: ";
		(ptr_jugador + i)->altura = leerReal();
		fflush(stdin);
		cout << "\t\tIngrese su Nacionalidad: ";
		fflush(stdin);
		cin.getline((ptr_jugador + i)->nacionalidad, 20);
		fflush(stdin);
		cout << "\t\tIngrese su Puesto: ";
		cin.getline((ptr_jugador + i)->puesto, 20);
		fflush(stdin);
		cout << "\t\tIngrese su Equipo: ";
		cin.getline((ptr_jugador + i)->equipo.nombreEquipo, 20);
		cout << "\t\tIngrese la Liga en la que juega su equipo: ";
		cin.getline((ptr_jugador + i)->equipo.nombreLiga, 20);
		fflush(stdin);
		cout << "\t\tIngrese N° de Copas de su equipo: ";
		cin >> ((ptr_jugador + i)->equipo.copas);
		cout << "------------------------------" << endl;
		cout << endl;
	}
}
void buscarJugador(Jugador* j, int n) {
	int datobuscado;
	int z;
	do {
		system("cls");
		cout << "Ingrese DNI de jugador: ";
		datobuscado = leerEntero();
	} while (datobuscado < 10000000 || datobuscado>99999999);
	z = busquedaBinaria(j, datobuscado, 0, n-1);
	if (z != -1) {
		mostrarJugador(j, z);
	}
	else {
		cout << "DNI no se ha encontrado";

	}
}
int busquedaBinaria(Jugador *&j, int datobuscado, int inicio, int fin) {
	cout<<"borrar"<<endl;
	int centro = inicio + (fin - inicio) / 2;
	if(inicio > fin) {
		return -1;
	} else if(j[centro].DNI == datobuscado) {
		return centro;
	} else if(j[centro].DNI > datobuscado) {
		return busquedaBinaria(j, datobuscado, inicio, centro - 1);
	} else {
		return busquedaBinaria(j, datobuscado, centro + 1, fin);
	}
	return -1;
}

void modificarDatos(Jugador* j, int z) {
	int opcion;
	do {
		cout << "\t\n¿Que deseas modificar?";
		cout << "\n\t1. Nombre.";
		cout << "\n\t2. Edad.";
		cout << "\n\t3. Altura.";
		cout << "\n\t4. Liga.";
		cout << "\n\t5. Equippo.";
		cout << "\n\t6. Nacionalidad.";
		cout << "\n\t7. Puesto.";
		cout << "\n\t8. Copas.";
		cout << "\n\t9. Salir.";
		cout << "\nIngrese opción: ";
		cin >> opcion;

		while (opcion < 1 || opcion > 10) {
			cout << "Opcion incorrecta, ingrese nuevamente [1 - 9]: ";
			opcion = leerEntero();
		}

		switch (opcion) {
		case 1: cout << "\tNuevo nombre: ";
			cin.ignore();
			leerLetrasYNumeros(j[z].nombre);
			break;

		case 2:
			do {
				cout << "\tNueva edad: ";
				j[z].edad = leerEntero();
			} while (j[z].edad < 17);
			break;
		case 3:
			do {
				cout << "Nueva Altura: ";
				j[z].altura = leerReal();
			} while (j[z].altura <= 0 || j[z].altura >= 250);
			break;

		case 4:
			cout << "Nueva Liga: ";
			cin.ignore();
			leerLetrasYNumeros(j[z].equipo.nombreLiga);
			break;

		case 5:
			cout << "Nuevo Equipo: ";
			cin.ignore();
			leerLetrasYNumeros(j[z].equipo.nombreEquipo);
			break;

		case 6:
			cout << "Nueva nacionalidad: ";
			cin.ignore();
			leerLetrasYNumeros(j[z].nacionalidad);
			break;

		case 7: cout << "Nuevo Puesto: ";
			cin.ignore();
			leerLetrasYNumeros(j[z].puesto);
			break;
		case 8:
			cout << "Nuevas Nº copas: ";
			cin.ignore();
			j[z].equipo.copas = leerEntero();
			break;
		}
	} while (opcion != 8);
}
void buscarDNI(Jugador* j, int n) {
	int datobuscado;
	int z;
	system("cls");
	ordenarDni(j, n);
	cout << "Ingrese DNI de jugador: ";
	datobuscado = leerEntero();
	z = busquedaBinaria(j, datobuscado, 0, n-1);
	if (z != -1) {
		mostrarJugador(j, z);
	}
	else {
		cout << "DNI no se ha encontrado";
		system("cls");
	}
}

void ordenarDni(Jugador* ptr_jugador, int n) {
	//Funcion que ordena el arreglo segun el DNI de forma ascedente
	int pos;
	system("CLS");
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if ((ptr_jugador + i)->DNI > (ptr_jugador + j)->DNI) {
				pos = (ptr_jugador + i)->DNI;
				(ptr_jugador + i)->DNI = (ptr_jugador + j)->DNI;
				(ptr_jugador + j)->DNI = pos;
			}
		}
	}
}

void ordenarEdad(Jugador* ptr_jugador, int n) {
	//Funcion que ordena el arreglo segun la edad de forma ascedente
	int pos;
	system("CLS");
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if ((ptr_jugador + i)->edad > (ptr_jugador + j)->edad) {
				pos = (ptr_jugador + i)->edad;
				(ptr_jugador + i)->edad = (ptr_jugador + j)->edad;
				(ptr_jugador + j)->edad = pos;
			}
		}
	}
}
void mostrarEdad(Jugador* j, int n) {
	cout << "\n\tLista de Jugadores de Edad (Ascendentes)";
	cout << "\n\t-----------------------------------------";
	cout << "\n\tNombre" << "\tEdad " << endl;
	for (int i = 0; i < n; i++) {
		cout << "\t" << j[i].nombre << "\t " << j[i].edad << endl;
	}
}
void ordenEquipo(Jugador* j, int n) {
	//Funcion que ordena el arreglo segun Equipo de forma ascendente
	Jugador pos;
	system("cls");
	for (int i = 0; i < n; i++) {
		for (int y = i + 1; y < n; y++) {
			if (j[i].equipo.nombreEquipo > j[y].equipo.nombreEquipo) {
				pos = j[i];
				j[i] = j[y];
				j[y] = pos;
			}
		}
	}
}
void mostrarEquipo(Jugador* j, int n) {
	cout << "\n\tLista de Jugadores de Equipos(alfabeticamente)";
	cout << "\n\t------------------------------------------";
	cout << "\n\tNombre" << "\tEquipo " << endl;
	for (int i = 0; i < n; i++) {
		cout << "\t" << j[i].nombre << "\t " << j[i].equipo.nombreEquipo << endl;
	}
}
int buscarNacionalidad(Jugador* j, int n, char nacionalidad[]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(j[i].nacionalidad, nacionalidad) == 0) {
			return i;
		}
	}
	return -1;
}
void mostrarNacionalidad(Jugador* j, int n) {
	char nacionalidad[30];
	int z;
	system("cls");
	cout << "Ingrese nacionalidad: ";
	leerLetrasYNumeros(nacionalidad);
	z = buscarNacionalidad(j, n, nacionalidad);
	if (z == -1) {
		cout << "El jugador no se encuentra registrado.";
	}
	else {
		cout << "\nJugadores de la mima Nacionalidad\n";
		cout << "-------------------------------------" << endl;
		cout << "\n\tNombre" << "\tEdad " << "\tNacionalidad" << endl;
		for (int i = 0; i < n; i++) {
			cout << "\t" << j[i].nombre << "\t " << j[i].edad << "\t " << j[i].nacionalidad << endl;
		}
	}
}
void mostrarCopas(Jugador* j, int n) {
	cout << "Mostrando Copas de los Jugadores";
	cout << "\n\t----------------------------";
	cout << "\n\tNombre" << "\tCopas " << endl;
	for (int i = 0; i < n; i++) {
		cout << "\t" << j[i].nombre << "\t " << j[i].equipo.copas << endl;
	}
	cout << "\n////////GANADOR DEL BALON DE ORO////////" << endl;
	ganaBalon(j, n);

}
void ganaBalon(Jugador* j, int n) {
	int aleatorio;
	aleatorio = rand() % n;
	cout << "\nDatos del jugador ";
	cout << "\n\tDNI: " << j[aleatorio].DNI;
	cout << "\n\tNombre: " << j[aleatorio].nombre;
	cout << "\n\tEdad: " << j[aleatorio].edad;
	cout << "\n\tAltura: " << j[aleatorio].altura;
	cout << "\n\tNacionalidad: " << j[aleatorio].nacionalidad;
	cout << "\n\tPuesto: " << j[aleatorio].puesto;
	cout << "\n\tLiga: " << j[aleatorio].equipo.nombreLiga;
	cout << "\n\tEquipo: " << j[aleatorio].equipo.nombreEquipo;
	cout << "\n\tCopas: " << j[aleatorio].equipo.copas;
	cout << "\n\n";
}

int busquedasecuencial(Jugador* j, int n) {
	int dni;
	cout << "Ingrese DNI del jugador: ";
	dni = leerEntero();
	for (int i = 0; i < n; i++) {
		if (j[i].DNI == dni) {
			return i;
		}
	}
	return -1;
}
void eliminarJugador(Jugador* j, int& n) {
	int z;
	z = busquedasecuencial(j, n);
	if (z != -1) {
		cout << "Datos del Jugador a Eliminar..." << endl;
		cout << "\n\tDNI: " << j[z].DNI;
		cout << "\n\tNombre: " << j[z].nombre;
		cout << "\n\tEdad: " << j[z].edad;
		cout << "\n\tAltura: " << j[z].altura;
		cout << "\n\tNacionalidad: " << j[z].nacionalidad;
		cout << "\n\tPuesto: " << j[z].puesto;
		cout << "\n\tEquippo: " << j[z].equipo.nombreEquipo;
		cout << "\n\tLiga: " << j[z].equipo.nombreLiga;
		cout << "\n\tCopas: " << j[z].equipo.copas;
		for (int i = z; i < n - 1; i++) {
			j[i] = j[i + 1];
			n = n - 1;
			cout << "\nEl JUGADOR HA SIDO ELIMINADO" << endl;
		}
	}
	else {
		cout << "\nEL JUGADOR NO HA SIDO REGISTRADO" << endl;
	}
}
void reporteJugadores(Jugador* ptr_jugador, int n) {
	cout << "\n-------MOSTRANDO DATOS DE LOS JUGADORES TOTALES-------------\n\n";
	for (int i = 0; i < n; i++) {
		cout << "\tJugador N° " << i + 1 << endl;
		mostrarJugador(ptr_jugador, i);
	}

}

void mostrarJugador(Jugador* ptr_jugador, int posJugadorArray) {
	cout << "\n\t\tDni: " << ((ptr_jugador + posJugadorArray)->DNI) << endl;
	cout << "\t\tNombre: " << ((ptr_jugador + posJugadorArray)->nombre) << endl;
	cout << "\t\tEdad: " << ((ptr_jugador + posJugadorArray)->edad) << endl;
	cout << "\t\tAltura: " << ((ptr_jugador + posJugadorArray)->altura) << endl;
	cout << "\t\tNacionalidad: " << ((ptr_jugador + posJugadorArray)->nacionalidad) << endl;
	cout << "\t\tPuesto: " << ((ptr_jugador + posJugadorArray)->puesto) << endl;
	cout << "\t\tEquipo: " << ((ptr_jugador + posJugadorArray)->equipo.nombreEquipo) << endl;
	cout << "\t\tLiga: " << ((ptr_jugador + posJugadorArray)->equipo.nombreLiga) << endl;
	cout << "\t\tN° de Copas del equipo: " << ((ptr_jugador + posJugadorArray)->equipo.copas) << endl;
	cout << "------------------------------" << endl;
	cout << endl;
}
