#include "common.h"
#include "RentInfo.h"
#include "Cus_AND_DVD_RENT_Manager.h"
#include "screenOut.h"

enum { RENT = 1, RETURN, QUIT, RENT_DVD_CUSSEARCH, RENTDATE_CUS_DVDSEARCH, OVERDUE_CUS_SEARCH};

// �� ���α׷��� ����ϱ� ���� �޴� ���
void ShowMenu(void)
{
	system("cls");

	puts("-------�޴� ����-------");
	puts(" 1. �ű԰���");
	puts(" 2. ȸ����ȸ");
	puts(" 3. DVD���");
	puts(" 4. DVD��ȸ");
	puts(" 5. �뿩 / �ݳ�");
	puts(" 6. ��ȸ");
	puts(" 7. SAVE");
	puts(" 8. BACK_UP");
	puts(" 9. ����");
	printf(">> ���� : ");
}

// ������ ���
void ShowCustomerInfo(cusInfo * pCus)
{
	puts("");
	printf("ID : %s\n", pCus->ID);
	printf("�̸� : %s\n", pCus->name);
	printf("��ȭ��ȣ : %s\n", pCus->phoneNum);
}

// DVD���� ���
void ShowDVDInfo(dvdInfo * pDVD)
{
	puts("");
	printf("DVD ISBN : %s\n", pDVD->ISBN);
	printf("Ÿ��Ʋ : %s\n", pDVD->title);
	printf("�帣 : "); ShowGenre(pDVD->genre); 
	printf("\n");
}

// DVD�帣 ����
void ShowGenre(int gen)
{
	switch (gen)
	{
	case ACTION:
		printf("�׼�");
		break;

	case COMIC:
		printf("�ڹ�");
		break;

	case SF:
		printf("SF");
		break;

	case ROMANTIC:
		printf("�θǽ�");
		break;
	}
}

// �뿩 / �ݳ� �޴�ȭ�� ���
void Show_RENT_AND_RETURN(void)
{
	int menu = 0;

	while (1)
	{
		printf("\n������ �޴� ��ȣ �Է�(�뿩 : 1, �ݳ� : 2, ���θ޴� : 3) >>");
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
			printf("���θ޴� ȭ������ �̵�");
			getchar();
			break;			
		}
	}
}


// �뿩���� ���
void ShowRentInfo(cusInfo *Cus)
{
	printf("ID : %s\n", Cus->ID);
	printf("�̸� : %s\n", Cus->name);
	printf("��ȭ��ȣ : %s\n", Cus->phoneNum);
}

// ��ȸ���� �޴� ���
void Show_SEACHING(void)
{
	int menu = 0;

	while (1)
	{
		puts("-------�޴� ����-------");
		puts(" 3. ���θ޴��� �̵�");
		puts(" 4. DVD�뿩 ������ ��ȸ");
		puts(" 5. �����Ⱓ�� �뿩DVD���� ��ȸ");
		puts(" 6. ���� DVD��ü���� ��ȸ");		
		printf(">> ���� : ");
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
			printf("\n���θ޴� ȭ������ �̵�");
			getchar();
			break;
		}
	}	
}

// Ư�� ISBN�� DVD �뿩�� �������
void ShowCustomerInfoContinue(cusInfo * pCus)
{
	printf("ID : %s\n", pCus->ID);
	printf("�̸� : %s\n", pCus->name);
	printf("��ȭ��ȣ : %s\n", pCus->phoneNum);
	puts("");
}

// Ư������ �Ⱓ�� �뿩�̷� �������
void ShowDVDRentInfo(RentInfo dvd)
{
	puts("");
	printf("ISBN : %s\n", dvd.ISBN);
	printf("�뿩�� : %u\n", dvd.rentDay);
}