/*
	* ���   : �ܼ������ ���� �Լ����� ����
	* �ۼ��� : LEE
	* �ۼ��� : 2019-03-11
	* ver    : 1.0
*/

#ifndef __SCREENOUT_H__
#define __SCREENOUT_H__

#include "cusInfo.h"
#include "dvdInfo.h"
#include "RentInfo.h"

void ShowMenu(void); // �� ���α׷��� ����ϱ� ���� �޴� ���

void ShowCustomerInfo(cusInfo * pCus); // ������ ���

void ShowGenre(int gen); // DVD�帣 ����

void ShowDVDInfo(dvdInfo * pDVD); // DVD���� ���

void Show_RENT_AND_RETURN(void); // �뿩 / �ݳ� �޴�ȭ�� ���

void ShowRentInfo(cusInfo *Cus); // �뿩���� ���

void Show_SEACHING(void); // ��ȸ���� �޴� ���

void ShowCustomerInfoContinue(cusInfo * pCus); // Ư�� ISBN�� DVD �뿩�� �������

void ShowDVDRentInfo(RentInfo dvd); // Ư������ �Ⱓ�� �뿩�̷� �������

#endif // !__SCREENOUT_H__