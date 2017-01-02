#include "stdafx.h"
#include "Utmpx.h"

void Utmpx::convertTime(utmp *utmp_buf, wchar_t ** ut_time)
{
	char * time = new char[40];

	time_t t = (time_t)utmp_buf->ut_tv.tv_sec;
	struct tm time_info = { 0 };
	localtime_s(&time_info, &t);
	asctime_s(time, sizeof(struct tm), &time_info);

	*ut_time = MbsToWcs(time);

	delete time;
}

wchar_t * Utmpx::MbsToWcs(const char * pBuf)
{
	if (NULL == pBuf) return NULL;

	int OutLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pBuf, -1, NULL, 0);

	wchar_t *OutWchar = new wchar_t[OutLen * sizeof(wchar_t)];

	if (NULL == OutWchar) return NULL;

	RtlZeroMemory(OutWchar, OutLen);

	if (MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pBuf, -1, OutWchar, OutLen) == 0)
	{
		return NULL;
	}

	return OutWchar;
}

void Utmpx::parse(wchar_t * path)
{
	FILE			*utmp_file_ptr;
	struct utmp		utmp_buf;

	_wfopen_s(&utmp_file_ptr, path, L"rb");

	if (utmp_file_ptr == NULL)
	{
		_wperror(path);
		return;
	}

	while (fread(&utmp_buf, sizeof(utmp_buf), 1, utmp_file_ptr))
	{
		utmpx utmp = { 0 };
		convertTime(&utmp_buf, &utmp.ut_time);

		if (utmp_buf.ut_type == RUN_LVL)
		{
			utmp.ut_type = L"RUN_LVL";
			utmp.ut_user = MbsToWcs(utmp_buf.ut_user);
			utmp.ut_host = MbsToWcs(utmp_buf.ut_host);
		}

		else if (utmp_buf.ut_type == BOOT_TIME)
		{
			utmp.ut_type = L"BOOT_TIME";
			utmp.ut_user = MbsToWcs(utmp_buf.ut_user);
			utmp.ut_host = MbsToWcs(utmp_buf.ut_host);
		}

		else if (utmp_buf.ut_type == INIT_PROCESS)
		{
			utmp.ut_type = L"INIT_PROCESS";
			utmp.ut_line = MbsToWcs(utmp_buf.ut_line);
			utmp.ut_id = MbsToWcs(utmp_buf.ut_id);
		}

		else if (utmp_buf.ut_type == LOGIN_PROCESS)
		{
			utmp.ut_type = L"LOGIN_PROCESS";
			utmp.ut_pid = utmp_buf.ut_pid;
			utmp.ut_line = MbsToWcs(utmp_buf.ut_line);
			utmp.ut_user = MbsToWcs(utmp_buf.ut_user);
			utmp.ut_host = MbsToWcs(utmp_buf.ut_host);
		}

		else if (utmp_buf.ut_type == USER_PROCESS)
		{
			utmp.ut_type = L"USER_PROCESS";
			utmp.ut_pid = utmp_buf.ut_pid;
			utmp.ut_line = MbsToWcs(utmp_buf.ut_line);
			utmp.ut_user = MbsToWcs(utmp_buf.ut_user);
			utmp.ut_host = MbsToWcs(utmp_buf.ut_host);
		}

		else if (utmp_buf.ut_type == DEAD_PROCESS)
		{
			utmp.ut_type = L"DEAD_PROCESS";
			utmp.ut_line = MbsToWcs(utmp_buf.ut_line);
			utmp.ut_id = MbsToWcs(utmp_buf.ut_id);
		}

		this->result.push_back(utmp);
	}

	fclose(utmp_file_ptr);
}

std::list<utmpx> Utmpx::getResult()
{
	return this->result;
}
