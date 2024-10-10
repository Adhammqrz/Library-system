#include <stdio.h>
#include <string.h>


void librarianoptiondisplay(){
    printf("\n--- Welcome to the librarian page ---\n");
    printf("\n----------------------------------\n");
    printf("1. Book Inventory Management\n");
    printf("2. Membership Management\n");
    printf("3. Borrowing and Return\n");
    printf("4. Report Generation\n");
    printf("0. exit\n");
    printf("Your input:");
}

void librarianmenu()
{

            int domainchoice;
            ///book inventory
            do{
                librarianoptiondisplay();
                while (scanf("%d", &domainchoice) != 1) {
                printf("Invalid input! Please try again.\n");
                librarianoptiondisplay();
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                }


                switch (domainchoice){
                    case 1:
                        bookmanagement();
                        break;

                    case 2:
                        membermanagement();
                        break;


                    case 3:
                        borrowreturn();
                        break;

                    case 4:
                        reportgeneration();
                        break;

                    case 0:
                        printf("....");
                        break;
                        main();

                    default:
                        printf("invalid input! Please try again!\n");
                }
            }while (domainchoice!=0);


}

