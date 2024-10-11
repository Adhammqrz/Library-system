#ifndef MAIN_H
#define MAIN_H


#include <stdio.h>
#include <string.h>


typedef struct{
    char username[30];
    char password[30];
    int role;
} User;

typedef struct{
    char id[50];
    char title[50];
    char author[50];
    char genre[50];
    int quantity;
} Book;


int validation(User *data, int totaluser, char *inputusername, char *inputpass);

int loaduserdata(char *filename, User *data);
#endif // MAIN_H


