#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fractal.h"
#include <semaphore.h>

typedef enum { false, true } bool;
pthread_mutex_t mutexFractal;
sem_t empty;
sem_t full;
int MAXTHREADS=4;
int FILEAMOUNT=0;
fractal * slots[10];
char  files [100][100];
bool eof =false;
int currentFile = 0;
bool noMoreFiles=false;
fractal * emptyFract;
double highest_mean_value;


char* getFractal(char file[], int lineNumber){
	//printf("in get fractal, file = %s \n", file);
	int currentline = 1;
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
	FILE *fp = fopen(file, "r");
	
	if (fp == NULL){
        exit(EXIT_FAILURE);
	}
	
    while ((read = getline(&line, &len, fp)) != -1) {
        if(currentline == lineNumber){
			
			break;
		}
      currentline++;
    }
    if(line==-1){
		eof =true;
	}
	
    fclose(fp);
	printf("Line found here return: %s", line); 
	
	return line;
}


void producer(){
	
	int currentLine = 1;
	int currentFile = 0;
	
	while(currentFile<FILEAMOUNT)
	{
		
		char* fractalResult=getFractal(files[currentFile], currentLine);
		currentLine++;
		printf("after get fractal: %s",fractalResult);
		if(eof==true){
			currentFile++;
			eof=false;
		}
		
		if(fractalResult[0]!="#"){
			printf("just before sem wait \n");
			sem_wait(&empty); 
			pthread_mutex_lock(&mutexFractal);
			
			int index;
			for(int i =0;i<10;i++){
				if(fractal_get_height(slots[i])<0){
					index=i;
				}
			}
			char * name= strtok(fractalResult," ");
			char * width = strtok(NULL," ");
			char * height = strtok(NULL," ");
			char * a = strtok(NULL," ");
			char * b = strtok(NULL," ");
			
			slots[index]= fractal_new(atoi(width), atoi(height), atof(a), atof(b), name);
		
			pthread_mutex_unlock(&mutexFractal);
			sem_post(&full);
		}
	}
	printf("After while");
	noMoreFiles=true;
	
}












int main(int argc, char *argv[])
{
	///////LECTURE PARAMETRES/////////////
	 
    
    int printAll = 0;
 
    //entier dans lequel on va stocker la position du "-" dans le tableau d'argument
    //et qui nous indiquera si il faut gerer l'entree standard
    int pos = 0;
 
    
    //Commence a 1 car 0 est le nom du file
    int i = 1;
 
    
    
    int comp_maxthread1 = strcmp("--maxthreads", argv[i]);
    int comp_d1 = strcmp("-d", argv[i]);
    
    if(comp_maxthread1 == 0){
        i++;
        MAXTHREADS = atoi(argv[i]);
        i++;
    }
    else if(comp_d1 == 0){
        printAll = 1;
        i++;
    }
 
    //on regarde quel est le deuxieme argument
    int comp_maxthread2 = strcmp("--maxthreads", argv[i]);
    int comp_d2 = strcmp("-d", argv[i]);
    if(comp_maxthread2==0){
        i++;
        MAXTHREADS = atoi(argv[i]);
        i++;
    }
 
    if(comp_d2==0){
        printAll = 1;
        i++;
    }
 
    while(i<argc-1){
        int comp2 = strcmp("-",argv[i]);
        if(comp2==0){
            pos = i;
        }
        else{
			strcpy(files[FILEAMOUNT],argv[i]);
            FILEAMOUNT++;
            
        }    
 
        i++;
    }
    char* fichierout = argv[argc-1];
    
	//////////FIN LECTURE PARAMETRES////////:
	
	printf("maxThreads : %d \n",MAXTHREADS);
	printf("file amount : %d \n",FILEAMOUNT);
	for(i=0;i<100;i++){
		if(files[i] !=NULL){
			printf("file: %s \n",files[i]);
		}
	}
	emptyFract=fractal_new(-1,-1,-1.0,-1.0,"empty");
	for(int i =0;i<10;i++){
		slots[i]=emptyFract;
	}
	
	
	int err=pthread_mutex_init( &mutexFractal, NULL); 
	if(err!=0) 
		error(err,"pthread_mutex_init");
	sem_init(&empty, 0 , 10); // buffer vide
	sem_init(&full, 0 , 0); // buffer vide
	printf("Before producer call");
	producer();
	
	
	
    return 0;
}
