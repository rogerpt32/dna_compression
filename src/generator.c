#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int main (int argc, char *argv[]) {
    if(argc!=3){
        fprintf(stderr,"Error: Wrong number of arguments\n");
        return -1;
    }
    int n = atoi(argv[1]);
    char* fname = argv[2];
    char labels[4]={'A','C','G','T'};
    time_t t;

    /* Intializes random number generator */
    srand((unsigned) time(&t));

    FILE *file;
    if((file = fopen(fname, "w")) == NULL){
        fprintf(stderr,"Error: Opening file to write %s\n",fname);
        return -1;
    }

    for(int i = 0 ; i < n ; i++ ) {
        putc((int)labels[rand()%4],file);
    }
    fclose(file);

    return 0;
}