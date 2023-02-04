/**
 * Realizado para la Univesidad Nacional Experimental del Táchira
 * Asignatura de Sistemas Operativos, profesor Miguel Useche
 * Estudiantes:
 * Carlos Rosales / C.I. V-27.920.644
 * Diego Fernández / C.I. V-27.271.032
 * PRÁCTICA NUMERO 3 - ASIGNACIÓN  Crackeador de MD5
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <pthread.h>
#include <queue>
#include "md5.cpp"

using namespace std;

struct Usuario
{
    string usuario;
    string password_encriptada;
    string password_desencriptada;
    int posicion;
};

string obtener_password(string);
int saltarse_caracteres_especiales(int);
void *ejecutar_hilo(void *);

pthread_mutex_t mutex_semaforo;
ofstream archivoDeSalida("users_out.txt");
int posicion_global = 0;

int main(int argc, char const *argv[])
{
    cout << "======================== Crackeador de MD5 ========================\n\n"
         << "Numero de argumentos ingresados: " << argc - 1 << "\n";

    if (argc >= 3)
    {
        if (argc > 3)
        {
            cout << "-!- La cantidad de argumentos ingresados es superior a la requerida, se continuara con la ejecucion pero se aconseja revisar -!-\n";
        }

        string rutaDelArchivo = argv[1];
        cout << "Ruta del archivo a leer: " << rutaDelArchivo << "\n";

        string cantidadDeHilos = argv[2];
        int nHilos = stoi(cantidadDeHilos);
        cout << "Numero de hilos a usar: " << nHilos << "\n";

        if (nHilos <= 0)
        {
            cout << "--!!!!!-- La cantidad de hilos debe ser superior a 0 --!!!!!!--\n";
            cout << "======================== EJECUCION TERMINADA ========================\n";
            return -1;
        }

        if (nHilos >= 7)
        {
            cout << "--!!!!!-- La cantidad de hilos debe ser inferior a 7 --!!!!!!--\n";
            cout << "======================== EJECUCION TERMINADA ========================\n";
            return -1;
        }

        ifstream archivo(rutaDelArchivo);

        if (archivo.good())
        {
            cout << "ARCHIVO ABIERTO\n";
            string lineaActual;

            queue<pthread_t *> hilos;

            cout << "--!!!!!-- DESENCRIPTANDO CONTRASEÑAS --!!!!!!--\n\n";

            struct Usuario *usuarioActual;

            int posicion_actual = 0;
            while (getline(archivo, lineaActual) && posicion_actual < 50)
            {

                if (hilos.size() + 1 > nHilos)
                {
                    pthread_t *hiloActual = hilos.front();
                    pthread_join(*hiloActual, NULL);
                    hilos.pop();
                }

                string delimitador = "::";
                // cout << "Linea de entrada: " << lineaActual << "\n";
                string usuario = lineaActual.substr(0, lineaActual.find(delimitador));
                string password_encriptada = lineaActual.substr(lineaActual.find(delimitador) + 2, lineaActual.length());

                usuarioActual = new Usuario();

                usuarioActual->usuario = usuario;
                usuarioActual->password_encriptada = password_encriptada;
                usuarioActual->password_desencriptada = "";
                usuarioActual->posicion = posicion_actual;

                posicion_actual++;

                pthread_t *hilo = new pthread_t();
                pthread_create(hilo, NULL, ejecutar_hilo, (void *)usuarioActual);
                hilos.push(hilo);
            }

            while (!hilos.empty())
            {
                pthread_t *hiloActual = hilos.front();
                pthread_join(*hiloActual, NULL);
                hilos.pop();
            }

            cout << "\n--!!!!!-- CONTRASEÑAS DESENCRIPTADAS --!!!!!!--\n\n";

            archivoDeSalida.close();

            cout << "ARCHIVO CERRADO\n\n";
            cout << "======================== EJECUCION TERMINADA ========================\n";

            return 0;
        }
        else
        {
            cout << "--!!!!!-- Algo ha sucedido leyendo el archivo --!!!!!!--\n";
            cout << "======================== EJECUCION TERMINADA ========================\n";
            return -1;
        }

        cout << "======================== EJECUCION TERMINADA ========================\n";
    }
    else
    {
        cout << "--!!!!!-- La cantidad de argumentos ingresados es insuficiente --!!!!!!--\n"
             << "======================== EJECUCION TERMINADA ========================\n";
        return -1;
    }

    return 0;
}

void *ejecutar_hilo(void *usuario)
{
    Usuario *punteroUsuario = (Usuario *)usuario;

    punteroUsuario->password_desencriptada = obtener_password(punteroUsuario->password_encriptada);

    while (posicion_global < punteroUsuario->posicion)
    {
        pthread_mutex_lock(&mutex_semaforo);
    }

    cout << punteroUsuario->usuario << "    " << punteroUsuario->password_desencriptada << "\n";

    archivoDeSalida << punteroUsuario->usuario << "    " << punteroUsuario->password_desencriptada << "\n";

    posicion_global = punteroUsuario->posicion + 1;

    pthread_mutex_unlock(&mutex_semaforo);

    return (void *)&usuario;
}

string obtener_password(string password_encriptada)
{

    for (int contadorPrimeraLetra = 65; contadorPrimeraLetra < 123; contadorPrimeraLetra++)
    {
        string primeraRecopilacion;

        contadorPrimeraLetra = saltarse_caracteres_especiales(contadorPrimeraLetra);
        primeraRecopilacion.push_back(contadorPrimeraLetra);

        for (int contadorSegundaLetra = 65; contadorSegundaLetra < 123; contadorSegundaLetra++)
        {
            string segundaRecopilacion = primeraRecopilacion;
            contadorSegundaLetra = saltarse_caracteres_especiales(contadorSegundaLetra);
            segundaRecopilacion.push_back(contadorSegundaLetra);

            for (int contadorTerceraLetra = 65; contadorTerceraLetra < 123; contadorTerceraLetra++)
            {
                string terceraRecopilacion = segundaRecopilacion;

                contadorTerceraLetra = saltarse_caracteres_especiales(contadorTerceraLetra);
                terceraRecopilacion.push_back(contadorTerceraLetra);

                for (int contadorCuartaLetra = 65; contadorCuartaLetra < 123; contadorCuartaLetra++)
                {
                    string cuartaRecopilacion = terceraRecopilacion;

                    contadorCuartaLetra = saltarse_caracteres_especiales(contadorCuartaLetra);
                    cuartaRecopilacion.push_back(contadorCuartaLetra);

                    string intentoDeEncriptacion = MD5(cuartaRecopilacion).hexdigest();

                    // cout << password_encriptada << " == " << intentoDeEncriptacion << " (" << cuartaRecopilacion << ")\n";

                    if (password_encriptada == intentoDeEncriptacion)
                    {
                        return cuartaRecopilacion;
                    }
                }
            }
        }
    }

    return "NO SE LOGRO DESENCRIPTAR";
}

int saltarse_caracteres_especiales(int codigoCaracter)
{
    if (codigoCaracter > 90 && codigoCaracter < 97)
    {
        return 97;
    }
    return codigoCaracter;
}
