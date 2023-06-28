#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

//Declaraciones
void ingresarElementos(Pila*);
void apilarRandom(int, int, int, Pila*);
void apilarTodoInvertido(Pila*, Pila*);
void apilarTodo(Pila*, Pila*);
int menorPila(Pila*, Pila*);
void ordenarPilaSeleccion(Pila*, Pila*);
void insertarOrdenado(Pila*, int);

void ejercicioNro1();
void ejercicioNro2();
void ejercicioNro3();
void ejercicioNro4();
void ejercicioNro5();
void ejercicioNro6();

//Funciones
void ingresarElementos(Pila *pila)
{
    char continuar = 's';
    while ( continuar == 's' )
    {
        printf("\nIngrese el valor del elemento que desea apilar. ");
        leer(pila);
        printf("\nDesea continuar agregando valores? ('s' para continuar, cualquier otro caracter para salir): ");
        fflush(stdin);
        scanf("%c", &continuar);
    }
}

void apilarRandom(int insertarHasta, int minRango, int maxRango, Pila* pila)
{
    srand(time(NULL));
    int rango;
    rango = maxRango - minRango;
    while(insertarHasta > 0)
    {
        apilar(pila, rand()%rango+minRango);
        insertarHasta--;
    }
}

void apilarTodoInvertido(Pila* destino, Pila* origen)
{
    while ( !pilavacia(origen) )
    {
        apilar(destino, desapilar(origen));
    }
}

void apilarTodo(Pila* destino, Pila* origen)
{
    Pila aux;
    inicpila(&aux);

    while ( !pilavacia(origen) )
    {
        apilar(&aux, desapilar(origen));
    }
    while ( !pilavacia(&aux) )
    {
        apilar(destino, desapilar(&aux));
    }
}

int menorPila(Pila* pila, Pila* descarte)
{
    Pila menor, aux;
    inicpila(&menor);
    inicpila(&aux);

    apilar(&menor, desapilar(pila));
    while( !pilavacia(pila) )
    {
        if( tope(pila) > tope(&menor) )
        {
            apilar(&aux, desapilar(pila));
        }
        else
        {
            apilar(&aux, desapilar(&menor));
            apilar(&menor, desapilar(pila));
        }
    }
    while( !pilavacia(&aux) )
    {
        apilar(pila, desapilar(&aux));
    }
    apilar(descarte, desapilar(&menor));
    return tope(descarte);
}

void ordenarPilaSeleccion(Pila* pila, Pila* descarte)
{
    Pila pilaOrdenada;
    inicpila(&pilaOrdenada);

    while( !pilavacia(pila) )
    {
        apilar(&pilaOrdenada, menorPila(pila, descarte));
    }
    apilarTodo(pila, &pilaOrdenada);
}

void insertarOrdenado(Pila* pila, int elemento)
{
    Pila aux;
    inicpila(&aux);

    while( !pilavacia(pila) )
    {
        if( tope(pila) >= elemento )
        {
            apilar(&aux, desapilar(pila));
        }
        else
        {
            apilar(pila, elemento);
        }
    }
    while( !pilavacia(&aux) )
    {
        apilar(pila, desapilar(&aux));
    }
}

//Ejercicios
void ejercicioNro1()
{
    Pila pila;
    inicpila(&pila);

    ingresarElementos(&pila);
    mostrar(&pila);
}

void ejercicioNro2()
{
    Pila pila1, pila2;
    inicpila(&pila1);
    inicpila(&pila2);

    printf("\nGenerando pila1...");
    apilarRandom(8, 0, 10, &pila1); // apilarRandom(int insertarHasta, int minRango, int maxRango, Pila* pila)
    printf("\npila1: ");
    mostrar(&pila1);
    printf("\nApilando todo pila1 en pila2...");
    apilarTodoInvertido(&pila2, &pila1);
    printf("\npila2: ");
    mostrar(&pila2);
}

void ejercicioNro3()
{
    Pila pila1, pila2;
    inicpila(&pila1);
    inicpila(&pila2);

    printf("\nGenerando pila1...");
    apilarRandom(8, 0, 10, &pila1);
    printf("\npila1: ");
    mostrar(&pila1);

    printf("\nApilando todo pila1 en pila2 conservando el orden...");
    apilarTodo(&pila2, &pila1);
    printf("\npila2: ");
    mostrar(&pila2);
}

void ejercicioNro4()
{
    Pila pila, descarte;
    inicpila(&pila);
    inicpila(&descarte);

    printf("\nGenerando pila...");
    apilarRandom(8, 0, 10, &pila);
    printf("\npila: ");
    mostrar(&pila);

    printf("\nBuscando el menor elemento de pila...");
    printf("\nEl menor elemento de pila es: %i", menorPila(&pila, &descarte)); // menorPila(Pila* pila, Pila* descarte)
    printf("\nEl elemento ha sido eliminado con exito de la pila");
    printf("\npila: ");
    mostrar(&pila);
}

void ejercicioNro5()
{
    Pila pila, descarte;
    inicpila(&pila);
    inicpila(&descarte);

    printf("\nGenerando pila...");
    apilarRandom(8, 0, 10, &pila);
    printf("\npila: ");
    mostrar(&pila);

    printf("\nOrdenando pila por seleccion...");
    ordenarPilaSeleccion(&pila, &descarte);
    printf("\npila: ");
    mostrar(&pila);
}

void ejercicioNro6()
{
    Pila pila, descarte;
    inicpila(&pila);
    inicpila(&descarte);
    int elemento;

    printf("\nGenerando y ordenando pila...");
    apilarRandom(8, 0, 10, &pila);
    ordenarPilaSeleccion(&pila, &descarte);
    printf("\npila: ");
    mostrar(&pila);

    printf("\nIngrese un valor para el elemento a introducir. ");
    scanf("%i", &elemento);

    printf("\nIntroduciendo elemento: %i en pila...", elemento);
    insertarOrdenado(&pila, elemento);
    printf("\npila: ");
    mostrar(&pila);
}

//MAIN MENU
int main()
{
    int continuar, nroEjercicio;
    continuar = 1; //cuando continuar = 0 se sale del programa

    do
    {
        printf("\nUTN - FR Mar del Plata - Tecnico Universitario en Programacion");
        printf("\n\nProgramacion I y Laboratorio I");
        printf("\n\nTrabajo Practico Nro3: Funciones");
        printf("\n\n1. Hacer una funcion que permita ingresar varios elementos a una pila, tanto como quiera el usuario.");
        printf("\n\n2. Hacer una funcion que pase todos los elementos de una pila a otra.");
        printf("\n\n3. Hacer una funcion que pase todos los elementos de una pila a otra, pero conservando el orden.");
        printf("\n\n4. Hacer una funcion que encuentre el menor elemento de una pila y lo retorna. La misma debe eliminar");
        printf("\nese dato de la pila.");
        printf("\n\n5. Hacer una funcin que pase los elementos de una pila a otra, de manera que se genere una");
        printf("\nnueva pila ordenada. Usar la funcion del ejercicio 4. (Ordenamiento por seleccion)");
        printf("\n\n6. Hacer una funcion que inserta en una pila ordenada un nuevo elemento, conservando el orden de esta.");
        printf("\n\n7. Hacer una funcion que pase los elementos de una pila a otra, de manera que se genere una");
        printf("\nnueva pila ordenada. Usar la funcion del ejercicio 6. (Ordenamiento por insercion)");
        printf("\n\n8. Hacer una funcion que sume y retorne los dos primeros elementos de una pila (tope y anterior)");
        printf("\nsin alterar su contenido.");
        printf("\n\n9. Hacer una funcion que calcule el promedio de los elementos de una pila, para ello hacer tambien");
        printf("\nuna funcion que calcule la suma, otra para la cuenta y otra que divida. En total son cuatro");
        printf("\nfunciones, y la funcion que calcula el promedio invoca a las otras 3.");
        printf("\n\n10. Hacer una funcion que reciba una pila con numeros de un solo digito (es responsabilidad de");
        printf("\nquien usa el programa) y que transforme esos digitos en un numero decimal.");
        printf("\nPor ejemplo, la pila: BASE 5 | 7 | 6 | 4 | 1 TOPE, debe retornar: 14675");

        printf("\n\nIngrese un numero de ejercicio a ejecutar (0 para salir): ");
        scanf("%i", &nroEjercicio);

        switch(nroEjercicio)
        {
        case 1:
            ejercicioNro1();
            break;
        case 2:
            ejercicioNro2();
            break;
        case 3:
            ejercicioNro3();
            break;
        case 4:
            ejercicioNro4();
            break;
        case 5:
            ejercicioNro5();
            break;
        case 6:
            ejercicioNro6();
            break;
        case 7:
            //ejercicioNro7();
            break;
        case 8:
            //ejercicioNro8();
            break;
        case 9:
            //ejercicioNro9();
            break;
        case 10:
            //ejercicioNro10();
            break;
        case 0:
            continuar = 0;
            break;
        default:
            printf("\nEl numero de ejercicio ingresado no es valido.\n\n");
            break;
        }

        if ( continuar != 0 )
        {
            printf("\nEjercicio finalizado, desea continuar ejecutando la guia? (0 para salir): ");
            scanf("%i", &continuar);
        }

    }
    while ( continuar != 0 );

    printf("\n\nSaliendo del programa...\n");
}
