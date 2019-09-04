#include "common.h"
#include "RentInfo.h"
#include "cusInfoAccess.h"
#include "dvdInfoAccess.h"
#include "RentInfoAccess.h"
#include "screenOut.h"


enum { CHARGING_DELAYFEE = 1, RECIEVE_DELAYFEE, QUIT };

// ȸ�����
void Register_Customer(void)
{			
	char ID[ID_LEN];
	char name[NAME_LEN];
	char phonenum[PHONE_LEN];
	int delay_fee = 0;

	printf("ID �Է� : ");
	gets(ID);	

	if (IsregistID(ID))
	{
		puts("�ش� ID�� ������Դϴ�.");
		getchar();
		return;
	}

	printf("�̸� �Է� : ");
	gets(name);

	printf("��ȭ��ȣ �Է� : ");
	gets(phonenum);

	if (!AddCusInfo(ID, name, phonenum, delay_fee))
	{
		puts("������ �������");
		getchar();
		return;
	}

	puts("ȸ������ �Ϸ�");
	getchar();
}

// ȸ�� �˻�
void Search_CusInfo(void)
{
	cusInfo *pCus;
	char ID[ID_LEN];

	printf("��ȸ�� �� ID �Է� : ");
	gets(ID);	

	pCus = GetCusPtrByID(ID);
	if (pCus == 0)
	{
		puts("��ϵ��� ���� ID�Դϴ�.\n");		
		getchar();
		return;
	}
		
	ShowCustomerInfo(pCus);
	getchar();
}

// DVD ���
void Regist_DVD(void)
{
	char ISBN[ISBN_LEN], title[TITLE_LEN];
	int genre, rentstate;

	printf("DVD ISBN �Է� : ");
	gets(ISBN);

	if (IsRegistISBN(ISBN))
	{
		puts("�ش� ISBN�� ������Դϴ�.");
		getchar();
		return;
	}

	printf("Ÿ��Ʋ �Է� : ");
	gets(title);

	printf("�帣 �Է� (�׼� : 1, �ڹ� : 2, SF : 3, �θ�ƽ : 4)");
	scanf("%d", &genre);	
	rewind(stdin);

	rentstate = RETURNED;

	if (!AddDVDInfo(ISBN, title, genre, rentstate))
	{
		puts("DVD���� �������");
		return;
	}

	puts("DVD ��ϿϷ�");
	getchar();
}

// DVD ��ȸ
void Search_DVDInfo(void)
{
	dvdInfo *pDVD;
	char ISBN[ISBN_LEN];

	printf("��ȸ�� DVD ISBN �Է� : ");
	gets(ISBN);

	pDVD = GetDVDPtrByISBN(ISBN);
	if (pDVD == 0)
	{
		puts("��ϵ��� ���� ISBN�Դϴ�.");		
		getchar();
		return;
	}

	ShowDVDInfo(pDVD);
	getchar();
}

// DVD �뿩
void Rent_DVD(void) 
{
	char ISBN[ISBN_LEN];
	int registDVD; // DVDȮ��
	int registcus; // ��Ȯ��
	int rentstate; // �뿩Ȯ��
	char ID[ID_LEN]; // �뿩�� ID
	unsigned int rentDay; // �뿩��¥

	// �뿩�� DVD�� ISBN ��Ͽ��� üũ
	printf("�뿩 DVD ISBN �Է� : ");
	gets(ISBN);

	registDVD = IsRegistISBN(ISBN);
	if (registDVD == 0)
	{
		puts("��ϵ��� ���� ISBN�Դϴ�.");
		getchar();
		return;
	}

	// �뿩���� ���� üũ
	rentstate = Get_RENT_STATE_DVD(ISBN);
	if (rentstate == RENTED)
	{
		puts("�뿩���� DVD�Դϴ�.");
		getchar();
		return;
	}

	// �뿩���� ����
	puts("�뿩����, �뿩�����մϴ�.");

	printf("�뿩�� ID : ");
	gets(ID);

	// �� ID üũ
	registcus = IsregistID(ID);
	if (registcus == 0)
	{
		puts("���Ե��� ���� ���Դϴ�.");
		getchar();
		return;
	}

	printf("�뿩��¥(�� : 20190320) : ");
	scanf("%u", &rentDay);
	getchar();

	rentstate = Set_Rent_DVD(ISBN);

	// �̷°����� �и��� RentInfoAccess.c�� �ִ� AddRentList()�Լ� ���
	AddRentInfo(ISBN, ID, rentDay, rentstate);

	puts("�뿩 �Ϸ�");
	getchar();
}

// DVD �ݳ�
void Return_DVD(void) 
{
	char ISBN[ISBN_LEN];
	int registDVD; // DVDȮ��
	int registcus; // ��Ȯ��
	int rentstate; // �ݳ�Ȯ��
	char ID[ID_LEN]; // �ݳ��� ID
	unsigned int rentDay; // �ݳ���¥

	printf("�ݳ� DVD ISBN �Է� : ");
	gets(ISBN);

	// �Էµ� ISBN ��Ͽ��� Ȯ��
	registDVD = IsRegistISBN(ISBN);
	if (registDVD == 0)
	{
		puts("��ϵ��� ���� ISBN�Դϴ�.");
		getchar();
		return;
	}

	// �ݳ����� ���� Ȯ��
	rentstate = Get_RENT_STATE_DVD(ISBN);
	if (rentstate == RETURNED)
	{
		puts("�뿩���� ���� DVD�̹Ƿ� �ݳ��Ұ�");
		getchar();
		return;
	}

	// �ݳ����� ����
	puts("�ݳ�����, �ݳ������մϴ�.");

	printf("�ݳ��� ID : ");
	gets(ID);

	// �� ID üũ
	registcus = IsregistID(ID);
	if (registcus == 0)
	{
		puts("���Ե��� ���� ���Դϴ�.");
		getchar();
		return;
	}

	printf("�ݳ���¥(�� : 20190320) : ");
	scanf("%u", &rentDay);
	getchar();

	// �ݳ����� ����
	rentstate = Set_Return_DVD(ISBN);

	AddReturnInfo(ISBN, ID, rentDay, rentstate);

	puts("�ݳ� �Ϸ�");
	getchar();
}

// Ư�� DVD�� �뿩�� ��� �� ����
void Show_DVDRent_ALL_CusInfo(void) 
{
	dvdInfo *ptrDVDInfo; // DVD ����
	char ISBN[ISBN_LEN];

	printf("�뿩�̷��� ��ȸ�� DVD ISBN �Է� : ");
	gets(ISBN);

	ptrDVDInfo = GetDVDPtrByISBN(ISBN);
	if (ptrDVDInfo == 0)
	{
		puts("�������� �ʴ� DVD ISBN�Դϴ�.");
		getchar();
		return;
	}

	Print_Out_Rent_All_CusInfo(ISBN); // Ư�� ISBN�� DVD ��� �뿩�� �������

	puts("��ȸ �Ϸ�");
	getchar();
}

// Ư������ �Ⱓ�� �뿩�̷� ����
void ShowDVD_CusAllRentInfo(void)
{
	cusInfo *pcus;
	char ID[ID_LEN];
	unsigned int Rent_start, Rent_end;

	printf("�˻��� �� ID : ");
	gets(ID);

	pcus = GetCusPtrByID(ID);
	if (pcus == 0)
	{
		puts("���Ե� ���� �ƴմϴ�.");
		getchar();
		return;
	}

	printf("�˻��� �Ⱓ���� �Է� : ");
	scanf("%u %u", &Rent_start, &Rent_end);

	if (Rent_start > Rent_end)
	{
		puts("�Ⱓ ������ �߸� �Էµ�");
		getchar();
		return;
	}

	Print_Out_Cus_All_RentInfo(ID, Rent_start, Rent_end); // Ư������ �Ⱓ�� �뿩�̷� �������

	puts("��ȸ �Ϸ�");
	getchar();
}

// ���� DVD��ü���� ��ȸ
void ShowCus_DelayFee_ByOverdue(void)
{
	char ID[ID_LEN];
	int menu;

	while (1)
	{
		puts("-------�޴� ����-------");
		puts("1. Ư������ ��ü�Ͽ� ���� ��ü�� �ΰ�");
		puts("2. Ư������ ��ü�� ��������");
		puts("3. ��ȸ���ø޴��� �̵�");
		printf(">> ���� : ");
		scanf("%d", &menu);
		getchar();

		switch (menu)
		{
		case CHARGING_DELAYFEE:
			printf("�˻��� �� ID �Է� : ");
			gets(ID);
			
			if (GetCusPtrByID(ID) == 0)
			{
				puts("���Ե� ���� �ƴմϴ�.");
				getchar();
				return;
			}

			Charging_Delay_Fee(ID); // Ư������ ��ü�Ͽ� ���� ��ü�� �ΰ� ��������
			break;

		case RECIEVE_DELAYFEE:
			Recieve_DelayFee(); // Ư������ ��ü�� ��������
			break;
		}

		if (menu == QUIT)
		{
			puts("��ȸ���ø޴� ȭ������ �̵�\n\n");
			break;
		}
	}
}