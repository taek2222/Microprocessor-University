#include <stdio.h>
#include "MyCGI_web.h"

void MyCGI_web(char* data, char* time)
{
	char* sp, * ep;
	printf("Content-Type: text/html; charset=euc-kr\n\n");
	printf("<!DOCTYPE HTML PUBLIC \" -//W3C//DTD HTML 4.0//EN\">\n");
	printf("<html>\n");
	printf("    <head>\n");
	printf("               <title> MyCGI.exe(Dynamic Web Page) </title> \n");
	printf("    </head>\n");
	printf("    <body>\n");
	printf("               <H2> lot Testing(MyCGI - dynamic web page) </H2>\n");
	printf("               <HR>\n");
	for (sp = ep = data; *ep; ep++) { // 없어도 출력 가능.
		if (*ep == '\n') { // 줄 바꿈 조건문
			*ep = '\0'; // 널 문자
			printf("%s\n<BR>", sp); // 줄 내림 이전까지만 출력
			sp = ep + 1; // 그 다음 문자열
		}
	}
	printf_s("%s\n<BR>\n", sp);
	printf_s("%s\n<BR>\n", time);
	printf("     </body>\n");
	printf("</html>\n");
}