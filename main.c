#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct user_info {
    char name[50];
    char account_num[25];
    char password[25];
    char mobile[20];
    float balance;
};

void rem_leftover_inp() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct user_info user_id;
    char filename[30], phone[20], password[25];
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
        system("cls || clear"); 
        srand((unsigned int)time(0));
        int random_number = 100000000 + rand() % 900000000;
        snprintf(user_id.account_num, sizeof(user_id.account_num), "%d", random_number);

        rem_leftover_inp(); 

        printf("Enter your name: ");
        fgets(user_id.name, sizeof(user_id.name), stdin);
        user_id.name[strcspn(user_id.name, "\n")] = '\0';

        printf("Enter your phone number: ");
        fgets(user_id.mobile, sizeof(user_id.mobile), stdin);
        user_id.mobile[strcspn(user_id.mobile, "\n")] = '\0';


        rem_leftover_inp();

        printf("Create a new password: ");
        fgets(user_id.password, sizeof(user_id.password), stdin);
        user_id.password[strcspn(user_id.password, "\n")] = '\0';

        user_id.balance = 0;

        strcpy(filename, user_id.mobile);
        strcat(filename, ".dat");

        file = fopen(filename, "wb");
        if (file == NULL) {
            printf("Error creating account file.\n");
            return 1;
        }

        if (fwrite(&user_id, sizeof(struct user_info), 1, file) == 1) {
            printf("\nYour account has been registered successfully!\n");
            printf("Account number: %s\n", user_id.account_num);
            printf("Current balance: %.2f\n", user_id.balance);
        } else {
            printf("An error occurred. Please try again.\n");
        }

        fclose(file);

    } else if (option == 2) {
        system("cls || clear");

        rem_leftover_inp();

        printf("Enter your phone number: ");
        fgets(phone, sizeof(phone), stdin);
        phone[strcspn(phone, "\n")] = '\0';

        printf("Enter your password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        strcpy(filename, phone);
        strcat(filename, ".dat");

        file = fopen(filename, "rb");
        if (file == NULL) {
            printf("Account not found.\n");
            return 1;
        }

        fread(&user_id, sizeof(struct user_info), 1, file);
        fclose(file);

        while (strcmp(password, user_id.password) != 0) {
            printf("Invalid password. Try again: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = '\0';
        }

        while (cont == 'y' || cont == 'Y') {
            system("cls || clear");
            printf("\nWelcome, %s\n", user_id.name);
            printf("1. Balance inquiry\n");
            printf("2. Add funds\n");
            printf("3. Withdraw cash\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Current balance: Rs. %.2f\n", user_id.balance);
                    break;

                case 2:
                    printf("Enter amount to deposit: ");
                    scanf("%f", &amount);
                    user_id.balance += amount;
                    file = fopen(filename, "wb");
                    if (file != NULL) {
                        fwrite(&user_id, sizeof(struct user_info), 1, file);
                        fclose(file);
                        printf("Deposit successful. New balance: Rs. %.2f\n", user_id.balance);
                    } else {
                        printf("Failed to update balance.\n");
                    }
                    break;

                case 3:
                    printf("Enter amount to withdraw: ");
                    scanf("%f", &amount);
                    if (amount <= 0) {
                        printf("Invalid amount!\n");
                    } else if (amount > user_id.balance) {
                        printf("Insufficient balance! Your balance is Rs. %.2f\n", user_id.balance);
                    } else {
                        user_id.balance -= amount;
                        file = fopen(filename, "wb");
                        if (file != NULL) {
                            fwrite(&user_id, sizeof(struct user_info), 1, file);
                            fclose(file);
                            printf("Withdrawal successful. New balance: Rs. %.2f\n", user_id.balance);
                        } else {
                            printf("Transaction failed!\n");
                        }
                    }
                    break;

                default:
                    printf("Invalid option.\n");
                    break;
            }

            rem_leftover_inp(); 
            printf("\nDo you want to continue? [y/n]: ");
            scanf(" %c", &cont);
        }

        printf("You have exited your account.\n");

    } else {
        printf("Bank account management system exited.\n");
    }

    return 0;
}
