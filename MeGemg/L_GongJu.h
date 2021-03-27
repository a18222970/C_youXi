#pragma once
//#include <iostream>//标准库
#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")

//typedef  int  NEICUN;
//#define 1 NEICUN_FENPEI

/*
局部变量 n_bianLiang 小写n开头

全局性变量 Q_BianLiang 大写Q开头

函数 bian_liang 中间用_间隔

类 L_BIAN_LIANG 大写L开头,后面全部大写并用_间隔

类实例化 l_bian_laing 小写l开头

结构体 J_bian_liang 大写J开头

结构体实例化 j_bianLiang 小写j开头
*/

class L_GongJu
{
private:
	BOOL	n_jianXia_zuoBi_kaiGuan;//剑侠作弊开关
	BOOL	n_wuDi_kaiGuan;		 //无敌功能开关
	BOOL	n_neiLi_kaiGuan;		 //内力无限开关
	BOOL	n_tiLi_kaiGuan;		 //体力无限开关
	LPVOID  Q_fenPei_diZhi;

protected:

public:

	/*游戏信息*/
	struct J_ti_qu_xin_xi
	{
		LPCSTR n_chuang_kou_lei;
		LPCSTR n_chuang_kou_ming;
		PVOID n_jiZhi;
		DWORD n_PDI;
		DWORD n_jinCheng;
		HANDLE n_jinCheng_jubBing;
		LPVOID n_fenPei_diZhi;
	};

	/*修改相关机器码*/
	struct J_ji_qi_ma
	{
		char n_xue1[5];  
		char n_xue2[20];
		char n_xue3[5];
		char n_nei1[4];
		char n_nei2[11];
		char n_nei3[4];
		char n_ti1[4];
		char n_ti2[11];
		char n_ti3[4];
	};


	J_ti_qu_xin_xi J_ren_wu;

	/*构造函数,并初始化成员变量*/
	L_GongJu() 
	{
		n_wuDi_kaiGuan		    = FALSE;
		n_neiLi_kaiGuan		    = FALSE;
		n_tiLi_kaiGuan          = FALSE;
		n_jianXia_zuoBi_kaiGuan = FALSE;
		Q_fenPei_diZhi			= NULL;

		
	};
	/*析构函数*/
	~L_GongJu() {};

	BOOL get_n_wuDi_kaiGuan()
	{
		return n_wuDi_kaiGuan;
	}
	void set_n_wuDi_kaiGuan(BOOL _n_wuDi_kaiGuan)
	{
		n_wuDi_kaiGuan = _n_wuDi_kaiGuan;
	}

	BOOL get_n_jianXia_zuoBi_kaiGuan()
	{
		return n_jianXia_zuoBi_kaiGuan;
	}
	void set_n_jianXia_zuoBi_kaiGuan(BOOL _n_jianXia_zuoBi_kaiGuan)
	{
		n_jianXia_zuoBi_kaiGuan = _n_jianXia_zuoBi_kaiGuan;
	}

	BOOL get_n_neiLi_kaiGuan()
	{
		return n_neiLi_kaiGuan;
	}
	void set_n_neiLi_kaiGuan(bool _n_neiLi_kaiGuan)
	{
		n_neiLi_kaiGuan = _n_neiLi_kaiGuan;
	}

	BOOL get_n_tiLi_kaiGuan()
	{
		return n_tiLi_kaiGuan;
	}
	void set_n_tiLi_kaiGuan(bool _n_tiLi_kaiGuan)
	{
		n_tiLi_kaiGuan = _n_tiLi_kaiGuan;
	}

	LPVOID get_Q_fenPei_diZhi()
	{
		return Q_fenPei_diZhi;
	}
	void set_Q_fenPei_diZhi(LPVOID _Q_fenPei_diZhi)
	{
		Q_fenPei_diZhi = _Q_fenPei_diZhi;
	}




	/*传入PDI,获得程序内存起始地址*/
	PVOID get_ji_zhi_1(DWORD pid);

	/*传入PDI,获得程序内存起始地址*/
	PVOID get_ji_zhi_2(DWORD pid);

	/*获取游戏(模块)基址 
	参数a: 程序窗口类名
	参数b: 程序窗口标题
	*/
	PVOID get_chen_xu_ji_zhi(LPCSTR a, LPCSTR b);

	/* 打开进程, 获取模块进程句柄 参数:传入模块PID */
	HANDLE get_moKai_ju_bing(DWORD pid);

	/*获取游戏(模块)基址->结构体指针*/
	int get_chen_xu_ji_zhi1(J_ti_qu_xin_xi* jieGouTi);

	/*获取游戏(模块)基址->结构体指针*/
	BOOL get_chen_xu_ji_zhi_bool(LPCSTR a, LPCSTR b, J_ti_qu_xin_xi* jieGouTi);

	/*获取PDI*/
	DWORD get_pdi(LPCSTR a, LPCSTR b);

	/*获取进程
	参数a: 程序窗口类名
	参数b: 程序窗口标题
	*/
	DWORD get_jin_cheng(LPCSTR a, LPCSTR b);

	/*获取句柄
	参数a: 程序窗口类名
	参数b: 程序窗口标题
	*/
	HWND get_ju_bing(LPCSTR a, LPCSTR b);

	/*查询unsigned类型,单个地址数据
    * 参数1:句柄
    * 参数2:什么类型的(一次读取的内存长度)内存地址
    */
	int query_shu_ju(HANDLE ju_bing, unsigned nei_chun_di_zhi);

	/*查询unsigned类型,J_ren_wu结构体长度的地址数据
	* 参数1:句柄
	* 参数2:读取地址
	* 参数3:定义的J_ti_qu_xin_xi结构体;
	*/
	BOOL query_shu_ju_kuai(HANDLE ju_bing, unsigned nei_chun_di_zhi, J_ti_qu_xin_xi* ren_wu_shu_xin);

	/*写入unsigned类型,xr_shu_ju 长度的数据
	* 参数1:句柄
	* 参数2:妖写入的起始地址
	* 参数3:妖写入的数据
	*/
	void xie_shu_ju(HANDLE ju_bing, unsigned nei_chun_di_zhi, int xr_shu_ju);

	/*直接修改执行的机器码来改变程序运行状态
	* 参数1:要修改的项目,即准备修改什么.
	* 参数2:获得的程序信息结构体,包括句柄,pid,进程,以及程序内存基址
	*/
	BOOL xiu_gai_ji_qi_ma(int xiang_mu, J_ti_qu_xin_xi* jieGouTi);


	BOOL L_GongJu::zhi_xing_1(int xiangMu,J_ti_qu_xin_xi* jieGouTi);
	BOOL zhi_xing(J_ti_qu_xin_xi* jieGouTi);
};

