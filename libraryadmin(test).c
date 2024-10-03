#include <stdio.h>
#include <stdbool.h>
#include "headertester.h"

int main()
{
    if (librarianlogin()==true)
    {
        printf("\n--- Welcome to the librarian page ---\n");
        printf("\n----------------------------------\n");
        printf("1. Book Inventory Management\n");
        printf("2. Membership Management\n");
        printf("3. Borrowing and Return\n");
        printf("4. Report Generation\n");

        int domainchoice;
        int domain[4]={1,2,3,4};
        printf("Your input:");
        scanf("%d",&domainchoice);

        ///book inventory
        if (domainchoice==domain[0])
        {
            printf("\n--- Book Inventory Management ---\n");
            printf("\n1. Add Books");
            printf("\n2. Update Books");
            printf("\n3. Remove Books");
        }

        else if (domainchoice==domain[1])
        {
            printf("\n--- Book Inventory Management ---\n");
            printf("\n1. Add New Member");
            printf("\n2. Update Member Information");
            printf("\n3. Manage Memberships");
        }

        else if (domainchoice==domain[2])
        {
            printf("\n--- Borrowing and Return ---\n");
            printf("\n1. Book Borrowed List");
            printf("\n2. Overdue Fines");
        }

        else if (domainchoice==domain[3])
        {
            printf("\n--- Report Generation ---\n");
            printf("\n1. Popular Books");
            printf("\n2. Overdue Books");
            printf("\n3. Book Circulation");
        }

        else
        {
            printf("Invalid input! PLease Try Again!");
        }

        ///membership management
        {

        }
    }
    else

}
