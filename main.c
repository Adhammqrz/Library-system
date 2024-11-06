#include "main.h"

int validation(char *inputusername ,char *inputpass){
    FILE *fptr=fopen("userdata.txt","r");
    FILE *file=fopen("member.txt","r");

    if (fptr==NULL || file==NULL){
        printf("File not found!");
        return;
    }
    User user;
    Member member;
    char line[2048];

    while (fgets(line, sizeof(line),fptr) != NULL){
        if (strcmp(line, "\n") != 0) {

            sscanf(line, "%49[^,],%49[^,],%d", user.username, user.password, &user.role);

            if (strcmp(user.username, inputusername) == 0 && strcmp(user.password, inputpass) == 0){
                if (fclose(file)!= 0)
                    perror("error");
                if (fclose(fptr)!= 0)
                    perror("error");

                return user.role;
            }
            }
    }

    while (fgets(line, sizeof(line),file) != NULL){
    if (strcmp(line, "\n") != 0) {

        sscanf(line, "%49[^,],%49[^,],%d", member.username, member.password, &member.role);

        if (strcmp(member.username, inputusername) == 0 && strcmp(member.password, inputpass) == 0){
                if (fclose(file)!= 0)
                    perror("error");
                if (fclose(fptr)!= 0)
                    perror("error");

            return member.role;
            }
        }
    }
    if (fclose(file)!= 0)
        perror("error");
    if (fclose(fptr)!= 0)
        perror("error");
    return -1;
}

int main()
{
    User userdata[100];
    Member memberdata[100];
    char username[30];
    char password[30];
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
            printf("\n--- Login ---");
            printf("\nenter your usename:");
            scanf("%s",&username);
            printf("\nenter your password:");
            scanf("%s",&password);

            int role = validation(username,password);

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
                printf("login successful!\n");
                membermenu();
            }
            else
            {
                printf("login failed!");
            }
            break;


        case 2:
            printf("\nWelcome, guest!");
            guestmenu();
            break;

        case 3:
            printf("\nplease register!\n");

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
