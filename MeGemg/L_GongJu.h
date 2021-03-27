#pragma once
//#include <iostream>//��׼��
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
�ֲ����� n_bianLiang Сдn��ͷ

ȫ���Ա��� Q_BianLiang ��дQ��ͷ

���� bian_liang �м���_���

�� L_BIAN_LIANG ��дL��ͷ,����ȫ����д����_���

��ʵ���� l_bian_laing Сдl��ͷ

�ṹ�� J_bian_liang ��дJ��ͷ

�ṹ��ʵ���� j_bianLiang Сдj��ͷ
*/

class L_GongJu
{
private:
	BOOL	n_jianXia_zuoBi_kaiGuan;//�������׿���
	BOOL	n_wuDi_kaiGuan;		 //�޵й��ܿ���
	BOOL	n_neiLi_kaiGuan;		 //�������޿���
	BOOL	n_tiLi_kaiGuan;		 //�������޿���
	LPVOID  Q_fenPei_diZhi;

protected:

public:

	/*��Ϸ��Ϣ*/
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

	/*�޸���ػ�����*/
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

	/*���캯��,����ʼ����Ա����*/
	L_GongJu() 
	{
		n_wuDi_kaiGuan		    = FALSE;
		n_neiLi_kaiGuan		    = FALSE;
		n_tiLi_kaiGuan          = FALSE;
		n_jianXia_zuoBi_kaiGuan = FALSE;
		Q_fenPei_diZhi			= NULL;

		
	};
	/*��������*/
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




	/*����PDI,��ó����ڴ���ʼ��ַ*/
	PVOID get_ji_zhi_1(DWORD pid);

	/*����PDI,��ó����ڴ���ʼ��ַ*/
	PVOID get_ji_zhi_2(DWORD pid);

	/*��ȡ��Ϸ(ģ��)��ַ 
	����a: ���򴰿�����
	����b: ���򴰿ڱ���
	*/
	PVOID get_chen_xu_ji_zhi(LPCSTR a, LPCSTR b);

	/* �򿪽���, ��ȡģ����̾�� ����:����ģ��PID */
	HANDLE get_moKai_ju_bing(DWORD pid);

	/*��ȡ��Ϸ(ģ��)��ַ->�ṹ��ָ��*/
	int get_chen_xu_ji_zhi1(J_ti_qu_xin_xi* jieGouTi);

	/*��ȡ��Ϸ(ģ��)��ַ->�ṹ��ָ��*/
	BOOL get_chen_xu_ji_zhi_bool(LPCSTR a, LPCSTR b, J_ti_qu_xin_xi* jieGouTi);

	/*��ȡPDI*/
	DWORD get_pdi(LPCSTR a, LPCSTR b);

	/*��ȡ����
	����a: ���򴰿�����
	����b: ���򴰿ڱ���
	*/
	DWORD get_jin_cheng(LPCSTR a, LPCSTR b);

	/*��ȡ���
	����a: ���򴰿�����
	����b: ���򴰿ڱ���
	*/
	HWND get_ju_bing(LPCSTR a, LPCSTR b);

	/*��ѯunsigned����,������ַ����
    * ����1:���
    * ����2:ʲô���͵�(һ�ζ�ȡ���ڴ泤��)�ڴ��ַ
    */
	int query_shu_ju(HANDLE ju_bing, unsigned nei_chun_di_zhi);

	/*��ѯunsigned����,J_ren_wu�ṹ�峤�ȵĵ�ַ����
	* ����1:���
	* ����2:��ȡ��ַ
	* ����3:�����J_ti_qu_xin_xi�ṹ��;
	*/
	BOOL query_shu_ju_kuai(HANDLE ju_bing, unsigned nei_chun_di_zhi, J_ti_qu_xin_xi* ren_wu_shu_xin);

	/*д��unsigned����,xr_shu_ju ���ȵ�����
	* ����1:���
	* ����2:��д�����ʼ��ַ
	* ����3:��д�������
	*/
	void xie_shu_ju(HANDLE ju_bing, unsigned nei_chun_di_zhi, int xr_shu_ju);

	/*ֱ���޸�ִ�еĻ��������ı��������״̬
	* ����1:Ҫ�޸ĵ���Ŀ,��׼���޸�ʲô.
	* ����2:��õĳ�����Ϣ�ṹ��,�������,pid,����,�Լ������ڴ��ַ
	*/
	BOOL xiu_gai_ji_qi_ma(int xiang_mu, J_ti_qu_xin_xi* jieGouTi);


	BOOL L_GongJu::zhi_xing_1(int xiangMu,J_ti_qu_xin_xi* jieGouTi);
	BOOL zhi_xing(J_ti_qu_xin_xi* jieGouTi);
};

