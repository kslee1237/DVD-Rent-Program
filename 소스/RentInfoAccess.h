#ifndef __RENTINFOACCESS_H__
#define __RENTINFOACCESS_H__

#include "RentInfo.h"

int AddRentInfo(char *ISBN, char *ID, unsigned int rentday, 
	int rentstate); // 대여정보 기록(구조체 배열에 저장)

int AddReturnInfo(char *ISBN, char *ID, unsigned int rentday, 
	int rentstate); // 반납정보 기록(구조체 배열에 저장)
 
void Print_Out_Rent_All_CusInfo(char *ISBN); // 특정 DVD를 대여한 모든 고객 정보를 출력

void Print_Out_Cus_All_RentInfo(char *ID, unsigned int start, 
	unsigned int end); // 특정고객의 기간별 대여이력 정보출력

void Charging_Delay_Fee(char *ID); // 특정고객의 연체일에 따른 연체료 부과 절차진행

int Recieve_DelayFee(void); // 특정고객의 연체료 납부진행

void FILE_SAVE_RentInfo(void); // 추가되는 대여기록 파일저장

void FILE_SAVE_ReturnInfo(void); // 추가되는 반납기록 파일저장

void BACKUP_FILE_SAVE_RentInfo(void); // 대여기록 파일 백업

void BACKUP_FILE_SAVE_ReturnInfo(void); // 반납기록 파일 백업
 
#endif // !__RENTINFOACCESS_H__

