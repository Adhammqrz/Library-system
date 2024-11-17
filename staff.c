#include "main.h"

// Function declarations
void main_menu(void);
int menu_option(void);

void member_menu(void);
int member_option(void);
void member_assistance(void);
void search_book(void);
void reserves_book(void);
void service(void);

void shelf_page(void);
int shelf_option(void);
void shelf_management(void);
void list_shelf(void);
void update_shelf(void);
void digital_resource_assistance(void);
void e_books(void);
void online_journals(void);
void audiobooks(void);

#define MAX_BOOKS 100
#define MAX_MEMBERS 100
#define MAX_BORROW_RECORDS 100

void main_menu(void) {
    printf("\n-----------------------------------\n");
    printf("Welcome to Library Staff\n");
    printf("1. Member Assistance\n");
    printf("2. Shelf Management\n");
    printf("3. Digital Resource Assistance\n");
    printf("4. Exit\n");
    printf("-----------------------------------\n");
}

int menu_option(void) {
    int choice;

    while (1) {
        printf("Enter an option: ");
        if (scanf("%d", &choice) == 1) {
            getchar(); // Consume the newline character left in the buffer
            if (choice >= 1 && choice <= 4) {
                return choice;
            } else {
                printf("Invalid option. Please re-enter.\n");
            }
        } else {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }
}

void member_menu(void){
    printf("-----------------------------------\n");
    printf("Welcome to Member Assistance Page\n");
    printf("1. Search Book\n");
    printf("2. Provide Information on Library Service\n");
    printf("3. Reserve Book\n");
    printf("4. Back to Home Page\n");
    printf("-----------------------------------\n");
}

int member_option(void) {
    int choice;

    while (1) {
        printf("Enter an option: ");
        if (scanf("%d", &choice) == 1) {
            getchar(); // Consume the newline character left in the buffer
            if (choice >= 1 && choice <= 4) {
                return choice;
            } else {
                printf("Invalid option. Please re-enter.\n");
            }
        } else {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }
}

void member_assistance(void) {
    int choice;

    while (1) {
        member_menu();
        choice = member_option();

        switch (choice) {
            case 1:
                search_book();
                break;
            case 2:
                service();
                break;
            case 3:
                reserves_book();
                break;
            case 4:
                printf("Returning to Main Menu...\n\n");
                return; // Exit the member_assistance function
            default:
                printf("Error: Invalid option.\n");
                break;
        }
    }
}

void search_book(void) {
    int choice;
    char search_term[256];
    char continue_choice = '\0';
    Book books[MAX_BOOKS];
    int book_count = 0;

    FILE *file = fopen("book.txt", "r");
    if (file == NULL) {
        perror("Error opening book.txt");
        return;
    }

    while (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                  books[book_count].shelfID, books[book_count].id, books[book_count].title,
                  books[book_count].author, books[book_count].genre,
                  &books[book_count].quantity, books[book_count].type) == 7) {
        book_count++;
        if (book_count >= MAX_BOOKS) {
            printf("Maximum book limit reached. Some books may not be loaded.\n");
            break;
        }
    }
    fclose(file);

    if (book_count == 0) {
        printf("No books available to search.\n");
        return;
    }

    do {
        printf("\n---- Search Book Menu ----\n");
        printf("1. Search by Book Name\n");
        printf("2. Search by Book Author\n");
        printf("3. Search by Book Genre\n");
        printf("4. Search by Book Type\n");
        printf("5. Exit\n");
        printf("--------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int found = 0;

        switch (choice) {
            case 1:
                printf("Enter Book Name to search: ");
                scanf(" %[^\n]s", search_term);
                break;
            case 2:
                printf("Enter Book Author to search: ");
                scanf(" %[^\n]s", search_term);
                break;
            case 3:
                printf("Enter Book Genre to search: ");
                scanf(" %[^\n]s", search_term);
                break;
            case 4:
                printf("Enter Book Type to search: ");
                scanf(" %[^\n]s", search_term);
                break;
            case 5:
                printf("Exiting search.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }

        printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
               "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
        printf("-------------------------------------------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < book_count; i++) {
            int match = 0;
            switch (choice) {
                case 1: match = strstr(books[i].title, search_term) != NULL; break;
                case 2: match = strstr(books[i].author, search_term) != NULL; break;
                case 3: match = strstr(books[i].genre, search_term) != NULL; break;
                case 4: match = strstr(books[i].type, search_term) != NULL; break;
            }

            if (match) {
                printf("%-10s %-10s %-30s %-30s %-20s %-10d %-20s\n",
                       books[i].shelfID, books[i].id, books[i].title, books[i].author,
                       books[i].genre, books[i].quantity, books[i].type);
                found = 1;
            }
        }

        if (!found) {
            printf("No books found for the specified search term.\n");
        }

        printf("Do you want to search for another book? (y/n): ");
        getchar();  // Clear newline from buffer
        scanf("%c", &continue_choice);
    } while (continue_choice == 'y' || continue_choice == 'Y');
}

void service(void) {
    int choice;
    char line[256];
    FILE *servicefile = fopen("service.txt", "r");
    if (servicefile == NULL) {
        printf("Error opening service.txt.\n");
        return;
    }

    while (1) {
        printf("\n---- Service Menu ----\n");
        printf("1. Study and Meeting Spaces\n");
        printf("2. Technology and Internet Services\n");
        printf("3. Children’s and Teen Programs\n");
        printf("4. Community Engagement and Cultural Programs\n");
        printf("5. Exit\n");
        printf("--------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        rewind(servicefile);

        if (choice >= 1 && choice <= 4) {
            for (int i = 0; i < choice - 1; i++) {
                fgets(line, sizeof(line), servicefile);
            }
            if (fgets(line, sizeof(line), servicefile)) {
                printf("\n--- Selected Service ---\n");
                printf("%s\n", line);
                printf("------------------------\n");
            }
        } else if (choice == 5) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    fclose(servicefile);
}

void reserves_book(void) {
    int duration = 0;
    char day[10], continue_choice;
    char member_username[50];

    do {
        FILE *file = fopen("book.txt", "r");
        if (file == NULL) {
            printf("Error opening book.txt.\n");
            return;
        }

        printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
               "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
        printf("-------------------------------------------------------------------------------------------------------------------------------\n");

        Book book;
        while (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                      book.shelfID, book.id, book.title, book.author, book.genre, &book.quantity, book.type) == 7) {
            printf("%-10s %-10s %-30s %-30s %-20s %-10d %-20s\n",
                   book.shelfID, book.id, book.title, book.author, book.genre, book.quantity, book.type);
        }
        fclose(file);

        char reserveBookID[50];
        int bookExists = 0;

        while (!bookExists) {
            printf("Enter the Book ID you want to reserve (or type 'back' to return to the menu): ");
            scanf("%s", reserveBookID);

            if (strcmp(reserveBookID, "back") == 0) {
                return;
            }

            file = fopen("book.txt", "r");
            if (file == NULL) {
                printf("Error opening book.txt.\n");
                return;
            }

            while (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                          book.shelfID, book.id, book.title, book.author, book.genre, &book.quantity, book.type) == 7) {
                if (strcmp(book.id, reserveBookID) == 0) {
                    bookExists = 1;
                    break;
                }
            }
            fclose(file);

            if (!bookExists) {
                printf("Book ID %s not found. Please enter a valid Book ID or type 'back' to return to the menu.\n", reserveBookID);
            }
        }

        FILE *historyFile = fopen("borrowbook.txt", "r");
        if (historyFile == NULL) {
            printf("Error opening borrowbook.txt.\n");
            return;
        }

        printf("\nBorrow History for Book ID %s:\n", reserveBookID);
        printf("%-10s %-10s %-20s %-10s %-10s %-10s\n", "Member ID", "Book ID", "Book Name", "Date", "Status", "Overdue Days");
        printf("--------------------------------------------------------------------------\n");

        BorrowBook borrow;
        int historyFound = 0;
        while (fscanf(historyFile, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d\n",
                      borrow.username, borrow.bookid, borrow.booktitle, borrow.duedate, borrow.status, &borrow.fines) == 6) {
            if (strcmp(borrow.bookid, reserveBookID) == 0) {
                printf("%-10s %-10s %-20s %-10s %-10s %-10d\n",
                       borrow.username, borrow.bookid, borrow.booktitle, borrow.duedate, borrow.status, borrow.fines);
                historyFound = 1;
            }
        }
        fclose(historyFile);

        if (!historyFound) {
            printf("No borrow history found for Book ID %s.\n", reserveBookID);
        }

        printf("Do you want to reserve the book with ID %s? (y/n): ", reserveBookID);
        getchar();  // Clear newline from buffer
        scanf("%c", &continue_choice);

        if (continue_choice == 'y' || continue_choice == 'Y') {
            printf("Enter your Username: ");
            scanf("%s", member_username);

            FILE *memberfile = fopen("member.txt", "r");
            if (memberfile == NULL) {
                printf("Error opening member.txt.\n");
                return;
            }

            Member member;
            int found = 0;
            while (fscanf(memberfile, "%49[^,],%49[^,],%d,%99[^,],%49[^\n]\n",
                          member.username, member.password, &member.role, member.name, member.status) == 5) {
                if (strcmp(member.username, member_username) == 0) {
                    found = 1;
                    break;
                }
            }
            fclose(memberfile);

            if (found) {
                file = fopen("book.txt", "r");
                FILE *tempfile = fopen("temp.txt", "w");
                if (file == NULL || tempfile == NULL) {
                    printf("Error opening files.\n");
                    return;
                }

                while (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                              book.shelfID, book.id, book.title, book.author, book.genre, &book.quantity, book.type) == 7) {
                    if (strcmp(book.id, reserveBookID) == 0) {
                        printf("Available Quantity: %d\n", book.quantity);

                        printf("How many copies do you want to reserve? ");
                        int quantity_reserve;
                        scanf("%d", &quantity_reserve);

                        if (quantity_reserve > 0 && quantity_reserve <= book.quantity) {
                            book.quantity -= quantity_reserve;
                            printf("Reservation successful! Reserved %d copies of '%s'.\n", quantity_reserve, book.title);

                            FILE *reservefile = fopen("reservation.txt", "a");
                            if (reservefile != NULL) {
                                printf("Enter day for reserve (DD/MM/YY): ");
                                scanf("%s", day);
                                printf("Enter reserve duration (how many days): ");
                                scanf("%d", &duration);
                                fprintf(reservefile, "%s,%s,%s,%d,%s,%d\n",
                                        member_username, book.id, book.title, quantity_reserve, day, duration);
                                fclose(reservefile);
                            }
                        } else if (quantity_reserve > book.quantity) {
                            printf("Not enough copies available to reserve. Keeping the book quantity unchanged.\n");
                        }

                        fprintf(tempfile, "%s,%s,%s,%s,%s,%d,%s\n",
                                book.shelfID, book.id, book.title, book.author, book.genre,
                                book.quantity < 0 ? 0 : book.quantity,  // Ensure quantity is never negative.
                                book.type);
                    } else {
                        fprintf(tempfile, "%s,%s,%s,%s,%s,%d,%s\n",
                                book.shelfID, book.id, book.title, book.author, book.genre, book.quantity, book.type);
                    }
                }
                fclose(file);
                fclose(tempfile);

                remove("book.txt");
                rename("temp.txt", "book.txt");
            } else {
                printf("Member not found.\n");
            }
        }

        printf("Do you want to reserve another book? (y/n): ");
        getchar();
        scanf("%c", &continue_choice);

    } while (continue_choice == 'Y' || continue_choice == 'y');
}



void shelf_page(void) {
    printf("-----------------------------------\n");
    printf("Welcome to Shelf Management Page\n");
    printf("1. List Shelf\n");
    printf("2. Update Shelf and Remove Book\n");
    printf("3. Back to Home Page\n");
    printf("-----------------------------------\n");
}

int shelf_option(void) {
    int choice;

    while (1) {
        printf("Enter an option : ");
        if (scanf("%d", &choice) == 1) {
            if (choice >= 1 && choice <= 3) {
                return choice;
            } else {
                printf("Invalid option. Please re-enter.\n");
            }
        } else {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }
}

void shelf_management(void) {
    int choice;

    while (1) {
        shelf_page();
        choice = shelf_option();

        switch (choice) {
            case 1:
                list_shelf();
                break;
            case 2:
                update_shelf();
                break;
            case 3:
                printf("Returning to Main Menu...\n\n");
                return;  // Return to the main Library Staff menu
            default:
                printf("Error: Invalid option.\n");
                break;
        }
    }
}

void list_shelf(void) {
    char shelf_id[50];
    char continue_choice;
    int found;

    FILE *file = fopen("book.txt", "r");
    if (file == NULL) {
        printf("Error opening book.txt.\n");
        return;
    }
    do {
        printf("Enter Shelf ID to list: ");
        scanf(" %[^\n]s", shelf_id);
        found = 0;
        rewind(file);
        printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
               "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
        printf("-------------------------------------------------------------------------------------------------------------------------------\n");

        Book book;
        while (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                      book.shelfID, book.id, book.title, book.author, book.genre,
                      &book.quantity, book.type) != EOF) {
            if (strstr(book.shelfID, shelf_id) != NULL) {
                printf("%-10s %-10s %-30s %-30s %-20s %-10d %-20s\n",
                       book.shelfID, book.id, book.title, book.author, book.genre,
                       book.quantity, book.type);
                found = 1;
            }
        }
        if (!found) {
            printf("No books found matching Shelf ID '%s'.\n", shelf_id);
        }

        printf("Do you want to list another shelf? (y/n): ");
        getchar();  // Clear newline from buffer
        scanf("%c", &continue_choice);
    } while (continue_choice == 'y' || continue_choice == 'Y');
    fclose(file);
}


void update_shelf(void) {
    char book_id[50], new_shelf_id[50];
    char continue_choice;
    int found;

    do {
        FILE *file = fopen("book.txt", "r");
        if (file == NULL) {
            printf("Error opening book.txt.\n");
            return;
        }

        printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
               "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
        printf("-------------------------------------------------------------------------------------------------------------------------------\n");

        Book book;
        while (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                      book.shelfID, book.id, book.title, book.author, book.genre,
                      &book.quantity, book.type) != EOF) {
            if (strcmp(book.type, "Physical") == 0) {
                printf("%-10s %-10s %-30s %-30s %-20s %-10d %-20s\n",
                       book.shelfID, book.id, book.title, book.author, book.genre,
                       book.quantity, book.type);
            }
        }

        printf("Enter Book ID to update placement: ");
        scanf("%s", book_id);

        FILE *tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            printf("Error creating temp file.\n");
            fclose(file);
            return;
        }

        rewind(file);
        found = 0;

        while (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                      book.shelfID, book.id, book.title, book.author, book.genre,
                      &book.quantity, book.type) != EOF) {
            if (strcmp(book.id, book_id) == 0) {
                printf("Enter new Shelf ID for Book ID %s: ", book_id);
                scanf("%s", new_shelf_id);
                strcpy(book.shelfID, new_shelf_id);
                found = 1;
            }
            fprintf(tempFile, "%s,%s,%s,%s,%s,%d,%s\n",
                    book.shelfID, book.id, book.title, book.author, book.genre,
                    book.quantity, book.type);
        }

        fclose(file);
        fclose(tempFile);

        if (found) {
            remove("book.txt");
            rename("temp.txt", "book.txt");
            printf("Book ID %s has been updated with Shelf ID %s.\n", book_id, new_shelf_id);
        } else {
            printf("Book ID %s not found.\n", book_id);
        }

        printf("Do you want to update another book? (y/n): ");
        getchar();  // Clear newline from buffer
        scanf("%c", &continue_choice);
    } while (continue_choice == 'y' || continue_choice == 'Y');
}

void digital_page(void){
    printf("-----------------------------------\n");
    printf("Welcome to Digital Resource Assistance Page\n");
    printf("1. E-Books\n");
    printf("2. Online Journals\n");
    printf("3. Audiobooks\n");
    printf("4. Back to Home Page\n");
    printf("-----------------------------------\n");
}

int digital_option(void) {
    int choice;

    while (1) {
        printf("Enter an option: ");
        if (scanf("%d", &choice) == 1) {
            if (choice >= 1 && choice <= 4) {
                return choice;
            } else {
                printf("Invalid option. Please re-enter.\n");
            }
        } else {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
        }
    }
}

void digital_resource_assistance(void) {
    int choice;

    while (1) {
        digital_page();
        choice = digital_option();

        switch (choice) {
            case 1:
                e_books();
                break;
            case 2:
                online_journals();
                break;
            case 3:
                audiobooks();
                break;
            case 4:
                printf("Returning to Main Menu...\n\n");
                return;
            default:
                printf("Error: Invalid option.\n");
                break;
        }

    }
}

void e_books(void) {
    FILE *file = fopen("book.txt", "r");
    if (file == NULL) {
        printf("Error opening book.txt.\n");
        return;
    }

    printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
           "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");

    Book book;
    while (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                  book.shelfID, book.id, book.title, book.author, book.genre,
                  &book.quantity, book.type) != EOF) {
        if (strcmp(book.type, "Ebook") == 0) {
            printf("%-10s %-10s %-30s %-30s %-20s %-10d %-20s\n",
                   book.shelfID, book.id, book.title, book.author, book.genre,
                   book.quantity, book.type);
        }
    }
    fclose(file);
}

void online_journals(void) {
    FILE *file = fopen("book.txt", "r");
    if (file == NULL) {
        printf("Error opening book.txt.\n");
        return;
    }

    printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
           "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");

    Book book;
    while (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                  book.shelfID, book.id, book.title, book.author, book.genre,
                  &book.quantity, book.type) != EOF) {
        if (strcmp(book.type, "Online Journal") == 0) {
            printf("%-10s %-10s %-30s %-30s %-20s %-10d %-20s\n",
                   book.shelfID, book.id, book.title, book.author, book.genre,
                   book.quantity, book.type);
        }
    }
    fclose(file);
}

void audiobooks(void) {
    FILE *file = fopen("book.txt", "r");
    if (file == NULL) {
        printf("Error opening book.txt.\n");
        return;
    }

    printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
           "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");

    Book book;
    while (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                  book.shelfID, book.id, book.title, book.author, book.genre,
                  &book.quantity, book.type) != EOF) {
        if (strcmp(book.type, "AudioBook") == 0) {
            printf("%-10s %-10s %-30s %-30s %-20s %-10d %-20s\n",
                   book.shelfID, book.id, book.title, book.author, book.genre,
                   book.quantity, book.type);
        }
    }
    fclose(file);
}

// Main function
int staffmenu(void) {
    int choice;

    do {
        main_menu();
        choice = menu_option();

        switch (choice) {
            case 1:
                member_assistance();
                break;
            case 2:
                shelf_management();
                break;
            case 3:
                digital_resource_assistance();
                break;
            case 4:
                printf("Logging Out. Goodbye!\n");
                return 0;  // Exit the function and return to the main login menu
            default:
                printf("Error: Invalid option.\n");
                break;
        }
    } while (choice != 4);  // Continue looping unless the user selects option 4 to log out
    return 0;
}
