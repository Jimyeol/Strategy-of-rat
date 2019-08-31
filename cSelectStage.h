#ifndef _cSelectStage_H
#define _cSelectStage_H

#include "MyInclude.h"
#include <KGEmotion.h>

using namespace KG;

class cSelectStage : public KGScene , public KGResponseDialog
{

private:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;

public:
	cSelectStage();
	~cSelectStage();

public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

};

#endif