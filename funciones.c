#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

/*Toma un puntero a FILE y abre un lote Masterstock de prueba*/
void crearArchivoPrueba(FILE *pf)
{
    tProducto vecprod[] =
        {
            {189, "Lavandina", 32, 23.3},
            {213, "Chocolate", 21, 104.54},
            {718, "Aceite", 34, 60.43},
            {839, "Queso cremoso", 19, 190.21},
            {124, "Cacao en polvo", 29, 36.45}
        };

    pf = fopen("masterstock.dat", "wb");
    /*Grabamos el vector entero*/
    fwrite(vecprod, sizeof(vecprod), 1, pf);

    fclose(pf);

}
/*Toma un puntero a FILE y genera el archivo de texto en el que nos basamos para hacer la actualizacion de precios*/
void crearArchivoModificador(FILE *pfm)
{
    tMovimiento vec_cambios[] =
    {
        {213, 56, 'r'},
        {124, 48, 'r'}
    };

    pfm = fopen("cambios.txt", "wt");
    for(int i = 0; i<2; i++)
    {
        fprintf(pfm, "%d | %d | %c\n", vec_cambios[i].id, vec_cambios[i].cant, vec_cambios[i].tipo);
    }
    fclose(pfm);
}
/*Muestra el archivo Masterstock con un lindo formato*/
void mostrarArchivo(FILE *pf)
{
    tProducto temp;
    pf = fopen("masterstock.dat", "rb");
    if(!pf)
    {
        printf("ERROR");
        exit(-1);
    }

    printf("\n\nID     | NOMBRE                | CT | PRECIO\n");
    printf("------- ----------------------- ---- -------\n");
    fread(&temp, sizeof(tProducto), 1, pf);
    while(!feof(pf))
    {
        printf("%06d | %-21s | %d | %.2f \n", temp.id, temp.nom, temp.cant, temp.precio);
        fread(&temp, sizeof(tProducto), 1, pf);
    }
    fclose(pf);
}
/*Modificamos el archivo masterstock en base a los datos del archivo txt*/
void modificarArchivo(FILE *pf, FILE*pfm)
{
    /*Creamos dos variables donde guardamos temporalmente los datos de las lecturas*/
    tMovimiento tempmov;
    char cad[31];

    pf = fopen("masterstock.dat", "r+b");
    pfm = fopen("cambios.txt", "rt");

    /*Secuencialmente recorremos el archivo de texto*/
    while(fgets(cad, sizeof(cad), pfm))
    {
        /*A cada cadena que capturamos, le hacemos un parsing para guardarla en una variable tMovimiento*/
        sscanf(cad, "%d %*s %d %*s %c", &tempmov.id, &tempmov.cant, &tempmov.tipo);
        buscarYReemplazar(tempmov, pf);
    }
    fclose(pfm);
    fclose(pf);
}

/*Busqueda del ID dentro de todo el archivo. Si lo encuentra, lo modifica segun el resto.*/
int buscarYReemplazar(tMovimiento mov, FILE *pf)
{
    tProducto temp;
    fread(&temp, sizeof(tProducto), 1, pf);
    while(!feof(pf))
    {
        if(mov.id == temp.id)
        {
            if(mov.tipo == 'r')
            {
                temp.cant+=mov.cant;
            }
            else
            {
                temp.cant-=mov.cant;
            }
            fseek(pf, -1L * sizeof(tProducto), SEEK_CUR);
            fwrite(&temp, sizeof(tProducto), 1, pf);
            fseek(pf, 0L, SEEK_SET);
            return 1;
        }
        fread(&temp, sizeof(tProducto), 1, pf);
    }
    fseek(pf, 0L, SEEK_SET);
    return 0;
}
