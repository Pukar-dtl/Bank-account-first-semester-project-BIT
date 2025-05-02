#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct user_info {
    char name[20];
    char account_num[25];
    char password[20];
    char mobile[20];
    float balance;
};

int main() {
    struct user_info user_id;
    char filename[30], phone[20], password[20];
    int option = 4;
    float amount = 0;
    int choice;
    char cont = 'y';
    FILE *file;

    printf("Enter your choice:\n");
    printf("1. Register an account\n");
    printf("2. Login into your account\n");
    printf("3. Exit\n");

    while (option > 3 || option <= 0) {
        printf("Enter an option: ");
        scanf("%d", &option);
        if (option > 3 || option <= 0) {
            printf("Please enter a correct option.\n");
        }
    }

    if (option == 1) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        srand(time(0));
        int random_number = 100000000 + rand() % 900000000;
        sprintf(user_id.account_num, "%d", random_number);

        printf("Enter your name: ");
        scanf("%s", user_id.name);

        printf("Enter your phone number: ");
        scanf("%s", user_id.mobile);

        printf("Create a new password: ");
        scanf("%s", user_id.password);

        user_id.balance = 0.0;

        strcpy(filename, user_id.mobile);
        strcat(filename, ".dat");

        file = fopen(filename, "wb");
        if (file != NULL && fwrite(&user_id, sizeof(struct user_info), 1, file) > 0) {
            printf("\nYour account has been registered successfully.\n");
            printf("Your account number is: %s\n", user_id.account_num);
            printf("Your balance is currently: %.2f\n", user_id.balance);
        } else {
            printf("An error occurred. Please try again.\n");
        }
        fclose(file);
    }

    else if (option == 2) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("Enter your phone number: ");
        scanf("%s", phone);
        printf("Enter your password: ");
        scanf("%s", password);

        strcpy(filename, phone);
        strcat(filename, ".dat");

        file = fopen(filename, "rb");
        if (file == NULL) {
            printf("Account number not registered.\n");
        } else {
            fread(&user_id, sizeof(struct user_info), 1, file);
            fclose(file);

            while (strcmp(password, user_id.password) != 0) {
                printf("Invalid password. Try again: ");
                scanf("%s", password);
            }
            printf("Correct password.\n");

            while (cont == 'y' || cont == 'Y') {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif

                printf("\n\tWelcome %s\n", user_id.name);
                printf("Press 1 for balance inquiry\n");
                printf("Press 2 for adding funds\n");
                printf("Press 3 for cash withdrawal\n");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        printf("Your current balance is Rs. %.2f\n", user_id.balance);
                        break;

                    case 2:
                        printf("Enter the amount: ");
                        scanf("%f", &amount);
                        user_id.balance += amount;
                        file = fopen(filename, "wb");
                        if (file != NULL && fwrite(&user_id, sizeof(struct user_info), 1, file) > 0) {
                            printf("Deposition successful. Your balance is now Rs. %.2f\n", user_id.balance);
                        } else {
                            printf("Failed to update balance.\n");
                        }
                        fclose(file);
                        break;

                    case 3:
                        printf("Enter the amount: ");
                        scanf("%f", &amount);
                        if (amount > user_id.balance) {
                            printf("Insufficient Balance! Your current balance is Rs. %.2f\n", user_id.balance);
                        } else if (amount <= 0) {
                            printf("Invalid amount! Please enter a valid amount.\n");
                        } else {
                            user_id.balance -= amount;
                            file = fopen(filename, "wb");
                            if (file != NULL && fwrite(&user_id, sizeof(struct user_info), 1, file) > 0) {
                                printf("Withdrawal successful! Your new balance is Rs. %.2f\n", user_id.balance);
                            } else {
                                printf("Transaction failed! Please try again.\n");
                            }
                            fclose(file);
                        }
                        break;

                    default:
                        printf("Invalid option.\n");
                        break;
                }

                printf("Do you want to continue? [y/n]: ");
                scanf(" %c", &cont);
            }

            printf("Bank account management system has been exited successfully.\n");
        }
    }

    else {
        printf("Bank account management system has been exited successfully.\n");
    }

    return 0;
}
