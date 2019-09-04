#include "common.h"
#include "RentInfo.h"
#include "Cus_AND_DVD_RENT_Manager.h"
#include "screenOut.h"

enum { RENT = 1, RETURN, QUIT, RENT_DVD_CUSSEARCH, RENTDATE_CUS_DVDSEARCH, OVERDUE_CUS_SEARCH};

// 고객 프로그램을 사용하기 위한 메뉴 출력
void ShowMenu(void)
{
	system("cls");

	puts("-------메뉴 선택-------");
	puts(" 1. 신규가입");
	puts(" 2. 회원조회");
	puts(" 3. DVD등록");
	puts(" 4. DVD조회");
	puts(" 5. 대여 / 반납");
	puts(" 6. 조회");
	puts(" 7. SAVE");
	puts(" 8. BACK_UP");
	puts(" 9. 종료");
	printf(">> 선택 : ");
}

// 고객정보 출력
void ShowCustomerInfo(cusInfo * pCus)
{
	puts("");
	printf("ID : %s\n", pCus->ID);
	printf("이름 : %s\n", pCus->name);
	printf("전화번호 : %s\n", pCus->phoneNum);
}

// DVD정보 출력
void ShowDVDInfo(dvdInfo * pDVD)
{
	puts("");
	printf("DVD ISBN : %s\n", pDVD->ISBN);
	printf("타이틀 : %s\n", pDVD->title);
	printf("장르 : "); ShowGenre(pDVD->genre); 
	printf("\n");
}

// DVD장르 선택
void ShowGenre(int gen)
{
	switch (gen)
	{
	case ACTION:
		printf("액션");
		break;

	case COMIC:
		printf("코믹");
		break;

	case SF:
		printf("SF");
		break;

	case ROMANTIC:
		printf("로맨스");
		break;
	}
}

// 대여 / 반납 메뉴화면 출력
void Show_RENT_AND_RETURN(void)
{
	int menu = 0;

	while (1)
	{
		printf("\n선택할 메뉴 번호 입력(대여 : 1, 반납 : 2, 메인메뉴 : 3) >>");
		scanf("%d", &menu);
		getchar();

		switch (menu)
		{
		case RENT:
			Rent_DVD();
			break;

		case RETURN:
			Return_DVD();
			break;
		}

		if (menu == QUIT)
		{
			printf("메인메뉴 화면으로 이동");
			getchar();
			break;			
		}
	}
}


// 대여정보 출력
void ShowRentInfo(cusInfo *Cus)
{
	printf("ID : %s\n", Cus->ID);
	printf("이름 : %s\n", Cus->name);
	printf("전화번호 : %s\n", Cus->phoneNum);
}

// 조회선택 메뉴 출력
void Show_SEACHING(void)
{
	int menu = 0;

	while (1)
	{
		puts("-------메뉴 선택-------");
		puts(" 3. 메인메뉴로 이동");
		puts(" 4. DVD대여 고객정보 조회");
		puts(" 5. 고객ㆍ기간별 대여DVD정보 조회");
		puts(" 6. 고객별 DVD연체정보 조회");		
		printf(">> 선택 : ");
		scanf("%d", &menu);
		getchar();

		switch (menu)
		{
		case RENT_DVD_CUSSEARCH:
			Show_DVDRent_ALL_CusInfo();
			break;

		case RENTDATE_CUS_DVDSEARCH:
			ShowDVD_CusAllRentInfo();
			break;

		case OVERDUE_CUS_SEARCH:
			ShowCus_DelayFee_ByOverdue();
			break;
		}

		if (menu == QUIT)
		{
			printf("\n메인메뉴 화면으로 이동");
			getchar();
			break;
		}
	}	
}

// 특정 ISBN의 DVD 대여고객 정보출력
void ShowCustomerInfoContinue(cusInfo * pCus)
{
	printf("ID : %s\n", pCus->ID);
	printf("이름 : %s\n", pCus->name);
	printf("전화번호 : %s\n", pCus->phoneNum);
	puts("");
}

// 특정고객의 기간별 대여이력 정보출력
void ShowDVDRentInfo(RentInfo dvd)
{
	puts("");
	printf("ISBN : %s\n", dvd.ISBN);
	printf("대여일 : %u\n", dvd.rentDay);
}