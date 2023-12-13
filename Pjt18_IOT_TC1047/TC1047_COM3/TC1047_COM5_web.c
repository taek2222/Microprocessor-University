#include <stdio.h>
#include "TC1047_COM5_web.h"

void TC1047_COM5_web(char* data)
{
	char* sp, * ep;

	printf_s("Content-Type: text/html; charset=euc-kr\n\n");
	printf_s("<docTYPE HTML PUBLIC \"-//W3C//Dtd HTML 4.0//EN\">\n");
	printf_s("<html>\n");
	printf_s("		<head>\n");
	printf_s("			<title>TC1047_COM5.exe(IOT)</title>\n");
	printf_s("		</head>\n");
	printf_s("		<body>\n");
	printf_s("			<H2> IOT: TC1047_COM5(using a fixed serial port) </H2>\n");
	printf_s("			<HR>\n");

	for (sp = ep = data; *ep; ep++) {
		if (*ep == '\n') {
			*ep = '\0'; 
			printf("%s\n<BR>", sp); 
			sp = ep + 1;
		}
	}
	printf_s("%s\n<BR>\n", sp);
	printf_s("		</body>\n");
	printf_s("</html>\n");
}