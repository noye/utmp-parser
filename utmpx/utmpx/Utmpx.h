#pragma once
#include "stdafx.h"

#ifndef UTMP_H
#define UTMP_H

typedef struct utmpx
{
	wchar_t	* ut_type;
	int		  ut_pid;
	wchar_t * ut_line;
	wchar_t * ut_id;
	wchar_t * ut_user;
	wchar_t * ut_host;
	wchar_t * ut_time;

#if __WORDSIZE == 64 && defined __WORDSIZE_COMPAT32
	int32_t ut_session;
#else
	long ut_session;
#endif

} utmpx, *pUtmpx;


class Utmpx
{
private:
	std::list<utmpx> result;
	void convertTime(_In_ utmp *utmp_buf, _Inout_ wchar_t ** ut_time);
	wchar_t * MbsToWcs(const char *pBuf);

public:
	void parse(_In_ wchar_t * path);
	std::list<utmpx> getResult();
};

#endif // !UTMP_H

