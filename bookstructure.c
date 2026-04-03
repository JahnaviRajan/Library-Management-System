#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Books {
    int id;
    char title[50];
    char author[50];
    int isIssued;
};

void addBook(){
    struct Books newBook;
    FILE *file = fopen("library.dat", "ab");
    printf("Enter Book ID:");
    scanf("%d", &newBook.id);
    getchar();
    printf("Enter Book title:");
    fgets(newBook.title, 50, stdin);
    printf("Enter author name:");
    fgets(newBook.author, 50, stdin);
    newBook.isIssued = 0;

    fwrite(&newBook, sizeof(struct Books), 1, file);
    fclose(file);

    printf("Book has been added successfully!\n");
}

void displayBooks(){
    struct Books book;
    FILE *file = fopen("library.dat", "rb");
    

    while(fread(&book, sizeof(struct Books), 1, file)){
        printf("ID:%d\nTitle:%s\nAuthor:%s\nStatus:%s\n\n", book.id, book.title, book.author, book.isIssued ? "Issued" : "Available");
    }
    fclose(file);
}

void issueBook(){
    struct Books book;
    int bookID, found = 0;
    FILE *file = fopen("library.dat", "rb+");
    printf("Enter Book ID to issue:");
    scanf("%d", &bookID);

    while(fread(&book, sizeof(struct Books),1, file )){
        if(book.id == bookID && book.isIssued == 0){
            book.isIssued = 1;
            fseek(file, -sizeof(struct Books), SEEK_CUR);
            fwrite(&book, sizeof(struct Books), 1, file);
            printf("Book issued successfully!\n");
            found = 1;
            break;


        }
    }
    if(!found){
        printf("Book already issued or not found\n");

    }
    fclose(file);
}
void returnBook(){
    struct Books book;
    int bookID, found = 0;
    FILE *file = fopen("library.dat", "rb+");
    printf("Enter book ID to return:");
    scanf("%d", &bookID);

    while(fread(&book, sizeof(struct Books),1,file)){
        if(book.id == bookID && book.isIssued == 1){
           book.isIssued=0;
        fseek(file, -sizeof(struct Books), SEEK_CUR);
        fwrite(&book, sizeof(struct Books), 1, file);
        printf("Book returned successfully\n");
        found =1;
        break;
    }
    }
    if(!found){
        printf("Book ID is invalid or book is not issued\n");

    }
    fclose(file);
}

int main(){
    int choice;
    while(1){
        printf("Library Management System\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Exit\n");
        printf("Enter your choice:");
        scanf("%d", &choice);


        switch(choice){
            case 1:
            addBook();
            break;

            case 2:
            displayBooks();
            break;

            case 3:
            issueBook();
            break;

            case 4:
            returnBook();
            break;

            case 5:
            exit(0);
            
            default:
            printf("Invalid choice entered");
        }
    }
    return 0;
}