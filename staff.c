#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function declarations
int login(char *username);
void main_menu(char *Username);
int menu_option(void);

void member_menu(void);
int member_option(void);
void member_assistance(void);
void search_book(void);
void reserve_book(void);
void service(void);

void shelf_page(void);
int shelf_option(void);
void shelf_management(void);
void list_shelf(void);
void update_shelf(void);

void digital_page(void);
int digital_option(void);
void digital_resource_assistance(void);
void e_books(void);
void online_journals(void);
void audiobooks(void);

int login(char *username) {
    char password[50];
    char line[256];
    char continue_choice;

    do {
        printf("Enter your username: ");
        scanf("%49s", username);

        printf("Enter your password: ");
        scanf("%49s", password);

        FILE *file = fopen("user.txt", "r");
        if (file == NULL) {
            printf("Error opening user.txt\n");
            return 0;
        }

        int loginSuccess = 0;

        while (fgets(line, sizeof(line), file)) {
            char fileUsername[50], filePassword[50], role[50];
            sscanf(line, "%49[^,],%49[^,],%49[^,\n]", fileUsername, filePassword, role);

            if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
                if (strcmp(role, "Staff") == 0 || strcmp(role, "Admin") != 0) {
                    printf("Login successful!\n");
                    loginSuccess = 1;
                    break;
                } else {
                    printf("Access denied. Role is not allowed.\n");
                    break;
                }
            }
        }
        fclose(file);

        if (loginSuccess) {
            return 1; // Login was successful
        } else {
            printf("Invalid username or password.\n");
        }
        
        printf("Enter Y to login again or any other key to exit: ");
        getchar();
        scanf("%c", &continue_choice);
        
    } while (continue_choice == 'Y' || continue_choice == 'y');

    return 0; // Login was unsuccessful
}


// Function to display the Main Menu
void main_menu(char *username) {
    printf("-----------------------------------\n");
    printf("Welcome to Library Staff %s\n", username);
    printf("1. Member Assistance\n");
    printf("2. Shelf Management\n");
    printf("3. Digital Resource Assistance\n");
    printf("4. Exit\n");
    printf("-----------------------------------\n");
}

// Function to get the user's choice from the Main Menu
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

// Function to display the Member Assistance Menu
void member_menu(void){
    printf("-----------------------------------\n");
    printf("Welcome to Member Assistance Page\n");
    printf("1. Search Book\n");
    printf("2. Provide Information on Library Service\n");
    printf("3. Reserve Book\n");
    printf("4. Back to Home Page\n");
    printf("-----------------------------------\n");
}

// Function to get the user's choice from the Member Assistance Menu
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

// Function to handle Member Assistance operations
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
                reserve_book();
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
    char bookname[256], bookauthor[256], bookgenre[256], booktype[256];
    char line[512];
    char continue_choice;

    FILE *file = fopen("book.txt", "r");
    if (file == NULL) {
        perror("Error opening book.txt");
        return;
    }

    if (fgets(line, sizeof(line), file) == NULL) {
        printf("No books available to search.\n");
        fclose(file);
        return;
    } else {
        rewind(file);
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

        int found = 0;  // Flag to check if a book was found

        switch (choice) {
            case 1:
                printf("Enter Book Name to search: ");
                scanf(" %[^\n]s", bookname);
                rewind(file);
                printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                        "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
                printf("---------------------------------------------------------------------------------------------------------\n");
                while (fgets(line, sizeof(line), file)) {
                    char shelfID[50], bookID[50], bookName[256], author[256], genre[256], quantity[50], type[256];
                    sscanf(line, "%49[^,],%49[^,],%255[^,],%255[^,],%255[^,],%49[^,],%255[^\n]",
                           shelfID, bookID, bookName, author, genre, quantity, type);

                    // Use strstr for partial match
                    if (strstr(bookName, bookname) != NULL) {
                        printf("%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                                shelfID, bookID, bookName, author, genre, quantity, type);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No book found with the specified name.\n");
                }
                break;

            case 2:
                printf("Enter Book Author to search: ");
                scanf(" %[^\n]s", bookauthor);
                rewind(file);
                printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                        "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
                printf("---------------------------------------------------------------------------------------------------------\n");
                while (fgets(line, sizeof(line), file)) {
                    char shelfID[50], bookID[50], bookName[256], author[256], genre[256], quantity[50], type[256];
                    sscanf(line, "%49[^,],%49[^,],%255[^,],%255[^,],%255[^,],%49[^,],%255[^\n]",
                           shelfID, bookID, bookName, author, genre, quantity, type);

                    // Use strstr for partial match
                    if (strstr(author, bookauthor) != NULL) {
                        printf("%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                                shelfID, bookID, bookName, author, genre, quantity, type);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No book found with the specified author.\n");
                }
                break;

            case 3:
                printf("Enter Book Genre to search: ");
                scanf(" %[^\n]s", bookgenre);
                rewind(file);
                printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                        "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
                printf("---------------------------------------------------------------------------------------------------------\n");
                while (fgets(line, sizeof(line), file)) {
                    char shelfID[50], bookID[50], bookName[256], author[256], genre[256], quantity[50], type[256];
                    sscanf(line, "%49[^,],%49[^,],%255[^,],%255[^,],%255[^,],%49[^,],%255[^\n]",
                           shelfID, bookID, bookName, author, genre, quantity, type);

                    // Use strstr for partial match
                    if (strstr(genre, bookgenre) != NULL) {
                        printf("%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                                shelfID, bookID, bookName, author, genre, quantity, type);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No book found with the specified genre.\n");
                }
                break;

            case 4:
                printf("Enter Book Type to search: ");
                scanf(" %[^\n]s", booktype);
                rewind(file);
                printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                        "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
                printf("---------------------------------------------------------------------------------------------------------\n");
                while (fgets(line, sizeof(line), file)) {
                    char shelfID[50], bookID[50], bookName[256], author[256], genre[256], quantity[50], type[256];
                    sscanf(line, "%49[^,],%49[^,],%255[^,],%255[^,],%255[^,],%49[^,],%255[^\n]",
                           shelfID, bookID, bookName, author, genre, quantity, type);

                    // Use strstr for partial match
                    if (strstr(type, booktype) != NULL) {
                        printf("%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                                shelfID, bookID, bookName, author, genre, quantity, type);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No book found with the specified type.\n");
                }
                break;

            case 5:
                printf("Exiting search.\n");
                fclose(file);
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("Do you want to search for another book? (y/n): ");
        getchar();  // Clear newline from buffer
        scanf("%c", &continue_choice);
    } while (continue_choice == 'y' || continue_choice == 'Y');

    fclose(file);
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

void reserve_book(void) {
    int duration = 0;
    char day[10];
    char member_id[50], line[256], continue_choice;

    do {
        // Display books from book.txt
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

        // Get the book ID to reserve
        char reserveBookID[50];
        int bookExists = 0;
        
        while (!bookExists) {
            printf("Enter the Book ID you want to reserve (or type 'back' to back to the menu): ");
            scanf("%s", reserveBookID);
            
            if (strcmp(reserveBookID, "back") == 0) {
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

        // Confirm reservation and member ID
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
                file = fopen("book.txt", "r");
                FILE *tempfile = fopen("temp.txt", "w");
                if (file == NULL || tempfile == NULL) {
                    printf("Error opening files.\n");
                    return;
                }

                char shelfID[50], bookID[50], bookName[256], author[256], genre[256], type[256], quantity[50];
                int availableQuantity = 0;
                
                while (fgets(line, sizeof(line), file)) {
                    sscanf(line, "%49[^,],%49[^,],%255[^,],%255[^,],%255[^,],%49[^,],%255[^\n]",
                           shelfID, bookID, bookName, author, genre, quantity, type);
                    
                    if (strcmp(bookID, reserveBookID) == 0) {
                        availableQuantity = atoi(quantity);
                        printf("Available Quantity: %d\n", availableQuantity);
                        
                        printf("How many copies do you want to reserve? ");
                        int quantity_reserve;
                        scanf("%d", &quantity_reserve);
                        getchar();

                        if (quantity_reserve > 0 && quantity_reserve <= availableQuantity) {
                            availableQuantity -= quantity_reserve;
                            fprintf(tempfile, "%s,%s,%s,%s,%s,%d,%s\n",
                                    shelfID, bookID, bookName, author, genre, availableQuantity, type);
                            
                            FILE *reservefile = fopen("reservation.txt", "a");
                            if (reservefile != NULL) {
                                printf("Enter day for reserve(DD/MM/YY): ");
                                scanf("%s", day);
                                printf("Enter reserve duration(how many days(number)): ");
                                scanf("%d", &duration);
                                fprintf(reservefile, "%s,%s,%s,%d,%s,%d\n",
                                        member_id, reserveBookID, bookName, quantity_reserve, day, duration);
                                fclose(reservefile);
                                printf("Reservation successful! Reserved %d copies of '%s'.\n", quantity_reserve, bookName);
                            }
                        } else {
                            printf("Not enough copies available to reserve.\n");
                        }
                    } else {
                        fputs(line, tempfile);
                    }
                }
                fclose(file);
                fclose(tempfile);
                
                remove("book.txt");
                rename("temp.txt", "book.txt");
            } else {
                printf("Member ID not found in member.txt\n");
            }
        }
        
        printf("Do you want to reserve for another book? (y/n): ");
        getchar();
        scanf("%c", &continue_choice);
        
    } while (continue_choice == 'Y' || continue_choice == 'y');
}

// Function to display the Shelf Management Menu
void shelf_page(void){
    printf("-----------------------------------\n");
    printf("Welcome to Shelf Management Page\n");
    printf("1. List Shelf\n");
    printf("2. Update Shelf and Remove Book\n");
    printf("3. Back to Home Page\n");
    printf("-----------------------------------\n");
}

// Function to get the user's choice from the Shelf Management Menu
int shelf_option(void) {
    int choice;

    while (1) {
        printf("Enter an option: ");
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

// Function to handle Shelf Management operations
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
                return; // Exit the shelf_management function
            default:
                printf("Error: Invalid option.\n");
                break;
        }
    }
}

void list_shelf(void){
    char line[256];
    char shelf_id[256];
    int found = 0;
    char continue_choice;
    
    FILE *file = fopen("book.txt","r");
    if (file == NULL){
        printf("Error open book.txt");
        return;
    }
    
    do{
        printf("Enter Shelf ID to list: ");
        scanf(" %[^\n]s", shelf_id);
        rewind(file);
        printf("\n%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
               "Shelf ID", "Book ID", "Book Name", "Author Name", "Genre", "Quantity", "Type");
        printf("---------------------------------------------------------------------------------------------------------\n");
        while (fgets(line, sizeof(line), file)) {
            char shelfID[50], bookID[50], bookName[256], author[256], genre[256], quantity[50], type[256];
            sscanf(line, "%49[^,],%49[^,],%255[^,],%255[^,],%255[^,],%49[^,],%255[^\n]",
                   shelfID, bookID, bookName, author, genre, quantity, type);

            // Use strstr for partial match
            if (strstr(shelfID, shelf_id) != NULL) {
                printf("%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n", shelfID, bookID, bookName, author, genre, quantity, type);
                found = 1;
            }
        }
        if (!found) {
            printf("No %s found in the book.txt\n", shelf_id);
        }
        printf("Do you want to list another shelf? (y/n): ");
        getchar();  // Clear newline from buffer
        scanf("%c", &continue_choice);
    }while (continue_choice == 'y' || continue_choice == 'Y');
    
    fclose(file);
}


void update_shelf(void) {
    char line[256];
    char book_id[256];
    char shelf_id[256];
    int found = 0;
    int bookFound = 0;
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
            char shelfID[50], bookID[50], bookName[256], author[256], genre[256], quantity[256], type[256];
            sscanf(line, "%49[^,],%49[^,],%255[^,],%255[^,],%255[^,],%49[^,],%255[^\n]",
                   shelfID, bookID, bookName, author, genre, quantity, type);
            
            if (strcmp(type, "Physical") == 0) {
                printf("%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n", shelfID, bookID, bookName, author, genre, quantity, type);
            }
            found = 1;
        }
        
        if (!found) {
            printf("No books found.\n");
            fclose(file);
            return;
        }
        
        printf("Enter Book ID to update placement: ");
        scanf("%s", book_id);
        
        rewind(file);
        
        while (fgets(line, sizeof(line), file)) {
            char shelfID[50], bookID[50], bookName[256], author[256], genre[256], quantity[256], type[256];
            sscanf(line, "%49[^,],%49[^,],%255[^,],%255[^,],%255[^,],%49[^,],%255[^\n]",
                   shelfID, bookID, bookName, author, genre, quantity, type);
            
            if (strcmp(book_id, bookID) == 0) {
                // Book found; prompt for a shelf ID or to remove
                do {
                    printf("Enter Shelf ID for Book %s: ", book_id);
                    scanf("%s", shelf_id);
                    
                    if (strcmp(shelf_id, "-") == 0) {
                        // If removing, skip uniqueness check
                        break;
                    }
                    
                    // No uniqueness check here anymore
                    
                    break;
                    
                } while (1);
                
                bookFound = 1;
                break;
            }
        }
        
        if (!bookFound) {
            printf("Book ID %s not found.\n", book_id);
            fclose(file);
            return;
        }
        
        FILE *loadFile = fopen("load.txt", "w");
        if (loadFile == NULL) {
            printf("Error opening load file.\n");
            fclose(file);
            return;
        }
        
        // Write the updated file with the new shelf ID for the selected book
        rewind(file);  // Return to the start of book.txt to copy contents
        while (fgets(line, sizeof(line), file)) {
            char shelfID[50], bookID[50], bookName[256], author[256], genre[256], quantity[256], type[256];
            sscanf(line, "%49[^,],%49[^,],%255[^,],%255[^,],%255[^,],%49[^,],%255[^\n]",
                   shelfID, bookID, bookName, author, genre, quantity, type);
            
            if (strcmp(book_id, bookID) == 0) {
                fprintf(loadFile, "%s,%s,%s,%s,%s,%s,%s\n", shelf_id, bookID, bookName, author, genre, quantity, type);
            } else {
                fprintf(loadFile, "%s", line);
            }
        }
        
        fclose(file);
        fclose(loadFile);
        
        remove("book.txt");
        rename("load.txt", "book.txt");
        
        if (strcmp(shelf_id, "-") == 0) {
            printf("Book %s has been removed from the shelf.\n", book_id);
        } else {
            printf("Book %s has been placed on Shelf ID %s.\n", book_id, shelf_id);
        }
        
        printf("Do you want to place another book? (y/n): ");
        getchar();
        scanf("%c", &continue_choice);
    } while (continue_choice == 'Y' || continue_choice == 'y');
}




// Function to display the Digital Resource Assistance Menu
void digital_page(void){
    printf("-----------------------------------\n");
    printf("Welcome to Digital Resource Assistance Page\n");
    printf("1. E-Books\n");
    printf("2. Online Journals\n");
    printf("3. Audiobooks\n");
    printf("4. Back to Home Page\n");
    printf("-----------------------------------\n");
}

// Function to get the user's choice from the Digital Resource Assistance Menu
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
    char line[256];
    
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
        
        if (strcmp(type, "Ebook") == 0) {
            printf("%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                   shelfID, bookID, bookName, author, genre, quantity, type);
        }
    }
    fclose(file);
}
    
void online_journals(void) {
    char line[256];
    
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
        
        if (strcmp(type, "Online Journal") == 0) {
            printf("%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                   shelfID, bookID, bookName, author, genre, quantity, type);
        }
    }
    fclose(file);
}

void audiobooks(void){
    char line[256];
    
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
        
        if (strcmp(type, "AudioBook") == 0) {
            printf("%-10s %-10s %-30s %-30s %-20s %-10s %-20s\n",
                   shelfID, bookID, bookName, author, genre, quantity, type);
        }
    }
    fclose(file);
}

// Main function
int main(void) {
    int choice;
    char username[50];

    if (login(username)) {  // Login successful
        while (1) {
            main_menu(username);
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
                    printf("Exiting the program. Goodbye!\n");
                    return 0;
                default:
                    printf("Error: Invalid option.\n");
                    break;
            }
        }
    } else {
        printf("Login failed. Exiting program.\n");
    }
    return 0;
}



