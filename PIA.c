#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NODOS 22
#define NUM_VERTICES 21
#define NOMBRE_MAX 30

int num_nodos = MAX_NODOS;
char nombres[MAX_NODOS][NOMBRE_MAX];
int grafo[MAX_NODOS][MAX_NODOS];

void inicializar_nombres(){
	strcpy(nombres[1], "Programa");
	strcpy(nombres[2], "PiezaRed");
	strcpy(nombres[3], "PiezaUtils");
	strcpy(nombres[4], "PiezaHTTP");
	strcpy(nombres[5], "LectorDatos");
	strcpy(nombres[6], "ManejadorRutas");
	strcpy(nombres[7], "ProcesadorConsultas");
	strcpy(nombres[8], "EnviadorArchivos");
	strcpy(nombres[9], "ManejadorRedireccion");
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
	for(i = 0; i < MAX_NODOS; i++){
		for(j = 0; j < MAX_NODOS; j++){
			grafo[i][j] = 0;
		}
	}
	
	//V1 Programa
	grafo[1][2]=1; 
	grafo[1][3]=1;  
	grafo[1][4]=1;
	
	//V2 PiezaRed
	grafo[2][5]=1; 
	grafo[2][6]=1; 
	grafo[2][7]=1; 
	grafo[2][8]=1; 
	grafo[2][21]=1;
	
	//V4 PiezaHTTP
	grafo[4][8]=1; 
	grafo[4][9]=1; 
	
	//V5 LectorDatos
	grafo[5][10]=1; 
	grafo[5][11]=1; 
	grafo[5][12]=1; 
	grafo[5][13]=1; 
	
	//V7 ProcesadorConsultas
	grafo[7][11]=1; 
	grafo[7][13]=1; 
	
	//V8 EnviadorArchivos
	grafo[8][13]=1;
	grafo[8][14]=1;
	grafo[8][15]=1;   
	
	//V11 RegistradorEventos
	grafo[11][16]=1;   
	
	//V12 ConvertidoTexto
	grafo[12][17]=1;   
	
	//V13 IdentificadorFormato
	grafo[13][18]=1;
	
	//V14 EjecutorTareas
	grafo[14][19]=1;
	grafo[14][20]=1;      
}

void imprimir_separado(){
	printf("===============================\n");
}

void titulo(const char *titulo){
	printf("====================\n  %s\n====================\n", titulo);	
}

void mostrar_nodos() {
	int i;
    printf("\n  Nodos disponibles:\n");
    for (i = 1; i <= NUM_VERTICES; i++) {
        const char *marca = (i == 11 || i == 13) ? " ***" : "";
        printf("    [V%-2d] %s%s\n", i, nombres[i], marca);
    }
    printf("  (*** = nodo critico)\n\n");
}

int main(){
	inicializar_nombres();
	inicializar_grafo();
	srand(time(NULL));
	
	int opcion, nodo;
	
	do{
		printf("\n");
		imprimir_separado();
		printf(" SISTEMA DE ANALISIS DE DEPENDENCIAS DE SOFTWARE\n");
		imprimir_separado();
		printf("  1. Detectar nodo critico (grado de entrada)\n");
		printf("  2. Rastrear impacto de un fallo (DFS)\n");
		printf("  3. Priorizar correcciones desde un fallo (BFS)\n");
        printf("  4. Ver lista de componentes\n");
        printf("  5. Visualizar grafo completo por niveles\n");
        printf("  6. Simular fallo automatico\n");
        printf("  0. Salir\n");
        imprimir_separado();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion){
        	case 1:
        		// PERSONA 2 calcular_nodo_critico();
        		break;
        	case 2:
        		mostrar_nodos();
        		printf("  Numero del componente fallido (1-%d): ", NUM_VERTICES);
                scanf("%d", &nodo);
                if (nodo >= 1 && nodo <= NUM_VERTICES)
                    // PERSONA 3 rastrear_impacto(nodo);
                    printf("  [funcion DFS pendiente]\n");
                else
                    printf("  Numero invalido.\n");
                break;
            case 3:
            	mostrar_nodos();
                printf("  Numero del componente fallido (1-%d): ", NUM_VERTICES);
                scanf("%d", &nodo);
                if (nodo >= 1 && nodo <= NUM_VERTICES)
                    // PERSONA 3  priorizar_correcciones(nodo);
                    printf("  [funcion BFS pendiente]\n");
                else
                    printf("  Numero invalido.\n");
                break;
            case 4:
            	mostrar_nodos();
            	break;
            case 5:
            	// PERSONA 2  mostrar_grafo();
            	break;
            case 6:
            	//PERSONA 2 simular_fallo();
            	break;
            case 0:
            	printf("\n Terminando programa \n\n");
            	break;
            default:
            	printf("\n Opcion invalida \n");
		}
		
	}while (opcion != 0);
	
	return 0; 
}
