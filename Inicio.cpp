#include <stdio.h>
#define NUM_MAX_FUENTES 1000
struct Tfuente {
	int numfuente;
	float ph;	
	int conductividad, turbidez, coliformes, mes, annyo;
}; 


int main() {
//ALMACENAMOS DATOS DADOS
//al añadir variables de mes y año(para que al introducir datos nuevos se distingan entre ellos, establecemos los datos iniciales dados, con mes y año abril 2023
	int numfuente, conductividad, turbidez, coliformes;
	float ph; 
	int ndatos, i, mes, annyo;
	struct Tfuente fuente[NUM_MAX_FUENTES];
	
	//Abrimos el archivo de datos
	FILE *fichero;
	fichero=fopen("trabajodatos.txt", "r");
	if (fichero==NULL) {
		printf("error, no puede abrir el fichero.\n");
		return 0;
	}
	
	//leemos el archivo
	fscanf(fichero, "%d", &ndatos); //habra este numero de datos en total
	for(i=0; i<ndatos; i++) {
		fscanf(fichero,"%d %f %d %d %d %d %d", &fuente[i].numfuente, &fuente[i].ph,&fuente[i].conductividad, &fuente[i].turbidez, &fuente[i].coliformes, &fuente[i].mes, &fuente[i].annyo); 
	}
	fclose(fichero);
	
	
//COMIENZA EL PROGRAMA:
	int a, contador=0; 
	do{
		printf("seleccione una opcion:\n 1-Annyadir nuevos datos\n 2-Busqueda de datos\n 3-Diferencia entre años\n 4-Estadisticas\n 5-Comparacion\n 6-Salir \n");
		scanf("%d", &a);
		contador++;
		switch (a) {
			case(1): {
				int mes_nuevo, annyo_nuevo, ndatos_nuevo, x, b;
				printf("Ha seleccionado annyadir nuevos datos, se le crearan nuevos documentos de texto para almacenar estos datos.\n\n");
				printf("Puede decidir si quiere guardar los datos para la proxima vez que abra el programa (Introduzca 1), o no, y solo trabajar con ellos esta vez(Introduzca 2): ");
				scanf("%d", &b); 
				FILE *fsalida;
				fsalida= fopen("trabajodatos_nuevos.txt",  "w");
				if(fsalida==NULL) {
					printf("Error, no se puede crear el fichero.\n");
					return 0;
				}
				printf("Introduzca el annyo de los datos a introducir: ");
				scanf("%d", &annyo_nuevo);
				printf("Introduzca el numero de mes de los datos a introducir: ");
				scanf("%d", &mes_nuevo); 
				printf("introduzca el numero de fuentes sobre el que va a introducir datos: ");
				scanf("%d", &ndatos_nuevo);
				fprintf(fsalida, "DATOS %d-%d\n", mes_nuevo, annyo_nuevo);
				for(x=0;x<ndatos_nuevo; x++) {
					fuente[ndatos+x].mes=mes_nuevo;
					fuente[ndatos+x].annyo=annyo_nuevo;
					fuente[ndatos+x].numfuente=x+1;
					fprintf(fsalida, "%d\t", fuente[ndatos+x].numfuente);
					printf("introduzca el ph de la fuente %d: ", x+1);
					scanf("%f", &fuente[ndatos+x].ph);
					fprintf(fsalida, "%f\t", fuente[ndatos+x].ph);
					printf("introduzca la conductividad de la fuente %d: ", x+1);
					scanf("%d", &fuente[ndatos+x].conductividad);
					fprintf(fsalida, "%d\t", fuente[ndatos+x].conductividad);
					printf("introduzca la turbidez de la fuente %d: ", x+1);
					scanf("%d", &fuente[ndatos+x].turbidez);
					fprintf(fsalida, "%d\t", fuente[ndatos+x].turbidez);
					printf("introduzca los coliformes de la fuente %d: ", x+1);
					scanf("%d", &fuente[ndatos+x].coliformes);
					fprintf(fsalida, "%d\t", fuente[ndatos+x].coliformes);
					fprintf(fsalida, "\n"); 
				}
				ndatos+=ndatos_nuevo;
				fclose(fsalida);
				/*Si han seleccionado que se guarden los datos para la proxima vez, guardaremos los 
				nuevos datos (junto con los antiguos) en el mismo fichero que abre el programa nada mas comenzar*/
				if(b==1) {      		
					FILE *fsalida;
					fsalida= fopen("trabajodatos.txt", "w");
					if(fsalida==NULL) {
						printf("Error, no se puede crear el fichero.\n");
						return 0;
					}
					int j;
					fprintf(fsalida, "%d\n", ndatos);
					for(j=0; j<ndatos; j++) {
						fprintf(fsalida, "%d\t", fuente[j].numfuente);
						fprintf(fsalida, "%f\t", fuente[j].ph);
						fprintf(fsalida, "%d\t", fuente[j].conductividad);
						fprintf(fsalida, "%d\t", fuente[j].turbidez);
						fprintf(fsalida, "%d\t", fuente[j].coliformes);
						fprintf(fsalida, "%d\t", fuente[j].mes);
						fprintf(fsalida, "%d\t", fuente[j].annyo);
						fprintf(fsalida, "\n");
					}
					fclose(fsalida);
				}
				break;
			}
		}
	}while(a!=6);
	printf("FIN DEL PROGRAMA"); 
	
	return 0;
}
