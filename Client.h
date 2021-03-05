#ifndef CLIENT_H
#define CLIENT_H

struct Client // Main structure.
{
    char dni[30];
    char name[30];
    int age;
};

char showClient(struct Client *client) // This function show the information about the client structure.
{
    printf("\n\t - DNI: %s\n", client->dni);
    printf("\t - Nombre: %s\n", client->name);
    printf("\t - Edad: %d\n", client->age);
}

#endif // CLIENT_H
