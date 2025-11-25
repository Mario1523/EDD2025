#include <stdio.h>

#define TAM 10  // Tamaño fijo del arreglo

// Enumeración para opciones del menú
enum OpcionesMenu {
    LLENAR = 1,
    MOSTRAR,
    ORDENAR_ASC,
    ORDENAR_DESC,
    SALIR
};

// Prototipos
void llenarArreglo(int arr[], int n);
void mostrarArreglo(const int arr[], int n);
void ordenarAscendenteSelection(int arr[], int n);
void ordenarDescendenteInsertion(int arr[], int n);
int mostrarMenu();

int main() {
    int arreglo[TAM];
    int opcion;
    int arregloLleno = 0;

    do {
        opcion = mostrarMenu();

        switch (opcion) {
            case LLENAR:
                llenarArreglo(arreglo, TAM);
                arregloLleno = 1;
                break;

            case MOSTRAR:
                if (arregloLleno)
                    mostrarArreglo(arreglo, TAM);
                else
                    printf("Primero debe llenar el arreglo.\n");
                break;

            case ORDENAR_ASC:
                if (arregloLleno)
                    ordenarAscendenteSelection(arreglo, TAM);
                else
                    printf("Primero debe llenar el arreglo.\n");
                break;

            case ORDENAR_DESC:
                if (arregloLleno)
                    ordenarDescendenteInsertion(arreglo, TAM);
                else
                    printf("Primero debe llenar el arreglo.\n");
                break;

            case SALIR:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != SALIR);

    return 0;
}

// --- FUNCIONES ---

int mostrarMenu() {
    int opcion;
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Llenar arreglo\n");
    printf("2. Mostrar arreglo original\n");
    printf("3. Ordenar (Selection Sort Ascendente)\n");
    printf("4. Ordenar (Insertion Sort Descendente)\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

void llenarArreglo(int arr[], int n) {
    printf("\nIngrese %d numeros enteros positivos:\n", n);
    for (int i = 0; i < n; i++) {
        int valor;
        do {
            printf("Elemento [%d]: ", i);
            scanf("%d", &valor);
            if (valor <= 0)
                printf("Valor no valido. Ingrese un numero positivo.\n");
        } while (valor <= 0);
        arr[i] = valor;
    }
}

void mostrarArreglo(const int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

void ordenarAscendenteSelection(int arr[], int n) {
    printf("\n--- Selection Sort (Ascendente) ---\n");
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
        printf("Paso %d: ", i + 1);
        mostrarArreglo(arr, n);
    }
    printf("Resultado final: ");
    mostrarArreglo(arr, n);
}

void ordenarDescendenteInsertion(int arr[], int n) {
    printf("\n--- Insertion Sort (Descendente) ---\n");
    for (int i = 1; i < n; i++) {
        int clave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < clave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = clave;
        printf("Paso %d: ", i);
        mostrarArreglo(arr, n);
    }
    printf("Resultado final: ");
    mostrarArreglo(arr, n);
}
