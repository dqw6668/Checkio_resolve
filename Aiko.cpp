#include <Windows.h>
#include <stdio.h>



DWORD �����ַ = 0x039B4230;
DWORD ���ֻ�ַ = 0x038D1264;
DWORD ���ܻ�ַ = 0x039FE3D8;
DWORD ���ܻ�ַ = 0x039FE378;
DWORD ���ܲ���1 = 0x03490A80;
DWORD ���ܲ���2 = 0x03490C80;
DWORD �޵�call = 0x026569A0;
DWORD ������ = 0x00005AA0;
DWORD ������ƫ�� = 0x00000084;
DWORD ���ܵȼ�ƫ�� = 0x000006F0;
DWORD ������ȴƫ�� = 0x00000300;
DWORD �Զ�ʰȡ = 0x01849D8B;
DWORD �����Χ = 0x01849D5D;
DWORD �̵��ַ = 0x038D2F30;
DWORD ���ȹ��� = 0x0197E320;


DWORD pid = 0;

int ���ڴ�����(int Pid, int address)
{
	HANDLE hProcess;
	LPVOID ��������;
	SIZE_T length = 4;//����
	if (Pid == -1)
	{
		hProcess = GetCurrentProcess(); //�򿪵�ǰ����
	}
	else
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)Pid);//PROCESS_VM_READ

	}
	int abb;
	abb = ReadProcessMemory(hProcess, (LPCVOID)address, &��������, length, FALSE);//�ڴ������
	CloseHandle(hProcess);
	return (int)��������;
}

BOOL  д�ڴ�����(int pid, int address, int data)
{
	HANDLE hProcess;
	if (pid == -1)
	{
		hProcess = GetCurrentProcess(); //�򿪵�ǰ����
	}
	else
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);//PROCESS_VM_READ

	}

	BOOL a = WriteProcessMemory(hProcess, (LPVOID)address, (LPCVOID)&data, 4, 0);

	CloseHandle(hProcess);//�رն���


	return a;




}

byte *p;
byte *���ڴ��ֽڼ�(int Pid, int address, int length)
{
	HANDLE hProcess;
	//fhbyte = {};
	if (Pid == -1)
	{
		hProcess = GetCurrentProcess(); //�򿪵�ǰ����
	}
	else
	{
		//hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)����ID);//PROCESS_VM_READ
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, Pid);
	}

	p = new byte[length];//ȡ�հ��ֽڼ������洢������ 
	memset(p, 0, length);//�������Ļ�����
	ReadProcessMemory(hProcess, (LPCVOID)address, p, length, NULL);

	CloseHandle(hProcess);//�رն���

	return p;//���ﷵ�ض�ȡ�����ֽڼ����׵�ַ


}


BOOL д�ڴ��ֽڼ�(int Pid, int address, byte data[], int length)
{
	HANDLE hProcess;
	if (Pid == -1)
	{
		hProcess = GetCurrentProcess(); //�򿪵�ǰ����
	}
	else
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)Pid);//PROCESS_VM_READ

	}

	BOOL a = WriteProcessMemory(hProcess, (LPVOID)address, (LPCVOID)data, length, 0);
	CloseHandle(hProcess);//�رն���
	return a;
}


void ����(int ��ַ, int ��ֵ)
{
	int edi, ecx, eax, esi, edx, ss;
	ecx = ��ַ;
	eax = ���ڴ�����(pid, ���ܻ�ַ);
	eax = eax + 1;
	д�ڴ�����(pid, 0x39FE3D8, eax);
	edx = eax;
	edx >>= 8;
	edx <<= 24;
	edx >>= 24;
	edx = ���ڴ�����(pid, edx * 2 + ���ܲ���1);
	edx = WORD(edx);
	eax <<= 24;
	eax = eax = 24;
	ss = ���ڴ�����(pid, eax * 2 + ���ܲ���2);
	ss = WORD(ss);
	edx = edx^ ss;
	eax = edx;
	eax = WORD(eax);
	esi = ��ֵ;
	edx = esi >> 16;
	Sleep(10);
	ss = WORD(esi);
	edx = edx + ss;
	edx = edx^ eax;
	edi = edx;
	edx = eax;
	eax <<= 16;
	eax = eax + edx;
	esi = ��ֵ;
	eax = eax^esi;
	esi = ��ַ + 4;
	д�ڴ�����(pid, esi, eax);
	eax = ���ڴ�����(pid, ��ַ);
	esi = ���ڴ�����(pid, ���ܻ�ַ);
	ecx = edi;
	ecx <<= 16;
	ecx = ecx + edx;
	edx = eax;
	edx >>= 16;
	edx = ���ڴ�����(pid, esi + edx * 4 + 36);
	eax = WORD(eax);
	д�ڴ�����(pid, edx + eax * 4 + 8468, ecx);

}


int ����(int ��ַ)
{
	int eax, esi, edx;
	eax = ���ڴ�����(pid, ��ַ);
	esi = ���ڴ�����(pid, ���ܻ�ַ);
	edx = eax;
	edx >>= 16;
	edx = ���ڴ�����(pid, esi + edx * 4 + 36);
	eax = WORD(eax);
	eax = ���ڴ�����(pid, edx + eax * 4 + 8468);
	eax = WORD(eax);
	edx = eax;
	esi = edx;
	esi <<= 16;
	esi = esi + edx;
	edx = ���ڴ�����(pid, ��ַ + 4);
	eax = esi^edx;
	return eax;

}

void ����()
{
	����(���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x2B0C) + 0x97C, 600);//����
	//Sleep(500);
	����(���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x2B0C) + 0x994, 500);//����
	//Sleep(500);
	����(���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x2B0C) + 0x99C, 800);//ʩ��
}

void �;�()
{
	����(���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x2B0C) + 0x5FC, 0);//��װ �������;�
	//Sleep(500);
	����(���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x2B14) + 0x5FC, 0);//��װ
	//Sleep(500);
	����(���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x2B10) + 0x5FC, 0);//ͷ��
	//Sleep(500);
	����(���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x2B18) + 0x5FC, 0);//Ь��
	//Sleep(500);
	����(���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x2B1C) + 0x5FC, 0);//����
	//Sleep(500);
	����(���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x2B04) + 0x5FC, 0);//����
}

void �޵�Call(int ����ָ��, int ����)
{
	__asm{

		mov ecx, dword ptr ds : [����ָ��]
			mov esi, dword ptr ss : [ecx]
			push - 1
			push 1
			push ����
			push 1
			call �޵�call

	     }

}


void ��CD()
{
	int ����a=0, ����s=0, ����d=0, ����f=0, ����g=0, ����h=0, ����q=0, ����w=0, ����e=0, ����r=0, ����t=0, ����y=0;
    ����a = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ)+ ������) +������ƫ��) + 0x00000000) + ���ܵȼ�ƫ��);
	����s = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000004) + ���ܵȼ�ƫ��);
	����d = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000008) + ���ܵȼ�ƫ��);
	����f = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x0000000C) + ���ܵȼ�ƫ��);
	����g = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000010) + ���ܵȼ�ƫ��);
	����h = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000014) + ���ܵȼ�ƫ��);
	����q = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000318) + ���ܵȼ�ƫ��);
	����w = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x0000031C) + ���ܵȼ�ƫ��);
	����e = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000320) + ���ܵȼ�ƫ��);
	����r = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000324) + ���ܵȼ�ƫ��);
	����t = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000328) + ���ܵȼ�ƫ��);
	����y = ����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x0000032C) + ���ܵȼ�ƫ��);
	
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000000) + ������ȴƫ��) + (����a - 1) * 8, 0);
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000004) + ������ȴƫ��) + (����s - 1) * 8, 0);
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000008) + ������ȴƫ��) + (����d - 1) * 8, 0);
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x0000000C) + ������ȴƫ��) + (����f - 1) * 8, 0);
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000010) + ������ȴƫ��) + (����g - 1) * 8, 0);
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000014) + ������ȴƫ��) + (����h - 1) * 8, 0);
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000318) + ������ȴƫ��) + (����q - 1) * 8, 0);
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x0000031C) + ������ȴƫ��) + (����w - 1) * 8, 0);
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000320) + ������ȴƫ��) + (����e - 1) * 8, 0);
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000324) + ������ȴƫ��) + (����r - 1) * 8, 0);
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x00000328) + ������ȴƫ��) + (����t - 1) * 8, 0);
	����(���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + ������) + ������ƫ��) + 0x0000032C) + ������ȴƫ��) + (����y - 1) * 8, 0);
}

void �޵а���()
{
	д�ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x838, 1);
	д�ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x924, 100);
}

void ����΢��()
{
	����(���ڴ�����(pid, ���ڴ�����(pid, �����ַ) + 0x2B0C) + 0x7D4, 800);//��ά
}












	int main()
	{   
		printf("        Aiko��ing��Ȩ���С�\n");
		printf("\n");
		printf("��������ȫ��ѣ��벻Ҫ������ҵ;����\n");
		printf("*****************************************\n");
		printf("*****************************************\n");
		HWND hWnd = FindWindow(TEXT("���³�����ʿ"), TEXT("���³�����ʿ"));//����DNF�Ĵ��ھ��������
		if (hWnd == NULL)//�жϴ��ھ���Ƿ����
		{
			printf("δ�ҵ�����\n");
		}

		GetWindowThreadProcessId(hWnd, &pid);//��ȡDNF���̾��
		if (pid == 0)//�жϽ����Ƿ����
		{
			printf("δ�ҵ�����\n");
		}
		HANDLE hProcss = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);//��DNF���� ����Ȩ��
		if (hProcss == NULL)//�ж�DNF����ʱ�����
		{
			printf("δ�ҵ�����\n");
		}
		else
		{
			printf("----------���ӽ��̳ɹ�---------��\n");
			SYSTEMTIME sys;
			GetLocalTime(&sys);
			printf("\n");
			printf("��ǰʱ��Ϊ��%4d/%02d/%02d %02d:%02d:%02d.%03d ����%1d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, sys.wDayOfWeek);
			printf("\n");
			//���߳�();
			if (���ڴ�����(pid, �����ַ) >88888888)
			{
				printf("*****************************************\n");
				����(���ڴ�����(pid, ���ֻ�ַ) + 0x110, 6666666);
				�޵а���();
				����();
				��CD();
				printf("�޸ĳɹ�\n");
				printf("*****************************************\n");

			}
			else
			{
				printf("*****************************************\n");
				printf("��Ϸû��ͼ�꣬��ȡ�ڴ�ʧ�ܣ�\n");
				printf("*****************************************\n");
			}

		}
			
		


		//b = ���ڴ�����(pid, BaTi);
		//printf("�õ�ַ�޸ĺ������Ϊ��%d\n", b);//����޸ĺ������
		//==================================================================
		CloseHandle(hProcss);//�ر�DNF�����ֹ�߳�ռ��
		system("pause");//��ͣ �������û�����= = ��
		return 0;//����

	}
