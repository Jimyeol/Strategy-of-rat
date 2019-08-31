#ifndef _CMAPMNG_H
#define _CMAPMNG_H

#include "MyInclude.h"

using namespace KG;

class cStagePart;

class cMapMng : public KGScene , public KGResponseDialog
{
public:
	KGSound*			m_pSound;
	KGSprite*			m_pSprite;
	KGAnimate*			m_pAnimate;
	KGFont*				m_pFont;
	KGDialog*			m_pZoneDialog;
	KGDialog*			m_pDialog;
	KGDialog*			m_pInterFace;
	KGDialog*			m_pPause;
	KGDialog**			m_ppZoneDialog;
	KGCursor*			m_pCursor;



public:
	cStagePart**		m_ppStagePart;
	int					m_nMapListCount;


public:
	bool				m_bSelectStage;
	bool				m_bPause;

	D3DXVECTOR3			m_vBackMove1;
	D3DXVECTOR3			m_vBackMove2;

public:
	class CLEARXY_TAG
	{
		int m_x;
		int m_y;

		CLEARXY_TAG( int iX, int iY )
		{
			m_x = iX;
			m_y = iY;
		}
		~CLEARXY_TAG()
		{
		}
	};

	int*				m_pClearList;	//스테이지 클리어 집어넣는거.
	KGDialog*			m_pClearDlg;
	CLEARXY_TAG**		m_tppClearXY;

private:
	int					m_nStageTileX;
	int					m_nStageTileY;
	int					m_nTileInterVal2;
	int					m_nTileInterVal;


public:
	cMapMng();
	~cMapMng();

public:
	HRESULT CALLBACK	OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	HRESULT CALLBACK	OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnDestroyDevice(void* pUserContext);
	void CALLBACK		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void CALLBACK		OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
						   bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
	LRESULT CALLBACK	OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
	void CALLBACK		OnEvent(UINT id, int xPos, int yPos);
	void				OnSwitchSelectStage(UINT id, int nMapListCount);

private:
	void				LoadStageData(const WCHAR* pFileName);
	void				DecodeStage(FILE* fp);
	void				LoadStageSaveData(const WCHAR* pFileName);
	void				DecodeStageSave(FILE* fp);
	

private:
	bool				HeroPositionReset();

public:
	//클리어관리
	void				OnClearUpdate();
	void				StageSAve(const WCHAR* pFileName);

};

#endif