#include <Windows.h>
#include <stdio.h>

int main()
{
	HWND hWnd = FindWindow(TEXT("���³�����ʿ"),TEXT("���³�����ʿ"));//����DNF�Ĵ��ھ��������
	if (hWnd == NULL)//�жϴ��ھ���Ƿ����
	{
		printf("δ�ҵ�����\n");
	}
	DWORD pid = 0;
	GetWindowThreadProcessId(hWnd,&pid);//��ȡDNF����ID���
	if (pid == 0)//�жϽ���ID�Ƿ����
	{
		printf("δ�ҵ�����\n");
	}
	HANDLE hProcss = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);//��DNF���� ����Ȩ��
	if (hProcss == NULL)//�ж�DNF����ʱ�����
	{
		printf("δ�ҵ�����\n");
	}
	DWORD renwujizhi = 0x03160DD0;//���������ַ
	ReadProcessMemory(hProcss, (LPCVOID)renwujizhi, &renwujizhi, sizeof(renwujizhi), NULL);//��ȡ�����ַ
	DWORD Linshi1 = renwujizhi + 0x00002A98;//�����ַ+������ַ
	ReadProcessMemory(hProcss, (LPCVOID)Linshi1, &Linshi1, sizeof(Linshi1), NULL);//��ȡ�����ַ+������ַ
	DWORD Linshi2 = Linshi1 + 0x0000114C;//�����ַ+������ַ+�޵�ƫ��
	//�����޵�ƫ��
	DWORD a = 100;//�����޸��޵е�ֵ
	//�޵�
	WriteProcessMemory(hProcss, (LPVOID)Linshi2, &a, sizeof(a), NULL);//�޸��޵е�ֵΪ100
	printf("�õ�ַ�޸ĺ������Ϊ��%d\n", a);//����޸ĺ������
	printf("\n*******************************************\n");
	//==================================================================
	DWORD RenWuJiZhi = 0x03160DD0;//���������ַ
	ReadProcessMemory(hProcss, (LPCVOID)RenWuJiZhi, &RenWuJiZhi, sizeof(RenWuJiZhi), NULL);//��ȡ�����ַ
	DWORD BaTi = RenWuJiZhi + 0x000008AC;//�����ַ+����ƫ��
	//�������ƫ��
	DWORD b = 1;//�����޸İ����ֵ
	//����
	WriteProcessMemory(hProcss, (LPVOID)BaTi, &b, sizeof(b), NULL);//�޸İ����ֵΪ1
	printf("�õ�ַ�޸ĺ������Ϊ��%d\n", b);//����޸ĺ������
	printf("\n*******************************************\n");
	//==================================================================
	CloseHandle(hProcss);//�ر�DNF�����ֹ�߳�ռ��
	system("pause");//��ͣ �������û�����= = ��
	return 0;//����
}
