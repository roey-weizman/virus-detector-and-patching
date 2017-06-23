

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc,char ** argv)
{
   FILE *fp; char buffer[1];
   
   fp = fopen(argv[1],"r"); // read mode
 
   if( fp == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   fseek(fp, SEEK_SET, 0);
 
   while(fread(buffer,1,1,fp)==1){
    PrintHex(buffer, 1);
} 
 printf("\n");
   fclose(fp);
   return 0;
} 
void PrintHex(char buffer[],int  length){
 for(int i=0;i<length;i++){
    printf("%X ", (unsigned char)buffer[i]);
 }
}
