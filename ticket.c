#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct book {
    char code[20];
    char name[20];
    char date[20];
    int cost;
} b;

int seat = 60;

void insert_details();   // for inserting movie details
void viewAll();          // for viewing all data
void find();             // for finding data
void book_ticket();      // for booking tickets
void old_record();       // for viewing old records of users, booked tickets

int main() {
    int ch;
    do {
        printf("\n====================================================================");
        printf("\n");
        printf("\t Movie Ticket Booking ");
        printf("\n");
        printf("\n====================================================================");

        printf("\nPress <1> Insert Movie");
        printf("\nPress <2> View All Movies");
        printf("\nPress <3> Find Movie");
        printf("\nPress <4> Book Ticket");
        printf("\nPress <5> View All Transactions");
        printf("\nPress <0> Exit");

        printf("\nEnter your Choice: ");
        scanf("%d", &ch);
        fflush(stdin);

        switch (ch) {
            case 1:
                insert_details();
                break;
            case 2:
                viewAll();
                break;
            case 3:
                find();
                break;
            case 4:
                book_ticket();
                break;
            case 5:
                old_record();
                break;
            case 0:
                exit(0);
            default:
                printf("Wrong choice! Please try again.\n");
                break;
        }
    } while (ch != 0);
}

void insert_details() {
    FILE *fp;
    printf("Enter movie code: ");
    scanf("%s", b.code);
    printf("Enter movie name: ");
    scanf("%s", b.name);
    printf("Enter release date: ");
    scanf("%s", b.date);
    printf("Enter ticket price: ");
    scanf("%d", &b.cost);

    fp = fopen("data.txt", "a");
    if (fp == NULL) {
        printf("File not found!\n");
    } else {
        fprintf(fp, "%s %s %s %d\n", b.code, b.name, b.date, b.cost);
        printf("Record inserted successfully.\n");
    }
    fclose(fp);
}

void viewAll() {
    char ch;
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("File not found!\n");
    } else {
        printf("\nList of Movies:\n");
        while ((ch = fgetc(fp)) != EOF) {
            putchar(ch);
        }
    }
    fclose(fp);
}

void find() {
    FILE *fp;
    char ch[20];
    printf("Enter movie code: ");
    scanf("%s", ch);

    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    int found = 0;
    while (fscanf(fp, "%s %s %s %d", b.code, b.name, b.date, &b.cost) != EOF) {
        if (strcmp(b.code, ch) == 0) {
            printf("\nRecord Found\n");
            printf("\tCode: %s\n", b.code);
            printf("\tMovie Name: %s\n", b.name);
            printf("\tRelease Date: %s\n", b.date);
            printf("\tTicket Price: %d\n", b.cost);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No record found with the given movie code.\n");
    }
    fclose(fp);
}

void book_ticket() {
    FILE *fp;
    FILE *ufp;

    int total_seat, mobile, total_amount;
    char name[20];
    char movie_code[20];

    viewAll();

    printf("\nEnter movie code: ");
    scanf("%s", movie_code);

    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    int found = 0;
    while (fscanf(fp, "%s %s %s %d", b.code, b.name, b.date, &b.cost) != EOF) {
        if (strcmp(b.code, movie_code) == 0) {
            printf("\nRecord Found\n");
            printf("\tCode: %s\n", b.code);
            printf("\tMovie Name: %s\n", b.name);
            printf("\tRelease Date: %s\n", b.date);
            printf("\tTicket Price: %d\n", b.cost);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("Invalid movie code. Booking aborted.\n");
        return;
    }

    printf("\nEnter your name: ");
    scanf("%s", name);
    printf("Enter mobile number: ");
    scanf("%d", &mobile);
    printf("Enter total number of tickets: ");
    scanf("%d", &total_seat);

    total_amount = b.cost * total_seat;

    printf("\n***** ENJOY MOVIE *****\n");
    printf("\tName: %s\n", name);
    printf("\tMobile: %d\n", mobile);
    printf("\tMovie: %s\n", b.name);
    printf("\tTotal Tickets: %d\n", total_seat);
    printf("\tCost per Ticket: %d\n", b.cost);
    printf("\tTotal Amount: %d\n", total_amount);

    ufp = fopen("oldTransaction.txt", "a");
    if (ufp == NULL) {
        printf("File not found!\n");
    } else {
        fprintf(ufp, "%s %d %d %d %s %d\n", name, mobile, total_seat, total_amount, b.name, b.cost);
        printf("Record inserted successfully into the transaction file.\n");
    }
    fclose(ufp);
}

void old_record() {
    char ch;
    FILE *fp = fopen("oldTransaction.txt", "r");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("\nAll Transactions:\n");
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
}
