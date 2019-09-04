/*
	* ���   : �� ���� ���� �� ���� �Լ����� ����
	* �ۼ��� : LEE
	* �ۼ��� : 2019-03-11
	* ver    : 1.0
*/

#ifndef __CUSACCESS_H__
#define __CUSACCESS_H__

#include "cusInfo.h"

int AddCusInfo(char *ID, char *name, char *num, int delay_fee); // cusInfo ������� �Ҵ� �� ����ü �迭�� ����

cusInfo * GetCusPtrByID(char *ID); // �ش� �� ID�� ������ ������ �ִ� ������ ��ȯ

int IsregistID(char *ID); // ���Ե� ID���� üũ

void FILE_SAVE_CusInfo(void); // �߰��Ǵ� ������ ��������

void BACKUP_FILE_SAVE_CusInfo(void); // ������ ���� ���

#endif // !__CUSACCESS_H__
