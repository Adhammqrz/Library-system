#include <stdio.h>
#include <string.h>


void searchBook() {
    char title[50];
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open books file.\n");
        return;
    }

    printf("Enter the title of the book to search: ");
    scanf(" %[^\n]%*c", title);

    char line[200];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        char bookID[10], bookTitle[50], author[50], genre[20], available[10], format[20];
        int copies;

        
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d,%s", bookID, bookTitle, author, genre, &copies, format);

        if (strstr(bookTitle, title) != NULL) {
            printf("Book found:\nID: %s\nTitle: %s\nAuthor: %s\nGenre: %s\nCopies Available: %d\nFormat: %s\n",
                   bookID, bookTitle, author, genre, copies, format);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
    fclose(file);
}

void reserveBook() {
    char title[50];
    FILE *file = fopen("books.txt", "r+");
    FILE *accountFile = fopen("account.txt", "a");
    if (file == NULL || accountFile == NULL) {
        printf("Error: Could not open books or account file.\n");
        if (file != NULL) fclose(file);
        if (accountFile != NULL) fclose(accountFile);
        return;
    }

    printf("Enter the title of the book to reserve: ");
    scanf(" %[^\n]%*c", title);

    char line[200];
    int found = 0;
    long pos;

    while (fgets(line, sizeof(line), file)) {
        char bookID[10], bookTitle[50], author[50], genre[20], format[20];
        int copies;

       
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d,%s", bookID, bookTitle, author, genre, &copies, format);

        if (strstr(bookTitle, title) != NULL && strcmp(format, "physical") == 0 && copies > 0) {
            found = 1;
            pos = ftell(file) - strlen(line);
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s,%s,%s,%s,%d,%s\n", bookID, bookTitle, author, genre, copies - 1, format);
            printf("Book reserved successfully.\n");

          
            fprintf(accountFile, "Reserved Book: ID=%s, Title=%s\n",bookID, bookTitle);
            break;
        }
    }

    if (!found) {
        printf("Book not available or not found.\n");
    }
    fclose(file);
    fclose(accountFile);
}


void viewAccount() {
    FILE *file = fopen("account.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open account file.\n");
        return;
    }

    char line[100];
    printf("--- Account Details ---\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}


void renewBorrowedItems() {
    printf("All borrowed items have been renewed successfully.\n");
   
}


void payFines() {
    FILE *file = fopen("fines.txt", "r+");
    if (file == NULL) {
        printf("Error: Could not open fines file.\n");
        return;
    }

    double fine;
    fscanf(file, "%lf", &fine);

    if (fine > 0) {
        printf("Your overdue fine is: $%.2f\n", fine);
        printf("Do you want to pay it? (1 for Yes, 0 for No): ");
        int pay;
        scanf("%d", &pay);
        if (pay == 1) {
            fine = 0;
            fseek(file, 0, SEEK_SET);
            fprintf(file, "%.2f", fine);
            printf("Fine paid successfully.\n");
        } else {
            printf("Fine not paid.\n");
        }
    } else {
        printf("No fines due.\n");
    }
    fclose(file);
}

void recommendBooks() {
    FILE *books = fopen("books.txt", "r");
    if (books == NULL) {
        printf("Error: Could not open books file for recommendations.\n");
        return;
    }

    char preferredGenre[20];
    char line[200];
    int found = 0;

    printf("Enter your preferred genre: ");
    scanf(" %[^\n]%*c", preferredGenre);

    printf("\n--- Book Recommendations in Genre: %s ---\n", preferredGenre);
    while (fgets(line, sizeof(line), books)) {
        char bookID[10], bookTitle[50], author[50], genre[20], available[10], format[20];
        int copies;

        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d,%s", bookID, bookTitle, author, genre, &copies, format);

        if (strcasecmp(genre, preferredGenre) == 0) {
            printf("ID: %s\nTitle: %s\nAuthor: %s\nGenre: %s\nCopies Available: %d\nFormat: %s\n\n",
                   bookID, bookTitle, author, genre, copies, format);
            found = 1;
        }
    }

    if (!found) {
        printf("No books available in the genre \"%s\".\n", preferredGenre);
    }
    fclose(books);
}


void membermenu() {
    int choice;

    while (1) {
        printf("\n--- Library Member Menu ---\n");
        printf("1. Search for a book\n");
        printf("2. Reserve a book\n");
        printf("3. View account details\n");
        printf("4. Renew borrowed items\n");
        printf("5. Pay fines\n");
        printf("6. View Book Recommendations\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchBook();
                break;
            case 2:
                reserveBook();
                break;
            case 3:
                viewAccount();
                break;
            case 4:
                renewBorrowedItems();
                break;
            case 5:
                payFines();
                break;
            case 6:
                recommendBooks();
                break;
            case 0:
                printf("Exiting the system. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}


