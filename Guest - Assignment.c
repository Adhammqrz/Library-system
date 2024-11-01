
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TITLE_LENGTH 100
#define MAX_SUMMARY_LENGTH 1000
#define MAX_LINE_LENGTH 80
#define MAX_EVENTNAME_LENGTH 100
#define MAX_EVENTDETAILS_LENGTH 1000


typedef struct
{
    char genre[20];
    char title[50];
    char author[50];
} Book;


typedef struct
{
    char eventname[100];
    char month[10];
    int day;
    int year;
}Event;


typedef struct
{
    char aboutlibraryservices[100];
}Services;


typedef struct {
    char booktitle[MAX_TITLE_LENGTH];
    char booksumm[MAX_SUMMARY_LENGTH];
} Summ;


typedef struct {
    char eventname[MAX_EVENTNAME_LENGTH];
    char eventsumm[MAX_EVENTDETAILS_LENGTH];
    char month[10];
    int day;
    int year;
    char time[50];
    char location[50];
} Eventdet;



//Library Exploration
void libraryexploration()
{
    int choice;
    do
    {
        printf("\n=========================================");
        printf("\n Welcome to The Library Exploration Page");
        printf("\n=========================================");
        printf("\n\n1. Browse Categories ");
        printf("\n2. Search by Title or Author");
        printf("\n3. View All Available Books");
        printf("\n4. Exit");
        printf("\n\n=========================================");
        printf("\n\nPlease Choose an Option:");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            categories();
            break;
        case 2:
            titleorauthor();
            break;
        case 3:
            available();
            booksummary();
            break;
        case 4:
            printf("\n\n==============");
            printf("\n Exiting....");
            printf("\n==============");
            break;
        default:
            printf("\nInvalid Choice. Please insert the Correct Input");
        }
    }while (choice != 4);
}


//Browse By Categories
void categories()
{
    int choice;
    do
    {
        printf("\n================================");
        printf("\n      Browse by Categories");
        printf("\n================================");
        printf("\n\n1. Fiction ");
        printf("\n2. Non-fiction");
        printf("\n3. Science");
        printf("\n4. History");
        printf("\n5. Philosophy");
        printf("\n6. Biography");
        printf("\n7. Back to Main Menu");
        printf("\n\n================================");
        printf("\n\nPlease Choose a Category:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fiction();
            break;
        case 2:
            nonfiction();
            break;
        case 3:
            science();
            break;
        case 4:
            history();
            break;
        case 5:
            philosophy();
            break;
        case 6:
            biography();
            break;
        case 7:
            printf("Exit\n");
            break;
        default:
            printf("\nInvalid Choice. Please insert the Correct Input");
        }

    }while (choice != 7);
}


//Search by Title or Author
void titleorauthor()
{
    Book book;
    FILE *file;
    char searchTerm[50];
    char choice;

    do
    {
        printf("\n================================");
        printf("\n        Search Books");
        printf("\n================================");

        do
        {
            printf("\nEnter the Book Title or Author Name: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0; // Remove newline character

            if(strlen(searchTerm)<3)
            {
                printf("Please enter at least 3 characters for more accurate finding.\n");
            }
        }while (strlen(searchTerm)<3);



        file = fopen("assignment_booklist.txt", "r");
        if (file == NULL)
        {
            printf("No Available Book\n");
            continue;
        }

        int found = 0;
        while (fscanf(file, " %[^,], %[^,], %[^\n]", book.genre, book.title, book.author) == 3) {
            if (strstr(book.title, searchTerm) != NULL || strstr(book.author, searchTerm) != NULL) {
                printf("\nGenre: %s\n", book.genre);
                printf("Title: %s\n", book.title);
                printf("Author: %s\n", book.author);
                found = 1;
            }
        }

        if (!found) {
            printf("No matching books found.\n");
        }

        fclose(file);

        do
        {
            printf("\nDo you want to continue searching? (y/n): ");
            scanf("%s", &choice);
            getchar();

            if(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
            {
                printf("Invalid input, Please enter 'Y' for Yes and 'N' for No.");
            }
        }while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

    } while (choice == 'y' || choice == 'Y');

    printf("Returning to main menu...\n");
}



//Available Books
void available()
 {
    Book book;
    FILE *file = fopen("assignment_booklist.txt", "r");
    if (file == NULL)
    {
        printf("No Available Book\n");
        return;
    }

    printf("\n================================");
    printf("\n     Available Book List");
    printf("\n================================");

    // Read until the end of the file
    while (fscanf(file, " %[^,], %[^,], %[^\n]", book.genre, book.title, book.author) == 3)
        {
            printf("\nGenre: %s\n", book.genre);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
        }

    fclose(file);
}

//Available Fiction Books
void fiction()
{
    Book book;
    FILE *file = fopen("assignment_booklist.txt", "r");
    if (file == NULL)
    {
        printf("No Available Book\n");
        return;
    }

    printf("\n================================");
    printf("\n     Fiction Book List");
    printf("\n================================");

    int found = 0;
    while(fscanf(file, " %[^,], %[^,], %[^\n]", book.genre, book.title, book.author) == 3)
    {
        if(strcasecmp(book.genre, "Fiction")==0)
        {
            printf("\nGenre: %s\n", book.genre);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            found = 1;
        }
    }
    if(!found)
    {
        printf("\nNo Fiction Books Found.\n");
    }
    fclose(file);
}



//Available Non-Fiction Books
void nonfiction()
{
    Book book;
    FILE *file = fopen("assignment_booklist.txt", "r");
    if (file == NULL)
    {
        printf("No Available Book\n");
        return;
    }

    printf("\n================================");
    printf("\n     Non-Fiction Book List");
    printf("\n================================");

    int found = 0;
    while(fscanf(file, " %[^,], %[^,], %[^\n]", book.genre, book.title, book.author) == 3)
    {
        if(strcasecmp(book.genre, "Non-Fiction")==0)
        {
            printf("\nGenre: %s\n", book.genre);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            found = 1;
        }
    }
    if(!found)
    {
        printf("\nNo Non-Fiction Books Found.\n");
    }
    fclose(file);
}



//Available Science Books
void science()
{
    Book book;
    FILE *file = fopen("assignment_booklist.txt", "r");
    if (file == NULL)
    {
        printf("No Available Book\n");
        return;
    }

    printf("\n================================");
    printf("\n     Science Book List");
    printf("\n================================");

    int found = 0;
    while(fscanf(file, " %[^,], %[^,], %[^\n]", book.genre, book.title, book.author) == 3)
    {
        if(strcasecmp(book.genre, "Science")==0)
        {
            printf("\nGenre: %s\n", book.genre);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            found = 1;
        }
    }
    if(!found)
    {
        printf("\nNo Science Books Found.\n");
    }
    fclose(file);
}




//Available History Books
void history()
{
    Book book;
    FILE *file = fopen("assignment_booklist.txt", "r");
    if (file == NULL)
    {
        printf("No Available Book\n");
        return;
    }

    printf("\n================================");
    printf("\n     History Book List");
    printf("\n================================");

    int found = 0;
    while(fscanf(file, " %[^,], %[^,], %[^\n]", book.genre, book.title, book.author) == 3)
    {
        if(strcasecmp(book.genre, "History")==0)
        {
            printf("\nGenre: %s\n", book.genre);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            found = 1;
        }
    }
    if(!found)
    {
        printf("\nNo History Books Found.\n");
    }
    fclose(file);
}


//Available Philosophy Books
void philosophy()
{
    Book book;
    FILE *file = fopen("assignment_booklist.txt", "r");
    if (file == NULL)
    {
        printf("No Available Book\n");
        return;
    }

    printf("\n================================");
    printf("\n     Philosophy Book List");
    printf("\n================================");

    int found = 0;
    while(fscanf(file, " %[^,], %[^,], %[^\n]", book.genre, book.title, book.author) == 3)
    {
        if(strcasecmp(book.genre, "Philosophy")==0)
        {
            printf("\nGenre: %s\n", book.genre);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            found = 1;
        }
    }
    if(!found)
    {
        printf("\nNo Philosophy Books Found.\n");
    }
    fclose(file);
}



//Available Biography Books
void biography()
{
    Book book;
    FILE *file = fopen("assignment_booklist.txt", "r");
    if (file == NULL)
    {
        printf("No Available Book\n");
        return;
    }

    printf("\n================================");
    printf("\n     Biography Book List");
    printf("\n================================");

    int found = 0;
    while(fscanf(file, " %[^,], %[^,], %[^\n]", book.genre, book.title, book.author) == 3)
    {
        if(strcasecmp(book.genre, "Biography")==0)
        {
            printf("\nGenre: %s\n", book.genre);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            found = 1;
        }
    }
    if(!found)
    {
        printf("\nNo Biography Books Found.\n");
    }
    fclose(file);
}




//Print Feature Debugging
void print_wrapped_text(const char *text, int line_length) {
    int i = 0, line_start = 0;
    while (text[i] != '\0') {
        if (i - line_start >= line_length && text[i] == ' ') {
            printf("\n");
            line_start = i + 1;
        } else {
            putchar(text[i]);
        }
        i++;
    }
    printf("\n");
}



//Book Summary
void booksummary()
{
    char choice;
    do
    {
        printf("\nDo you want to read a book summary? (y/n): ");
        scanf("%s", &choice);
        getchar();
        if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            printf("Invalid input, please enter 'Y' for Yes and 'N' for No.\n");
        }
    } while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');


    if (choice == 'n' || choice == 'N')
    {
        printf("Returning to main menu...\n");
        return;
    }

        Summ summ;
        FILE *file;
        char booksearch[50];

    do{
        do
        {
            printf("\n========================");
            printf("\nEnter the Book Title: ");
            fgets(booksearch, sizeof(booksearch), stdin);
            booksearch[strcspn(booksearch, "\n")] = 0; // Remove newline character
            if (strlen(booksearch) < 3)
            {
                printf("Please enter at least 3 characters for more accurate finding.\n");
            }
        } while (strlen(booksearch) < 3);

        file = fopen("books_summary.txt", "r");
        if (file == NULL)
        {
            printf("No Available Book\n");
            return;
        }

        int found = 0;
        while (fscanf(file, "%99[^,], %999[^\n]", summ.booktitle, summ.booksumm) == 2)
         {
            if (strstr(summ.booktitle, booksearch) != NULL)
            {
                printf("\n======================");
                printf("Book Summary");
                printf("======================");
                printf("%s\n\n", summ.booktitle);
                print_wrapped_text(summ.booksumm, MAX_LINE_LENGTH);
                found = 1;
            }
        }

        if (!found)
        {
            printf("No matching books found.\n");
        }

        fclose(file);

        do
        {
            printf("\nDo you want to continue searching? (y/n): ");
            scanf("%s", &choice);
            getchar();

            if(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
            {
                printf("Invalid input, Please enter 'Y' for Yes and 'N' for No.");
            }
        }while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

    }while (choice == 'y' || choice == 'Y');
}


//Event Information
void eventinformation()
{
    int choice;
    do
    {
        printf("\n===============================================");
        printf("\n Welcome to The Library Event Information Page");
        printf("\n===============================================");
        printf("\n\n1. Explore Upcoming Events");
        printf("\n2. View Workshops");
        printf("\n3. Community Programs");
        printf("\n4. Exit");
        printf("\n\n===============================================");
        printf("\n\nPlease Choose an Option:");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            upcomingevent();
            break;
        case 2:
            workshops();
            break;
        case 3:
            communityprograms();
            break;
        case 4:
            printf("\n\n==============");
            printf("\n Exiting....");
            printf("\n==============");
            break;
        default:
            printf("\nInvalid Choice. Please insert the Correct Input");
        }
    }while (choice != 4);
}


//Upcoming Event
void upcomingevent()
{
    char choice;
    Event event;
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printf("No Events\n");
        return;
    }

    printf("\n================================");
    printf("\n       Upcoming Events");
    printf("\n================================");

    int count = 1;
    // Read until the end of the file
    while (fscanf(file, " %[^,], %[^,], %d, %d", event.eventname, event.month, &event.day, &event.year) == 4)
    {
        printf("\n%d. %s on %s %d, %d", count, event.eventname, event.month, event.day, event.year);
        count++;
    }

    fclose(file);

    do
    {
        printf("\n\nDo You Want to Read Event Details (y/n): ");
        scanf("%s", &choice);
        getchar();
        if(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            printf("Invalid input, Please enter 'Y' for Yes and 'N' for No.");
        }
        else if (choice == 'y' || choice == 'Y')
        {
            eventdetails();
            return;
        }
        else
        {
            return;
        }
    }while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');
}



//Event Details
void eventdetails()
{
    char choice;
    Eventdet eventdet;
    FILE *file;
    char eventtitle[50];
    char line[1200];

    do{
        do
        {
            printf("\n========================");
            printf("\nEnter the Event Name: ");
            fgets(eventtitle, sizeof(eventtitle), stdin);
            eventtitle[strcspn(eventtitle, "\n")] = 0; // Remove newline character
            if (strlen(eventtitle) < 3)
            {
                printf("Please enter at least 3 characters for more accurate finding.\n");
            }
        } while (strlen(eventtitle) < 3);

        file = fopen("event_details.txt", "r");
        if (file == NULL)
        {
            printf("No Event Findings\n");
            return;
        }

        int found = 0;
        while (fgets(line, sizeof(line), file))
         {
            sscanf(line, "%99[^,], %999[^|]| %[^,], %d, %d, %[^,], %[^\n]", eventdet.eventname, eventdet.eventsumm, eventdet.month, &eventdet.day, &eventdet.year, eventdet.time, eventdet.location);
            if (strstr(eventdet.eventname, eventtitle) != NULL)
            {
                printf("\n======================");
                printf(" Event Details ");
                printf("======================");
                printf("\n%s\n\n", eventdet.eventname);
                print_wrapped_text(eventdet.eventsumm, MAX_LINE_LENGTH);
                printf("\nDate: %s %d, %d", eventdet.month, eventdet.day, eventdet.year);
                printf("\nTime: %s", eventdet.time);
                printf("\nLocation: %s\n", eventdet.location);
                found = 1;
            }
        }

        if (!found)
        {
            printf("No Event Finding.\n");
        }

        fclose(file);

        do
        {
            printf("\nDo you want to continue searching? (y/n): ");
            scanf("%s", &choice);
            getchar();

            if(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
            {
                printf("\nInvalid input, Please enter 'Y' for Yes and 'N' for No.");
            }
        }while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

    }while (choice == 'y' || choice == 'Y');
}



//Workshops
void workshops()
{
    char choice;
    Event workshop;
    FILE *file = fopen("workshops.txt", "r");
    if (file == NULL)
    {
        printf("No Workshops\n");
        return;
    }

    printf("\n================================");
    printf("\n       Upcoming Workshops");
    printf("\n================================");

    int count = 1;
    // Read until the end of the file
    while (fscanf(file, " %[^,], %[^,], %d, %d", workshop.eventname, workshop.month, &workshop.day, &workshop.year) == 4)
    {
        printf("\n%d. %s on %s %d, %d", count, workshop.eventname, workshop.month, workshop.day, workshop.year);
        count++;
    }

    do
    {
        printf("\n\nAre you Interested to Join (y/n): ");
        scanf("%s", &choice);
        getchar();
        if(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            printf("Invalid input, Please enter 'Y' for Yes and 'N' for No.");
        }
        else if (choice == 'y' || choice == 'Y')
        {
            printf("\n[Please register on Front Desk or Visit our Website.]");
            return;
        }
        else
        {
            return;
        }
    }while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

    fclose(file);
}


//Community Programs
void communityprograms()
{
    char choice;
    Event community;
    FILE *file = fopen("community.txt", "r");
    if (file == NULL)
    {
        printf("No Workshops\n");
        return;
    }

    printf("\n================================");
    printf("\n  Upcoming Community Programs");
    printf("\n================================");

    int count = 1;
    // Read until the end of the file
    while (fscanf(file, " %[^,], %[^,], %d, %d", community.eventname, community.month, &community.day, &community.year) == 4)
    {
        printf("\n%d. %s on %s %d, %d", count, community.eventname, community.month, community.day, community.year);
        count++;
    }

    do
    {
        printf("\n\nAre you Interested to Join (y/n): ");
        scanf("%s", &choice);
        getchar();
        if(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            printf("Invalid input, Please enter 'Y' for Yes and 'N' for No.");
        }
        else if (choice == 'y' || choice == 'Y')
        {
            printf("\n[Please register on Front Desk or Visit our Website.]");
            return;
        }
        else
        {
            return;
        }
    }while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');
    fclose(file);
}



//Library Services Overview
void libraryservices()
{
    int choice;
    do
    {
        printf("\n================================================");
        printf("\n  Welcome to The Library Services Overview Page");
        printf("\n================================================");
        printf("\n\n1. About Library Services");
        printf("\n2. Membership Benefits");
        printf("\n3. How to Join The Library");
        printf("\n4. Exit");
        printf("\n\n================================");
        printf("\n\nPlease Choose an Option:");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            aboutlibrary();
            break;
        case 2:
            membership();
            break;
        case 3:
            joinlibrary();
            break;
        case 4:
            printf("\n\n==============");
            printf("\n Exiting....");
            printf("\n==============");
            break;
        default:
            printf("\nInvalid Choice. Please insert the Correct Input");
        }
    }while (choice != 4);
}



//About Library
void aboutlibrary()
{
    Services service;
    FILE *file = fopen("libraryservices.txt", "r");
    if (file == NULL)
    {
        printf("No Library Services\n");
        return;
    }

    printf("\n================================");
    printf("\n     About Library Services");
    printf("\n================================");
    printf("\nOur Library offers the following services:\n");

    // Read until the end of the file
    while (fscanf(file, " %[^\n]", service.aboutlibraryservices) == 1)
    {
        printf("- %s\n", service.aboutlibraryservices);

    }

    fclose(file);
}


//Membership
void membership()
{
    Services service;
    FILE *file = fopen("membership.txt", "r");
    if (file == NULL)
    {
        printf("No Membership Benefits\n");
        return;
    }

    printf("\n================================");
    printf("\n      Membership Benefits");
    printf("\n================================");
    printf("\nOur As a Library Member, you can:\n");

    // Read until the end of the file
    while (fscanf(file, " %[^\n]", service.aboutlibraryservices) == 1)
    {
        printf("- %s\n", service.aboutlibraryservices);
    }

    fclose(file);
}




//About Library
void joinlibrary()
{
    Services service;
    FILE *file = fopen("joinlibrary.txt", "r");
    if (file == NULL)
    {
        printf("Can't Join Library\n");
        return;
    }

    printf("\n================================");
    printf("\n How to Join Library Membership");
    printf("\n================================");
    printf("\nOur Library offers the following services:\n");

    // Read until the end of the file
    while (fscanf(file, " %[^\n]", service.aboutlibraryservices) == 1)
    {
        printf("- %s\n", service.aboutlibraryservices);
    }

    fclose(file);
}



int main()
{
    int choice;
    do
    {
        printf("\n====================");
        printf("\n     Hey Guest");
        printf("\n====================");
        printf("\n\n1. Library Exploration");
        printf("\n2. Event Information");
        printf("\n3. Library Service Overview");
        printf("\n4. Exit");
        printf("\n\n==================== ");
        printf("\n\nPlease Choose an Option:");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            libraryexploration();
            break;
        case 2:
            eventinformation();
            break;
        case 3:
            libraryservices();
            break;
        case 4:
            printf("\n\n========");
            printf("\n  BYE!");
            printf("\n========");
            break;
        default:
            printf("\n[Invalid Choice. Please insert the Correct Input.]");
        }
    }while (choice != 4);
}


