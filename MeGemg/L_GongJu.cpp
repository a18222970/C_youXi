#include "pch.h"
#include "L_GongJu.h"


L_GongJu l_gong_ju1;


/*����PDI,��ó����ڴ���ʼ��ַ*/
PVOID L_GongJu::get_ji_zhi_1(DWORD pid)
{
	PVOID pProcessImageBase = NULL;
	MODULEENTRY32 me32 = { 0 };
	me32.dwSize = sizeof(MODULEENTRY32);

	// ��ȡָ������ȫ��ģ��Ŀ���
	HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (INVALID_HANDLE_VALUE == hModuleSnap)
	{

		return pProcessImageBase;
	}

	// ��ȡ�����е�һ����Ϣ
	BOOL bRet = Module32First(hModuleSnap, &me32);
	if (bRet)
	{
		// ��ȡ���ػ�ַ
		pProcessImageBase = (PVOID)me32.modBaseAddr;
	}

	// �رվ��
	CloseHandle(hModuleSnap);
	return pProcessImageBase;
}

/*����PDI,��ó����ڴ���ʼ��ַ*/
PVOID L_GongJu::get_ji_zhi_2(DWORD pid)
{
	PVOID n_pProcessImageBase = NULL;
	HANDLE n_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);//�򿪽���, ��ȡ���̾��
	if (NULL == n_hProcess)
	{
		AfxMessageBox(L"��ȡ���ʧ��");
		return n_pProcessImageBase;
	}

	// ��������ģ��,
	HMODULE hModule[100] = { 0 };
	DWORD dwRet = 0;
	BOOL bRet = EnumProcessModules(n_hProcess, (HMODULE*)(hModule), sizeof(hModule), &dwRet);
	if (FALSE == bRet)
	{
		CloseHandle(n_hProcess);
		AfxMessageBox(L"��ȡ����ģ���ڴ��ַʧ��");
		return n_pProcessImageBase;
	}
	// ��ȡ��һ��ģ����ػ�ַ
	n_pProcessImageBase = hModule[0];
	// �رվ��
	CloseHandle(n_hProcess);

	return n_pProcessImageBase;
}

/*��ȡ��Ϸ(ģ��)��ַ*/
PVOID L_GongJu::get_chen_xu_ji_zhi(LPCSTR a, LPCSTR b)
{
	HWND n_juBing = FindWindowA("Sword2 Class", "Sword2 Window");//��ȡ��Ϸ���ھ��
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing)
	{
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//��ȡ���� n_jinCheng ��PDI n_pdi 
		if (!n_jinCheng)
		{
			return (PVOID)-3;

		}
		AfxMessageBox((LPCTSTR)n_pdi);
		AfxMessageBox((wchar_t)"moohjjkh");
	}
	else
	{
		return (PVOID)-2;
	}
	// std::cout << "jubeng" << n_jinCheng << "  jingcheng:" << n_pdi << std::endl;

	PVOID n_jiZhi = NULL;
	n_jiZhi = get_ji_zhi_2(n_pdi);
	if (NULL == n_jiZhi)
	{
		return NULL;
	}
	return n_jiZhi;
}

/* �򿪽���, ��ȡģ����̾�� ����:����ģ��PID */
HANDLE L_GongJu::get_moKai_ju_bing(DWORD pid)
{
	HANDLE n_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);//�򿪽���, ��ȡ���̾��
	CloseHandle(n_hProcess);// �رվ��
	return n_hProcess;

}

/*��ȡ����*/
DWORD L_GongJu::get_jin_cheng(LPCSTR a, LPCSTR b)
{
	HWND n_juBing = FindWindowA("Sword2 Class", "Sword2 Window");//��ȡ��Ϸ���ھ��
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing)
	{
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//��ȡ���� n_jinCheng ��PDI n_pdi 
		if (n_jinCheng)
		{
			return n_jinCheng;

		}
		else
		{
			return (DWORD)-3;
		}
	}
	else
	{
		return (DWORD)-2;
	}
	return n_jinCheng;
}

/*��ȡ���
����a: ���򴰿�����
����b: ���򴰿ڱ���
*/
HWND L_GongJu::get_ju_bing(LPCSTR a, LPCSTR b)
{
	HWND n_juBing = FindWindowA("Sword2 Class", "Sword2 Window");//��ȡ��Ϸ���ھ��
	if (n_juBing)
	{
		return n_juBing;

	}
	else
	{
		return (HWND)-2;
	}
	return n_juBing;
}

/*��ѯunsigned����,������ַ����
* ����1:���
* ����2:ʲô���͵�(һ�ζ�ȡ���ڴ泤��)�ڴ��ַ
*/
int L_GongJu::query_shu_ju(HANDLE ju_bing, unsigned nei_chun_di_zhi)
{
	int fan_hui_jg;
	SIZE_T du_qu_hp;
	/*ReadProcessMemory��ָ����ַ��Χ�ڵ����ݴ�ָ�����̵ĵ�ַ�ռ临�Ƶ���ǰ���̵�ָ��������*/
	ReadProcessMemory(ju_bing, (LPCVOID)nei_chun_di_zhi, (LPVOID)&fan_hui_jg, sizeof(fan_hui_jg), &du_qu_hp);

	return fan_hui_jg;
}

BOOL L_GongJu::query_shu_ju_kuai(HANDLE ju_bing, unsigned nei_chun_di_zhi, J_ti_qu_xin_xi* ren_wu_shu_xin)
{
	SIZE_T du_qu_hp;
	BOOL bRhm = ReadProcessMemory(ju_bing, (LPCVOID)nei_chun_di_zhi, (LPVOID)ren_wu_shu_xin, sizeof(J_ren_wu), &du_qu_hp);
	return bRhm;
}

void L_GongJu::xie_shu_ju(HANDLE ju_bing, unsigned nei_chun_di_zhi, int xr_shu_ju)
{
	/*WriteProcessMemory ��ָ���Ľ����н�����д���ڴ����򡣱���д���������򣬷��������ʧ�ܡ�*/
	WriteProcessMemory(ju_bing, (LPVOID)nei_chun_di_zhi, &xr_shu_ju, sizeof(xr_shu_ju), NULL);
}

BOOL L_GongJu::zhi_xing_1(int xiangMu, J_ti_qu_xin_xi* jieGouTi)
{
	char n_xue_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00,0x90 };//0x90 Ϊnop
	char n_xue_XG_2[]{ 0x81,0xFE, //cmp esi
					   0x00,0x00,0x00,0x00,      //4CE60C
					   0x75,0x02,                //jne 0247000A
					   0x31,0xFF,                //xor edi edi
					   0x8B,0xD0,                //mov edx eax
					   0x29,0xFA,                //sub edx ecx
					   0x39,0xCA,                //cmp edx ecx
					   0xE9,                     //jmp
					   0x00,0x00,0x00,0x00 };    //�����ַ=41FD67-��ǰ��ַ-5(����������ֽ�)
	char n_xue_XG_3[]{ 0x8B,0XD0,0X2B,0XD7,0X3B,0XD1 };//�ָ�
	char n_nei_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_nei_XG_2[]{ 0xC1,0xE1,0x06,
					   0x31,0xD2,
					   0x29,0xC1,
					   0xE9,
					   0x00,0x00,0x00,0x00 };
	char n_nei_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//�ָ�
	char n_ti_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_ti_XG_2[]{ 0xC1,0xE1,0x06,
					  0x31,0xD2,
					  0x29,0xC1,
					  0xE9,
					  0x00,0x00,0x00,0x00 };
	char n_ti_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//�ָ�

	HANDLE n_juBing = OpenProcess(PROCESS_ALL_ACCESS, false, jieGouTi->n_PDI);
	if (!n_juBing)
	{
		return FALSE;
	}
	else
	{
		LPVOID n_diZhi;
		LPVOID n_fenPei_diZhi;
		DWORD n_laShi = 0;
		BOOL n_pan_duan;
		int n_jmp_di_zhi;
		int* n_xr_di_zhi;
		int n_neiLi_di_zhi;
		int n_tiLi_di_zhi;
		if (!get_n_jianXia_zuoBi_kaiGuan())
		{
			printf("001");
			n_fenPei_diZhi = VirtualAllocEx(n_juBing, NULL, 512, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (!n_fenPei_diZhi)
			{
				CloseHandle(n_juBing);// �رս��̾��
				printf("�����ڴ�ʧ��");
				return FALSE;
			}
			else
			{
				set_Q_fenPei_diZhi(n_fenPei_diZhi);
				jieGouTi->n_fenPei_diZhi = n_fenPei_diZhi;
			}
		}
		n_diZhi = get_Q_fenPei_diZhi();
			switch (xiangMu)
			{
			case 1:
				if (!get_n_wuDi_kaiGuan())
				{
					printf("�����ڴ�: %p\n", n_diZhi);
					/*����ԭʼ����ִ�е�ַ*/
					n_jmp_di_zhi = 0x41FD67 - ((int)n_diZhi + 0x10) - 5; //����jmp��ǰҪ��ת�������ַ(������)
					n_xr_di_zhi = (int*)(n_xue_XG_2 + 0x11);   //����ֵΪ0xE9��0x00��λ��,������n_data��ָ�����0x11λ��
					n_xr_di_zhi[0] = n_jmp_di_zhi;  //��Ҫjmp��ת�ĵ�ַ��ʼλ 0x00 ���� (8�ֽ� ������)
					/*����ԭʼ���� jmp ********/

					/*cmp �Ƚ� ***********/
					n_xr_di_zhi = (int*)(n_xue_XG_2 + 0x2);   //����ֵΪcmp 0xFEҪ�Ƚϵ�ֵ 0x00 ��λ��
					n_xr_di_zhi[0] = 0x4CE60C;  //��cmpҪ�Ƚϵĵ�ַ���� 0x00,0x00,0x00,0x00
					/*cmp �Ƚ� ***********/

					/*д���ڴ�*/
					n_pan_duan = WriteProcessMemory(n_juBing, n_diZhi, n_xue_XG_2, sizeof(n_xue_XG_2), NULL);
					if (!n_pan_duan)
					{
						CloseHandle(n_juBing);// �رս��̾��
						return FALSE;
					}
					set_n_wuDi_kaiGuan(TRUE);
					set_n_jianXia_zuoBi_kaiGuan(TRUE);
				}
				/*�޸�Ѫ��Դ���� ����Ѫ�޵�*/
				n_jmp_di_zhi = (int)n_diZhi - 0x41FD61 - 0x5; //����jmp��ǰҪ��ת�ĵ�ַ(������)
				n_xr_di_zhi = (int*)(n_xue_XG_1 + 0x1);   //����ֵΪ0xE9���Ҫ��ת�ڴ��ַ����ʼλ��0x00
				n_xr_di_zhi[0] = n_jmp_di_zhi;  //��Ҫjmp��ת�ĵ�ַ��ʼλ�ô��� 0x00

				/*���Ķ�ָ�����̵������ַ�ռ��е����ύҳ������ı���,�ı��ڴ��ַ��������
				PAGE_EXECUTE_READWRITE ��ʾ�ɶ���д.VirtualProtectEx������ҪOpenProcess������ģ��*/
				VirtualProtectEx(n_juBing, (LPVOID)0x4FD61, sizeof(n_xue_XG_1), PAGE_EXECUTE_READWRITE, &n_laShi);

				/*д��*/
				n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x41FD61, n_xue_XG_1, sizeof(n_xue_XG_1), NULL);
				if (!n_pan_duan)
				{
					CloseHandle(n_juBing);// �رս��̾��
					return FALSE;
				}
				break;
			case 2:
				if (get_n_wuDi_kaiGuan())
				{
					/*���Ķ�ָ�����̵������ַ�ռ��е����ύҳ������ı���,�ı��ڴ��ַ��������*/
					VirtualProtectEx(n_juBing, (LPVOID)0x4FD61, sizeof(n_xue_XG_3), PAGE_EXECUTE_READWRITE, &n_laShi);

					/*д��*/
					n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x41FD61, n_xue_XG_3, sizeof(n_xue_XG_3), NULL);
					if (!n_pan_duan)
					{
						CloseHandle(n_juBing);// �رս��̾��
						return FALSE;
					}
					//set_n_wuDi_kaiGuan(FALSE);
				}
				break;
			case 3:
				n_neiLi_di_zhi = (int)jieGouTi->n_fenPei_diZhi + sizeof(n_xue_XG_2);
				if (!get_n_neiLi_kaiGuan())
				{
					printf("�����ڴ�: %p\n", n_neiLi_di_zhi);
					/*  n_jmp_di_zhi = 0x4262B3 - (n_neiLi_di_zhi + 0x7) - 0x5;
					��λҪ��ת��ԭʼ������ڴ��ַ,(E9�ĵ�ַ-e9��ǰ�����ڴ��ַ,
					��ȥE9+Ҫ���ص��ڴ��ַ,��5���ֽ�).  */
					n_jmp_di_zhi = 0x4262B8 - (n_neiLi_di_zhi + 0x7) - 0x5;
					/*׼��д�����ת��ԭʼ���봦���ڴ��ַ��д���ַ
					���������Ҳ�������Ϊ:��ָ�����n_xr_di_zhi��ָ��ָ�������ڵ�9����Ա����E9�����0x00*/
					n_xr_di_zhi = (int*)(n_nei_XG_2 + 0x8);
					/*��n_jmp_di_zhi������,�������9����Ա��ʼ���󰤸���Ա��ֵ
					n_xr_di_zhi[0]���ھ���ǰ���(int*)(n_nei_XG_2 + 0x8) */
					n_xr_di_zhi[0] = n_jmp_di_zhi;
					n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)n_neiLi_di_zhi, n_nei_XG_2, sizeof(n_nei_XG_2), NULL);
					if (!n_pan_duan)
					{
						CloseHandle(n_juBing);// �رս��̾��
						return FALSE;
					}
					set_n_neiLi_kaiGuan(true);
					set_n_jianXia_zuoBi_kaiGuan(TRUE);
				}
				/*n_jmp_di_zhi = (int)n_diZhi - 0x41FD61 - 0x5; //����jmp��ǰҪ��ת�ĵ�ַ(������)
				n_xr_di_zhi = (int*)(n_xue_XG_1 + 0x1);   //����ֵΪ0xE9���Ҫ��ת�ڴ��ַ����ʼλ��0x00
				n_xr_di_zhi[0] = n_jmp_di_zhi;  //��Ҫjmp��ת�ĵ�ַ��ʼλ�ô��� 0x00*/

				/*�޸�����ԭʼ����*/
				n_jmp_di_zhi = n_neiLi_di_zhi - 0x4262B3 - 0x5;
				n_xr_di_zhi = (int*)(n_nei_XG_1 + 0x1);
				n_xr_di_zhi[0] = n_jmp_di_zhi;
				/*���Ķ�ָ�����̵������ַ�ռ��е����ύҳ������ı���,�ı��ڴ��ַ��������
				PAGE_EXECUTE_READWRITE ��ʾ�ɶ���д.VirtualProtectEx������ҪOpenProcess������ģ��*/
				VirtualProtectEx(n_juBing, (LPVOID)0x4262B3, sizeof(n_nei_XG_1), PAGE_EXECUTE_READWRITE, &n_laShi);
				n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x4262B3, n_nei_XG_1, sizeof(n_nei_XG_1), NULL);
				if (!n_pan_duan)
				{
					CloseHandle(n_juBing);// �رս��̾��
					return FALSE;
				}
				break;
			case 4:
				/*�ָ�ԭʼ����*/
				/*���Ķ�ָ�����̵������ַ�ռ��е����ύҳ������ı���,�ı��ڴ��ַ��������
				PAGE_EXECUTE_READWRITE ��ʾ�ɶ���д.VirtualProtectEx������ҪOpenProcess������ģ��*/
				VirtualProtectEx(n_juBing, (LPVOID)0x4262B3, sizeof(n_nei_XG_3), PAGE_EXECUTE_READWRITE, &n_laShi);
				n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x4262B3, n_nei_XG_3, sizeof(n_nei_XG_3), NULL);
				if (!n_pan_duan)
				{
					CloseHandle(n_juBing);// �رս��̾��
					return FALSE;
				}
				break;
			case 5:
				n_tiLi_di_zhi = (int)get_Q_fenPei_diZhi() + sizeof(n_xue_XG_2) + sizeof(n_nei_XG_2);
				if (!get_n_tiLi_kaiGuan())
				{
					/*  n_jmp_di_zhi = 0x4262B3 - (n_neiLi_di_zhi + 0x7) - 0x5;
					��λҪ��ת��ԭʼ������ڴ��ַ,(E9�ĵ�ַ-e9��ǰ�����ڴ��ַ,
					��ȥE9+Ҫ���ص��ڴ��ַ,��5���ֽ�).  */
					n_jmp_di_zhi = 0x426238 - (n_tiLi_di_zhi + 0x7) - 0x5;
					/*׼��д�����ת��ԭʼ���봦���ڴ��ַ��д���ַ
					���������Ҳ�������Ϊ:��ָ�����n_xr_di_zhi��ָ��ָ�������ڵ�9����Ա����E9�����0x00*/
					n_xr_di_zhi = (int*)(n_ti_XG_2 + 0x8);
					/*��n_jmp_di_zhi������,�������9����Ա��ʼ���󰤸���Ա��ֵ
					n_xr_di_zhi[0]���ھ���ǰ���(int*)(n_nei_XG_2 + 0x8) */
					n_xr_di_zhi[0] = n_jmp_di_zhi;
					n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)n_tiLi_di_zhi, n_ti_XG_2, sizeof(n_ti_XG_2), NULL);
					if (!n_pan_duan)
					{
						CloseHandle(n_juBing);// �رս��̾��
						return FALSE;
					}
					set_n_tiLi_kaiGuan(true);
					set_n_jianXia_zuoBi_kaiGuan(TRUE);
				}
				/*�޸�����ԭʼ����*/
				n_jmp_di_zhi = n_tiLi_di_zhi - 0x426233 - 0x5;
				n_xr_di_zhi = (int*)(n_ti_XG_1 + 0x1);
				n_xr_di_zhi[0] = n_jmp_di_zhi;
				/*���Ķ�ָ�����̵������ַ�ռ��е����ύҳ������ı���,�ı��ڴ��ַ��������
				PAGE_EXECUTE_READWRITE ��ʾ�ɶ���д.VirtualProtectEx������ҪOpenProcess������ģ��*/
				VirtualProtectEx(n_juBing, (LPVOID)0x426233, sizeof(n_ti_XG_1), PAGE_EXECUTE_READWRITE, &n_laShi);
				n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x426233, n_ti_XG_1, sizeof(n_ti_XG_1), NULL);
				if (!n_pan_duan)
				{
					CloseHandle(n_juBing);// �رս��̾��
					return FALSE;
				}
				break;
			case 6:
				/*�ָ�ԭʼ����*/
				/*���Ķ�ָ�����̵������ַ�ռ��е����ύҳ������ı���,�ı��ڴ��ַ��������
				PAGE_EXECUTE_READWRITE ��ʾ�ɶ���д.VirtualProtectEx������ҪOpenProcess������ģ��*/
				VirtualProtectEx(n_juBing, (LPVOID)0x426233, sizeof(n_ti_XG_3), PAGE_EXECUTE_READWRITE, &n_laShi);
				n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x426233, n_ti_XG_3, sizeof(n_ti_XG_3), NULL);
				if (!n_pan_duan)
				{
					CloseHandle(n_juBing);// �رս��̾��
					return FALSE;
				}
				break;
			default:
				break;
			}
		return TRUE;


	}
	return TRUE;
}

BOOL L_GongJu::zhi_xing(J_ti_qu_xin_xi* jieGouTi)
{
	char n_xue_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00,0x90 };
	char n_xue_XG_2[]{ 0x81,0xFE, //cmp esi
					   0x00,0x00,0x00,0x00,      //4CE60C
					   0x75,0x02,                //jne 0247000A
					   0x31,0xFF,                //xor edi edi
					   0x8B,0xD0,                //mov edx eax
					   0x29,0xFA,                //sub edx ecx
					   0x39,0xCA,                //cmp edx ecx
					   0xE9,                     //jmp
					   0x00,0x00,0x00,0x00 };    //�����ַ=41FD67-��ǰ��ַ-5(����������ֽ�)
	char n_xue_XG_3[]{ 0x8B,0XD0,0X2B,0XD7,0X3B,0XD1 };//�ָ�
	char n_nei_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_nei_XG_2[]{ 0xC1,0xE1,0x06,
					   0x31,0xD2,
					   0x29,0xC1,
					   0xE9,
					   0x00,0x00,0x00,0x00 };
	char n_nei_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//�ָ�
	char n_ti_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_ti_XG_2[]{ 0xC1,0xE1,0x06,
					  0x31,0xD2,
					  0x29,0xC1,
					  0xE9,
					  0x00,0x00,0x00,0x00 };
	char n_ti_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//�ָ�
	HANDLE n_juBing = OpenProcess(PROCESS_ALL_ACCESS, false, jieGouTi->n_PDI);
	if (!n_juBing)
	{
		return FALSE;
	}
	else
	{
		LPVOID n_diZhi = VirtualAllocEx(n_juBing, NULL, 512, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (!n_diZhi)
		{
			CloseHandle(n_juBing);// �رս��̾��
			printf("�����ڴ�ʧ��");
			return FALSE;
		}
		else
		{
			printf("�����ڴ�: %p\n", n_diZhi);
			/*����ԭʼ����ִ�е�ַ*/
			int n_jmp_di_zhi = 0x41FD67 - ((int)n_diZhi + 0x10) - 5; //����jmp��ǰҪ��ת�������ַ(������E9)
			int* n_xr_di_zhi = (int*)(n_xue_XG_2 + 0x11);   //����ֵΪ0xE9��0x00��λ��,������n_data��ָ�����0x11λ��
			n_xr_di_zhi[0] = n_jmp_di_zhi;  //��Ҫjmp��ת�ĵ�ַ��ʼλ 0x00 ���� (8�ֽ� ������)
			/*����ԭʼ���� jmp ********/

			/*cmp �Ƚ� ***********/
			n_xr_di_zhi = (int*)(n_xue_XG_2 + 0x2);   //����ֵΪcmp 0xFEҪ�Ƚϵ�ֵ 0x00 ��λ��
			n_xr_di_zhi[0] = 0x4CE60C;  //��cmpҪ�Ƚϵĵ�ַ���� 0x00,0x00,0x00,0x00
			/*cmp �Ƚ� ***********/

			/*д���ڴ�*/
			BOOL n_pan_duan = WriteProcessMemory(n_juBing, n_diZhi, n_xue_XG_2, sizeof(n_xue_XG_2), NULL);
			if (!n_pan_duan)
			{
				//printf("��õĽ���Ϊ: % ld\n", n_jinCheng);
				CloseHandle(n_juBing);// �رս��̾��
				return FALSE;
			}
			/*����Ѫ�޵�*/
			n_jmp_di_zhi = (int)n_diZhi - 0x41FD61 - 0x5; //����jmp��ǰҪ��ת�ĵ�ַ(������)
			//std::cout << "tiaozhuan: " << std::hex << n_jmp_di_zhi << std::endl;
			n_xr_di_zhi = (int*)(n_xue_XG_1 + 0x1);   //����ֵΪ0xE9���Ҫ��ת�ڴ��ַ����ʼλ��0x00
			n_xr_di_zhi[0] = n_jmp_di_zhi;  //��Ҫjmp��ת�ĵ�ַ��ʼλ�ô��� 0x00

			/*���Ķ�ָ�����̵������ַ�ռ��е����ύҳ������ı���,�ı��ڴ��ַ��������*/
			DWORD n_laShi = 0;
			VirtualProtectEx(n_juBing, (LPVOID)0x4FD61, sizeof(n_xue_XG_1), PAGE_EXECUTE_READWRITE, &n_laShi);

			/*д��*/
			n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x41FD61, n_xue_XG_1, sizeof(n_xue_XG_1), NULL);
			if (!n_pan_duan)
			{
				CloseHandle(n_juBing);// �رս��̾��
				return FALSE;
			}
			CloseHandle(n_juBing);// �رս��̾��
			return TRUE;
		}
	}
	CloseHandle(n_juBing);// �رս��̾��
	return TRUE;
}

/*ֱ���޸�ִ�еĻ��������ı��������״̬*/
BOOL L_GongJu::xiu_gai_ji_qi_ma(int xiang_mu, J_ti_qu_xin_xi* jieGouTi)
{
	char n_xue_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00,0x90 };
	char n_xue_XG_2[]{ 0x81,0xFE, //cmp esi
					   0x00,0x00,0x00,0x00,      //4CE60C
					   0x75,0x02,                //jne 0247000A
					   0x31,0xFF,                //xor edi edi
					   0x8B,0xD0,                //mov edx eax
					   0x29,0xFA,                //sub edx ecx
					   0x39,0xCA,                //cmp edx ecx
					   0xE9,                     //jmp
					   0x00,0x00,0x00,0x00 };    //�����ַ=41FD67-��ǰ��ַ-5(����������ֽ�)
	char n_xue_XG_3[]{ 0x8B,0XD0,0X2B,0XD7,0X3B,0XD1 };//�ָ�
	char n_nei_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_nei_XG_2[]{ 0xC1,0xE1,0x06,
					   0x31,0xD2,
					   0x29,0xC1,
					   0xE9,
					   0x00,0x00,0x00,0x00 };
	char n_nei_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//�ָ�
	char n_ti_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_ti_XG_2[]{ 0xC1,0xE1,0x06,
					  0x31,0xD2,
					  0x29,0xC1,
					  0xE9,
					  0x00,0x00,0x00,0x00 };
	char n_ti_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//�ָ�


	switch (xiang_mu)
	{
	case 1:
		return zhi_xing(jieGouTi);
		break;
	case 2:
		break;
	default:
		break;
	}
}


/*��ȡ��Ϸ(ģ��)��ַ->�ṹ��ָ��*/
int L_GongJu::get_chen_xu_ji_zhi1(J_ti_qu_xin_xi* jieGouTi)
{
	HWND n_juBing = FindWindowA(jieGouTi->n_chuang_kou_lei, jieGouTi->n_chuang_kou_ming);//��ȡ��Ϸ���ھ��
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing == NULL)
	{
		return -2;
	}
	else
	{
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//��ȡ���� n_jinCheng ��PDI n_pdi 
		if (n_jinCheng == NULL)
		{
			return -3;
		}
	}

	PVOID n_jiZhi = NULL;
	n_jiZhi = get_ji_zhi_2(n_pdi);
	if (NULL == n_jiZhi)
	{
		return NULL;
	}
	else
	{
		jieGouTi->n_jiZhi = n_jiZhi;
		jieGouTi->n_PDI = n_pdi;
		jieGouTi->n_jinCheng = n_jinCheng;
		jieGouTi->n_jinCheng_jubBing = n_juBing;
		return -1;
	}
	return -1;
}
/*��ȡ��Ϸ(ģ��)��ַ->�ṹ��ָ��*/
BOOL L_GongJu::get_chen_xu_ji_zhi_bool(LPCSTR a, LPCSTR b, J_ti_qu_xin_xi* jieGouTi)
{
	HWND n_juBing = FindWindowA(a, b);//��ȡ��Ϸ���ھ��
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing)
	{
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//��ȡ���� n_jinCheng ��PDI n_pdi 
		if (!n_jinCheng)
		{
			AfxMessageBox(L"������pid��ȡʧ��");
			return false;
		}
	}

	PVOID n_jiZhi = NULL;
	n_jiZhi = get_ji_zhi_2(n_pdi);
	if (NULL == n_jiZhi)
	{
		AfxMessageBox(L"��Ϸ��ַ��ȡʧ��");
		return FALSE;
	}
	else
	{

		jieGouTi->n_jiZhi = n_jiZhi;
		jieGouTi->n_PDI = n_pdi;
		jieGouTi->n_jinCheng = n_jinCheng;
		jieGouTi->n_jinCheng_jubBing = n_juBing;
		return TRUE;
	}
	return TRUE;
}

/*��ȡPDI*/
DWORD L_GongJu::get_pdi(LPCSTR a, LPCSTR b)
{
	HWND n_juBing = FindWindowA("Sword2 Class", "Sword2 Window");//��ȡ��Ϸ���ھ��
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing)
	{
		//std::cout << "�����: " << n_juBing << "\n";
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//��ȡ���� n_jinCheng ��PDI n_pdi 
		if (n_jinCheng)
		{
			return n_pdi;

		}
		else
		{
			return (DWORD)-3;
		}
	}
	else
	{
		return (DWORD)-2;
	}
	return n_pdi;
}
