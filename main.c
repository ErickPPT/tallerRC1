#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main(void) {
    int opcion;
    do {
        mostrarMenu();
        
        scanf("%d", &opcion);
        getchar();  // limpiar buffer

        switch (opcion) {
            case 1: agregarProducto(); break;
            case 2: editarProducto(); break;
            case 3: eliminarProducto(); break;
            case 4: calcularTotales(); break;
            case 5: verificarFactibilidad(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opción no válida\n");
        }
    } while (opcion != 0);

    return 0;
}
