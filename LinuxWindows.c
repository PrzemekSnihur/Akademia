#ifdef __unix__
#include <unistd.h>
 // LINUX
#elif defined(_WIN32) || defined(WIN32)
#define OS_Windows 1
#include <windows.h>
#endif // WINDOWS

#include <stdio.h>

void _sleep(unsigned int time)
{
    #ifdef __unix__
        sleep(time);
    #endif // LINUX
    #ifdef OS_Windows
        Sleep(time * 1000);
    #endif // WINDOWS
}

int main()
{
    printf("Costam\n");
	_sleep(5);
	printf("Costam\n"); // - I would like this to work on Linux and Windows

	return 0;
}
