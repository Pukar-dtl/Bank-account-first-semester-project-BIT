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
    float amount = 0;
    int option;
    FILE *file;
    char cont;

    while (1) {
        system("cls || clear");
        printf("==== Bank Account Management System ====\n");
        printf("1. Register an account\n");
        printf("2. Login into your account\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        rem_leftover_inp();

        if (option == 1) {
            system("cls || clear");
            printf("=== Register Account ===\n");

            printf("Enter your phone number: ");
            fgets(user_id.mobile, sizeof(user_id.mobile), stdin);
            user_id.mobile[strcspn(user_id.mobile, "\n")] = '\0';

            strcpy(filename, user_id.mobile);
            strcat(filename, ".dat");

            file = fopen(filename, "rb");
            if (file != NULL) {
                printf("An account with this phone number already exists.\n");
                fclose(file);
                printf("Press Enter to continue...");
                getchar();
                continue;
            }

            printf("Enter your name: ");
            fgets(user_id.name, sizeof(user_id.name), stdin);
            user_id.name[strcspn(user_id.name, "\n")] = '\0';

            printf("Create a password: ");
            fgets(user_id.password, sizeof(user_id.password), stdin);
            user_id.password[strcspn(user_id.password, "\n")] = '\0';

            user_id.balance = 0;
            srand((unsigned int)time(0));
            int random_number = 100000000 + rand() % 900000000;
            snprintf(user_id.account_num, sizeof(user_id.account_num), "%d", random_number);

            file = fopen(filename, "wb");
            if (file == NULL) {
                printf("Error creating account file.\n");
                continue;
            }

            fwrite(&user_id, sizeof(struct user_info), 1, file);
            fclose(file);

            printf("\nAccount registered successfully!\n");
            printf("Account number: %s\n", user_id.account_num);
            printf("Current balance: Rs. %.2f\n", user_id.balance);
            printf("Press Enter to continue...");
            getchar();

        } else if (option == 2) {
            // Login
            system("cls || clear");
            printf("=== Login ===\n");

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
                printf("Press Enter to continue...");
                getchar();
                continue;
            }

            fread(&user_id, sizeof(struct user_info), 1, file);
            fclose(file);

            if (strcmp(password, user_id.password) != 0) {
                printf("Incorrect password.\n");
                printf("Press Enter to continue...");
                getchar();
                continue;
            }

            cont = 'y';
            while (cont == 'y' || cont == 'Y') {
                system("cls || clear");
                printf("\nWelcome, %s\n", user_id.name);
                printf("1. Balance Inquiry\n");
                printf("2. Add Funds\n");
                printf("3. Withdraw Cash\n");
                printf("4. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &option);
                rem_leftover_inp();

                switch (option) {
                    case 1:
                        printf("Current balance: Rs. %.2f\n", user_id.balance);
                        break;

                    case 2:
                        printf("Enter amount to deposit: ");
                        scanf("%f", &amount);
                        rem_leftover_inp();
                        if (amount > 0) {
                            user_id.balance += amount;
                            file = fopen(filename, "wb");
                            fwrite(&user_id, sizeof(struct user_info), 1, file);
                            fclose(file);
                            printf("Deposit successful. New balance: Rs. %.2f\n", user_id.balance);
                        } else {
                            printf("Invalid deposit amount.\n");
                        }
                        break;

                    case 3:
                        printf("Enter amount to withdraw: ");
                        scanf("%f", &amount);
                        rem_leftover_inp();
                        if (amount <= 0) {
                            printf("Invalid amount.\n");
                        } else if (amount > user_id.balance) {
                            printf("Insufficient balance! Current balance: Rs. %.2f\n", user_id.balance);
                        } else {
                            user_id.balance -= amount;
                            file = fopen(filename, "wb");
                            fwrite(&user_id, sizeof(struct user_info), 1, file);
                            fclose(file);
                            printf("Withdrawal successful. New balance: Rs. %.2f\n", user_id.balance);
                        }
                        break;

                    case 4:
                        cont = 'n';
                        printf("Logging out...\n");
                        break;

                    default:
                        printf("Invalid option.\n");
                }

                if (cont == 'y' || cont == 'Y') {
                    printf("\nDo you want to continue in your account? (y/n): ");
                    scanf(" %c", &cont);
                    rem_leftover_inp();
                }
            }

        } else if (option == 3) {
            printf("Thank you for using the system.\n");
            break;
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}