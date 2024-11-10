#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_SUMMARY_LENGTH 1000
#define MAX_LINE_LENGTH 80
#define MAX_EVENTNAME_LENGTH 100
#define MAX_EVENTDETAILS_LENGTH 1000


typedef struct
{
    char shelfID[50];
    char ID[50];
    char title[50];
    char author[50];
    char genre[20];
    char availability[50];
    char version[50];
} Book;


typedef struct
{
    char aboutlibraryservices[100];
}Services;


typedef struct
{
    char booktitle[MAX_TITLE_LENGTH];
    char booksumm[MAX_SUMMARY_LENGTH];
} Summ;


typedef struct
{
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
            print_books_by_genre("Fiction");
            break;
        case 2:
            print_books_by_genre("Non-Fiction");
            break;
        case 3:
            print_books_by_genre("Science");
            break;
        case 4:
            print_books_by_genre("History");
            break;
        case 5:
            print_books_by_genre("Philosophy");
            break;
        case 6:
            print_books_by_genre("Biography");
            break;
        case 7:
            printf("Back to Main Menu.\n");
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
                printf("\nPlease enter at least 3 characters for more accurate finding.\n");
            }
        }while (strlen(searchTerm)<3);



        file = fopen("book.txt", "r");
        if (file == NULL)
        {
            printf("No Available Book\n");
            continue;
        }

        int found = 0;
        while(fscanf(file, "%[^,], %[^,], %[^,], %[^,],%[^,], %[^,], %[^\n]", book.shelfID, book.ID, book.title, book.author, book.genre, book.availability, book.version) == 7)
            {
                if (strstr(book.title, searchTerm) != NULL || strstr(book.author, searchTerm) != NULL)
                {
                    printf("\nGenre: %s\n", book.genre);
                    printf("Title: %s\n", book.title);
                    printf("Author: %s\n", book.author);
                    printf("\nThe Book Exist in Our Library.\n");
                    found = 1;
                }
            }

        if (!found) {
            printf("\nNo matching books found.\n");
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

    } while (choice == 'y' || choice == 'Y');

    printf("Returning to main menu...\n");
}



//Available Books
void available()
 {
    Book book;
    FILE *file = fopen("book.txt", "r");
    if (file == NULL)
    {
        printf("No Available Book\n");
        return;
    }

    printf("\n================================");
    printf("\n     Available Book List");
    printf("\n================================");

    // Read until the end of the file
    while (fscanf(file, "%[^,], %[^,], %[^,], %[^,],%[^,], %[^,], %[^\n]", book.shelfID, book.ID, book.title, book.author, book.genre, book.availability, book.version) == 7)
        {
            if (strcasecmp(book.availability, "available") == 0)
            {
                printf("\nGenre: %s\n", book.genre);
                printf("Title: %s\n", book.title);
                printf("Author: %s\n", book.author);
                printf("Book's Format: %s\n", book.version);
            }
        }

    fclose(file);
}




//Print Available Book Based on Genre
void print_books_by_genre(const char *genre_name)
{
    Book book;
    FILE *file = fopen("book.txt", "r");
    if (file == NULL)
    {
        printf("No Available Book\n");
        return;
    }

    printf("\n================================");
    printf("\n     %s Book List", genre_name);
    printf("\n================================");

    int found = 0;
    while(fscanf(file, "%[^,], %[^,], %[^,], %[^,],%[^,], %[^,], %[^\n]", book.shelfID, book.ID, book.title, book.author, book.genre, book.availability, book.version) == 7)
    {
        if (strcasecmp(book.genre, genre_name) == 0)
        {
            printf("\nGenre: %s\n", book.genre);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\nNo %s Books Found.\n", genre_name);
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
            printf("\nInvalid input, please enter 'Y' for Yes and 'N' for No.\n");
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
            printf("\n\nEnter the Book Title: ");
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
                printf("======================\n");
                printf("%s\n\n", summ.booktitle);
                print_wrapped_text(summ.booksumm, MAX_LINE_LENGTH);
                printf("\n========================================================\n");
                found = 1;
            }
        }

        if (!found)
        {
            printf("\nNo matching books found.\n");
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
            print_by_event_type("'Workshop");
            break;
        case 3:
            print_by_event_type("'Community Program");
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
    Eventdet event;
    FILE *file = fopen("event_details.txt", "r");
    char line[1200];
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
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%99[^,], %999[^|]| %[^,], %d, %d, %[^,], %[^\n]", event.eventname, event.eventsumm, event.month, &event.day, &event.year, event.time, event.location);
        printf("\n%d.%s on %s %d, %d", count, event.eventname, event.month, event.day, event.year);
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
            printf("\nInvalid input, Please enter 'Y' for Yes and 'N' for No.");
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
            printf("No Event Finding\n");
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
                printf("======================\n");
                printf("\n%s\n\n", eventdet.eventname);
                print_wrapped_text(eventdet.eventsumm, MAX_LINE_LENGTH);
                printf("\nDate: %s %d, %d", eventdet.month, eventdet.day, eventdet.year);
                printf("\nTime: %s", eventdet.time);
                printf("\nLocation: %s\n", eventdet.location);
                printf("\n===========================================================\n");
                found = 1;
            }
        }

        if(!found)
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



void print_by_event_type(const char *eventtype)
{
    char line[1200];
    char choice;
    Eventdet events;
    FILE *file = fopen("event_details.txt", "r");
    if (file == NULL)
    {
        printf("No Event.\n");
        return;
    }

    printf("\n========================================");
    printf("\n       Upcoming %s'", eventtype);
    printf("\n========================================");

    int count = 1;
    int found = 0;

    // Read until the end of the file
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%99[^,], %999[^|]| %[^,], %d, %d, %[^,], %[^\n]", events.eventname, events.eventsumm, events.month, &events.day, &events.year, events.time, events.location);
        if (strncmp(events.eventname, eventtype, strlen(eventtype)) == 0)
        {
            printf("\n%d. %s on %s %d, %d", count, events.eventname, events.month, events.day, events.year);
            found = 1;
            count++;
        }
    }

    if (!found) {
        printf("\nNo %s events found.\n", eventtype);
    }

    do {
        printf("\n\nAre you Interested to Join (y/n): ");
        scanf(" %c", &choice);
        getchar();
        if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
            printf("\nInvalid input, Please enter 'Y' for Yes and 'N' for No.");
        } else if (choice == 'y' || choice == 'Y') {
            printf("\n[Please register at the Front Desk or Visit our Website.]\n");
            return;
        } else {
            return;
        }
    } while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

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
    printf("\nHere are The Steps:\n");

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


