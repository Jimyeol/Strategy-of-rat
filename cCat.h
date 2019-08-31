#ifndef _cCat_H
#define _cCat_H

#include "MyInclude.h"
#include <KGEmotion.h>

using namespace KG;

class cCat
{

private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGRenderSingle*			m_pSingleHero[HEROMOVE_MAX];



public:


public:
	cCat(KGAnimate* pAnimate, int nTileSizeX, int nTileSizeY, int nMapTileX, int nMapTileY);
	~cCat();

public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

};

#endif