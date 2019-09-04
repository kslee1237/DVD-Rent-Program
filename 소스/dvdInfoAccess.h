#ifndef __DVDINFOACCESS_H__
#define __DVDINFOACCESS_H__

#include "dvdInfo.h"

int AddDVDInfo(char *ISBN, char *title, int genre, int rentstate); // dvdInfo 저장공간 할당 및 구조체 배열에 저장

dvdInfo *GetDVDPtrByISBN(char *ISBN); // 해당 ISBN의 정보를 담고 있는 변수의 포인터 반환

int IsRegistISBN(char *ISBN); // 기 등록된 ISBN인지 체크

int Get_RENT_STATE_DVD(char *ISBN); // DVD 대여상태 정보

int Set_Rent_DVD(char *ISBN); // DVD 대여상태로 변환

int Set_Return_DVD(char *ISBN); // DVD 반납(대여가능)상태로 변환

void FILE_SAVE_DVDInfo(void); // 추가되는 DVD정보 파일저장

void BACKUP_FILE_SAVE_DVDInfo(void); // DVD 정보파일 백업

#endif // !__DVDINFOACCESS_H__