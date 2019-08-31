#ifndef _CMENU_H
#define _CMENU_H

#include "MyInclude.h"

using namespace KG;

#pragma warning(disable:4996)

#define GaRo 700
#define SeRo 100

#define BACKMUSIC 22
#define CLICKMUSIC 23

enum{
	Mouse_StandMotion	= 0 , 
	Mouse_BackMotion		,
	Mouse_FrontMotion		,
	Mouse_LeftMotion		,
	Mouse_RightMotion		,
	Mouse_MaxMotion			,
};
enum{
	WDGD_LeftMotion = 0,
	WDGD_RightMotion,
	WDGD_MaxMotion,
};

class cMenu : public KGScene, KGResponseDialog
{
private:
	KGSound*				m_pBgm;				//¹è°æÀ½¾Ç
	KGSound*				m_pSound;			//È¿°úÀ½¾Ç
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGRenderSingle*			m_pSingle[Mouse_MaxMotion];
	KGRenderSingle*			m_pWhatDaGodDa[WDGD_MaxMotion];

	int						m_nWhat;
	int						m_nOption;
	int						m_nMouseState;
	int						m_nWhatDaGodDa;

	float					m_fDCircle;
	float					m_nMouseMoveX;
	float					m_nMouseMoveY;
	float					m_fChogihwa;
	float					m_fAlpa;
	float					m_fAlpa2;
	float					m_fBlackX;

	bool					m_bSound,m_bBgm,m_bDone;

	//int						m_nButton[3][3];

	D3DXVECTOR3				m_vMouse;
	D3DXVECTOR3				m_vWhatDaGodDa;
	D3DXVECTOR3				m_vButton[9];

	//WCHAR					m_sName[9][255];

	KGRenderSingle*			m_pCatHero[2];
	int						m_nCatState;

	bool					m_bTjfaudtjCheck;

public:
	cMenu();
	~cMenu();


public:
	HRESULT CALLBACK		OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);

	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnDestroyDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

	LRESULT CALLBACK		OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);

	void					Buttons(D3DXCOLOR color);
	void					Where();
	void					ButtonMove();
	void					hakin(int i);
	void					SubButtons(int i);
	void					Return();
	bool					Macgi(int i);
};

#endif