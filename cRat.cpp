#include "cRat.h"
#include "CMAIN.h"

cRat::cRat(KGSound* pSound, KGAnimate* pAnimate, int nOrglTileX, int nOrglTileY, int nTileSizeX, int nTileSizeY, int nMapTileX, int nMapTileY)
{

	m_nCurrentAct			= HERO_STAND;		//초기행동 
	m_pSound				= pSound;

	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;

	m_nTileSizeX			= nTileSizeX;		//타일사이즈
	m_nTileSizeY			= nTileSizeY;

	m_nHeroTileX			= nOrglTileX-1;
	m_nHeroTileY			= nOrglTileY-1;		//배열은 0부터 시작하니 -1 필수!	

	m_nHeroOrgX				= nOrglTileX-1;
	m_nHeroOrgY				= nOrglTileY-1;		//히어로 원래 위치

	m_nHeroPosX				= m_nHeroTileY * nTileSizeX;		//히어로 초기 위치. 
	m_nHeroPosY				= m_nHeroTileX * nTileSizeY;

	m_nHeroLieX				= m_nHeroTileY * nTileSizeX;
	m_nHeroLieY				= m_nHeroTileX * nTileSizeY;		//가짜 좌표 진짜 값과 항상 같이 움직임

	m_nMapTileX				= nMapTileX;
	m_nMapTileY				= nMapTileY;

	m_nKeyTiming			= 0.f;		//키 두번 누르는거 해결 방안.

	m_nTileAttribe			= -1;

	for( int i = 0; i < HEROMOVE_MAX; i++ )
	{
		m_pSingleHero[i]			= NULL;
		if( m_pSingleHero[i] == NULL )
		{
			m_pSingleHero[i]		= new KGRenderSingle( m_pAnimate ) ;
		}
	}
	m_pHeroParticle					= new KGRenderSingle( m_pAnimate ) ;

	m_pSingleHero[HEROMOVE_L]->Entry(L"LeftMotion", D3DXVECTOR3((float)m_nHeroLieX + m_nTileSizeX/2,
		(float)m_nHeroLieY + m_nTileSizeY/2, 0));

	m_pSingleHero[HEROMOVE_R]->Entry(L"RightMotion", D3DXVECTOR3((float)m_nHeroLieX + m_nTileSizeX/2,
		(float)m_nHeroLieY + m_nTileSizeY/2, 0));

	m_pSingleHero[HEROMOVE_U]->Entry(L"BackMotion", D3DXVECTOR3((float)m_nHeroLieX + m_nTileSizeX/2,
		(float)m_nHeroLieY + m_nTileSizeY/2, 0));

	m_pSingleHero[HEROMOVE_D]->Entry(L"FrontMotion", D3DXVECTOR3((float)m_nHeroLieX + m_nTileSizeX/2,
		(float)m_nHeroLieY + m_nTileSizeY/2, 0));

	m_pSingleHero[HERO_CAT]->Entry(L"CatMotion", D3DXVECTOR3((float)m_nHeroLieX + m_nTileSizeX/2,
		(float)m_nHeroLieY + m_nTileSizeY/2, 0));

	m_pSingleHero[HERO_ARR]->Entry(L"GetMotion", D3DXVECTOR3((float)m_nHeroLieX + m_nTileSizeX/2,
		(float)m_nHeroLieY + m_nTileSizeY/2, 0));

	m_pSingleHero[HERO_STAND]->Entry(L"StandMotion", D3DXVECTOR3((float)m_nHeroLieX + m_nTileSizeX/2,
		(float)m_nHeroLieY + m_nTileSizeY/2, 0));


	for( int i = 0; i < HEROMOVE_MAX; i++ )
	{
		//======================================================
		// 사이즈 설정
		//======================================================
		int SizeSum = m_nTileSizeX + m_nTileSizeY;
		if( SizeSum >= 0 && SizeSum <= 400 )
			m_pSingleHero[i]->SetScale(0.3f);
		else if( SizeSum > 400 && SizeSum <= 600)
			m_pSingleHero[i]->SetScale(0.6f);
	}

}


cRat::~cRat()
{
	for( int i = 0; i < HEROMOVE_MAX; i++ )
	{
		SAFE_DELETE(m_pSingleHero[i]);
	}
	SAFE_DELETE(m_pHeroParticle);
}


void cRat::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if( cMain()->m_nCurrentStage == -1)
		return;

	cMapMng* pMapMng = (cMapMng*)cMain()->GetCurrent();

	m_nKeyTiming += fElapsedTime;

	m_nHeroLieX				= (m_nHeroTileY) * m_nTileSizeX;
	m_nHeroLieY				= (m_nHeroTileX) * m_nTileSizeY;

	if( m_nHeroLieX != m_nHeroPosX )
	{
		if( m_nHeroLieX >= m_nHeroPosX )
		{
			m_nHeroPosX += HERO_SPEED;
			if( m_nHeroLieX+4 >= m_nHeroPosX && m_nHeroLieX-4 <= m_nHeroPosX)
			{
				int i;
				i = m_nHeroLieX - m_nHeroPosX;
				m_nHeroPosX += i;
				m_nCurrentAct = HERO_STAND; //
			}
		}
		else
		{
			m_nHeroPosX -= HERO_SPEED;
			if( m_nHeroLieX+4 >= m_nHeroPosX && m_nHeroLieX-4 <= m_nHeroPosX)
			{
				int i;
				i = m_nHeroLieX - m_nHeroPosX;
				m_nHeroPosX -= i;
				m_nCurrentAct = HERO_STAND; //
			}
		}
	}
	if( m_nHeroLieY != m_nHeroPosY )
	{
		if( m_nHeroLieY >= m_nHeroPosY )
		{
			m_nHeroPosY += HERO_SPEED;
			if( m_nHeroLieY+4 >= m_nHeroPosY && m_nHeroLieY-4 <= m_nHeroPosY)
			{
				int i;
				i = m_nHeroLieY - m_nHeroPosY;
				m_nHeroPosY += i;
				m_nCurrentAct = HERO_STAND; //
			}
		}
		else
		{
			m_nHeroPosY -= HERO_SPEED;
			if( m_nHeroLieY+4 >= m_nHeroPosY && m_nHeroLieY-4 <= m_nHeroPosY)
			{
				int i;
				i = m_nHeroLieY - m_nHeroPosY;
				m_nHeroPosY -= i;
				m_nCurrentAct = HERO_STAND; //
			}
		}
	}


	switch( pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->GetCurrentTile( m_nHeroTileX, m_nHeroTileY ) )
	{
	case HERO_CAT:
		if( m_nHeroLieX+4 >= m_nHeroPosX && m_nHeroLieX-4 <= m_nHeroPosX)
		{
			if( m_nHeroLieY+4 >= m_nHeroPosY && m_nHeroLieY-4 <= m_nHeroPosY)
			{
			m_nCurrentAct = HERO_CAT;
			}
		}
		break;
	case HERO_ARR:
		if( m_nHeroLieX+4 >= m_nHeroPosX && m_nHeroLieX-4 <= m_nHeroPosX)
		{
			if( m_nHeroLieY+4 >= m_nHeroPosY && m_nHeroLieY-4 <= m_nHeroPosY)
			{
			m_nCurrentAct = HERO_ARR;
			}
		}
		break;
	default:
		break;
	}

	printf(" Hero Pos X : %d\n", m_nHeroPosX);
	printf(" Hero Lie X : %d\n", m_nHeroLieX);

	for( int i = 0; i < HEROMOVE_MAX; i++ )
	{
		m_pSingleHero[i]->SetMove(D3DXVECTOR3((float)m_nHeroPosX + m_nTileSizeX/2, (float)m_nHeroPosY + m_nTileSizeY/2, 0));
	}

}


void cRat::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	SAFE_ONFRAMERENDER(m_pSingleHero[m_nCurrentAct]);
	SAFE_ONFRAMERENDER(m_pHeroParticle);
}


void cRat::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	cMapMng* pMapMng = (cMapMng*)cMain()->GetCurrent();

	if( m_nKeyTiming >= 0.3f)
	{
		switch(nChar)
		{
		case VK_LEFT:
			if( m_nHeroTileY <= 0 )
				break;
			m_nTileAttribe = pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->GetAttrib( m_nHeroTileX, m_nHeroTileY );
			if( pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->ZoneMoveStop( m_nHeroTileX, m_nHeroTileY-1 ) == true)
			{
				m_nCurrentAct = HEROMOVE_L;
				m_nHeroTileY--;
				pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->ZoneCountSetting( m_nHeroTileX, m_nHeroTileY );
			}
			break;
		case VK_RIGHT:
			if( m_nHeroTileY >= m_nMapTileY-1 )
				break;
			m_nTileAttribe = pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->GetAttrib( m_nHeroTileX, m_nHeroTileY );
			if( pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->ZoneMoveStop( m_nHeroTileX, m_nHeroTileY+1 ) == true)
			{
				m_nCurrentAct = HEROMOVE_R;
				m_nHeroTileY++;
				pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->ZoneCountSetting( m_nHeroTileX, m_nHeroTileY );
			}
			break;
		case VK_UP:
			if( m_nHeroTileX <= 0 )
				break;
			m_nTileAttribe = pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->GetAttrib( m_nHeroTileX, m_nHeroTileY );
			if( pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->ZoneMoveStop( m_nHeroTileX-1, m_nHeroTileY ) == true)
			{
				m_nCurrentAct = HEROMOVE_U;
				m_nHeroTileX--;
				pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->ZoneCountSetting( m_nHeroTileX, m_nHeroTileY );
			}
			break;
		case VK_DOWN:
			if( m_nHeroTileX >= m_nMapTileX-1 )
				break;
			m_nTileAttribe = pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->GetAttrib( m_nHeroTileX, m_nHeroTileY );
			if( pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->ZoneMoveStop( m_nHeroTileX+1, m_nHeroTileY ) == true)
			{
				m_nCurrentAct = HEROMOVE_D;
				m_nHeroTileX++;
				pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->ZoneCountSetting( m_nHeroTileX, m_nHeroTileY );
			}
			break;
		}
		m_nKeyTiming = 0.f;

	}
}


void cRat::OnRatReset()
{
	if( cMain()->m_bMusicOn )
	{
		m_pSound->Play(L"ClearSound");
	}
	cMapMng* pMapMng = (cMapMng*)cMain()->GetCurrent();
	m_nCurrentAct			= HERO_STAND;
	//히어로 위치 한번에 셋팅.
	m_nHeroTileX			= m_nHeroOrgX;
	m_nHeroTileY			= m_nHeroOrgY;

	m_nHeroPosX				= m_nHeroOrgY * m_nTileSizeX;
	m_nHeroPosY				= m_nHeroOrgX * m_nTileSizeY;

	m_nHeroLieX				= m_nHeroOrgY * m_nTileSizeX;
	m_nHeroLieY				= m_nHeroOrgX * m_nTileSizeY;

	for( int i = 0; i < pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->m_nInterFaceCount; i++ )
		pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->m_ppInterFace[i]->m_nZoneCount = 
		pMapMng->m_ppStagePart[cMain()->m_nCurrentStage]->m_ppInterFace[i]->m_nOrgZoneCount;



	m_pHeroParticle->Entry(L"HiParticle", D3DXVECTOR3((float)m_nHeroLieX + m_nTileSizeX/2+16,
		(float)m_nHeroLieY + m_nTileSizeY/2, 0), true, 1);
	int SizeSum = m_nTileSizeX + m_nTileSizeY;
	if( SizeSum >= 0 && SizeSum <= 400 )
		m_pHeroParticle->SetScale(1.6f);
	else if( SizeSum > 400 && SizeSum <= 600)
		m_pHeroParticle->SetScale(2.7f);

}