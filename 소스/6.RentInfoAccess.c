#include "common.h"
#include "RentInfo.h"
#include "cusInfoAccess.h"
#include "RentInfoAccess.h"
#include "screenOut.h"

#define RENT_MAX 100

static RentInfo Rent_List[RENT_MAX];
static RentInfo Return_List[RENT_MAX];
static int Rent_CNT = 0; 
static int Return_CNT = 0; 

// �뿩���� ���(����ü �迭�� ����)
int AddRentInfo(char *ISBN, char *ID, unsigned int rentday, int rentstate)
{
	strcpy(Rent_List[Rent_CNT].ISBN, ISBN);
	strcpy(Rent_List[Rent_CNT].ID, ID);
	Rent_List[Rent_CNT].rentDay = rentday;
	Rent_List[Rent_CNT].rentstate = rentstate;

	Rent_CNT++;

	return Rent_CNT;
}

// �ݳ����� ���(����ü �迭�� ����)
int AddReturnInfo(char *ISBN, char *ID, unsigned int rentday, int rentstate)
{
	strcpy(Return_List[Return_CNT].ISBN, ISBN);
	strcpy(Return_List[Return_CNT].ID, ID);
	Return_List[Return_CNT].rentDay = rentday;
	Return_List[Return_CNT].rentstate = rentstate;

	Return_CNT++;

	return Return_CNT;
}

// Ư�� DVD�� �뿩�� ��� �� ������ ���
void Print_Out_Rent_All_CusInfo(char *ISBN)
{
	cusInfo *pcus;
	int i;

	for (i = 0; i < Rent_CNT; i++)
	{
		if (!strcmp(Rent_List[i].ISBN, ISBN))
		{
			printf("\n�뿩�� : %d\n", Rent_List[i].rentDay);
			pcus = GetCusPtrByID(Rent_List[i].ID);
			ShowCustomerInfoContinue(pcus);
		}
	}
}

// Ư������ �Ⱓ�� �뿩�̷� �������
void Print_Out_Cus_All_RentInfo(char *ID, unsigned int start, unsigned int end)
{
	int i;

	for (i = 0; i < Rent_CNT; i++)
	{
		if (!strcmp(Rent_List[i].ID, ID))
		{
			if (start <= Rent_List[i].rentDay&&Rent_List[i].rentDay <= end)
			{
				ShowDVDRentInfo(Rent_List[i]);
			}
		}
	}

	getchar();
}

// Ư������ ��ü�Ͽ� ���� ��ü�� �ΰ� ��������
void Charging_Delay_Fee(char *ID)
{
	cusInfo * pcus = GetCusPtrByID(ID);
	if (pcus == 0) { puts("���� ID�Դϴ�."); return ; }

	unsigned int start = 0, end = 0; 
	int Fee = 500; // �⺻ ��ü��(4�Ϻ��� ��ü�� �ΰ�)
	int total = 0, sum = 0; // total : ��ü�� ���� �հ�, sum : 3�� �ʰ����� Ȯ���ϴ� ����
	int	i;
	
	for (i = 0; i < Rent_CNT; i++)
	{
		if (!strcmp(Rent_List[i].ID, pcus->ID))
		{			
			start = Rent_List[i].rentDay;
		}		
	}
	
	for (i = 0; i < Return_CNT; i++)
	{
		if (!strcmp(Return_List[i].ID, pcus->ID))
		{			
			end = Return_List[i].rentDay;
		}
	}
	
	sum = sum + (end - start);
	if (sum > 3) total = Fee * (sum-3);
	else total = 0;
	printf("�뿩�� : %u\n�ݳ��� : %u", start, end);
	
	if(pcus->delay_fee < total) pcus->delay_fee = total - pcus->delay_fee;
	else pcus->delay_fee = total;
	
	printf("\n��ü�� : %d\n", pcus->delay_fee);
	getchar();
}

// Ư������ ��ü�� ��������
int Recieve_DelayFee(void)
{
	cusInfo * pcus;
	char ID[ID_LEN];
	int Fee = 0;

	printf("��ü�� ������ �� ID �Է� : ");
	gets(ID);

	pcus = GetCusPtrByID(ID);
	if (pcus == 0)
	{
		puts("���Ե� ���� �ƴմϴ�.");
		getchar();
		return 0;
	}

	for (int i = 0; i < Rent_CNT; i++)
	{
		if (!strcmp(Rent_List[i].ID, pcus->ID))
		{
			if (pcus->delay_fee > 0)
			{
				printf("������ ��ü�� �ݾ��Է� : ");
				scanf("%d", &Fee);
				getchar();
								
				
				if ((pcus->delay_fee - Fee) < 0)
				{
					pcus->delay_fee = pcus->delay_fee;
					puts("�ݳ��� �ݾ��� �ʰ��߽��ϴ�. �ٽ� �Է����ּ���");
					getchar();
					return;
				}
				else
				{
					pcus->delay_fee = pcus->delay_fee - Fee;
					printf("���� ��ü�� : %d\n", pcus->delay_fee);
				}
			}
			else puts("������ ��ü�ᰡ �����ϴ�.");
		}		
	}	

	getchar();
	return pcus->delay_fee;
}

// �߰��Ǵ� �뿩��� ��������
void FILE_SAVE_RentInfo(void)
{
	FILE *fr = fopen("rm.txt", "w+");
	if (fr == NULL) puts("���Ͽ������");

	int i = 0;

	for (i = 0; i < Rent_CNT; i++)
	{
		fprintf(fr, "%s %s %u %d\n", Rent_List[i].ISBN, Rent_List[i].ID, 
			Rent_List[i].rentDay, Rent_List[i].rentstate);
	}

	fclose(fr);
}

// �߰��Ǵ� �ݳ���� ��������
void FILE_SAVE_ReturnInfo(void)
{
	FILE *fret = fopen("retm.txt", "w+");
	if (fret == NULL) puts("���Ͽ������");

	int i = 0;

	for (i = 0; i < Return_CNT; i++)
	{
		fprintf(fret, "%s %s %u %d\n", Return_List[i].ISBN, Return_List[i].ID, 
			Return_List[i].rentDay, Return_List[i].rentstate);
	}

	fclose(fret);
}

// �뿩��� ���� ���
void BACKUP_FILE_SAVE_RentInfo(void)
{
	FILE *fr = fopen("Backup_rm.txt", "w+");
	if (fr == NULL) puts("���Ͽ������");

	int i = 0;

	for (i = 0; i < Rent_CNT; i++)
	{
		fprintf(fr, "%s %s %u %d\n", Rent_List[i].ISBN, Rent_List[i].ID, 
			Rent_List[i].rentDay, Rent_List[i].rentstate);
	}

	fclose(fr);
}

// �ݳ���� ���� ���
void BACKUP_FILE_SAVE_ReturnInfo(void)
{
	FILE *fret = fopen("Backup_retm.txt", "w+");
	if (fret == NULL) puts("���Ͽ������");

	int i = 0;

	for (i = 0; i < Return_CNT; i++)
	{
		fprintf(fret, "%s %s %u %d\n", Return_List[i].ISBN, Return_List[i].ID,
			Return_List[i].rentDay, Return_List[i].rentstate);
	}

	fclose(fret);
}