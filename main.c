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
    printf("Please choose:");
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
                        printf("okay");
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


void displayoption(int domain){
    if (domain==1){
        printf("\n--- Book Inventory Management ---\n");
        printf("\n1. Add Books");
        printf("\n2. Update Books");
        printf("\n3. Remove Books");
        printf("\n0. exit");
        printf("\nplease choose:");
    }

    if (domain==2){
        printf("\n--- Membership Management ---\n");
        printf("\n1. Add New Member");
        printf("\n2. Update Member Information");
        printf("\n3. Manage Memberships");
        printf("\n0. exit");
        printf("\nplease choose:");
    }
    if (domain==3){
        printf("\n--- Borrowing and Return ---\n");
        printf("\n1. Book Borrowed List");
        printf("\n2. Overdue Fines");
        printf("\n0. exit");
        printf("\nplease choose:");
    }
    if (domain==4){
        printf("\n--- Report Generation ---\n");
        printf("\n1. Popular Books");
        printf("\n2. Overdue Books");
        printf("\n3. Book Circulation");
        printf("\n0. exit");
        printf("\nplease choose:");
    }
}

void bookmanagement(){
    int domain1;
    do{
        displayoption(1);
        while (scanf("%d", &domain1) != 1) {
        printf("Invalid input! Please try again.\n");
        displayoption(1);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        }

        if (domain1==1)
        {
            printf("\n--- Book addition ---\n");
            addbook();
            break;
        }
        else if (domain1==2){
            printf("\n--- Book updation ---\n");
            displaybook();
            updatebook();
            break;
        }
        else if (domain1==3){
            printf("\n--- Book deletion ---\n");
            displaybook();
            deletebook();
            break;
        }
        else if (domain1==0){
            printf("....");
        }
        else{
            printf("Invalid Input! Please try again");
        }

        }while (domain1!=0);
}


void membermanagement(){
    int domain2;
    do{
        displayoption(2);
        while (scanf("%d", &domain2) != 1) {
        printf("Invalid input! Please try again.\n");
        displayoption(2);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        }

        switch (domain2){
        case 1:
            printf("\n--- Member Registration ---\n");
            registermember();
            break;

        case 2:
            printf("\n--- Member Information Updation ---\n");
            displaymember();
            updatemember();
            break;

        case 3:
            printf("membership");
            break;
        case 0:
            printf("....");
            break;
        default:
            printf("Invalid Input! Please try again");
            }

        }while (domain2!=0);

        printf("okay");

}

void borrowreturn(){
    int domain3;
    do{
        displayoption(3);
        while (scanf("%d", &domain3) != 1) {
        printf("Invalid input! Please try again.\n");
        displayoption(3);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        }

        if (domain3==1)
        {
            printf("book borrow list");
        }
        else if (domain3==2){
            printf("overdue fines");
        }
        else if (domain3==0){
            printf("....");
        }
        else{
            printf("Invalid Input! Please try again");
        }

        }while (domain3!=0);
}

void reportgeneration(){
    int domain4;
    do{
        displayoption(4);
        while (scanf("%d", &domain4) != 1) {
        printf("Invalid input! Please try again.\n");
        displayoption(4);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        }

        if (domain4==1)
        {
            printf("popular book");
        }
        else if (domain4==2){
            printf("overdue book");
        }
        else if (domain4==3){
            printf("book circulation");
        }
        else if (domain4==0){
            printf("....");
        }
        else{
            printf("Invalid Input! Please try again");
        }

        }while (domain4!=0);
}

