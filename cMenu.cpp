#include "cMenu.h"

WCHAR m_sName[6][255] = { L"∞‘¿”1", L"ø…º«1", L"≥™∞°±‚1", L" ", L" ", L" "};


cMenu::cMenu()
{
	m_pSprite				= NULL;
	m_pBgm					= NULL;
	m_pSound				= NULL;
	m_pAnimate				= NULL;
	m_bTjfaudtjCheck		= false;
	for( int i = 0; i < 2; i++)
	{
		m_pCatHero[i]				= NULL;
	}
	m_nCatState				= 0;

	m_nMouseState = Mouse_StandMotion;
	m_nWhatDaGodDa = WDGD_RightMotion;

	m_fAlpa					= 1.f;
	m_fAlpa2				= 0.f;
	m_nWhat					= 4;
	m_nOption				= 4;
	m_bDone					= false;
	m_fChogihwa				= 0.f;
	m_fBlackX				= 300.f;

	m_fDCircle = 5000.f;
	m_nMouseMoveX = m_nMouseMoveY = 0.f;

	//memset(m_nButton,NULL,sizeof(m_nButton));
	memset(m_vButton,NULL,sizeof(m_vButton));
	memset(m_pWhatDaGodDa,NULL,sizeof(m_pWhatDaGodDa));
	memset(m_pSingle,NULL,sizeof(m_pSingle));
	for(int i = 0; i < 3; i++)
		m_vButton[i] = D3DXVECTOR3(GaRo,SeRo+((float)i*100),0);
	//for(int i = 0; i < 3; i++)
	//	m_nButton[0][i] = 1;

	m_vMouse = D3DXVECTOR3(GaRo+70,SeRo,0);
	m_vWhatDaGodDa = D3DXVECTOR3(50,500,0);

}


cMenu::~cMenu()
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	for( int i = 0; i < 2; i++)
	{
		SAFE_DELETE(m_pCatHero[i]);
	}
	for(int i = 0; i < Mouse_MaxMotion; i++)
		SAFE_DELETE(m_pSingle[i]);
	for(int i = 0; i < WDGD_MaxMotion; i++)
		SAFE_DELETE(m_pWhatDaGodDa[i]);
	if(m_pBgm)
	{
		m_pBgm->Stop();
		SAFE_DELETE(m_pBgm);
	}
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
}


HRESULT cMenu::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(!m_pSprite)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"Resource/Image/TE/MenuLogo/FIFO.Te");
		m_pSprite->Entry(L"Resource/Image/TE/object.Te");
		m_pSprite->Entry(L"Resource/Image/TE/MenuLogo/Cheeze.Te");
		m_pSprite->Entry(L"Resource/Image/TE/MenuLogo/Button.Te");
		m_pSprite->Entry(L"Resource/Image/TE/MenuLogo/Circle.Te");
		m_pSprite->Entry(L"Resource/Image/TE/MenuLogo/Chogihwa.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Rat/RatMotion1.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Rat/RatMotion2.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Cat/CatSleep1.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Cat/CatSleep2.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Back.Te");
		m_pSprite->Entry(L"Resource/Image/TE/tjfaudtj.Te");
	}
	if(!m_pAnimate)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
		m_pAnimate->Entry(L"Resource/Image/TA/RatMotion.Ta");
		m_pAnimate->Entry(L"Resource/Image/TA/SleepCat.Ta");
	}
	for(int i = 0; i < Mouse_MaxMotion; i++)
		if(!m_pSingle[i])
		{
			m_pSingle[i]	= new KGRenderSingle(m_pAnimate);
		}	
	for(int i = 0; i < WDGD_MaxMotion; i++)
		if(!m_pWhatDaGodDa[i])
		{
			m_pWhatDaGodDa[i] = new KGRenderSingle(m_pAnimate);
		}
		
	if(!m_pBgm)
	{
		m_pBgm			= new KGSound(cMain()->GethWnd());
		m_pBgm->Entry(L"BackMusic", L"Resource/Sound/BackMusic.wav");
		m_pBgm->Play(L"BackMusic");
	}
	if(!m_pSound)
	{
		m_pSound			= new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"ButtonClick", L"Resource/Sound/ButtonClick.wav");
		//m_pSound->Play(L"BackMusic");
	}
	for( int i = 0; i < 2; i++)
	{
		if( m_pCatHero[i] == NULL)
		{
			m_pCatHero[i]			= new KGRenderSingle(m_pAnimate);
		}
	}

	m_pCatHero[0]->Entry(L"CatSleep", D3DXVECTOR3(400,270,0));
	m_pCatHero[1]->Entry(L"GetUpCat", D3DXVECTOR3(400,270,0));
	m_pCatHero[0]->SetScale(0.8f);
	m_pCatHero[1]->SetScale(0.8f);

	m_pSingle[Mouse_StandMotion]->Entry(L"StandMotion",D3DXVECTOR3(0,0,0));
	m_pSingle[Mouse_BackMotion]->Entry(L"BackMotion",D3DXVECTOR3(0,0,0));
	m_pSingle[Mouse_FrontMotion]->Entry(L"FrontMotion",D3DXVECTOR3(0,0,0));
	m_pSingle[Mouse_LeftMotion]->Entry(L"LeftMotion",D3DXVECTOR3(0,0,0));
	m_pSingle[Mouse_RightMotion]->Entry(L"RightMotion",D3DXVECTOR3(0,0,0));

	m_pWhatDaGodDa[WDGD_LeftMotion]->Entry(L"LeftMotion",D3DXVECTOR3(0,0,0));
	m_pWhatDaGodDa[WDGD_RightMotion]->Entry(L"RightMotion",D3DXVECTOR3(0,0,0));

	return S_OK;
}


HRESULT cMenu::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	return S_OK;
}


void cMenu::OnLostDevice(void* pUserContext)
{
}


void cMenu::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	for( int i = 0; i < 2; i++)
	{
		SAFE_DELETE(m_pCatHero[i]);
	}
	for(int i = 0; i < Mouse_MaxMotion; i++)
		SAFE_DELETE(m_pSingle[i]);
	for(int i = 0; i < WDGD_MaxMotion; i++)
		SAFE_DELETE(m_pWhatDaGodDa[i]);
	if(m_pBgm)
	{
		m_pBgm->Stop();
		SAFE_DELETE(m_pBgm);
	}
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
}


void cMenu::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if(m_nWhatDaGodDa == WDGD_RightMotion)
	{
		m_vWhatDaGodDa.x += 8;
		if(m_vWhatDaGodDa.x > 950.f)
		{
			m_nWhatDaGodDa = WDGD_LeftMotion;
		}
	}
	else
	{
		m_vWhatDaGodDa.x -= 8;
		if(m_vWhatDaGodDa.x < -50)
		{
			m_nWhatDaGodDa = WDGD_RightMotion;
		}
	}
	if(m_fChogihwa > 0.f)
	{
		m_fChogihwa -= 0.05f;
	}
	if(m_fDCircle != 5000)
	{
		m_fDCircle -= 250;
		if(m_fBlackX != 0)
			m_fBlackX -= 15;
		if(m_fDCircle == -500)
			cMain()->Trans(L"map");
		m_nCatState = 1;
	}
	if(m_fAlpa != 0.f)
		m_fAlpa -= 0.01f;
	if(m_nMouseMoveX != 0)
	{
		if(m_nMouseMoveX < 0)
		{
			m_nMouseMoveX	+= 5;
			m_vMouse.x		-= 5;
			if(m_nMouseMoveX == 0)
				hakin(3);
		}
		else
		{
			m_nMouseMoveX	-= 5;
			m_vMouse.x		+= 5;
			if(m_nMouseMoveX == 0)
				hakin(4);
		}
	}
	else if(m_nMouseMoveY == m_nMouseMoveX)
	{
		m_nMouseState = Mouse_StandMotion;
	}

	if(m_nMouseMoveY != 0)
	{
		if(m_nMouseMoveY < 0)
		{
			m_nMouseMoveY	+= 5;
			m_vMouse.y		-= 5;
			if(m_nMouseMoveY == 0)
				hakin(2);
		}
		else
		{
			m_nMouseMoveY	-= 5;
			m_vMouse.y		+= 5;
			if(m_nMouseMoveY == 0)
				hakin(1);
		}
	}
	

	if(m_nMouseMoveX == m_nMouseMoveY)
	{
		Where();
	}
	ButtonMove();
}


void cMenu::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;
	D3DXCOLOR				color = D3DXCOLOR(1,1,1,1);

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{	
		m_pSprite->Render(L"dd",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));

		Buttons(color);
		if(m_bDone)
		{
			if(m_bSound)
				m_pSprite->Render(L"ØÅ¿∏",m_vButton[3],D3DXCOLOR(1,1,1,1));
			if(m_bBgm)
				m_pSprite->Render(L"ØÅ¿∏",m_vButton[4],D3DXCOLOR(1,1,1,1));
		}
		//m_pSprite->Render(L"¡„¡¬",m_vMouse,D3DXCOLOR(1,1,1,1));
		m_pSingle[m_nMouseState]->SetScale(0.4f);
		m_pSingle[m_nMouseState]->SetMove(m_vMouse);
		SAFE_ONFRAMERENDER(m_pSingle[m_nMouseState]);

		m_pWhatDaGodDa[m_nWhatDaGodDa]->SetScale(0.4f);
		m_pWhatDaGodDa[m_nWhatDaGodDa]->SetMove(m_vWhatDaGodDa);
		m_pSprite->Render(L"¡¶∏Ò∏«",D3DXVECTOR3(450,520,0),D3DXCOLOR(1,1,1,1));

		SAFE_ONFRAMERENDER(m_pWhatDaGodDa[m_nWhatDaGodDa]);
		SAFE_ONFRAMERENDER(m_pCatHero[m_nCatState]);
		m_pSprite->Render(L"∆‰¿Œ∆‰æ∆",KGRect(0,0,900,600),D3DXCOLOR(1,1,1,m_fAlpa));
		m_pSprite->Render(L"ø¯»ø∞˙",KGRect(-m_fDCircle - 380 ,-m_fDCircle -900 ,m_fDCircle + 1620 , m_fDCircle + 1100),D3DXCOLOR(1,1,1,m_fAlpa2));
		m_pSprite->Render(L"∞Àπ⁄",KGRect(0,0,150 - (int)m_fBlackX, 1000),D3DXCOLOR(1,1,1,1));

		if( m_bTjfaudtjCheck == true)
			m_pSprite->Render(L"º≥∏Ìº≠",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		V(pd3dDevice->EndScene());
	}
}


void cMenu::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	switch(nChar)
	{
	case VK_RIGHT:
		m_nMouseState = Mouse_RightMotion;
		break;
	case VK_LEFT:
		m_nMouseState = Mouse_LeftMotion;
		break;
	case VK_UP:
		m_nMouseState = Mouse_BackMotion;
		break;
	case VK_DOWN:
		m_nMouseState = Mouse_FrontMotion;
		break;
	case VK_RETURN:
		
		break;
	}
#if defined(DEBUE) || defined(_DEBUG)
#endif

}

LRESULT cMenu::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	if(m_nMouseMoveX == 0 && m_nMouseMoveY == 0 && m_fDCircle == 5000)
	{
		switch(uMsg) 
		{
		case WM_KEYDOWN:
			switch(wParam)
			{
			case VK_DOWN:
				m_nMouseMoveY += 100;
				if(m_vMouse.y + 100 > SeRo + 200
					|| Macgi(0) == true)
				{
					m_nMouseMoveY -= 100;
				}
				break;
			case VK_UP:
				m_nMouseMoveY -= 100;
				if(m_vMouse.y - 100 < SeRo
					|| Macgi(1) == true)
				{
					m_nMouseMoveY += 100;
				}
				break;
			case VK_LEFT:
				m_nMouseMoveX -= 150;
				if(m_vMouse.x - 150 < GaRo + 70 -200
					|| Macgi(2) == true)
				{
					m_nMouseMoveX += 150;		
				}
				break;
			case VK_RIGHT:
				m_nMouseMoveX += 150;
				if(m_vMouse.x + 150 > GaRo + 70
					|| Macgi(3) == true)
				{
					m_nMouseMoveX -= 150;
				}
				break;
			case VK_RETURN:
				if( cMain()->m_bEffectOn )
				{
					m_pSound->Play(L"ButtonClick");
				}
				Return();
				break;
			case VK_ESCAPE:
				if ( m_bTjfaudtjCheck )
					m_bTjfaudtjCheck = false;
				break;
			}
		}
	}
	return uMsg;
}

void cMenu::Buttons(D3DXCOLOR color)
{
	for(int i = 2; i > -1; i--)
		for(int j = 0; j < 3; j++)
			m_pSprite->Render(m_sName[(i*3)+j],m_vButton[(i*3)+j],color);
}

void cMenu::Where()
{
	if((m_vMouse.x - (GaRo+70))/150 == 0)
	{
		swprintf(m_sName[0],L"∞‘¿”1");
		swprintf(m_sName[1],L"ø…º«1");
		swprintf(m_sName[2],L"≥™∞°±‚1");		

		switch((int)(m_vMouse.y - (SeRo))/100)
		{
		case 0:
			swprintf(m_sName[0],L"∞‘¿”2");
			swprintf(m_sName[3],L"Ω√¿€1");
			m_nWhat = 0;
			break;
		case 1:
			swprintf(m_sName[1],L"ø…º«2");
			swprintf(m_sName[3],L"»ø∞˙¿Ω1");
			swprintf(m_sName[4],L"∫Í±›1");
			swprintf(m_sName[5],L"√ ±‚»≠1");
			m_nWhat = 1;
			break;
		case 2:
			swprintf(m_sName[2],L"≥™∞°±‚2");
			swprintf(m_sName[5],L"øπ1");
			m_nWhat = 2;
			break;
		}
	}
	
	SubButtons((int)(m_vMouse.y - (SeRo))/100);
}

void cMenu::ButtonMove()
{
	for(int i= 0; i< 3; i++)
		if(wcsstr(m_sName[i],L"2") != 0)
		{
			switch(i)
			{
			case 0:
				if(m_vButton[3] == D3DXVECTOR3(0,0,0))
				{
					m_vButton[3] = D3DXVECTOR3(m_vButton[0].x,m_vButton[0].y,0);
				}
				else
				{
					if(m_vButton[3].x > m_vButton[0].x - 150)
					{
						m_vButton[3].x -= 5;
					}
				}
				break;
			case 1:
				if(m_vButton[3] == D3DXVECTOR3(0,0,0))
				{
					m_vButton[3] = m_vButton[4] = m_vButton[5] = D3DXVECTOR3(m_vButton[1].x,m_vButton[1].y,0);
				}
				else
				{
					if(m_vButton[3].x > m_vButton[1].x - 150)
					{
						m_vButton[3].x -= 5;
						m_vButton[4].x -= 5;
						m_vButton[5].x -= 5;
					}
					else if(m_vButton[5].y < m_vButton[1].y + 100)
					{
						m_vButton[3].y -= 5;
						m_vButton[5].y += 5;
					}
					else
					{
						if(!m_bDone)
							m_bDone = true;
					}
				}
				break;
			case 2:
				if(m_vButton[5] == D3DXVECTOR3(0,0,0))
				{
					m_vButton[5] = D3DXVECTOR3(m_vButton[2].x,m_vButton[2].y,0);
				}
				else
				{
					if(m_vButton[5].x > m_vButton[2].x - 150)
					{
						m_vButton[5].x -= 5;
					}
				}
				break;
			}
		}
}

void cMenu::hakin(int i)
{
	if(m_vMouse.x == GaRo + 70)
	{
		if(m_nWhat != (m_vMouse.y - SeRo)/100)
		{
			for(int j = 0; j < 3; j++)
			{
				m_bDone = false;
				m_vButton[3+j] = D3DXVECTOR3(0,0,0);
				swprintf(m_sName[3+j],L" ");
			}
		}
	}
	m_nMouseState = Mouse_StandMotion;
}

void cMenu::SubButtons(int i)
{
	if((m_vMouse.x - (GaRo+70))/-150 == 1)
	{
		switch(m_nWhat)
		{
		case 0:
			swprintf(m_sName[3],L"Ω√¿€2");
			break;
		case 1:
			switch(i)
			{
			case 0:
				swprintf(m_sName[3],L"»ø∞˙¿Ω2");
				swprintf(m_sName[4],L"∫Í±›1");
				swprintf(m_sName[5],L"√ ±‚»≠1");
				m_nOption = 0;
				break;
			case 1:
				swprintf(m_sName[3],L"»ø∞˙¿Ω1");
				swprintf(m_sName[4],L"∫Í±›2");
				swprintf(m_sName[5],L"√ ±‚»≠1");
				m_nOption = 1;
				break;
			case 2:
				swprintf(m_sName[3],L"»ø∞˙¿Ω1");
				swprintf(m_sName[4],L"∫Í±›1");
				swprintf(m_sName[5],L"√ ±‚»≠2");
				m_nOption = 2;
				break;
			}
			break;
		case 2:
			swprintf(m_sName[5],L"øπ2");
			break;
		}
	}
}


void cMenu::Return()
{
	switch(m_nWhat)
	{
	case 0:
		if(((int)m_vMouse.x-770)/(-150) * 3 + ((int)m_vMouse.y-100)/(100) == 3 ||
			((int)m_vMouse.x-770)/(-150) * 3 + ((int)m_vMouse.y-100)/(100) == 4)
		{
			m_fDCircle -= 250 ;
			m_fAlpa2 += 1;
		}
		break;
	case 1:
		switch(((int)m_vMouse.x-770)/(-150) * 3 + ((int)m_vMouse.y-100)/(100))
		{
		case 3:
			if(m_bSound)
			{
				m_bSound = false;
				cMain()->m_bEffectOn = false;
				m_pSound->Stop();
			}
			else
			{
				m_bSound = true;
				cMain()->m_bEffectOn = true;
			}
			break;
		case 4:
			if(m_bBgm)
			{
				m_bBgm = false;
				cMain()->m_bMusicOn = false;
				m_pBgm->Stop();
			}
			else
			{
				m_bBgm = true;
				cMain()->m_bMusicOn = true;
				m_pBgm->Play(L"BackMusic");
			}
			break;
		case 5:
			m_fChogihwa = 1.f;
			if(!m_bTjfaudtjCheck)
			m_bTjfaudtjCheck = true;
			break;
		}
		break;
	case 2:
		if(((int)m_vMouse.x-770)/(-150) * 3 + ((int)m_vMouse.y-100)/(100) == 5)
			cMain()->CloseWindow();
		break;
	}
}

bool cMenu::Macgi(int i)
{
	switch(m_nWhat)
	{
	case 0:
		switch(i)
		{
		case 0:
			if((m_vMouse.x - (GaRo + 70))/(-150) == 1)
				return true;
			break;
		}
		break;
	case 2:
		switch(i)
		{
		case 1:
			if((m_vMouse.x - (GaRo + 70))/(-150) == 1)
				return true;
			break;
		}
		break;
	}

	return false;
}