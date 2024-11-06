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
    char shelfID[50];
    char id[50];
    char title[50];
    char author[50];
    char genre[50];
    char status[50];
    char type[50];
} Book;

typedef struct {
    char id[50];
    char title[50];
    int count;
} popular_book;

typedef struct{
    char name[100];
    char username[50];
    char password[50];
    int role;
    char status[50];
} Member;

typedef struct{
    char username[50];
    char bookid[50];
    char booktitle[50];
    char duedate[50];
    char status[50];
    int fines;
}BorrowBook;

int validation(char *inputusername, char *inputpass);

#endif // MAIN_H



