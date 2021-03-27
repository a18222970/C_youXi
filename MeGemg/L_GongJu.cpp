#include "pch.h"
#include "L_GongJu.h"


L_GongJu l_gong_ju1;


/*传入PDI,获得程序内存起始地址*/
PVOID L_GongJu::get_ji_zhi_1(DWORD pid)
{
	PVOID pProcessImageBase = NULL;
	MODULEENTRY32 me32 = { 0 };
	me32.dwSize = sizeof(MODULEENTRY32);

	// 获取指定进程全部模块的快照
	HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (INVALID_HANDLE_VALUE == hModuleSnap)
	{

		return pProcessImageBase;
	}

	// 获取快照中第一条信息
	BOOL bRet = Module32First(hModuleSnap, &me32);
	if (bRet)
	{
		// 获取加载基址
		pProcessImageBase = (PVOID)me32.modBaseAddr;
	}

	// 关闭句柄
	CloseHandle(hModuleSnap);
	return pProcessImageBase;
}

/*传入PDI,获得程序内存起始地址*/
PVOID L_GongJu::get_ji_zhi_2(DWORD pid)
{
	PVOID n_pProcessImageBase = NULL;
	HANDLE n_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);//打开进程, 获取进程句柄
	if (NULL == n_hProcess)
	{
		AfxMessageBox(L"获取句柄失败");
		return n_pProcessImageBase;
	}

	// 遍历进程模块,
	HMODULE hModule[100] = { 0 };
	DWORD dwRet = 0;
	BOOL bRet = EnumProcessModules(n_hProcess, (HMODULE*)(hModule), sizeof(hModule), &dwRet);
	if (FALSE == bRet)
	{
		CloseHandle(n_hProcess);
		AfxMessageBox(L"获取程序模块内存地址失败");
		return n_pProcessImageBase;
	}
	// 获取第一个模块加载基址
	n_pProcessImageBase = hModule[0];
	// 关闭句柄
	CloseHandle(n_hProcess);

	return n_pProcessImageBase;
}

/*获取游戏(模块)基址*/
PVOID L_GongJu::get_chen_xu_ji_zhi(LPCSTR a, LPCSTR b)
{
	HWND n_juBing = FindWindowA("Sword2 Class", "Sword2 Window");//获取游戏窗口句柄
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing)
	{
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//获取进程 n_jinCheng 与PDI n_pdi 
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

/* 打开进程, 获取模块进程句柄 参数:传入模块PID */
HANDLE L_GongJu::get_moKai_ju_bing(DWORD pid)
{
	HANDLE n_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);//打开进程, 获取进程句柄
	CloseHandle(n_hProcess);// 关闭句柄
	return n_hProcess;

}

/*获取进程*/
DWORD L_GongJu::get_jin_cheng(LPCSTR a, LPCSTR b)
{
	HWND n_juBing = FindWindowA("Sword2 Class", "Sword2 Window");//获取游戏窗口句柄
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing)
	{
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//获取进程 n_jinCheng 与PDI n_pdi 
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

/*获取句柄
参数a: 程序窗口类名
参数b: 程序窗口标题
*/
HWND L_GongJu::get_ju_bing(LPCSTR a, LPCSTR b)
{
	HWND n_juBing = FindWindowA("Sword2 Class", "Sword2 Window");//获取游戏窗口句柄
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

/*查询unsigned类型,单个地址数据
* 参数1:句柄
* 参数2:什么类型的(一次读取的内存长度)内存地址
*/
int L_GongJu::query_shu_ju(HANDLE ju_bing, unsigned nei_chun_di_zhi)
{
	int fan_hui_jg;
	SIZE_T du_qu_hp;
	/*ReadProcessMemory将指定地址范围内的数据从指定进程的地址空间复制到当前进程的指定缓冲区*/
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
	/*WriteProcessMemory 在指定的进程中将数据写入内存区域。必须写入整个区域，否则操作将失败。*/
	WriteProcessMemory(ju_bing, (LPVOID)nei_chun_di_zhi, &xr_shu_ju, sizeof(xr_shu_ju), NULL);
}

BOOL L_GongJu::zhi_xing_1(int xiangMu, J_ti_qu_xin_xi* jieGouTi)
{
	char n_xue_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00,0x90 };//0x90 为nop
	char n_xue_XG_2[]{ 0x81,0xFE, //cmp esi
					   0x00,0x00,0x00,0x00,      //4CE60C
					   0x75,0x02,                //jne 0247000A
					   0x31,0xFF,                //xor edi edi
					   0x8B,0xD0,                //mov edx eax
					   0x29,0xFA,                //sub edx ecx
					   0x39,0xCA,                //cmp edx ecx
					   0xE9,                     //jmp
					   0x00,0x00,0x00,0x00 };    //这个地址=41FD67-当前地址-5(这条命令的字节)
	char n_xue_XG_3[]{ 0x8B,0XD0,0X2B,0XD7,0X3B,0XD1 };//恢复
	char n_nei_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_nei_XG_2[]{ 0xC1,0xE1,0x06,
					   0x31,0xD2,
					   0x29,0xC1,
					   0xE9,
					   0x00,0x00,0x00,0x00 };
	char n_nei_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//恢复
	char n_ti_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_ti_XG_2[]{ 0xC1,0xE1,0x06,
					  0x31,0xD2,
					  0x29,0xC1,
					  0xE9,
					  0x00,0x00,0x00,0x00 };
	char n_ti_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//恢复

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
				CloseHandle(n_juBing);// 关闭进程句柄
				printf("分配内存失败");
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
					printf("分配内存: %p\n", n_diZhi);
					/*返回原始代码执行地址*/
					n_jmp_di_zhi = 0x41FD67 - ((int)n_diZhi + 0x10) - 5; //返回jmp当前要跳转的命令地址(机器码)
					n_xr_di_zhi = (int*)(n_xue_XG_2 + 0x11);   //返回值为0xE9后0x00的位置,把数组n_data的指针调到0x11位置
					n_xr_di_zhi[0] = n_jmp_di_zhi;  //将要jmp跳转的地址起始位 0x00 存入 (8字节 机器码)
					/*返回原始代码 jmp ********/

					/*cmp 比较 ***********/
					n_xr_di_zhi = (int*)(n_xue_XG_2 + 0x2);   //返回值为cmp 0xFE要比较的值 0x00 的位置
					n_xr_di_zhi[0] = 0x4CE60C;  //将cmp要比较的地址存入 0x00,0x00,0x00,0x00
					/*cmp 比较 ***********/

					/*写入内存*/
					n_pan_duan = WriteProcessMemory(n_juBing, n_diZhi, n_xue_XG_2, sizeof(n_xue_XG_2), NULL);
					if (!n_pan_duan)
					{
						CloseHandle(n_juBing);// 关闭进程句柄
						return FALSE;
					}
					set_n_wuDi_kaiGuan(TRUE);
					set_n_jianXia_zuoBi_kaiGuan(TRUE);
				}
				/*修改血量源代码 不减血无敌*/
				n_jmp_di_zhi = (int)n_diZhi - 0x41FD61 - 0x5; //返回jmp当前要跳转的地址(机器码)
				n_xr_di_zhi = (int*)(n_xue_XG_1 + 0x1);   //返回值为0xE9后的要跳转内存地址的起始位置0x00
				n_xr_di_zhi[0] = n_jmp_di_zhi;  //将要jmp跳转的地址起始位置存入 0x00

				/*更改对指定进程的虚拟地址空间中的已提交页面区域的保护,改变内存地址处的属性
				PAGE_EXECUTE_READWRITE 表示可读可写.VirtualProtectEx函数需要OpenProcess函数打开模块*/
				VirtualProtectEx(n_juBing, (LPVOID)0x4FD61, sizeof(n_xue_XG_1), PAGE_EXECUTE_READWRITE, &n_laShi);

				/*写入*/
				n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x41FD61, n_xue_XG_1, sizeof(n_xue_XG_1), NULL);
				if (!n_pan_duan)
				{
					CloseHandle(n_juBing);// 关闭进程句柄
					return FALSE;
				}
				break;
			case 2:
				if (get_n_wuDi_kaiGuan())
				{
					/*更改对指定进程的虚拟地址空间中的已提交页面区域的保护,改变内存地址处的属性*/
					VirtualProtectEx(n_juBing, (LPVOID)0x4FD61, sizeof(n_xue_XG_3), PAGE_EXECUTE_READWRITE, &n_laShi);

					/*写入*/
					n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x41FD61, n_xue_XG_3, sizeof(n_xue_XG_3), NULL);
					if (!n_pan_duan)
					{
						CloseHandle(n_juBing);// 关闭进程句柄
						return FALSE;
					}
					//set_n_wuDi_kaiGuan(FALSE);
				}
				break;
			case 3:
				n_neiLi_di_zhi = (int)jieGouTi->n_fenPei_diZhi + sizeof(n_xue_XG_2);
				if (!get_n_neiLi_kaiGuan())
				{
					printf("分配内存: %p\n", n_neiLi_di_zhi);
					/*  n_jmp_di_zhi = 0x4262B3 - (n_neiLi_di_zhi + 0x7) - 0x5;
					定位要跳转回原始代码的内存地址,(E9的地址-e9当前所在内存地址,
					减去E9+要跳回的内存地址,共5个字节).  */
					n_jmp_di_zhi = 0x4262B8 - (n_neiLi_di_zhi + 0x7) - 0x5;
					/*准备写入的跳转回原始代码处的内存地址的写入地址
					这里的作用也可以理解为:将指针变量n_xr_di_zhi的指针指向数组内第9个成员就是E9后面的0x00*/
					n_xr_di_zhi = (int*)(n_nei_XG_2 + 0x8);
					/*将n_jmp_di_zhi的内容,从数组第9个成员开始往后挨个成员赋值
					n_xr_di_zhi[0]现在就是前面的(int*)(n_nei_XG_2 + 0x8) */
					n_xr_di_zhi[0] = n_jmp_di_zhi;
					n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)n_neiLi_di_zhi, n_nei_XG_2, sizeof(n_nei_XG_2), NULL);
					if (!n_pan_duan)
					{
						CloseHandle(n_juBing);// 关闭进程句柄
						return FALSE;
					}
					set_n_neiLi_kaiGuan(true);
					set_n_jianXia_zuoBi_kaiGuan(TRUE);
				}
				/*n_jmp_di_zhi = (int)n_diZhi - 0x41FD61 - 0x5; //返回jmp当前要跳转的地址(机器码)
				n_xr_di_zhi = (int*)(n_xue_XG_1 + 0x1);   //返回值为0xE9后的要跳转内存地址的起始位置0x00
				n_xr_di_zhi[0] = n_jmp_di_zhi;  //将要jmp跳转的地址起始位置存入 0x00*/

				/*修改内力原始代码*/
				n_jmp_di_zhi = n_neiLi_di_zhi - 0x4262B3 - 0x5;
				n_xr_di_zhi = (int*)(n_nei_XG_1 + 0x1);
				n_xr_di_zhi[0] = n_jmp_di_zhi;
				/*更改对指定进程的虚拟地址空间中的已提交页面区域的保护,改变内存地址处的属性
				PAGE_EXECUTE_READWRITE 表示可读可写.VirtualProtectEx函数需要OpenProcess函数打开模块*/
				VirtualProtectEx(n_juBing, (LPVOID)0x4262B3, sizeof(n_nei_XG_1), PAGE_EXECUTE_READWRITE, &n_laShi);
				n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x4262B3, n_nei_XG_1, sizeof(n_nei_XG_1), NULL);
				if (!n_pan_duan)
				{
					CloseHandle(n_juBing);// 关闭进程句柄
					return FALSE;
				}
				break;
			case 4:
				/*恢复原始代码*/
				/*更改对指定进程的虚拟地址空间中的已提交页面区域的保护,改变内存地址处的属性
				PAGE_EXECUTE_READWRITE 表示可读可写.VirtualProtectEx函数需要OpenProcess函数打开模块*/
				VirtualProtectEx(n_juBing, (LPVOID)0x4262B3, sizeof(n_nei_XG_3), PAGE_EXECUTE_READWRITE, &n_laShi);
				n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x4262B3, n_nei_XG_3, sizeof(n_nei_XG_3), NULL);
				if (!n_pan_duan)
				{
					CloseHandle(n_juBing);// 关闭进程句柄
					return FALSE;
				}
				break;
			case 5:
				n_tiLi_di_zhi = (int)get_Q_fenPei_diZhi() + sizeof(n_xue_XG_2) + sizeof(n_nei_XG_2);
				if (!get_n_tiLi_kaiGuan())
				{
					/*  n_jmp_di_zhi = 0x4262B3 - (n_neiLi_di_zhi + 0x7) - 0x5;
					定位要跳转回原始代码的内存地址,(E9的地址-e9当前所在内存地址,
					减去E9+要跳回的内存地址,共5个字节).  */
					n_jmp_di_zhi = 0x426238 - (n_tiLi_di_zhi + 0x7) - 0x5;
					/*准备写入的跳转回原始代码处的内存地址的写入地址
					这里的作用也可以理解为:将指针变量n_xr_di_zhi的指针指向数组内第9个成员就是E9后面的0x00*/
					n_xr_di_zhi = (int*)(n_ti_XG_2 + 0x8);
					/*将n_jmp_di_zhi的内容,从数组第9个成员开始往后挨个成员赋值
					n_xr_di_zhi[0]现在就是前面的(int*)(n_nei_XG_2 + 0x8) */
					n_xr_di_zhi[0] = n_jmp_di_zhi;
					n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)n_tiLi_di_zhi, n_ti_XG_2, sizeof(n_ti_XG_2), NULL);
					if (!n_pan_duan)
					{
						CloseHandle(n_juBing);// 关闭进程句柄
						return FALSE;
					}
					set_n_tiLi_kaiGuan(true);
					set_n_jianXia_zuoBi_kaiGuan(TRUE);
				}
				/*修改体力原始代码*/
				n_jmp_di_zhi = n_tiLi_di_zhi - 0x426233 - 0x5;
				n_xr_di_zhi = (int*)(n_ti_XG_1 + 0x1);
				n_xr_di_zhi[0] = n_jmp_di_zhi;
				/*更改对指定进程的虚拟地址空间中的已提交页面区域的保护,改变内存地址处的属性
				PAGE_EXECUTE_READWRITE 表示可读可写.VirtualProtectEx函数需要OpenProcess函数打开模块*/
				VirtualProtectEx(n_juBing, (LPVOID)0x426233, sizeof(n_ti_XG_1), PAGE_EXECUTE_READWRITE, &n_laShi);
				n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x426233, n_ti_XG_1, sizeof(n_ti_XG_1), NULL);
				if (!n_pan_duan)
				{
					CloseHandle(n_juBing);// 关闭进程句柄
					return FALSE;
				}
				break;
			case 6:
				/*恢复原始代码*/
				/*更改对指定进程的虚拟地址空间中的已提交页面区域的保护,改变内存地址处的属性
				PAGE_EXECUTE_READWRITE 表示可读可写.VirtualProtectEx函数需要OpenProcess函数打开模块*/
				VirtualProtectEx(n_juBing, (LPVOID)0x426233, sizeof(n_ti_XG_3), PAGE_EXECUTE_READWRITE, &n_laShi);
				n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x426233, n_ti_XG_3, sizeof(n_ti_XG_3), NULL);
				if (!n_pan_duan)
				{
					CloseHandle(n_juBing);// 关闭进程句柄
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
					   0x00,0x00,0x00,0x00 };    //这个地址=41FD67-当前地址-5(这条命令的字节)
	char n_xue_XG_3[]{ 0x8B,0XD0,0X2B,0XD7,0X3B,0XD1 };//恢复
	char n_nei_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_nei_XG_2[]{ 0xC1,0xE1,0x06,
					   0x31,0xD2,
					   0x29,0xC1,
					   0xE9,
					   0x00,0x00,0x00,0x00 };
	char n_nei_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//恢复
	char n_ti_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_ti_XG_2[]{ 0xC1,0xE1,0x06,
					  0x31,0xD2,
					  0x29,0xC1,
					  0xE9,
					  0x00,0x00,0x00,0x00 };
	char n_ti_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//恢复
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
			CloseHandle(n_juBing);// 关闭进程句柄
			printf("分配内存失败");
			return FALSE;
		}
		else
		{
			printf("分配内存: %p\n", n_diZhi);
			/*返回原始代码执行地址*/
			int n_jmp_di_zhi = 0x41FD67 - ((int)n_diZhi + 0x10) - 5; //返回jmp当前要跳转的命令地址(机器码E9)
			int* n_xr_di_zhi = (int*)(n_xue_XG_2 + 0x11);   //返回值为0xE9后0x00的位置,把数组n_data的指针调到0x11位置
			n_xr_di_zhi[0] = n_jmp_di_zhi;  //将要jmp跳转的地址起始位 0x00 存入 (8字节 机器码)
			/*返回原始代码 jmp ********/

			/*cmp 比较 ***********/
			n_xr_di_zhi = (int*)(n_xue_XG_2 + 0x2);   //返回值为cmp 0xFE要比较的值 0x00 的位置
			n_xr_di_zhi[0] = 0x4CE60C;  //将cmp要比较的地址存入 0x00,0x00,0x00,0x00
			/*cmp 比较 ***********/

			/*写入内存*/
			BOOL n_pan_duan = WriteProcessMemory(n_juBing, n_diZhi, n_xue_XG_2, sizeof(n_xue_XG_2), NULL);
			if (!n_pan_duan)
			{
				//printf("获得的进程为: % ld\n", n_jinCheng);
				CloseHandle(n_juBing);// 关闭进程句柄
				return FALSE;
			}
			/*不减血无敌*/
			n_jmp_di_zhi = (int)n_diZhi - 0x41FD61 - 0x5; //返回jmp当前要跳转的地址(机器码)
			//std::cout << "tiaozhuan: " << std::hex << n_jmp_di_zhi << std::endl;
			n_xr_di_zhi = (int*)(n_xue_XG_1 + 0x1);   //返回值为0xE9后的要跳转内存地址的起始位置0x00
			n_xr_di_zhi[0] = n_jmp_di_zhi;  //将要jmp跳转的地址起始位置存入 0x00

			/*更改对指定进程的虚拟地址空间中的已提交页面区域的保护,改变内存地址处的属性*/
			DWORD n_laShi = 0;
			VirtualProtectEx(n_juBing, (LPVOID)0x4FD61, sizeof(n_xue_XG_1), PAGE_EXECUTE_READWRITE, &n_laShi);

			/*写入*/
			n_pan_duan = WriteProcessMemory(n_juBing, (LPVOID)0x41FD61, n_xue_XG_1, sizeof(n_xue_XG_1), NULL);
			if (!n_pan_duan)
			{
				CloseHandle(n_juBing);// 关闭进程句柄
				return FALSE;
			}
			CloseHandle(n_juBing);// 关闭进程句柄
			return TRUE;
		}
	}
	CloseHandle(n_juBing);// 关闭进程句柄
	return TRUE;
}

/*直接修改执行的机器码来改变程序运行状态*/
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
					   0x00,0x00,0x00,0x00 };    //这个地址=41FD67-当前地址-5(这条命令的字节)
	char n_xue_XG_3[]{ 0x8B,0XD0,0X2B,0XD7,0X3B,0XD1 };//恢复
	char n_nei_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_nei_XG_2[]{ 0xC1,0xE1,0x06,
					   0x31,0xD2,
					   0x29,0xC1,
					   0xE9,
					   0x00,0x00,0x00,0x00 };
	char n_nei_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//恢复
	char n_ti_XG_1[]{ 0xE9,0x00,0x00,0x00,0x00 };
	char n_ti_XG_2[]{ 0xC1,0xE1,0x06,
					  0x31,0xD2,
					  0x29,0xC1,
					  0xE9,
					  0x00,0x00,0x00,0x00 };
	char n_ti_XG_3[]{ 0xC1,0xE1,0x06,0x2B,0xC8 };//恢复


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


/*获取游戏(模块)基址->结构体指针*/
int L_GongJu::get_chen_xu_ji_zhi1(J_ti_qu_xin_xi* jieGouTi)
{
	HWND n_juBing = FindWindowA(jieGouTi->n_chuang_kou_lei, jieGouTi->n_chuang_kou_ming);//获取游戏窗口句柄
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing == NULL)
	{
		return -2;
	}
	else
	{
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//获取进程 n_jinCheng 与PDI n_pdi 
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
/*获取游戏(模块)基址->结构体指针*/
BOOL L_GongJu::get_chen_xu_ji_zhi_bool(LPCSTR a, LPCSTR b, J_ti_qu_xin_xi* jieGouTi)
{
	HWND n_juBing = FindWindowA(a, b);//获取游戏窗口句柄
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing)
	{
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//获取进程 n_jinCheng 与PDI n_pdi 
		if (!n_jinCheng)
		{
			AfxMessageBox(L"进程与pid获取失败");
			return false;
		}
	}

	PVOID n_jiZhi = NULL;
	n_jiZhi = get_ji_zhi_2(n_pdi);
	if (NULL == n_jiZhi)
	{
		AfxMessageBox(L"游戏基址获取失败");
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

/*获取PDI*/
DWORD L_GongJu::get_pdi(LPCSTR a, LPCSTR b)
{
	HWND n_juBing = FindWindowA("Sword2 Class", "Sword2 Window");//获取游戏窗口句柄
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing)
	{
		//std::cout << "句柄是: " << n_juBing << "\n";
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//获取进程 n_jinCheng 与PDI n_pdi 
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
