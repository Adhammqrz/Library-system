#include <stdio.h>
#include <string.h>


typedef struct{
    char username[30];
    char password[30];
    int role;
} User;

int validation(User *data,int totaluser, char *inputusername ,char *inputpass){
        for (int i=0; i<totaluser; i++)
        {
            if (strcmp(data[i].username, inputusername) == 0 && strcmp(data[i].password, inputpass) == 0)
                return data[i].role;
            }
        return -1;
}


int loaduserdata(char *filename, User *data){
    FILE *fptr=fopen(filename,"r");

    if (fptr==NULL){
        printf("Error: no %s found!", filename);
        return 0;
    }

    /*char line[100];*/
    int counter=0;
    char line[100];

    while (fgets(line, sizeof(line),fptr)){
        sscanf(line,"%s %s %d", data[counter].username, data[counter].password, &data[counter].role);
        counter++;
    }
    fclose(fptr);
    return counter;
}

