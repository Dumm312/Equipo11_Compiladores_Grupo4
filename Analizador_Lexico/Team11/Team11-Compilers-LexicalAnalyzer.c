#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

int main(int argc, char *argv[]){
	FILE *archivo;							//Declaración de un puntero a un archivo
    char exp[100][1000]; 					// Matriz para almacenar las lineas del archivo
    char linea[10000];    					// Tamaño del buffer para una linea

    archivo = fopen("archivo.txt", "r");	//Apertura del Archivo "archivo.txt" en modo lectura	

	/*Validación para verificar si se pudo abrir el archivo en caso contrario
	mostrara el mensaje de "No se pudo abrir el archivo"*/
	
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;							//Se regresa 1 para indicar un error
    }
    
    //Declaración de Variables a Usar
	int cont1=0, cont2=0, len1, contfor;
	bool b1=true, b2=false, err=true;
	int op=100, igu=0, parizq=0, parder=0;
	int i, i1,tokens_invalidos=0;											//Variables y contador para tokens invalidos
	int contdig, contsigno, contoper, contpunto, contL, contR, contigual;	//Contadores para cada token
	
	//Imprime el mensaje de bienvenida y condiciones de Aceptación de Cadenas
	printf(" =========================================================================================== \n");
	printf("|------------------------------BIENVENIDX al analizador l%cxico------------------------------|\n", 130);
	printf("|\t\t\t\t ***Puntos a considerar***\t\t\t\t    |\n");
	printf("|->1) La operaci%cn debe contener el signo igual (=) al final de la expresi%cn \t\t    |\n", 162, 162);
	printf("|->2) El uso del punto decimal es obligatorio \t\t\t\t\t\t    |\n");
	printf("|->3) Los numeros pueden o no contener signo (+, -) \t\t\t\t\t    |\n");
	printf("|->4) Las operaciones permitidas son: suma, resta, multiplicaci%cn y divisi%cn (+, -, *, /)   |\n", 162, 162);
	printf(" =========================================================================================== \n ");

	
	//Bucle Principal el cual se ejecuta por ahora 100 veces
    while(op--){
    	int cont1 = 0; // índice para la fila en la matriz exp

	    // Bucle que se ocupa para leer y procesar cada línea del archivo
	    while (fgets(linea, sizeof(linea), archivo)) {
	        // Buscar el salto de línea en la línea
	        char *salto = strchr(linea, '\n');

	        if (salto != NULL) {
	            // Reemplazar el salto de línea con un terminador nulo
	            *salto = '\0';

	            // Copiar la línea a la matriz exp en la fila i
	            strcpy(exp[cont1], linea);
	            len1=strlen(exp[cont1]);
	            if( len1 == 0 ){ break; }
	            printf("============================================================================================");
	            printf("\n\t\t\t\tEJECUTANDO LA EXPRESI%cN #%d\n", 224, cont1+1);
	            printf( "La expresi%cn es: %s\n", 162, exp[cont1] );

        //Caso especial para cuando la expresión inicia en punto
        if( exp[cont1][0] == 46 ){
            printf("\n\t La cadena est%c formada por:\n\t\tp ", 160);
            if( len1 == 1 ){ printf("X--0. Expresi%cn inv%clida--\n", 162, 160); break; } //Si solo es el punto es invalido
            for( int j = 1; j < len1-1; j++){
                if( exp[cont1][j] >= 48 && exp[cont1][j] <=57 ){ printf("d "); } //Puede haber 1 o más digitos
                else{ printf("X--0. Expresi%cn inv%clida--\n", 162, 160); break; } //No puede tener otro terminal
            }
            if( exp[cont1][len1-1] == 61 ){ printf("i \n\n"); }
            else{ printf("X--0. Expresi%cn inv%clida--   no termina en igual\n", 162, 160); break; } //Debe terminar en igual
        }

    	if(len1<8){ //La cadena más corta que acepta es con longitud=8, por lo que si es más chica no se acepta
		}
		else{
                //Si se acepta la cadena, comienza a contar la cantidad de iguales (sólo debe haber uno al final de la expresión),
                //parentesis izquierdos y derechos, de estos debe haber la misma cantidad
			for (i1=0; i1<len1; i1++){
				if(exp[cont1][i1]==61){
					igu++;
				}
				if(exp[cont1][i1]==40){
					parizq++;
				}
				if(exp[cont1][i1]==41){
					parder++;
				}
			}
			printf("\nSe encontraron %i iguales, %i parentesis izquierdos y %i parentesis derechos\n", igu, parizq, parder);

			//Se delimita el rango en código ASCII del lenguaje aceptado
			//El último digito no es igual, hay más o menos de un igual, no hay igual cantidad de paréntesis izquierdos que derechos
			//no es un dígito del 0 al 9, no es ni signo '+' o signo '-' o espacio
			if((exp[cont1][len1-1]!=61)||(igu!=1)||(parizq!=parder)||(!(((exp[cont1][0]>=48)&&(exp[cont1][0]<=57))||(exp[cont1][0]==43)||(exp[cont1][0]==45)||(exp[cont1][0]==32)))){
				//if( exp[cont1][len1-1] != 61 ){ printf("La expresi%cn no termina en igual\n\n", 162); }
				if( igu == 0 ){ printf("C%cmo no hay signo igual la expresi%cn es err%cnea\n\n", 162, 162, 162); }
                if( igu > 1){ printf("C%cmo hay mas de un igual la expresi%cn es err%cnea\n\n", 162, 162, 162); }
                if( parizq != parder ){ printf("No hay igual cantidad de parentesis que abren y de parentesis que cierran\n\n"); }
                if( !(((exp[cont1][0]>=48)&&(exp[cont1][0]<=57))||(exp[cont1][0]==43)||(exp[cont1][0]==45)||(exp[cont1][0]==32)) ){ printf("No inicia con un dato v%clido\n\n", 160); }

				printf("X<--1. Expresi%cn inv%clida-- \n", 162, 160);
				tokens_invalidos++;
			}else{
				i=0;
				err=true; //Mientras que err sea igual a 1 no habr? error
				printf("\n\t\t\t\t La cadena est%c formada por:\n\n\t\t", 160);
				if((exp[cont1][i]==43)||(exp[cont1][i]==45)||(exp[cont1][i]==32)||((exp[cont1][i]>=48)&&(exp[cont1][i]<=57))){ //La cadena puede empezar con un n?mero o signo + o -
					if((exp[cont1][i]==43)||(exp[cont1][i]==45) || (exp[cont1][i] == 32)){ //Si el primer digito es un + o - se pasa al siguiente caracter de la cadena
						i++;
						printf(" s ");
						if((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){ //Comprobacion de digito
							while((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){
								printf("d ");
								i++;
							}
						}else{
							printf("X--2. Expresi%cn inv%clida-- \n", 162, 160);
							err=false;
							tokens_invalidos++;
						}
					}else{ //Si no se inicia con signo debe iniciar con digito
						if((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){ //Comprobacion de digito
							while((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){
								printf("d ");
								i++;
							}
						}else{
							printf("X--3. Expresi%cn inv%clida-- \n", 162, 160);
							err=false;
							tokens_invalidos++;
							}
						}
				}
				else{
					printf("X--4. Expresi%cn inv%clida-- \n", 162, 160);
					err=false;
					tokens_invalidos++;
				}
				if(err){
					//printf("entra");
					if((exp[cont1][i]==46)){
						printf("p ");
						i++;
						if((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){
							while((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){
								printf("d ");
								i++;
								}
						}else{
							err=false;
							tokens_invalidos++;
						}
					}else{
						err=false;
						tokens_invalidos++;
					}
				}
				if(err){
					for(i; i<len1-1;i++){
						if((exp[cont1][i]==42)||(exp[cont1][i]==43)||(exp[cont1][i]==45)||(exp[cont1][i]==47)){ //Compruebasi es operador
							printf("o ");
							i++;
							if((exp[cont1][i]==40)||((exp[cont1][i]>=48)&&(exp[cont1][i]<=57))){ //Comprueba si es parentesis izquierdo o d?gito
								if((exp[cont1][i]==40)){//hay parentesis izquierdo
									printf("L ");
									i++;
									if((exp[cont1][i]==43)||(exp[cont1][i]==45)||((exp[cont1][i]>=48)&&(exp[cont1][i]<=57))){ //Comprueba si hay + o - o d?gito
										if((exp[cont1][i]==43)||(exp[cont1][i]==45)){ //Comprueba si es un + o -
											printf("s ");
											i++;
											if(!(exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){ //Si no continua un digito estaria mal
												err=false;
												tokens_invalidos++;
												break;
											}
										}
										if((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){ //Comprueba si s? es un digito
											while((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){
											printf("d ");
											i++;
											}
											if((exp[cont1][i]==46)){ //Comprueba si hay un punto
												printf("p ");
												i++;
												if((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){ //Despues del punto debe haber m?s digitos
													while((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){
														printf("d ");
														i++;
													}
													if((exp[cont1][i]==41)){ //hay parentesis de cierre
														printf("R ");
														continue;
													}else{
														err=false; //Si no se cierran los parentesis estaria mal
														tokens_invalidos++;
														break;
													}
												}else{
													err=false;
													tokens_invalidos++;
													break;
												}
											}else{
												err=false;
												tokens_invalidos++;
												break;
											}
										}
									}else{
										err=false;
										tokens_invalidos++;
										break;
									}
								}else{
									while((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){ // comprueba si hay numeros
										printf("d ");
										i++;
									}
									if((exp[cont1][i]==46)){ //Comprueba si hay un punto seguido de los digitos
										printf("p ");
										i++;
										if((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){ //Despues del punto debe haber m?s digitos
											while((exp[cont1][i]>=48)&&(exp[cont1][i]<=57)){
												printf("d ");
												i++;
											}
											i--;
										}else{
											err=false;
											tokens_invalidos++;
											break;
										}
									}else{
										err=false;
										tokens_invalidos++;
										break;
									}
								}
							}else{
								err=false;
								tokens_invalidos++;
								break;
							}

						}else{
							err=false;
							tokens_invalidos++;
							break;
						}
					}
					if(err){
						printf("i \n\n");
					}else{
						printf("X--5. Expresi%cn inv%clida-- \n", 162, 160);

					}
				}else{
					printf("X--6. Expresi%cn inv%clida-- \n", 162, 160);
				}
			}
		}
    	cont1++;
    	igu=0, parizq=0, parder=0;			//Reiniciamos para cada que termina un ciclo de lectura y principal
    	fflush(stdin);

	   		}
	    }
	}
	printf("\n\n La cantidad de tokens invalidos son: %i \n",tokens_invalidos);
    fclose(archivo);
    system("pause");
	return 0;
    
}

