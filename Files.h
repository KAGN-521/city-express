#ifndef FILES_H
#define FILE_H
#include <stdio.h>

char principal[99999];


struct TextFile {
    FILE *f;
};

//open a writting file only
struct TextFile *openWriteFile(char fileName[]) {

    struct TextFile *f = fopen(fileName,"w");

    return f;
}

//open a reading file only
struct TextFile *openReadFile(char fileName[]) {
    struct TextFile *f = fopen(fileName,"r");

    if(f==NULL) {
        fprintf(stderr,"\nError Opened File\n");
        exit(1);
    }

    return f;
}

//close the file
void closeFile(struct TextFile *f) {
    fclose(f);
}

//write inside the file
void writeFile(char content[]) {

    //opens the writting file
    FILE *esc = openWriteFile("Balance.txt");

    // write struct to file
    fputs(content,esc);

    //closing the file
    closeFile(esc);
}

//Read a specific File
void ReadFile(char fileName[]) {

    FILE *r = openReadFile(fileName);
    int c;

    while ((c = fgetc (r)) != EOF)
        putchar(c);

    closeFile(r);
}

void generalBalance(tam,can) {
    char str3[100];
    char str4[100];
    char str5[100];
    strcpy(principal,"");

    strcat(principal,"\n\t\tBalance General:\n\n");
    sprintf(str3,"\tTotal de Habitaciones: %d\n", tam);
    sprintf(str4,"\tHabitaciones Libres: %d\n", (tam - can));
    sprintf(str5,"\tHabitaciones ocupadas: %d\n", can);

    strcat(principal,str3);
    strcat(principal,str4);
    strcat(principal,str5);
}

void monetaryBalance(int olders, int kids, double allInclude, double normals ) {
    char str1[100];
    char str2[100];
    char str6[100];
    char str7[100];
    char str8[100];

    sprintf(str1,"\tAdultos: %d\n", olders);
    sprintf(str2,"\tNiños: %d\n", kids);
    sprintf(str6,"\t - Clientes 'Todo Incluido': $%0.2f\n", allInclude);
    sprintf(str7,"\t - Clientes 'Normales': $%0.2f\n", normals);
    sprintf(str8,"\t - Total: $%0.2f\n\n", (allInclude + normals));

    strcat(principal,str1);
    strcat(principal,str2);
    strcat(principal,"\tBalance Monetario: \n");
    strcat(principal,str6);
    strcat(principal,str7);
    strcat(principal,str8);

}


#endif // FILES_H
