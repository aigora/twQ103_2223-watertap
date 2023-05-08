#include <stdio.h>
#include <math.h>
#include <locale.h> // Libreria que contiene la funcion setlocale
#define NUM_MAX_FUENTES 1000
struct Tfuente {
	int numfuente;
	float ph;	
	int conductividad, turbidez, coliformes, mes, annyo;
	int incluido; //Sera 0 predeterminado. Si la fuente se usara para alguna estdistica, se cambiara incluido=1.
	int esVolatil; //Bulleano para saber si es guardado o no para todos los programas
}; 

void reset(struct Tfuente[], int, int); //Funcion para resetear la variable "incluido", usada para estadisticas
//Funciones comparacion
float fcomparacionmayor (struct Tfuente[]);
float fcomparacionmenor (struct Tfuente[]);
void fcomparacionfuentes (struct Tfuente[]); 

float fdispersionPh(int, struct Tfuente[]);
//Funciones medias variables al cuadrado
float fmedia2ph(struct Tfuente[], int);
float fmedia2cond(struct Tfuente[],int);
float fmedia2turb(struct Tfuente[], int);
float fmedia2colif(struct Tfuente[], int);
//Funiones de medias de dos variables
float fmediaCondPh(struct Tfuente[], int);
float fmediaTurbPh(struct Tfuente[], int);
float fmediaColifPh(struct Tfuente[], int);
float fmediaCondTurb(struct Tfuente[], int);
float fmediaCondColif(struct Tfuente[], int);
float fmediaTurbColif(struct Tfuente[], int);
//Funciones valor de la media
float fmediaCond(struct Tfuente[], int);
float fmediaPh(struct Tfuente[], int);
float fmediaTurb(struct Tfuente[], int);
float fmediaCol(struct Tfuente[], int);

//Funciones media para estadisticas
void fmediaph11(struct Tfuente[],int ndatos);
void fmediacond2(struct Tfuente[],int ndatos);
void fmediaturb2(struct Tfuente[], int ndatos);
void fmediacoliformes2(struct Tfuente[],int ndatos);


int main() 
{	
	setlocale(LC_CTYPE, "spanish"); // para que el compilador reconozca las � y tildes 
	//preguntar el nombre y apellido
	char nombre[50];
	char apellido[50];
	printf("Buenas, �Cu�l es su nombre y apellido? \n");
	scanf("%s %s", nombre, apellido);
	fflush(stdin);
	printf("Buenas, %s %s  \n", nombre, apellido);
	printf("\n");	
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
		printf("Error, no puede abrir el fichero.\n");
		return 0;
	}
	
	//leemos el archivo
	fscanf(fichero, "%d", &ndatos); //habr� este numero de datos en total
	for(i=0; i<ndatos; i++) {
		fscanf(fichero,"%d %f %d %d %d %d %d", &fuente[i].numfuente, &fuente[i].ph,&fuente[i].conductividad, &fuente[i].turbidez, &fuente[i].coliformes, &fuente[i].mes, &fuente[i].annyo); 
	}
	fclose(fichero);
	for(i=0; i<ndatos; i++) {
		fuente[i].esVolatil=0;
	}
	
//COMIENZA EL PROGRAMA:
	int a, contador=0; 
	do{
		printf("****************************** MEN� PRINCIPAL ******************************\n");
		printf("Seleccione una opcion:\n \t\t\t1-A�adir nuevos datos\n \t\t\t2-B�squeda de datos\n \t\t\t3-Diferencia entre a�os\n \t\t\t4-Estad�sticas\n \t\t\t5-Comparaci�n\n \t\t\t6-Dispersi�n PH\n \t\t\t7-Pron�sticos\n \t\t\t8-Salir\n\n");
		scanf("%d", &a);
		switch (a) {
			case(1): {
				printf("=========* A�ADIR NUEVOS DATOS *=========\n");
				int n=0, n1=0, n2=0, n3=0, numeroDatos=0, k;
				contador++;
				int mes_nuevo, annyo_nuevo, ndatos_nuevo, x, b;
				char nombreFichero[250];
				sprintf(nombreFichero, "trabajodatos%d_nuevos.txt",contador);
				FILE *fsalida;
				fsalida= fopen(nombreFichero, "w");
				do {
					n++;
					if(n>1) {
						printf("El valor intoducido es incorrecto, por favor introd�zcalo de nuevo\n");
					}
					printf("Ha seleccionado a�adir nuevos datos, se le crearan nuevos documentos de texto para almacenar estos datos.\n\n");
					printf("Puede decidir si quiere guardar los datos para la pr�xima vez que abra el programa (Introduzca 1), o no, y solo trabajar con ellos esta vez(Introduzca 2): ");
					scanf("%d", &b);
				} while (b!=1 && b!=2); 
				if(fsalida==NULL) {
					printf("Error, no se puede crear el fichero.\n");
					return 0;
				}
				printf("Introduzca el a�o de los datos a introducir: ");
				scanf("%d", &annyo_nuevo);
				do {
					n1++;
					if(n1>1) {
						printf("Error, el mes introducido debe ser un valor entre 1 y 12\n Por favor introd�zcalo de nuevo\n");
					}
					printf("Introduzca el numero de mes de los datos a introducir: ");
					scanf("%d", &mes_nuevo);
				}while (mes_nuevo>12 && mes_nuevo<1); 
				do {
					n2++;
					if(n2>1) {
						printf("Error, debe introducir al menos 1 dato nuevo\n");
					}
					printf("Introduzca el numero de fuentes sobre el que va a introducir datos: ");
					scanf("%d", &ndatos_nuevo);
				}while (ndatos_nuevo<=0);
				fprintf(fsalida, "DATOS %d-%d\n", mes_nuevo, annyo_nuevo);
				for(x=0;x<ndatos_nuevo; x++) {
					fuente[ndatos+x].mes=mes_nuevo;
					fuente[ndatos+x].annyo=annyo_nuevo;
					printf("introduzca el n�mero de la fuente: ");
					scanf("%d", &fuente[ndatos+x].numfuente);
					fprintf(fsalida, "%d\t", fuente[ndatos+x].numfuente);
					n3=0;
					do {
						n3++;
						if(n3>1) {
							printf("Error, el valor de ph solo puede estar entre 0 y 14. Por favor, introd�zcalo de nuevo\n");
						}
						printf("Introduzca el ph de la fuente %d: ", fuente[ndatos+x].numfuente);
						scanf("%f", &fuente[ndatos+x].ph);
					} while (fuente[ndatos+x].ph<0 && fuente[ndatos+x].ph>14);
					fprintf(fsalida, "%f\t", fuente[ndatos+x].ph);
					printf("Introduzca la conductividad de la fuente %d: ", fuente[ndatos+x].numfuente);
					scanf("%d", &fuente[ndatos+x].conductividad);
					fprintf(fsalida, "%d\t", fuente[ndatos+x].conductividad);
					printf("Introduzca la turbidez de la fuente %d: ", fuente[ndatos+x].numfuente);
					scanf("%d", &fuente[ndatos+x].turbidez);
					fprintf(fsalida, "%d\t", fuente[ndatos+x].turbidez);
					printf("Introduzca los coliformes de la fuente %d: ", fuente[ndatos+x].numfuente);
					scanf("%d", &fuente[ndatos+x].coliformes);
					fprintf(fsalida, "%d\t", fuente[ndatos+x].coliformes);
					fprintf(fsalida, "\n"); 
					fuente[ndatos+x].incluido=0;
					if(b==1){
						fuente[ndatos+x].esVolatil=0;
					} else {
						fuente[ndatos+x].esVolatil=1;
					}
				}
				ndatos+=ndatos_nuevo;
				fclose(fsalida);
				/*Si han seleccionado que se guarden los datos para la proxima vez, guardaremos los 
				nuevos datos (junto con los antiguos) en el mismo fichero que abre el programa nada m�s comenzar*/
				for(k=0;k<ndatos; k++) {
					if(fuente[k].esVolatil==0) {
						numeroDatos++;
					}
				}
				if(b==1) {    		
					FILE *fsalida;
					fsalida= fopen("trabajodatos.txt", "w");
					if(fsalida==NULL) {
						printf("Error, no se puede crear el fichero.\n");
						return 0;
					}
					int j;
					fprintf(fsalida, "%d\n", numeroDatos);
					for(j=0; j<ndatos; j++) {
						if(fuente[j].esVolatil==0) {
							fprintf(fsalida, "%d\t", fuente[j].numfuente);
							fprintf(fsalida, "%f\t", fuente[j].ph);
							fprintf(fsalida, "%d\t", fuente[j].conductividad);
							fprintf(fsalida, "%d\t", fuente[j].turbidez);
							fprintf(fsalida, "%d\t", fuente[j].coliformes);
							fprintf(fsalida, "%d\t", fuente[j].mes);
							fprintf(fsalida, "%d\t", fuente[j].annyo);
							fprintf(fsalida, "\n");
						}
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
						printf("Ha seleccionado la opci�n de busqueda de datos.\n");
						do {
							n++;
							if(n>1) {
								printf("Error, el valor introducido es incorrecto. Por favor, introd�zcalo de nuevo.\n");
							}
							printf("Seleccione en funci�n de que par�metro desea buscar el dato:\n 1-PH\n 2-Turbidez\n 3-Coliformes\n 4-N�mero de fuente\n 5-Conductividad\n 6-Mes\n 7-A�o\n");
							scanf("%d", &decision);
						} while (decision<1 && decision>7);
						switch(decision) {
							case(1): {
								float phBuscado; 
								int a;
								int decision2;
								do {
									n1++;
									if(n1>1) {
										printf("Error, el valor introducido es incorrecto. Por favor, introd�zcalo de nuevo.\n");
									}
									printf("si desea buscar un dato espec�fico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
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
												printf("Se encontr� que la fuente %d tiene el ph buscado %.2f: \n", fuente[a].numfuente, phBuscado);
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Mes %d\t A�o %d\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].coliformes, fuente[a].conductividad, fuente[a].mes, fuente[a].annyo);
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
												printf("Error, el valor m�ximo es menor al valor m�nimo indicado.Por favor, introd�zcalo de nuevo\n");
											}
											printf("Introduzca el m�nimo del intervalo que desea buscar:");
											scanf("%f", &min);
											printf("Introduzca el m�ximo del intervalo que desea buscar: ");
											scanf("%f", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].ph>=min && fuente[x].ph<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("Se encontr� que la fuente %d esta en el intervalo de ph buscado, con un ph %.2f: \n", fuente[x].numfuente, fuente[x].ph );
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Mes %d\t A�o %d\t", fuente[x].numfuente, fuente[x].turbidez, fuente[x].coliformes, fuente[x].conductividad, fuente[x].mes, fuente[x].annyo);
												printf("\n");
											} else {
												fuente[x].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("No se ha encontrado ninguna fuente con un ph entre los valores indicados");
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
									printf("Error, el valor introducido es incorrecto. Por favor, introd�zcalo de nuevo.\n");
								}
								printf("Si desea buscar un dato espec�fico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
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
											printf("Se encontr� que la fuente %d tiene la turbidez buscada %d: \n", fuente[a].numfuente, turbidezBuscada);
											printf("\tFuente %d\t Ph %.2f\t Coliformes %d\t Conductividad %d\t Mes %d\t A�o %d\t", fuente[a].numfuente, fuente[a].ph, fuente[a].coliformes, fuente[a].conductividad, fuente[a].mes, fuente[a].annyo);
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
											printf("Error, el valor m�ximo es menor al valor minimo indicado.Por favor, introd�zcalo de nuevo\n");
										}
										printf("Introduzca el m�nimo del intervalo que desea buscar:");
										scanf("%d", &min);
										printf("Introduzca el m�ximo del intervalo que desea buscar: ");
										scanf("%d", &max);
									} while (max<min);
									for(x=0; x<ndatos; x++) {
										if(fuente[x].turbidez>=min && fuente[x].turbidez<=max && fuente[x].incluido==1) {
											encontrado=1;
											printf("Se encontr� que la fuente %d esta en el intervalo de turbidez buscado, con una turbidez %d: \n", fuente[x].numfuente, fuente[x].turbidez );
											printf("\tFuente %d\t Ph %.2f\t Coliformes %d\t Conductividad %d\t Mes %d\t A�o %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].conductividad, fuente[x].mes, fuente[x].annyo);
											printf("\n");
										} else {
											fuente[x].incluido=0;
										}
									}
									if(encontrado==0) {
										printf("No se ha encontrado ninguna fuente con una turbidez entre los valores indicados");
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
									printf("Error, el valor introducido es incorrecto. Por favor, introd�zcalo de nuevo.\n");
								}
								printf("Si desea buscar un dato espec�fico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
								scanf("%d", &decision2);
							} while (decision2!=1 && decision2!=2);
							switch(decision2) {
								case(1):{
									int encontrado=0;
									printf("Introduzca el n�mero de coliformes que desea buscar: ");
									scanf("%f", &ColBuscado);
									for(a=0; a<ndatos; a++) {
										if(fuente[a].coliformes==ColBuscado && fuente[a].incluido==1) {
											encontrado=1; 
											printf("Se encontr� que la fuente %d tiene los coliformes buscados %d: \n", fuente[a].numfuente, ColBuscado);
											printf("\tFuente %d\t Turbidez %d\t Ph %.2f\t Conductividad %d\t Mes %d\t A�o %d\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].ph, fuente[a].conductividad, fuente[a].mes, fuente[a].annyo);
											printf("\n");
										} else {
											fuente[a].incluido=0;
										}
									}
									if(encontrado==0) {
										printf("No se ha encontrado ninguna fuente con dicho n�mero de coliformes");
									}
									break;
								}
								case(2): {
									int min, max;
									int x, encontrado=0;
									do {
										n2++;
										if(n2>1) {
											printf("Error, el valor m�ximo es menor al valor m�nimo indicado.Por favor, introd�zcalo de nuevo\n");
										}
										printf("Introduzca el m�nimo del intervalo que desea buscar:");
										scanf("%d", &min);
										printf("Introduzca el m�ximo del intervalo que desea buscar: ");
										scanf("%d", &max);
									} while (max<min);
									for(x=0; x<ndatos; x++) {
										if(fuente[x].coliformes>=min && fuente[x].coliformes<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontr� que la fuente %d esta en el intervalo de coliformes buscado, con unos coliformes %d: \n", fuente[x].numfuente, fuente[x].coliformes );
												printf("\tFuente %d\t Ph %.2f\t Turbidez %d\t Conductividad %d\t Mes %d\t A�o %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].turbidez, fuente[x].conductividad, fuente[x].mes, fuente[x].annyo);
												printf("\n");
											} else {
												fuente[x].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("No se ha encontrado ninguna fuente con coliformes entre los valores indicados");
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
										printf("Error, el valor introducido es incorrecto. Por favor, introd�zcalo de nuevo.\n");
									}
									printf("Si desea buscar un dato espec�fico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
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
												printf("Se encontr� que la fuente %d\n", fuente[a].numfuente);
												printf("\tFuente %d\t Ph %.2f\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Mes %d\t A�o %d\t", fuente[a].numfuente, fuente[a].ph, fuente[a].turbidez, fuente[a].coliformes, fuente[a].conductividad, fuente[a].mes, fuente[a].annyo);
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
												printf("Error, el valor m�ximo es menor al valor m�nimo indicado.Por favor, introd�zcalo de nuevo\n");
											}
											printf("Introduzca el m�nimo del intervalo que desea buscar:");
											scanf("%d", &min);
											printf("Introduzca el m�ximo del intervalo que desea buscar: ");
											scanf("%d", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].numfuente>=min && fuente[x].numfuente<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("Se encontr� la fuente %d en el intervalo buscado\n", fuente[x].numfuente );
												printf("\tFuente %d\t Ph %.2f\t coliformes %d\t Conductividad %d\t Turbidez %d\t Mes %d\t A�o %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].conductividad, fuente[x].turbidez, fuente[x].mes, fuente[x].annyo);
												printf("\n");
											} else {
												fuente[x].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("No se ha encontrado ninguna fuente entre los valores indicados");
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
										printf("Error, el valor introducido es incorrecto. Por favor, introd�zcalo de nuevo.\n");
									}
									printf("Si desea buscar un dato espec�fico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
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
												printf("Se encontro que la fuente %d tiene la conductividad buscada %d: \n", fuente[a].numfuente, conBuscado);
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Ph %.2f\t Mes %d\t A�o %d\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].coliformes, fuente[a].ph, fuente[a].mes, fuente[a].annyo);
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
												printf("Error, el valor m�ximo es menor al valor m�nimo indicado.Por favor, introd�zcalo de nuevo\n");
											}
											printf("Introduzca el m�nimo del intervalo que desea buscar:");
											scanf("%d", &min);
											printf("Introduzca el m�ximo del intervalo que desea buscar: ");
											scanf("%d", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].conductividad>=min && fuente[x].conductividad<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("Se encontr� que la fuente %d esta en el intervalo de conducctividad buscado, con una conductividad %d: \n", fuente[x].numfuente, fuente[x].conductividad );
												printf("\tFuente %d\t Ph %.2f\t Coliformes %d\t Turbidez %d\t Mes %d\t A�o %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].turbidez, fuente[x].mes, fuente[x].annyo);
												printf("\n");
											} else {
												fuente[x].incluido=0;
											}
										}
										if(encontrado==0) {
											printf("No se ha encontrado ninguna fuente con la conductividad entre los valores indicados");
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
										printf("Error, el valor introducido es incorrecto. Por favor, introd�zcalo de nuevo.\n");
									}
									printf("Si desea buscar un dato espec�fico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
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
												printf("se encontr� que la fuente %d es del mes buscado %d: \n", fuente[a].numfuente, mesBuscado);
												printf("\tFuente %d\t Turbidez %d\t Coliformes %d\t Conductividad %d\t Ph %.2f\t A�o %d\t", fuente[a].numfuente, fuente[a].turbidez, fuente[a].coliformes, fuente[a].conductividad, fuente[a].ph, fuente[a].annyo);
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
												printf("Error, el valor m�ximo es menor al valor m�nimo indicado.Por favor, introd�zcalo de nuevo\n");
											}
											printf("Introduzca el m�nimo del intervalo que desea buscar:");
											scanf("%d", &min);
											printf("Introduzca el m�ximo del intervalo que desea buscar: ");
											scanf("%d", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].mes>=min && fuente[x].mes<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontr� que la fuente %d est� en el intervalo de meses buscado, con el mes %d: \n", fuente[x].numfuente, fuente[x].mes );
												printf("\tFuente %d\t Ph %.2f\t Coliformes %d\t Turbidez %d\t Conductividad %d\t A�o %d\t", fuente[x].numfuente, fuente[x].ph, fuente[x].coliformes, fuente[x].turbidez, fuente[x].conductividad, fuente[x].annyo);
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
										printf("Error, el valor introducido es incorrecto. Por favor, introd�zcalo de nuevo.\n");
									}
									printf("si desea buscar un dato espec�fico introduzca 1, si desea buscar un intervalo de datos, introduzca 2:");
									scanf("%d", &decision2);
								} while (decision2!=1 && decision2!=2);
								switch(decision2) {
									case(1): {
										int annyoBuscado, a, encontrado=0;
										printf("Introduzca el a�o que desea buscar: ");
										scanf("%d", &annyoBuscado);
										for(a=0; a<ndatos; a++) {
											if(fuente[a].annyo==annyoBuscado && fuente[a].incluido==1) {
												encontrado=1; 
												printf("se encontr� que la fuente %d pertenece al annyo buscado %f: \n", fuente[a].numfuente, annyoBuscado);
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
												printf("Error, el valor m�ximo es menor al valor m�nimo indicado.Por favor, introd�zcalo de nuevo\n");
											}
											printf("Introduzca el m�nimo del intervalo que desea buscar:");
											scanf("%d", &min);
											printf("Introduzca el m�ximo del intervalo que desea buscar: ");
											scanf("%d", &max);
										} while (max<min);
										for(x=0; x<ndatos; x++) {
											if(fuente[x].annyo>=min && fuente[x].annyo<=max && fuente[x].incluido==1) {
												encontrado=1;
												printf("se encontr� que la fuente %d esta en el intervalo de a�os buscado, con el mes %d: \n", fuente[x].numfuente, fuente[x].annyo );
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
							printf("Error, el valor introducido es incorrecto. Por favor, introd�zcalo de nuevo\n");
						}
						printf("\nSi desea realizar una b�squeda dentro de la ya hecha, introduzca 1, si desea por el contrario volver al men� principal introduzca 0: ");
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
				printf("Ha seleccionado la opcion de las estad�sticas.\n");
				printf("=========* MENU ESTAD�STICAS *=========\n");
				FILE *fsalida;
				fsalida= fopen("trabajodatos.txt", "r");
				if(fsalida==NULL) {
					printf("Error, no se puede abrir el fichero.\n");
					return 0;
				}
				do { 
    				printf("Elige una opci�n que desee\n");
    				printf("1: Ver todas las estad�sticas\n");
    				printf("2: Media \n");
    				printf("3: Mediana \n");
    				printf("4: Salir de estad�sticas.\n");
    				scanf("%d", &opcion);
					
					switch (opcion) {
						case 1:
							printf("========= TODAS LAS ESTAD�STICAS =========  \n");
							printf("Puede ser de todas las fuentes (Introduzca 1), de fuentes seleccionadas (Introduzca 2), o en un intervalo (Introduzca 3) \n");
							scanf("%d", &est);
							if(est==1) {
								reset(fuente, ndatos, 1);
								/*printf("La media de pH %.2f\n", media / ndatos);
								printf("La media de conductividad %.2f\n", media / ndatos);
								printf("La media de turbidez %.2f\n", media / ndatos);
								printf("La media de coliformes %.2f\n", media / ndatos);
								printf("El pH maximo es: %.2f\n", phMax);
								printf("La conductividad maxima es: %.2f\n", condMax);
								printf("La turbidez maxima es: %.2f\n", turMax);
								printf("El coliforme maximo es: %.2f\n", coliMax);
								*/	
							}
							else if(est==2) {
								int a;
								do{
									printf("Introduzca un n�mero de la fuente seleccionada, si no desea a�adir m�s introduzca 0");
									scanf("d", &a);
									fuente[a-1].incluido=1;
								}while(a!=0);
								
								/*printf("La media de pH %.2f\n", media / cantidad);
								printf("La media de conductividad %.2f\n", media / cantidad);
								printf("La media de turbidez %.2f\n", media / cantidad);
								printf("La media de coliformes %.2f\n", media / cantidad);
								printf("El pH maximo es: %.2f\n", phMax);
								printf("La conductividad maxima es: %.2f\n", condMax);
								printf("La turbidez maxima es: %.2f\n", turMax);
								printf("El coliforme maximo es: %.2f\n", coliMax);
								*/
							}								
							break;
						case 2: {
							//dentro de la media decides primero sobre que fuentes y seguido sobre qu� dato
							reset(fuente, ndatos, 0);
							printf("========= MEDIA =========  \n");
							int c1=0, c2=0;
							do {
								c1++;
								if(c1>1) {
									printf("El dato introducido es incorrecto, por favor introduzcalo de nuevo\n");
								}
								printf("Puede ver la media de todas las fuentes (Introduzca 1), de fuentes seleccionadas (Introduzca 2), en un intervalo (Introduzca 3)\n");
								scanf("%d", &md);
							} while (md!=1 && md!=2 && md!=3);
							do {
								c2++;
								if(c2>1) {
									printf("El dato introducido es incorrecto, por favor introduzcalo de nuevo\n");
								}
								printf("Puede calcular la media de ph (1), conductividad (2), turbidez (3), coliformes (4)  \n");
								scanf("%d", &sobremd);
							} while (sobremd!=1 && sobremd!=2 && sobremd!=3 && sobremd!=4);
							//est� organizado por datos y seguido el numero que indica sobre qu� fuentes se trata
							//ph 1
							if(md == 1 && sobremd == 1) {
								reset(fuente, ndatos, 1);
								fmediaph11(fuente,ndatos);
							}
							//ph 2
							if(md == 2 && sobremd == 1) {
								do{
									printf("Introduzca un n�mero de la fuente seleccionada, si no desea a�adir m�s introduzca 0");
									scanf("%d", &a);
									if(a!=0) {
										fuente[a-1].incluido=1;	
									}
								}while(a!=0);
								fmediaph11(fuente,ndatos);
							}
							//ph 3
							if(md == 3 && sobremd == 1) {
								//opci�n 3
								int min, max;
								do {
									printf("Introduzca el numero de la fuente minima del intervalo que desea buscar:");
									scanf("%d", &min);
									printf("Introduzca el  numero de la fuente maximo del intervalo que desea buscar: ");
									scanf("%d", &max);
									if (max<min) {
										printf("ERROR, el min tiene que ser menor que el m�ximo \n");
									}
								} while (max<min);
								for (i=min-1; i<max; i++) {
									fuente[i].incluido=1;									
								}	
								fmediaph11(fuente, ndatos);
							}
							//conductividad 1
							if(md == 1 && sobremd == 2) {
								reset(fuente, ndatos, 1);
								fmediacond2(fuente,ndatos);
							}
							//condutividad 2
							if(md == 2 && sobremd == 2) {
								do{
									printf("Introduzca un n�mero de la fuente seleccionada, si no desea a�adir m�s introduzca 0");
									scanf("%d", &a);
									if(a!=0) {
										fuente[a-1].incluido=1;
									}
								}while(a!=0);
								fmediacond2(fuente, ndatos);
							}
							//conductividad 3
							if(md==3 && sobremd==2) {
								int min, max;
								do {
									printf("Introduzca el m�nimo del intervalo que desea buscar:");
									scanf("%d", &min);
									printf("Introduzca el m�ximo del intervalo que desea buscar: ");
									scanf("%d", &max);
									if (max<min) {
										printf("ERROR, el m�nimo tiene que ser menor que el m�ximo \n");
									}
								} while (max<min);
								for (i=min-1; i<max; i++) {
									fuente[i].incluido=1;									
								}	
								fmediacond2(fuente, ndatos);
							}
							//turbidez 1
							if(md == 1 && sobremd == 3) {
								reset(fuente, ndatos, 1);
								fmediaturb2(fuente, ndatos);
							}
							//turbidez 2
							if(md == 2 && sobremd == 3) {
								do{
									printf("Introduzca un n�mero de la fuente seleccionada, si no desea a�adir m�s introduzca 0");
									scanf("%d", &a);
									if(a!=0) {
										fuente[a-1].incluido=1;
									}
								}while(a!=0);
								fmediaturb2(fuente, ndatos);
							}
							if(md==3 && sobremd==3) {
								int min, max;
								do {
									printf("Introduzca el minimo del intervalo que desea buscar:");
									scanf("%d", &min);
									printf("Introduzca el maximo del intervalo que desea buscar: ");
									scanf("%d", &max);
									if (max<min) {
										printf("ERROR, el min tiene que ser menor que el m�ximo \n");
									}
								} while (max<min);
								for (i=min; i<max; i++) {
									fuente[i].incluido=1;									
								}
								fmediaturb2(fuente, ndatos);
							}
							//coliformes 1
							if(md == 1 && sobremd == 4) {
								reset(fuente, ndatos, 1);
								fmediacoliformes2(fuente, ndatos);
							}
							//coliformes 2
							if(md == 2 && sobremd == 4) {
								do{
									printf("Introduzca un n�mero de la fuente seleccionada, si no desea a�adir m�s introduzca 0");
									scanf("%d", &a);
									if(a!=0) {
										fuente[a-1].incluido=1;
									}
								}while(a!=0);
								fmediacoliformes2(fuente,ndatos);
							}
							//coliformes 3
							if(md==3 && sobremd==4) {
								int min, max;
								do {
									printf("Introduzca el minimo del intervalo que desea buscar:");
									scanf("%d", &min);
									printf("Introduzca el maximo del intervalo que desea buscar: ");
									scanf("%d", &max);
									if (max<min) {
										printf("ERROR, el min tiene que ser menor que el m�ximo \n");
									}
								} while (max<min);
								for (i=min; i<max; i++) {
									fuente[i].incluido=1;									
								}
								fmediacoliformes2(fuente, ndatos);
							}
							reset(fuente, ndatos, 0);
							break;
						}
						case 3: 
							printf("========= MEDIANA =========  \n");
							int tipomediana, i,j;
							float aux; 
							printf("Puede ver la mediana de todas las fuentes (Introduzca 1), de fuentes seleccionadas (Introduzca 2), o en un intervalo (Introduzca 3)\n");
							scanf("%d",&tipomediana);
							
							for(i = 0; i < ndatos; i++){
    							for(j = i+1; j < ndatos; j++){
       								 if(fuente[i].ph > fuente[j].ph){
           								aux = fuente[i].ph;
           								fuente[i].ph = fuente[j].ph;
            							fuente[j].ph = aux;
       								}//fin if
    							}//fin for
  							}//fin for
  							float m;
  							if(ndatos%2==0){
  								m=(fuente[ndatos/2].ph+fuente[(ndatos/2)+1].ph)/2;
  								printf("La mediana es %f",m);
							  }
							if(ndatos%2!=0){
								m=fuente[(ndatos/2)].ph;
								printf("La mediana es: %f\n", m);

							}
						case 4:
							printf("Ha salido de estad�sticas\n");
							break;
						default:{
							printf("ERROR, la opci�n no es valida\n");
							break;
						}
					}
					
				} while (opcion != 4);
				
					//scanf("%d", &b);	
					break;
				
				break;
			}	case (5): 
				printf ("Has seleccionado la opcion de comparar datos \n"); 
				float n,a, ph; 
				int fuente1, fuente2, opcion;
				float phmayor, phmenor, comparacion; 
				int mayor, menor;  
	
		// menu de opciones para seleccionar que tipo de dato queremos comparar
				do{
					printf("========= COMPARACIONES ========= \n");
					printf("Seleccione que datos quiere comparar: \n 1: pH\n 2: conductividad \n 3:turbidez\n 4:coliformes\n"); // creo que esto iria dentro del switch case
					scanf("%d", &opcion); 
					if (opcion<1 && opcion>4) {
						printf(" ERROR. Esa opci�n no est� disponible, pruebe otra vez por favor \n"); 
					}
			} while (opcion<1 && opcion>4); 
		//menu de opciones para seleccionar qu� quiere hacer el usuario 
			switch (opcion)  {
				case (1): 
					printf("Has seleccionado comparar datos de ph entre fuentes \n"); 
					printf ("Escriba 1 si quiere comparar los datos de pH de mayor a menor o 2 si los quiere de menor a mayor \n"); 
					printf("Escriba 3 si quiere comparar los datos de pH por a�os \n"); 
					scanf("%d", &n);
					if (opcion==1){
						phmayor=fcomparacionmayor(fuente); 
						printf("El mayor valor de pH es: %f", phmayor);
					} 
					else if(opcion==2) {
						phmenor=fcomparacionmenor(fuente); 
						printf("El menor valor de pH es: %f", phmenor);
					}
					else if (opcion==3){
						printf("Introduzca el primer a�o a comparar \n"); 
						scanf("%d", &fuente1); 
						printf ("Introduzca el segundo a�o a comparar \n");
						scanf("%d", &fuente2);
						fcomparacionfuentes; 
					}
				break;
				case (2) : 
					printf("Has seleccionado comparar datos de conductividad entre fuentes \n"); 
					printf ("Escriba 1 si quiere ver el mayor valor de conductividad o 2 si quiere ver el menor valor de conductividad  \n"); 
					printf("Escriba 3 si quiere comparar los datos de conductividad por a�os \n"); 
					scanf("%d", &opcion);
					if (opcion==1){
							for(i=0; i<25; i++){
								if(fuente[i].conductividad>mayor){
									mayor=fuente[i].conductividad; 
								}
							}
						printf("Valor m�ximo de conductividad: %d \n", mayor);
					} 
					else if(opcion==2) {
						for(i=0; i<25; i++){
								if(fuente[i].conductividad<menor){
									menor=fuente[i].conductividad; 
								}
							}
						printf("Valor m�nimo de conductividad: %d \n", menor); 
					}
					else if (opcion==3){
						printf("Introduzca la primera fuente a comparar \n"); 
						scanf("%d", &fuente1); 
						printf ("Introduzca  la segunda fuente a comparar \n");
						scanf("%d", &fuente2);
						if (fuente[i].conductividad>fuente[i].conductividad){
							printf("La conductividad de la primera fuente introducida es mayor a la conductividad de la segunda fuente \n"); 
						} else if( fuente[i].conductividad<fuente[i].conductividad){
							printf("La conductividad de la segunda fuente introducida es mayor a la conductividad de la primera fuente \n"); 
						}else if(fuente[i].conductividad==fuente[i].conductividad){
							printf("Ambas fuentes tienen las mismas conductividades \n"); 
						}
					}	
					break;
				case(3): 
					printf ("Escriba 1 si quiere comparar los datos de turbidez de mayor a menor o 2 si los quiere de menor a mayor \n"); 
					printf("Escriba 3 si quiere comparar los datos de turbidez por a�os \n"); 
					scanf("%d", &opcion);
					if (opcion==1){
						printf("Datos de turbidez ordenados de mayor a menor \n"); 
					//	comparacion=fcomparacionmayor(fuente); 
						//printf("El mayor valor de turbidez es: %d", comparacion);
					} 
					else if(opcion==2) {
						printf("Datos de turbidez ordenados de menor a mayor \n"); 
						//comparacion=fcomparacionmenor(fuente); 
						printf("El menor valor de turbidez es: %d", comparacion);
					}
					else if (opcion==3){
						printf("Introduzca el primer anno a comparar \n"); 
						scanf("%d", &fuente1); 
						printf ("Introduzca el segundo anno a comparar \n");
						scanf("%d", &fuente2);
						fcomparacionfuentes; 
					
					}
				break;  
				case (4): 
					printf ("Escriba 1 si quiere comparar los datos de coliformes de mayor a menor o 2 si los quiere de menor a mayor \n"); 
					printf("Escriba 3 si quiere comparar los datos de coliformes por a�os \n"); 
					scanf("%d", &n);
					if (opcion==1){
						printf("Datos de coliformes ordenados de mayor a menor \n"); 
						comparacion=fcomparacionmayor(fuente); 
						printf("El mayor valor de coliformes es: %d", comparacion);
					} 
					else if(opcion==2) {
						printf("Datos de coliformes ordenados de menor a mayor \n"); 
						comparacion=fcomparacionmenor(fuente); 
						printf("El menor valor de coliformes es: %d", comparacion);
					}
					else if (opcion==3){
						printf("Introduzca la primera fuente a comparar \n"); 
						scanf("%d", &fuente1); 
						printf ("Introduzca la segundo fuente a comparar \n");
						scanf("%d", &fuente2);
						fcomparacionfuentes; 
					} 
				break;
			}
			case(8): 
				break;
			case(6): {
				int h, A, M, valorEncontrado=0, n7=0;
				printf("Ha seleccionado medir la dispersi�n de los ph respecto a un ph neutro\n");		
				printf("Introduzca el numero de la fuente cuyo ph desea comparar\n");
				scanf("%d", &h);
				do{
					n7++;
					if(n7>1) {
						printf("La fuente seleccionada no tiene datos registrados para dicho mes y a�o, introduzca valores de nuevo\n");
					}	
					printf("introduzca de que mes desea coger el dato: ");
					scanf("%d", &M);
					printf("introduzca de que a�o desea coger el dato:");
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
				printf("La dispersi�n del ph con respecto a un ph neutro es %.2f por ciento\n",fdispersionPh(h, fuente));	
				if(fuente[h].ph>7) {
					printf("La fuente tiene un ph b�sico");
				} else if (fuente[h].ph<7) {
					printf("la fuente tiene un ph �cido");
				} else {
					printf("La fuente tiene un ph neutro");
				}
				break;
			}
			case 7: {
				int dato1, dato2, dato3;
				float dt, cv, b, beta, r;
				reset(fuente, ndatos, 0);
				printf("Se le dir� el pron�stico esperado de un dato en funcion de otro");
				printf("Seleccione en funci�n de que dato desea realizar el pron�stico: \n 1-Ph\n 2-Conductividad\n 3-Coliformes\n 4-turbidez\n");
				scanf("%d", &dato1);
				printf("Seleccione una opcion:\n 1-Pronosticos pra todas las fuentes\n 2-Pronosticos para una fuente en concreto\n");
				scanf("%d", &dato3);
				switch(dato1) {
					case 1: {
						float phEsperado;
						printf("seleccione en funci�n de que dato desea hacer la predicci�n:\n 1-Conductividad\n 2-turbidez\n 3-Coliformes\n");
						scanf("%d", &dato2);
						if(dato2==1) {
							int ConductividadDada;
							printf("Para qu� valor de conductividad desea hacer la predicci�n del ph: \n");
							scanf("%d", &ConductividadDada);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el n�mero de la fuente para el que desea el pron�stico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2cond(fuente, ndatos)-(fmediaCond(fuente, ndatos)*fmediaCond(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaCondPh(fuente, ndatos)-(fmediaCond(fuente, ndatos)*fmediaPh(fuente, ndatos));
							phEsperado=((cv*(ConductividadDada-fmediaCond(fuente, ndatos)))/dt)+fmediaPh(fuente, ndatos);
							printf("El ph esperado para este valor es %f\n", phEsperado);
							b=cv/dt;
							beta=cv/(fmedia2ph(fuente, ndatos)-(fmediaPh(fuente, ndatos)*fmediaPh(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlaci�n es significativa puesto que es %f", r);
							} else {
								printf("La correlaci�n no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						} else if(dato2==2) {
							int TurbidezDada;
							printf("Para qu� valor de turbidez desea hacer la predicci�n del ph: \n");
							scanf("%d", &TurbidezDada);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el n�mero de la fuente para el que desea el pron�stico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2turb(fuente, ndatos)-(fmediaTurb(fuente, ndatos)*fmediaTurb(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaTurbPh(fuente, ndatos)-(fmediaTurb(fuente, ndatos)*fmediaPh(fuente, ndatos));
							phEsperado=((cv*(TurbidezDada-fmediaTurb(fuente, ndatos)))/dt)+fmediaPh(fuente, ndatos);
							printf("El ph esperado para este valor es %f\n", phEsperado);
							b=cv/dt;
							beta=cv/(fmedia2ph(fuente, ndatos)-(fmediaPh(fuente, ndatos)*fmediaPh(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlaci�n es significativa puesto que es %f", r);
							} else {
								printf("La correlaci�n no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						} else if (dato2==3) {
							int ColDada;
							printf("Para qu� valor de coliformes desea hacer la predicci�n del ph: \n");
							scanf("%d", &ColDada);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el n�mero de la fuente para el que desea el pron�stico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2colif(fuente, ndatos)-(fmediaCol(fuente, ndatos)*fmediaCol(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaColifPh(fuente, ndatos)-(fmediaCol(fuente, ndatos)*fmediaPh(fuente, ndatos));
							phEsperado=((cv*(ColDada-fmediaCol(fuente, ndatos)))/dt)+fmediaPh(fuente, ndatos);
							printf("El ph esperado para este valor es %f\n", phEsperado);
							b=cv/dt;
							beta=cv/(fmedia2ph(fuente, ndatos)-(fmediaPh(fuente, ndatos)*fmediaPh(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlaci�n es significativa puesto que es %f", r);
							} else {
								printf("La correlaci�n no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						} 
						break;
					} case 2: {
						float CondEsperado;
						printf("seleccione en funci�n de que dato desea hacer la predicci�n:\n 1-Ph\n 2-turbidez\n 3-Coliformes\n");
						scanf("%d", &dato2);
						if(dato2==1) {
							float PhDado;
							printf("Para qu� valor de ph desea hacer la prediccion de la conductividad: \n");
							scanf("%f", &PhDado);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el n�mero de la fuente para el que desea el pron�stico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2ph(fuente, ndatos)-(fmediaPh(fuente, ndatos)*fmediaPh(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaCondPh(fuente, ndatos)-(fmediaPh(fuente, ndatos)*fmediaCond(fuente, ndatos));
							CondEsperado=((cv*(PhDado-fmediaPh(fuente, ndatos)))/dt)+fmediaCond(fuente, ndatos);
							printf("La conductividad esperada para este valor es %f\n", CondEsperado);
							b=cv/dt;
							beta=cv/(fmedia2cond(fuente, ndatos)-(fmediaCond(fuente, ndatos)*fmediaCond(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlaci�n es significativa puesto que es %f", r);
							} else {
								printf("La correlaci�n no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						} else if(dato2==2) {
							int TurbidezDada;
							printf("Para qu� valor de turbidez desea hacer la predicci�n de conductividad: \n");
							scanf("%d", &TurbidezDada);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el n�mero de la fuente para el que desea el pron�stico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2turb(fuente, ndatos)-(fmediaTurb(fuente, ndatos)*fmediaTurb(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaCondTurb(fuente, ndatos)-(fmediaTurb(fuente, ndatos)*fmediaCond(fuente, ndatos));
							CondEsperado=((cv*(TurbidezDada-fmediaTurb(fuente, ndatos)))/dt)+fmediaCond(fuente, ndatos);
							printf("La conductividad esperada para este valor es %f\n", CondEsperado);
							b=cv/dt;
							beta=cv/(fmedia2cond(fuente, ndatos)-(fmediaCond(fuente, ndatos)*fmediaCond(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlaci�n es significativa puesto que es %f", r);
							} else {
								printf("La correlaci�n no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						} else if (dato2==3) {
							int ColDada;
							printf("Para qu� valor de coliformes desea hacer la predicci�n de conductividad: \n");
							scanf("%d", &ColDada);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el n�mero de la fuente para el que desea el pron�stico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2colif(fuente, ndatos)-(fmediaCol(fuente, ndatos)*fmediaCol(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaCondColif(fuente, ndatos)-(fmediaCol(fuente, ndatos)*fmediaCond(fuente, ndatos));
							CondEsperado=((cv*(ColDada-fmediaCol(fuente, ndatos)))/dt)+fmediaCond(fuente, ndatos);
							printf("La conductividad esperada para este valor es %f\n", CondEsperado);
							b=cv/dt;
							beta=cv/(fmedia2cond(fuente, ndatos)-(fmediaCond(fuente, ndatos)*fmediaCond(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlaci�n es significativa puesto que es %f", r);
							} else {
								printf("La correlaci�n no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						} 
						break;
					} case 3: {
						float ColEsperado;
						printf("seleccione en funci�n de que dato desea hacer la predicci�n:\n 1-Ph\n 2-turbidez\n 3-Conductividad\n");
						scanf("%d", &dato2);
						if(dato2==1) {
							float PhDado;
							printf("Para qu� valor de ph desea hacer la predicci�n de los coliformes: \n");
							scanf("%f", &PhDado);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el n�mero de la fuente para el que desea el pron�stico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2ph(fuente, ndatos)-(fmediaPh(fuente, ndatos)*fmediaPh(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaColifPh(fuente, ndatos)-(fmediaPh(fuente, ndatos)*fmediaCol(fuente, ndatos));
							ColEsperado=((cv*(PhDado-fmediaPh(fuente, ndatos)))/dt)+fmediaCol(fuente, ndatos);
							printf("Los coliformes esperados para este valor son %f\n", ColEsperado);
							b=cv/dt;
							beta=cv/(fmedia2colif(fuente, ndatos)-(fmediaCol(fuente, ndatos)*fmediaCol(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlacion es significativa puesto que es %f", r);
							} else {
								printf("La correlacion no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						} else if(dato2==2) {
							int TurbidezDada;
							printf("Para qu� valor de turbidez desea hacer la predicci�n de los coliformes: \n");
							scanf("%d", &TurbidezDada);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el n�mero de la fuente para el que desea el pron�stico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2turb(fuente, ndatos)-(fmediaTurb(fuente, ndatos)*fmediaTurb(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaTurbColif(fuente, ndatos)-(fmediaTurb(fuente, ndatos)*fmediaCol(fuente, ndatos));
							ColEsperado=((cv*(TurbidezDada-fmediaTurb(fuente, ndatos)))/dt)+fmediaCol(fuente, ndatos);
							printf("Los coliformes esperados para este valor son %f\n", ColEsperado);
							b=cv/dt;
							beta=cv/(fmedia2colif(fuente, ndatos)-(fmediaCol(fuente, ndatos)*fmediaCol(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlacion es significativa puesto que es %f", r);
							} else {
								printf("La correlacion no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						} else if (dato2==3) {
							int ConDada;
							printf("Para que valor de conductividad desea hacer la prediccion de los coliformes: \n");
							scanf("%d", &ConDada);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el numero de la fuente para el que desea el pronostico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2cond(fuente, ndatos)-(fmediaCond(fuente, ndatos)*fmediaCond(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaCondColif(fuente, ndatos)-(fmediaCond(fuente, ndatos)*fmediaCol(fuente, ndatos));
							ColEsperado=((cv*(ConDada-fmediaCond(fuente, ndatos)))/dt)+fmediaCol(fuente, ndatos);
							printf("Los coliformes esperados para este valor es %f\n", ColEsperado);
							b=cv/dt;
							beta=cv/(fmedia2colif(fuente, ndatos)-(fmediaCol(fuente, ndatos)*fmediaCol(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlacion es significativa puesto que es %f", r);
							} else {
								printf("La correlacion no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						} 
						break; 
					} case 4: {
						float TurEsperado;
						printf("seleccione en funcion de que dato desea hacer la prediccion:\n 1-Ph\n 2-Coliformes\n 3-Conductividad\n");
						scanf("%d", &dato2);
						if(dato2==1) {
							float PhDado;
							printf("Para que valor de ph desea hacer la prediccion de la turbidez: \n");
							scanf("%f", &PhDado);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el numero de la fuente para el que desea el pronostico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2ph(fuente, ndatos)-(fmediaPh(fuente, ndatos)*fmediaPh(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaTurbPh(fuente, ndatos)-(fmediaPh(fuente, ndatos)*fmediaTurb(fuente, ndatos));
							TurEsperado=((cv*(PhDado-fmediaPh(fuente, ndatos)))/dt)+fmediaTurb(fuente, ndatos);
							printf("La turbidez esperada para este valor es %f\n", TurEsperado);
							b=cv/dt;
							beta=cv/(fmedia2turb(fuente, ndatos)-(fmediaTurb(fuente, ndatos)*fmediaTurb(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlacion es significativa puesto que es %f", r);
							} else {
								printf("La correlacion no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						} else if(dato2==2) {
							int ColDada;
							printf("Para que valor de coliformes desea hacer la prediccion de la  turbidez: \n");
							scanf("%d", &ColDada);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el numero de la fuente para el que desea el pronostico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2colif(fuente, ndatos)-(fmediaCol(fuente, ndatos)*fmediaCol(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaTurbColif(fuente, ndatos)-(fmediaCol(fuente, ndatos)*fmediaTurb(fuente, ndatos));
							TurEsperado=((cv*(ColDada-fmediaCol(fuente, ndatos)))/dt)+fmediaTurb(fuente, ndatos);
							printf("La turbidez esperada para este valor es %f\n", TurEsperado);
							b=cv/dt;
							beta=cv/(fmedia2turb(fuente, ndatos)-(fmediaTurb(fuente, ndatos)*fmediaTurb(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlacion es significativa puesto que es %f", r);
							} else {
								printf("La correlacion no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						} else if (dato2==3) {
							int ConDada;
							printf("Para que valor de conductividad desea hacer la prediccion de la turbidez: \n");
							scanf("%d", &ConDada);
							if(dato3==2) {
								int dato4, s;
								printf("Introduzca el numero de la fuente para el que desea el pronostico: ");
								scanf("%d", &dato4);
								for(s=0; s<ndatos; s++) {
									if(fuente[s].numfuente==dato4) {
										fuente[s].incluido=1;
									}
								}
							} else if(dato3==1) {
								reset(fuente, ndatos, 1);	
							}
							dt=fmedia2cond(fuente, ndatos)-(fmediaCond(fuente, ndatos)*fmediaCond(fuente, ndatos));
							if(dt==0) {
								dt=0.000001;
							}
							cv=fmediaCondTurb(fuente, ndatos)-(fmediaCond(fuente, ndatos)*fmediaTurb(fuente, ndatos));
							TurEsperado=((cv*(ConDada-fmediaCond(fuente, ndatos)))/dt)+fmediaTurb(fuente, ndatos);
							printf("La turbidez esperada para este valor es %f\n", TurEsperado);
							b=cv/dt;
							beta=cv/(fmedia2turb(fuente, ndatos)-(fmediaTurb(fuente, ndatos)*fmediaTurb(fuente, ndatos))+0.000001);
							r=sqrt(b*beta);
							if(r>0.5) {
								printf("La correlacion es significativa puesto que es %f", r);
							} else {
								printf("La correlacion no es significativa, puesto que es %f", r);
							}
							printf("El porcentaje aproximado de fiabilidad es %f", r*100);
						}
						break;
					}
				}
				reset(fuente, ndatos, 0);
				break;
			}
			default: {
				printf("El valor introducido es incorrecto, por favor vuelva a introducirlo:");
				break;
			}
		}
		printf("\n");
	}while(a!=6);
	printf("Hasta la proxima %s %s \n", nombre, apellido); 
	printf("FIN DEL PROGRAMA"); 
	
	return 0;

}




void reset (struct Tfuente matriz[], int num, int a) {
	int i; 
	for(i=0; i<num; i++) {
		matriz[i].incluido=a;
	}
}
float fcomparacionmayor (struct Tfuente fuente[]) {
		int i; 
		float phmayor=0; 
		for(i=0; i<25; i++){
			if(fuente[i].ph>phmayor){
				phmayor=fuente[i].ph; 
			}
		}
		return phmayor; 

}
float fcomparacionmenor (struct Tfuente fuente[]){
		int i; 
		float phmenor=0; 
		for(i=0; i<25; i++){
			if(fuente[i].ph<phmenor){
				phmenor=fuente[i].ph; 
			}
		}
		return phmenor; 
}
void fcomparacionfuentes (struct Tfuente fuente[]) {
	int i, a, b;
	for(i=0; i<25; i++) {
		printf("Introduce el numero de la fuente 1"); 
		scanf("%d", &a); 
		printf("Introduce el numero de la fuente 2"); 
		scanf("%d", &b); 
		if(fuente[a-1].ph> fuente[b-1].ph){
			printf("El ph de la fuente 1 es mayor que el de la fuente 2 ");
		}else {
			printf("El ph de la fuente 2 es mayor que el de la fuente 1"); 
		}
	}
}
//media ph11
void fmediaph11(struct Tfuente fuente[], int ndatos){
	int z; 
	float phMax=0, media=0, cantidad=0;
	for(z=0; z<ndatos; z++) {
		if(fuente[z].incluido==1){
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
//media 21
/*
void fmediaph21(struct Tfuente fuente[], int ndatos){
	int i,z,non;
	float phMax=0, media=0, cantidad=0;
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
*/
float fdispersionPh(int n, struct Tfuente fuente[]) {
	if(fuente[n].ph<7) {
		return ((7-fuente[n].ph)*100)/7;
	} else {
		return ((fuente[n].ph-7)*100)/7;	
	}
}

float fmedia2ph(struct Tfuente fuente[], int ndatos) {
	int i, num=0;
	float suma=0;
	for(i=0;i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=(fuente[i].ph*fuente[i].ph);
			num++;
		}
	}
	return suma/num;
}

float fmedia2cond(struct Tfuente fuente[],int ndatos) {
	int i, num=0;
	float suma=0;
	for(i=0;i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=(fuente[i].conductividad*fuente[i].conductividad);
			num++;
		}
	}
	return suma/num;
}

float fmedia2turb(struct Tfuente fuente[], int ndatos) {
	int i, num=0;
	float suma=0;
	for(i=0;i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=(fuente[i].turbidez*fuente[i].turbidez);
			num++;
		}
	}
	return suma/num;
}

float fmedia2colif(struct Tfuente fuente[], int ndatos) {
	int i, num=0;
	float suma=0;
	for(i=0;i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=(fuente[i].coliformes*fuente[i].coliformes);
			num++;
		}
	}
	return suma/num;
}

float fmediaCondPh(struct Tfuente fuente[], int ndatos) {
	int i, num=0;
	float suma=0;
	for(i=0;i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=(fuente[i].conductividad*fuente[i].ph);
			num++;		
		}
	}
	return suma/num;
}
float fmediaTurbPh(struct Tfuente fuente[], int ndatos) {
	int i, num=0;
	float suma=0;
	for(i=0;i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=(fuente[i].turbidez*fuente[i].ph);
			num++;
		}
	}
	return suma/num;
}
float fmediaColifPh(struct Tfuente fuente[], int ndatos) {
	int i, num=0;
	float suma=0;
	for(i=0;i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=(fuente[i].coliformes*fuente[i].ph);
			num++;
		}
	}
	return suma/num;
}
float fmediaCondTurb(struct Tfuente fuente[], int ndatos) {
	int i, num=0;
	float suma=0;
	for(i=0;i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=(fuente[i].conductividad*fuente[i].turbidez);
			num++;
		}
	}
	return suma/num;
}
float fmediaCondColif(struct Tfuente fuente[], int ndatos) {
	int i, num=0;
	float suma=0;
	for(i=0;i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=(fuente[i].coliformes*fuente[i].conductividad);
			num++;
		}
	}
	return suma/num;
}
float fmediaTurbColif(struct Tfuente fuente[], int ndatos) {
	int i, num=0;
	float suma=0;
	for(i=0;i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=(fuente[i].coliformes*fuente[i].turbidez);
			num++;
		}
	}
	return suma/num;
}

float fmediaCond(struct Tfuente fuente[], int ndatos) {
	int i, num=0; 
	float suma=0;
	for(i=0; i<ndatos;i++) {
		if(fuente[i].incluido==1) {
			suma+=(fuente[i].conductividad);
			num++;
		}
	}
	return suma/num;
}
float fmediaPh(struct Tfuente fuente[], int ndatos) {
	int i, num=0; 
	float suma=0;
	for(i=0; i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=fuente[i].ph;
			num++;
		}
	}
	return suma/num;
}

float fmediaTurb(struct Tfuente fuente[], int ndatos) {
	int i, num=0; 
	float suma=0;
	for(i=0; i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=fuente[i].turbidez;	
			num++;
		}
	}
	return suma/num;
}
float fmediaCol(struct Tfuente fuente[], int ndatos) {
	int i, num=0; 
	float suma=0;
	for(i=0; i<ndatos; i++) {
		if(fuente[i].incluido==1) {
			suma+=fuente[i].coliformes;
			num++;
		}
	}
	return suma/num;
}
/*
void fmediacond1(struct Tfuente fuente[],int ndatos){
	int z; 
	float condMax=0, media=0, cantidad=0;	
	for(z=0; z<ndatos; z++) {
		cantidad++;
		media+=fuente[z].conductividad;
		if (fuente[z].conductividad > condMax) {
			condMax = fuente[z].conductividad;
		}	
	}
	printf("La media de conductividad es: %.2f\n", media / ndatos);
	printf("La conductividad maxima es: %.2f\n", condMax);
}
*/
void fmediacond2(struct Tfuente fuente[],int ndatos){
	int z; 
	float condMax=0, media=0, cantidad=0;	
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
/*
void fmediaturb1(struct Tfuente fuente[], int ndatos){
	int z; 
	float turMax=0, media=0, cantidad=0;	
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
*/
void fmediaturb2(struct Tfuente fuente[],int ndatos){
	int z; 
	float turMax=0, media=0, cantidad=0;	
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
/*
void fmediacoliformes1(struct Tfuente fuente[], int ndatos){
	int z; 
	float coliMax=0, media=0, cantidad=0;	
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
*/
void fmediacoliformes2(struct Tfuente fuente[],int ndatos){
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

