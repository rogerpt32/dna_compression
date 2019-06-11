#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int label(char c){
    switch(c){
        case 'A': 
            return 0;
        case 'C': 
            return 1;
        case 'G': 
            return 2;
        case 'T': 
            return 3;
        default:
            break;        
    }
    return -1;
}

char hash(char* key){
    printf("%c%c%c%c\n",key[0],key[1],key[2],key[3]);
    return ((label(key[0])<<6)|(label(key[1])<<4)|(label(key[2])<<2)|label(key[3]))%256;
}

int main() {
    char labels[4]={'A','C','G','T'};
    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
            for(int k=0; k<4; ++k){
                for(int l=0; l<4; ++l){
                    char key[4]={labels[i],labels[j],labels[k],labels[l]};
                    printf("%c%c%c%c\t%02hhx\n",labels[i],labels[j],labels[k],labels[l],hash(key));
                }
            }
        }
    }
}