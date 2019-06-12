#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *rename_file(char *name){
    char *uscore, *newname;
    int len;
    
    /* Get position of the last dot in the name */
    uscore = strrchr(name, '_');
    /* If a dot was found, calculate the length to this point */
    if(uscore) len = uscore - name;
    else len = strlen(name);
    /* Allocate a buffer big enough to hold the result.
    * 6 extra characters: 5 for "C.dat", 1 for null byte */
    newname = malloc(len + 18);
    /* Build the new name */
    strncpy(newname, name, len);
    strcpy(newname + len, "_decompressed.txt");
    return newname;
}

int main(int argc, char *argv[]) {
    if(argc!=2){
        fprintf(stderr,"Error: Wrong number of arguments\n");
        return -1;
    }

    // Generate Hashtable (dictionary)
    char labels[4]={'A','C','G','T'};
    int counter=0;
    char hashtable[256][4];

    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
            for(int k=0; k<4; ++k){
                for(int l=0; l<4; ++l){
                    hashtable[counter][0]=labels[i];
                    hashtable[counter][1]=labels[j];
                    hashtable[counter][2]=labels[k];
                    hashtable[counter++][3]=labels[l];
                }
            }
        }
    }
    // Open files to read and write
    FILE *infile;
    char *fname = argv[1];
    if((infile = fopen(fname, "r")) == NULL){
        fprintf(stderr,"Error: Opening file %s\n",fname);
        return -1;
    }

    FILE *outfile;
    char *outfname = rename_file(fname);
    if((outfile = fopen(outfname, "w")) == NULL){
        fprintf(stderr,"Error: Opening file to write %s\n",outfname);
        return -1;
    }

    // Compress file
    int aux;
    unsigned char c1,c2;
    
    if((aux = fgetc(infile)) != EOF){
        c2 = (char) aux;
        if((aux = fgetc(infile)) != EOF){
            c1 = (char) aux;
        }
    }
    while((aux = fgetc(infile)) != EOF){
        fwrite(hashtable[(int)c2],sizeof(char),4,outfile);
        c2 = c1;
        c1 = (char) aux;
    }
    fwrite(hashtable[(int)c2],sizeof(char),4-(int)c1,outfile);
    fclose(infile);
    fclose(outfile);
}