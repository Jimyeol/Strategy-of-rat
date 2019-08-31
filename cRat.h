#ifndef _cRat_H
#define _cRat_H

#include "MyInclude.h"
#include <KGEmotion.h>

using namespace KG;

class cRat
{

private:
	KGSound*				m_pSound;
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGRenderSingle*			m_pSingleHero[HEROMOVE_MAX];
	KGRenderSingle*			m_pHeroParticle;
	

public:
	int						m_nCurrentAct;
	int						m_nHeroPosX;
	int						m_nHeroPosY;
	int						m_nHeroLieX;
	int						m_nHeroLieY;

	int						m_nHeroTileX;
	int						m_nHeroTileY;

	int						m_nTileSizeX;
	int						m_nTileSizeY;
	
	int						m_nMapTileX;
	int						m_nMapTileY;

	float					m_nKeyTiming;

	int						m_nTileAttribe;

	int						m_nHeroOrgX;
	int						m_nHeroOrgY;


public:
	cRat(KGSound* pSound, KGAnimate* pAnimate, int nOrglTileX, int nOrglTileY, int nTileSizeX, int nTileSizeY, int nMapTileX, int nMapTileY);
	~cRat();

public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	
	void					OnRatReset();

};

#endif