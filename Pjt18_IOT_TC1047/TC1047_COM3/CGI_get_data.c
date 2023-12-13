#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"
#include "CGI_get_data.h"

void CGI_get_data(char* port, char* cmd, int nHeadLine, int nTailLine, char* data)
{
	HANDLE hSerialPort;
	char errmsg[64];

	if ((hSerialPort = openPort(port, errmsg)) == INVALID_HANDLE_VALUE) {
		strcpy_s(data, 64, errmsg);
		return;
	}
	if (!wirteCommand(hSerialPort, cmd, errmsg) || !readData(hSerialPort, nHeadLine, nTailLine, data, errmsg))
		strcpy_s(data, 64, errmsg);

	CloseHandle(hSerialPort);
	return;
}