#pragma once
#include "L_GongJu.h"
#include <Windows.h>
class L_zhiXing
{
private:
	BOOL n_hp;
	BOOL n_mp;
	BOOL n_ti;
	
protected:

public:

	/*���캯��*/
	L_zhiXing() {};
	/*���캯������,����Ա��ʼ���б�*/
	L_zhiXing(BOOL _n_hp, bool _n_mp, bool _n_ti) :n_hp{FALSE},n_mp{FALSE},n_ti{FALSE}
	{
	}

	BOOL get_hp()
	{
		return n_hp;
	}
	BOOL get_mp()
	{
		return n_mp;
	}
	BOOL get_tp()
	{
		return n_ti;
	}

	void set_hp(bool h)
	{
		n_hp = !n_hp;
	}
	void set_mp(bool m)
	{
		n_mp = !n_mp;
	}
	void set_ti(bool t)
	{
		n_ti = !n_ti;
	}

	
	//L_GongJu::J_ti_qu_xin_xi j_get_xiXin;

	/*��ȡ�����Ҫ����Ϣ*/
	BOOL get_xin_xi(LPCSTR a, LPCSTR b, L_GongJu::J_ti_qu_xin_xi* jieGouTi);

	BOOL get_xin_xi_00(LPCSTR a, LPCSTR b, L_GongJu::J_ti_qu_xin_xi* jieGouTi);




};


//���ȷ�� �����޸�׼��
//�����Ӧ��ѡ�� ʵ�ֶ�Ӧ����

