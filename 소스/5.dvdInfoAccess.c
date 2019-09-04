#include "common.h"
#include "dvdInfo.h"

#define DVD_MAX 100

static dvdInfo *DVD_List[DVD_MAX];
static int DVD_CNT = 0;

// dvdInfo 저장공간 할당 및 구조체 배열에 저장
int AddDVDInfo(char *ISBN, char *title, int genre, int rentstate)
{
	dvdInfo *pDVD;

	if (DVD_CNT >= DVD_MAX) return 0;
	pDVD = (dvdInfo*)malloc(sizeof(dvdInfo));
	if (pDVD == NULL)
	{
		puts("저장 공간 부족");
		return 0;
	}

	strcpy(pDVD->ISBN, ISBN);
	strcpy(pDVD->title, title);
	pDVD->genre= genre;
	pDVD->rentState = rentstate;

	DVD_List[DVD_CNT++] = pDVD;

	return DVD_CNT;
}

// 해당 ISBN의 정보를 담고 있는 변수의 포인터 반환
dvdInfo *GetDVDPtrByISBN(char *ISBN)
{
	for (int i = 0; i < DVD_CNT; i++)
	{
		if (!strcmp(DVD_List[i]->ISBN, ISBN)) return DVD_List[i];
	}

	return (dvdInfo*)0;
}

// 기 등록된 ISBN인지 체크
int IsRegistISBN(char *ISBN)
{
	dvdInfo *pdvd = GetDVDPtrByISBN(ISBN);

	if (pdvd == 0) return 0;
	else return 1;
}

// // DVD 대여상태 정보
int Get_RENT_STATE_DVD(char *ISBN)
{
	dvdInfo *pdvd = GetDVDPtrByISBN(ISBN);

	if (pdvd == 0) return -1;

	return pdvd->rentState;
}

// DVD 대여상태로 변환
int Set_Rent_DVD(char *ISBN)
{
	dvdInfo *pdvd = GetDVDPtrByISBN(ISBN);

	if (pdvd == 0) return -1;

	pdvd->rentState = RENTED; // RENTED = 0

	return pdvd->rentState;
}

// DVD 반납(대여가능)상태로 변환
int Set_Return_DVD(char *ISBN)
{
	dvdInfo *pdvd = GetDVDPtrByISBN(ISBN);

	if (pdvd == 0) return -1;

	pdvd->rentState = RETURNED; // RETURNED = 1

	return pdvd->rentState;
}

// 추가되는 DVD정보 파일저장
void FILE_SAVE_DVDInfo(void)
{
	FILE *fd = fopen("dm.txt", "w+");
	if (fd == NULL) puts("파일열기실패");
	
	int i = 0;

	for (i = 0; i < DVD_CNT; i++)
	{
		fprintf(fd, "%s %s %d %d\n", DVD_List[i]->ISBN, DVD_List[i]->title, 
			DVD_List[i]->genre, DVD_List[i]->rentState);
	}

	fclose(fd);
}

// DVD 정보파일 백업
void BACKUP_FILE_SAVE_DVDInfo(void)
{
	FILE *fd = fopen("Backup_dm.txt", "w+");
	if (fd == NULL) puts("파일열기실패");

	int i = 0;

	for (i = 0; i < DVD_CNT; i++)
	{
		fprintf(fd, "%s %s %d %d\n", DVD_List[i]->ISBN, DVD_List[i]->title, 
			DVD_List[i]->genre, DVD_List[i]->rentState);
	}

	fclose(fd);
}