#ifndef __DVDINFOACCESS_H__
#define __DVDINFOACCESS_H__

#include "dvdInfo.h"

int AddDVDInfo(char *ISBN, char *title, int genre, int rentstate); // dvdInfo ������� �Ҵ� �� ����ü �迭�� ����

dvdInfo *GetDVDPtrByISBN(char *ISBN); // �ش� ISBN�� ������ ��� �ִ� ������ ������ ��ȯ

int IsRegistISBN(char *ISBN); // �� ��ϵ� ISBN���� üũ

int Get_RENT_STATE_DVD(char *ISBN); // DVD �뿩���� ����

int Set_Rent_DVD(char *ISBN); // DVD �뿩���·� ��ȯ

int Set_Return_DVD(char *ISBN); // DVD �ݳ�(�뿩����)���·� ��ȯ

void FILE_SAVE_DVDInfo(void); // �߰��Ǵ� DVD���� ��������

void BACKUP_FILE_SAVE_DVDInfo(void); // DVD �������� ���

#endif // !__DVDINFOACCESS_H__