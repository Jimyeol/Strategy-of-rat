#ifndef _cZone_H
#define _cZone_H

#include "MyInclude.h"
#include <KGEmotion.h>

using namespace KG;

class cZone
{

private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;

public:
	int						m_nKindZone;

public:
	cZone()
	{
		m_nKindZone = -1;
	}
	cZone(KGAnimate* pAnimate);
	~cZone();

public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

};

#endif