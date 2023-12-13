#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "CGI_get_data.h"
#include "serial.h"

HANDLE openPort(char* port, char* msg) {
	HANDLE	hSerial;
	wchar_t	portNo[20], portBuf[20];
	DCB		dcbSerialParams = { 0, };
	COMMTIMEOUTS timeOuts = { 0 };

	MultiByteToWideChar(CP_ACP, 0, port, 8, portBuf, 16);
	swprintf_s(portNo, 20, L"\\\\.\\%s", portBuf);

	hSerial = CreateFile(portNo, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hSerial == INVALID_HANDLE_VALUE) {
		sprintf_s(msg, 64, "\nError: Open the serial port(%s)...\n\n", port);
		return INVALID_HANDLE_VALUE;
	}
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (GetCommState(hSerial, &dcbSerialParams) == FALSE) {
		strcpy_s(msg, 64, "\nError: Get the COM state...\n\n");
		CloseHandle(hSerial); return INVALID_HANDLE_VALUE;
	}
	dcbSerialParams.BaudRate = CBR_115200;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (SetCommState(hSerial, &dcbSerialParams) == FALSE) {
		strcpy_s(msg, 64, "\nError: set the COM state(DCB Structure)...\n\n");
		CloseHandle(hSerial); return INVALID_HANDLE_VALUE;
	}
	timeOuts.ReadIntervalTimeout = 100;
	timeOuts.ReadTotalTimeoutConstant = 100;
	timeOuts.ReadTotalTimeoutMultiplier = 10;
	timeOuts.WriteTotalTimeoutConstant = 100;
	timeOuts.WriteTotalTimeoutMultiplier = 100;

	if (SetCommTimeouts(hSerial, &timeOuts) == FALSE) {
		strcpy_s(msg, 32, "\nError: Set timeout to the serial port...\n\n");
		CloseHandle(hSerial); return INVALID_HANDLE_VALUE;
	}
	return hSerial;
}

char* headLine[MAX_N_HEAD], * tailLine[MAX_N_TAIL];

DWORD readData(HANDLE hPort, int N_HEAD, int N_TAIL, char* data, char* msg) {
	char ch, *buf, i;
	DWORD nBytesRead;
	int nHead = 0, nTail = 0, cLen = 0;

	for (i = 0; i < N_HEAD; i++)
		headLine[i] = (char*)malloc(CHR_P_LINE);

	for (i = 0; i < N_TAIL; i++)
		tailLine[i] = (char*)malloc(CHR_P_LINE);

	for (buf = headLine[nHead++]; ; ) {
		if (ReadFile(hPort, &ch, sizeof(ch), &nBytesRead, NULL) == FALSE) {
			strcpy_s(msg, 64, "\nError: Read from the serial port...\n\n");
			return 0;
		}
		if (!nBytesRead) {
			buf[cLen] = '\0';
			break;
		}
		buf[cLen++] = ch;

		if (ch == '\n') {
			buf[cLen] = '\0';
			if (nHead < N_HEAD) buf = headLine[nHead++];
			else				buf = tailLine[nTail++ % N_TAIL];
			cLen = 0;
		}
	}
	for (i = 0, buf = data; i < nHead; i++) {
		sprintf_s(buf, 128, "%s", headLine[i]);
		buf += (int)strlen(buf);
	}

	sprintf_s(buf, 128, ":::\n");
	buf += (int)strlen(buf);

	if (nTail > N_TAIL) i = nTail % N_TAIL, nTail = N_TAIL;
	else	i = 0;

	for (int j = 0; j < nTail; j++) {
		sprintf_s(buf, 128, "%s", tailLine[i++ % N_TAIL]);
		buf += strlen(buf);
	}

	for (i = 0; i < N_HEAD; i++)
		free(headLine[i]);

	for (i = 0; i < N_TAIL; i++)
		free(tailLine[i]);

	return nHead + nTail;
}

DWORD wirteCommand(HANDLE hPort, char* cmd, char* msg) {
	DWORD	Status, nBytesWritten;
	char buf[64];

	sprintf_s(buf, 64,  "%c%s\n%c", '\33', cmd, '\33');

	Status = WriteFile(hPort, buf, (DWORD)strlen(buf), &nBytesWritten, NULL);
	if (Status == FALSE) {
		strcpy_s(msg, 64, "\nError: wirte to the serial port...\n\n");
		return 0;
	}
	return nBytesWritten;
}