#ifndef _KRCONTROL_H
#define _KRCONTROL_H

#include"KrWindow.h"
#include "KrUIManager.h"
#include "KrWindow.h"
#include<windowsx.h>
#include <map>
using namespace std;

namespace KrUI{


	class KrWindow;
	typedef LRESULT(*MSGFUNC)(void* pObject, WPARAM wParam, LPARAM lParam);

	class KrControl
	{
	private:
		UINT      m_type;
		KrWindow* m_pKrWindow;
		LPCWSTR m_lpCtrlName;
		RECT m_rect;
		bool m_bVisible;
		bool m_bMouseIn;
		map<UINT, MSGFUNC> m_MsgFuncMap;
	public:
		KrControl();
		void    KrSetCtrlType(UINT type);
		UINT    KrGetCtrlType();
		void    KrSetWindow(KrWindow* pKrWindow);//
		KrWindow* KrGetWindow();
		void	KrSetName(LPCWSTR lpCtrlName);//
		LPCWSTR KrGetName();//
		RECT*   KrGetRect();//
		void    KrSetRect(RECT* pRect); //
		int     KrGetX();//
		int     KrGetY();//
		int     KrGetWidth();//
		int     KrGetHeight();//
		void    KrSetX(int x);//
		void    KrSetY(int y);//
		void    KrSetWidth(int width);//
		void    KrSetHeight(int height);//
		void    KrRegMsg(UINT msg, MSGFUNC func);
		void  virtual  KrDraw();
		bool  KrIsVisible();
		void  KrShow();
		void  KrHide();
		void  KrHandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		void  KrCallMsgFunc(UINT Message, WPARAM wParam, LPARAM lParam);


	};


}//namespace KrUI
#endif
