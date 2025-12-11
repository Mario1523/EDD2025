#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX_DESTINO 50
#define MAX_TIPO 20

// Estructura del nodo Pasajero
typedef struct Pasajero {
    int documento;
    char destino[MAX_DESTINO];
    char tipo_pasaje[MAX_TIPO];
    struct Pasajero *izquierdo;
    struct Pasajero *derecho;
} Pasajero;

// Prototipos de funciones
Pasajero* crearNodo(int documento, char destino[], char tipo_pasaje[]);
Pasajero* insertar(Pasajero* raiz, int documento, char destino[], char tipo_pasaje[]);
void mostrarInorden(Pasajero* raiz);
void mostrarPreorden(Pasajero* raiz);
void mostrarPostorden(Pasajero* raiz);
int contarPasajeros(Pasajero* raiz);
Pasajero* buscarMinimo(Pasajero* raiz);
Pasajero* eliminar(Pasajero* raiz, int documento);
void liberarArbol(Pasajero* raiz);
void mostrarMenu();
void limpiarBuffer();

// Función para crear un nuevo nodo
Pasajero* crearNodo(int documento, char destino[], char tipo_pasaje[]) {
    Pasajero* nuevo = (Pasajero*)malloc(sizeof(Pasajero));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return NULL;
    }
    nuevo->documento = documento;
    strcpy(nuevo->destino, destino);
    strcpy(nuevo->tipo_pasaje, tipo_pasaje);
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    return nuevo;
}

// Función para insertar un pasajero en el ABB
Pasajero* insertar(Pasajero* raiz, int documento, char destino[], char tipo_pasaje[]) {
    // Si el árbol está vacío, crear un nuevo nodo
    if (raiz == NULL) {
        return crearNodo(documento, destino, tipo_pasaje);
    }
    
    // Si el documento ya existe, ignorar la inserción
    if (documento == raiz->documento) {
        printf("El documento %d ya existe en el sistema. No se puede duplicar.\n", documento);
        return raiz;
    }
    
    // Si el documento es menor, insertar en el subárbol izquierdo
    if (documento < raiz->documento) {
        raiz->izquierdo = insertar(raiz->izquierdo, documento, destino, tipo_pasaje);
    }
    // Si el documento es mayor, insertar en el subárbol derecho
    else {
        raiz->derecho = insertar(raiz->derecho, documento, destino, tipo_pasaje);
    }
    
    return raiz;
}

// Función para mostrar pasajeros en Inorden
void mostrarInorden(Pasajero* raiz) {
    if (raiz != NULL) {
        mostrarInorden(raiz->izquierdo);
        printf("Documento: %d | Destino: %s | Tipo: %s\n", 
               raiz->documento, raiz->destino, raiz->tipo_pasaje);
        mostrarInorden(raiz->derecho);
    }
}

// Función para mostrar pasajeros en Preorden
void mostrarPreorden(Pasajero* raiz) {
    if (raiz != NULL) {
        printf("Documento: %d | Destino: %s | Tipo: %s\n", 
               raiz->documento, raiz->destino, raiz->tipo_pasaje);
        mostrarPreorden(raiz->izquierdo);
        mostrarPreorden(raiz->derecho);
    }
}

// Función para mostrar pasajeros en Postorden
void mostrarPostorden(Pasajero* raiz) {
    if (raiz != NULL) {
        mostrarPostorden(raiz->izquierdo);
        mostrarPostorden(raiz->derecho);
        printf("Documento: %d | Destino: %s | Tipo: %s\n", 
               raiz->documento, raiz->destino, raiz->tipo_pasaje);
    }
}

// Función para contar el número total de pasajeros
int contarPasajeros(Pasajero* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarPasajeros(raiz->izquierdo) + contarPasajeros(raiz->derecho);
}

// Función auxiliar para encontrar el nodo mínimo (usado en eliminación)
Pasajero* buscarMinimo(Pasajero* raiz) {
    while (raiz != NULL && raiz->izquierdo != NULL) {
        raiz = raiz->izquierdo;
    }
    return raiz;
}

// Función para eliminar un pasajero por documento
Pasajero* eliminar(Pasajero* raiz, int documento) {
    if (raiz == NULL) {
        printf("El documento %d no se encuentra en el sistema.\n", documento);
        return raiz;
    }
    
    // Buscar el nodo a eliminar
    if (documento < raiz->documento) {
        raiz->izquierdo = eliminar(raiz->izquierdo, documento);
    }
    else if (documento > raiz->documento) {
        raiz->derecho = eliminar(raiz->derecho, documento);
    }
    else {
        // Nodo encontrado, proceder a eliminar
        // Caso 1: Nodo sin hijos o con un solo hijo
        if (raiz->izquierdo == NULL) {
            Pasajero* temp = raiz->derecho;
            free(raiz);
            printf("Pasajero con documento %d eliminado exitosamente.\n", documento);
            return temp;
        }
        else if (raiz->derecho == NULL) {
            Pasajero* temp = raiz->izquierdo;
            free(raiz);
            printf("Pasajero con documento %d eliminado exitosamente.\n", documento);
            return temp;
        }
        
        // Caso 2: Nodo con dos hijos
        // Encontrar el sucesor inorden (menor en el subárbol derecho)
        Pasajero* temp = buscarMinimo(raiz->derecho);
        
        // Copiar los datos del sucesor al nodo actual
        raiz->documento = temp->documento;
        strcpy(raiz->destino, temp->destino);
        strcpy(raiz->tipo_pasaje, temp->tipo_pasaje);
        
        // Eliminar el sucesor
        raiz->derecho = eliminar(raiz->derecho, temp->documento);
    }
    
    return raiz;
}

// Función para liberar toda la memoria del árbol
void liberarArbol(Pasajero* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izquierdo);
        liberarArbol(raiz->derecho);
        free(raiz);
    }
}

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Función para mostrar el menú principal
void mostrarMenu() {
    printf("\n========================================\n");
    printf("  SISTEMA DE GESTION DE TIQUETES\n");
    printf("  Muelle Turistico\n");
    printf("========================================\n");
    printf("1. Registrar nuevo pasajero\n");
    printf("2. Mostrar pasajeros (Inorden)\n");
    printf("3. Mostrar pasajeros (Preorden)\n");
    printf("4. Mostrar pasajeros (Postorden)\n");
    printf("5. Contar total de pasajeros\n");
    printf("6. Eliminar pasajero\n");
    printf("7. Salir\n");
    printf("========================================\n");
    printf("Seleccione una opcion: ");
}

int main() {
    Pasajero* raiz = NULL;
    int opcion, documento, total;
    char destino[MAX_DESTINO];
    char tipo_pasaje[MAX_TIPO];
    int tipo_opcion;
    
    printf("Bienvenido al Sistema de Gestion de Tiquetes\n");
    
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        limpiarBuffer();
        
        switch (opcion) {
            case 1: // Registrar nuevo pasajero
                printf("\n--- REGISTRO DE NUEVO PASAJERO ---\n");
                printf("Ingrese el numero de documento: ");
                scanf("%d", &documento);
                limpiarBuffer();
                
                printf("\nDestinos disponibles:\n");
                printf("1. Timbiqui\n");
                printf("2. Juanchaco\n");
                printf("3. Tumaco\n");
                printf("4. Guapi\n");
                printf("Seleccione el destino (1-4): ");
                scanf("%d", &tipo_opcion);
                limpiarBuffer();
                
                switch (tipo_opcion) {
                    case 1:
                        strcpy(destino, "Timbiqui");
                        break;
                    case 2:
                        strcpy(destino, "Juanchaco");
                        break;
                    case 3:
                        strcpy(destino, "Tumaco");
                        break;
                    case 4:
                        strcpy(destino, "Guapi");
                        break;
                    default:
                        printf("Opcion invalida. Se asignara Timbiqui por defecto.\n");
                        strcpy(destino, "Timbiqui");
                        break;
                }
                
                printf("\nTipo de pasaje:\n");
                printf("1. Ida\n");
                printf("2. Ida y Regreso\n");
                printf("Seleccione el tipo (1-2): ");
                scanf("%d", &tipo_opcion);
                limpiarBuffer();
                
                if (tipo_opcion == 1) {
                    strcpy(tipo_pasaje, "Ida");
                } else if (tipo_opcion == 2) {
                    strcpy(tipo_pasaje, "Ida y Regreso");
                } else {
                    printf("Opcion invalida. Se asignara 'Ida' por defecto.\n");
                    strcpy(tipo_pasaje, "Ida");
                }
                
                raiz = insertar(raiz, documento, destino, tipo_pasaje);
                printf("Pasajero registrado exitosamente.\n");
                break;
                
            case 2: // Mostrar Inorden
                printf("\n--- LISTADO DE PASAJEROS (INORDEN) ---\n");
                if (raiz == NULL) {
                    printf("No hay pasajeros registrados en el sistema.\n");
                } else {
                    mostrarInorden(raiz);
                }
                break;
                
            case 3: // Mostrar Preorden
                printf("\n--- LISTADO DE PASAJEROS (PREORDEN) ---\n");
                if (raiz == NULL) {
                    printf("No hay pasajeros registrados en el sistema.\n");
                } else {
                    mostrarPreorden(raiz);
                }
                break;
                
            case 4: // Mostrar Postorden
                printf("\n--- LISTADO DE PASAJEROS (POSTORDEN) ---\n");
                if (raiz == NULL) {
                    printf("No hay pasajeros registrados en el sistema.\n");
                } else {
                    mostrarPostorden(raiz);
                }
                break;
                
            case 5: // Contar pasajeros
                total = contarPasajeros(raiz);
                printf("\n--- CONTEO DE PASAJEROS ---\n");
                printf("Total de pasajeros registrados: %d\n", total);
                break;
                
            case 6: // Eliminar pasajero
                printf("\n--- ELIMINAR PASAJERO ---\n");
                printf("Ingrese el numero de documento a eliminar: ");
                scanf("%d", &documento);
                limpiarBuffer();
                raiz = eliminar(raiz, documento);
                break;
                
            case 7: // Salir
                printf("\nGracias por usar el sistema. Hasta luego!\n");
                break;
                
            default:
                printf("\nOpcion invalida. Por favor, seleccione una opcion del 1 al 7.\n");
                break;
        }
        
    } while (opcion != 7);
    
    // Liberar memoria antes de salir
    liberarArbol(raiz);
    
    return 0;
}
