#include "cLogo.h"

cLogo::cLogo()
{
	m_pSprite				= NULL;

	m_fAlpa					= 1.f;
	m_fTime					= NULL;
}


cLogo::~cLogo()
{
	SAFE_DELETE(m_pSprite);	//!< 동적 할당한 변수를 delete시켜주는 메크로
}


HRESULT cLogo::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"Resource/Image/TE/MenuLogo/FIFO.Te");
		m_pSprite->Entry(L"Resource/Image/TE/MenuLogo/Logo1.Te");
		m_pSprite->Entry(L"Resource/Image/TE/MenuLogo/Logo2.Te");
	}

	return S_OK;
}


HRESULT cLogo::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	return S_OK;
}


void cLogo::OnLostDevice(void* pUserContext)
{
}


void cLogo::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite); //!< 동적 할당한 변수를 delete시켜주는 메크로
}


void cLogo::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if(m_fTime < 6.f)
	{
		if(m_fAlpa > 0)
			m_fAlpa -= 0.05f;
		else
			m_fTime += fElapsedTime;
	}
	else
	{ 
		m_fAlpa += 0.05f;
		if(m_fAlpa >= 1.f)
			cMain()->Trans(L"menu");
	}
}


void cLogo::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{	
		if(m_fTime < 3.f)
		{
			m_pSprite->Render(L"Logo",D3DXVECTOR3( 450, 300, 0 ),D3DXCOLOR(1,1,1,1));
		}
		else
		{
			m_pSprite->Render(L"페인페아",KGRect(0,0,900,600),D3DXCOLOR(1,1,1,1));
			m_pSprite->Render(L"팀로고",D3DXVECTOR3( 450, 300, 0 ), D3DXCOLOR(1,1,1,1));
		}
		m_pSprite->Render(L"페인페아",KGRect(0,0,900,600),D3DXCOLOR(1,1,1,m_fAlpa));

		V(pd3dDevice->EndScene());
	}
}


void cLogo::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
//#if defined(DEBUE) || defined(_DEBUG)
	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case VK_RETURN:
		if(m_fTime < 3.f)
			m_fTime = 3.f;
		else
			m_fTime = 6.f;
		break;
	}
//#endif
}