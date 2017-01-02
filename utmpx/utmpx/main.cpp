#include "stdafx.h"
#include "Utmpx.h"


int wmain(int argc, wchar_t *argv[])
{
	if (argc == 2)
	{
		Utmpx * utmp = new Utmpx();
		utmp->parse(argv[1]);

		std::list<utmpx> result = utmp->getResult();
		std::list<utmpx>::iterator it = result.begin();
		
		while (result.end() != it)
		{
			wprintf_s(L"[type] : %ws\n", it->ut_type);

			if (it->ut_pid != NULL)
				wprintf_s(L"[pid]  : %wd\n", it->ut_pid);

			if (it->ut_line != NULL)
				wprintf_s(L"[line] : %ws\n", it->ut_line);

			if (it->ut_id != NULL)
				wprintf_s(L"[id]   : %ws\n", it->ut_id);

			if(it->ut_user != NULL)
				wprintf_s(L"[user] : %ws\n", it->ut_user);
			
			if(it->ut_host != NULL)
				wprintf_s(L"[host] : %ws\n", it->ut_host);
			
			wprintf_s(L"[time] : %ws\n", it->ut_time);
			wprintf_s(L"\n");

			it++;
		}
	}
	else
		wprintf_s(L"utmpx.exe [fileName]\n");

    return 0;
}

