#include <stdio.h>


int validation(id,pass,correctid,correctpass)
{
    return (id==correctid && pass==correctpass);
}


void loginmenu()
{
    int roles;
    printf(" 1:Admin | 2:Doctor | 3:Nurse | 4:Patient ");
    printf("\nWelcome, who are you signing as?\n");
    scanf("%d",&roles);
    return roles;
}


int librarianlogin()
{
    int adminID=001, adminpassword=1234;
    int ID,password;
    printf("\nenter your ID:");
    scanf("%d",&ID);
    printf("\nenter your password:");
    scanf("%d",&password);

    if (validation(ID, password, adminID, adminpassword))
    {
        printf("Login Succesful!\n");
        return true;
    }
    else
    {
        printf("login failed!");
        return false;
    }
}
