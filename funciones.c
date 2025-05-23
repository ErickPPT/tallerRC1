#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

char nombres[MAX_PRODUCTS][MAX_NAME_LEN];
int cantidades[MAX_PRODUCTS];
int tiempos[MAX_PRODUCTS];
int recursos[MAX_PRODUCTS];
int totalProductos = 0;

/* Función para ingresar datos numéricos */
int ingresoDatos(char* mensaje, int valor) {
    printf("%s", mensaje);
    while (scanf("%d", &valor) != 1 || valor < 0) {
        printf("Error, ingrese datos válidos\n");
        while (getchar() != '\n');
        printf("%s", mensaje);
    }
    while (getchar() != '\n'); // limpiar Enter que queda en el buffer
    return valor;
}

/* Muestra las opciones disponibles */
void mostrarMenu(void) {
    printf("\n=== MENU FABRICA DE COMPONENTES ELECTRONICOS ===\n");
    printf("Elige opción: \n");
    printf("1. Agregar producto\n");
    printf("2. Editar producto\n");
    printf("3. Eliminar producto\n");
    printf("4. Calcular tiempo y recursos totales\n");
    printf("5. Verificar factibilidad\n");
    printf("0. Salir\n\n");
}

/* Agrega un nuevo producto al arreglo */
void agregarProducto(void) {
    if (totalProductos >= MAX_PRODUCTS) {
        printf("Capacidad máxima alcanzada.\n");
        return;
    }

    printf("Nombre del producto: ");
    fgets(nombres[totalProductos], MAX_NAME_LEN, stdin);
    nombres[totalProductos][strcspn(nombres[totalProductos], "\n")] = '\0';

    cantidades[totalProductos] = ingresoDatos("Cantidad demandada: ", 0);
    tiempos[totalProductos] = ingresoDatos("Tiempo por unidad (min): ", 0);
    recursos[totalProductos] = ingresoDatos("Recursos por unidad: ", 0);

    totalProductos++;
    printf("Producto agregado.\n");
}

/* Busca un producto por nombre */
int buscarProducto(const char *nombre) {
    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(nombres[i], nombre) == 0) {
            return i;
        }
    }
    return -1;
}

/* Edita datos de un producto existente */
void editarProducto(void) {
    char nombreBuscado[MAX_NAME_LEN];
    printf("Nombre del producto a editar: ");
    fgets(nombreBuscado, MAX_NAME_LEN, stdin);
    nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';

    int idx = buscarProducto(nombreBuscado);
    if (idx < 0) {
        printf("No se encontró el producto.\n");
        return;
    }

    cantidades[idx] = ingresoDatos("Nueva cantidad demandada: ", 0);
    tiempos[idx] = ingresoDatos("Nuevo tiempo por unidad (min): ", 0);
    recursos[idx] = ingresoDatos("Nuevos recursos por unidad: ", 0);

    printf("Producto actualizado.\n");
}

/* Elimina un producto desplazando los elementos posteriores */
void eliminarProducto(void) {
    char nombreBuscado[MAX_NAME_LEN];
    printf("Nombre del producto a eliminar: ");
    fgets(nombreBuscado, MAX_NAME_LEN, stdin);
    nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';

    int idx = buscarProducto(nombreBuscado);
    if (idx < 0) {
        printf("No se encontró el producto.\n");
        return;
    }

    for (int i = idx; i < totalProductos - 1; i++) {
        strcpy(nombres[i], nombres[i + 1]);
        cantidades[i] = cantidades[i + 1];
        tiempos[i] = tiempos[i + 1];
        recursos[i] = recursos[i + 1];
    }

    totalProductos--;
    printf("Producto eliminado.\n");
}

/* Calcula y muestra el tiempo total y recursos totales */
void calcularTotales(void) {
    long tiempoTotal = 0, recursoTotal = 0;

    for (int i = 0; i < totalProductos; i++) {
        tiempoTotal += (long)cantidades[i] * tiempos[i];
        recursoTotal += (long)cantidades[i] * recursos[i];
    }

    printf("Tiempo total requerido: %ld minutos\n", tiempoTotal);
    printf("Recursos totales requeridos: %ld unidades\n", recursoTotal);
}

/* Verifica si la demanda es factible según límites dados */
void verificarFactibilidad(void) {
    long tiempoTotal = 0, recursoTotal = 0;
    int limiteTiempo, limiteRecursos;

    for (int i = 0; i < totalProductos; i++) {
        tiempoTotal += (long)cantidades[i] * tiempos[i];
        recursoTotal += (long)cantidades[i] * recursos[i];
    }

    limiteTiempo = ingresoDatos("Límite de tiempo disponible (min): ", 0);
    limiteRecursos = ingresoDatos("Límite de recursos disponibles: ", 0);

    if (tiempoTotal <= limiteTiempo && recursoTotal <= limiteRecursos) {
        printf("Factible, se puede cumplir la demanda.\n");
    } else {
        printf("No es factible con los recursos/tiempo actuales.\n");
        if (tiempoTotal > limiteTiempo)
            printf("Falta tiempo: necesita %ld más minutos\n", tiempoTotal - limiteTiempo);
        if (recursoTotal > limiteRecursos)
            printf("Faltan recursos: necesita %ld más unidades\n", recursoTotal - limiteRecursos);
    }
}