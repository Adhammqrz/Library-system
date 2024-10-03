#include "headertester.h"


int loginmain()
{
    loginmenu();

    if (roles==1)
        {
            librarianlogin();
        }
}
    /*
    else if (roles==2)
    {
        printf("\nenter your ID:");
        scanf("%d",&ID);
        printf("\nenter your password:");
        scanf("%d",&password);

        if (validation(ID, password, doctorID, doctorpassword))
            printf("Login Succesful!\n");
        else
            printf("login failed!");
    }

    else if (roles==3)
    {
        printf("\nenter your ID:");
        scanf("%d",&ID);
        printf("\nenter your password:");
        scanf("%d",&password);

        if (validation(ID, password, nurseID, nursepassword))
            printf("Login Succesful!\n");
        else
            printf("login failed!");
    }

    else if (roles==4)
    {
        printf("\nenter your ID:");
        scanf("%d",&ID);
        printf("\nenter your password:");
        scanf("%d",&password);

        if (validation(ID, password, patientID, patientpassword))
            printf("Login Succesful!\n");
        else
            printf("login failed!");
    }

    else
        printf("invalid input! Please try again!");
}*/
