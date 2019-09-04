#include "common.h"
#include "Cus_AND_DVD_RENT_Manager.h"
#include "FILE_LOAD, SAVE.h"
#include "screenOut.h"

enum{CUS_REGIST = 1, CUS_SEARCH, DVD_REGIST, DVD_SEARCH, 
		RENT_AND_RETURN, SEARCHING, SAVE, BACKUP, QUIT};

int main(void)
{
	int inputMenu = 0;

	FILE_SHOW(); // 파일에 저장된 목록 출력
	FILE_LOAD(); // 파일 불러오기

	while (1)
	{	
		ShowMenu(); // 고객 프로그램을 사용하기 위한 메뉴 출력
		scanf("%d", &inputMenu);
		getchar();

		switch (inputMenu)
		{
		case CUS_REGIST:
			Register_Customer(); // 회원등록	 		
			break;

		case CUS_SEARCH:
			Search_CusInfo(); // 회원 검색
			break;

		case DVD_REGIST:
			Regist_DVD(); // DVD 등록
			break;

		case DVD_SEARCH:
			Search_DVDInfo(); // DVD 조회
			break;

		case RENT_AND_RETURN:
			Show_RENT_AND_RETURN(); // 대여 / 반납 메뉴화면 출력
			break;

		case SEARCHING:
			Show_SEACHING(); // 조회선택 메뉴 출력
			break;
		
		case SAVE:
			FILE_SAVE(); // 파일 저장
			break;

		case BACKUP:
			FILE_BACKUP(); // 파일 백업
			break;
		}		

		if (inputMenu == QUIT)
		{
			puts("이용해주셔서 감사합니다.");
			break;
		}
	}

	return 0;
}