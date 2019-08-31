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

	//��Ʈ
	float				m_fFontAlpha;

	//ġ��
	bool				m_bChesseBool;

	
	//���ΰ�
	cRat*				m_pRat;
	//�������̽�
	cInterFace**		m_ppInterFace;
	int					m_nInterFaceCount;


	//�� ��
	cZone***			m_pppZone;

	//vector<vector<cZone>>		vZone;

	int					m_nTileSizeX;
	int					m_nTileSizeY;
	int					m_nTileNumberX;
	int					m_nTileNumberY;

	//ġ��
	float				m_fCheeseTime;

	typedef struct TAG_GETCAT
	{
		//�����
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