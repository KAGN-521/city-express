#ifndef INVOICE_H
#define INVOICE_H

#include "Reserve.h"

// This function said what is the discount.
float perDiscount(int entryTime, int numberClients)
{
    float discount = 0;
    if(entryTime >= 6)
    {
        if(numberClients == 1)
        {
            discount = 0.25;
        }
        else if(numberClients == 2)
        {
            discount = 0.2;
        }
        else if(numberClients == 3)
        {
            discount = 0.15;
        }
        else if(numberClients > 3)
        {
            discount = 0.1;
        }
    }
    return discount;
}

// This function said what is the price per night when the service is Not All Included.
int priceNight(int num)
{
    int cost = 0;
    if(num == 1)
    {
        cost = 150;
    }
    else if(num == 2)
    {
        cost = 250;
    }
    else if(num == 3)
    {
        cost = 350;
    }
    else if(num > 3)
    {
        cost = 400;
    }
    return cost;
}

double invoiceTotal(struct Reserve *reserve)
{
    int numberClients = reserve->length;
    double total = 0;

    if(reserve->allIncluded == 0)
    {
        float subTotal = reserve->numberNights * priceNight(numberClients);
        float discount = subTotal * perDiscount(reserve->entryTime, numberClients);
        total = subTotal - discount;
    }
    else
    {
        total = (numberOlders(reserve) * 300 + numberKids(reserve) * 200) * reserve->numberNights;
    }

    return total;
}

// This function said how many olders client are in the reserve.
int numberOlders(struct Reserve *reserve)
{
    int num = 0;
    for(int i=0; i<reserve->length; i++)
    {
        if(reserve->clients[i].age > 12)
        {
            num++;
        }
    }
    return num;
}

// This function said how many kids are in the reserve.
int numberKids(struct Reserve *reserve)
{
    return reserve->length - numberOlders(reserve);
}

#endif // INVOICE_H
