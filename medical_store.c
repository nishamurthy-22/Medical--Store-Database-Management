#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct customer
{
    char customer_name[20];
    int customer_id;
    char purchase_item[20];
    int product_price;
    struct customer *link;
};

struct customer *start = NULL;

struct customer *createnode()
{
    return ((struct customer *)malloc(sizeof(struct customer)));
}

void writeFile(FILE *fptr, struct customer *start)
{
    struct customer *head;
    head = start;
    if (head->link != NULL)
    {
        fprintf(fptr, "customer_name: %s\ncustomer_id: %d\npurchase_item: %s\nproduct_price: %d\n\n", head->customer_name, head->customer_id, head->purchase_item, head->product_price);
        writeFile(fptr, head->link);
    }
    else
    {
        fprintf(fptr, "customer_name: %s\ncustomer_id: %d\npurchase_item: %s\nproduct_price: %d\n\n", head->customer_name, head->customer_id, head->purchase_item, head->product_price);
        fclose(fptr);
    }
}

void readFile()
{
    FILE *fPtr;

    char buf[1000];
    int r = 0;

    fPtr = fopen("text.txt", "r");

    if (fPtr == NULL)
    {
        printf("Unable to open file.\n");
    }
    printf("\n\n--------------READING FROM text.txt FILE---------------\n");
    while (fgets(buf, 1000, fPtr) != NULL)
    {
        r = strlen(buf);
        buf[r - 1] = buf[r - 1] == '\n' ? '\0' : buf[r - 1];
        printf("%s\n", buf);
    }
    fclose(fPtr);
}

void display(struct customer *start)
{
    struct customer *temp;
    temp = start;
    while (temp != NULL)
    {
        printf("%s\n", temp->customer_name);
        printf("%d\n", temp->customer_id);
        printf("%s\n", temp->purchase_item);
        printf("%d\n", temp->product_price);

        temp = temp->link;
    }

}

void insert()
{
    struct customer *temp, *nn;
    nn = createnode();
    temp = start;
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    printf("Enter First name:\n");
    scanf("%s", &nn->customer_name);
    printf("Enter customer_id:\n");
    scanf("%d", &nn->customer_id);
    printf("Enter the name of the product purchase:\n");
    scanf("%s", &nn->purchase_item);
    printf("Enter the price of the product purchased:\n");
    scanf("%d", &nn->product_price);
    temp->link = nn;
    nn->link = NULL;
   
    FILE *fp = fopen("text.txt", "a");
    writeFile(fp, nn);
}

struct customer *create()
{
    struct customer *temp, *nn;
    if (start != NULL)
        insert();
    else
    {
        nn = createnode();
        start = nn;
        temp = start;
        printf("Enter First name:\n");
        scanf("%s", &nn->customer_name);
        printf("Enter customer_id:\n");
        scanf("%d", &nn->customer_id);
        printf("Enter the name of the product purchase:\n");
        scanf("%s", &nn->purchase_item);
        printf("Enter the price of the product purchased:\n");
        scanf("%d", &nn->product_price);
        nn->link = NULL;
        

        FILE *fp = fopen("text.txt", "a");
        writeFile(fp, nn);
    }
}
void search()
{
    struct customer *temp;
    int f;
    temp = start;
    printf("Enter customer id to be searched:\n");
    scanf("%d", &f);
    while ((temp->customer_id != f))
    {
        temp = temp->link;
    }
    printf("%s\n", temp->customer_name);
    printf("%d\n", temp->customer_id);
    printf("%s\n", temp->purchase_item);
    printf("%d\n", temp->product_price);
}

void del()
{
    struct customer *pretemp, *temp;
    int f;
    temp = start;
    pretemp = start->link;
    printf("Enter customr id :");
    scanf("%d", &f);
    while (temp != NULL)
    {
        if ((pretemp->customer_id== f))
        {
            printf("%s ", pretemp->customer_name);
            printf("%d ", pretemp->customer_id);
            printf("%s\n", pretemp->purchase_item);
            printf("%d\n", pretemp->product_price);
            temp->link = pretemp->link;
            free(pretemp);
            break;
        }
        else
        {
            temp = temp->link;
            pretemp = pretemp->link;
        }
        
    }
}

int main()
{
    int op, ch;
    do
    {
        printf("-------Welcome--------\n ");
        printf("1.Create\n2.Insert\n3.Display\n4.Read file\n5.Search\n6.Delete\n");
        printf("Enter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            create();
            break;
        case 2:
            insert();
            break;
        case 3:
            display(start);
            break;
        case 4:
            readFile();
            break;
        case 5:
            search();
            break;
        case 6:
            del();
            break;
        }
        printf("Do you want to quit ? 0 for no / 1 for yes:");
        scanf("%d", &op);
    } while (op != 1);
    return 0;
}