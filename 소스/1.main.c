#include "common.h"
#include "Cus_AND_DVD_RENT_Manager.h"
#include "FILE_LOAD, SAVE.h"
#include "screenOut.h"

enum{CUS_REGIST = 1, CUS_SEARCH, DVD_REGIST, DVD_SEARCH, 
		RENT_AND_RETURN, SEARCHING, SAVE, BACKUP, QUIT};

int main(void)
{
	int inputMenu = 0;

	FILE_SHOW(); // ���Ͽ� ����� ��� ���
	FILE_LOAD(); // ���� �ҷ�����

	while (1)
	{	
		ShowMenu(); // �� ���α׷��� ����ϱ� ���� �޴� ���
		scanf("%d", &inputMenu);
		getchar();

		switch (inputMenu)
		{
		case CUS_REGIST:
			Register_Customer(); // ȸ�����	 		
			break;

		case CUS_SEARCH:
			Search_CusInfo(); // ȸ�� �˻�
			break;

		case DVD_REGIST:
			Regist_DVD(); // DVD ���
			break;

		case DVD_SEARCH:
			Search_DVDInfo(); // DVD ��ȸ
			break;

		case RENT_AND_RETURN:
			Show_RENT_AND_RETURN(); // �뿩 / �ݳ� �޴�ȭ�� ���
			break;

		case SEARCHING:
			Show_SEACHING(); // ��ȸ���� �޴� ���
			break;
		
		case SAVE:
			FILE_SAVE(); // ���� ����
			break;

		case BACKUP:
			FILE_BACKUP(); // ���� ���
			break;
		}		

		if (inputMenu == QUIT)
		{
			puts("�̿����ּż� �����մϴ�.");
			break;
		}
	}

	return 0;
}