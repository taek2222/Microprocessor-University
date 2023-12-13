#include <stdio.h>
#include "MyCGI_web.h"
#include <time.h> // 시간 헤더

int main()
{
	char data[64];

	time_t t = time(NULL); // 현재 시간 출력 해주는 부분
	char* tp = ctime(&t);

	sprintf_s(data, 64, "Current temperature is 10 degree."); // data 배열에 문자열 복사

	MyCGI_web(data, tp); // 웹 사이트 data 전송 // 시간 출력 시 tp 전송

	return 0;
}