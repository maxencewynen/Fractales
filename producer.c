#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fractal.h"
#include <semaphore.h>

typedef enum { false, true } bool;
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int MAXTHREADS=1;
int FILEAMOUNT=0;
struct fractal slots[10];
char files [100][100];


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
    /*
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0 , 10); // buffer vide
	sem_init(&full, 0 , 0); // buffer vide
	
    char test[]  = getFractal(argv[0],1);
    printf("test : %s",test);
	*/
	
    return 0;
}
/*
void producer(char files[]){
	
	int currentLine = 0;
	int currentFile = 0;
	
	while(true)
	{
		char fractal[]=getFractal(files[currentFile], currentLine);
		currentLine++;
		
		if(item[1]==true){
			currentFile++;
		}
		//ajouter de pas faire si #commentaire
		sem_wait(&empty); 
		pthread_mutex_lock(&mutex);
		
		addToSlots(fractal);
		
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
	
}

char[] getFractal(file, lineNumber){
	int currentline = 1;
	bool eof = false;
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
	FILE *fp = fopen(file, "r");
	
	if (fp == NULL){
        exit(EXIT_FAILURE);
	}
	
    while ((read = getline(&line, &len, fp)) != -1) {
        if(currentline == lineNumber){
			printf("Line found: %s", line); 
			if(read = getline(&line, &len, fp)) == -1){
				eof =true
			}
			break;
		}
      currentline++;
    }

    fclose(fp);
    if (line){
        free(line);
	}
	return [line,eof];
}

void insertItem(fractal){
	
}
*/
