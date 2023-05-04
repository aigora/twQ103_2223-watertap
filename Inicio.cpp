#include <stdio.h>
#include <cmath>
#define NUM_MAX_FUENTES 1000
struct Tfuente {
	int numfuente;
	float ph;	
	int conductividad, turbidez, coliformes, mes, annyo;
	int incluido; //Sera 0 predeterminado. Si la fuente se usara para alguna estdistica, se cambiara incluido=1.
}; 

void reset(struct Tfuente[], int, int); //Funcion para resetear la variable "incluido", usada para estadisticas
<<<<<<< Updated upstream
float fdispersionPh(int, struct Tfuente[]);
=======
float fmedia1(struct Tfuente[], float, int );
>>>>>>> Stashed changes

int main() 
{
	//preguntar el nombre
	char nombre[50];
	char apellido[50];
	printf("Buenas, ¿Cual es su nombre y apellido? \n");
	scanf("%s %s", nombre, apellido);
	fflush(stdin);
	printf("Buenas, %s %s  \n", nombre, apellido);
	printf("\n");	
//ALMACENAMOS DATOS DADOS
//al añadir variables de mes y año(para que al introducir datos nuevos se distingan entre ellos, establecemos los datos iniciales dados, con mes y año abril 2023
	int numfuente, conductividad, turbidez, coliformes;
	float ph; 
	int ndatos, i, mes, annyo;
	struct Tfuente fuente[NUM_MAX_FUENTES];
	reset(fuente,NUM_MAX_FUENTES, 0);
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
		printf("==============MENU PRINCIPAL==============\n");
		printf("Seleccione una opcion:\n 1-Annyadir nuevos datos\n 2-Busqueda de datos\n 3-Diferencia entre annyos\n 4-Estadisticas\n 5-Comparacion\n 6-Salir \n 7-Dispersion acido/base");
		scanf("%d", &a);
		switch (a) {
			case(1): {
				int n=0, n1=0, n2=0, n3=0;
				contador++;
				int mes_nuevo, annyo_nuevo, ndatos_nuevo, x, b;
				char nombreFichero[250];
				sprintf(nombreFichero, "trabajodatos%d_nuevos.txt",contador);
				FILE *fsalida;
				fsalida= fopen(nombreFichero, "w");
				do {
					n++;
					if(n>1) {
						printf("El valor intoducido es incorrecto, por favor introduzcalo de nuevo\n");
					}
					printf("Ha seleccionado annyadir nuevos datos, se le crearan nuevos documentos de texto para almacenar estos datos.\n\n");
					printf("Puede decidir si quiere guardar los datos para la proxima vez que abra el programa (Introduzca 1), o no, y solo trabajar con ellos esta vez(Introduzca 2): ");
					scanf("%d", &b);
				} while (b!=1 || b!=2); 
				if(fsalida==NULL) {
					printf("Error, no se puede crear el fichero.\n");
					return 0;
				}
				printf("Introduzca el annyo de los datos a introducir: ");
				scanf("%d", &annyo_nuevo);
				do {
					n1++;
					if(n1>1) {
						printf("Error, el mes introducido debe ser un valor entre 1 y 12\n Por favor introduzcalo de nuevo\n");
					}
					printf("Introduzca el numero de mes de los datos a introducir: ");
					scanf("%d", &mes_nuevo);
				}while (mes_nuevo>12 || mes_nuevo<1); 
				do {
					n2++;
					if(n2>1) {
						printf("Error, debe introducir al menos 1 dato nuevo\n");
					}
					printf("introduzca el numero de fuentes sobre el que va a introducir datos: ");
					scanf("%d", &ndatos_nuevo);
				}while (ndatos_nuevo<=0);
				fprintf(fsalida, "DATOS %d-%d\n", mes_nuevo, annyo_nuevo);
				for(x=0;x<ndatos_nuevo; x++) {
					fuente[ndatos+x].mes=mes_nuevo;
					fuente[ndatos+x].annyo=annyo_nuevo;
					fuente[ndatos+x].numfuente=x+1;
					fprintf(fsalida, "%d\t", fuente[ndatos+x].numfuente);
					do {
						n3++;
						if(n3>1) {
							printf("Error, el valor de ph solo puede estar entre 0 y 14. Por favor, introduzcalo de nuevo\n");
						}
						printf("introduzca el ph de la fuente %d: ", x+1);
						scanf("%f", &fuente[ndatos+x].ph);
					} while (fuente[ndatos+x].ph<0 || fuente[ndatos+x].ph>14);
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
				nuevos datos (junto con los antiguos) en el mismo fichero que abre el programa nada más comenzar*/
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
			case(2): {
				int decision, valor=1;
				reset(fuente, ndatos, 1);
				do {
						int n=0, n1=0, n2=0, n3=0;
						printf("Ha seleccionado la opcion de busqueda de datos.\n");
						do {
							n++;
							if(n>1) {
								printf("Error, el valor introducido es incorrecto. Por favor, introduzcalo de nuevo.\n");
							}
							printf("Seleccione en funcion de que parametro desea buscar el dato:\n 1-PH\n 2-Turbidez\n 3-Coliformes\n 4-Numero de fuente\n 5-Conductividad\n 6-Mes\n 7-Annyo\n");
							scanf("%d", &decision);
						} while (decision<1 || decision>7);
						switch(decision) {
							case(1): {
								float phBuscado; 
								int a;
								int decision2;
								do {
									n1++;
									if(n1>1) {
										printf("Error, el valor introducido es incorrecto. Por favor, introduzcalo de nuevo.\n");
									}
									printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
									scanf("%d", &decision2);
								} while (decision2!=1 && decision2!=2);
								switch(decision2) {
									case(1): {
										int encontrado=0;
										printf("Introduzca el ph que desea buscar: ");
										scanf("%f", &phBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].ph==phBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("Se encontro que la fuente %d tiene el ph buscado %.2f: \n", fuente[a].numfuente, phBuscado);
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].coliformes, fuente[a].conductividad, fuente[a].mes, fuente[a].annyo);
												printf("\n");
											} else {
												fuente[a].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("No se ha encontrado ninguna fuente con dicho Ph");
										}
										break;
									}
									case(2): {
										float min, max;
										int x, encontrado=0;
										do {
											n2++;
											if(n2>1) {
												printf("Error, el valor maximo es menor al valor minimo indicado.Por favor, introduzcalo de nuevo\n");
											}
											printf("Introduzca el minimo del intervalo que desea buscar:");
											scanf("%f", &min);
											printf("Introduzca el maximo del intervalo que desea buscar: ");
											scanf("%f", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].ph>=min && fuente[x].ph<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("Se encontro que la fuente %d esta en el intervalo de ph buscado, con un ph %.2f: \n", fuente[x].numfuente, fuente[x].ph );
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[x].numfuente, fuente[x].turbidez, fuente[x].coliformes, fuente[x].conductividad, fuente[x].mes, fuente[x].annyo);
												printf("\n");
											} else {
												fuente[x].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("no se ha encontrado ninguna fuente con un ph entre los valores indicados");
										}
										break;
									}
								}
								break;
							}
							case(2): {
								int turbidezBuscada, a;
								int decision2;
								do {
									n1++;
									if(n1>1) {
										printf("Error, el valor introducido es incorrecto. Por favor, introduzcalo de nuevo.\n");
									}
									printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
									scanf("%d", &decision2);
								} while (decision2!=1 && decision2!=2);
								switch(decision2) {
									case(1): {
										int encontrado=0;
										printf("Introduzca la turbidez que desea buscar: ");
										scanf("%d", &turbidezBuscada);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].turbidez==turbidezBuscada && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d tiene la turbidez buscada %d: \n", fuente[a].numfuente, turbidezBuscada);
												printf("\tFuente %d\t Ph %.2f\t Coliformes %d\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[a].numfuente, fuente[a].ph, fuente[a].coliformes, fuente[a].conductividad, fuente[a].mes, fuente[a].annyo);
												printf("\n");
											} else {
												fuente[a].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("No se ha encontrado ninguna fuente con dicha Turbidez");
										}
										break;
									}
									case(2): {
										int min, max;
										int x, encontrado=0;
										do {
											n2++;
											if(n2>1) {
												printf("Error, el valor maximo es menor al valor minimo indicado.Por favor, introduzcalo de nuevo\n");
											}
											printf("Introduzca el minimo del intervalo que desea buscar:");
											scanf("%d", &min);
											printf("Introduzca el maximo del intervalo que desea buscar: ");
											scanf("%d", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].turbidez>=min && fuente[x].turbidez<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro que la fuente %d esta en el intervalo de turbidez buscado, con una turbidez %d: \n", fuente[x].numfuente, fuente[x].turbidez );
												printf("\tFuente %d\t Ph %.2f\t Coliformes %d\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].conductividad, fuente[x].mes, fuente[x].annyo);
												printf("\n");
											} else {
												fuente[x].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("no se ha encontrado ninguna fuente con una turbidez entre los valores indicados");
										}
										break;
									}
								}
								break;
							}
							case(3): {
								int ColBuscado, a;
								int decision2;
								do {
									n1++;
									if(n1>1) {
										printf("Error, el valor introducido es incorrecto. Por favor, introduzcalo de nuevo.\n");
									}
									printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
									scanf("%d", &decision2);
								} while (decision2!=1 && decision2!=2);
								switch(decision2) {
									case(1):{
										int encontrado=0;
										printf("Introduzca el numero de coliformes que desea buscar: ");
										scanf("%f", &ColBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].coliformes==ColBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d tiene los coliformes buscados %d: \n", fuente[a].numfuente, ColBuscado);
												printf("\tFuente %d\t Turbidez %d\t Ph %.2f\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].ph, fuente[a].conductividad, fuente[a].mes, fuente[a].annyo);
												printf("\n");
											} else {
												fuente[a].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("No se ha encontrado ninguna fuente con dicho numero de coliformes");
										}
										break;
									}
									case(2): {
										int min, max;
										int x, encontrado=0;
										do {
											n2++;
											if(n2>1) {
												printf("Error, el valor maximo es menor al valor minimo indicado.Por favor, introduzcalo de nuevo\n");
											}
											printf("Introduzca el minimo del intervalo que desea buscar:");
											scanf("%d", &min);
											printf("Introduzca el maximo del intervalo que desea buscar: ");
											scanf("%d", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].coliformes>=min && fuente[x].coliformes<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro que la fuente %d esta en el intervalo de coliformes buscado, con unos coliformes %d: \n", fuente[x].numfuente, fuente[x].coliformes );
												printf("\tFuente %d\t Ph %.2f\t Turbidez %d\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].turbidez, fuente[x].conductividad, fuente[x].mes, fuente[x].annyo);
												printf("\n");
											} else {
												fuente[x].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("no se ha encontrado ninguna fuente con coliformes entre los valores indicados");
										}
										break;
									}	
								}
								break;
							}
							case(4): {
								int numBuscado, a;
								int decision2;
								do {
									n1++;
									if(n1>1) {
										printf("Error, el valor introducido es incorrecto. Por favor, introduzcalo de nuevo.\n");
									}
									printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
									scanf("%d", &decision2);
								} while (decision2!=1 && decision2!=2);
								switch(decision2) {
									case(1):{
										int encontrado=0;
										reset(fuente, ndatos, 1);
										printf("Introduzca el numero de fuente que desea buscar: ");
										scanf("%d", &numBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].numfuente==numBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d\n", fuente[a].numfuente);
												printf("\tFuente %d\t Ph %.2f\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[a].numfuente, fuente[a].ph, fuente[a].turbidez, fuente[a].coliformes, fuente[a].conductividad, fuente[a].mes, fuente[a].annyo);
												printf("\n");
											} else {
												fuente[a].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("No se ha encontrado ninguna fuente\n");
										}
										break;
										
									}
									case(2): {
										int min, max;
										int x, encontrado=0;
										do {
											n2++;
											if(n2>1) {
												printf("Error, el valor maximo es menor al valor minimo indicado.Por favor, introduzcalo de nuevo\n");
											}
											printf("Introduzca el minimo del intervalo que desea buscar:");
											scanf("%d", &min);
											printf("Introduzca el maximo del intervalo que desea buscar: ");
											scanf("%d", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].numfuente>=min && fuente[x].numfuente<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro la fuente %d en el intervalo buscado\n", fuente[x].numfuente );
												printf("\tFuente %d\t Ph %.2f\t coliformes %d\t Conductividad %d\t Turbidez %d\t Mes %d\t Annyo %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].conductividad, fuente[x].turbidez, fuente[x].mes, fuente[x].annyo);
												printf("\n");
											} else {
												fuente[x].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("no se ha encontrado ninguna fuente entre los valores indicados");
										}
										break;
									}	
								}		
								break;
							}
							case(5): {
								int conBuscado, a;
								int decision2;
								do {
									n1++;
									if(n1>1) {
										printf("Error, el valor introducido es incorrecto. Por favor, introduzcalo de nuevo.\n");
									}
									printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
									scanf("%d", &decision2);
								} while (decision2!=1 && decision2!=2);
								switch(decision2) {
									case(1): {
										int encontrado=0;
										printf("Introduzca la conductividad que desea buscar: ");
										scanf("%d", &conBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].conductividad==conBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d tiene la conductividad buscada %d: \n", fuente[a].numfuente, conBuscado);
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Ph %.2f\t Mes %d\t Annyo %d\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].coliformes, fuente[a].ph, fuente[a].mes, fuente[a].annyo);
												printf("\n");
											} else {
												fuente[a].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("No se ha encontrado ninguna fuente con dicha conductividad");
										}	
										break;
									}
									case(2): {
										int min, max;
										int x, encontrado=0;
										do {
											n2++;
											if(n2>1) {
												printf("Error, el valor maximo es menor al valor minimo indicado.Por favor, introduzcalo de nuevo\n");
											}
											printf("Introduzca el minimo del intervalo que desea buscar:");
											scanf("%d", &min);
											printf("Introduzca el maximo del intervalo que desea buscar: ");
											scanf("%d", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].conductividad>=min && fuente[x].conductividad<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro que la fuente %d esta en el intervalo de conducctividad buscado, con una conductividad %d: \n", fuente[x].numfuente, fuente[x].conductividad );
												printf("\tFuente %d\t Ph %.2f\t Coliformes %d\t Turbidez %d\t Mes %d\t Annyo %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].turbidez, fuente[x].mes, fuente[x].annyo);
												printf("\n");
											} else {
												fuente[x].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("no se ha encontrado ninguna fuente con la conductividad entre los valores indicados");
										}
										break;
									}
								}
								break;
							}
							case(6): {
								int mesBuscado, a;
								int decision2;
								do {
									n1++;
									if(n1>1) {
										printf("Error, el valor introducido es incorrecto. Por favor, introduzcalo de nuevo.\n");
									}
									printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
									scanf("%d", &decision2);
								} while (decision2!=1 && decision2!=2);
								switch(decision2) {
									case(1): {
										int encontrado=0;
										printf("Introduzca el mes que desea buscar: ");
										scanf("%d", &mesBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].mes==mesBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d es del mes buscado %d: \n", fuente[a].numfuente, mesBuscado);
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Ph %.2f\t Annyo %d\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].coliformes, fuente[a].conductividad, fuente[a].ph, fuente[a].annyo);
												printf("\n");
											} else {
												fuente[a].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("No se ha encontrado ninguna fuente perteneciente a dicho mes");
										}
										break;
									}
									case(2): {
										int min, max;
										int x, encontrado=0;
										do {
											n2++;
											if(n2>1) {
												printf("Error, el valor maximo es menor al valor minimo indicado.Por favor, introduzcalo de nuevo\n");
											}
											printf("Introduzca el minimo del intervalo que desea buscar:");
											scanf("%d", &min);
											printf("Introduzca el maximo del intervalo que desea buscar: ");
											scanf("%d", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].mes>=min && fuente[x].mes<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro que la fuente %d esta en el intervalo de meses buscado, con el mes %d: \n", fuente[x].numfuente, fuente[x].mes );
												printf("\tFuente %d\t Ph %.2f\t Coliformes %d\t Turbidez %d\t Conductividad %d\t Annyo %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].turbidez, fuente[x].conductividad, fuente[x].annyo);
												printf("\n");
											} else {
												fuente[x].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("no se ha encontrado ninguna fuente con la conductividad entre los valores indicados");
										}	
										break;
									}	
								}
								break;
							}
							case(7): {
								int decision2;
								do {
									n1++;
									if(n1>1) {
										printf("Error, el valor introducido es incorrecto. Por favor, introduzcalo de nuevo.\n");
									}
									printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
									scanf("%d", &decision2);
								} while (decision2!=1 && decision2!=2);
								switch(decision2) {
									case(1): {
										int annyoBuscado, a, encontrado=0;
										printf("Introduzca el annyo que desea buscar: ");
										scanf("%d", &annyoBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].annyo==annyoBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d pertenece al annyo buscado %f: \n", fuente[a].numfuente, annyoBuscado);
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Mes %d\t Ph %.2f\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].coliformes, fuente[a].conductividad, fuente[a].mes, fuente[a].ph);
												printf("\n");
											} else {
												fuente[a].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("No se ha encontrado ninguna fuente con dicho Ph");
										}
										break;
									}
									case(2): {
										int min, max;
										int x, encontrado=0;
										do {
											n2++;
											if(n2>1) {
												printf("Error, el valor maximo es menor al valor minimo indicado.Por favor, introduzcalo de nuevo\n");
											}
											printf("Introduzca el minimo del intervalo que desea buscar:");
											scanf("%d", &min);
											printf("Introduzca el maximo del intervalo que desea buscar: ");
											scanf("%d", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].annyo>=min && fuente[x].annyo<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro que la fuente %d esta en el intervalo de annyos buscado, con el mes %d: \n", fuente[x].numfuente, fuente[x].annyo );
												printf("\tFuente %d\t Ph %.2f\t Coliformes %d\t Turbidez %d\t Conductividad %d\t Mes %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].turbidez, fuente[x].conductividad, fuente[x].mes);
												printf("\n");
											} else {
												fuente[x].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("no se ha encontrado ninguna fuente con la conductividad entre los valores indicados");
										}	
										break;
									}
								}
								break;
							}
						}
					do {
						n3++;
						if(n3>1) {
							printf("Error, el valor introducido es incorrecto. Por favor, introduzcalo de nuevo\n");
						}
						printf("\nSi desea realizar una busqueda dentro de la ya hecha, introduzca 1, si desea por el contrario volver al menu principal introduzca 0: ");
						scanf("%d", &valor);
					} while (valor!=1 && valor!=0);
				}while(valor!=0);
				reset(fuente, ndatos, 0);
				break;
			}
			case(4): {
				int opcion;
				int salirDelPrograma;
				int md, sobremd, est;
				float media, mediana, b;
				printf("Ha seleccionado la opcion de las estadisticas.\n");
				printf("========= MENU ESTADISTICAS =========\n");
				FILE *fsalida;
				fsalida= fopen("trabajodatos.txt", "r");
				if(fsalida==NULL) {
					printf("Error, no se puede abrir el fichero.\n");
					return 0;
				}
				do { 
    				printf("Elige una opcion que desee\n");
    				printf("1: Ver todas las estadisticas\n");
    				printf("2: Media \n");
    				printf("3: Mediana \n");
    				printf("4: Salir de estadisticas.\n");
    				scanf("%d", &opcion);
					
					switch (opcion) {
						case 1:
							printf("========= TODAS LAS ESTADISTICAS =========  \n");
							printf("Puede ser de todas las fuentes (Introduzca 1), de fuentes seleccionadas (Introduzca 2), o en un intervalo (Introduzca 3) \n");
							scanf("%d", &est);
							break;
						case 2:
							printf("========= MEDIA =========  \n");
							printf("Puede ver la media de todas las fuentes (Introduzca 1), de fuentes seleccionadas (Introduzca 2), en un intervalo (Introduzca 3)\n");
							scanf("%d", &md);
							int s, non;
							printf("Puede calcular la media de ph (1), conductividad (2), turbidez (3), coliformes (4)  \n");
							scanf("%d", &sobremd);
							//ph 1
							if(md == 1 && sobremd == 1) {
								int z; 
								float phMax=0, media, cantidad=0;
								media=fmedia1(fuentes, ndatos); 	
							/*	for(z=0; z<ndatos; z++) {
									cantidad++;
									media+=fuente[z].ph;
									if (fuente[z].ph > phMax) {
										phMax = fuente[z].ph;
									}	
								} */
								printf("La media de pH es: %.2f\n", fmedia1 / ndatos);
								printf("El pH maximo es: %.2f\n", phMax);
							}
							//ph 2
							else if(md == 2 && sobremd == 1) {
								for (i=0; i<ndatos; i++) {
									printf("Introduzca el numero de la fuente cuyo pH desea calcular LA media (minimo 2), si no quiere introducir mas pulse el 0. \n");
									scanf("%d", &non);
									if(non==0) {
										break;
									} else {
										non--;
										fuente[non].incluido=1;									
									}
								}
								int z; 
								float phMax=0, media, cantidad=0;	
								for(z=0; z<ndatos; z++) {
									if (fuente[z].incluido==1) {
										cantidad++;
										media+=fuente[z].ph;
										if (fuente[z].ph > phMax) {
											phMax = fuente[z].ph;
										}	
									}	
								}
								printf("La media de pH es: %.2f\n", media / cantidad);
								printf("El pH maximo es: %.2f\n", phMax);
							}
							//conductividad 1
							else if(md == 1 && sobremd == 2) {
								int z; 
								float condMax=0, media, cantidad=0;	
								for(z=0; z<ndatos; z++) {
									cantidad++;
									media+=fuente[z].conductividad;
									if (fuente[z].conductividad > condMax) {
										condMax = fuente[z].conductividad;
									}	
								}
								printf("La media de conductividad es: %.2f\n", media / ndatos);
								printf("La conductividad maxima es: %.2f\n", condMax);
							}else if(md==2 && sobremd==2) {
								for (i=0; i<ndatos; i++) {
									printf("Introduzca el numero de la fuente cuya conductividad desea calcular la media (minimo 2), si no quiere introducir mas pulse el 0. \n");
									scanf("%d", &non);
									if(non==0) {
										break;
									} else {
										non--;
										fuente[non].incluido=1;									
									}
								}
								int z; 
								float condMax=0, media, cantidad=0;	
								for(z=0; z<ndatos; z++) {
									if (fuente[z].incluido==1) {
										cantidad++;
										media+=fuente[z].conductividad;
										if (fuente[z].conductividad > condMax) {
											condMax = fuente[z].conductividad;
										}	
									}	
								}
								printf("La media de conductividad es: %.2f\n", media / cantidad);
								printf("La conductividad maxima es: %.2f\n", condMax);
							}
							//turbidez 1
							if(md == 1 && sobremd == 3) {
								int z; 
								float turMax=0, media, cantidad=0;	
								for(z=0; z<ndatos; z++) {
									cantidad++;
									media+=fuente[z].turbidez;
									if (fuente[z].turbidez > turMax) {
										turMax = fuente[z].turbidez;
									}	
								}
								printf("La media de turbidez es: %.2f\n", media / ndatos);
								printf("La turbidez maxima es: %.2f\n", turMax);
							}
							//turbidez 2
							if(md == 2 && sobremd == 3) {
								for (i=0; i<ndatos; i++) {
									printf("Introduzca el numero de la fuente cuyo pH desea calcular la media (minimo 2), si no quiere introducir mas pulse el 0. \n");
									scanf("%d", &non);
									if(non==0) {
										break;
									} else {
										non--;
										fuente[non].incluido=1;									
									}
								}
								int z; 
								float turMax=0, media, cantidad=0;	
								for(z=0; z<ndatos; z++) {
									if (fuente[z].incluido==1) {
										cantidad++;
										media+=fuente[z].turbidez;
										if (fuente[z].turbidez > turMax) {
											turMax = fuente[z].turbidez;
										}	
									}	
								}
								printf("La media de turbidez es: %.2f\n", media / cantidad);
								printf("La turbidez maxima es: %.2f\n", turMax);
							}
							//coliformes 1
							if(md == 1 && sobremd == 4) {
								int z; 
								float coliMax=0, media, cantidad=0;	
								for(z=0; z<ndatos; z++) {
									cantidad++;
									media+=fuente[z].coliformes;
									if (fuente[z].coliformes > coliMax) {
										coliMax = fuente[z].coliformes;
									}	
								}
								printf("La media de coliformes es: %.2f\n", media / ndatos);
								printf("El coliforme maximo es: %.2f\n", coliMax);
							}
							//coliformes 2
							if(md == 2 && sobremd == 4) {
								for (i=0; i<ndatos; i++) {
									printf("Introduzca el numero de la fuente cuyo pH desea calcular la media (minimo 2), si no quiere introducir mas pulse el 0. \n");
									scanf("%d", &non);
									if(non==0) {
										break;
									} else {
										non--;
										fuente[non].incluido=1;									
									}
								}
								int z; 
								float coliMax=0, media, cantidad=0;	
								for(z=0; z<ndatos; z++) {
									if (fuente[z].incluido==1) {
										cantidad++;
										media+=fuente[z].coliformes;
										if (fuente[z].coliformes > coliMax) {
											coliMax = fuente[z].coliformes;
										}	
									}	
								}
								printf("La media de coliformes es: %.2f\n", media / cantidad);
								printf("El coliforme maximo es: %.2f\n", coliMax);
							}
							break;
						case 3:
							printf("========= MEDIANA =========  \n");
							printf("Puede ver la mediana de todas las fuentes (Introduzca 1), de fuentes seleccionadas (Introduzca 2), o en un intervalo (Introduzca 3)\n");
							break;
						case 4:
							printf("Ha salido de estadisticas\n");
							break;
						default:{
							printf("ERROR, la opcion no es valida\n");
							break;
						}
					}
				} while (opcion != 4);
				
					//scanf("%d", &b);	
					break;
				
				break;
			}case(6): {
				break;
			} case(7): {
				int h, A, M, valorEncontrado=0, n7=0;
				printf("Ha seleccionado medir la dispersion de los ph respecto a un ph neutro\n");		
				printf("Introduzca el numero de la fuente cuyo ph desea comparar\n");
				scanf("%d", &h);
				do{
					n7++;
					if(n7>1) {
						printf("La fuente seleccionada no tiene datos registrados para dicho mes y annyo, introduzca valores de nuevo\n");
					}	
					printf("introduzca de que mes desea coger el dato: ");
					scanf("%d", &M);
					printf("introduzca de que annyo desea coger el dato:");
					scanf("%d", &A);
					if(fuente[h-1].annyo==A) {
						if (fuente[h-1].mes==M) {
							if(fuente[h-1].numfuente==h) {
								valorEncontrado=1;	
							} 
						}
					}
				} while (valorEncontrado==0);
				h--;
				printf("La dispersion del ph con respecto a un ph neutro es %.2f por ciento\n",fdispersionPh(h, fuente));	
				if(fuente[h].ph>7) {
					printf("La fuente tiene un ph basico");
				} else if (fuente[h].ph<7) {
					printf("la fuente tiene un ph acido");
				} else {
					printf("La fuente tiene un ph neutro");
				}
				break;
			}
			default: {
				printf("El valor introducido es incorrecto, por favor vuelva a introducirlo:");
				break;
			}
		}
		printf("\n");
	}while(a!=6);
	printf("FIN DEL PROGRAMA"); 
	
	return 0;

}

float fdispersionPh(int n, struct Tfuente fuente[]) {
	if(fuente[n].ph<7) {
		return ((7-fuente[n].ph)*100)/7;
	} else {
		return ((fuente[n].ph-7)*100)/7;	
	}
}


void reset (struct Tfuente matriz[], int num, int a) {
	int i; 
	for(i=0; i<num; i++) {
		matriz[i].incluido=a;
	}
}
float fmedia1(float fuente[z].ph, int ndatos ) {
	for(z=0; z<ndatos; z++) {
		cantidad++;
		media+=fuente[z].ph;
		if (fuente[z].ph > phMax) {
		phMax = fuente[z].ph;
		}	
	}	
}

