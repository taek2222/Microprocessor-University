#include <stdio.h>
#include "MyCGI_web.h"
#include <time.h> // �ð� ���

int main()
{
	char data[64];

	time_t t = time(NULL); // ���� �ð� ��� ���ִ� �κ�
	char* tp = ctime(&t);

	sprintf_s(data, 64, "Current temperature is 10 degree."); // data �迭�� ���ڿ� ����

	MyCGI_web(data, tp); // �� ����Ʈ data ���� // �ð� ��� �� tp ����

	return 0;
}