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

    printf("오늘 날짜(YYYY-MM-DD) : ");
    scanf("%d-%d-%d", &year, &month, &day);

    printf("\n사원 등록 후 로그인 해주세요.\n\n");
    printf("추가할 사원의 수 : ");
    scanf("%d", &n1);
    add_employee(n1, year, month, day);

    printf("\n로그인 화면으로 이동합니다.\n\n");
    enter_info(&start,year,month,day);

    printf("처음 시작할 때는 제품 등록부터 하세요.\n");

    while (1) {
        printf("\n\n실행할 메뉴를 선택하세요.\n\n");
        printf("1. 제품 등록 2. 제품 검색 3. 제품 재고 확인 4. 제품 입고 5. 계산 6. 종료 => ");
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
            printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }
}

//로그인 함수
int enter_info(time_t* start, int y, int m, int d) {
    int n1, n3;
    char id1[ID_SIZE], password1[PASSWORD_SIZE];

    printf("\n----- 로그인 화면 -----\n\n");
    printf("사원번호 입력 : ");
    scanf("%d", &n1);
    printf("아이디 : ");
    scanf("%s", id1);
    printf("비밀번호 : ");
    scanf("%s", password1);

    if (strcmp(id1, person[n1 - 1].id) == 0 && strcmp(password1, person[n1 - 1].password) == 0) {
        printf("\n----- 로그인 완료 !! -----\n\n");
       
        system("clear");
        printf("***** 사원 정보 *****\n\n");
        printf("아이디 : %s\n", person[n1 - 1].id);
        printf("이름 : %s\n\n", person[n1 - 1].name);
        printf("*********************\n\n");

        printf("아이디와 이름이 맞으면 확인을 눌러주세요.\n");
        printf("1. 확인 2. 취소 => ");
        scanf("%d", &n3);
        printf("\n\n");

        if (n3 == 1) {
            *start = time(NULL);
        
            system("clear");
            printf("Today : %d - %d - %d\n\n", y,m,d);
            return 0;
        }
    }
    printf("로그인 실패. 다시 시도하세요.\n");

    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
    return enter_info(start,y,m,d);
}

//사원 등록 함수
int add_employee(int n, int y, int m, int d) {
    for (int i = 0; i < n; ++i) {
        printf("\n%d번 사원 등록\n\n", i + 1);
        printf("아이디 : ");
        scanf("%s", person[i].id);
        printf("비밀번호 : ");
        scanf("%s", person[i].password);
        printf("이름 : ");
        scanf("%s", person[i].name);
    }
    system("clear");
    printf("Today : %d - %d - %d\n", y, m, d);
}

//제품 등록 함수
int product_input(int y,int m, int d) {
    int n;
    printf("\n----- 제품 등록 화면 ----- \n\n");
    printf("입력할 제품의 수 : ");
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        printf("\n%d번 제품\n\n", i+1);
        printf("제품명 : ");
        scanf("%s", product[i].name);
        printf("제조회사 : ");
        scanf("%s", product[i].company);
        printf("유통기한 (YYYY-MM-DD) : ");
        scanf("%d-%d-%d", &pdate[i].pyear, &pdate[i].pmonth, &pdate[i].pday);
        printf("19금 물품 (1: 예, 0: 아니오) : ");
        scanf("%d", &product[i].product_19);
        printf("가격 : ");
        scanf("%d", &product[i].price);
        printf("수량 : ");
        scanf("%d", &product[i].inventory);
    }
    
    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
}

//제품 검색 함수
int product_search(int y,int m, int d) {
    char name[PNAME_SIZE];
    char company[PCOMPANY_SIZE];
    printf("\n----- 제품 검색 화면 -----\n\n");
    printf("제품명 : ");
    scanf("%s", name);
    printf("제조회사 :");
    scanf("%s", company);
    printf("\n");

    for (int i = 0; i < PRODUCT; ++i) {
        if ((strcmp(name, product[i].name) == 0) && (strcmp(company, product[i].company)) == 0) {
            printf("\n제품명 : %s\n", product[i].name);
            printf("제조회사 : %s\n", product[i].company);
            printf("유통기한 : %d-%d-%d\n", pdate[i].pyear, pdate[i].pmonth, pdate[i].pday);
            printf("가격 : %d원\n", product[i].price);
            printf("재고 : %d개\n", product[i].inventory);
        }
    }
    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
}

//입고 함수
int product_warehousing(int y, int m, int d) {
    char name[PNAME_SIZE];
    char company[PCOMPANY_SIZE];
    int quantity;
    printf("\n----- 제품 입고 화면 -----\n\n");

    printf("제품명 : ");
    scanf("%s", name);
    printf("제조회사 :");
    scanf("%s", company);
    printf("수량 : ");
    scanf("%d", &quantity);

    for (int i = 0; i < PRODUCT; ++i) {
        if ((strcmp(name, product[i].name) == 0) && (strcmp(company, product[i].company) == 0)) { //제품명과 제조회사가 같으면 재고에 수량 더하기
            product[i].inventory += quantity;
            printf("입고가 완료되었습니다 !\n");
            break;
        }
        else {
            printf("제품을 찾을 수 없습니다. 다시 입력해주세요.\n");
           
            system("clear");
            printf("Today : %d - %d - %d\n\n", y, m, d);

            return product_warehousing(y, m, d);
        }
    }
    
    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
}

//재고 확인 함수
int product_inventory(int y, int m, int d) {
    printf("\n----- 재고 확인 화면 -----\n\n");

    for (int i = 0; i < PRODUCT; ++i) {
        if (product[i].inventory > 0) {
            printf("%d. %s(%s) : ", i + 1, product[i].name, product[i].company);
            for (int j = 0; j < product[i].inventory; ++j) {
                printf("*");
            }
            printf(" (%d개)\n", product[i].inventory);
        }
    }
    
    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
}

int product_pay(int y, int m, int d, int* balance) {
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int total_price = 0;    //총 결제금액
    int cash = 0;               //현금
    char card[20];          //카드번호
    char name[PNAME_SIZE];
    char company[PCOMPANY_SIZE];
    int quantity = 0;           //수량
    int count1 = 0;
    int count2 = 0;

    printf("구매하는 제품의 수 : ");
    scanf("%d", &n1);

    for (int i = 0; i < n1; ++i) {
        printf("제품명 : ");
        scanf("%s", name);
        printf("제조회사 : ");
        scanf("%s", company);
        printf("수량 : ");
        scanf("%d", &quantity);

        for (int j = 0; j < PRODUCT; ++j)
        {
            if (strcmp(name, product[j].name) == 0)
            {
                if (product[j].product_19 == 1)
                {
                    printf("주민등록증 검사를 한 후 확인을 눌러주세요.\n");
                    printf("1을 누르면 확인이 완료됩니다.\n");
                    scanf("%d", &n2);
                    if (n2 != 1) {
                        printf("19금 물품을 빼고 다시 계산해주세요.\n");
                        
                        system("clear");
                        printf("Today : %d - %d - %d\n\n", y, m, d);
                        return product_pay(y, m, d, balance);
                    }
                }

                if ((pdate[j].pyear < y) ||
                    (pdate[j].pyear == y && pdate[j].pmonth < m) ||
                    (pdate[j].pyear == y && pdate[j].pmonth == m && pdate[j].pday < d))
                {
                    printf("%s(%s)은(는) 유통기한이 지났습니다. 계산을 다시 진행해주세요. \n", name, product[j].company);
                    
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

    printf("총 가격 : %d\n", total_price);
    printf("결제 수단 (1. 카드 2. 현금) : ");
    scanf("%d", &n3);

    if (n3 == 1) {
        printf("카드 번호 입력 : ");
        scanf("%s", card);
    }
    else
    {
        printf("받은 현금 : ");
        scanf("%d", &cash);
        printf("거스름돈 : %d\n\n", cash - total_price);
    }
    *balance += total_price;
    printf("결제 완료!\n");

    
    system("clear");
    printf("Today : %d - %d - %d\n\n", y, m, d);
}


int program_end(time_t start, int* balance) {
    time_t end = time(NULL);
    double elapsed_time = difftime(end, start) / 60.0;
    int wage = (int)(elapsed_time * 9600);
    *balance -= wage;

    printf("근무 시간: %.2lf 분\n", elapsed_time);
    printf("일당 : %d원\n", wage);
    printf("잔고: %d원\n", *balance);
}
