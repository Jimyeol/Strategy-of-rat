#include "cZone.h"
#include "CMAIN.h"

cZone::cZone(KGAnimate* pAnimate)
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

}


cZone::~cZone()
{
	m_pSprite				= NULL;
	m_pAnimate				= NULL;
}


void cZone::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{


}


void cZone::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

}


void cZone::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

	switch(nChar)
	{
	case VK_UP:
		break;
	case VK_DOWN:
		break;
	case VK_LEFT:
		break;
	case VK_RIGHT:
		break;
	}
}