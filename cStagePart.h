#ifndef _CSTAGEPART_H
#define _CSTAGEPART_H

#include "MyInclude.h"

using namespace KG;


class cRat;
class cZone;
class cInterFace;


class cStagePart
{
public:
	KGSound*			m_pSound;
	KGSprite*			m_pSprite;
	KGAnimate*			m_pAnimate;
	KGFont*				m_pFont;


	KGDialog*			m_pZoneDialog;

	WCHAR				m_cStageName[255];
	WCHAR				m_cStageRoot[255];
	int					m_nStageNumber;

	//폰트
	float				m_fFontAlpha;

	//치즈
	bool				m_bChesseBool;

	
	//주인공
	cRat*				m_pRat;
	//인터페이스
	cInterFace**		m_ppInterFace;
	int					m_nInterFaceCount;


	//각 땅
	cZone***			m_pppZone;

	//vector<vector<cZone>>		vZone;

	int					m_nTileSizeX;
	int					m_nTileSizeY;
	int					m_nTileNumberX;
	int					m_nTileNumberY;

	//치즈
	float				m_fCheeseTime;

	typedef struct TAG_GETCAT
	{
		//고양이
		bool				m_bGetCat;
		float				m_fCatTime;
		float				m_fDonTime;
		bool				m_bCatAnimationCheck;
		bool				m_bKeyCheck;
		int					m_nX;
		int					m_nY;

		TAG_GETCAT()
		{
			m_bGetCat		= false;
			m_bCatAnimationCheck = false;
			m_bKeyCheck		= false;
			m_fCatTime		= 0.f;
			m_fDonTime		= 0.f;
			m_nX			= 0;
			m_nY			= -600;
		}
	}TAG_GETCATS;
	
	TAG_GETCATS			m_srtTagGetCat;


public:
	


public:
	cStagePart(KGSound* pSound, KGAnimate* pAnimate, KGDialog* pZoneDialog, int nStageNumber, WCHAR *cStageRoot, WCHAR *cStageName);
	~cStagePart();

public:
	void CALLBACK		OnLostDevice(void* pUserContext);
	void CALLBACK		OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

private:
	void				LoadObjectData(const WCHAR* pFileName);
	void				DecodeObject(FILE* fp);
	void				DecodeLayer(int nTileX, FILE* fp);
public:
	int					GetAttrib( int h_x, int h_y );
	void				OnRenderZonePart( int i, int j, int nKindZone );
	void				OnRenderClickZonePart( int i, int j, int nKindZone );
	void				RenderKindZone( WCHAR *cZoneName, int i, int j );
	void				ZoneCountSetting( int h_x, int h_y );
	bool				ZoneMoveStop( int h_x, int h_y );
	int					GetCurrentTile( int h_x, int h_y );
};

#endif