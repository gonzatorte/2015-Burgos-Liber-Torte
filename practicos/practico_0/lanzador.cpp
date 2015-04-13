//Ejercicio 2:
//Utilizando el resultado del ejercicio 1, implemente una simulación de lanzamiento de
//proyectil en 3D con las siguientes características:
//    *El usuario debe poder ingresar 3 valores correspondientes a la proyección de la velocidad inicial sobre los ejes cartesianos y un valor deltaT que indica el intervalo de tiempo.
//    *La posición inicial del proyectil es el origen.
//    *La aplicación debe calcular todas las posiciones del proyectil cada deltaT segundos hasta que el proyectil tenga altura cero.
//Notas:
//El objetivo del ejercicio está centrado en la utilización de vectores para resolver
//un problema específico, no se requiere presentar el resultado utilizando gráficos
//3D.
#include "vector_3d.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
    for (int i=0;i<argc;i++)
    {
        cout << argv[i];
    }
    string val1;
    cin >> val1;
}
