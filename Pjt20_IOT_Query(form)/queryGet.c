#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queryGet.h"

int queryGet(char* port, char* cmd, char* msg) {
	char* qp, * pp, * cp, * dp = NULL, * content_length;
	int i_content_length, i;

	char* request_method = getEnv("REQUEST_METHOD");
	char* content_type = getEnv("CONTENT_TYPE");

	if (request_method == NULL) {
		strcpy_s(msg, 64, "Error: html method not defined... \n\n");
		return 0;
	}

	if (strcmp(request_method, "GET") || !(qp = getEnv("QUERY_STRING"))) {
		strcpy_s(msg, 64, "Error: html QUERY_STRING not defined ... \n\n");
		return 0;
	}

	i_content_length = (int)strlen(qp);
	
	if (!(pp = strstr(qp, "PORT="))) {
		strcpy_s(msg, 64, "Error: 'PORT' field not defined ...\n\n");
		return 0;
	}
	pp = pp + 5;
	if (*pp == '&' || *pp == '.') {
		strcpy_s(msg, 64, "Error: 'PORT' value not defined ...\n\n");
		return 0;
	}

	if (!(cp = strstr(qp, "CMD="))) {
		strcpy_s(msg, 64, "Error : 'CMD' field not define...\n\n");
		return 0;
	}

	cp = cp + 4;
	if (*cp == '&' || *cp == '.') {
		strcpy_s(msg, 64, "Error: 'CMD' value not defined ... \n\n");
		return 0;
	}

	pp = strtok_s(pp, " \n\r\t&.", &dp);
	cp = strtok_s(cp, " \n\r\t&.", &dp);

	decode(port, pp);
	decode(cmd, cp);

	return 1;

}

char* getEnv(char* en) {
	char* ep;
	size_t el;

	if (_dupenv_s(&ep, &el, en))
		return NULL;
	return(ep);
}

void decode(char* bfp, char* qp)
{
	while (*qp) {
		if (*qp == '%') *bfp++ = ' ', qp += 3;
		else
			*bfp++ = *qp++;
	}
	*bfp = '\0';
}