/*
	* 기능   : 고객 정보 저장 및 참조 함수들의 선언
	* 작성자 : LEE
	* 작성일 : 2019-03-11
	* ver    : 1.0
*/

#ifndef __CUSACCESS_H__
#define __CUSACCESS_H__

#include "cusInfo.h"

int AddCusInfo(char *ID, char *name, char *num, int delay_fee); // cusInfo 저장공간 할당 및 구조체 배열에 저장

cusInfo * GetCusPtrByID(char *ID); // 해당 고객 ID의 정보를 가지고 있는 포인터 반환

int IsregistID(char *ID); // 가입된 ID인지 체크

void FILE_SAVE_CusInfo(void); // 추가되는 고객정보 파일저장

void BACKUP_FILE_SAVE_CusInfo(void); // 고객정보 파일 백업

#endif // !__CUSACCESS_H__
