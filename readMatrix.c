#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <malloc.h>
int maximo(int q, int a);

// Define filename etc
#define filename "usuarios-peliculas.txt"
#define rows 4
#define cols 4


int  matrixui()
{
   FILE *file;
	char *buffer;
	int  ret,row=0,i,j;

	// Set Field Separator here
	char delims[]=" \t";
	char *result=NULL;

	// Memory allocation
	int **mat = malloc( rows*sizeof(double*));
	for(i = 0; i < rows; i++) {
		mat[i] = malloc( cols*sizeof(double));
	}
	if ((file = fopen(filename, "r")) == NULL){
		fprintf(stdout, "Error: Can't open file !\n");
		return -1;
	}
	while(!feof(file))
	{
		buffer = malloc(sizeof(char) * 4096);
		memset(buffer, 0, 4096);
		ret = fscanf(file, "%4095[^\n]\n", buffer);
		if (ret != EOF) {
			int field = 0;
			result = strtok(buffer,delims);
			while(result!=NULL){
				// Set no of fields according to your requirement
				if(field>4)break;
				mat[row][field]=atof(result);    
				result=strtok(NULL,delims);
				field++;
			}
			++row;            
		}
		free(buffer);
	}
	fclose(file);
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++)
			printf("%d%s",mat[i][j], j < cols-1 ? "\t" : "\n");
		
	}
	return mat;
}

int matrixcorr(){
	int  iterador=1;
	int x=1;
	int y=0;
	int  u = 0;
	int p=0;
	int **mat= matrixui();	//se llama a la matriz de usuarios vs peliculas para ver su similitud
	double matrixcorr[rows][cols];


	int localrow=0;
	int localcol=0;
	int distancia =0;
	double similitud=0;
	
	for(u=0;u<rows;u++){
		for(p=0;p<cols;p++)
			matrixcorr[u][p]=-10;
		
	}


while (localrow < rows-1){

	while (localrow < rows){
	
	double diferencia=0;
	int numeroCeros=0;
		while(localcol < cols){
		
			//saco las diferencias y las promedio
			//falta verificar si es localrow +1

			if(mat[localrow][localcol]== 0||mat[localrow +iterador][localcol]==0)
			{
				distancia = 10;														//miro si ya se vieron la pelicula
				numeroCeros++;
			}
			else{
				distancia = mat[localrow][localcol] - mat[localrow +iterador][localcol];

			}


			 
				switch( abs(distancia ) )
				{
					case 0:
						diferencia = 1;
						break;
					case 1 :
						diferencia = 0.5;
						break;
					case 2 :
						diferencia = 0;
						break;
					case 3 :
						diferencia = -0.5;
						break;
					case 4 :
						diferencia =-1;
						break;
					case 10 :   //este caso es para cuando alguna de las 2 peliculas este en 0 (no vistas)
						localcol++;
						continue;
						break;
				}


			similitud= similitud +(diferencia);


			localcol++;
		}
		matrixcorr[y][x]= similitud/(cols-numeroCeros);
		iterador++;
		x++;
		localcol=0;
		similitud=0;

		if(iterador == rows-localrow){
		break;
		}
		//tengo que poner en la matriz que voy a hacer (matrix corr) la diferencia /rows;


		
		
	}
	localrow++;
	y++;
	x = y+1;
	iterador= 1;

}
printf("\n");
printf("\n");
printf("\n");
printf( "correlation matrix \n");


for (u=0;u<rows;u++)
{ 
for(p=0;p<cols;p++)
{
printf("%05.1f\t ",matrixcorr[u][p], p < cols-1 ? "\n" : "\n");
}

}
}



int maximo(int num1, int num2) 
{
   /* local variable declaration */
   int result;
 
   if (num1 > num2)
      result = num1;
   else
      result = num2;
 
   return result; 
}



main(){

	  int **mat= matrixui();
	  matrixcorr();
	  printf("%d%",mat[0][1]);
		//como imprimir alguna scosa

		printf("%d%",maximo(mat[1][1], mat[2][2]));
	
	getchar();


}



