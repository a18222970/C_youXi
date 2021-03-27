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

	/*构造函数*/
	L_zhiXing() {};
	/*构造函数重载,带成员初始化列表*/
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

	/*获取程序必要的信息*/
	BOOL get_xin_xi(LPCSTR a, LPCSTR b, L_GongJu::J_ti_qu_xin_xi* jieGouTi);

	BOOL get_xin_xi_00(LPCSTR a, LPCSTR b, L_GongJu::J_ti_qu_xin_xi* jieGouTi);




};


//点击确定 做好修改准备
//点击相应单选框 实现对应功能

