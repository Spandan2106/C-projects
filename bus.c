// c code for bus reservation system
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct bus {
    int bus_no;
    char bus_name[20];
    char source[20];
    char destination[20];
    int seats;
};
struct bus b[10];
int count = 0;
void add_bus() {
    if (count < 10) {
        printf("Enter bus number: ");
        scanf("%d", &b[count].bus_no);
        printf("Enter bus name: ");
        scanf("%s", b[count].bus_name);
        printf("Enter source: ");
        scanf("%s", b[count].source);
        printf("Enter destination: ");
        scanf("%s", b[count].destination);
        printf("Enter number of seats: ");
        scanf("%d", &b[count].seats);
        count++;
    } else {
        printf("Bus list is full.\n");
    }
}
void display_buses() {
    if (count == 0) {
        printf("No buses available.\n");
    } else {
        printf("Available Buses:\n");
        printf("-----------------\n");
        printf("Bus No \t Bus Name \t Source \tDestination \t Seats\n\n");
        printf("-----------------------------------------------------------------------------\n");
        for (int i = 0; i < count; i++) {
            printf("%d  \t  %s\t    %s\t      %s\t      %d\n", b[i].bus_no, b[i].bus_name, b[i].source, b[i].destination, b[i].seats);
        }
    }
}
void book_ticket() {
    int bus_no, seats;
    printf("Enter bus number: ");
    scanf("%d", &bus_no);
    for (int i = 0; i < count; i++) {
        if (b[i].bus_no == bus_no) {
            printf("Enter number of seats to book: ");
            scanf("%d", &seats);
            if (seats <= b[i].seats) {
                b[i].seats -= seats;
                printf("Ticket booked successfully.\n");
                printf("Seats booked: %d\n", seats);
                printf("Seats remaining: %d\n", b[i].seats);
                printf("Thank you for using our bus reservation system.\n");
            } else {
                printf("Not enough seats available.\n");
                printf("Available seats: %d\n", b[i].seats);
                printf("Booking failed.\n");
                printf("Please try booking with fewer seats.\n");
                printf("Thank you for using our bus reservation system.\n");
            }
            return;
        }
    }
    printf("Bus not found.\n");
    printf("Please check the bus number and try again.\n");
    printf("Thank you for using our bus reservation system.\n");
}
void cancel_ticket() {
    int bus_no, seats;
    printf("Enter bus number: ");
    scanf("%d", &bus_no);
    for (int i = 0; i < count; i++) {
        if (b[i].bus_no == bus_no) {
            printf("Enter number of seats to cancel: ");
            scanf("%d", &seats);
            b[i].seats += seats;
            printf("Ticket cancelled successfully.\n");
            printf("Seats cancelled: %d\n", seats);
            printf("Seats available now: %d\n", b[i].seats);
            printf("Thank you for using our bus reservation system.\n");
            return;
        }
    }
    printf("Bus not found.\n");
    printf("Please check the bus number and try again.\n");
    printf("Thank you for using our bus reservation system.\n");
}
void search_bus() {
    int bus_no;
    printf("Enter bus number to search: ");
    scanf("%d", &bus_no);
    for (int i = 0; i < count; i++) {
        if (b[i].bus_no == bus_no) {
            printf("Bus No: %d\n", b[i].bus_no);
            printf("Bus Name: %s\n", b[i].bus_name);
            printf("Source: %s\n", b[i].source);
            printf("Destination: %s\n", b[i].destination);
            printf("Available Seats: %d\n", b[i].seats);
            return;
        }
    }
    printf("Bus not found.\n");
    printf("Please check the bus number and try again.\n");
    printf("Thank you for using our bus reservation system.\n");
}
void menu() {
    printf("\nBus Reservation System\n");
    printf("1. Add Bus\n");
    printf("2. Display Buses\n");
    printf("3. Book Ticket\n");
    printf("4. Cancel Ticket\n");
    printf("5. Search Bus\n");
    printf("6. Exit\n");
}
int main() {
    int choice;
    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_bus();
                break;
            case 2:
                display_buses();
                break;
            case 3:
                book_ticket();
                break;
            case 4:
                cancel_ticket();
                break;
            case 5:
                search_bus();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

