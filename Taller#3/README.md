# Taller #3 - Sistema de Gestión de Tiquetes

## Descripción

Sistema de gestión de tiquetes para el Muelle Turístico implementado en C. El programa utiliza un **Árbol Binario de Búsqueda (ABB)** para gestionar los pasajeros de manera eficiente, permitiendo operaciones de inserción, búsqueda, eliminación y recorrido.

## Características

- ✅ Registro de pasajeros con número de documento, destino y tipo de pasaje
- ✅ Gestión mediante Árbol Binario de Búsqueda (ABB)
- ✅ Recorridos del árbol: Inorden, Preorden y Postorden
- ✅ Conteo total de pasajeros registrados
- ✅ Eliminación de pasajeros por documento
- ✅ Validación de documentos duplicados
- ✅ Gestión automática de memoria

## Destinos Disponibles

1. Timbiquí
2. Juanchaco
3. Tumaco
4. Guapi

## Tipos de Pasaje

- Ida
- Ida y Regreso

## Estructura del Proyecto

```
taller#3/
├── prueba-taller.c    # Código fuente principal
└── README.md          # Este archivo
```

## Compilación

Para compilar el programa, use un compilador de C como GCC:

```bash
gcc prueba-taller.c -o prueba-taller
```

En Windows con MinGW:

```bash
gcc prueba-taller.c -o prueba-taller.exe
```

## Ejecución

```bash
./prueba-taller
```

O en Windows:

```bash
prueba-taller.exe
```

## Funcionalidades del Menú

1. **Registrar nuevo pasajero**: Agrega un nuevo pasajero al sistema con su documento, destino y tipo de pasaje
2. **Mostrar pasajeros (Inorden)**: Muestra los pasajeros ordenados por documento (ascendente)
3. **Mostrar pasajeros (Preorden)**: Muestra los pasajeros en orden de raíz, izquierda, derecha
4. **Mostrar pasajeros (Postorden)**: Muestra los pasajeros en orden de izquierda, derecha, raíz
5. **Contar total de pasajeros**: Muestra el número total de pasajeros registrados
6. **Eliminar pasajero**: Elimina un pasajero del sistema por su número de documento
7. **Salir**: Cierra el programa y libera la memoria

## Estructura de Datos

El programa utiliza una estructura `Pasajero` que contiene:
- `documento`: Número de documento (clave única)
- `destino`: Destino del viaje
- `tipo_pasaje`: Tipo de pasaje (Ida o Ida y Regreso)
- `izquierdo`: Puntero al hijo izquierdo
- `derecho`: Puntero al hijo derecho

## Algoritmos Implementados

- **Inserción**: Inserta un nuevo nodo manteniendo la propiedad del ABB
- **Eliminación**: Elimina un nodo considerando los tres casos (sin hijos, un hijo, dos hijos)
- **Recorridos**: Implementación recursiva de los tres tipos de recorrido
- **Búsqueda del mínimo**: Encuentra el nodo con el valor mínimo en un subárbol

## Requisitos

- Compilador de C (GCC, Clang, o MSVC)
- Sistema operativo: Windows, Linux o macOS

## Autor

Mario1523

## Curso

EDD2025 - Estructuras de Datos

## Licencia

Este proyecto es parte de un trabajo académico.

