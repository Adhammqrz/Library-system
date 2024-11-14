#include "main.h"


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

void librarianmenu(){
            int domainchoice;
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


void displayoption(int domain){
    if (domain==1){
        printf("\n--- Book Inventory Management ---\n");
        printf("\n1. Add Books");
        printf("\n2. Update Books");
        printf("\n3. Remove Books");
        printf("\n4. Display Books List");
        printf("\n0. exit");
        printf("\nplease choose:");
    }

    if (domain==2){
        printf("\n--- Membership Management ---\n");
        printf("\n1. Add New Member");
        printf("\n2. Update Member Information");
        printf("\n3. Display Member List");
        printf("\n0. exit");
        printf("\nplease choose:");
    }
    if (domain==3){
        printf("\n--- Borrowing and Return ---\n");
        printf("\n1. Book Borrowing System");
        printf("\n2. Book Returning System");
        printf("\n3. Overdue Book System");
        printf("\n4. Borrowed Book List");
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

        if (domain1==1){
            printf("\n--- Book addition ---\n"); ///add new book
            addbook();
        }
        else if (domain1==2){
            printf("\n--- Book updation ---\n"); ///update book
            displaybook(1);
            updatebook();
        }
        else if (domain1==3){
            printf("\n--- Book deletion ---\n"); ///delete book
            displaybook(1);
            deletebook();
        }
        else if (domain1==4){
            displaybook(2);
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
        if (domain2==1){
            printf("\n--- Member Registration ---\n"); ///add new member
            registermember();
        }

        else if(domain2==2){
            printf("\n--- Member Information Updation ---\n"); ///update member information
            displaymember();
            updatemember();
        }

        else if(domain2==3){
            printf("\n--- Member List ---\n"); ///member information list
            displaymember();
        }

        else if(domain2==0){
            printf("....");
        }
        else
            printf("Invalid Input! Please try again");

        }while (domain2!=0);
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
        if (domain3==1){
            printf("\n--- Book Borrowing System ---\n"); ///borrowing system
            borrow_book();
        }
        else if (domain3==2){
            printf("\n---- Book Returning System---\n"); ///returning book system
            display_borrow_book(1);
            return_book();
        }

        else if (domain3==3){
            printf("\n--- Overdue Book System ---\n"); ///overdue the selected items with fines
            display_borrow_book(2);
            overduesystem();
        }

        else if (domain3==4){
            printf("\n--- Borrowing Book List ---\n"); ///display borrowed book list
            display_borrow_book(1);
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
        if (domain4==1){
            printf("\n--- popular book ---\n"); ///show popular book
            popularbook();
        }
        else if (domain4==2){
            printf("\n--- overdue book ---\n"); ///show all overdue book
            overdueitem();
        }
        else if (domain4==3){
            printf("\n--- book circulation ---\n"); ///list all borrow history book
            bookcirculation();
        }
        else if (domain4==0){
            printf("....");
        }
        else{
            printf("Invalid Input! Please try again");
        }

        }while (domain4!=0);
}

int isUsernameUnique(const char *newUsername) {
    FILE *file = fopen("member.txt", "r");
    if (file == NULL) {
        printf("Error: unable to open file.\n");
        return 0;
    }

    char line[2048];
    Member data;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "\n") != 0) {
            sscanf(line, "%49[^,],%49[^,],%d,%99[^,],%49[^,]", data.username, data.password, &data.role, data.name, data.status);
            if (strcmp(data.username, newUsername) == 0) {
                fclose(file);
                return 0; // Username already exists
            }
        }
    }

    fclose(file);
    return 1; // Username is unique
}

int isBookUnique(const char *newId) {
    FILE *file = fopen("book.txt", "r");
    if (file == NULL) {
        printf("Error: unable to open file.\n");
        return 0;
    }

    char line[2048];
    Book data;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "\n") != 0) {
            sscanf(line,"%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,]", data.shelfID,data.id,data.title,data.author,data.genre,data.status,data.type);
            if (strcmp(data.id, newId) == 0) {
                fclose(file);
                return 0; // Username already exists
            }
        }
    }

    fclose(file);
    return 1; // Username is unique
}

int isBorrowUnique(const char *username, const char *ID){
    FILE *file = fopen("borrowbook.txt", "r");
    FILE *file2 = fopen("member.txt", "r");
    if (file == NULL) {
        printf("Error: unable to open file.\n");
        return 0;
    }
    char line[2048];
    char member[2048];
    BorrowBook data;
    Member User;
    int found=0;
    int userfound=0;
    while (fgets(line, sizeof(line), file) && fgets(member, sizeof(member), file2)){
        if (strcmp(line, "\n") != 0 && strcmp(member, "\n") != 0){
             sscanf(line, "%49[^,],%49[^,]", data.username,data.bookid);
                if (strcmp(data.bookid, ID) == 0)
                    if ((data.username, username)==0) {
                        fclose(file);
                        fclose(file2);
                        return 0; //found data
                }
            }
        }

    fclose(file);
    fclose(file2);
    return 1; // no data found
}

//book management
void addbook() {
    FILE *file = fopen("book.txt", "a+");
    FILE *file2 = fopen("books_summary.txt", "a+");
    if (file == NULL || file2 == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }

    Book data;
    Book newdata;
    char line[2048];
    char summary[1000];

   int idfound=0;
    do{
        printf("Enter book id (0 to exit): ");
    scanf(" %49[^\n]",newdata.id);

    if (strcmp(newdata.id,"0")==0){
        fclose(file);
        fclose(file2);
        printf("...");
        return;
    }

    if (isBookUnique(newdata.id)) {
        idfound=1;
    }
    else{
        printf("Error: Book ID already exist! Please try again!\n");
    }
    }while(idfound==0);

    printf("Enter book title (0 to exit): ");
    scanf(" %49[^\n]",newdata.title);

    if (strcmp(newdata.title,"0")==0){
        fclose(file);
        fclose(file2);
        printf("...");
        return;
    }

    printf("Enter book author (0 to exit): ");
    scanf(" %49[^\n]",newdata.author);
    if (strcmp(newdata.author,"0")==0){
    fclose(file);
    fclose(file2);
    printf("...");
    return;
    }

    printf("Enter book genre (0 to exit): ");
    scanf(" %49[^\n]",newdata.genre);
    if (strcmp(newdata.genre,"0")==0){
    fclose(file);
    fclose(file2);
    printf("...");
    return;
    }

    printf("Enter book type[physical or digital] (0 to exit): ");
    scanf(" %49[^\n]",newdata.type);
    if (strcmp(newdata.type,"0")==0){
    fclose(file);
    fclose(file2);
    printf("...");
    return;
    }

    printf("Enter summary (0 to exit): ");
    scanf(" %49[^\n]",summary);
    if (strcmp(summary,"0")==0){
    fclose(file);
    fclose(file2);
    printf("...");
    return;
    }

    fprintf(file,"-,%s,%s,%s,%s,available,%s\n", newdata.id, newdata.title, newdata.author, newdata.genre,newdata.type);
    fprintf(file2,"%s,%s\n", newdata.title,summary);
    printf("Book added successfully.\n");

    fclose(file);
    fclose(file2);
    return;
}

void displaybook(int mode){ //i=1 - bookID, bookTitle | i=2 - all
    FILE *file = fopen("book.txt", "r");
    if (file == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }

    Book data;
    printf("\nBooks in the system:\n");

    char line[2048];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "\n") != 0) {
            sscanf(line,"%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,]", data.shelfID,data.id,data.title,data.author,data.genre,&data.status,data.type);

            if (mode==1){
            printf( "BookID: %s | BookTitle: %s \n", data.id, data.title);
            }
            if (mode==2){
            printf( "ShelfID:%s | BookID: %s | BookTitle: %s | BookAuthor: %s | BookGenre: %s | BookStatus: %s | BookType: %s\n", data.shelfID,data.id, data.title, data.author, data.genre, data.status,data.type);
            }
        }
    }
    fclose(file);
    return;
}

void updatebook(){
    FILE *file = fopen("book.txt", "r");
    FILE *temp= fopen("temp___book.txt","w");

    FILE *file2 = fopen("books_summary.txt" , "r");
    FILE * temp2 = fopen("temp____books_summary.txt", "w");

    if (file == NULL || temp == NULL || file2 == NULL || temp2 == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }
    char line[2048];
    char IDpick[50];

    int update_domain;
    char newInfo[50];
    int new_quantity;

    Book data;
    char line2[2048];
    char title[50];
    char summary[1000];

    int idfound=0;
    do{
    printf("Enter a Book ID to update (enter 0 to exit):");
    scanf("%s", &IDpick);

    if (strcmp(IDpick,"0")==0){
        fclose(file);
        fclose(temp);
        fclose(file2);
        fclose(temp2);
        printf("...");
        return;
    }

    if (!isBookUnique(IDpick)) {
        idfound=1;
    }
    else{
        printf("Error: Book ID not found! Please try again!\n");
    }
    }while(idfound==0);

    while (fgets(line, sizeof(line), file) != NULL){
        if (strcmp(line, "\n") != 0) {
            sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,]", data.shelfID,data.id,data.title,data.author,data.genre,&data.status,data.type);
        }

        if (strcmp(IDpick,data.id)!=0){
            fputs(line,temp);
        }

        else if (strcmp(IDpick,data.id)==0){
            do{
            fgets(line2, sizeof(line2), file2);
            sscanf(line2,"%49[^,],%999[^,]",title,summary);

            if (strcmp(title,data.title)!=0){
                fputs(line2,temp2);
                }
            } while (strcmp(title,data.title)!=0);

            printf( "\nBookID: %s | Book Title: %s | Book Author: %s | Book Genre: %s | Book Status: %s | Book Type: %s | Book Summary: %s\n", data.id, data.title, data.author, data.genre, data.status, data.type,summary);
            printf("(1) Book Title | (2) Book Author | (3) Book Genre | (4) Book Type | (5) Book Summary |(0) Exit\n");

            do{
            printf("\nchoose a domain to update:");
            scanf("%d",&update_domain);

            if (update_domain==1){
                printf("Enter new book title: ");
                scanf(" %49[^\n]",newInfo);
                strcpy(data.title, newInfo);
            }

            else if (update_domain==2){
                printf("Enter new book author: ");
                scanf(" %49[^\n]",newInfo);
                strcpy(data.author, newInfo);
            }

            else if (update_domain==3){
                printf("Enter new book genre: ");
                scanf(" %49[^\n]",newInfo);
                strcpy(data.genre, newInfo);
            }

            else if (update_domain==4){
                printf("Enter new book type: ");
                scanf(" %49[^\n]",newInfo);
                strcpy(data.type, newInfo);
            }

            else if (update_domain==5){
                printf("Enter new book summary: ");
                scanf(" %49[^\n]",newInfo);
                strcpy(summary, newInfo);
            }

            else if (update_domain==0){
                fclose(file);
                fclose(temp);
                printf("...");
                return;
            }
            else{
                printf("Error: invalid Input!");
            }
            }while (update_domain!=0);

            printf( "BookID: %s | BookTitle: %s | BookAuthor: %s | BookGenre: %s | BookStatus: %s | BookType: %s | BookSummary: %s\n", data.id, data.title, data.author, data.genre, data.status,data.type, summary);
            fprintf(temp,"%s,%s,%s,%s,%s,%s,%s", data.shelfID,data.id, data.title, data.author, data.genre, data.status,data.type);
            fprintf(temp2,"%s,%s",data.title,summary);
            printf("Succesfully update a book!\n");
        }
    }
    fclose(file);
    fclose(temp);
    fclose(file2);
    fclose(temp2);
    remove("book.txt");
    rename("temp___book.txt", "book.txt");
    remove("books_summary.txt");
    rename("temp____books_summary.txt", "books_summary.txt");
    return;
}

void deletebook(){
    FILE *file = fopen("book.txt", "r");
    FILE *temp= fopen("temp___book.txt","w");

    FILE *file2 = fopen("books_summary.txt", "r");
    FILE *temp2 = fopen("temp___books_summary.txt","w");

    if (file == NULL || temp == NULL || file2 == NULL || temp2 == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }
    char line[2048];
    char line2[2048];
    char IDpick[50];
    char title[50];
    char summary[1000];
    Book data;

    int idfound=0;
    do{
    printf("Enter a Book ID to delete (0 to exit):");
    scanf("%s", &IDpick);

    if (strcmp(IDpick,"0")==0){
        fclose(file);
        fclose(temp);
        printf("...");
        return;
    }
    if (!isBookUnique(IDpick)) {
        idfound=1;
    }
    else{
        printf("Error: Book ID not found! Please try again!\n");
    }
    }while(idfound==0);

    bool keep_reading=true;
    int current_line=1;

    do{
        if (strcmp(line, "\n") != 0){
        fgets(line, sizeof(line),file);
        sscanf(line,"%49[^,],%49[^,],%49[^,]",data.shelfID,data.id,data.title);

        if (feof(file)){
            printf("Book deletion is succesful!\n");
            keep_reading=false;
        }

        else if (strcmp(IDpick,data.id)!=0){
            fputs(line,temp);
            rewind(file2);
            while (fgets(line2, sizeof(line2),file2)){
                sscanf(line2,"%49[^,],%999[^,]",title,summary);
                if (strcmp(title,data.title)==0){
                    fputs(line2,temp2);
                    break;
                }
            }
        }
        current_line++;}
    }while (keep_reading);

    fclose(file);
    fclose(temp);
    fclose(file2);
    fclose(temp2);

    remove("book.txt");
    rename("temp___book.txt", "book.txt");

    remove("books_summary.txt");
    rename("temp___books_summary.txt", "books_summary.txt");
    return;
}

//member management function
void registermember(){
    FILE *file = fopen("member.txt", "a+");

    if (file == NULL) {
        printf("Error: unable to open file.\n");
        return;
        }

    Member data;
    Member newdata;
    char line[2048];

    printf("Enter your full name (0 to exit): ");
    scanf(" %99[^\n]",newdata.name);


    if (strcmp(newdata.name,"0")==0){
        fclose(file);
        printf("...");
        return;
    }

    int userfound=0;
    do{
    printf("Enter your username (0 to exit): ");
    scanf(" %49[^\n]",newdata.username);

    if (strcmp(newdata.username,"0")==0){
        fclose(file);
        printf("...");
        return;
    }

    if (isUsernameUnique(newdata.username)) {
        userfound=1;
    }
    else{
        printf("Error: Username already exist! Please try again!\n");
    }
    }while(userfound==0);

    printf("Enter your password: ");
    scanf(" %49[^\n]",newdata.password);

    newdata.role=3;

    fprintf(file,"%s,%s,%d,%s,active\n",newdata.username,newdata.password,newdata.role,newdata.name);
    printf("Register successful!\n");
    fclose(file);
    return;
}

void displaymember(){
    FILE *file = fopen("member.txt", "r");

    if (file == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }

    Member data;
    printf("\nMembers in the system:\n");

    char line[2048];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "\n") != 0) {
            sscanf(line, "%49[^,],%49[^,],%d,%99[^,],%49[^,]", data.username, data.password,&data.role,data.name,data.status);
            printf( "Member Username: %s | Member Name: %s | Member Status: %s\n", data.username, data.name, data.status);
            }
    }
    fclose(file);
    return;
}

void updatemember(){
    FILE *file = fopen("member.txt", "r");
    FILE *temp= fopen("temp___member.txt","w");

    char line[2048];
    char usernamepick[50];
    int update_domain;
    char newInfo[50];
    Member data;

    if (file == NULL || temp == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }

    int userfound=0;
    do{
    printf("Enter member username to update (enter 0 to exit):");
    scanf("%s", &usernamepick);

    if (strcmp(usernamepick,"0")==0){
        fclose(file);
        printf("...");
        return;
    }

    if (!isUsernameUnique(usernamepick)) {
        userfound=1;
    }
    else{
        printf("Error: Username not found! Please try again!\n");
    }
    }while(userfound==0);

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "\n") != 0) {
            sscanf(line, "%49[^,],%49[^,],%d,%99[^,],%49[^,]", data.username, data.password,&data.role,data.name,data.status);
            }

        if (strcmp(usernamepick,data.username)!=0){
            fputs(line,temp);
            }
        if (strcmp(usernamepick,data.username)==0){
            printf( "\nMember Username: %s | Member Name: %s | Member Status: %s\n", data.username, data.name, data.status);
            printf("(1) Member Username | (2) Member Name | (3) Member Password | (4) Member Status | (0) Exit\n");
            printf("choose a domain to update:");
            scanf("%d",&update_domain);

            if (update_domain==1){
            userfound=0;
            do{
                printf("Enter new username: ");
                scanf(" %49[^\n]",newInfo);
                if (isUsernameUnique(newInfo)) {
                    strcpy(data.username, newInfo);
                    userfound=1;
                }
                else{
                    printf("Error: Username already exist! Please try again!");
                }
            }while (userfound==0);
            }

            else if (update_domain==2){
                printf("Enter new name: ");
                scanf(" %99[^\n]",newInfo);
                strcpy(data.name, newInfo);
            }

            else if (update_domain==3){
                printf("Enter new password: ");
                scanf(" %49[^\n]",newInfo);
                strcpy(data.password, newInfo);
            }
            else if (update_domain==4){
                printf("Enter member status (active/inactive): ");
                scanf(" %49[^\n]",newInfo);
                strcpy(data.status, newInfo);
            }

            else if (update_domain==0){
                printf("...");
                return;
            }

            else
            {
                printf("Error: invalid Input!");
            }

            printf( "\nMemberUsername: %s | MemberName: %s | MemberStatus: %s\n", data.username, data.name, data.status);
            fprintf(temp,"%s,%s,%d,%s,%s\n",data.username,data.password,data.role,data.name,data.status);
            printf("\nSuccesfully update member information!\n");
        }
    }
    fclose(file);
    fclose(temp);

    remove("member.txt");
    rename("temp___member.txt","member.txt");
    return;
}


//borrow and return function
void borrow_book() {
    FILE *file = fopen("borrowbook.txt", "r");
    FILE *temp = fopen("temp___borrowbook.txt","w");

    FILE *filebook = fopen("book.txt","r");
    FILE *filebooktemp = fopen("temp____book.txt","w");

    FILE *user = fopen("member.txt","r");

    if (file == NULL || temp == NULL || filebook == NULL || filebooktemp == NULL || user == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }

    Book book;
    BorrowBook data;
    char line[2048];
    char buffer[2048];
    bool keep_reading=true;

    int found = 0;
    do{
    printf("Enter username (0 to exit): ");
    scanf(" %49[^\n]",data.username);

    if (strcmp(data.username,"0")==0){
        fclose(file);
        fclose(temp);
        fclose(filebook);
        fclose(filebooktemp);
        printf("...");
        return;
    }

    printf("Enter book id (0 to exit): ");
    scanf(" %49[^\n]",data.bookid);

    if (strcmp(data.bookid,"0")==0){
        fclose(file);
        fclose(temp);
        fclose(filebook);
        fclose(filebooktemp);
        printf("...");
        return;
    }
    if (!isUsernameUnique(data.username) && !isBookUnique(data.bookid)) {
        found=1;
    }
    else{
        printf("Error: Username or Book ID not exist! Please try again!\n");
    }
    }while(found==0);

    printf("Enter due date (0 to exit): ");
    scanf(" %49[^\n]",data.duedate);
        if (strcmp(data.username,"0")==0){
        fclose(file);
        fclose(temp);
        fclose(filebook);
        fclose(filebooktemp);
        printf("...");
        return;
    }
    strcpy(data.status,"borrowed");

    while(fgets(buffer,sizeof(buffer),filebook)){
        if (strcmp(buffer, "\n") != 0) {
            sscanf(buffer, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,]", book.shelfID,book.id,book.title,book.author,book.genre,book.status,book.type);
        }

            if (strcmp(data.bookid,book.id)==0){
                if ((strcmp(book.status,"unavailable")==0)){
                    printf("Error: The book is unavailable to be borrowed!");
                    fclose(file);
                    fclose(temp);

                    fclose(filebook);
                    fclose(filebooktemp);
                    return;
                }

                    strcpy(data.booktitle,book.title);
                    data.fines=0;
                    fprintf(temp,"%s,%s,%s,%s,%s,%d\n", data.username, data.bookid, data.booktitle, data.duedate, data.status, data.fines);

                    strcpy(book.status,"unavailable");
                    fprintf(filebooktemp,"%s,%s,%s,%s,%s,%s,%s", book.shelfID,book.id, book.title, book.author, book.genre, book.status,book.type);
                }
            else if (strcmp(data.bookid,book.id)!=0){
                fputs(buffer,filebooktemp);
                }
        }

    do{
        fgets(line, sizeof(line), file);

        if (feof(file))
            keep_reading=false;
        else
            fputs(line,temp);

    }while (keep_reading);

    fclose(file);
    fclose(temp);

    fclose(filebook);
    fclose(filebooktemp);

    remove("borrowbook.txt");
    rename("temp___borrowbook.txt", "borrowbook.txt");

    remove("book.txt");
    rename("temp____book.txt", "book.txt");

    printf("Book borrowed successfully.\n");
    return;
}

void return_book(){
    FILE *file = fopen("borrowbook.txt", "r");
    FILE *temp= fopen("temp___borrowbook.txt","w");

    FILE *filebook = fopen("book.txt","r");
    FILE *filebooktemp = fopen("temp____book.txt","w");

    if (file == NULL || temp == NULL || filebook == NULL || filebooktemp == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }

    char line[2048];
    char buffer[2048];
    char IDpick[50];
    char usernamepick[50];
    BorrowBook data;
    Book book;

    int found = 0;
    do{
    printf("Enter your username (0 to exit):");
    scanf("%s", &usernamepick);

        if (strcmp(usernamepick,"0")==0){
        fclose(file);
        fclose(temp);
        fclose(filebook);
        fclose(filebooktemp);
        printf("...");
        return;
    }

    printf("Enter a Book ID to return:");
    scanf("%s", &IDpick);

    if (strcmp(IDpick,"0")==0){
        fclose(file);
        fclose(temp);
        fclose(filebook);
        fclose(filebooktemp);
        printf("...");
        return;
    }
    if (isBorrowUnique(usernamepick,IDpick)) {
        found=1;
    }
    else{
        printf("Error: Data not found! Please try again!\n");
    }
    }while(found==0);

    while (fgets(line, sizeof(line), file)){
        if (strcmp(line, "\n") != 0){
            sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d", data.username, data.bookid, data.booktitle, data.duedate, data.status, &data.fines);

        if  ((strcmp(IDpick,data.bookid)!=0) || (strcmp(usernamepick,data.username)!=0)){
            fputs(line,temp);
            }

        else if ((strcmp(IDpick,data.bookid)==0) && (strcmp(usernamepick,data.username)==0)){
            strcpy(data.status,"returned");
            data.fines=0;
            fprintf(temp,"%s,%s,%s,%s,%s,%d\n",  data.username, data.bookid, data.booktitle, data.duedate, data.status, data.fines);
            printf("Book returned succesfully!\n");
            }
        }
    }

    while (fgets(buffer,sizeof(buffer),filebook)){
       sscanf(buffer, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,]",book.shelfID, book.id,book.title,book.author,book.genre,book.status,book.type);
       if (strcmp(book.id,IDpick)==0){
            strcpy(book.status,"available");
            fprintf(filebooktemp,"%s,%s,%s,%s,%s,%s,%s", book.shelfID,book.id, book.title, book.author, book.genre, book.status,book.type);
            }

        else if (strcmp(book.id,IDpick)!=0){
            fputs(buffer,filebooktemp);
        }
    }

    fclose(file);
    fclose(temp);

    fclose(filebook);
    fclose(filebooktemp);

    remove("borrowbook.txt");
    rename("temp___borrowbook.txt", "borrowbook.txt");

    remove("book.txt");
    rename("temp____book.txt", "book.txt");
    return;
}

void overduesystem(){
    FILE *file = fopen("borrowbook.txt", "r");
    FILE *temp= fopen("temp___borrowbook.txt","w");

    if (file == NULL || temp == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }

    char line[2048];
    char buffer[2048];
    char IDpick[50];
    char usernamepick[50];
    BorrowBook data;

    int found = 0;
    do{
    printf("Enter your username (0 to exit):");
    scanf("%s", &usernamepick);

    if (strcmp(usernamepick,"0")==0){
        fclose(file);
        fclose(temp);
        printf("...");
        return;
    }

    printf("Enter a Book ID to overdue (0 to exit):");
    scanf("%s", &IDpick);

    if (strcmp(IDpick,"0")==0){
        fclose(file);
        fclose(temp);
        printf("...");
        return;
    }

    if (isBorrowUnique(usernamepick,IDpick)) {
        found=1;
    }
    else{
        printf("Error: Data not found! Please try again!\n");
    }
    }while(found==0);

    while (fgets(line, sizeof(line), file)){
        if (strcmp(line, "\n") != 0){
        sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d", data.username,data.bookid,data.booktitle,data.duedate,data.status,&data.fines);

         if  ((strcmp(IDpick,data.bookid)!=0) || (strcmp(usernamepick,data.username)!=0)){
            fputs(line,temp);
            }

        else if ((strcmp(IDpick,data.bookid)==0) && (strcmp(usernamepick,data.username)==0)){
            strcpy(data.status,"overdue");
            data.fines=0;
            fprintf(temp,"%s,%s,%s,%s,%s,%d\n",  data.username, data.bookid, data.booktitle, data.duedate, data.status, data.fines);
             printf("Book status has been change to overdue!\n");
            }
        }
    }

    fclose(file);
    fclose(temp);

    remove("borrowbook.txt");
    rename("temp___borrowbook.txt", "borrowbook.txt");
    return;
}

void display_borrow_book(int mode){ ///1-no returned 2- no overdue
    FILE *file = fopen("borrowbook.txt", "r");
    if (file == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }

    BorrowBook data;
    printf("\nBooks Borrowed in the system:\n");
    char line[2048];
    int fines;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "\n") != 0) {
            sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%s", data.username,data.bookid,data.booktitle,data.duedate, data.status, data.fines);
            if (mode==1){
            if (strcmp(data.status,"returned")!=0){
                sscanf(data.fines, "%d", &fines);
                printf( "Borrower: %s | BookID: %s | Booktitle: %s | DueDate: %s | Fines:RM%d | Status:%s \n", data.username,data.bookid,data.booktitle,data.duedate, fines, data.status);
                }
            }

            else if (mode==2){
            if (strcmp(data.status,"borrowed")==0){
                sscanf(data.fines, "%d", &fines);
                printf( "Borrower: %s | BookID: %s | Booktitle: %s | DueDate: %s | Fines:RM%d | Status:%s \n", data.username,data.bookid,data.booktitle,data.duedate, fines, data.status);
                }
            }
        }
    }
    fclose(file);
    return;
}

//report function
void popularbook(){
 FILE *file = fopen("borrowbook.txt", "r");

    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
        }

    BorrowBook data;
    char line[2048];
    int totalbooks=0;
    popular_book books[2048];
    char maxid[50];
    char maxtitle[50];
    int maxcount=0;

    while (fgets(line, sizeof(line), file)!=NULL){
        if (strcmp(line, "\n") != 0){
    sscanf(line, "%49[^,],%49[^,],%49[^,]", data.username,data.bookid,data.booktitle);
    }

    int found = 0;
    for (int i = 0; i < totalbooks; i++) {
        if (strcmp(books[i].id, data.bookid) == 0) {
            books[i].count++;
            found = 1;
            break;
        }
    }

    if (!found) {
        strcpy(books[totalbooks].id, data.bookid);
        strcpy(books[totalbooks].title, data.booktitle);
        books[totalbooks].count = 1;
        totalbooks++;
        }
    }

    fclose(file);
    printf("Most popular book borrowed:\n");
    for (int i = 0; i < totalbooks; i++) {

        if (books[i].count>maxcount){
            maxcount=books[i].count;
            strcpy(maxid,books[i].id);
            strcpy(maxtitle,books[i].title);
        }
    }
    printf("Book ID: %s | Book Title: %s | Borrowed count: %d\n", maxid,maxtitle,maxcount);
    fclose(file);
    return;
}


void overdueitem(){
    FILE *file = fopen("borrowbook.txt", "r");

    if (file == NULL) {
        printf("Error: unable to open file.\n");
        return;
        }

    BorrowBook data;
    char line[2048];
    int fines;

    printf("\n Overdue items:\n");

    while ( fgets(line, sizeof(line), file)!=NULL){
    if (strcmp(line, "\n") != 0){
    sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%s", data.username,data.bookid,data.booktitle,data.duedate, data.status, data.fines);
    }

    if (strcmp(data.status,"overdue")!=0){
        sscanf(data.fines, "%d", &fines);
        fines=fines;
        printf( "Borrower: %s | BookID: %s | Booktitle: %s | DueDate: %s | Fines:RM%d | Status:%s \n", data.username,data.bookid,data.booktitle,data.duedate, fines, data.status);
        }
    }
    fclose(file);
    return;
}

void bookcirculation(){
    FILE *file = fopen("borrowbook.txt", "r");

    if (file == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }

    BorrowBook data;
    char line[2048];
    int fines;

    printf("\nBooks Borrowed in the system:\n");

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "\n") != 0) {
            sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%s", data.username,data.bookid,data.booktitle,data.duedate, data.status, data.fines);
            sscanf(data.fines, "%d", &fines);
            printf( "Borrower: %s | BookID: %s | Booktitle: %s | Due Date: %s | Fines:RM%d | Status:%s \n", data.username,data.bookid,data.booktitle,data.duedate, fines, data.status);
            }
    }
    fclose(file);
    return;
}


