
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFF 10000
typedef struct link link;


typedef struct virus virus;

struct virus {
    unsigned short length;
    char name[16];
    char signature[1000 ];
};
struct link {
    virus *v;
    link *next;
};
link* list_append(link* virus_list, virus* data){
    if(virus_list==NULL){
        virus_list=(link*)malloc(sizeof(link));
        virus_list->v=data;
        virus_list->next=NULL;
        return virus_list;}
    link* linkNew=(link*)malloc(sizeof(link));
    linkNew->v=data;
    linkNew->next=NULL;
    link* curr=virus_list;
    while(curr->next!=NULL){
        curr=curr->next;
    }
    curr->next=linkNew;
    return virus_list;
}
void list_print(link *virus_list) {
    link *curr = virus_list;
    while (curr != NULL) {
        printf("Virus name:%s\n",curr->v->name);
        printf("Virus size: %d\n",curr->v->length);
        printf("signature:\n");
        PrintHex(curr->v->signature,curr->v->length);
        printf("\n");
        printf("\n");
        curr=curr->next;
    }
}


void list_free(link *virus_list){
    link *curr = virus_list;
    while (curr != NULL) {
        link* next=curr->next;
        free(curr->v);
        free(curr);
        curr=next;
    }
} /* Free the memory allocated by the list. */


int main(int argc, char** argv){
    struct virus Myvirus;
    FILE* fp; int counter=0; int length;
    fp = fopen(argv[1],"r");
    char buffer1[1]; char buffer2[2];
    if(fread(buffer1, 1, 1, fp)!=1){//big and little indian
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    link* a=NULL;
    FILE* file=fopen(argv[2],"r+");
    while(fread(buffer2, 1, 2, fp)){
        if(buffer1[0]==1){//regular reading-big endian
                        char tmp=buffer2[0];buffer2[0]=buffer2[1];buffer2[1]=tmp;

            length=*((unsigned short*)(buffer2));
            virus* vir1=(virus*)malloc(sizeof(virus));
            fread(vir1->name, 1, 16, fp);
            vir1->length=length-18;
            length=vir1->length-18;
            fread(vir1->signature, 1, vir1->length, fp);
            a=list_append(a, vir1);




        }
        else {//little endian
            length=*((unsigned short*)(buffer2));
            virus* vir1=(virus*)malloc(sizeof(virus));
            fread(vir1->name, 1, 16, fp);
            printf("Virus name:%s\n",vir1->name);
            vir1->length=length-18;
            printf("Virus size: %d\n",vir1->length);
            length=vir1->length-18;
            fread(vir1->signature, 1, vir1->length, fp);
            printf("signature:\n");
            PrintHex(vir1->signature,vir1->length);
            printf("\n");
            printf("\n");
            a=list_append(a, vir1);

        }



    }

    char infBuffer[MAX_BUFF];
    if(file){
        size_t p=fread(infBuffer,1,MAX_BUFF,file);
        if(ferror(file)!=0){
            fputs("error loading file",stderr);
        }
        else{
            detect_virus(infBuffer,a,p);

        }
    }
    //list_print(a);
    list_free(a);
    fclose(fp);
    fclose(file);
    return 0;
}

void PrintHex(char buffer[],int  length) {
    for (int i = 0; i < length; i++) {
        printf("%02X ", (unsigned char) buffer[i]);
    }
}
void detect_virus(char buffer[], link *virus_list, unsigned int size){
    int j=0;
    for(;j<size;j++){
        link * tmp=virus_list;
        while(tmp!=NULL){
            if(memcmp(tmp->v->signature, buffer+j,tmp->v->length)==0){
                printf("The starting byte location in the suspected file is :%d\n",j);
                printf( "The detected  virus name is : %s\n",tmp->v->name );
                printf( "The size of the virus signature is : %d\n\n",tmp->v->length );

            }tmp=tmp->next;
        }
    }
}
//
// Created by roey on 02/04/17.
//

