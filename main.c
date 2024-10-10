#include <stdio.h>
#include <string.h>
#include "main.h"

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
