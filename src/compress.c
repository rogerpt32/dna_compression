#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *rename_file(char *name){
    char *dot, *newname;
    int len;
    
    /* Get position of the last dot in the name */
    dot = strrchr(name, '.');
    /* If a dot was found, calculate the length to this point */
    if(dot) len = dot - name;
    else len = strlen(name);
    /* Allocate a buffer big enough to hold the result.
    * 6 extra characters: 5 for "C.dat", 1 for null byte */
    newname = malloc(len + 16);
    /* Build the new name */
    strncpy(newname, name, len);
    strcpy(newname + len, "_compressed.dna");
    return newname;
}

int label(char c){
    return 0b11 & (c>>1);
}

int hash(char* key){
    return ((label(key[0])<<6)|(label(key[1])<<4)|(label(key[2])<<2)|label(key[3]))%256;
}

int main(int argc, char *argv[]) {
    if(argc!=2){
        fprintf(stderr,"Error: Wrong number of arguments\n");
        return -1;
    }

    // Generate Hashtable (dictionary)
    char labels[4]={'A','C','G','T'};
    char counter=0x00;
    char hashtable[256];

    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
            for(int k=0; k<4; ++k){
                for(int l=0; l<4; ++l){
                    char key[4]={labels[i],labels[j],labels[k],labels[l]};
                    hashtable[hash(key)]=counter++;
                    //printf("%s\t%02hhx\n",key,hashtable[hash(key)]);
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
    int endfile=0;
    while(!endfile){
        int aux;
        char c[4];
        int pos=0;
        int final=0;
        while (pos<4){
            if((aux = fgetc(infile)) != EOF){
                c[pos++] = (char) aux;
            }
            else{
                endfile=1;
                final=4-pos; // number of extra characters to fill last key
                while (pos<4) c[pos++]='A';
            }
        }
        if(final>3) putc(0,outfile);
        else {
            int out = (int) hashtable[hash(c)];
            putc((unsigned char) out,outfile);
            if(endfile) putc(final,outfile);
        }
    }
    fclose(infile);
    fclose(outfile);
}