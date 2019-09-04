#include "common.h"
#include "cusInfo.h"
#include "FILE_LOAD, SAVE.h"

#define Cus_MAX 100

static cusInfo *Cus_List[Cus_MAX];
static int Cus_CNT = 0;

// cusInfo ������� �Ҵ� �� ����ü �迭�� ����
int AddCusInfo(char *ID, char *name, char *num, int delay_fee)
{	
	cusInfo *pCus;
	
	if (Cus_CNT >= Cus_MAX) return 0;
	pCus = (cusInfo*)malloc(sizeof(cusInfo));
	if (pCus == NULL)
	{
		puts("���� ���� ����");
		return 0;
	}

	strcpy(pCus->ID, ID);
	strcpy(pCus->name, name);
	strcpy(pCus->phoneNum, num);
	pCus->delay_fee = delay_fee;

	Cus_List[Cus_CNT++] = pCus;

	return Cus_CNT;
}

// �ش� �� ID�� ������ ������ �ִ� ������ ��ȯ
cusInfo * GetCusPtrByID(char *ID)
{	
	for (int i = 0; i < Cus_CNT; i++)
	{
		if (!strcmp(Cus_List[i]->ID, ID)) return Cus_List[i];
	}

	return (cusInfo*)0;
}

// ���Ե� ID���� üũ
int IsregistID(char *ID)
{
	cusInfo *pcus = GetCusPtrByID(ID);

	if (pcus == 0) return 0;
	else return 1;
}

// �߰��Ǵ� ������ ��������
void FILE_SAVE_CusInfo(void)
{
	FILE *fc = fopen("cm.txt", "w+");	
	int i = 0;

	for (i = 0; i < Cus_CNT; i++)
	{
		fprintf(fc, "%s %s %s %d\n", Cus_List[i]->ID, Cus_List[i]->name, 
			Cus_List[i]->phoneNum, Cus_List[i]->delay_fee);
	}	

	fclose(fc);
}

// ������ ���� ���
void BACKUP_FILE_SAVE_CusInfo(void)
{
	FILE *fc = fopen("Backup_cm.txt", "w+");
	int i = 0;

	for (i = 0; i < Cus_CNT; i++)
	{
		fprintf(fc, "%s %s %s %d\n", Cus_List[i]->ID, Cus_List[i]->name, 
			Cus_List[i]->phoneNum, Cus_List[i]->delay_fee);
	}

	fclose(fc);
}