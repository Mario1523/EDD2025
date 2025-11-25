// Inclusión de librería estándar para printf y scanf
#include <stdio.h>

typedef struct {
    int codigo;
    float nota;
} Estudiante;

#define NUM_ESTUDIANTES 6

Estudiante estudiantes[NUM_ESTUDIANTES] = {
    {2024101, 4.5},
    {2024102, 3.2},
    {2024103, 2.9},
    {2024104, 4.0},
    {2024105, 3.8},
    {2024106, 4.7}
};

// Función para mostrar estudiantes
void mostrarEstudiantes(const Estudiante arr[], int n) {
    printf("\nCod\tNota\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%.2f\n", arr[i].codigo, arr[i].nota);
}

// Opciones del menú

enum OpcionesMenu {
    NOTA_MAX = 1,
    PROMEDIO,
    ORDENAR_COD,
    MOSTRAR,
    SALIR
};


int mostrarMenu() {
    int op;
    printf("\n=== MENÚ ===\n");
    printf("1. Nota máxima (recursivo)\n");
    printf("2. Promedio (recursivo)\n");
    printf("3. Ordenar por código (Selection Sort Recursivo)\n");
    printf("4. Mostrar estudiantes\n");
    printf("5. Salir\n");
    printf("Opción: ");
    scanf("%d", &op);
    return op;
}




// Prototipos de funciones
float notaMaxRec(const Estudiante arr[], int n);
float sumaNotasRec(const Estudiante arr[], int n);
void ordenarCodRec(Estudiante arr[], int n, int inicio);
int buscarMinIdx(const Estudiante arr[], int n, int inicio, int minIdx);

int main() {
    int opcion;
    int ordenado = 0;

    do {
        opcion = mostrarMenu();

        switch(opcion) {
            case NOTA_MAX:
                printf("Nota máxima: %.2f\n", notaMaxRec(estudiantes, NUM_ESTUDIANTES));
                break;
            case PROMEDIO:
                printf("Promedio: %.2f\n", sumaNotasRec(estudiantes, NUM_ESTUDIANTES)/NUM_ESTUDIANTES);
                break;
            case ORDENAR_COD:
                ordenarCodRec(estudiantes, NUM_ESTUDIANTES, 0);
                ordenado = 1;
                printf("Estudiantes ordenados por código.\n");
                break;
            case MOSTRAR:
                mostrarEstudiantes(estudiantes, NUM_ESTUDIANTES);
                break;
            case SALIR:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while(opcion != SALIR);

    return 0;
}

// Función recursiva para encontrar la nota máxima
float notaMaxRec(const Estudiante arr[], int n) {
    if (n == 1) return arr[0].nota;
    float maxRest = notaMaxRec(arr, n-1);
    return (arr[n-1].nota > maxRest) ? arr[n-1].nota : maxRest;
}

// Función recursiva para sumar las notas
float sumaNotasRec(const Estudiante arr[], int n) {
    if (n == 0) return 0;
    return arr[n-1].nota + sumaNotasRec(arr, n-1);
}

// Función recursiva para ordenar por código (Selection Sort)
void ordenarCodRec(Estudiante arr[], int n, int inicio) {
    if (inicio >= n-1) return;
    int minIdx = buscarMinIdx(arr, n, inicio, inicio);
    if (minIdx != inicio) {
        Estudiante tmp = arr[inicio];
        arr[inicio] = arr[minIdx];
        arr[minIdx] = tmp;
    }
    ordenarCodRec(arr, n, inicio+1);
}

// Función recursiva para buscar el índice del menor código
int buscarMinIdx(const Estudiante arr[], int n, int inicio, int minIdx) {
    if (inicio >= n) return minIdx;
    if (arr[inicio].codigo < arr[minIdx].codigo) minIdx = inicio;
    return buscarMinIdx(arr, n, inicio+1, minIdx);
}