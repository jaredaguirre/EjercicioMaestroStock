#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

/*
Se dispone de un archivo binario con la información de un Maestro de Stock. Se informan una serie de movimientos
en el stock a través de un archivo de texto. El objetivo final es la actualización del archivo maestro de stock
basado en los datos de movimientos almacenados en el archivo de texto teniendo en cuenta lo siguiente:
El archivo maestro contiene la información del producto: ID, Nombre, Cantidad, Precio
El archivo de novedades contiene ID Producto, Cantidad y Tipo de movimiento (Venta o reposición)

Desarrollar una función que a partir de los punteros FILE, genere lo archivos con datos de pruebas.

Parte C:
Implemente la actualización del archivo maestro de stock con la información contenida en el archivo de novedades.
*/
int main()
{
    FILE *pf, *pfm;
    crearArchivoPrueba(pf);
    crearArchivoModificador(pfm);

    mostrarArchivo(pf);
    modificarArchivo(pf, pfm);
    mostrarArchivo(pf);

    return 0;
}
