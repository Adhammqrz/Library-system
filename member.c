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


void reserve_book(void) {
    int choice;
    char member_id[50];
    char line[256];
    int day, month;
    char continue_choice;

    do {
        
        FILE *file = fopen("book.txt", "r");
        if (file == NULL) {
            printf("Error opening book.txt.\n");
            return;
        }

        printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
               "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
        printf("---------------------------------------------------------------------------------------------------------\n");

        while (fgets(line, sizeof(line), file)) {
            char shelfID[50], bookID[50], bookName[256], author[256], genre[256], quantity[50], type[256];
            sscanf(line, "%49[^,],%49[^,],%255[^,],%255[^,],%255[^,],%49[^,],%255[^\n]",
                   shelfID, bookID, bookName, author, genre, quantity, type);
            printf("%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                   shelfID, bookID, bookName, author, genre, quantity, type);
        }
        fclose(file);

        int bookExists = 0;
        char reserveBookID[50];

        
        while (!bookExists) {
            printf("Enter the Book ID you want to reserve (or type 'exit' to return to the menu): ");
            scanf("%s", reserveBookID);

            
            if (strcmp(reserveBookID, "exit") == 0) {
                return;  
            }

            
            file = fopen("book.txt", "r");
            if (file == NULL) {
                printf("Error opening book.txt.\n");
                return;
            }

           
            while (fgets(line, sizeof(line), file)) {
                char bookID[50];
                sscanf(line, "%*[^,],%49[^,]", bookID);
                if (strcmp(bookID, reserveBookID) == 0) {
                    bookExists = 1;
                    break;
                }
            }
            fclose(file);

            if (!bookExists) {
                printf("Book ID %s not found. Please enter a valid Book ID or type 'exit' to return to the menu.\n", reserveBookID);
            }
        }

        
        FILE *borrowfile = fopen("borrowbook.txt", "r");
        if (borrowfile == NULL) {
            printf("Error opening borrowbook.txt\n");
            return;
        }

        printf("\n%-10s %-10s %-30s %-10s %-10s %-10s\n",
               "Member", "Book ID", "Book Name", "Date", "Status", "Fine");
        printf("--------------------------------------------------------------------\n");

        int borrowRecordFound = 0;
        while (fgets(line, sizeof(line), borrowfile)) {
            char member[50], bID[50], bName[256], date[20], status[50], fine[10];
            sscanf(line, "%49[^,],%49[^,],%255[^,],%19[^,],%49[^,],%9[^\n]",
                   member, bID, bName, date, status, fine);
            if (strcmp(bID, reserveBookID) == 0) {
                printf("%-10s %-10s %-30s %-10s %-10s %-10s\n",
                       member, bID, bName, date, status, fine);
                borrowRecordFound = 1;
            }
        }
        fclose(borrowfile);

        if (!borrowRecordFound) {
            printf("No borrow records found for Book ID %s.\n", reserveBookID);
        }

       
        printf("Do you want to reserve the book with ID %s? (y/n): ", reserveBookID);
        getchar();  
        scanf("%c", &continue_choice);

        if (continue_choice == 'y' || continue_choice == 'Y') {
            
            printf("Enter your Member ID: ");
            scanf("%s", member_id);

            FILE *memberfile = fopen("member.txt", "r");
            if (memberfile == NULL) {
                printf("Error opening member.txt\n");
                return;
            }

            int found = 0;
            while (fgets(line, sizeof(line), memberfile)) {
                if (strstr(line, member_id) != NULL) {
                    found = 1;
                    break;
                }
            }
            fclose(memberfile);

            if (found) {
                
                printf("Enter the day of reservation: ");
                scanf("%d", &day);
                printf("Enter the month of reservation: ");
                scanf("%d", &month);

                
                if (day < 1 || day > 31 || month < 1 || month > 12) {
                    printf("Invalid date. Please enter a valid day and month.\n");
                    continue;
                }

               
                FILE *reservationFile = fopen("reservation.txt", "a");
                if (reservationFile == NULL) {
                    printf("Error opening reservation.txt\n");
                    return;
                }

                fprintf(reservationFile, "%s,%s,%02d/%02d\n", member_id, reserveBookID, day, month);
                fclose(reservationFile);

                
                FILE *accountFile = fopen("account.txt", "a");
                if (accountFile == NULL) {
                    printf("Error opening account.txt\n");
                    return;
                }

                fprintf(accountFile, "Member ID: %s | Book ID: %s | Reservation Date: %02d/%02d\n",
                        member_id, reserveBookID, day, month);
                fclose(accountFile);

                printf("Reservation successful for Member ID: %s, Book ID: %s on %02d/%02d\n",
                       member_id, reserveBookID, day, month);
            } else {
                printf("Member ID not found in member.txt\n");
            }
        }

        printf("Do you want to reserve another book? (y/n): ");
        getchar();  // Clear newline from buffer
        scanf("%c", &continue_choice);

    } while (continue_choice == 'Y' || continue_choice == 'y');
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
    FILE *books = fopen("book.txt", "r");
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
        char shelfID[10], bookID[10], bookTitle[50], author[50], genre[20], availability[20], format[20];


        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",
               shelfID, bookID, bookTitle, author, genre, availability, format);


        if (strcasecmp(genre, preferredGenre) == 0) {
            printf("ID: %s\nTitle: %s\nAuthor: %s\nGenre: %s\nAvailability: %s\nFormat: %s\n\n",
                   bookID, bookTitle, author, genre, availability, format);
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
        printf("4. Pay fines\n");
        printf("5. View Book Recommendations\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchBook();
                break;
            case 2:
                reserve_book();
                break;
            case 3:
                viewAccount();
                break;
            case 4:
                payFines();
                break;
            case 5:
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


