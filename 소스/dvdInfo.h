#ifndef __DVDINFO_H__
#define __DVDINFO_H__

#include "cusInfo.h"

#define ISBN_LEN 30
#define TITLE_LEN 30
#define RENT_LEN 100

// ���� �帣 ����
enum { ACTION = 1, COMIC, SF, ROMANTIC };

// �뿩 ���� ����
enum { RENTED, RETURNED }; // RENTED = 0, RETURNED = 1 

typedef struct __dvdInfo
{
	char ISBN[ISBN_LEN];
	char title[TITLE_LEN];
	int genre; //���� �帣 ��� ����	
	int rentState; // �뿩���ɿ���(�뿩, �ݳ�)
} dvdInfo;

#endif // !__DVDINFO_H__