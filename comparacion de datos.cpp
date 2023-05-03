p//TRABAJO PROGRA PARTE DE COMPARACION DE DATOS 

#include <stdio.h>

//prototipo de las funciones 

//funcion main 
int main () {
	
	float n, ph[25]; 
	int conductividad[25], turbidez[25], coliformes[25],  anno1, anno2; 
	
	
	
	
	// menu de opciones para seleccionar que tipo de dato queremos comparar
	do{
		printf("Seleccione que datos quiere comparar: \n 1: ph\n 2: conductividad \n 3:turbidez\n 4:coliformes\n"); // creo que esto iria dentro del switch case
		scanf("%d", &n); 
		if (n!=1 && n!=2 && n!=3 && n!=4 && n!=5) {
			printf(" ERROR. Esa opcion no esta disponible, pruebe otra vez por favor \n"); 
		}
	} while (n!=1 && n!=2 && n!=3 && n!=4 && n!=5); 
	switch (n) {
		case (1): {
			printf ("Escriba 1 si quiere comparar los datos de ph de mayor a menor o 2 si los quiere de menor a mayor \n"); 
			printf("Escriba 3 si quiere comparar los datos de ph por años \n"); 
			scanf("%d", &n);
			if (n==1){
				printf("Datos de ph ordenados de mayor a menor \n"); 
				comparacion=fcomparacionmmayor(ph); 
			} 
			if(n==2) {
				printf("Datos de ph ordenados de menor a mayor \n"); 
				comparacion=fcomparacionmenor(ph); 
			}
			if (n==3){
				printf("introduzca el primer anno a comparar \n"); 
				scanf("%d", &anno1); 
				printf ("introduzca el seugndo anno a comparar \n");
				scanf("%d", &anno2);
				fcomparacionannos; 
				
			}
			break;
		}
		case (2) : {
			printf ("Escriba 1 si quiere comparar los datos de conductividad de mayor a menor o 2 si los quiere de menor a mayor \n"); 
			printf("Escriba 3 si quiere comparar los datos de conductividad por años \n"); 
			scanf("%d", &n);
			if (n==1){
				printf("Datos de conductividad ordenados de mayor a menor \n"); 
				comparacion=fcomparacionmmayor(ph); 
			} 
			if(n==2) {
				printf("Datos de conductividad ordenados de menor a mayor \n"); 
				comparacion=fcomparacionmenor(ph); 
			}
			if (n==3){
				printf("introduzca el primer anno a comparar \n"); 
				scanf("%d", &anno1); 
				printf ("introduzca el seugndo anno a comparar \n");
				scanf("%d", &anno2);
				fcomparacionannos; 
				
			}	
			break;
		}
		case(3): {
			printf ("Escriba 1 si quiere comparar los datos de turbidez de mayor a menor o 2 si los quiere de menor a mayor \n"); 
			printf("Escriba 3 si quiere comparar los datos de turbidez por años \n"); 
			scanf("%d", &n);
			if (n==1){
				printf("Datos de turbidez ordenados de mayor a menor \n"); 
				comparacion=fcomparacionmmayor(ph); 
			} 
			if(n==2) {
				printf("Datos de turbidez ordenados de menor a mayor \n"); 
				comparacion=fcomparacionmenor(ph); 
			}
			if (n==3){
				printf("introduzca el primer anno a comparar \n"); 
				scanf("%d", &anno1); 
				printf ("introduzca el seugndo anno a comparar \n");
				scanf("%d", &anno2);
				fcomparacionannos; 
				
			}
			break; 
		} 
		case (4): {
			printf ("Escriba 1 si quiere comparar los datos de coliformes de mayor a menor o 2 si los quiere de menor a mayor \n"); 
			printf("Escriba 3 si quiere comparar los datos de coliformes por años \n"); 
			scanf("%d", &n);
			if (n==1){
				printf("Datos de coliformes ordenados de mayor a menor \n"); 
				comparacion=fcomparacionmmayor(ph); 
			} 
			if(n==2) {
				printf("Datos de coliformes ordenados de menor a mayor \n"); 
				comparacion=fcomparacionmenor(ph); 
			}
			if (n==3){
				printf("introduzca el primer anno a comparar \n"); 
				scanf("%d", &fuente1); 
				printf ("introduzca el seugndo anno a comparar \n");
				scanf("%d", &feunte2);
				fcomparacionannos; 
				
			}
			break;
		}
	
	
	
	return 0; 
}

// despues de la main 
	float foperacionmayor (float ph[]) {
		int i; 
		float mayor; 
		for(i=0; i<25; i++){
			if(ph[i]>mayor){
				mayor=fuente[z].ph; 
			}
			fscanf(fichero, "%f", ph[i]);
		}

}
	float comparacionmenor (float ph){
		int i; 
		float menor; 
		for(i=0; i<25; i++){
			if(fuente[z].ph<menor){
				menor=fuente[z].ph; 
			}
			fscanf(fichero, "%f", ph[i]); //pero es que estoy sacando el mayor de todos los datos, no los estoy ordenando 
		}
	
}
	void fcomparacionfuentes (float ph, int fuente1, int fuente2) {
		if
		
	
}



