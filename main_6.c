#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#define SIZE_n 50  // size of name array
#define SIZE_e  50//size of email array
#define SIZE_d  20 //size of dob array
#define SIZE_m  20  //size of mobile number array
#define SIZE_p  20  //size of password array
#define SIZE_a  10 //size of account


// define a struct to hold user details
struct user {
    char name[SIZE_n];
    char email[SIZE_e];
    char dob[SIZE_d];
    char mobile[SIZE_m];
    char password[SIZE_p];
    char account[SIZE_a];
    double balance;
};

// function to generate a random account address
void generate_account_address(char *account) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 9; i++) {
        account[i] = alphanum[1+rand() % (sizeof(alphanum)-1)];
    }
    account[9] = '\0';
}

// function to print user details
void print_user_details(struct user u) {
    printf("Hi %s,\n", u.name);
    printf("Your account address is: %s\n", u.account);
    printf("Your details are:\n");
    printf("Name: %s\n", u.name);
    printf("Email: %s\n", u.email);
    printf("Date of birth: %s\n", u.dob);
    printf("Mobile: %s\n", u.mobile);
    printf("Password: %s\n", u.password);
    printf("Balance: %.2lf\n", u.balance);
}

// function to store user details in a text file
int store_user_details(struct user u) {
    FILE *fptr;
    fptr = fopen("user_details.txt", "r");
    if (fptr == NULL) {
        printf("Error: could not open file for reading.\n");
        exit(1);
    }
    char line[200];
    while (fgets(line, sizeof(line), fptr)) {
        char *token;
        token = strtok(line, ",");
        if (strcmp(u.email, token) == 0) {
            fclose(fptr);
            printf("Error: email address already exists. Please use a different email address.\n");
            return 0;
        }
    }
    fclose(fptr);

    fptr = fopen("user_details.txt", "a");
    if (fptr == NULL) {
        printf("Error: could not open file for writing.\n");
        exit(1);
    }
    fprintf(fptr, "%s,%s,%s,%s,%s,%s,%.2lf\n", u.name, u.email, u.dob, u.mobile, u.password, u.account, u.balance);
    fclose(fptr);
    return 1;
}

// function to read user details from the text file
int read_user_details(char *email, char *password, struct user *u) {
    FILE *fptr;
    fptr = fopen("user_details.txt", "r");
    if (fptr == NULL) {
        printf("Error: could not open file for reading.\n");
        exit(1);
    }
    char line[200];
    while (fgets(line, sizeof(line), fptr)) {
        char *token;
        token = strtok(line, ",");
        if (strcmp(email, token) == 0) {
            token = strtok(NULL, ",");
            if (strcmp(password, token) == 0) {
                strcpy(u->name, strtok(NULL, ","));
                strcpy(u->dob, strtok(NULL, ","));
                strcpy(u->mobile, strtok(NULL, ","));
                strcpy(u->password, password);
                strcpy(u->account, strtok(NULL, ","));
                u->balance = atof(strtok(NULL, ","));
                fclose(fptr);
                return 1;
            }
        }
    }
    fclose(fptr);
    return 0;
}
// function to check if user exists in the text file
int check_user_exists(char *email) {
    FILE *fptr;
    fptr = fopen("user_details.txt", "r");
    if (fptr == NULL) {
        printf("Error: could not open file for reading.\n");
        exit(1);
    }
    char line[200];
    while (fgets(line, sizeof(line), fptr)) {
        char *token;
        token = strtok(line, ",");
        if (strcmp(email, token) == 0) {
            fclose(fptr);
            return 1;
        }
    }
    fclose(fptr);
    return 0;
}

int main() {
    int is_new;
    printf("Are you a new user? Enter 1 for yes, 0 for no: ");
    scanf("%d", &is_new);
  

    struct user u;

    if (is_new) {
        printf("Enter your name: ");
        scanf("%s", u.name);
        printf("Enter your email: ");
        scanf("%s", u.email);
        printf("Enter your date of birth (dd/mm/yyyy): ");
        scanf("%s", u.dob);
        printf("Enter your mobile number: ");
        scanf("%s", u.mobile);
        printf("Enter your desired password: ");
        scanf("%s", u.password);
        u.balance = 0.0;
        generate_account_address(u.account);
        printf("\nYour account has been created successfully!\n");
        print_user_details(u);
        store_user_details(u);
    } 
    else {
        char email[50], password[20];
        printf("Enter your email: ");
        scanf("%s", email);
        printf("Enter your password: ");
        scanf("%s", password);
        if (read_user_details(email, password, &u)) {
            printf("\nLogin successful!\n");
            print_user_details(u);

// shows account details to the user
           // show account details to the user
    char account_filename[100];
    sprintf(account_filename, "%s_details.txt", u.account);
    char data[200];
    sprintf(data, "Name: %s\nEmail: %s\nDate of birth: %s\nMobile: %s\nBalance: %.2lf\n", u.name, u.email, u.dob, u.mobile, u.balance);
    save_file(account_filename, data);
    printf("\nYour account details have been saved to %s.\n", account_filename);
} 
 
        else {
            printf("\nInvalid email or password. Please try again.\n");
        }
    }

    return 0;
}
  