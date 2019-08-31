#include "cStagePart.h"


cStagePart::cStagePart(KGSound* pSound, KGAnimate* pAnimate, KGDialog* pZoneDialog, int nStageNumber, WCHAR *cStageRoot, WCHAR *cStageName)
{
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;
	m_pSound				= pSound;
	m_pZoneDialog			= pZoneDialog;
	m_nStageNumber			= nStageNumber;
	m_pRat					= NULL;
	m_ppInterFace			= NULL;
	m_pppZone				= NULL;
	m_pFont					= NULL;
	m_nInterFaceCount		= 0;

	m_fFontAlpha			= 1.f;			//글씨 알파값
	m_bChesseBool			= false;

	m_fCheeseTime			= 0.f;

	if(m_pFont == NULL)
	{
		m_pFont				= new KGFont(m_pSprite->Getd3dDevice());
		m_pFont->Entry(1, L"Resource/Font/Melrang.ttf", L"Rix멜랑촐리 M", 100, 80);
		m_pFont->Entry(2, L"Resource/Font/Melrang.ttf", L"Rix멜랑촐리 M", 100, 80);
	}

	wcscpy(m_cStageName, cStageName);		//맵의 이름
	wcscpy(m_cStageRoot, cStageRoot);		//로드할 맵의 경로 복사

	LoadObjectData(m_cStageRoot);
}	


cStagePart::~cStagePart()
{
	m_pSprite				= NULL;
	m_pAnimate				= NULL;
	m_pZoneDialog			= NULL;

	SAFE_DELETE(m_pRat);

	if(m_ppInterFace != NULL)
	{
		for( int i = 0; i < m_nInterFaceCount; i++ )
		{
			SAFE_DELETE(m_ppInterFace[i]);
		}
		SAFE_DELETE(m_ppInterFace);
	}

	if(m_pppZone != NULL)
	{
		for( int i = 0; i < m_nTileNumberX; i++ )
		{
			for( int j = 0; j < m_nTileNumberY; j++ )
			{
				SAFE_DELETE(m_pppZone[i][j]);
			}
			SAFE_DELETE(m_pppZone[i]);
		}
		SAFE_DELETE(m_pppZone);
	}
	SAFE_DELETE(m_pFont);
}


void cStagePart::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pFont);
}


void cStagePart::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	cMapMng* pMapMng = (cMapMng*)cMain()->GetCurrent();

	m_fCheeseTime += fElapsedTime;
	m_srtTagGetCat.m_fCatTime += fElapsedTime;
	m_srtTagGetCat.m_fDonTime += fElapsedTime;

	printf("%f\n", m_fCheeseTime);

	SAFE_ONFRAMEMOVE(m_pRat);
	for( int i = 0; i < m_nInterFaceCount; i++ )
		SAFE_ONFRAMEMOVE(m_ppInterFace[i]);
	
	if( m_fFontAlpha >= 0)
	{
		m_fFontAlpha -= 0.004f;
	}


	//============================================
	// 스테이지 깨면 1초후에 다음판이동
	//============================================
	if( m_bChesseBool)
	{

		if( pMapMng->m_nMapListCount == cMain()->m_nCurrentStage+1);
		else
		{
			if( m_fCheeseTime >= 2.0f)
			{
				m_fCheeseTime = 0.f;
				m_bChesseBool = false;
				m_pRat->OnRatReset();
				m_fFontAlpha = 1.f;
				cMain()->m_nCurrentStage++;
			}
		}
	}

	//============================================
	// 고양이를 만나면?
	//============================================
	if( m_srtTagGetCat.m_bGetCat )
	{
		if( m_srtTagGetCat.m_fCatTime >= 2.0f && !m_srtTagGetCat.m_bCatAnimationCheck)
		{
			m_srtTagGetCat.m_bCatAnimationCheck = true;
		}

		if( m_srtTagGetCat.m_bCatAnimationCheck == true)
		{
			if( !m_srtTagGetCat.m_bKeyCheck)
			{
				if( m_srtTagGetCat.m_nY != 0 )
					m_srtTagGetCat.m_nY += 10;
			}
			else
			{
				if( m_srtTagGetCat.m_nY != -600 )
					m_srtTagGetCat.m_nY -= 10;
				if( m_srtTagGetCat.m_nY == -600 )
				{
					m_srtTagGetCat.m_bGetCat		= false;
					m_srtTagGetCat.m_bCatAnimationCheck = false;
					m_srtTagGetCat.m_bKeyCheck		= false;
					m_srtTagGetCat.m_fCatTime		= 0.f;
					m_srtTagGetCat.m_fDonTime		= 0.f;
					m_srtTagGetCat.m_nX			= 0;
					m_srtTagGetCat.m_nY			= -600;
					m_pRat->OnRatReset();
				}
			}
		}
	}
}


void cStagePart::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	for( int i = 0; i < m_nTileNumberY; i++ )
	{
		for( int j = 0; j < m_nTileNumberX; j++ )
		{
			OnRenderZonePart( i, j, m_pppZone[j][i]->m_nKindZone );
			OnRenderClickZonePart( m_pRat->m_nHeroTileY , m_pRat->m_nHeroTileX , 
				m_pppZone[m_pRat->m_nHeroTileX][m_pRat->m_nHeroTileY]->m_nKindZone );
		}
	}
	SAFE_ONFRAMERENDER(m_pRat);

	for( int i = 0; i < m_nInterFaceCount; i++ )
		SAFE_ONFRAMERENDER(m_ppInterFace[i]);

	m_pFont->DrawText(1, NULL, m_cStageName, -1, KGRect(150,230,1024,768), DT_NOCLIP , D3DXCOLOR(0, 0, 0, m_fFontAlpha));
	m_pFont->DrawText(2, NULL, m_cStageName, -1, KGRect(145,225,1024,768), DT_NOCLIP , D3DXCOLOR(1, 1, 1, m_fFontAlpha));

	if( m_srtTagGetCat.m_bGetCat )
	{
		m_pSprite->Render(L"DontGiveUp", D3DXVECTOR3((float)m_srtTagGetCat.m_nX, (float)m_srtTagGetCat.m_nY, 0), D3DXCOLOR(1, 1, 1, 1));
	}
	



}


void cStagePart::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	
	SAFE_ONKEYBOARD(m_pRat);
	switch(nChar)
	{
	case VK_RETURN:
		if( m_srtTagGetCat.m_nY == 0 )
		{
			m_srtTagGetCat.m_bKeyCheck = true;
			if( cMain()->m_bEffectOn )
				m_pSound->Play(L"ButtonClick");
		}
		break;
	case VK_SPACE:
		break;
	}
}

void cStagePart::LoadObjectData(const WCHAR* pFileName)
{
	WCHAR					FileNameBuffer[256];
	WCHAR					m_cLine[100];
	WCHAR					m_cString[100];

	KGFindDXSDKMediaFileCch(FileNameBuffer, 256, pFileName);

	FILE*	fp = NULL;

#pragma warning ( disable : 4996)

	fp	= _wfopen(FileNameBuffer, L"rt");

	if(fp == NULL)
	{
		KGOutputDebugString(L"맵 로딩 실패\n");
		return;
	}

	while(!feof(fp))
	{
		fgetws(m_cLine, sizeof(m_cLine), fp);
		swscanf(m_cLine, L"%s", m_cString);

		if(wcscmp(m_cString, L"//") == 0)
			continue;

		if(wcscmp(m_cString, L"[TILE]") == 0)
			DecodeObject(fp);
	}
	fclose(fp);

}


void cStagePart::DecodeObject(FILE* fp)
{
	WCHAR cLine[LARGE_SIZE];
	WCHAR ctemp[LARGE_SIZE];
	int nTileSizeX, nTileSizeY, nTileNumberX, nTileNumberY;

	memset(cLine, 0, sizeof(cLine));
	memset(ctemp, 0, sizeof(ctemp));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d %d %d %d", &nTileSizeX, &nTileSizeY, &nTileNumberX, &nTileNumberY); //스테이지의 갯수를 가져옵니다.

	m_nTileSizeX		= nTileSizeX;
	m_nTileSizeY		= nTileSizeY;
	m_nTileNumberX		= nTileNumberX;
	m_nTileNumberY		= nTileNumberY;


	m_pppZone = new cZone**[nTileNumberX];
	for( int i = 0; i < nTileNumberX; i++ )
	{
		m_pppZone[i] = new cZone*[nTileNumberY];
		for( int j = 0; j < nTileNumberY; j++)
		{
			m_pppZone[i][j] = new cZone(m_pAnimate);
		}
	}

	//std::vector<cZone>vZone(nTileNumberX, cZone(m_pAnimate));
	//std::vector<cZone>vZone(nTileNumberX, new cZone(m_pAnimate));

	//vector<vector<int> > v;*/


	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);//[LAYER] 출력

	//=====================================================
	// 레이어 해석
	//=====================================================
	for( int TileX = 0; TileX < nTileNumberX; TileX++)
	{
		DecodeLayer(TileX, fp);
		//printf("\n");
	}


	//=====================================================
	// 주인공 호출
	//=====================================================
	int nRatPosX, nRatPosY;
	memset(ctemp, 0, sizeof(ctemp));
	fgetws(cLine, sizeof(cLine), fp); //[HERO] 출력

	memset(ctemp, 0, sizeof(ctemp));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d %d", &nRatPosX, &nRatPosY); //타일 어디에 있는지 알아오기.

	m_pRat = new cRat(m_pSound, m_pAnimate, nRatPosX, nRatPosY, m_nTileSizeX, m_nTileSizeY, m_nTileNumberX, m_nTileNumberY);


	for( int i = 0; i < m_nTileNumberX; i++ )
	{
		for( int j = 0; j < m_nTileNumberY; j++ )
		{
			printf("%d  ", m_pppZone[i][j]->m_nKindZone);
		}
		printf("\n");
	}

	memset(ctemp, 0, sizeof(ctemp));
	fgetws(ctemp, sizeof(ctemp), fp);	//[INTERFACE]출력

	memset(ctemp, 0, sizeof(ctemp));
	fgetws(ctemp, sizeof(ctemp), fp);
	swscanf(ctemp, L"%d", &m_nInterFaceCount); //타일 어디에 있는지 알아오기.

	WCHAR					cZoneName[255];
	int						nZoneCount;

	m_ppInterFace = new cInterFace*[m_nInterFaceCount];


	for( int i = 0; i < m_nInterFaceCount; i++ )
	{
		memset(ctemp, 0, sizeof(ctemp));
		fgetws(ctemp, sizeof(ctemp), fp);
		swscanf(ctemp, L"%s %d", cZoneName, &nZoneCount); //타일 어디에 있는지 알아오기.

		m_ppInterFace[i] = new cInterFace(m_pAnimate, m_pZoneDialog,  cZoneName, nZoneCount, cMain()->m_nDialogID);
		cMain()->m_nDialogID ++;
	}

	int					m_nPoSetting = 0;

	for( int i = 0; i < m_nInterFaceCount; i++ )
		m_nPoSetting = m_ppInterFace[i]->OnPositionSetting( m_nInterFaceCount, m_nPoSetting );
	//자리셋팅
}


void cStagePart::DecodeLayer(int nTileX, FILE* fp)
{
	WCHAR cLine[LARGE_SIZE];

	//=====================================================
	// 각 숫자몇개인지 알으는 코드
	//=====================================================
	int nCount = 0;



	memset(cLine, 0, sizeof(cLine));
	fgetws(cLine, sizeof(cLine), fp);

	for( int z = 0; z < LARGE_SIZE; z++ )
	{
		if(cLine[z] == L'/')
			break;

		nCount++;
	}
	//========= 주석을 만날때까지 숫자를 샘.


	//=====================================================
	// 각 숫자 해당 읽음.
	//=====================================================
	int j = 0;
	int sum = 0;
	for( int xx = 0; xx < nCount; xx++ )
	{
		if(cLine[xx] == L' ')	//공백 만나면 생략
			continue;

		switch(cLine[xx])
		{
		case 'A':
			m_pppZone[nTileX][j]->m_nKindZone = GOAL;
			j++;
			break;
		case 'C':
			m_pppZone[nTileX][j]->m_nKindZone = CAT;
			j++;
			break;
		case 'R':
			m_pppZone[nTileX][j]->m_nKindZone = RED;
			j++;
			break;
		case 'O':
			m_pppZone[nTileX][j]->m_nKindZone = ORANGE;
			j++;
			break;
		case 'Y':
			m_pppZone[nTileX][j]->m_nKindZone = YELLOW;
			j++;
			break;
		case 'G':
			m_pppZone[nTileX][j]->m_nKindZone = GREEN;
			j++;
			break;
		case 'B':
			m_pppZone[nTileX][j]->m_nKindZone = BLUE;
			j++;
			break;
		case 'N':
			m_pppZone[nTileX][j]->m_nKindZone = NAVY;
			j++;
			break;
		case 'P':
			m_pppZone[nTileX][j]->m_nKindZone = PURPLE;
			j++;
			break;
		default:
			m_pppZone[nTileX][j]->m_nKindZone = NONE;
			j++;
			break;
		}

	}
}


int cStagePart::GetAttrib( int h_x, int h_y )
{
	//printf("%d\n\n\n", m_pppZone[h_x][h_y]->m_nKindZone);
	return m_pppZone[h_x][h_y]->m_nKindZone;
}


void cStagePart::OnRenderZonePart( int i, int j, int nKindZone )
{
	switch( nKindZone )
	{
	case RED:
		RenderKindZone( L"RedZone", i, j );
		break;
	case ORANGE:
		RenderKindZone( L"OrangeZone", i, j );
		break;
	case YELLOW:
		RenderKindZone( L"YellowZone", i, j );
		break;
	case GREEN:
		RenderKindZone( L"GreenZone", i, j );
		break;
	case BLUE:
		RenderKindZone( L"BlueZone", i, j );
		break;
	case NAVY:
		RenderKindZone( L"NavyZone", i, j );
		break;
	case PURPLE:
		RenderKindZone( L"PurpleZone", i, j );
		break;
	case GOAL:
		RenderKindZone( L"GoalZone", i, j );
		break;
	case CAT:
		RenderKindZone( L"고양이잔다1", i, j );
		break;
	}
}


void cStagePart::OnRenderClickZonePart( int i, int j, int nKindZone )
{
	switch( nKindZone )
	{
	case RED:
		RenderKindZone( L"RedZone1", i, j );
		break;
	case ORANGE:
		RenderKindZone( L"OrangeZone1", i, j );
		break;
	case YELLOW:
		RenderKindZone( L"YellowZone1", i, j );
		break;
	case GREEN:
		RenderKindZone( L"GreenZone1", i, j );
		break;
	case BLUE:
		RenderKindZone( L"BlueZone1", i, j );
		break;
	case NAVY:
		RenderKindZone( L"NavyZone1", i, j );
		break;
	case PURPLE:
		RenderKindZone( L"PurpleZone1", i, j );
		break;
	case GOAL:
		RenderKindZone( L"GoalZone", i, j );
		break;
	case CAT:
		RenderKindZone( L"양이깨어남", i, j );
		break;
	}
}


void cStagePart::RenderKindZone( WCHAR *cZoneName, int i, int j )
{
	//==================================================
	//그림그리기
	//==================================================
	WCHAR m_cZoneName[255];
	wcscpy(m_cZoneName, cZoneName);		//로드할 맵의 경로 복사

	m_pSprite->Render( m_cZoneName, 
		KGRect( (i*m_nTileSizeX) - m_nTileSizeX/2 + m_nTileSizeX/2, 
		(j*m_nTileSizeY) - m_nTileSizeY/2 + m_nTileSizeY/2, 
		(i*m_nTileSizeX) + m_nTileSizeX/2 + m_nTileSizeX/2, 
		(j*m_nTileSizeY) + m_nTileSizeY/2 + m_nTileSizeY/2 ),
		D3DXCOLOR( 1, 1, 1, 1 ) );
}


void cStagePart::ZoneCountSetting( int h_x, int h_y )
{
	for( int i = 0; i < m_nInterFaceCount; i++ )
	{
		if( m_ppInterFace[i]->m_nZoneKind == m_pppZone[h_x][h_y]->m_nKindZone)
		{
			if( m_ppInterFace[i]->m_nZoneCount >= 1 )
			{
				m_ppInterFace[i]->m_nZoneCount--;
				m_ppInterFace[i]->m_pMultiParticle->Entry(L"NumberParticle", D3DXVECTOR3((float)750 ,(float)m_ppInterFace[i]->m_nInterFaceY-15, 0), true, 1);
				//위코드 파티클 출력
			}
		}
	}
}


bool cStagePart::ZoneMoveStop( int h_x, int h_y )
{
	cMapMng* pMapMng = (cMapMng*)cMain()->GetCurrent();


	int GoalCheck = 0;
	for( int i = 0; i < m_nInterFaceCount; i++ )
	{
		if( m_ppInterFace[i]->m_nZoneCount == 0 )
			GoalCheck++;
	}

	switch( m_pppZone[h_x][h_y]->m_nKindZone )
	{
	case CAT:
		if( !m_srtTagGetCat.m_bGetCat )
		{
			printf("사망");
			m_srtTagGetCat.m_bGetCat = true;
			m_srtTagGetCat.m_fCatTime = 0.f;
			if( cMain()->m_bEffectOn )
				m_pSound->Play(L"CatSound");
			break;
		}
	case GOAL:
		if( GoalCheck == m_nInterFaceCount && !m_bChesseBool )
		{
			pMapMng->m_pClearList[m_nStageNumber] = CLEAR;
			pMapMng->OnClearUpdate();
			pMapMng->StageSAve(L"Resource/MapManager/StageClearMng.txt");
			if( cMain()->m_bEffectOn )
				m_pSound->Play(L"ClearSound");
			m_bChesseBool = true;
			m_fCheeseTime = 0.f;
		}
		else
		{
			return false;
		}
	}


	for( int i = 0; i < m_nInterFaceCount; i++ )
	{
		if( m_ppInterFace[i]->m_nZoneKind == m_pppZone[h_x][h_y]->m_nKindZone)
		{
			switch( m_pppZone[h_x][h_y]->m_nKindZone )
			{
			case RED:
				if( m_ppInterFace[i]->m_nZoneCount == 0 )
					return false;
				break;
			case ORANGE:
				if( m_ppInterFace[i]->m_nZoneCount == 0 )
					return false;
				break;
			case YELLOW:
				if( m_ppInterFace[i]->m_nZoneCount == 0 )
					return false;
				break;
			case GREEN:
				if( m_ppInterFace[i]->m_nZoneCount == 0 )
					return false;
				break;
			case BLUE:
				if( m_ppInterFace[i]->m_nZoneCount == 0 )
					return false;
				break;
			case NAVY:
				if( m_ppInterFace[i]->m_nZoneCount == 0 )
					return false;
				break;
			case PURPLE:
				if( m_ppInterFace[i]->m_nZoneCount == 0 )
					return false;
				break;
			}
		}
	}
	return true;
}

int cStagePart::GetCurrentTile( int h_x, int h_y )
{
	int i;
	cMapMng* pMapMng = (cMapMng*)cMain()->GetCurrent();

	switch( m_pppZone[h_x][h_y]->m_nKindZone )
	{
	case CAT:
		i = HERO_CAT;
		break;
	case GOAL:
		i = HERO_ARR;
		break;
	default:
		i = -99;
		break;
	}
	return i;

}