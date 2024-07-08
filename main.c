#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct{
    int month;
    int year;
} date;

typedef struct {
    char  account_number[20];
    char name[50];
    char mobile[20];
    char address[30];
    double balance;
    date date_opened;
}account;
account a[100];
int counter=0;
User s[100];
int c=0;
int isvalidadd(char *a){
    int check1=0,check2=0;
    for(int i=0;i<strlen(a);i++)
    {
        if(a[i]=='@')
            check1++;
        if(a[i]=='.')
            check2++;
        if(a[i]==' ')
            return 0;
    }
    if(check1!=1||check2==0)
        return 0;
    if (!isalpha(a[0]))
        return 0;
    for(int i=0;i<strlen(a);i++)
    {
        if(a[i]=='@')
            check1=i;
        if(a[i]=='.')
            check2=i;
    }
    if(strstr(a,".com")==NULL)
        return 0;
    if(check2-check1>1&&(check2+1)!=strlen(a))
         return 1;
    else return 0;
}
int isvalidacc(char *a){
    if(strlen(a)!=10)
        return 0;
    for(int i=0;i<10;i++)
        if(!isdigit(a[i]))
            return 0; ;
    return 1;
}
int isvalidmobI(char *a){
    if(strlen(a)!=11)
        return 0;
    for(int i=0;i<strlen(a);i++)
        if(!isdigit(a[i]))
            return 0;
    return 1;
}
void ADD(){
    char acc_to_add[20];
    int unique;
    while(1)
    {
    unique=0;
    printf("\nPlease enter your new account number: ");
    gets(acc_to_add);
    while(!isvalidacc(acc_to_add))
    {
        printf("!! Account number not valid\n");
        printf("Please enter new account number: ");
        gets(acc_to_add);
    }
    for(int i=0;i<counter;i++)
        if(strcmp(acc_to_add,a[i].account_number)==0)
            unique++;
    if(unique)
        printf("<<The account number isn't unique>>\n");
    else break;
    }
    strcpy(a[counter].account_number,acc_to_add);
    printf("Please enter your name: ");
    gets(a[counter].name);
    printf("Please enter your address: ");
    gets(a[counter].address);
    while(!isvalidadd(a[counter].address))
    {
        printf("!! Address not valid\n");
        printf("Please enter new address: ");
        gets(a[counter].address);
    }
    a[counter].balance=0.0;
    time_t t;
    struct tm *current_time;
    time(&t);
    current_time = localtime(&t);
    a[counter].date_opened.month = current_time->tm_mon + 1;
    a[counter].date_opened.year= current_time->tm_year + 1900;
    printf("please enter your mobile: ");
    gets(a[counter].mobile);
    while(!isvalidmobI(a[counter].mobile))
    {
        printf("mobile not valid\n");
        printf("please enter new mobile number: ");
        gets(a[counter].mobile);
    }
    while(1)
    {
        int confirm=-1;
        printf("For confirm and save your new account:1\nFor exit and don't save:2\n-->");
        scanf("%d",&confirm);
        getchar();
        switch(confirm)
        {
        case 1:
            counter++;
            save();
            return ;
        case 2:
            return ;
        default:
            printf("you should choice 1 or 2 only\n");
        }
    }
}
int check_acc(){
    int number_account=-1;
    printf("\n~ Enter the account number: ");
    char acc[20];
    gets(acc);
    while(1)
    {
        int check=0;
        for(int i=0;i<counter;i++)
            if(strcmp(acc,a[i].account_number)==0)
            {check++; number_account=i; }
         if(check)
                break;
         else
         printf("The account number doesn't Exist\n");
         int exit=0;
         while(exit!=1)
        {
        printf("~To try again:1 \n~To exit:2\n");
         scanf("%d",&exit);
         getchar();
        switch(exit)
        {
        case 1: break;
        case 2:
            return number_account;
        default:
            printf("you should choice 1 or 2 only\n");
        }
        }
         printf("please enter account number again:");
         gets(acc);
    }
    return number_account;
}
void DELETE(){
    int number_account=check_acc();
    if(number_account==-1)
        return ;
    if(a[number_account].balance!=0)
    {
        printf("<<Can't delete account because balance greater than zero. >>\n");
        return ;
    }
    while(1)
    {
    printf("Confirm delete:1 \tFor exit and don't delete:2\n-->");
    int conform=-1;
    scanf("%d",&conform);
    getchar();
    switch(conform)
        {
        case 1:
            for(int i=number_account;i<counter;i++)
            {
                a[i]=a[i+1];
            }
            counter--;
            save();
            return;
        case 2:
            return;
        default:
            printf("!! You should choice 1 or 2 only.\n");
        }
    }
}
void MODIFY(){
    int number_account=check_acc();
    if(number_account==-1)
        return ;
    account orginal=a[number_account];
    int check_modify=0;
    while(1)
    {
        int choise=0;
        printf("modify name:1 \nmodify address:2 \nmodify mobile:3\nTo exit:4\n");
        scanf("%d",&choise);
        getchar();
        switch(choise)
        {
        case 1 :
            printf("please enter new name: ");
            gets(a[number_account].name);
            check_modify++;
            break;
        case 2 :
            printf("please enter new address: ");
            gets(a[number_account].address);
            while(!isvalidadd(a[number_account].address))
            {
                printf("address not valid\n");
                printf("please enter new address: ");
                gets(a[number_account].address);
            }
            check_modify++;
            break;
        case 3:
            printf("please enter your mobile: ");
            gets(a[number_account].mobile);
            while(!isvalidmobI(a[number_account].mobile))
            {
                printf("mobile not valid\n");
                printf("please enter new mobile number: ");
                gets(a[number_account].mobile);
            }
            check_modify++;
            break;
        case 4:
            if(check_modify==0)
                return ;
            while(1)
            {
            printf("conform modify:1 \nfor exit and don't modify:2\n");
            int conform=-1;
            scanf("%d",&conform);
            getchar();
            switch(conform)
            {
                case 1:
                    save();
                    return;
                case 2:
                    a[number_account]=orginal;
                    return;
                default:
                printf("you should choice 1 or 2 only\n");
                break;
            }
            }
        default:
            printf("you should choice from 1 to 4\n");
        }
    }
}
void printMonth(int month_Number){
    switch (month_Number)
     {
        case 1:
            printf("January ");
            break;
        case 2:
            printf("February ");
            break;
        case 3:
            printf("March ");
            break;
        case 4:
            printf("April ");
            break;
        case 5:
            printf("May ");
            break;
        case 6:
            printf("June ");
            break;
        case 7:
            printf("July ");
            break;
        case 8:
            printf("August ");
            break;
        case 9:
            printf("September ");
            break;
        case 10:
            printf("October ");
            break;
        case 11:
            printf("November ");
            break;
        case 12:
            printf("December ");
            break;
        default:
            printf("Invalid month number\n");
         break;}
}
void SEARCH(){
    int number_account=check_acc();
    if(number_account==-1)
        return ;
    printf("Account Number : %s\n",a[number_account].account_number);
    printf("Name : %s\n",a[number_account].name);
    printf("E-mail : %s\n",a[number_account].address);
    printf("Balance : %lf\n",a[number_account].balance);
    printf("Mobile : %s\n",a[number_account].mobile);
    printf("Date Opened: ");
    printMonth(a[number_account].date_opened.month);
    printf(" %d\n",a[number_account].date_opened.year);

}
void ADVANCED_SEARCH(){
    printf("\nPlease enter keyword to search: ");
    char keyword[20];
    gets(keyword);
    int check=0;
    for(int i=0;i<counter;i++)
        if(strstr(a[i].name,keyword)!=NULL)
        {
            check++;
            printf("Account Number : %s\n",a[i].account_number);
            printf("Name : %s\n",a[i].name);
            printf("E-mail : %s\n",a[i].address);
            printf("Balance : %lf\n",a[i].balance);
            printf("Mobile : %s\n",a[i].mobile);
            printf("Date Opened: ");
            printMonth(a[i].date_opened.month);
            printf(" %d\n",a[i].date_opened.year);
        }
        if(check==0)
            printf("<<No matches are found>>\n");
}
void print(){
    int x,flag;
    do{
        printf("\n ~ Sort by:\n 1. Name\t 2. Date\t 3. Balance\t 4. Cancel\n --> ");
        scanf("%d",&x);
        flag=0;
        switch(x){
            case 1:
                SortByName();
                break;
            case 2:
                SortByDate();
                break;
            case 3:
                SortByBalance();
                break;
            case 4:
                return;
            default:
                printf("\n !! Invalid Input !!\n");
                flag=1;
                break;
        }
    }while(flag);
}
void SortByName(){
    int x,flag,i,pass,sorted=0;
    account hold;
    do{
        flag=0;
        printf("\n 1. Ascending order\t2. Descending order\t3. Cancel\n --> ");
        scanf("%d",&x);
        switch(x){
            case 1:{
                for(pass=1; pass<counter && !sorted; pass++){
                    sorted = 1;
                    for(i=0;i<counter-pass;i++){
                        if(stricmp(a[i].name,a[i+1].name)>0){
                            hold = a[i];
                            a[i] = a[i+1];
                            a[i+1] = hold;
                            sorted = 0;
                        }
                    }
                }
                for(i=0;i<counter;i++){
                    printf("%s\t", a[i].account_number);
                    printf("%s\t\t", a[i].name);
                    printf("%s\t", a[i].mobile);
                    printf("%s\t", a[i].address);
                    printf("%.2lf\t", a[i].balance);
                    printMonth(a[i].date_opened.month);
                    printf("%d\n", a[i].date_opened.year);
                }
                break;
            }
            case 2:{
                for(pass=1; pass<counter && !sorted; pass++){
                    sorted = 1;
                    for(i=0;i<counter-pass;i++){
                        if(stricmp(a[i].name,a[i+1].name)<0){
                            hold = a[i];
                            a[i] = a[i+1];
                            a[i+1] = hold;
                            sorted = 0;
                        }
                    }
                }
                for(i=0;i<counter;i++){
                    printf("%s\t", a[i].account_number);
                    printf("%s\t\t", a[i].name);
                    printf("%s\t", a[i].mobile);
                    printf("%s\t", a[i].address);
                    printf("%.2lf\t", a[i].balance);
                    printMonth(a[i].date_opened.month);
                    printf("%d\n", a[i].date_opened.year);
                    }
                break;
            }
            case 3:
                return;
            default:
                printf("\n !! Invalid Input !!\n");
                flag=1;
                break;
        }
    }while(flag);
}
void SortByDate(){
    int x,flag,i,pass,sorted=0;
    account hold;
    do{
        flag=0;
        printf("\n 1. Newest to Oldest\t2. Oldest to Newest\t3. Cancel\n --> ");
        scanf("%d",&x);
        switch(x){
            case 1:{
                for(pass=1; pass<counter && !sorted; pass++){
                    sorted = 1;
                    for(i=0;i<counter-pass;i++){
                        if(a[i].date_opened.year<a[i+1].date_opened.year){
                            hold = a[i];
                            a[i] = a[i+1];
                            a[i+1] = hold;
                            sorted = 0;
                        }
                        if(a[i].date_opened.year==a[i+1].date_opened.year){
                            if(a[i].date_opened.month<a[i+1].date_opened.month){
                                hold = a[i];
                                a[i] = a[i+1];
                                a[i+1] = hold;
                                sorted = 0;
                            }
                        }
                    }
                }
                for(i=0;i<counter;i++){
                    printf("%s\t", a[i].account_number);
                    printf("%s\t\t", a[i].name);
                    printf("%s\t", a[i].mobile);
                    printf("%s\t", a[i].address);
                    printf("%.2lf\t", a[i].balance);
                    printMonth(a[i].date_opened.month);
                    printf("%d\n", a[i].date_opened.year);
                }
                break;
            }
            case 2:{
                for(pass=1; pass<counter && !sorted; pass++){
                    sorted = 1;
                    for(i=0;i<counter-pass;i++){
                        if(a[i].date_opened.year>a[i+1].date_opened.year){
                            hold = a[i];
                            a[i] = a[i+1];
                            a[i+1] = hold;
                            sorted = 0;
                        }
                        if(a[i].date_opened.year==a[i+1].date_opened.year){
                            if(a[i].date_opened.month>a[i+1].date_opened.month){
                                hold = a[i];
                                a[i] = a[i+1];
                                a[i+1] = hold;
                                sorted = 0;
                            }
                        }
                    }
                }
                for(i=0;i<counter;i++){
                    printf("%s\t", a[i].account_number);
                    printf("%s\t\t", a[i].name);
                    printf("%s\t", a[i].mobile);
                    printf("%s\t", a[i].address);
                    printf("%.2lf\t", a[i].balance);
                    printMonth(a[i].date_opened.month);
                    printf("%d\n", a[i].date_opened.year);
                }
                break;
            }
            case 3:
                return;
            default:
                printf("\n !! Invalid Input !!\n");
                flag=1;
                break;
        }
    }while(flag);
}
void SortByBalance(){
    int x,flag,i,pass,sorted=0;
    account hold;
    do{
        flag=0;
        printf("\n 1. Highest to Lowest\t2. Lowest to Highest\t3. Cancel\n --> ");
        scanf("%d",&x);
        switch(x){
            case 1:{
                for(pass=1; pass<counter && !sorted; pass++){
                    sorted = 1;
                    for(i=0;i<counter-pass;i++){
                        if(a[i].balance<a[i+1].balance){
                            hold = a[i];
                            a[i] = a[i+1];
                            a[i+1] = hold;
                            sorted = 0;
                        }
                    }
                }
                for(i=0;i<counter;i++){
                    printf("%s\t", a[i].account_number);
                    printf("%s\t\t", a[i].name);
                    printf("%s\t", a[i].mobile);
                    printf("%s\t", a[i].address);
                    printf("%.2lf\t", a[i].balance);
                    printMonth(a[i].date_opened.month);
                    printf("%d\n", a[i].date_opened.year);
                }
                break;
            }
            case 2:{
                for(pass=1; pass<counter && !sorted; pass++){
                    sorted = 1;
                    for(i=0;i<counter-pass;i++){
                        if(a[i].balance>a[i+1].balance){
                            hold = a[i];
                            a[i] = a[i+1];
                            a[i+1] = hold;
                            sorted = 0;
                        }
                    }
                }
                for(i=0;i<counter;i++){
                    printf("%s\t", a[i].account_number);
                    printf("%s\t\t", a[i].name);
                    printf("%s\t", a[i].mobile);
                    printf("%s\t", a[i].address);
                    printf("%.2lf\t", a[i].balance);
                    printMonth(a[i].date_opened.month);
                    printf("%d\n", a[i].date_opened.year);                }
                break;
            }
            case 3:
                return;
            default:
                printf("\n !! Invalid Input !!\n");
                flag=1;
                break;
        }
    }while(flag);
}
int quit(){
    int x;
    while(1){
        printf("\n ~ Are you sure you want to quit?\n 1. YES, Quit\t2. NO, Go Back\n --> ");
        scanf("%d",&x);
        getchar();
        switch(x)
        {
            case 1:
                exit(0);
            case 2:
                return;
            default:
                printf("\n !! Invalid Input !!\n");
                break;
        }
    }
}
int CheckPass_user(User check ) {

    for(int i=0;i<c;i++)
        if (strcmp(check.username, s[i].username) == 0 && strcmp(check.password,s[i].password ) == 0)
            return 1;
    return 0;
}
int LogIn() {
    load_User();
    User user;
    printf("\n~ Enter your username: ");
    scanf("%s", user.username);
    printf("~ Enter your password: ");
    scanf("%s", user.password);
    while(!CheckPass_user(user))
    {
        printf("<<Not exist>>\n");
        int check=0;
        while(check!=2)
        {
        printf("1. To exit\t 2. To try agian\n-->");
        scanf("%d",&check);
        switch (check)
        {
        case 1:
            return 0;
        case 2:
            break;
        default:
            printf("choise 1 or 2\n");
            break;
        }
        }
        printf("Enter your username: ");
        scanf("%s", user.username);

        printf("Enter your password: ");
         scanf("%s", user .password);
    }
    return 1;
}
void load_User() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    while (!feof(file))
    {
        fscanf(file, "%s" , s[c].username) ;
        fscanf(file, "%s" ,  s[c].password) ;
        c++;
    }
}
void save(){
   FILE *file2= fopen("accounts.txt", "w");
    for(int i=0;i<counter;i++)
    {
    fprintf(file2, "%s,%s,%s,%lf,%s,%d-%d\n",
                                                   a[i].account_number,
                                                  a[i].name,
                                                   a[i].address,
                                                   a[i].balance,
                                                   a[i].mobile,
                                                  a[i].date_opened.month,
                                                   a[i].date_opened.year) ;
    }
     fclose(file2);
}
void load() {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {

        sscanf(line, "%[^,],%[^,],%[^,],%lf,%[^,],%d-%d",
               a[counter].account_number, a[counter].name,
               a[counter].address, &a[counter].balance,
               a[counter].mobile, &a[counter].date_opened.month,
               &a[counter].date_opened.year);
        counter++;
    }
    fclose(file);
}
int checkAmunt(double amount){
    if(amount<10000)
        return 1;
    else
        return 0;
}
void WithDraw(){
    FILE *f;
    int x=check_acc();
    if(x==-1)
        return ;
    double amunt;
    printf("~ Enter amount to be withdrawn ");
    scanf("%lf",&amunt);
    getchar();
    if(a[x].balance>=amunt)
    {
        if (checkAmunt(amunt))
        {
            a[x].balance-=amunt;
            save();
            printf("<<The transaction was successful.>>");
            char filename[20];
            sprintf(filename,"%s.txt",a[x].account_number);
            f=fopen(filename, "a");
            fprintf(f," %.2lf withdrawn from your account. Your balance %.2lf\n",amunt,a[x].balance);
            fclose(f);
        }
        else
            printf("<<The transaction was not successful because the amount to withdrawn was bigger than 10000$>>");
    }
    else
        printf("<<Your account has not this amount to be withdrawn>>");
}
void Deposit(){
    FILE *f;
    int x=check_acc();
    if(x==-1)
        return ;
    double amunt;
    printf("~ Enter amount to be Deposite:\n-->");
    scanf("%lf",&amunt);
    getchar();
    if (checkAmunt(amunt))
    {
        (a[x].balance)+=amunt;
        save();
        printf("<<The transaction was successful.>>");
        char filename[20];
        sprintf(filename,"%s.txt",a[x].account_number);
        f=fopen(filename, "a");
        fprintf(f," %.2lf was deposited in your account. Your balance %.2lf\n",amunt,a[x].balance);
        fclose(f);
    }
    else
        printf("<<The transaction was not successful because amount to deposite \n bigger than 10000$>>");
}
void Transfer(){
    FILE *f;
    FILE *t;
    int x=check_acc();
    if(x==-1)
        return ;
    printf("account transfer money to it\n");
    int y=check_acc();
    if(y==-1)
        return ;
    double amunt;
    printf("~Enter amount money to transfer:\n-->");
    scanf("%lf",&amunt);
    getchar();
    if(checkAmunt(amunt))
    {
        if(a[x].balance>=amunt)
        {
            a[x].balance-=amunt;
            char filename[20];
            sprintf(filename,"%s.txt",a[x].account_number);
            f=fopen(filename, "a");
            fprintf(f,"%.2lf was Transfered from your account to this acount number :%s. Your balance %.2lf\n",amunt,a[y].account_number,a[x].balance);
            fclose(f);
            a[y].balance+=amunt;
            save();
            char T_filename[20];
            sprintf(T_filename,"%s.txt",a[y].account_number);
            t=fopen(T_filename, "a");
            fprintf(t,"%.2lf was depodite to your account from %s.Your balance %.2lf\n",amunt,a[x].account_number,a[y].balance);
            fclose(t);
            printf("~Tranfer Done.\n");
        }
        else
            printf("<<your account deosn't have this amount to be transfered>>\n");
    }
    else
        printf("<<The transaction was not successful because amount of money bigger than 10000$>>");

}
void Report(){
    FILE *f;
    int x=check_acc();
    if(x==-1)
        return ;
    char filename[20];
    sprintf(filename,"%s.txt",a[x].account_number);
    f=fopen(filename, "r");
    if(f!=NULL)
    {
        int n=0;
        char o;
        while ((o=getc(f))!=EOF)          //to get lines of file
        {
            if(o=='\n')
            n++;
        }
        rewind(f);
        if(n<=5)
        {
            char c;
            printf("~All your transiction on this account :\n");
            while((c=getc(f))!=EOF)
            putchar(c);
            fclose(f);
        }
        else
        {
            for (int i = 0; i < (n - 5); i++)
            {
                char a[120];
                fgets(a, sizeof(a), f);
            }
            char c;
            printf("~your last five transiction:\n");
            while((c=getc(f))!=EOF)
                putchar(c);
            fclose(f);
        }
    }
    else
        printf("<<This account not have any transaction before>>");
}
void menu(){
    int x,y;
    while(1){
        printf("\n ~ Type in the number of the service you want:\n");
        printf(" 1. LOGIN\t  2. QUIT\n --> ");
        scanf("%d",&x);
        if(x==1&&LogIn()){
                load();
                while(1){
                    printf("\n ~ Type in the number of the service you want:\n");
                    printf(" 1. ADD\t\t 2. DELETE\t 3. MODIFY\t 4. SEARCH\t 5. ADVANCED SEARCH\t 6. WITHDRAW\n 7. DEPOSIT\t 8. TRANSFER\t 9. REPORT\t10. PRINT\t11. QUIT\n --> ");
                    scanf("%d",&y);
                    getchar();
                    switch(y){
                        case 1:
                            ADD();
                            break;
                        case 2:
                            DELETE();
                            break;
                        case 3:
                            MODIFY();
                            break;
                        case 4:
                            SEARCH();
                            break;
                        case 5:
                            ADVANCED_SEARCH();
                            break;
                        case 6:
                            WithDraw();
                            break;
                        case 7:
                            Deposit();
                            break;
                        case 8:
                            Transfer();
                            break;
                        case 9:
                            Report();
                            break;
                        case 10:
                            print();
                            break;
                        case 11:
                            quit();
                            break;
                        default:
                            printf("\n !! Invalid Input !!\n");
                            break;
                    }
                }
        }
        else if(x==2)
            quit();
        else if(x!=1&&x!=2)
            printf("\n !! Invalid Input !!\n");
    }
}
int main()
{
    menu();
    return 0;
}
