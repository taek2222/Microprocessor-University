#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queryGet.h"
#include "IOT_Query_web.h"
#include "CGI_get_data.h"

int main(void) {
	char port[32], cmd[32], * data, errmsg[64] ;

	data = (char*)malloc((DFL_N_HEAD + DFL_N_TAIL) * CHR_P_LINE);
	if (!queryGet(port, cmd, errmsg))
		strcpy_s(data, 64, errmsg);
	else
		CGI_get_data(port, cmd, DFL_N_HEAD, DFL_N_TAIL, data);
	IOT_Query_web(data);

	free(data);
}