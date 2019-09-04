#include "common.h"
#include "RentInfo.h"
#include "cusInfoAccess.h"
#include "dvdInfoAccess.h"
#include "RentInfoAccess.h"
#include "screenOut.h"


enum { CHARGING_DELAYFEE = 1, RECIEVE_DELAYFEE, QUIT };

// 회원등록
void Register_Customer(void)
{			
	char ID[ID_LEN];
	char name[NAME_LEN];
	char phonenum[PHONE_LEN];
	int delay_fee = 0;

	printf("ID 입력 : ");
	gets(ID);	

	if (IsregistID(ID))
	{
		puts("해당 ID는 사용중입니다.");
		getchar();
		return;
	}

	printf("이름 입력 : ");
	gets(name);

	printf("전화번호 입력 : ");
	gets(phonenum);

	if (!AddCusInfo(ID, name, phonenum, delay_fee))
	{
		puts("고객정보 저장실패");
		getchar();
		return;
	}

	puts("회원가입 완료");
	getchar();
}

// 회원 검색
void Search_CusInfo(void)
{
	cusInfo *pCus;
	char ID[ID_LEN];

	printf("조회할 고객 ID 입력 : ");
	gets(ID);	

	pCus = GetCusPtrByID(ID);
	if (pCus == 0)
	{
		puts("등록되지 않은 ID입니다.\n");		
		getchar();
		return;
	}
		
	ShowCustomerInfo(pCus);
	getchar();
}

// DVD 등록
void Regist_DVD(void)
{
	char ISBN[ISBN_LEN], title[TITLE_LEN];
	int genre, rentstate;

	printf("DVD ISBN 입력 : ");
	gets(ISBN);

	if (IsRegistISBN(ISBN))
	{
		puts("해당 ISBN는 사용중입니다.");
		getchar();
		return;
	}

	printf("타이틀 입력 : ");
	gets(title);

	printf("장르 입력 (액션 : 1, 코믹 : 2, SF : 3, 로맨틱 : 4)");
	scanf("%d", &genre);	
	rewind(stdin);

	rentstate = RETURNED;

	if (!AddDVDInfo(ISBN, title, genre, rentstate))
	{
		puts("DVD정보 저장실패");
		return;
	}

	puts("DVD 등록완료");
	getchar();
}

// DVD 조회
void Search_DVDInfo(void)
{
	dvdInfo *pDVD;
	char ISBN[ISBN_LEN];

	printf("조회할 DVD ISBN 입력 : ");
	gets(ISBN);

	pDVD = GetDVDPtrByISBN(ISBN);
	if (pDVD == 0)
	{
		puts("등록되지 않은 ISBN입니다.");		
		getchar();
		return;
	}

	ShowDVDInfo(pDVD);
	getchar();
}

// DVD 대여
void Rent_DVD(void) 
{
	char ISBN[ISBN_LEN];
	int registDVD; // DVD확인
	int registcus; // 고객확인
	int rentstate; // 대여확인
	char ID[ID_LEN]; // 대여자 ID
	unsigned int rentDay; // 대여날짜

	// 대여할 DVD의 ISBN 등록여부 체크
	printf("대여 DVD ISBN 입력 : ");
	gets(ISBN);

	registDVD = IsRegistISBN(ISBN);
	if (registDVD == 0)
	{
		puts("등록되지 않은 ISBN입니다.");
		getchar();
		return;
	}

	// 대여가능 여부 체크
	rentstate = Get_RENT_STATE_DVD(ISBN);
	if (rentstate == RENTED)
	{
		puts("대여중인 DVD입니다.");
		getchar();
		return;
	}

	// 대여절차 진행
	puts("대여가능, 대여진행합니다.");

	printf("대여고객 ID : ");
	gets(ID);

	// 고객 ID 체크
	registcus = IsregistID(ID);
	if (registcus == 0)
	{
		puts("가입되지 않은 고객입니다.");
		getchar();
		return;
	}

	printf("대여날짜(예 : 20190320) : ");
	scanf("%u", &rentDay);
	getchar();

	rentstate = Set_Rent_DVD(ISBN);

	// 이력관리를 분리한 RentInfoAccess.c에 있는 AddRentList()함수 사용
	AddRentInfo(ISBN, ID, rentDay, rentstate);

	puts("대여 완료");
	getchar();
}

// DVD 반납
void Return_DVD(void) 
{
	char ISBN[ISBN_LEN];
	int registDVD; // DVD확인
	int registcus; // 고객확인
	int rentstate; // 반납확인
	char ID[ID_LEN]; // 반납자 ID
	unsigned int rentDay; // 반납날짜

	printf("반납 DVD ISBN 입력 : ");
	gets(ISBN);

	// 입력된 ISBN 등록여부 확인
	registDVD = IsRegistISBN(ISBN);
	if (registDVD == 0)
	{
		puts("등록되지 않은 ISBN입니다.");
		getchar();
		return;
	}

	// 반납가능 여부 확인
	rentstate = Get_RENT_STATE_DVD(ISBN);
	if (rentstate == RETURNED)
	{
		puts("대여되지 않은 DVD이므로 반납불가");
		getchar();
		return;
	}

	// 반납절차 진행
	puts("반납가능, 반납진행합니다.");

	printf("반납고객 ID : ");
	gets(ID);

	// 고객 ID 체크
	registcus = IsregistID(ID);
	if (registcus == 0)
	{
		puts("가입되지 않은 고객입니다.");
		getchar();
		return;
	}

	printf("반납날짜(예 : 20190320) : ");
	scanf("%u", &rentDay);
	getchar();

	// 반납절차 진행
	rentstate = Set_Return_DVD(ISBN);

	AddReturnInfo(ISBN, ID, rentDay, rentstate);

	puts("반납 완료");
	getchar();
}

// 특정 DVD를 대여한 모든 고객 정보
void Show_DVDRent_ALL_CusInfo(void) 
{
	dvdInfo *ptrDVDInfo; // DVD 정보
	char ISBN[ISBN_LEN];

	printf("대여이력을 조회할 DVD ISBN 입력 : ");
	gets(ISBN);

	ptrDVDInfo = GetDVDPtrByISBN(ISBN);
	if (ptrDVDInfo == 0)
	{
		puts("존재하지 않는 DVD ISBN입니다.");
		getchar();
		return;
	}

	Print_Out_Rent_All_CusInfo(ISBN); // 특정 ISBN의 DVD 모든 대여고객 정보출력

	puts("조회 완료");
	getchar();
}

// 특정고객의 기간별 대여이력 정보
void ShowDVD_CusAllRentInfo(void)
{
	cusInfo *pcus;
	char ID[ID_LEN];
	unsigned int Rent_start, Rent_end;

	printf("검색할 고객 ID : ");
	gets(ID);

	pcus = GetCusPtrByID(ID);
	if (pcus == 0)
	{
		puts("가입된 고객이 아닙니다.");
		getchar();
		return;
	}

	printf("검색할 기간정보 입력 : ");
	scanf("%u %u", &Rent_start, &Rent_end);

	if (Rent_start > Rent_end)
	{
		puts("기간 정보가 잘못 입력됨");
		getchar();
		return;
	}

	Print_Out_Cus_All_RentInfo(ID, Rent_start, Rent_end); // 특정고객의 기간별 대여이력 정보출력

	puts("조회 완료");
	getchar();
}

// 고객별 DVD연체정보 조회
void ShowCus_DelayFee_ByOverdue(void)
{
	char ID[ID_LEN];
	int menu;

	while (1)
	{
		puts("-------메뉴 선택-------");
		puts("1. 특정고객의 연체일에 따른 연체료 부과");
		puts("2. 특정고객의 연체료 납부진행");
		puts("3. 조회선택메뉴로 이동");
		printf(">> 선택 : ");
		scanf("%d", &menu);
		getchar();

		switch (menu)
		{
		case CHARGING_DELAYFEE:
			printf("검색할 고객 ID 입력 : ");
			gets(ID);
			
			if (GetCusPtrByID(ID) == 0)
			{
				puts("가입된 고객이 아닙니다.");
				getchar();
				return;
			}

			Charging_Delay_Fee(ID); // 특정고객의 연체일에 따른 연체료 부과 절차진행
			break;

		case RECIEVE_DELAYFEE:
			Recieve_DelayFee(); // 특정고객의 연체료 납부진행
			break;
		}

		if (menu == QUIT)
		{
			puts("조회선택메뉴 화면으로 이동\n\n");
			break;
		}
	}
}