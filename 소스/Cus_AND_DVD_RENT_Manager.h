/*
	* ���   : MGR ����ó�� �Լ����� ����
	* �ۼ��� : LEE
	* �ۼ��� : 2019-03-11
	* ver    : 1.0
*/

#ifndef __CUS_AND_DVD_RENT_MGR_H__
#define __CUS_AND_DVD_RENT_MGR_H__

void Register_Customer(void); // ȸ�����

void Search_CusInfo(void); // ȸ�� �˻�

void Regist_DVD(void); // DVD ���

void Search_DVDInfo(void); // DVD ��ȸ

void Rent_DVD(void); // DVD �뿩

void Return_DVD(void); // DVD �ݳ�

void Show_DVDRent_ALL_CusInfo(void); // Ư�� DVD�� �뿩�� ��� �� ����

void ShowDVD_CusAllRentInfo(void); // Ư������ �Ⱓ�� �뿩�̷� ����

void ShowCus_DelayFee_ByOverdue(void); // ���� DVD��ü���� ��ȸ

#endif // !__CUS_AND_DVD_RENT_MGR_H__