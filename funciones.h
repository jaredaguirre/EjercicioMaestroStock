#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct
{
    int id;
    char nom[21];
    int cant;
    float precio;
}tProducto;

typedef struct
{
    int id;
    int cant;
    char tipo;
    /*El tipo puede ser V (Venta) o R (Reposicion)*/
}tMovimiento;

void crearArchivoPrueba(FILE *);
void crearArchivoModificador(FILE *);
void modificarArchivo(FILE*, FILE*);
void mostrarArchivo(FILE *);

int buscarYReemplazar(tMovimiento, FILE*);

#endif // FUNCIONES_H_INCLUDED
