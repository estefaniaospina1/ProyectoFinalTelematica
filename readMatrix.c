#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <malloc.h>

// Define filename etc
#define filename "text1.txt"
#define rows 4
#define cols 4

main(){

    FILE *file;
    char *buffer;
    int  ret,row=0,i,j;

    // Set Field Separator here
    char delims[]=" \t";
    char *result=NULL;

    // Memory allocation
    double **mat = malloc( rows*sizeof(double*));
    for(i = 0; i < rows; i++) 
    mat[i] = malloc( cols*sizeof(double));

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
                              printf("%lf%s",mat[i][j], j < cols-1 ? "\t" : "\n");
                              free(mat[i]);
                       }    
        free(mat);        
     



    }