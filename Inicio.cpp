#include <stdio.h>
#define NUM_MAX_FUENTES 1000
struct Tfuente {
	int numfuente;
	float ph;	
	int conductividad, turbidez, coliformes, mes, annyo;
	int incluido; //Sera 0 predeterminado. Si la fuente se usara para alguna estdistica, se cambiara incluido=1.
}; 

void reset(struct Tfuente[], int, int); //Funcion para resetear la variable "incluido", usada para estadisticas


int main() {
//ALMACENAMOS DATOS DADOS
//al a�adir variables de mes y a�o(para que al introducir datos nuevos se distingan entre ellos, establecemos los datos iniciales dados, con mes y a�o abril 2023
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
		printf("Seleccione una opcion:\n 1-Annyadir nuevos datos\n 2-Busqueda de datos\n 3-Diferencia entre annyos\n 4-Estadisticas\n 5-Comparacion\n 6-Salir \n");
		scanf("%d", &a);
		contador++;
		switch (a) {
			case(1): {
				int mes_nuevo, annyo_nuevo, ndatos_nuevo, x, b;
				char nombreFichero[250];
				sprintf(nombreFichero, "trabajodatos%d_nuevos.txt",contador);
				FILE *fsalida;
				fsalida= fopen(nombreFichero, "w");
				printf("Ha seleccionado annyadir nuevos datos, se le crearan nuevos documentos de texto para almacenar estos datos.\n\n");
				printf("Puede decidir si quiere guardar los datos para la proxima vez que abra el programa (Introduzca 1), o no, y solo trabajar con ellos esta vez(Introduzca 2): ");
				scanf("%d", &b); 
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
				nuevos datos (junto con los antiguos) en el mismo fichero que abre el programa nada m�s comenzar*/
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
						printf("Ha seleccionado la opcion de busqueda de datos\n");
						printf("seleccione en funcion de que parametro desea buscar el dato:\n 1-PH\n 2-Turbidez\n 3-Coliformes\n 4-numero de fuente\n 5-Conductividad\n 6-mes\n 7-Annyo\n");
						scanf("%d", &decision);
						switch(decision) {
							case(1): {
								float phBuscado; 
								int a;
								int decision2;
								printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
								scanf("%d", &decision2);
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
										printf("Introduzca el minimo del intervalo que desea buscar:");
										scanf("%f", &min);
										printf("Introduzca el maximo del intervalo que desea buscar: ");
										scanf("%f", &max);
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
								printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
								scanf("%d", &decision2);
								switch(decision2) {
									case(1): {
										int encontrado=0;
										printf("Introduzca la turbidez que desea buscar: ");
										scanf("%d", &turbidezBuscada);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].turbidez==turbidezBuscada && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d tiene la turbidez buscada %d: \n", fuente[a].numfuente, turbidezBuscada);
												printf("\tFuente %d\t Ph %f\t Coliformes %d\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[a].numfuente, fuente[a].ph, fuente[a].coliformes, fuente[a].conductividad, fuente[a].mes, fuente[a].annyo);
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
										printf("introduzca el minimo del intervalo que desea buscar:");
										scanf("%d", &min);
										printf("Introduzca el maximo del intervalo que desea buscar: ");
										scanf("%d", &max);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].turbidez>=min && fuente[x].turbidez<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro que la fuente %d esta en el intervalo de turbidez buscado, con una turbidez %d: \n", fuente[x].numfuente, fuente[x].turbidez );
												printf("\tFuente %d\t Ph %f\t Coliformes %d\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].conductividad, fuente[x].mes, fuente[x].annyo);
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
								printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
								scanf("%d", &decision2);
								switch(decision2) {
									case(1):{
										int encontrado=0;
										printf("Introduzca el numero de coliformes que desea buscar: ");
										scanf("%f", &ColBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].coliformes==ColBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d tiene los coliformes buscados %d: \n", fuente[a].numfuente, ColBuscado);
												printf("\tFuente %d\t Turbidez %d\t Ph %f\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].ph, fuente[a].conductividad, fuente[a].mes, fuente[a].annyo);
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
										printf("introduzca el minimo del intervalo que desea buscar:");
										scanf("%d", &min);
										printf("Introduzca el maximo del intervalo que desea buscar: ");
										scanf("%d", &max);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].coliformes>=min && fuente[x].coliformes<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro que la fuente %d esta en el intervalo de coliformes buscado, con unos coliformes %d: \n", fuente[x].numfuente, fuente[x].coliformes );
												printf("\tFuente %d\t Ph %f\t Turbidez %d\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].turbidez, fuente[x].conductividad, fuente[x].mes, fuente[x].annyo);
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
								printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
								scanf("%d", &decision2);
								switch(decision2) {
									case(1):{
										int encontrado=0;
										printf("Introduzca el numero de fuente que desea buscar: ");
										scanf("%d", &numBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].numfuente==numBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d", fuente[a].numfuente);
												printf("\tFuente %d\t Ph %f\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Mes %d\t Annyo %d\t", fuente[a].numfuente, fuente[a].ph, fuente[a].turbidez, fuente[a].coliformes, fuente[a].conductividad, fuente[a].mes, fuente[a].annyo);
												printf("\n");
											} else {
												fuente[a].incluido=0;
											}
											if(encontrado==0) {
												printf("No se ha encontrado ninguna fuente");
											}
											break;
										}
									}
									case(2): {
										int min, max;
										int x, encontrado=0;
										printf("introduzca el minimo del intervalo que desea buscar:");
										scanf("%d", &min);
										printf("Introduzca el maximo del intervalo que desea buscar: ");
										scanf("%d", &max);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].numfuente>=min && fuente[x].numfuente<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro la fuente %d en el intervalo buscado\n", fuente[x].numfuente );
												printf("\tFuente %d\t Ph %f\t coliformes %d\t Conductividad %d\t Turbidez %d\t Mes %d\t Annyo %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].conductividad, fuente[x].turbidez, fuente[x].mes, fuente[x].annyo);
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
								printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
								scanf("%d", &decision2);
								switch(decision2) {
									case(1): {
										int encontrado=0;
										printf("Introduzca la conductividad que desea buscar: ");
										scanf("%d", &conBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].conductividad==conBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d tiene la conductividad buscada %d: \n", fuente[a].numfuente, conBuscado);
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Ph %f\t Mes %d\t Annyo %d\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].coliformes, fuente[a].ph, fuente[a].mes, fuente[a].annyo);
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
										printf("introduzca el minimo del intervalo que desea buscar:");
										scanf("%d", &min);
										printf("Introduzca el maximo del intervalo que desea buscar: ");
										scanf("%d", &max);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].conductividad>=min && fuente[x].conductividad<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro que la fuente %d esta en el intervalo de conducctividad buscado, con una conductividad %d: \n", fuente[x].numfuente, fuente[x].conductividad );
												printf("\tFuente %d\t Ph %f\t Coliformes %d\t Turbidez %d\t Mes %d\t Annyo %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].turbidez, fuente[x].mes, fuente[x].annyo);
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
								printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
								scanf("%d", &decision2);
								switch(decision2) {
									case(1): {
										int encontrado=0;
										printf("Introduzca el mes que desea buscar: ");
										scanf("%d", &mesBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].mes==mesBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d es del mes buscado %d: \n", fuente[a].numfuente, mesBuscado);
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Ph %f\t Annyo %d\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].coliformes, fuente[a].conductividad, fuente[a].ph, fuente[a].annyo);
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
										printf("introduzca el minimo del intervalo que desea buscar:");
										scanf("%d", &min);
										printf("Introduzca el maximo del intervalo que desea buscar: ");
										scanf("%d", &max);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].mes>=min && fuente[x].mes<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro que la fuente %d esta en el intervalo de meses buscado, con el mes %d: \n", fuente[x].numfuente, fuente[x].mes );
												printf("\tFuente %d\t Ph %f\t Coliformes %d\t Turbidez %d\t Conductividad %d\t Annyo %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].turbidez, fuente[x].conductividad, fuente[x].annyo);
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
								printf("si desea buscar un dato especifico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
								scanf("%d", &decision2);
								switch(decision2) {
									case(1): {
										int annyoBuscado, a, encontrado=0;
										printf("Introduzca el annyo que desea buscar: ");
										scanf("%d", &annyoBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].annyo==annyoBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontro que la fuente %d pertenece al annyo buscado %f: \n", fuente[a].numfuente, annyoBuscado);
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Mes %d\t Ph %f\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].coliformes, fuente[a].conductividad, fuente[a].mes, fuente[a].ph);
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
										printf("introduzca el minimo del intervalo que desea buscar:");
										scanf("%d", &min);
										printf("Introduzca el maximo del intervalo que desea buscar: ");
										scanf("%d", &max);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].annyo>=min && fuente[x].annyo<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontro que la fuente %d esta en el intervalo de annyos buscado, con el mes %d: \n", fuente[x].numfuente, fuente[x].annyo );
												printf("\tFuente %d\t Ph %f\t Coliformes %d\t Turbidez %d\t Conductividad %d\t Mes %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].turbidez, fuente[x].conductividad, fuente[x].mes);
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
					printf("\nSi desea realizar una busqueda dentro de la ya hecha, introduzca 1, si desea por el contrario volver al menu principal introduzca 0: ");
					scanf("%d", &valor);
				}while(valor!=0);
				reset(fuente, ndatos, 0);
				break;
			}
			case(4): {
				int s, non; 
				for(s=0; s<ndatos; s++) {
					printf("introduzca el numero de la fuente de cuyo PH desea calcular la media, si no quiere introducir mas introduzca 0: "); 
					scanf("%d", &non); 
					if(non==0) {
						break; 
					}
					else{
						non--; 
						fuente[non].incluido=1;
					}
				}
				int z; 
				float media=0, cantidad=0; 
				for(z=0; z<ndatos; z++) {
					if(fuente[z].incluido==1) {
					cantidad++;
					media+=fuente[z].ph;
					}
				}
				printf("la media es %f",media/cantidad); 
				
				break;
			}
		}
		printf("\n");
	}while(a!=6);
	printf("FIN DEL PROGRAMA"); 
	
	return 0;
}




void reset (struct Tfuente matriz[], int num, int a) {
	int i; 
	for(i=0; i<num; i++) {
		matriz[i].incluido=a;
	}
}


