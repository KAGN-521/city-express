#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include "Invoice.h"
#include "Files.h"

int main()
{

    // Change the language of the terminal
    setlocale(LC_ALL,"spanish");

    // Generals Configs
    struct TextFile *files;

    int totalFloors;
    int totalRooms;

    printf("\n\tHola!\n\n");
    printf("\tPrimero que nada necesitamos algo de información,\n");
    printf("\tpor favor complete el siguiente formulario!\n");
    printf("\n\tCuantos pisos tiene el hotel ? : ");
    scanf("%d", &totalFloors);
    printf("\tCuantas habitaciones tiene cada piso ? : ");
    scanf("%d", &totalRooms);
    printf("\n\tGracias y disfrute el sistema!\n\n");
    system("cls");

    // First we need to create the array of reservations and allocate the memory.
    struct Reserve **listRes;

    int canFloors = 0;
    int canRooms = 0;
    int totalReserves = totalFloors * totalRooms;
    int canReserves = 0;

    listRes = (struct Reserve*) malloc(totalRooms * sizeof(struct Reserve));

    for(int i=0; i<totalFloors; i++)
    {
        listRes[i] = (struct Reserve*) malloc(totalFloors * sizeof(struct Reserve));
    }

    // This count is for the control of the rooms.
    int numberRooms = 0;

    // Main menu
    int option = 0;
    while(option != 5)
    {
        system("cls");
        printf("\n\tBienvenido!                                                 Ocupadas: %d / %d Libres\n", canReserves, totalReserves - canReserves);
        printf("\t1. Crear una nueva reservación.\n");
        printf("\t2. Mostrar solo clientes.\n");
        printf("\t3. Mostrar reservaciones con clientes.\n");
        printf("\t4. Crear balance.\n");
        printf("\t5. Salir\n");
        scanf("%d", &option);

        switch(option)
        {
        case 1: // This case create a new reservation.
        {
            if(canReserves == totalReserves)
            {
                printf("\n\tLo sentimos pero el hotel esta lleno!\n\n");
                system("pause");
                break;
            }

            system("cls");
            int numberClients, currentHour, numberNights, allInclude;
            printf("\n\tComplete el siguiente formulario!\n\n");
            printf("\t1. Que hora es ? (ej: 7) : ");
            scanf("%d", &currentHour);
            printf("\t2. Cuantas noches estaran ? : ");
            scanf("%d", &numberNights);
            printf("\t3. 'Todo Incluido' ? (1 = Si / 0 = No) : ");
            scanf("%d", &allInclude);
            printf("\t4. Cuantos clientes son ? : ");
            scanf("%d", &numberClients);

            // We can register more than 5 clients per reserve.
            if(numberClients > 5)
            {
                printf("\n\tEl hotel solo puede registrar 5 clientes por reservacion!\n\n");
                system("pause");
                break;
            }

            printf("\n\tIngrese la infomacion de los clientes:\n");

            // Now we create the structure.
            struct Reserve res;
            res.length = numberClients;
            res.entryTime = currentHour;
            res.numberNights = numberNights;
            res.allIncluded = allInclude;
            res.numberRoom = numberRooms;

            // Then create the pointer and allocate memory for the array.
            struct Reserve *resPtr;
            resPtr = &res;
            resPtr->clients = (struct Client*) malloc(res.length * sizeof(struct Client));

            // Next add the clients in the array.
            for(int i = 0; i < resPtr->length; ++i)
            {
                int age = 0;
                printf("\n\tCliente %i:\n", i+1);
                printf("\tDNI: ");
                scanf("%s", (resPtr->clients+i)->dni);
                printf("\tNombre: ");
                scanf("%s", (resPtr->clients+i)->name);
                printf("\tEdad: ");
                scanf("%d", &(resPtr->clients+i)->age);
            }

            // This validate if the client is a younger and is alone.
            if(numberClients == 1 && resPtr->clients[0].age < 18)
            {
                printf("\n\tLo sentimos pero no aceptamos menores de edad solos!\n\n");
                system("pause");
                break;
            }

            if(canRooms == totalRooms)
            {
                canRooms = 0;
                canFloors++;
            }

            listRes[canFloors][canRooms] = *resPtr;
            canRooms++;
            numberRooms++;
            canReserves++;

            printf("\n\tReservacion creada exitosamente!\n\n");
            system("pause");

            break;
        }
        case 2: // This case only show the clients in order of the reservation.
        {
            if(canReserves == 0)
            {
                printf("\n\tEl hotel no tiene clientes que mostrar!\n\n");
                system("pause");
                break;
            }

            int aux = 0;
            for(int i=0; i<=canFloors; i++)
            {
                for(int j=0; j<totalRooms; j++)
                {
                    if(aux <= canReserves - 1)
                    {
                        int canClients = listRes[i][j].length;
                        printf("\n\t\tReserva #%d:", aux+1);
                        for(int k=0; k<canClients; k++) // This loop is for the clients in the reservation.
                        {
                            printf("\n\tCliente #%d:", k+1);
                            showClient(listRes[i][j].clients+k);
                        }
                        aux++;
                    }
                }
            }

            system("pause");
            break;
        }
        case 3:
        {
            if(canReserves == 0)
            {
                printf("\n\tEl hotel no tiene reservaciones que mostrar!\n\n");
                system("pause");
                break;
            }

            int aux = 0;

            for(int i=0; i<=canFloors; i++)
            {
                for(int j=0; j<totalRooms; j++)
                {
                    if(aux <= canReserves - 1)
                    {
                        printf("\n\t\tReserva #%d:\n", aux+1);
                        showReserve(&listRes[i][j]);
                        aux++;
                    }
                }
            }

            system("pause");
            break;
        }
        case 4:
        {
            generalBalance(totalReserves, canReserves);

            if(canReserves == 0)
            {
                printf("%s", principal);
                writeFile(principal); //writing in the text file
                strcpy(principal,"");

                printf("\n\tEl hotel actualmente no posee reservaciones para hacer un balance monetario!\n\n");
                printf("\n\tTambien se creo automaticamente un documento txt con el balance!\n\n");
                system("pause");
                break;
            }

            int olders = 0;
            int kids = 0;
            double allInclude = 0;
            double normals = 0;

            int aux = 0;

            for(int i=0; i<=canFloors; i++)
            {
                for(int j=0; j<totalRooms; j++)
                {
                    if(aux <= canReserves - 1)
                    {
                        olders += numberOlders(&listRes[i][j]);
                        kids += numberKids(&listRes[i][j]);

                        if(listRes[i][j].allIncluded == 1)
                        {
                            allInclude += invoiceTotal(&listRes[i][j]);
                        }
                        else
                        {
                            normals += invoiceTotal(&listRes[i][j]);
                        }
                        aux++;
                    }
                }
            }

            monetaryBalance(olders, kids, allInclude, normals);

            printf("%s", principal);
            writeFile(principal); //writing in the text file
            strcpy(principal,"");

            printf("\n\tTambien se creo automaticamente un documento txt con el balance!\n\n");
            system("pause");
            break;
        }

        case 5:
        {
            break;
        }

        default:
        {
            printf("\n\tEl numero no corresponde a ninguna opción!\n\n");
            system("pause");
            break;
        }
        }

    } // Close the for(;;).

    for(int i=0; i<totalFloors; i++)
    {
        free(listRes+i);
    }
    free(listRes);

    return 0;
}
