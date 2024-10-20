#ifndef MAIN_H
#define MAIN_H


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct{
    char username[50];
    char password[50];
    int role;
} User;

typedef struct{
    char id[50];
    char title[50];
    char author[50];
    char genre[50];
    int quantity;
    char type[50];
} Book;

typedef struct{
    char name[100];
    char username[50];
    char password[50];
    int role;
    char status[50];
} Member;


int validation(char *inputusername, char *inputpass);

#endif // MAIN_H


