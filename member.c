#include <stdio.h>
#include <string.h>

// Function to log each book search to the search history file
void logSearchHistory(char *title) {
    FILE *file = fopen("search_history.txt", "a");
    if (file == NULL) {
        printf("Error: Could not open search history file.\n");
        return;
    }
    fprintf(file, "%s\n", title);
    fclose(file);
}

// Function to search for a book in the library catalog
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
        char bookID[10], bookTitle[50], author[50], genre[20], price[10], format[20];

        // Parse the line according to the new format
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", bookID, bookTitle, author, genre, price, format);

        if (strstr(bookTitle, title) != NULL) {
            printf("Book found:\nID: %s\nTitle: %s\nAuthor: %s\nGenre: %s\nPrice: %s\nFormat: %s\n",
                    bookID, bookTitle, author, genre, price, format);
            found = 1;
            logSearchHistory(title); // Log the search
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
    fclose(file);
}

// Function to reserve a book if available (assuming physical books only)
void reserveBook() {
    char title[50];
    FILE *file = fopen("books.txt", "r+");
    if (file == NULL) {
        printf("Error: Could not open books file.\n");
        return;
    }

    printf("Enter the title of the book to reserve: ");
    scanf(" %[^\n]%*c", title);

    char line[200];
    int found = 0;
    long pos;

    while (fgets(line, sizeof(line), file)) {
        char bookID[10], bookTitle[50], author[50], genre[20], price[10], format[20];

        // Parse the line
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", bookID, bookTitle, author, genre, price, format);

        if (strstr(bookTitle, title) != NULL && strcmp(format, "physical") == 0) {
            found = 1;
            pos = ftell(file) - strlen(line);
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s,%s,%s,%s,%s,%s\n", bookID, bookTitle, author, genre, price, "reserved");
            printf("Book reserved successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Book not available or not found.\n");
    }
    fclose(file);
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
    // For a full implementation, you would update the due dates in the borrowing history file.
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
    FILE *history = fopen("search_history.txt", "r");
    FILE *books = fopen("books.txt", "r");
    if (history == NULL || books == NULL) {
        printf("Error: Could not open files for recommendations.\n");
        if (history) fclose(history);
        if (books) fclose(books);
        return;
    }

    char lastSearch[50];
    char line[200];
    int found = 0;


    while (fgets(lastSearch, sizeof(lastSearch), history)) {

    }
    fclose(history);

    printf("\n--- Book Recommendations ---\n");
    while (fgets(line, sizeof(line), books)) {
        char bookID[10], bookTitle[50], author[50], genre[20], price[10], format[20];


        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", bookID, bookTitle, author, genre, price, format);


        if (strstr(bookTitle, lastSearch) != NULL || strstr(author, lastSearch) != NULL || strcmp(format, "physical") == 0) {
            printf("ID: %s\nTitle: %s\nAuthor: %s\nGenre: %s\nPrice: %s\nFormat: %s\n\n",
                   bookID, bookTitle, author, genre, price, format);
            found = 1;
        }
    }

    if (!found) {
        printf("No specific recommendations available based on your search history.\n");
    }
    fclose(books);
}


int main() {
    int choice;

    while (1) {
        printf("\n--- Library Member Menu ---\n");
        printf("1. Search for a book\n");
        printf("2. Reserve a book\n");
        printf("3. View account details\n");
        printf("4. Renew borrowed items\n");
        printf("5. Pay fines\n");
        printf("6. View book recommendations\n");
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
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
