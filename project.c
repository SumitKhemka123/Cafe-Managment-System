#include <stdio.h>
#include <stdlib.h> //file handling
#include <string.h> //string functions
#include <unistd.h> //for sleep()

struct menu{
    int id;
    char name[100];
    int price;
};

struct details{
    int custNo;
    char name[100];
    char pass[100];
    char mobile[10];
    char address[100];
    int buycnt;             /*  buycnt = total number of items bought by the customer till now */
    int prevOrder[100]; /*  prevOrder = array for storing item id of order history of the customer */
    int prevOrderqty[100] ; /* prevOrderqty = array for storing qty of order history */
    };


int totalItem;            /* Variable for storing total Items in the menu */
int totalCust;            /* Variable for storing total number of customer served */

char admin[] = "jiit";          /* Admin login username */
char passadmin[] = "9876";      /*Password for admin */

void order_main(struct details d);
void signUp();
void delete_cust();
void delete_menu();
void aboutMe();
void addMenu();
void loadData();
void start();
void adminlogin();
void update(struct details cust);
void createFile();
void customerInfo();
int login();
int isDouble(char name[30]);


/*-> This function creates and intitialzes initial data if it didn't existed previoously -< */


void createFile(){      /* -> Creating the file and inputing sample data if it already didn't existed <- */

    /* Checking if file exists or not */

    FILE *fread;

    fread = fopen("menu.txt" , "r");
    if(fread== NULL){

            /* Creating file because it didn't existed */

            FILE *file;
            fclose(fread);
            file = fopen ("menu.txt", "w");
            if (file == NULL)
                {
                printf("\nError while opening file\n");
                exit (1);
                }

             /* -> Adding initial data in menu file <- */
            struct menu f1 = {1, "Samosa" , 10}; /* sample data of customer adding in file using structure */
            struct menu f2 = {2 , "Pizza" , 80};
            struct menu f3 = {3 , "Dosa" , 60};
            struct menu f4 = {4 , "Chai" , 10};
            fwrite (&f1, sizeof(struct menu), 1, file);
            fwrite (&f2, sizeof(struct menu), 1, file);
            fwrite (&f3, sizeof(struct menu), 1, file);
            fwrite (&f4, sizeof(struct menu), 1, file);
            if(fwrite != 0)
                printf("\nSuccessfully initialized menu!!\n");
            else
                printf("Error while initializing the menu!\n");
            fclose (file);

    }

    FILE *fileread2;
    fileread2 = fopen("details.txt" , "r");
    if(fileread2 == NULL){

        /* -> Adding initial data in customer file <- */




            FILE *file2;
            fclose(fileread2);
            struct details d1 = {1 , "ayush" , "a123" , "9929419734" , "JIIT 62" , 1 , {1} , {1}}; /*sample data of customer adding in file using structure*/
            struct details d2 = {2, "sumit", "1234", "9120805960","JIIT Hostel" ,  1, {2} , {3}};
            file2 = fopen ("details.txt", "w");
            if (file2 == NULL)
            {
                printf("\nError while opening file\n");
                exit (1);
            }

            fwrite (&d1, sizeof(struct details), 1, file2);
            fwrite (&d2, sizeof(struct details), 1, file2);
            if(fwrite != 0){
                printf("Successfully initialized the customer database !!\n");
            }
            else{
                printf("Error while initializing the customer database !\n");
                }
            fclose(file2);



    }



}

/* -> Loading data from file after the starting of program <-*/

void loadData(){
    if(totalItem == 0){

        FILE *file;
        struct menu data;

        file = fopen ("menu.txt", "r"); /* Opening menu file in read mode */
        if (file == NULL)
        {
            printf("\nError opening file(load data menu)\n");
            exit (1);
        }

        while(fread(&data, sizeof(struct menu), 1, file))
            totalItem ++;    /* -> Variable for storing total number of items in the menu <- */

        fclose (file);
    }

    if(totalCust == 0){
        FILE *file2;
        struct details data2;

        file2 = fopen ("details.txt", "r"); /* Opening customer data file in read mode */
        if (file2 == NULL)
        {
            printf("\nError opening file(load data details)\n");
            exit (0);
        }

        while(fread(&data2, sizeof(struct details), 1, file2))
            totalCust ++;      /* -> Variable for storing total number of customer served <- */

        fclose (file2);
    }




}

/* -> Main function works using switch case <-*/

void start(){
    createFile();
    totalCust = 0;
    totalItem = 0;
    loadData();
    int choice;
    printf("\n\n-------------------------> WELCOME TO THE FOOD ORDERING SYSTEM <------------------------");
    printf("\n\n-----------> Total Customer Served = %d <------------" , totalCust);
    printf("\n\n-----------> Total items in the menu = %d <------------" , totalItem);

    printf("\n\nPress 1 to see the menu and order and your ordern history (login required)\nPress 2 to signup\nPress 3 to exit\nPress 9 to know about me \nPress 0 for Admin Login\n-> ");
    scanf("%d" , &choice);
    switch (choice)
    {
    case 1:
        login();

        break;
    case 2:
        signUp();
        break;
    case 3:
        printf("\nExiting the system :(((");
        sleep(3);
        exit(1);
        break;
    case 0:
        adminlogin();
        break;
    case 9:
        aboutMe();
        break;
    default:
        printf("\nSorry you entered a wrong a choice \nExiting the system");
        sleep(5);
        exit(0);
        break;
    }

}

/* -> Update the detail database after ordering food <- */
void update(struct details cust){
    FILE *file;
    int i = 0 ;
    file = fopen("details.txt" , "a+");
    struct details cust2[totalCust];
    while(fread(&cust2[i], sizeof(struct details), 1, file));{
        if(cust2[i].custNo == cust.custNo){
            cust2[i] = cust;
        }
    }
    fclose(file);
    remove("details.txt");
    file = fopen("details.txt" , "w");
    for(i = 0 ; i < totalCust ; i++){
        fwrite(&cust2[i] , sizeof(struct details) , 1 , file);
    }
    fclose(file);

}

/* -> Check for double signUp of same username <- */

int isDouble(char name[30]){
    FILE *file;
    file = fopen("details.txt" , "r");
    struct details data;
    while(fread(&data , sizeof(struct details) ,1 , file)){
        if(strcasecmp(name , data.name) == 0){
            fclose(file);
            return 0;
        }


    }
    fclose(file);
    return 1;
}
/* -> Main function for ordering food <- */
/* -> This function takes structure details to get the user data <- */
void order_main(struct details custDetail){
    int process = 1 , noOfOrders = 0, choice , price_array[100] , orderCost = 0 , i , cnt_items = 0;
    int orders[50];

    FILE *file;
    struct menu data;

    file = fopen ("menu.txt", "r"); /* Opening menu file */
    if (file == NULL)
    {
        printf("\nError while loading menu\n");
        exit (1);
    }


    printf("-\n\n------------------------------------> WELCOME %s <-------------------------------------" , custDetail.name);
    printf("\n\nTotal order placed by you till now - %d\n\n" , custDetail.buycnt);
    printf("\n\nPress 1 to order food\nPress 2 to see your old order history\n-> ");
    scanf("%d" , &choice);
    if(choice == 1){
        choice = 0;
        printf("\nLoading the menu ..........\n\n\t\t\tITEM ID\t\tITEM NAME\tPRICE");
        sleep(1);
        while(fread(&data, sizeof(struct menu), 1, file)){
            printf("\n\n\t\t\t%d \t\t%s \t\t%d" , data.id , data.name , data.price);
            price_array[cnt_items] = data.price;
            cnt_items++;
            sleep(0);
        }

        fclose (file);


        while(process=1){
            printf("\nEnter your item id to order the dish\n or \nPress 0 to exit the ordering system\n-> ");

            scanf("%d" , &choice);
            if(choice == 0){
                process = 0;
                break;
            }
            else{
                int qty;
                printf("\nEnter quantity -> ");
                scanf("%d" , &qty);
                orders[noOfOrders] = choice;
                orderCost += price_array[choice-1]*qty;
                custDetail.prevOrder[custDetail.buycnt] = choice;
                custDetail.prevOrderqty[custDetail.buycnt] = qty;
                custDetail.buycnt +=1;
                noOfOrders++;
            }

    }

    printf("\nSuccessfully inputed your order !! \n");
    sleep(1);
    printf("\nYour total amount for the order is = %d Rs" , orderCost);
    sleep(1);
    printf("\nSaving these orders in your order History ......");
    sleep(1);
    printf("\n\nGenerating bill ..............\n\n");
    sleep(2);
    printf("\nCOST \t\t GST \t\t\t    Total");
    printf("\n\n%d \t\t 18 percent \t\t Rs %f" , orderCost , orderCost+(0.18*orderCost));
    printf("\n\n1 for UPI \n2 for cash\n-> ");
    scanf("%d" , &choice);
    if(choice == 1){
        printf("\nPAY AT FOODORDER@PAYTM.COM\n");
        printf("\nAfter payment wait for your order .....");

    }
    else{
        printf("\nKindly pay at the counter and wait for your order ...");
    }
    int delivery = 0;
    printf("\n\nPress 1 if you want to deliver your parcel at your entered address or\n Press 2 to take it from the counter\n-> ");
    scanf("%d" , &delivery);
    if(delivery == 1){
        printf("\n\nOur delivery guy will send it to your address it will take 15-20 minutes for delivery\n\nThank you");
    }
    else if(delivery == 2){
            printf("\n\nThanks for ordering kindly take your order from the counter\n");
            printf("\n\n\nEstimated waiting time - %d minutes" , noOfOrders*2);

    }
    else{
        printf("Invalid choice entered kindly take your order from the counter");
    }
    totalCust++;
    update(custDetail);
    printf("\n\n\nThanks for buying from us \n\n");
    printf("\nPress 0 to go to start menu \nPress 1 to order more\nPress any other key to exit\n-> ");
    scanf("%d" , &i);
    if(i == 0){
        start();
    }
    else if(i==1){
        order_main(custDetail);
    }
    else{
        exit(1);
        }

    }
    else if(choice == 2) {
        choice = 0;
        printf("\nLoading Order history data ......\n");
        sleep(2);
        if(custDetail.buycnt == 0){
            printf("You haven't bought anything till now \n\nStart buying from us now !!");
            order_main(custDetail);
        }
        else{
        printf("\n\t\t\tITEM ID\t\tITEM NAME\tPRICE\tQuantity\tTotal Cost");
        while(fread(&data, sizeof(struct menu), 1, file)){
            for(i = 0 ; i < custDetail.buycnt ; i++){
             if(data.id == custDetail.prevOrder[i]){
                printf("\n\n\t\t\t%d \t\t%s \t\t%d\t\t%d\t\t%d" , data.id , data.name , data.price , custDetail.prevOrderqty[i] , custDetail.prevOrderqty[i]*data.price);
             }
            }
            sleep(2);
        }
        printf("\n\n\nThanks for using our services \n\n");
        printf("\nPress 0 to go to start menu \nPress 1 to order more\nPress any other key to exit\n-> ");
        scanf("%d" , &i);
        if(i == 0){
            start();
        }
        else if(i==1){
            order_main(custDetail);
        }
        else{
            exit(1);
    }
        }


    }
    else {
        printf("Invalid choice entered exiting the system");
        exit(1);
    }


    }




/* -> Admin login for the owner usage <- */

void adminlogin(){
    char username[10];
    char passw[10];
    int choice;
    printf("-------------> ADMIN LOGIN <-------------\n\n\n");
    printf("Enter username \n-> ");
    scanf(" %100[^\n]" , username);
    printf("Enter password \n-> ");
    scanf(" %100[^\n]" , passw);
    if(strcasecmp(username , admin) == 0 && strcmp(passw , passadmin) == 0){
        printf("\n\n-------------------------------------------> WELCOME ADMIN <-------------------------------------------");
        printf("\nYou can customize this system here :))) ");
        printf("\nPress 1 to add a new dish to the menu \nPress 2 to get the list of all customers \nPress 3 to delete the menu\nPress 4 to delete the customer database\n->");
        scanf("%d" , &choice);
        switch (choice)
        {
        case 1:
            addMenu();
            break;

        case 2:
            customerInfo();
            break;
        case 3:
            delete_menu();
            break;
        case 4:
            delete_cust();
            break;

        default:
            printf("\nSorry you entered a wrong a choice \nExiting the system");
            break;
    }
        }


    else{
        printf("Invalid Id or password \nexiting");
        exit(1);
    }
    printf("Taking you to main page .... ");
    sleep(2);
    start();
}
void customerInfo(){
    FILE *file;
    file = fopen("details.txt" , "r");
    struct details cust;
    while(fread(&cust , sizeof(struct details) , 1, file)){
        printf("\nCustomer name => %s" , cust.name);
        printf("\nTotal items bought by %s => %d" , cust.name , cust.buycnt);
        printf("\n---------------------------------------------------------\n");
        }
    fclose(file);
}
/* -> Function for deleting the customer database <- */

void delete_cust(){
    int del = remove("details.txt");
   if (!del)
      printf("The file is Deleted successfully");
   else
      printf("the file is not Deleted");
    printf("\n\nPls restart the system to reflect the changes - ");
    exit(1);
}
/* -> Function for deleting the whole menu <- */

void delete_menu(){
    int del = remove("menu.txt");
   if (!del)
      printf("The file is Deleted successfully");
   else
      printf("the file is not Deleted");
   printf("\n\nPls restart the system to reflect the changes - ");
   exit(1);
}


/* -> Function for adding items in the menu only admin can use that <- */

void addMenu(){
    int num , i;
    FILE *file;
    char name[30];
    int price;
    file = fopen ("menu.txt", "a+");
    if (file == NULL)
    {
        printf("\nError while opening file\n");
        exit (1);
    }
    printf("How many dishes you want to enter in the menu\n-> ");
    scanf("%d" , &num);
    for(i = 0 ; i < num ; i++){
        printf("\nEnter the name of item -> ");
        scanf(" %100[^\n]" , name);
        printf("\nEnter price of %s ->" , name);
        scanf("%d" , &price);
        struct menu f1 = {totalItem+1, "" , price};
        strcpy(f1.name , name);
        fwrite (&f1, sizeof(struct menu), 1, file);

        if(fwrite != 0){
            printf("\nSuccessfully added in menu !!\n");
            totalItem++;}
        else
            printf("\nError while adding record in menu !\n");


    }
    fclose (file);

    printf("Taking you to the main page .... ");
    sleep(2);

    start();

}

void signUp(){
    FILE *file;
    int custNo;
    char name[30];
    char pass[30];
    char mobile[15];
    char address[100];
    printf("----------------------------------------------> SIGN UP PAGE <----------------------------------------------");
    printf("\nEnter your name -> ");
    scanf(" %100[^\n]" , name);
    struct details d1;
    d1.custNo = totalCust+1;

    while(1){
        if(isDouble(name) == 1){
            printf("\n");
            break;
        }
        else{
            printf("This username is already in use pls enter some unique username\n-> ");
            scanf(" %100[^\n]" , name);

        }
    }
    strcpy(d1.name , name);
    //printf("%s" , d1.name);
    printf("\nSet your password -> ");
    scanf(" %100[^\n]" , pass);
    printf("\nEnter your mobile number -> ");
    scanf(" %100[^\n]" , mobile);
    printf("\nEnter your address for delivery -> ");
    scanf(" %100[^\n]" , address);
    strcpy(d1.address , address);
    strcpy(d1.pass , pass);
    strcpy(d1.mobile , mobile);
    d1.buycnt = 0;
    file = fopen ("details.txt", "a+");
    if (file == NULL)
    {
        printf("\nError while opening file\n");
        exit (1);
    }

    fwrite (&d1, sizeof(struct details), 1, file);

    if(fwrite != 0){
        printf("\nSuccessfully added your details in the record \nPls login now!!\n\n\n");
        fclose(file);
        login();
    }
    else{
        printf("Error while adding record !\n");
        }
    fclose (file);



}
int login(){
    char name[30] , pass[30];
    int found = 1 , choice1;
    printf("\n\n---------------------------------> LOGIN PAGE <---------------------------------");
    printf("\n\nPress any key to go forward (from 1-9) or Press 0 to signUp if you don't have any account\n-> ");
    scanf("%d" , &choice1);
    if(choice1 == 0){
        signUp();
        return 1;
    }
    choice1 = 1;
    FILE *file;
    file = fopen ("details.txt", "r");
    if (file == NULL)
    {
        printf("file == null");
        printf("\nError opening file\n");
        exit (1);
    }
    printf("Pls enter your login details ...\n\n");
    struct details data;
    printf("Enter name -> ");
    scanf(" %100[^\n]" , name);
    //printf("Entered name is %s\n" , name);

    while(fread(&data, sizeof(struct details), 1, file)){
        //printf("Inside while loop\n");
        //printf("%s\n" , data.name);
        if(strcasecmp(data.name , name) == 0){
                found = 1;
                printf("Enter password -> ");
                scanf(" %100[^\n]" , pass);
                if(strcmp(data.pass , pass) == 0){
                    fclose (file);
                    order_main(data);
                    return 1;
                    }
                else{
                    printf("Invalid Password entered try again ! ");
                    printf("Enter password -> ");
                    scanf(" %100[^\n]" , pass);
                    if(strcmp(data.pass , pass) == 0){
                        fclose (file);
                        order_main(data);
                        return 1;
                        }
                    else{
                        printf("Invalid Password entered again Exiting ! ");
                        sleep(3);
                        exit(1);
                        }
                    }


            }
        else{
            found = 0;
        }
}
    if(found == 0){
        printf("User data not found in our records !! \n\nTaking you to signUp page pls sign up with a new account .....\n");
        sleep(1);
        signUp();
        return 1;
    }

}
void aboutMe(){
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("Loading Info about me .........");
    sleep(1);
    printf("\n\nI am a food ordering system that helps the owner to effectively manage his shop/cafeteria \nI can do various things and store various information and can help you with->\n");
    printf("1)Managing heavy load of requests\n");
    printf("2)Manage menu effectively  , can add new dish to menu");
    printf("\n3)Store customer information effectively to remove the writing of a ton of a data");
    printf("\n\n\nVersion - 1.0");
    printf("\n\nMade by - \nAyush Kumar Tomar\nSumit Khemka\nAmulya Agrawal");
    printf("\n\n");

}

int main(){
    start();

return 0;}