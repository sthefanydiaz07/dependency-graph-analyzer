#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_VERTICES 21
#define NOMBRE_MAX 30

int num_vertices_actual = NUM_VERTICES;

char   **nombres  = NULL;   
int   **grafo    = NULL;   
int    *visitado_dfs = NULL;
int    *afectados    = NULL;
int     num_afectados = 0;
int    *niveles       = NULL;

void liberar_memoria(){
    int i;
    if(nombres){
        for(i = 0; i <= num_vertices_actual; i++)
            free(nombres[i]); 
        free(nombres);
        nombres = NULL;
    }
    if(grafo){
        for(i = 0; i <= num_vertices_actual; i++)
            free(grafo[i]);
        free(grafo);
        grafo = NULL;
    }
    free(visitado_dfs); visitado_dfs = NULL;
    free(afectados);    afectados    = NULL;
    free(niveles);      niveles      = NULL;
}

void reservar_memoria(int n){
    int i;
    liberar_memoria();

    nombres = (char **)malloc((n + 1) * sizeof(char *));
    grafo   = (int  **)malloc((n + 1) * sizeof(int  *));
    for(i = 0; i <= n; i++){
        nombres[i] = (char *)calloc(NOMBRE_MAX, sizeof(char));
        grafo[i]   = (int  *)calloc(n + 1,      sizeof(int));
    }
    visitado_dfs = (int *)calloc(n + 1, sizeof(int));
    afectados    = (int *)calloc(n + 1, sizeof(int));
    niveles      = (int *)malloc((n + 1) * sizeof(int));
    for(i = 0; i <= n; i++) niveles[i] = -1;
}

void inicializar_nombres(){
    strcpy(nombres[1],  "Programa");
    strcpy(nombres[2],  "PiezaRed");
    strcpy(nombres[3],  "PiezaUtils");
    strcpy(nombres[4],  "PiezaHTTP");
    strcpy(nombres[5],  "LectorDatos");
    strcpy(nombres[6],  "ManejadorRutas");
    strcpy(nombres[7],  "ProcesadorConsultas");
    strcpy(nombres[8],  "EnviadorArchivos");
    strcpy(nombres[9],  "ManejadorRedireccion");
    strcpy(nombres[10], "MedidorTamanio");
    strcpy(nombres[11], "RegistradorEventos");
    strcpy(nombres[12], "ConvertidorTexto");
    strcpy(nombres[13], "IdentificadorFormato");
    strcpy(nombres[14], "EjecutorTareas");
    strcpy(nombres[15], "GestorErrores");
    strcpy(nombres[16], "MedidorTiempo");
    strcpy(nombres[17], "ProtectorMemoria");
    strcpy(nombres[18], "CatalogoFormatos");
    strcpy(nombres[19], "CombinadorFlujos");
    strcpy(nombres[20], "RetardadorFlujos");
    strcpy(nombres[21], "MonitorConexion");
}

void inicializar_grafo(){
    int i, j;
    for(i = 0; i <= num_vertices_actual; i++)
        for(j = 0; j <= num_vertices_actual; j++)
            grafo[i][j] = 0;

    grafo[1][2]=1; grafo[1][3]=1; grafo[1][4]=1;
    grafo[2][5]=1; grafo[2][6]=1; grafo[2][7]=1; grafo[2][8]=1; grafo[2][21]=1;
    grafo[4][8]=1; grafo[4][9]=1;
    grafo[5][10]=1; grafo[5][11]=1; grafo[5][12]=1; grafo[5][13]=1;
    grafo[7][11]=1; grafo[7][13]=1;
    grafo[8][13]=1; grafo[8][14]=1; grafo[8][15]=1;
    grafo[11][16]=1;
    grafo[12][17]=1;
    grafo[13][18]=1;
    grafo[14][19]=1; grafo[14][20]=1;
}

int validar_entero(){
    char Aux[50];
    int i, p, y, num;
    do{
        num = 0;
        printf(" ");
        fflush(stdin);
        fgets(Aux, sizeof(Aux), stdin);
        Aux[strcspn(Aux, "\n")] = 0;
        y = strlen(Aux);
        p = 1;
        for(i = 0; i < y; i++){
            if(i == 0 && Aux[i] == '-'){
                p = 1;
            } else {
                if(isdigit(Aux[i]))
                    p = 1;
                else{
                    p = 0;
                    printf("\n\nError, dato mal introducido. Ingrese de nuevo\n\n ");
                    break;
                }
            }
        }
        if(y == 0 || (y == 1 && Aux[0] == '-'))
            p = 0;
    }while(p == 0);
    num = atoi(Aux);
    return num;
}

void imprimir_separado(){
    printf("===============================\n");
}

void titulo(const char *t){
    printf("====================\n  %s\n====================\n", t);
}

void mostrar_nodos(){
    int i;
    printf("\n  Componentes disponibles:\n");
    for(i = 1; i <= num_vertices_actual; i++){
        printf("    [V%-2d] %s\n", i, nombres[i]);
    }
    printf("\n");
}

void dfs(int nodo){
    int i;
    for(i = 1; i <= num_vertices_actual; i++){
        if(grafo[i][nodo] == 1 && visitado_dfs[i] == 0){
            visitado_dfs[i] = 1;
            afectados[num_afectados++] = i;
            dfs(i);
        }
    }
}

void rastrear_impacto(int nodo){
    int i;
    for(i = 1; i <= num_vertices_actual; i++)
        visitado_dfs[i] = 0;
    num_afectados = 0;
    printf("\n  Componente con fallo: V%d %s\n\n", nodo, nombres[nodo]);
    printf("  Componentes afectados:\n\n");
    visitado_dfs[nodo] = 1;
    dfs(nodo);
    for(i = 0; i < num_afectados; i++)
        printf("   [V%d] %s\n", afectados[i], nombres[afectados[i]]);
    printf("\n Total afectados: %d\n", num_afectados);
}

void priorizar_correcciones(int nodo){
    int *cola    = (int *)malloc((num_vertices_actual + 1) * sizeof(int));
    int *visitado= (int *)calloc(num_vertices_actual + 1,   sizeof(int));
    int frente = 0, final_ = 0, i, actual;

    cola[final_++] = nodo;
    visitado[nodo] = 1;
    printf("\n Orden de correccion (BFS):\n");
    while(frente < final_){
        actual = cola[frente++];
        printf("   [V%d] %s\n", actual, nombres[actual]);
        for(i = 1; i <= num_vertices_actual; i++){
            if(grafo[i][actual] == 1 && visitado[i] == 0){
                cola[final_++] = i;
                visitado[i] = 1;
            }
        }
    }
    printf("\n Prioridad generada correctamente.\n");
    free(cola);
    free(visitado);
}

int calcular_nodo_critico(){
    int *grado = (int *)calloc(num_vertices_actual + 1, sizeof(int));
    int i, j, mayor = -99999, mayor_pos = 1;
    for(i = 1; i <= num_vertices_actual; i++)
        for(j = 1; j <= num_vertices_actual; j++)
            if(grafo[i][j] == 1)
                grado[j]++;
    for(i = 1; i <= num_vertices_actual; i++)
        if(grado[i] > mayor){ mayor = grado[i]; mayor_pos = i; }
    free(grado);
    return mayor_pos;
}

void calcular_niveles(){
    int *cola     = (int *)malloc((num_vertices_actual + 1) * sizeof(int));
    int *visitado = (int *)calloc(num_vertices_actual + 1,   sizeof(int));
    int frente = 0, final_ = 0, i, actual;

    for(i = 0; i <= num_vertices_actual; i++) niveles[i] = -1;
    niveles[1] = 0;
    cola[final_++] = 1;
    visitado[1] = 1;
    while(frente < final_){
        actual = cola[frente++];
        for(i = 1; i <= num_vertices_actual; i++){
            if(grafo[actual][i] == 1 && visitado[i] == 0){
                cola[final_++] = i;
                niveles[i] = niveles[actual] + 1;
                visitado[i] = 1;
            }
        }
    }
    free(cola);
    free(visitado);
}

void mostrar_grafo(){
    calcular_niveles();
    int i, j, mayor = -1;
    for(i = 1; i <= num_vertices_actual; i++)
        if(niveles[i] > mayor) mayor = niveles[i];
    for(i = 0; i <= mayor; i++){
        printf("Nivel %d:\n", i);
        for(j = 1; j <= num_vertices_actual; j++)
            if(niveles[j] == i)
                printf("  %s\n", nombres[j]);
        imprimir_separado();
    }
}

void ingresar_sistema(){
    int i, desde, hasta, mas_conexiones, n;
    char nombre_temp[256];

    system("cls");
    imprimir_separado();
    printf(" INGRESAR SISTEMA PERSONALIZADO\n");
    imprimir_separado();

    printf("\n  Cuantos componentes tiene su sistema? (minimo 1): ");
    n = validar_entero();
    while(n < 1){
        printf("  Numero invalido. Ingrese al menos 1: ");
        n = validar_entero();
    }

    num_vertices_actual = n;
    reservar_memoria(n);   

    printf("\n  Ingrese el nombre de cada componente:\n\n");
    for(i = 1; i <= n; i++){
        printf("  Nombre del componente %d: ", i);
        fflush(stdin);
        fgets(nombre_temp, sizeof(nombre_temp), stdin);
        nombre_temp[strcspn(nombre_temp, "\n")] = 0;
        if(strlen(nombre_temp) == 0)
            snprintf(nombres[i], NOMBRE_MAX, "Componente%d", i);
        else{
            strncpy(nombres[i], nombre_temp, NOMBRE_MAX - 1);
            nombres[i][NOMBRE_MAX - 1] = '\0';
        }
    }

    printf("\n  Ingrese las conexiones (quien depende de quien).\n");
    printf("  Formato: Componente origen y componente destino.\n\n");
    do {
        printf("  Componente que depende (origen, 1-%d): ", n);
        desde = validar_entero();
        while(desde < 1 || desde > n){
            printf("  Invalido. Ingrese entre 1 y %d: ", n);
            desde = validar_entero();
        }

        printf(" Componente del que depende (destino, 1-%d): ", n);
        hasta = validar_entero();
        while(hasta < 1 || hasta > n || hasta == desde){
            if(hasta == desde)
                printf("  Un componente no puede depender de si mismo. Ingrese otro: ");
            else
                printf("  Invalido. Ingrese entre 1 y %d: ", n);
            hasta = validar_entero();
        }

        grafo[desde][hasta] = 1;
        printf("  Conexion agregada: V%d %s -> V%d %s\n\n",
               desde, nombres[desde], hasta, nombres[hasta]);

        printf("  Agregar otra conexion? (1=Si, 0=No): ");
        mas_conexiones = validar_entero();
    } while(mas_conexiones == 1);

    printf("\n  Sistema personalizado cargado con %d componentes.\n", n);
}


int main(){
    srand(time(NULL));
    int modo, opcion, nodo, nodo_obtenido;

    do {
        system("cls");
        imprimir_separado();
        printf(" SISTEMA DE ANALISIS DE DEPENDENCIAS DE SOFTWARE\n");
        imprimir_separado();
        printf("  Seleccione el sistema a analizar:\n\n");
        printf("  1. Sistema predefinido\n");
        printf("  2. Ingresar sistema personalizado\n");
        printf("  0. Salir\n");
        imprimir_separado();
        printf("Seleccione una opcion: ");
        modo = validar_entero();
    } while(modo < 0 || modo > 2);

    if(modo == 0){ liberar_memoria(); return 0; }

    if(modo == 1){
        num_vertices_actual = NUM_VERTICES;
        reservar_memoria(num_vertices_actual);
        inicializar_nombres();
        inicializar_grafo();
    } else {
        ingresar_sistema();
    }

    do {
        printf("\n");
        imprimir_separado();
        printf(" SISTEMA DE ANALISIS DE DEPENDENCIAS DE SOFTWARE\n");
        imprimir_separado();
        printf("  1. Detectar componente critico (grado de entrada)\n");
        printf("  2. Rastrear impacto de un fallo (DFS)\n");
        printf("  3. Priorizar correcciones desde un fallo (BFS)\n");
        printf("  4. Ver lista de componentes\n");
        printf("  5. Visualizar grafo completo por niveles\n");
        printf("  6. Simular fallo automatico\n");
        printf("  7. Cambiar sistema\n");
        printf("  0. Salir\n");
        imprimir_separado();
        printf("Seleccione una opcion: ");
        opcion = validar_entero();

        switch(opcion){
            case 1:
                system("cls");
                nodo = calcular_nodo_critico();
                printf("El componente critico es: V%d %s\n", nodo, nombres[nodo]);
                break;
            case 2:
                system("cls");
                mostrar_nodos();
                printf("  Numero del componente fallido (1-%d): ", num_vertices_actual);
                nodo = validar_entero();
                if(nodo >= 1 && nodo <= num_vertices_actual)
                    rastrear_impacto(nodo);
                else
                    printf("  Numero invalido.\n");
                break;
            case 3:
                system("cls");
                mostrar_nodos();
                printf("  Numero del componente fallido (1-%d): ", num_vertices_actual);
                nodo = validar_entero();
                if(nodo >= 1 && nodo <= num_vertices_actual)
                    priorizar_correcciones(nodo);
                else
                    printf("  Numero invalido.\n");
                break;
            case 4:
                system("cls");
                mostrar_nodos();
                break;
            case 5:
                system("cls");
                mostrar_grafo();
                break;
            case 6:
                system("cls");
                nodo_obtenido = (rand() % (num_vertices_actual - 1)) + 2;
                printf("\n  [ALERTA] Fallo detectado en: V%d %s\n\n",
                       nodo_obtenido, nombres[nodo_obtenido]);
                rastrear_impacto(nodo_obtenido);
                priorizar_correcciones(nodo_obtenido);
                break;
            case 7:
                liberar_memoria();
                main();
                return 0;
            case 0:
                system("cls");
                printf("\n Terminando programa \n\n");
                break;
            default:
                system("cls");
                printf("\n Opcion invalida \n");
        }
    } while(opcion != 0);

    liberar_memoria();
    return 0;
}
