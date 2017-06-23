//
// Created by roey on 02/04/17.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct virus virus;

struct virus {
    unsigned short length;
    char name[16];
    char signature[1000];
};

int main(int argc, char** argv){
  struct virus Myvirus; int dynamic =1;
   FILE* fp; int counter=0; int length;
    fp = fopen(argv[1],"r");
    char buffer1[1]; char buffer2[2];
    if(fread(buffer1, 1, 1, fp)!=1){//big and little indian
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    while(fread(buffer2, 1, 2, fp)){

        if(buffer1[0]==1){//regular reading-big endian
            char tmp=buffer2[0];buffer2[0]=buffer2[1];buffer2[1]=tmp;
            length=*((unsigned short*)(buffer2));
            fread(Myvirus.name, 1, 16, fp);
            printf("Virus name:%s\n",Myvirus.name);
            Myvirus.length=length-18;
            printf("Virus size: %d\n",Myvirus.length);
            length=Myvirus.length-18;
            fread(Myvirus.signature, 1, Myvirus.length, fp);
            printf("signature:\n");
            PrintHex(Myvirus.signature,Myvirus.length);
            printf("\n");
            printf("\n");


        }
        else {//little endian
            length=*((unsigned short*)(buffer2));
            fread(Myvirus.name, 1, 16, fp);
            printf("Virus name:%s\n",Myvirus.name);
            Myvirus.length=length-18;
            printf("Virus size: %d\n",Myvirus.length);
            length=Myvirus.length-18;
            fread(Myvirus.signature, 1, Myvirus.length, fp);
            printf("signature:\n");
            PrintHex(Myvirus.signature,Myvirus.length);
            printf("\n");
            printf("\n");

        }



}
fclose(fp);
}

void PrintHex(char buffer[],int  length) {
    for (int i = 0; i < length; i++) {
        printf("%02X ", (unsigned char) buffer[i]);
    }

}