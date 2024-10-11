#include "main.h"

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

    int counter=0;
    char line[100];

    while (fgets(line, sizeof(line),fptr)){
        sscanf(line,"%s %s %d", data[counter].username, data[counter].password, &data[counter].role);
        counter++;
    }
    fclose(fptr);
    return counter;
}

int main()
{
    User userdata[100];
    char username[30];
    char password[30];
    int totalusers=loaduserdata("userdata.txt", userdata);
    int loginchoice;

    do{
        printf("\n---- APU Digital Library System ----\n");
        printf("\n(1)Login | (2)Guest | (3)Register | (0) exit \n Please choose:");
        while (scanf("%d", &loginchoice) != 1) {
            printf("Invalid input! Please try again.\n");
            printf("\n---- APU Digital Library System ----\n");
            printf("\n(1)Login | (2)Guest | (3)Register | (0) exit \n Please choose:");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        switch (loginchoice){
        case 1:
            printf("\nPlease Login!");
            printf("\nenter your usename:");
            scanf("%s",&username);
            printf("\nenter your password:");
            scanf("%s",&password);

            int role = validation(userdata,totalusers,username,password);

            if (role==1)
            {
                printf("login successful!\n");
                librarianmenu();
            }
            else if (role==2)
            {
                printf("login successful! welcome staff");
            }
            else if (role==3)
            {
                printf("login successful! welcome member");
            }
            else
            {
                printf("login failed!");
            }
            break;


        case 2:
            printf("\nWelcome, guest!");
            break;

        case 3:
            printf("\nplease register!");
            break;

        case 0:
            printf("exiting...\n");
            break;

        default:
            printf("Invalid input! Please try again!\n");
        }

    }while (loginchoice!=0);
    return 0;

}
