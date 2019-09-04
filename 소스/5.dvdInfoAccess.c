#include "common.h"
#include "dvdInfo.h"

#define DVD_MAX 100

static dvdInfo *DVD_List[DVD_MAX];
static int DVD_CNT = 0;

// dvdInfo ������� �Ҵ� �� ����ü �迭�� ����
int AddDVDInfo(char *ISBN, char *title, int genre, int rentstate)
{
	dvdInfo *pDVD;

	if (DVD_CNT >= DVD_MAX) return 0;
	pDVD = (dvdInfo*)malloc(sizeof(dvdInfo));
	if (pDVD == NULL)
	{
		puts("���� ���� ����");
		return 0;
	}

	strcpy(pDVD->ISBN, ISBN);
	strcpy(pDVD->title, title);
	pDVD->genre= genre;
	pDVD->rentState = rentstate;

	DVD_List[DVD_CNT++] = pDVD;

	return DVD_CNT;
}

// �ش� ISBN�� ������ ��� �ִ� ������ ������ ��ȯ
dvdInfo *GetDVDPtrByISBN(char *ISBN)
{
	for (int i = 0; i < DVD_CNT; i++)
	{
		if (!strcmp(DVD_List[i]->ISBN, ISBN)) return DVD_List[i];
	}

	return (dvdInfo*)0;
}

// �� ��ϵ� ISBN���� üũ
int IsRegistISBN(char *ISBN)
{
	dvdInfo *pdvd = GetDVDPtrByISBN(ISBN);

	if (pdvd == 0) return 0;
	else return 1;
}

// // DVD �뿩���� ����
int Get_RENT_STATE_DVD(char *ISBN)
{
	dvdInfo *pdvd = GetDVDPtrByISBN(ISBN);

	if (pdvd == 0) return -1;

	return pdvd->rentState;
}

// DVD �뿩���·� ��ȯ
int Set_Rent_DVD(char *ISBN)
{
	dvdInfo *pdvd = GetDVDPtrByISBN(ISBN);

	if (pdvd == 0) return -1;

	pdvd->rentState = RENTED; // RENTED = 0

	return pdvd->rentState;
}

// DVD �ݳ�(�뿩����)���·� ��ȯ
int Set_Return_DVD(char *ISBN)
{
	dvdInfo *pdvd = GetDVDPtrByISBN(ISBN);

	if (pdvd == 0) return -1;

	pdvd->rentState = RETURNED; // RETURNED = 1

	return pdvd->rentState;
}

// �߰��Ǵ� DVD���� ��������
void FILE_SAVE_DVDInfo(void)
{
	FILE *fd = fopen("dm.txt", "w+");
	if (fd == NULL) puts("���Ͽ������");
	
	int i = 0;

	for (i = 0; i < DVD_CNT; i++)
	{
		fprintf(fd, "%s %s %d %d\n", DVD_List[i]->ISBN, DVD_List[i]->title, 
			DVD_List[i]->genre, DVD_List[i]->rentState);
	}

	fclose(fd);
}

// DVD �������� ���
void BACKUP_FILE_SAVE_DVDInfo(void)
{
	FILE *fd = fopen("Backup_dm.txt", "w+");
	if (fd == NULL) puts("���Ͽ������");

	int i = 0;

	for (i = 0; i < DVD_CNT; i++)
	{
		fprintf(fd, "%s %s %d %d\n", DVD_List[i]->ISBN, DVD_List[i]->title, 
			DVD_List[i]->genre, DVD_List[i]->rentState);
	}

	fclose(fd);
}