#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<conio.h>
#include<unistd.h>

void enqeue(int *number_of_qeues,char people[][15],int *pwd,int *vip,int *normal);
void deqeue(int *number_of_qeues,char people[][15],int *vip,int *pwd,int *normal);
void print_qeue(int number_of_qeues,char people[][15],int count);
//***************************************************************************************************************************************************************
//structure
typedef struct {
    float price_of_food;
    char food[20];
}menu;

typedef struct {
    float price_of_drink;
    char drink[15];
}drink;
//***************************************************************************************************************************************************************
int take_order2(size_t sizeofdrinks,drink [],char customer[],char order[][20],float prices[],float *cost,int *count_of_order);
int take_order(size_t sizeoffood,menu [],char customer[],char order[][20],float prices[],float *cost,int *count_of_order);
void print_receipt(float cost,int count_of_order,float prices[],char order[][20]);
void delete_order(float *cost,int *count_of_order,float prices[],char order[][20]);
//***************************************************************************************************************************************************************
typedef int important;
//***************************************************************************************************************************************************************
#define header printf("\n\t\t\t\t\t\t\tJollikod\n\n");
#define line printf("========================================================================================================================\n\n");
#define small_line printf("\n\n________________________________________________________________________________________________________________________");
#define clear system("cls");
#define click getch();
#define prompt printf("\n\n\nPress any key to continue...");
#define loading printf("\n\n\n\n\n\t\t\t\t\t\t      Loading...\n\t\t\t\t\t\t      ");
//***************************************************************************************************************************************************************
//Main function
int main(){
    important count,number_of_qeues=0,i,choice,pwd=0,normal=0,vip=0,num_of_drinks,num_of_foods;
    int count_of_order;
    float cost,prices[10];

    FILE *foods,*beverage;
    menu *menus;
    drink *drinks;

    foods=fopen("foods.txt","r");
    beverage=fopen("drinks.txt","r");

    fscanf(foods,"%d",&num_of_foods);
    menus=(menu*)malloc(num_of_foods*sizeof(menu));
    for(i=0;i<num_of_foods;i++){
        fscanf(foods,"%d %20[^\n]s",(menus+i)->price_of_food,(menus+i)->food);
    }

    fscanf(beverage,"%d",&num_of_drinks);
    drinks=(drink*)malloc(num_of_drinks*sizeof(drink));
    for(i=0;i<num_of_drinks;i++){
        fscanf(beverage,"%d %20[^\n]s",(drinks+i)->price_of_drink,(drinks+i)->drink);
    }

    header
    line
    printf("\t\t\t\tEnter the number of Customer/s: ");
    scanf("%d",&count);
    clear
    header
    line
    loading
    for(int i=0;i<10;i++){
        usleep(200000);
        printf("%c",219);
    }

    char people[count][15], order[10][20], customer[15];

    do{
        do{
            count_of_order=0;
            cost=0;
            print_qeue(number_of_qeues,people,count);
            small_line
            printf("\n\n\t\t\t\t\t[1] Add a person to the qeue\n\t\t\t\t\t[2] Take the order of a customer\n\t\t\t\t\t[3] Exit\n\n\t\t\t\t\tEnter here: ");
            scanf("%d",&choice);

            if(number_of_qeues==0 && choice==2)
                choice=0;
            else if(count==number_of_qeues && choice==1)
                choice=0;

            switch(choice){
                case 1:
                    enqeue(&number_of_qeues,people,&vip,&pwd,&normal);
                    break;
                case 2:
                    strcpy(customer,people[0]);
                    do{
                        choice=take_order(sizeof(menus)/sizeof(menus[0]),menus,customer,order,prices,&cost,&count_of_order);
                            if(choice==4){
                                choice=take_order2(sizeof(drinks)/sizeof(drinks[0]),drinks,customer,order,prices,&cost,&count_of_order);
                            }
                    }while(choice==4);
                        if(choice==2){
                            clear
                            header
                            line
                            printf("\n\n\n\n\n\t\t\t\t\t\t     Cancelling...\n\t\t\t\t\t\t     ");
                            for(int i=0;i<13;i++){
                                usleep(200000);
                                printf("%c",219);
                            }
                            printf("\n\n\n\n\n");
                        }
                        else
                            print_receipt(cost,count_of_order,prices,order);

                        deqeue(&number_of_qeues,people,&vip,&pwd,&normal);
                    break;
                case 3:
                    clear
                    header
                    line
                    printf("\n\n\n\n\n\t\t\t\t\t\t      Exiting...\n\t\t\t\t\t\t      ");
                    for(int i=0;i<10;i++){
                        usleep(200000);
                        printf("%c",219);
                    }
                    printf("\n\n\n\n\n");
                    break;
                default:
                    clear
                    header
                    line
                    printf("\n\n\n\t\t\t\t\t\t\tInvalid\n\n\n\n");
                    click
                    break;
            }
        }while(choice<1 || choice>3);

    }while(choice!=3);
}

//**************************************************************************************************************************************************************
//For adding a person to the qeue
void enqeue(int *number_of_qeues,char people[][15],int *pwd,int *vip,int *normal){
    important status,i;
    do{
        clear
        header
        line
        printf("\n\n\n\n\t\t\t\t\t      Is the person PWD or normal?\n\n\t\t\t\t\t\t      [1] VIP\n\t\t\t\t\t\t      [2] PWD\n\t\t\t\t\t\t      [3] Normal\n\n\t\t\t\t\t\t    Enter here: ");
        scanf("%d",&status);
        clear
        header
        line
        switch(status){
            case 1:
                for(i=*normal;i>*vip;i--){
                    strcpy(people[i],people[i-1]);
                }
                printf("\n\n\n\t\t\t\t\tEnter the name of a person: ");
                scanf(" %[^\n]s",&people[*vip]);
                *number_of_qeues+=1;
                *vip+=1;
                *normal+=1;
                break;
            case 2:
                for(i=*normal;i>*vip;i--){
                    strcpy(people[i],people[i-1]);
                }
                for(i=*vip;i>*pwd;i--){
                    strcpy(people[i],people[i-1]);
                }
                printf("\n\n\n\t\t\t\t\tEnter the name of a person: ");
                scanf(" %[^\n]s",&people[*pwd]);
                *number_of_qeues+=1;
                *vip+=1;
                *pwd+=1;
                *normal+=1;
                break;
            case 3:
                printf("\n\n\n\t\t\t\t\tEnter the name of a person: ");
                scanf(" %[^\n]s",&people[*normal]);
                *number_of_qeues+=1;
                *normal+=1;
                break;
            default:
                printf("\n\n\n\t\t\t\t\t\t\tInvalid\n\n");
                click
                break;
        }
    }while(status<1 || status>3);

}
//***************************************************************************************************************************************************************
//For displaying the person to the qeue
void print_qeue(int number_of_qeues,char people[][15],int count){
    important i;
    clear
    header
    line
    printf("\n\n\t\t\t\t\tCapacity: %d\n",count);
    printf("\n\t\t\t\t\tThe number of people in the qeues are: %d\n",number_of_qeues);

    printf("\n\t\t\t\t\tThe people in the qeue are:\n");

    if(number_of_qeues==0)
        printf("\t\t\t\t\t\t\t\t    None\n\n");
    else
        for(i=0;i<number_of_qeues;i++)
            printf("\t\t\t\t\t\t\t\t    [%d] %s\n",i+1,people[i]);
}
//***************************************************************************************************************************************************************
//For removing the person to the qeue
void deqeue(int *number_of_qeues,char people[][15],int *vip,int *pwd,int *normal){
    important i;
    for(i=0;i<*number_of_qeues-1;i++){
        strcpy(people[i],people[i+1]);
    }
    *number_of_qeues-=1;
    *vip-=1;
    *pwd-=1;
    *normal-=1;
}
//***************************************************************************************************************************************************************
//For food
int take_order(size_t sizeoffood,menu menus[],char customer[],char order[][20],float prices[],float *cost,int *count_of_order){
    important i,choice;
    //Food
    do{
        clear
        header
        line
        printf("\n\t\t\t\t\t\t       Order food\n");
        for(i=0;i<sizeoffood;i++){
            printf("\n\t\t\t\t\t     [%d] P %6.2f   %s",i+1,menus[i].price_of_food,menus[i].food);
        }
        printf("\n\n\n");
        small_line
        printf("\n\n\t\t\t\t\t\t       Enter here: ");
        scanf("%d",&choice);
        i=0;
        if(choice>=1 && choice<=9){
            strcpy(order[*count_of_order],menus[choice-1].food);
            prices[*count_of_order]=menus[choice-1].price_of_food;
            *cost+=menus[choice-1].price_of_food;
            *count_of_order+=1;
            do{
                clear
                header
                line
                printf("\n\n\t\t\t\t\t\t      %s's order\n",customer);
                for(i=0;i<*count_of_order;i++){
                    printf("\n\t\t\t\t\t      [%d] P %6.2f   %s",i+1,prices[i],order[i]);
                }
                printf("\n\n\n\t\t\t\t\t\t     Cost: P %3.2f\n\n",*cost);
                small_line
                printf("\n\n\t\t\t\t\t\t      [1] Order again\n\t\t\t\t\t\t      [2] cancel taking order\n\t\t\t\t\t\t      [3] Delete an order\n\t\t\t\t\t\t      [4] Drinks\n\t\t\t\t\t\t     Enter here: ");
                scanf("%d",&i);

                if(i==2)
                    return 2;
                else if(i==3)
                    delete_order(cost,count_of_order,prices,order);
                else if(i==4)
                    return 4;
                else if(i<1 || i>4){
                    clear
                    header
                    line
                    printf("\n\n\n\t\t\t\t\t\t\tInvalid\n\n\n\n");
                    click
                }

            }while((i<1 || i>4) || i==3);
        }
        else{
            clear
            header
            line
            printf("\n\n\n\t\t\t\t\t\t\tInvalid\n\n\n\n");
            click
        }

    }while(i==1);
}
//For drinks=====================================================================================================================================================================
int take_order2(size_t sizeofdrinks,drink drinks[],char customer[],char order[][20],float prices[],float *cost,int *count_of_order){
    important i,choice;
    do{
        clear
        header
        line
        printf("\n\t\t\t\t\t\t       Order drinks\n");
        for(i=0;i<sizeofdrinks;i++){
            printf("\n\t\t\t\t\t      [%d] P %6.2f   %s",i+1,drinks[i].price_of_drink,drinks[i].drink);
        }
        printf("\n\n\n");
        small_line
        printf("\n\n\t\t\t\t\t\t       Enter here: ");
        scanf("%d",&choice);
        i=0;
        if(choice>=1 && choice<=9){
            strcpy(order[*count_of_order],drinks[choice-1].drink);
            prices[*count_of_order]=drinks[choice-1].price_of_drink;
            *cost+=drinks[choice-1].price_of_drink;
            *count_of_order+=1;
            do{
                clear
                header
                line
                printf("\n\n\t\t\t\t\t\t      %s's order\n",customer);
                for(i=0;i<*count_of_order;i++){
                    printf("\n\t\t\t\t\t      [%d] P %6.2f   %s",i+1,prices[i],order[i]);
                }
                printf("\n\n\n\t\t\t\t\t\t     Cost: P %3.2f\n\n",*cost);
                small_line
                printf("\n\n\t\t\t\t\t\t      [1] Order again\n\t\t\t\t\t\t      [2] cancel taking order\n\t\t\t\t\t\t      [3] Delete an order\n\t\t\t\t\t\t      [4] Food\n\t\t\t\t\t\t      [5] Done\n\t\t\t\t\t\t     Enter here: ");
                scanf("%d",&i);

                if(i==2)
                    return 2;
                else if(i==3)
                    delete_order(cost,count_of_order,prices,order);
                else if(i==4)
                    return 4;
                else if(i==5)
                    return 5;
                else if(i<1 || i>5){
                    clear
                    header
                    line
                    printf("\n\n\n\t\t\t\t\t\t\tInvalid\n\n\n\n");
                    click
                }
            }while((i<1 || i>5) || i==3);
        }
        else{
            clear
            header
            line
            printf("\n\n\n\t\t\t\t\t\t\tInvalid\n\n\n\n");
            click
        }

    }while(i==1);

}
//==============================================================================================================================================================
void print_receipt(float cost,int count_of_order,float prices[],char order[][20]){
    important increment=0,i;
    float payment;

    clear
    header
    line
    printf("\n\n\n\t\t\t\t\t\t     Price: P %6.2f\n\n\n\n\n\n",cost);
    small_line
    printf("\n\n\n\t\t\t\t\t\t       Pay: P ");
    scanf("%f",&payment);
    clear
    header
    line
    printf("\n\n\n\t\t\t\t\t\t\tReceipt\n\n\t\t\t\t\t       [Price]            [Order]\n");
        for(i=0;i<count_of_order;i++){
            printf("\n\t\t\t\t\t     [%d] P %6.2f     %s",i+1,prices[i],order[i]);
        }
    printf("\n\n\n\t\t\t\t\t\t   Cost: P %6.2f\n\t\t\t\t\t\tPayment: P %6.2f\n\t\t\t\t\t\t Change: P %6.2f\n\n\n",cost,payment,payment-cost);
    small_line
    prompt
    click
}
//For deleting order=================================================================================================================================================================
void delete_order(float *cost,int *count_of_order,float prices[],char order[][20]){
    important i,choice;
    do{
        do{
            clear
            header
            line
            printf("\n\n\t\t\t\t\t\t   Select which should be deleted:\n");
            for(i=0;i<*count_of_order;i++){
                printf("\n\t\t\t\t\t      [%d] P %6.2f   %s",i+1,prices[i],order[i]);
            }
            printf("\n\n\n\t\t\t\t\t\t     Cost: P %3.2f\n\n",*cost);
            small_line
            printf("\n\n\t\t\t\t\t\t      Enter here: ");
            scanf("%d",&choice);
            if(choice<1 || choice>*count_of_order){
                    clear
                    header
                    line
                    printf("\n\n\n\t\t\t\t\t\t\tInvalid\n\n\n\n");
                    click
            }
        }while(choice<1 || choice>*count_of_order);

        *cost-=prices[choice-1];
        for(i=choice-1;i<*count_of_order-1;i++){
            strcpy(order[i],order[i+1]);
            prices[i]=prices[i+1];
        }
        *count_of_order-=1;
        do{
            clear
            header
            line
            printf("\n\n\n\t\t\t\t\t\t\t Order\n");
            for(i=0;i<*count_of_order;i++){
                printf("\n\t\t\t\t\t      [%d] P %6.2f   %s",i+1,prices[i],order[i]);
            }
            printf("\n\n\n\t\t\t\t\t\t     Cost: P %3.2f\n\n",*cost);
            small_line
            printf("\n\n\t\t\t\t\t\t      [1] Delete again\n\t\t\t\t\t\t      [2] Done\n\n\t\t\t\t\t\t     Enter here: ");
            scanf("%d",&i);
            if(i<1 || i>2){
                clear
                header
                line
                printf("\n\n\n\t\t\t\t\t\t\tInvalid\n\n\n\n");
                click
            }
        }while(i<1 || i>2);
    }while(i==1);
}
