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

// 대여정보 기록(구조체 배열에 저장)
int AddRentInfo(char *ISBN, char *ID, unsigned int rentday, int rentstate)
{
	strcpy(Rent_List[Rent_CNT].ISBN, ISBN);
	strcpy(Rent_List[Rent_CNT].ID, ID);
	Rent_List[Rent_CNT].rentDay = rentday;
	Rent_List[Rent_CNT].rentstate = rentstate;

	Rent_CNT++;

	return Rent_CNT;
}

// 반납정보 기록(구조체 배열에 저장)
int AddReturnInfo(char *ISBN, char *ID, unsigned int rentday, int rentstate)
{
	strcpy(Return_List[Return_CNT].ISBN, ISBN);
	strcpy(Return_List[Return_CNT].ID, ID);
	Return_List[Return_CNT].rentDay = rentday;
	Return_List[Return_CNT].rentstate = rentstate;

	Return_CNT++;

	return Return_CNT;
}

// 특정 DVD를 대여한 모든 고객 정보를 출력
void Print_Out_Rent_All_CusInfo(char *ISBN)
{
	cusInfo *pcus;
	int i;

	for (i = 0; i < Rent_CNT; i++)
	{
		if (!strcmp(Rent_List[i].ISBN, ISBN))
		{
			printf("\n대여일 : %d\n", Rent_List[i].rentDay);
			pcus = GetCusPtrByID(Rent_List[i].ID);
			ShowCustomerInfoContinue(pcus);
		}
	}
}

// 특정고객의 기간별 대여이력 정보출력
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

// 특정고객의 연체일에 따른 연체료 부과 절차진행
void Charging_Delay_Fee(char *ID)
{
	cusInfo * pcus = GetCusPtrByID(ID);
	if (pcus == 0) { puts("없는 ID입니다."); return ; }

	unsigned int start = 0, end = 0; 
	int Fee = 500; // 기본 연체료(4일부터 연체료 부과)
	int total = 0, sum = 0; // total : 연체료 최종 합계, sum : 3일 초과인지 확인하는 변수
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
	printf("대여일 : %u\n반납일 : %u", start, end);
	
	if(pcus->delay_fee < total) pcus->delay_fee = total - pcus->delay_fee;
	else pcus->delay_fee = total;
	
	printf("\n연체료 : %d\n", pcus->delay_fee);
	getchar();
}

// 특정고객의 연체료 납부진행
int Recieve_DelayFee(void)
{
	cusInfo * pcus;
	char ID[ID_LEN];
	int Fee = 0;

	printf("연체료 납부할 고객 ID 입력 : ");
	gets(ID);

	pcus = GetCusPtrByID(ID);
	if (pcus == 0)
	{
		puts("가입된 고객이 아닙니다.");
		getchar();
		return 0;
	}

	for (int i = 0; i < Rent_CNT; i++)
	{
		if (!strcmp(Rent_List[i].ID, pcus->ID))
		{
			if (pcus->delay_fee > 0)
			{
				printf("납부할 연체료 금액입력 : ");
				scanf("%d", &Fee);
				getchar();
								
				
				if ((pcus->delay_fee - Fee) < 0)
				{
					pcus->delay_fee = pcus->delay_fee;
					puts("반납할 금액을 초과했습니다. 다시 입력해주세요");
					getchar();
					return;
				}
				else
				{
					pcus->delay_fee = pcus->delay_fee - Fee;
					printf("남은 연체료 : %d\n", pcus->delay_fee);
				}
			}
			else puts("납부할 연체료가 없습니다.");
		}		
	}	

	getchar();
	return pcus->delay_fee;
}

// 추가되는 대여기록 파일저장
void FILE_SAVE_RentInfo(void)
{
	FILE *fr = fopen("rm.txt", "w+");
	if (fr == NULL) puts("파일열기실패");

	int i = 0;

	for (i = 0; i < Rent_CNT; i++)
	{
		fprintf(fr, "%s %s %u %d\n", Rent_List[i].ISBN, Rent_List[i].ID, 
			Rent_List[i].rentDay, Rent_List[i].rentstate);
	}

	fclose(fr);
}

// 추가되는 반납기록 파일저장
void FILE_SAVE_ReturnInfo(void)
{
	FILE *fret = fopen("retm.txt", "w+");
	if (fret == NULL) puts("파일열기실패");

	int i = 0;

	for (i = 0; i < Return_CNT; i++)
	{
		fprintf(fret, "%s %s %u %d\n", Return_List[i].ISBN, Return_List[i].ID, 
			Return_List[i].rentDay, Return_List[i].rentstate);
	}

	fclose(fret);
}

// 대여기록 파일 백업
void BACKUP_FILE_SAVE_RentInfo(void)
{
	FILE *fr = fopen("Backup_rm.txt", "w+");
	if (fr == NULL) puts("파일열기실패");

	int i = 0;

	for (i = 0; i < Rent_CNT; i++)
	{
		fprintf(fr, "%s %s %u %d\n", Rent_List[i].ISBN, Rent_List[i].ID, 
			Rent_List[i].rentDay, Rent_List[i].rentstate);
	}

	fclose(fr);
}

// 반납기록 파일 백업
void BACKUP_FILE_SAVE_ReturnInfo(void)
{
	FILE *fret = fopen("Backup_retm.txt", "w+");
	if (fret == NULL) puts("파일열기실패");

	int i = 0;

	for (i = 0; i < Return_CNT; i++)
	{
		fprintf(fret, "%s %s %u %d\n", Return_List[i].ISBN, Return_List[i].ID,
			Return_List[i].rentDay, Return_List[i].rentstate);
	}

	fclose(fret);
}