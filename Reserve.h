#ifndef RESERVE_H
#define RESERVE_H

#include "Client.h"

struct Reserve
{
    struct Client *clients;

    int length;
    int numberNights;
    int entryTime;
    int allIncluded;
    int numberRoom;
};

void showReserve(struct Reserve *reserve)
{
    printf("\t1. Cantidad de Noches: %d\n", reserve->numberNights);
    printf("\t2. Hora de entrada: %d\n", reserve->entryTime);
    char state[3];
    reserve->allIncluded == 1 ? strcpy(state, "Si") : strcpy(state, "No");
    printf("\t3. Todo Incluido: %s\n", state);
    printf("\t4. Numero de Habitacion: %d\n", reserve->numberRoom);
    printf("\t4. Informacion de los clientes: \n");
    for(int i=0; i<reserve->length; i++){
        printf("\n\t\tCliente #%d :\n", i+1);
        showClient(reserve->clients+i);
    }
}

#endif // RESERVE_H
