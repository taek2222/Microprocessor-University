#pragma once

#define MAX_N_HEAD 100
#define MAX_N_TAIL 100

#define DFL_N_HEAD 10
#define DFL_N_TAIL 10

#define CHR_P_LINE 80

void CGI_get_data(char* port, char* cmd, int nHeadLine, int nTailLinem, char* data);