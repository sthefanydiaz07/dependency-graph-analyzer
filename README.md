# Dependency Graph Analyzer

Sistema de análisis de dependencias de software en C, que modela las relaciones entre componentes de un sistema como un grafo dirigido y aplica algoritmos de recorrido para evaluar el impacto de fallos.

## 📌 Descripción

Este proyecto simula un sistema de software compuesto por múltiples componentes interdependientes (por ejemplo, un módulo de red, un lector de datos, un manejador de rutas, etc.). Cada componente se representa como un nodo en un grafo, y cada dependencia como una arista dirigida.

El sistema permite:
- Identificar el **componente crítico** (el que tiene más dependencias apuntando hacia él).
- **Rastrear el impacto de un fallo** en cascada usando DFS (Depth-First Search).
- **Priorizar el orden de corrección** de componentes afectados usando BFS (Breadth-First Search).
- Visualizar el grafo organizado por niveles de profundidad.
- Simular un fallo automático aleatorio y ver su propagación.
- Cargar un sistema predefinido o ingresar uno personalizado (componentes y conexiones definidos por el usuario).

## 🧠 Cómo funciona

- El grafo se representa con una **matriz de adyacencia dinámica** (`int **grafo`), reservada en memoria según el número de componentes.
- **DFS** (`dfs()` / `rastrear_impacto()`): recorre recursivamente todos los nodos que dependen (directa o indirectamente) del componente que falló, marcando cada uno como afectado.
- **BFS** (`priorizar_correcciones()`): recorre el grafo por niveles usando una cola, generando el orden en que deberían corregirse los componentes afectados, priorizando los más cercanos al fallo.
- El **componente crítico** se calcula contando el grado de entrada de cada nodo (cuántos componentes dependen de él).
- La memoria se reserva y libera dinámicamente (`malloc`/`calloc`/`free`) según el tamaño del sistema ingresado.

## 🛠️ Tecnologías

- Lenguaje: **C**
- Manejo de memoria dinámica
- Estructuras de datos: grafo dirigido (matriz de adyacencia), colas para BFS
- Algoritmos: DFS, BFS, cálculo de grado de entrada

## ▶️ Cómo compilarlo y ejecutarlo

```bash
gcc PIA.c -o analyzer
./analyzer
```

> Nota: el programa usa `system("cls")` para limpiar la pantalla, por lo que está pensado para ejecutarse en **Windows**. En Linux/Mac, reemplaza esa línea por `system("clear")` si lo vas a correr ahí.

## 💡 Ejemplo de uso

Al ejecutar el programa, puedes elegir entre un sistema predefinido (21 componentes ya cargados) o ingresar uno personalizado. Por ejemplo, al simular un fallo en el componente `LectorDatos`:

## 👥 Trabajo en equipo

Propuse y lideré el diseño de este proyecto, desarrollado en equipo con 2 compañeros más. Definí el alcance del sistema (análisis de dependencias mediante grafos) y trabajé en la inicialización de la estructura de datos, el diseño del grafo base y el flujo/interfaz del programa. Además, revisé y validé la implementación completa de los algoritmos de recorrido (DFS/BFS) y el manejo de memoria dinámica.

## 🎯 Aprendizajes

- Aplicación práctica de teoría de grafos a un problema real de ingeniería de software.
- Manejo de memoria dinámica en C (reserva y liberación segura).
- Diferencias prácticas entre DFS y BFS según el tipo de análisis que se necesita (impacto vs. priorización).
