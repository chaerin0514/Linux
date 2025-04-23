#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include <Windows.h>

#define USER 100
#define ID_SIZE 20
#define PASSWORD_SIZE 20
#define NAME_SIZE 10
#define PRODUCT 100
#define PNAME_SIZE 50
#define PCOMPANY_SIZE 50
#define PDATE_SIZE 10

struct Person {
    char id[ID_SIZE];
    char password[PASSWORD_SIZE];
    char name[NAME_SIZE];
};
struct Person person[USER];

struct Product {
    char name[PNAME_SIZE];
    char company[PCOMPANY_SIZE];
    int product_19;
    int price;
    int inventory;
};
struct Product product[PRODUCT];

struct Pdate {
    int pyear;
    int pmonth;
    int pday;
};
struct Pdate pdate[PRODUCT];

int enter_info(time_t* start,int,int,int);
int add_employee(int, int, int, int);
int product_input(int,int,int);
int product_inventory(int,int,int);
int product_warehousing(int, int, int);
int product_search(int, int, int);
int product_pay(int, int, int, int*);
int program_end(time_t start, int*);

int main() {
    int balance = 1234000;
    int n1 = 0, n2 = 0;
    int year, month, day;
    time_t start = 0;

    printf("���� ��¥(YYYY-MM-DD) : ");
    scanf("%d-%d-%d", &year, &month, &day);

    printf("\n��� ��� �� �α��� ���ּ���.\n\n");
    printf("�߰��� ����� �� : ");
    scanf("%d", &n1);
    add_employee(n1, year, month, day);

    printf("\n�α��� ȭ������ �̵��մϴ�.\n\n");
    enter_info(&start,year,month,day);

    printf("ó�� ������ ���� ��ǰ ��Ϻ��� �ϼ���.\n");

    while (1) {
        printf("\n\n������ �޴��� �����ϼ���.\n\n");
        printf("1. ��ǰ ��� 2. ��ǰ �˻� 3. ��ǰ ��� Ȯ�� 4. ��ǰ �԰� 5. ��� 6. ���� => ");
        scanf("%d", &n2);

        switch (n2) {
        case 1:
            product_input(year, month, day);
            break;
        case 2:
            product_search(year, month, day);
            break;
        case 3:
            product_inventory(year, month, day);
            break;
        case 4:
            product_warehousing(year, month,day);
            break;
        case 5:
            product_pay(year, month, day, &balance);
            break;
        case 6:
            program_end(start, &balance);
            return 0;
        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �����ϼ���.\n");
        }
    }
}

//�α��� �Լ�
int enter_info(time_t* start, int y, int m, int d) {
    int n1, n3;
    char id1[ID_SIZE], password1[PASSWORD_SIZE];

    printf("\n----- �α��� ȭ�� -----\n\n");
    printf("�����ȣ �Է� : ");
    scanf("%d", &n1);
    printf("���̵� : ");
    scanf("%s", id1);
    printf("��й�ȣ : ");
    scanf("%s", password1);

    if (strcmp(id1, person[n1 - 1].id) == 0 && strcmp(password1, person[n1 - 1].password) == 0) {
        printf("\n----- �α��� �Ϸ� !! -----\n\n");
       
        system("clear");
        printf("***** ��� ���� *****\n\n");
        printf("���̵� : %s\n", person[n1 - 1].id);
        printf("�̸� : %s\n\n", person[n1 - 1].name);
        printf("*********************\n\n");

        printf("���̵�� �̸��� ������ Ȯ���� �����ּ���.\n");
        printf("1. Ȯ�� 2. ��� => ");
        scanf("%d", &n3);
        printf("\n\n");

        if (n3 == 1) {
            *start = time(NULL);
        
            system("clear");
            printf("Today : %d - %d - %d\n\n", y,m,d);
            return 0;
        }
    }
    printf("�α��� ����. �ٽ� �õ��ϼ���.\n");

    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
    return enter_info(start,y,m,d);
}

//��� ��� �Լ�
int add_employee(int n, int y, int m, int d) {
    for (int i = 0; i < n; ++i) {
        printf("\n%d�� ��� ���\n\n", i + 1);
        printf("���̵� : ");
        scanf("%s", person[i].id);
        printf("��й�ȣ : ");
        scanf("%s", person[i].password);
        printf("�̸� : ");
        scanf("%s", person[i].name);
    }
    system("clear");
    printf("Today : %d - %d - %d\n", y, m, d);
}

//��ǰ ��� �Լ�
int product_input(int y,int m, int d) {
    int n;
    printf("\n----- ��ǰ ��� ȭ�� ----- \n\n");
    printf("�Է��� ��ǰ�� �� : ");
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        printf("\n%d�� ��ǰ\n\n", i+1);
        printf("��ǰ�� : ");
        scanf("%s", product[i].name);
        printf("����ȸ�� : ");
        scanf("%s", product[i].company);
        printf("������� (YYYY-MM-DD) : ");
        scanf("%d-%d-%d", &pdate[i].pyear, &pdate[i].pmonth, &pdate[i].pday);
        printf("19�� ��ǰ (1: ��, 0: �ƴϿ�) : ");
        scanf("%d", &product[i].product_19);
        printf("���� : ");
        scanf("%d", &product[i].price);
        printf("���� : ");
        scanf("%d", &product[i].inventory);
    }
    
    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
}

//��ǰ �˻� �Լ�
int product_search(int y,int m, int d) {
    char name[PNAME_SIZE];
    char company[PCOMPANY_SIZE];
    printf("\n----- ��ǰ �˻� ȭ�� -----\n\n");
    printf("��ǰ�� : ");
    scanf("%s", name);
    printf("����ȸ�� :");
    scanf("%s", company);
    printf("\n");

    for (int i = 0; i < PRODUCT; ++i) {
        if ((strcmp(name, product[i].name) == 0) && (strcmp(company, product[i].company)) == 0) {
            printf("\n��ǰ�� : %s\n", product[i].name);
            printf("����ȸ�� : %s\n", product[i].company);
            printf("������� : %d-%d-%d\n", pdate[i].pyear, pdate[i].pmonth, pdate[i].pday);
            printf("���� : %d��\n", product[i].price);
            printf("��� : %d��\n", product[i].inventory);
        }
    }
    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
}

//�԰� �Լ�
int product_warehousing(int y, int m, int d) {
    char name[PNAME_SIZE];
    char company[PCOMPANY_SIZE];
    int quantity;
    printf("\n----- ��ǰ �԰� ȭ�� -----\n\n");

    printf("��ǰ�� : ");
    scanf("%s", name);
    printf("����ȸ�� :");
    scanf("%s", company);
    printf("���� : ");
    scanf("%d", &quantity);

    for (int i = 0; i < PRODUCT; ++i) {
        if ((strcmp(name, product[i].name) == 0) && (strcmp(company, product[i].company) == 0)) { //��ǰ��� ����ȸ�簡 ������ ��� ���� ���ϱ�
            product[i].inventory += quantity;
            printf("�԰� �Ϸ�Ǿ����ϴ� !\n");
            break;
        }
        else {
            printf("��ǰ�� ã�� �� �����ϴ�. �ٽ� �Է����ּ���.\n");
           
            system("clear");
            printf("Today : %d - %d - %d\n\n", y, m, d);

            return product_warehousing(y, m, d);
        }
    }
    
    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
}

//��� Ȯ�� �Լ�
int product_inventory(int y, int m, int d) {
    printf("\n----- ��� Ȯ�� ȭ�� -----\n\n");

    for (int i = 0; i < PRODUCT; ++i) {
        if (product[i].inventory > 0) {
            printf("%d. %s(%s) : ", i + 1, product[i].name, product[i].company);
            for (int j = 0; j < product[i].inventory; ++j) {
                printf("*");
            }
            printf(" (%d��)\n", product[i].inventory);
        }
    }
    
    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
}

int product_pay(int y, int m, int d, int* balance) {
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int total_price = 0;    //�� �����ݾ�
    int cash = 0;               //����
    char card[20];          //ī���ȣ
    char name[PNAME_SIZE];
    char company[PCOMPANY_SIZE];
    int quantity = 0;           //����
    int count1 = 0;
    int count2 = 0;

    printf("�����ϴ� ��ǰ�� �� : ");
    scanf("%d", &n1);

    for (int i = 0; i < n1; ++i) {
        printf("��ǰ�� : ");
        scanf("%s", name);
        printf("����ȸ�� : ");
        scanf("%s", company);
        printf("���� : ");
        scanf("%d", &quantity);

        for (int j = 0; j < PRODUCT; ++j)
        {
            if (strcmp(name, product[j].name) == 0)
            {
                if (product[j].product_19 == 1)
                {
                    printf("�ֹε���� �˻縦 �� �� Ȯ���� �����ּ���.\n");
                    printf("1�� ������ Ȯ���� �Ϸ�˴ϴ�.\n");
                    scanf("%d", &n2);
                    if (n2 != 1) {
                        printf("19�� ��ǰ�� ���� �ٽ� ������ּ���.\n");
                        
                        system("clear");
                        printf("Today : %d - %d - %d\n\n", y, m, d);
                        return product_pay(y, m, d, balance);
                    }
                }

                if ((pdate[j].pyear < y) ||
                    (pdate[j].pyear == y && pdate[j].pmonth < m) ||
                    (pdate[j].pyear == y && pdate[j].pmonth == m && pdate[j].pday < d))
                {
                    printf("%s(%s)��(��) ��������� �������ϴ�. ����� �ٽ� �������ּ���. \n", name, product[j].company);
                    
                    system("clear");
                    printf("Today : %d - %d - %d\n\n", y, m, d);
                    return product_pay(y, m, d, balance);
                }
                product[j].inventory -= quantity;
                total_price += product[j].price * quantity;
                break;
            }
        }
    }
    
    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);

    printf("�� ���� : %d\n", total_price);
    printf("���� ���� (1. ī�� 2. ����) : ");
    scanf("%d", &n3);

    if (n3 == 1) {
        printf("ī�� ��ȣ �Է� : ");
        scanf("%s", card);
    }
    else
    {
        printf("���� ���� : ");
        scanf("%d", &cash);
        printf("�Ž����� : %d\n\n", cash - total_price);
    }
    *balance += total_price;
    printf("���� �Ϸ�!\n");

    
    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
}


int program_end(time_t start, int* balance) {
    time_t end = time(NULL);
    double elapsed_time = difftime(end, start) / 60.0;
    int wage = (int)(elapsed_time * 9600);
    *balance -= wage;

    printf("�ٹ� �ð�: %.2lf ��\n", elapsed_time);
    printf("�ϴ� : %d��\n", wage);
    printf("�ܰ�: %d��\n", *balance);
}
