#include "pch.h"
#include "L_zhiXing.h"

L_GongJu l_gong_ju; 
//L_GongJu::J_ti_qu_xin_xi j_get_xiXin;

/*��ȡ�����Ҫ����Ϣ*/
BOOL L_zhiXing::get_xin_xi(LPCSTR a, LPCSTR b, L_GongJu::J_ti_qu_xin_xi* jieGouTi)
{
	// return l_gong_ju.get_chen_xu_ji_zhi_bool(a, b, jieGouTi);
	HWND n_juBing = FindWindowA(a, b);//��ȡ��Ϸ���ھ��
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing)
	{
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//��ȡ���� n_jinCheng ��PDI n_pdi 
		if (n_jinCheng)
		{
			PVOID n_jiZhi = NULL;
			HANDLE n_jinCheng_jubBing = NULL;
			n_jiZhi = l_gong_ju.get_ji_zhi_2(n_pdi);
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
					return TRUE;
			}

			return TRUE;
		}
		else
		{
			AfxMessageBox(L"������pid��ȡʧ��");
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL L_zhiXing::get_xin_xi_00(LPCSTR a, LPCSTR b, L_GongJu::J_ti_qu_xin_xi* jieGouTi)
{
	HWND n_juBing = FindWindowA(a,b);//��ȡ��Ϸ���ھ��
	DWORD n_pdi;
	DWORD n_jinCheng;
	if (n_juBing == NULL)
	{
		return FALSE;
	}
	else
	{
		
		n_jinCheng = GetWindowThreadProcessId(n_juBing, &n_pdi);//��ȡ���� n_jinCheng ��PDI n_pdi 
		if (n_jinCheng == NULL)
		{
			return FALSE;
		}
		printf("��õĽ���Ϊ: % ld\n", n_jinCheng);
	}

	PVOID n_jiZhi = NULL;
	n_jiZhi = l_gong_ju.get_ji_zhi_2(n_pdi);
	if (NULL == n_jiZhi)
	{
		return FALSE;
	}
	else
	{
		printf("��õ�pidΪ: % ld\n", n_pdi);
		printf("��õ�jizhiΪ: %p\n", n_jiZhi);
		jieGouTi->n_jiZhi = n_jiZhi;
		jieGouTi->n_PDI = n_pdi;
		jieGouTi->n_jinCheng = n_jinCheng;
		jieGouTi->n_jinCheng_jubBing = n_juBing;
		printf("��õ�jizhiΪ: %p\n", jieGouTi->n_jiZhi);
		return TRUE;
	}
	return TRUE;
}
