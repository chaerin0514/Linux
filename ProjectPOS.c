#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define USER 100
#define ID_SIZE 20
#define PASSWORD_SIZE 20
#define NAME_SIZE 10
#define PRODUCT 100
#define PNAME_SIZE 50
#define PCOMPANY_SIZE 50

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

void clear_screen() {
    system("clear");
}

int enter_info(time_t* start, int, int, int);
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
    enter_info(&start, year, month, day);

    printf("처음 시작할 때는 제품 등록부터 하세요.\n");

    while (1) {
        printf("\n\n실행할 메뉴를 선택하세요.\n\n");
        printf("1. 제품 등록 2. 제품 검색 3. 제품 재고 확인 4. 제품 입고 5. 계산 6. 종료 => ");
        scanf("%d", &n2);

        switch (n2) {
            case 1: product_input(year, month, day); break;
            case 2: product_search(year, month, day); break;
            case 3: product_inventory(year, month, day); break;
            case 4: product_warehousing(year, month, day); break;
            case 5: product_pay(year, month, day, &balance); break;
            case 6: program_end(start, &balance); return 0;
            default: printf("잘못된 입력입니다. 다시 선택하세요.\n"); break;
        }
    }
}

int enter_info(time_t* start, int y, int m, int d) {
    int n1, n3;
    char id1[ID_SIZE], password1[PASSWORD_SIZE];

    printf("\n----- 로그인 화면 -----\n\n");
    printf("사원번호 입력 : "); scanf("%d", &n1);
    printf("아이디 : "); scanf("%s", id1);
    printf("비밀번호 : "); scanf("%s", password1);

    if (strcmp(id1, person[n1 - 1].id) == 0 && strcmp(password1, person[n1 - 1].password) == 0) {
        printf("\n----- 로그인 완료 !! -----\n\n");
        clear_screen();
        printf("***** 사원 정보 *****\n\n아이디 : %s\n이름 : %s\n\n*********************\n\n", person[n1 - 1].id, person[n1 - 1].name);
        printf("아이디와 이름이 맞으면 확인을 눌러주세요.\n1. 확인 2. 취소 => ");
        scanf("%d", &n3);
        if (n3 == 1) {
            *start = time(NULL);
            clear_screen();
            printf("Today : %d - %d - %d\n\n", y, m, d);
            return 0;
        }
    }
    printf("로그인 실패. 다시 시도하세요.\n");
    clear_screen();
    printf("Today : %d - %d - %d\n\n", y, m, d);
    return enter_info(start, y, m, d);
}

int add_employee(int n, int y, int m, int d) {
    for (int i = 0; i < n; ++i) {
        printf("\n%d번 사원 등록\n\n아이디 : ", i + 1);
        scanf("%s", person[i].id);
        printf("비밀번호 : ");
        scanf("%s", person[i].password);
        printf("이름 : ");
        scanf("%s", person[i].name);
    }
    clear_screen();
    printf("Today : %d - %d - %d\n", y, m, d);
    return 0;
}

int product_input(int y, int m, int d) {
    int n;
    printf("\n----- 제품 등록 화면 ----- \n\n입력할 제품의 수 : ");
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        printf("\n%d번 제품\n\n제품명 : ", i+1);
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
    clear_screen();
    printf("Today : %d - %d - %d\n\n", y, m, d);
    return 0;
}

int product_search(int y, int m, int d) {
    char name[PNAME_SIZE];
    char company[PCOMPANY_SIZE];
    int found = 0;

    printf("\n----- 제품 검색 화면 -----\n\n제품명 : ");
    scanf("%s", name);
    printf("제조회사 : ");
    scanf("%s", company);

    for (int i = 0; i < PRODUCT; ++i) {
        if ((strcmp(name, product[i].name) == 0) && (strcmp(company, product[i].company) == 0)) {
            printf("\n제품명 : %s\n제조회사 : %s\n유통기한 : %d-%d-%d\n가격 : %d원\n재고 : %d개\n",
                   product[i].name, product[i].company, pdate[i].pyear, pdate[i].pmonth, pdate[i].pday,
                   product[i].price, product[i].inventory);
            found = 1;
        }
    }
    if (!found) printf("제품을 찾을 수 없습니다.\n");
    clear_screen();
    printf("Today : %d - %d - %d\n\n", y, m, d);
    return 0;
}

int product_warehousing(int y, int m, int d) {
    char name[PNAME_SIZE];
    char company[PCOMPANY_SIZE];
    int quantity, found = 0;

    printf("\n----- 제품 입고 화면 -----\n\n제품명 : ");
    scanf("%s", name);
    printf("제조회사 : ");
    scanf("%s", company);
    printf("수량 : ");
    scanf("%d", &quantity);

    for (int i = 0; i < PRODUCT; ++i) {
        if ((strcmp(name, product[i].name) == 0) && (strcmp(company, product[i].company) == 0)) {
            product[i].inventory += quantity;
            printf("입고가 완료되었습니다 !\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("제품을 찾을 수 없습니다. 다시 입력해주세요.\n");
        return product_warehousing(y, m, d);
    }
    clear_screen();
    printf("Today : %d - %d - %d\n\n", y, m, d);
    return 0;
}

int product_inventory(int y, int m, int d) {
    printf("\n----- 재고 확인 화면 -----\n\n");
    for (int i = 0; i < PRODUCT; ++i) {
        if (product[i].inventory > 0) {
            printf("%d. %s(%s) : ", i + 1, product[i].name, product[i].company);
            for (int j = 0; j < product[i].inventory; ++j) printf("*");
            printf(" (%d개)\n", product[i].inventory);
        }
    }
    clear_screen();
    printf("Today : %d - %d - %d\n\n", y, m, d);
    return 0;
}

int product_pay(int y, int m, int d, int* balance) {
    int n1, n2, n3, total_price = 0, cash = 0, quantity = 0;
    char name[PNAME_SIZE], company[PCOMPANY_SIZE], card[20];

    printf("구매하는 제품의 수 : "); scanf("%d", &n1);

    for (int i = 0; i < n1; ++i) {
        printf("제품명 : "); scanf("%s", name);
        printf("제조회사 : "); scanf("%s", company);
        printf("수량 : "); scanf("%d", &quantity);

        for (int j = 0; j < PRODUCT; ++j) {
            if (strcmp(name, product[j].name) == 0 && strcmp(company, product[j].company) == 0) {
                if (product[j].product_19 == 1) {
                    printf("주민등록증 검사를 완료했으면 1을 누르세요: ");
                    scanf("%d", &n2);
                    if (n2 != 1) {
                        printf("19금 제품 제외 후 다시 계산해주세요.\n");
                        clear_screen();
                        return product_pay(y, m, d, balance);
                    }
                }
                if ((pdate[j].pyear < y) ||
                    (pdate[j].pyear == y && pdate[j].pmonth < m) ||
                    (pdate[j].pyear == y && pdate[j].pmonth == m && pdate[j].pday < d)) {
                    printf("%s(%s)의 유통기한이 지났습니다. 다시 진행해주세요.\n", name, company);
                    clear_screen();
                    return product_pay(y, m, d, balance);
                }
                product[j].inventory -= quantity;
                total_price += product[j].price * quantity;
                break;
            }
        }
    }

    clear_screen();
    printf("Today : %d - %d - %d\n\n총 가격 : %d\n결제 수단 (1. 카드 2. 현금) : ", y, m, d, total_price);
    scanf("%d", &n3);

    if (n3 == 1) {
        printf("카드 번호 입력 : "); scanf("%s", card);
    } else {
        printf("받은 현금 : "); scanf("%d", &cash);
        printf("거스름돈 : %d\n\n", cash - total_price);
    }
    *balance += total_price;
    printf("결제 완료!\n");
    clear_screen();
    printf("Today : %d - %d - %d\n\n", y, m, d);
    return 0;
}

int program_end(time_t start, int* balance) {
    time_t end = time(NULL);
    double elapsed_time = difftime(end, start) / 60.0;
    int wage = (int)(elapsed_time * 9600);
    *balance -= wage;

    printf("근무 시간: %.2lf 분\n일당 : %d원\n잔고: %d원\n", elapsed_time, wage, *balance);
    return 0;
}
