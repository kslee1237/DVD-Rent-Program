/*
	* 기능   : MGR 업무처리 함수들의 선언
	* 작성자 : LEE
	* 작성일 : 2019-03-11
	* ver    : 1.0
*/

#ifndef __CUS_AND_DVD_RENT_MGR_H__
#define __CUS_AND_DVD_RENT_MGR_H__

void Register_Customer(void); // 회원등록

void Search_CusInfo(void); // 회원 검색

void Regist_DVD(void); // DVD 등록

void Search_DVDInfo(void); // DVD 조회

void Rent_DVD(void); // DVD 대여

void Return_DVD(void); // DVD 반납

void Show_DVDRent_ALL_CusInfo(void); // 특정 DVD를 대여한 모든 고객 정보

void ShowDVD_CusAllRentInfo(void); // 특정고객의 기간별 대여이력 정보

void ShowCus_DelayFee_ByOverdue(void); // 고객별 DVD연체정보 조회

#endif // !__CUS_AND_DVD_RENT_MGR_H__