#ifndef FUNCIONES2_H
#define FUNCIONES2_H

#define MAX_PRODUCTS   100
#define MAX_NAME_LEN   50

/* Solo declaración (no hay espacio asignado aquí) */
extern char nombres[MAX_PRODUCTS][MAX_NAME_LEN];
extern int  cantidades[MAX_PRODUCTS];
extern int  tiempos[MAX_PRODUCTS];
extern int  recursos[MAX_PRODUCTS];
extern int  totalProductos;

/* Prototipos */
void mostrarMenu(void);
void agregarProducto(void);
int  buscarProducto(const char *nombre);
void editarProducto(void);
void eliminarProducto(void);
void calcularTotales(void);
void verificarFactibilidad(void);
int ingresoDatos(char *mensaje, int valor);

#endif // FUNCIONES2_H
