#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int main (int argc, char *argv[]) {
    if(argc!=3 && argc!=4){
        fprintf(stderr,"Error: Wrong number of arguments\n");
        return -1;
    }
    int n = atoi(argv[1]);
    char* fname = argv[2];
    char* fname2;
    char labels[4]={'A','C','G','T'};
    time_t t;
    int counter=0;

    /* Intializes random number generator */
    srand((unsigned) time(&t));

    FILE *file;
    if((file = fopen(fname, "w")) == NULL){
        fprintf(stderr,"Error: Opening file to write %s\n",fname);
        return -1;
    }
    FILE *file2;
    if(argc==4){
        fname2=argv[3];
        if((file2 = fopen(fname2, "w")) == NULL){
            fprintf(stderr,"Error: Opening file to write %s\n",fname2);
            return -1;
        }
        fprintf(file2, "> random_file  %d nb\n",n);
    }

    for(int i = 0 ; i < n ; i++ ) {
        int aux=rand()%4;
        putc((int)labels[aux],file);
        if(argc==4){
            putc((int)labels[aux],file2);
            ++counter;
            if(counter>=79){
                fprintf(file2, "\n");
                counter=0;
            }
        }
    }
    fclose(file);
    if(argc==4)fclose(file2);
    return 0;
}