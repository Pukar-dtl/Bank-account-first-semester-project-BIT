#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct user_info{
    char name[20];
    char account_num[25];
    char password[20];
    char mobile[20];
    float balance;
};

int main() {
    struct user_info user_id;
    char filename[30], phone[10], password[15];
    int option = 4 ;
    float amount = 0;
    int choice;
    char cont= 'y';
    FILE *file;

    printf("Enter your choice: \n");
    printf("\n1.Register an account: ");
    printf("\n2.Login into your account: ");
    printf("\n3.Exit: ");

    while(option>3 || option<=0){
        printf("\nEnter a option: ");
        scanf("%d", &option);
        if(option>3 || option<=0){
            printf("Please enter a correct option: ");
        }
    }

    if(option==1) {
        system("cls");
        srand(time(0));
        int random_number = 100000000 + rand() % 900000000;
        itoa(random_number, user_id.account_num, 15);

        puts("Enter your name: ");
        scanf("%s", &user_id.name);

        puts("Enter your phone number: ");
        scanf("%s", &user_id.mobile);

        puts("Create a new password : ");
        scanf("%s", &user_id.password);

        user_id.balance = 0;
        strcpy(filename, user_id.mobile);
        file = fopen(strcat(filename, ".dat"), "w");
        fwrite(&user_id, sizeof(struct user_info), 1, file);

        if (fwrite > 0) {
            printf("Your account has been registered successfully: \n");
            printf("Your account number is: %s\n", user_id.account_num);
            printf("Your balance is currently: %.2f", user_id.balance);
        } else
            printf("An error occurred, please try again: ");
        fclose(file);


    }else if(option == 2) {
        system("cls");
        puts("Enter your phone number: ");
        scanf("%s", &phone);
        puts("enter your password: ");
        scanf("%s", &password);
        strcpy(filename, phone);
        file = fopen(strcat(filename, ".dat"), "r");
        if (file == NULL) {
            puts("Account number not registered: ");
        } else {
            fread(&user_id, sizeof(struct user_info), 1, file);
            fclose(file);

            while (strcmp(password, user_id.password) != 0) {
                puts("enter your password: ");
                scanf("%s", &password);
                puts("Invalid password");
            }
            if (!strcmp(password, user_id.password)) {
                puts("Correct password");
            }
            while (cont == 'y') {
                system("cls");
                printf("\n\tWelcome %s\n", user_id.name);
                puts("Press 1 for balance inquiry");
                puts("Press 2 for adding fund");
                puts("Press 3 for cash withdraw");
                scanf("%d", &choice);
                switch(choice){
                    case 1:
                        printf("Your current balance is Rs. %.2f",user_id.balance);
                        break;
                    case 2:
                        puts("Enter the amount: ");
                        scanf("%f", &amount);
                        user_id.balance +=amount;
                        file = fopen(filename, "w");
                        fwrite(&user_id,sizeof(struct user_info), 1, file);
                        if(fwrite !=NULL)
                            printf("Deposition successful..");
                        fclose(file);
                        break;
                    case 3:
                        puts("Enter the amount: ");
                        scanf("%f", &amount);
                        user_id.balance -=amount;
                        file = fopen(filename, "w");
                        fwrite(&user_id,sizeof(struct user_info), 1, file);
                        if(fwrite !=NULL)
                            printf("Deposition successful..");
                        fclose(file);
                        break;
                    default:
                        puts("Invalid option");
                }
                printf("Do you want to continue? [y/n]");
                scanf("%c", &cont);
            }

        }
    } else
        printf("Bank account management system has been exited successfully");
    return 0;
}