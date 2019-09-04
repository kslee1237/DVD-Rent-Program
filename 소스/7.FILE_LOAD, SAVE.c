#include "common.h"
#include "RentInfo.h"
#include "cusInfoAccess.h"
#include "dvdInfoAccess.h"
#include "RentInfoAccess.h"

FILE *fc; // 고객정보 파일
FILE *fd; // DVD정보 파일
FILE *fr; // 대여정보 파일
FILE *fret; // 반납정보 파일

#define FILE_MAX 100

cusInfo Cus_List[FILE_MAX];
dvdInfo DVD_List[FILE_MAX];
RentInfo Rent_List[FILE_MAX];
RentInfo Return_List[FILE_MAX];

int Cus_Cnt = 0;
int DVD_Cnt = 0;
int Rent_Cnt = 0;
int Return_Cnt = 0;

// 파일에 저장된 목록 출력
void FILE_SHOW(void)
{
	int resc, resd = 0, resr = 0, resret = 0;

	fc = fopen("cm.txt", "rt");
	fd = fopen("dm.txt", "rt");
	fr = fopen("rm.txt", "rt");
	fret = fopen("retm.txt", "rt");

	if (fc == NULL) { puts("파일열기실패"); return; }
	if (fd == NULL) { puts("파일열기실패"); return; }
	if (fr == NULL) { puts("파일열기실패"); return; }
	if (fret == NULL) { puts("파일열기실패"); return; }


	puts("┌───파일 목록 ───┐");
	puts("│");

	puts("│------ 고객 정보 -------");

	for (Cus_Cnt = 0; Cus_Cnt < FILE_MAX; Cus_Cnt++)
	{
		resc = fscanf(fc, "%s %s %s %d", Cus_List[Cus_Cnt].ID, Cus_List[Cus_Cnt].name, 
			Cus_List[Cus_Cnt].phoneNum,	&Cus_List[Cus_Cnt].delay_fee);
		if (resc == EOF) break;

		fprintf(stdout, "│%s  %s %s %d\n", Cus_List[Cus_Cnt].ID, Cus_List[Cus_Cnt].name, 
			Cus_List[Cus_Cnt].phoneNum,	Cus_List[Cus_Cnt].delay_fee);
	}
	
	puts("\n│------- DVD 정보 -------");

	for (DVD_Cnt = 0; DVD_Cnt < FILE_MAX; DVD_Cnt++)
	{
		resd = fscanf(fd, "%s %s %d %d", DVD_List[DVD_Cnt].ISBN, DVD_List[DVD_Cnt].title, 
			&DVD_List[DVD_Cnt].genre, &DVD_List[DVD_Cnt].rentState);
		if (resd == EOF) break;

		fprintf(stdout, "│%s %s %d %d\n", DVD_List[DVD_Cnt].ISBN, DVD_List[DVD_Cnt].title,
			DVD_List[DVD_Cnt].genre, DVD_List[DVD_Cnt].rentState);
	}

	puts("\n│----- DVD 대여정보 -----");

	for (Rent_Cnt = 0; Rent_Cnt < FILE_MAX; Rent_Cnt++)
	{
		resr = fscanf(fr, "%s %s %u %d", Rent_List[Rent_Cnt].ISBN, Rent_List[Rent_Cnt].ID, 
			&Rent_List[Rent_Cnt].rentDay, &Rent_List[Rent_Cnt].rentstate);
		if (resr == EOF) break;

		fprintf(stdout, "│%s %s %u %d\n", Rent_List[Rent_Cnt].ISBN, Rent_List[Rent_Cnt].ID,
			Rent_List[Rent_Cnt].rentDay, Rent_List[Rent_Cnt].rentstate);
	}

	puts("\n│----- DVD 반납정보 -----");

	for (Return_Cnt = 0; Return_Cnt < FILE_MAX; Return_Cnt++)
	{
		resret = fscanf(fret, "%s %s %u %d", Return_List[Return_Cnt].ISBN, Return_List[Return_Cnt].ID,
			&Return_List[Return_Cnt].rentDay, &Return_List[Return_Cnt].rentstate);
		if (resret == EOF) break;

		fprintf(stdout, "│%s %s %u %d\n", Return_List[Return_Cnt].ISBN, Return_List[Return_Cnt].ID,
			Return_List[Return_Cnt].rentDay, Return_List[Return_Cnt].rentstate);
	}

	puts("└────────────┘");

	fclose(fc);
	fclose(fd);
	fclose(fr);
	fclose(fret);
	getchar();
}

// 파일 불러오기
void FILE_LOAD(void)
{
	int resc, resd = 0, resr = 0, resret = 0;

	fc = fopen("cm.txt", "r+");
	fd = fopen("dm.txt", "r+");
	fr = fopen("rm.txt", "r+");
	fret = fopen("retm.txt", "r+");

	if (fc == NULL) { puts("파일열기실패"); return; }
	if (fd == NULL) { puts("파일열기실패"); return; }
	if (fr == NULL) { puts("파일열기실패"); return; }
	if (fret == NULL) { puts("파일열기실패"); return; }

	for (Cus_Cnt = 0; Cus_Cnt < FILE_MAX; Cus_Cnt++)
	{
		resc = fscanf(fc, "%s %s %s %d", Cus_List[Cus_Cnt].ID, Cus_List[Cus_Cnt].name, 
			Cus_List[Cus_Cnt].phoneNum, &Cus_List[Cus_Cnt].delay_fee);
		if (resc == EOF) break;

		AddCusInfo(Cus_List[Cus_Cnt].ID, Cus_List[Cus_Cnt].name, 
			Cus_List[Cus_Cnt].phoneNum, Cus_List[Cus_Cnt].delay_fee);
	}

	for (DVD_Cnt = 0; DVD_Cnt < FILE_MAX; DVD_Cnt++)
	{
		resd = fscanf(fd, "%s %s %d %d", DVD_List[DVD_Cnt].ISBN, DVD_List[DVD_Cnt].title, 
			&DVD_List[DVD_Cnt].genre, &DVD_List[DVD_Cnt].rentState);
		if (resd == EOF) break;

		AddDVDInfo(DVD_List[DVD_Cnt].ISBN, DVD_List[DVD_Cnt].title, 
			DVD_List[DVD_Cnt].genre, DVD_List[DVD_Cnt].rentState);
	}

	for (Rent_Cnt = 0; Rent_Cnt < FILE_MAX; Rent_Cnt++)
	{
		resr = fscanf(fr, "%s %s %u %d", Rent_List[Rent_Cnt].ISBN, Rent_List[Rent_Cnt].ID,
			&Rent_List[Rent_Cnt].rentDay, &Rent_List[Rent_Cnt].rentstate);
		if (resr == EOF) break;

		AddRentInfo(Rent_List[Rent_Cnt].ISBN, Rent_List[Rent_Cnt].ID,
			Rent_List[Rent_Cnt].rentDay, Rent_List[Rent_Cnt].rentstate);
	}

	for (Return_Cnt = 0; Return_Cnt < FILE_MAX; Return_Cnt++)
	{
		resret = fscanf(fret, "%s %s %u %d", Return_List[Return_Cnt].ISBN, Return_List[Return_Cnt].ID,
			&Return_List[Return_Cnt].rentDay, &Return_List[Return_Cnt].rentstate);
		if (resret == EOF) break;

		AddReturnInfo(Return_List[Return_Cnt].ISBN, Return_List[Return_Cnt].ID,
			Return_List[Return_Cnt].rentDay, Return_List[Return_Cnt].rentstate);
	}
	
	fclose(fc);
	fclose(fd);
	fclose(fr);
	fclose(fret);
}

// 파일 저장
void FILE_SAVE(void)
{
	FILE_SAVE_CusInfo();
	puts("고객정보 저장완료");

	FILE_SAVE_DVDInfo();
	puts("DVD정보 저장완료");

	FILE_SAVE_RentInfo();
	puts("대여정보 저장완료");

	FILE_SAVE_ReturnInfo();
	puts("반납정보 저장완료");
	getchar();
}

// 파일 백업
void FILE_BACKUP(void)
{
	BACKUP_FILE_SAVE_CusInfo();

	BACKUP_FILE_SAVE_DVDInfo();

	BACKUP_FILE_SAVE_RentInfo();

	BACKUP_FILE_SAVE_ReturnInfo();

	puts("백업 완료");
	getchar();
}