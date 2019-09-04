#ifndef __RENTINFOACCESS_H__
#define __RENTINFOACCESS_H__

#include "RentInfo.h"

int AddRentInfo(char *ISBN, char *ID, unsigned int rentday, 
	int rentstate); // �뿩���� ���(����ü �迭�� ����)

int AddReturnInfo(char *ISBN, char *ID, unsigned int rentday, 
	int rentstate); // �ݳ����� ���(����ü �迭�� ����)
 
void Print_Out_Rent_All_CusInfo(char *ISBN); // Ư�� DVD�� �뿩�� ��� �� ������ ���

void Print_Out_Cus_All_RentInfo(char *ID, unsigned int start, 
	unsigned int end); // Ư������ �Ⱓ�� �뿩�̷� �������

void Charging_Delay_Fee(char *ID); // Ư������ ��ü�Ͽ� ���� ��ü�� �ΰ� ��������

int Recieve_DelayFee(void); // Ư������ ��ü�� ��������

void FILE_SAVE_RentInfo(void); // �߰��Ǵ� �뿩��� ��������

void FILE_SAVE_ReturnInfo(void); // �߰��Ǵ� �ݳ���� ��������

void BACKUP_FILE_SAVE_RentInfo(void); // �뿩��� ���� ���

void BACKUP_FILE_SAVE_ReturnInfo(void); // �ݳ���� ���� ���
 
#endif // !__RENTINFOACCESS_H__

