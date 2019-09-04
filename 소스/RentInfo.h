#ifndef __RENTINFO_H__
#define __RENTINFO_H__

#include "cusInfo.h"
#include "dvdInfo.h"

typedef struct __RentInfo_
{
	char ISBN[ISBN_LEN];
	char ID[ID_LEN];
	unsigned int rentDay;
	int rentstate;
} RentInfo;

#endif // !__RENTINFO_H__

