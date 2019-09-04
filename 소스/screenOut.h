/*
	* 기능   : 콘솔출력을 위한 함수들의 선언
	* 작성자 : LEE
	* 작성일 : 2019-03-11
	* ver    : 1.0
*/

#ifndef __SCREENOUT_H__
#define __SCREENOUT_H__

#include "cusInfo.h"
#include "dvdInfo.h"
#include "RentInfo.h"

void ShowMenu(void); // 고객 프로그램을 사용하기 위한 메뉴 출력

void ShowCustomerInfo(cusInfo * pCus); // 고객정보 출력

void ShowGenre(int gen); // DVD장르 선택

void ShowDVDInfo(dvdInfo * pDVD); // DVD정보 출력

void Show_RENT_AND_RETURN(void); // 대여 / 반납 메뉴화면 출력

void ShowRentInfo(cusInfo *Cus); // 대여정보 출력

void Show_SEACHING(void); // 조회선택 메뉴 출력

void ShowCustomerInfoContinue(cusInfo * pCus); // 특정 ISBN의 DVD 대여고객 정보출력

void ShowDVDRentInfo(RentInfo dvd); // 특정고객의 기간별 대여이력 정보출력

#endif // !__SCREENOUT_H__