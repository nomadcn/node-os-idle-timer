#include <windows.h>
#include <stdint.h>

/**
 * get user's input idle time in millisecond.
 */
int64_t getIdleTime_ms()
{
	LASTINPUTINFO lastInputInfo;
	memset(&lastInputInfo, 0, sizeof(lastInputInfo));
	lastInputInfo.cbSize = sizeof(lastInputInfo);

	BOOL ret = GetLastInputInfo(&lastInputInfo);
	if (ret)
	{
		const int64_t idleTime = (int64_t)(GetTickCount() - lastInputInfo.dwTime);
		return idleTime;
	}

	return -1;
}
