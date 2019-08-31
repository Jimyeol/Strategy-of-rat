#include "cMapMng.h"



cMapMng::cMapMng()
{
	m_pSound				= NULL;

	m_pSprite				= NULL;
	m_pAnimate				= NULL;
	m_pFont					= NULL;
	m_pZoneDialog			= NULL;
	m_pDialog				= NULL;
	m_pInterFace			= NULL;
	m_pPause				= NULL;
	m_ppZoneDialog			= NULL;
	m_tppClearXY			= NULL;
	m_pCursor				= NULL;

	//======================================
	//Clear관리
	//======================================
	m_pClearDlg				= NULL;
	m_pClearList			= NULL;


	//======================================
	//Stage관리
	//======================================
	m_ppStagePart			= NULL;
	m_nMapListCount			= 0;

	m_bSelectStage			= true;
	m_bPause				= false;

}


cMapMng::~cMapMng()
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pZoneDialog);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pInterFace);
	SAFE_DELETE(m_pPause);
	SAFE_DELETE(m_pCursor);

	if(m_ppZoneDialog != NULL)
	{
		for( int i = 0; i < m_nMapListCount; i++ )
		{
			SAFE_DELETE(m_ppZoneDialog[i]);
		}
		SAFE_DELETE(m_ppZoneDialog);
	}

	if(m_ppStagePart != NULL)
	{
		for( int i = 0; i < m_nMapListCount; i++ )
		{
			SAFE_DELETE(m_ppStagePart[i]);
		}
		SAFE_DELETE(m_ppStagePart);
	}

	SAFE_DELETE_ARRAY(m_pClearList);

	SAFE_DELETE(m_pClearDlg);

	SAFE_DELETE_ARRAY(m_tppClearXY);

	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}

}


void cMapMng::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pZoneDialog);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pInterFace);
	SAFE_DELETE(m_pPause);
	SAFE_DELETE(m_pCursor);

	if(m_ppZoneDialog != NULL)
	{
		for( int i = 0; i < m_nMapListCount; i++ )
		{
			SAFE_DELETE(m_ppZoneDialog[i]);
		}
		SAFE_DELETE(m_ppZoneDialog);
	}

	if(m_ppStagePart != NULL)
	{
		for( int i = 0; i < m_nMapListCount; i++ )
		{
			SAFE_DELETE(m_ppStagePart[i]);
		}
		SAFE_DELETE(m_ppStagePart);
	}

	SAFE_DELETE_ARRAY(m_pClearList);

	SAFE_DELETE(m_pClearDlg);

	SAFE_DELETE_ARRAY(m_tppClearXY);

	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
}


HRESULT cMapMng::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"Resource/Image/TE/example.te");
		m_pSprite->Entry(L"Resource/Image/TE/Object.te");
		m_pSprite->Entry(L"Resource/Image/TE/InterFace.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Pause.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Pause1.Te");
		m_pSprite->Entry(L"Resource/Image/TE/ZoneType.Te");
		m_pSprite->Entry(L"Resource/Image/TE/InterfaceZoneType.Te");
		m_pSprite->Entry(L"Resource/Image/TE/StageChoice.Te");
		m_pSprite->Entry(L"Resource/Image/TE/DonGiveUp.Te");
		m_pSprite->Entry(L"Resource/Image/TE/NumberParticle.Te");
		m_pSprite->Entry(L"Resource/Image/TE/InterFace/InterFacePattern00.Te");
		m_pSprite->Entry(L"Resource/Image/TE/InterFace/InterFacePattern01.Te");
		m_pSprite->Entry(L"Resource/Image/TE/InterFace/InterFacePattern02.Te");
		m_pSprite->Entry(L"Resource/Image/TE/InterFace/InterFacePattern03.Te");
		m_pSprite->Entry(L"Resource/Image/TE/InterFace/InterFacePattern04.Te");
		m_pSprite->Entry(L"Resource/Image/TE/InterFace/InterFacePattern05.Te");
		m_pSprite->Entry(L"Resource/Image/TE/InterFace/InterFacePattern06.Te");
		m_pSprite->Entry(L"Resource/Image/TE/InterFace/InterFacePattern07.Te");
		m_pSprite->Entry(L"Resource/Image/TE/InterFace/InterFacePattern08.Te");
		m_pSprite->Entry(L"Resource/Image/TE/InterFace/InterFaceNumber.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Rat/RatMotion1.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Rat/RatMotion2.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Cat/CatSleep2.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Cat/CatSleep1.Te");
		m_pSprite->Entry(L"Resource/Image/TE/StageSelect/StageSelectBack.Te");
		m_pSprite->Entry(L"Resource/Image/TE/StageSelect/MoveBack.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Rat/HiRat1.Te");
		m_pSprite->Entry(L"Resource/Image/TE/Rat/HiRat2.Te");
		m_pSprite->Entry(L"Resource/Image/TE/ETC.Te");
	}

	if(m_pAnimate == NULL)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
		m_pAnimate->Entry(L"Resource/Image/TA/Hero.Ta");
		m_pAnimate->Entry(L"Resource/Image/TA/NumberParticle.Ta");
		m_pAnimate->Entry(L"Resource/Image/TA/InterFacePattern.Ta");
		m_pAnimate->Entry(L"Resource/Image/TA/RatMotion.Ta");
		m_pAnimate->Entry(L"Resource/Image/TA/HiParticles.Ta");
	}
	if( m_pSound == NULL )
	{
		m_pSound			= new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"ButtonClick", L"Resource/Sound/ButtonClick.wav");
		m_pSound->Entry(L"BackMusic", L"Resource/Sound/BackMusic.wav");
		m_pSound->Entry(L"CatSound", L"Resource/Sound/CatSound.wav");
		m_pSound->Entry(L"ClearSound", L"Resource/Sound/ClearSound.wav");
		if( cMain()->m_bMusicOn )
		{
			m_pSound->Play(L"BackMusic");
		}
	}
	if( m_pDialog == NULL )
	{
		m_pDialog			= new KGDialog(m_pSprite, NULL, this);
		m_pDialog->AddNumber(100, L"InterFaceNumber",D3DXVECTOR3(100,0,0), 10);
		m_pDialog->AddNumber(101, L"InterFaceNumber", D3DXVECTOR3(0, 0, 0 ), 10 );
	}

	if( m_pInterFace == NULL )
	{
		m_pInterFace			= new KGDialog(m_pAnimate, NULL, this);
		m_pInterFace->AddAniButton(103, L"InterFacePattern", L"InterFacePattern", L"InterFacePattern", L"InterFacePattern", KGRect(650, 0, 900, 600));
	}

	if( m_pPause == NULL )
	{
		m_pPause				= new KGDialog(m_pSprite, NULL, this);
		m_pPause->AddButton(BT_PAUSENO, L"GamePauseNoDefault", L"GamePauseNoClick", L"GamePauseNoOver", L"GamePauseNo", D3DXVECTOR3(450, 170, 0));
		m_pPause->AddButton(BT_RESTART, L"GameRestartDefault", L"GameRestartClick", L"GameRestartOver", L"GameRestart", D3DXVECTOR3(450, 270, 0));
		m_pPause->AddButton(BT_GOTOMENU, L"GoToMenuDefault", L"GoToMenuClick", L"GoToMenuOver", L"GoToMenu", D3DXVECTOR3(450, 370, 0));
		m_pPause->AddButton(BT_SAVEEXIT, L"StageSaveExitDefault", L"StageSaveExitClick", L"StageSaveExitDefault", L"StageSaveExit", D3DXVECTOR3(450, 470, 0));

		//m_pPause->AddButton(BT_SAVEEXIT, L"GoToMenuDefault", L"GoToMenuClick", L"GoToMenuOver", L"GoToMenu", D3DXVECTOR3(450, 470, 0));


	}

	if( m_pZoneDialog == NULL )
	{
		m_pZoneDialog			= new KGDialog(m_pSprite, NULL, this);
	}

	if(m_ppStagePart == NULL)
	{
		LoadStageData(L"Resource/MapManager/StageManager.txt");
		LoadStageSaveData(L"Resource/MapManager/StageClearMng.txt");
	}
	if(m_pCursor == NULL)
	{
		m_pCursor			= new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,900,600),L"마우스당첨", L"마우스당첨",L"마우스당첨");
	}

	m_vBackMove1			= D3DXVECTOR3(0, 0, 0);
	m_vBackMove2			= D3DXVECTOR3(0, -590, 0);
	return S_OK;
}


HRESULT cMapMng::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	SAFE_ONRESETDEVICE(m_pInterFace);
	SAFE_ONRESETDEVICE(m_pPause);
	SAFE_ONRESETDEVICE(m_pZoneDialog);
	SAFE_ONRESETDEVICE(m_pClearDlg);

	return S_OK;
}


void cMapMng::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
	SAFE_ONLOSTDEVICE(m_pInterFace);
	SAFE_ONLOSTDEVICE(m_pPause);
	SAFE_ONLOSTDEVICE(m_pZoneDialog);
	SAFE_ONLOSTDEVICE(m_pClearDlg);
}


void cMapMng::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if( !m_bSelectStage )
	{
		if(m_bPause)
		{
			SAFE_ONFRAMEMOVE(m_pPause);
		}
		SAFE_ONFRAMEMOVE(m_pInterFace);
		SAFE_ONFRAMEMOVE(m_pZoneDialog);
		SAFE_ONFRAMEMOVE(m_ppStagePart[cMain()->m_nCurrentStage]);

	}
	else
	{
		SAFE_ONFRAMEMOVE(m_pDialog);
		SAFE_ONFRAMEMOVE(m_pClearDlg);
		m_vBackMove1.y++;
		m_vBackMove2.y++;
		if( m_vBackMove1.y == 600)
		{
			m_vBackMove1.y = -590;
		}
		if( m_vBackMove2.y == 600)
		{
			m_vBackMove2.y = -590;
		}
	}

}


void cMapMng::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT hr;
	V(pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255,255,255,255), 1.0f, 0));
	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		if( !m_bSelectStage )
		{
			SAFE_ONFRAMERENDER(m_pInterFace);

			SAFE_ONFRAMERENDER(m_ppStagePart[cMain()->m_nCurrentStage]);
			SAFE_ONFRAMERENDER(m_pZoneDialog);
			if(m_bPause)
			{
				m_pSprite->Render(L"Pause", D3DXVECTOR3(450, 300, 0), D3DXCOLOR(1,1,1,1));
				SAFE_ONFRAMERENDER(m_pPause);
			}
		}
		else
		{
			m_pSprite->Render(L"백움직임", m_vBackMove1, D3DXCOLOR(1, 1, 1, 1));
			m_pSprite->Render(L"백움직임", m_vBackMove2, D3DXCOLOR(1, 1, 1, 1));
			SAFE_ONFRAMERENDER(m_pDialog);
			SAFE_ONFRAMERENDER(m_pClearDlg);
			m_pSprite->Render(L"배경스", D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 1, 1, 1));
		}
		SAFE_ONFRAMERENDER(m_pCursor);

		V(pd3dDevice->EndScene());
	}
}


void cMapMng::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					  bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	SAFE_ONMOUSE(m_pCursor);

	if( m_bSelectStage )
	{
		SAFE_ONMOUSE(m_pDialog);
		SAFE_ONMOUSE(m_pClearDlg);

	}
	else
	{
		SAFE_ONMOUSE(m_pInterFace);
		SAFE_ONMOUSE(m_pPause);
		SAFE_ONMOUSE(m_pZoneDialog);
	}



	m_pDialog->GetNumber(100)->SetNumber(yPos);
	m_pDialog->GetNumber(101)->SetNumber(xPos);


}


void cMapMng::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	if( !m_bSelectStage )
		SAFE_ONKEYBOARD(m_ppStagePart[cMain()->m_nCurrentStage]);

	switch(nChar)
	{
	case VK_SPACE:
		break;
	}
}


LRESULT cMapMng::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	if( m_bSelectStage )
	{
		SAFE_ONMSGPROC(m_pDialog);
		SAFE_ONMSGPROC(m_pClearDlg);
	}
	else
	{
		SAFE_ONMSGPROC(m_pInterFace);
		SAFE_ONMSGPROC(m_pPause);
		SAFE_ONMSGPROC(m_pZoneDialog);
	}


	return uMsg;
}


void cMapMng::OnEvent(UINT id, int xPos, int yPos)
{
	switch(id)
	{
	case 103:
		if( !m_bPause )
		{
			m_bPause = true;
			if( cMain()->m_bEffectOn )
				m_pSound->Play(L"ButtonClick");
		}
		break;
	case BT_GOTOMENU:
		if( m_bPause )
			m_bPause = false;
		m_ppStagePart[cMain()->m_nCurrentStage]->m_pRat->OnRatReset();
		m_bSelectStage	= true;
		cMain()->m_nCurrentStage = -1;
		if( cMain()->m_bEffectOn )
			m_pSound->Play(L"ButtonClick");
		break;
	case BT_RESTART:
		if( m_bPause )
		{
			m_bPause = HeroPositionReset();
			m_ppStagePart[cMain()->m_nCurrentStage]->m_fFontAlpha = 1.f;
		}
		if( cMain()->m_bEffectOn )
			m_pSound->Play(L"ButtonClick");
		break;
	case BT_PAUSENO:
		if( m_bPause )
		{
			m_bPause = false;
			if( cMain()->m_bEffectOn )
				m_pSound->Play(L"ButtonClick");
		}
		break;
	case BT_SAVEEXIT:
		cMain()->CloseWindow();
		break;
	}
	OnSwitchSelectStage(id, m_nMapListCount);
}


void cMapMng::LoadStageData(const WCHAR* pFileName)
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
		printf("맵로딩실패!!\n");
		return;
	}

	while(!feof(fp))
	{
		fgetws(m_cLine, sizeof(m_cLine), fp);
		swscanf(m_cLine, L"%s", m_cString);

		if(wcscmp(m_cString, L"//") == 0)
			continue;

		if(wcscmp(m_cString, L"[MAPLIST]") == 0)
			DecodeStage(fp);
	}
	fclose(fp);
}


void cMapMng::DecodeStage(FILE* fp)
{
	WCHAR cLine[LARGE_SIZE];
	WCHAR ctemp[LARGE_SIZE];
	WCHAR cStageRoot[LARGE_SIZE];
	WCHAR cStageName[LARGE_SIZE];

	int nStageNumber		= 0;
	int	nMapListCount		= 0;

	memset(cLine, 0, sizeof(cLine));
	memset(ctemp, 0, sizeof(ctemp));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d", &nMapListCount); //스테이지의 갯수를 가져옵니다.

	m_nMapListCount = nMapListCount;

	m_ppStagePart = new cStagePart*[nMapListCount];	//스테이지을 동적할당 합니다.
	m_ppZoneDialog = new KGDialog*[nMapListCount];

	for( int i = 0 ; i < nMapListCount; i++ )
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf(cLine, L"%s %s", cStageRoot, cStageName); //Stage Number StageName 읽음

		m_ppZoneDialog[i] = new KGDialog(m_pSprite, NULL, this);

		m_ppStagePart[i] = new cStagePart(m_pSound, m_pAnimate, m_ppZoneDialog[i], i, cStageRoot, cStageName);
	}


	//==========================================================
	//스테이지 자동 셋팅
	//==========================================================
	memset(ctemp, 0, sizeof(ctemp));
	fgetws(ctemp, sizeof(ctemp), fp);

	int nStageTileX, nStageTileY, nTileInterVal, nTileInterVal2;
	WCHAR TRASH[255];

	memset(ctemp, 0, sizeof(ctemp));
	fgetws(ctemp, sizeof(ctemp), fp);
	swscanf(ctemp, L"%d %d %s %d %d", &nStageTileX, &nStageTileY, TRASH, &nTileInterVal, &nTileInterVal2); //


	//==========================================================
	//스테이지 정리
	//==========================================================
	int nIDGive = 0;	//ID값 주기 위한것.
	for( int j = 0; j < nStageTileX; j++ )
	{
		for( int k = 0; k < nStageTileY; k++ )
		{
			m_pDialog->AddButton(nIDGive, L"StageChoice", L"StageChoice_Click", L"StageChoice_Over", L"StageChoice", 
				D3DXVECTOR3((float)k*nTileInterVal2+nTileInterVal,(float)j*nTileInterVal2+nTileInterVal,0));
			if( nIDGive <= 8 )
			{
				m_pDialog->AddNumber(nIDGive, L"StageNum_", D3DXVECTOR3((float)k*nTileInterVal2+nTileInterVal,
					(float)j*nTileInterVal2+nTileInterVal,0));
				m_pDialog->GetNumber(nIDGive)->SetNumber(nIDGive+1);
			}
			else	//스테이지 넘버 숫자가 10을 넘어가면 다시 위치 조정.
			{
				m_pDialog->AddNumber(nIDGive, L"StageNum_", D3DXVECTOR3((float)k*nTileInterVal2+nTileInterVal - 25,
					(float)j*nTileInterVal2+nTileInterVal,0));
				m_pDialog->GetNumber(nIDGive)->SetNumber(nIDGive+1);
			}
			nIDGive++;
		}
	}

	m_nTileInterVal		= nTileInterVal;
	m_nTileInterVal2	= nTileInterVal2;
	m_nStageTileX		= nStageTileX;
	m_nStageTileY		= nStageTileY;



}


void cMapMng::LoadStageSaveData(const WCHAR* pFileName)
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
		printf("맵로딩실패!!\n");
		return;
	}

	while(!feof(fp))
	{
		fgetws(m_cLine, sizeof(m_cLine), fp);
		swscanf(m_cLine, L"%s", m_cString);

		if(wcscmp(m_cString, L"//") == 0)
			continue;

		if(wcscmp(m_cString, L"[STAGELIST]") == 0)
			DecodeStageSave(fp);
	}
	fclose(fp);
}


void cMapMng::DecodeStageSave(FILE* fp)
{
	WCHAR cLine[LARGE_SIZE];
	WCHAR cCheckClear[LARGE_SIZE];

	m_tppClearXY = new CLEARXY_TAG*[m_nMapListCount];	//클리어 XY좌표 얻어오는거 동적할당

	//==========================================================
	//스테이지가 클리어 되어있는지?
	//==========================================================

	int nStageClearNumber = 0;
	int checkClear = 0;

	m_pClearList = new int[m_nMapListCount];
	m_pClearDlg = new KGDialog(m_pSprite, NULL, this);

	for( int i = 0 ; i < m_nMapListCount; i++ )
	{
		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf(cLine, L"%d %s", &nStageClearNumber, cCheckClear); //Stage Number StageName 읽음

		if(wcsstr(cCheckClear, L"yes"))
			checkClear = CLEAR;
		else if(wcsstr(cCheckClear, L"no"))
			checkClear = NOCLEAR;

		m_pClearList[i] = checkClear;

	}

	OnClearUpdate();

}


void cMapMng::OnSwitchSelectStage(UINT id, int nMapListCount)
{
	//==========================================================
	//Switch문 유동적으로 구현한 함수
	//==========================================================
	for( int i = 0; i < nMapListCount; i++ )
	{
		if( id == 1*i)
		{
			cMain()->m_nCurrentStage = 1*i;
			m_bSelectStage = false;
			if( cMain()->m_bEffectOn )
				m_pSound->Play(L"ButtonClick");
			return;
		}
	}
}


bool cMapMng::HeroPositionReset()
{
	if( cMain()->m_nCurrentStage == -1 )
		return true;

	m_ppStagePart[cMain()->m_nCurrentStage]->m_pRat->OnRatReset();

	for( int i = 0; i < m_ppStagePart[cMain()->m_nCurrentStage]->m_nInterFaceCount; i++ )
		m_ppStagePart[cMain()->m_nCurrentStage]->m_ppInterFace[i]->m_nZoneCount = 
		m_ppStagePart[cMain()->m_nCurrentStage]->m_ppInterFace[i]->m_nOrgZoneCount;

	return false;


}


void cMapMng::OnClearUpdate()
{
	int nIDCount = 0;
	for( int j = 0; j < m_nStageTileX; j++ )
	{
		for( int k = 0; k < m_nStageTileY; k++ )
		{
			if( m_pClearList[nIDCount] != CLEAR )
			{
				nIDCount ++;
				continue;
			}

			m_pClearDlg->SetSprite(L"StageClear", D3DXVECTOR3((float)k*m_nTileInterVal2+m_nTileInterVal, 
				(float)j*m_nTileInterVal2+m_nTileInterVal+20, 0), D3DXCOLOR(1,1,1,1));
			//스테이지 클리어가 됬는지? 업데이트 하는 함수
			nIDCount ++;

		}
	}
}


void cMapMng::StageSAve(const WCHAR* pFileName)
{
	WCHAR					FileNameBuffer[256];

	KGFindDXSDKMediaFileCch(FileNameBuffer, 256, pFileName);

	FILE*	fp = NULL;

#pragma warning ( disable : 4996)

	fp	= _wfopen(FileNameBuffer, L"wt");

	if(fp == NULL)
	{
		KGOutputDebugString(L"클리어 실패\n");
		printf("클리어실패!!\n");
		return;
	}


	fwprintf(fp, L"[STAGELIST]\n");

	for( int i = 0; i < m_nMapListCount; i++ )
	{
		if( i+1 == m_nMapListCount)
		{
			if( m_pClearList[i] == CLEAR)
				fwprintf(fp, L"%d yes", i+1);
			else
				fwprintf(fp, L"%d no", i+1);;
		}
		else
		{
			if( m_pClearList[i] == CLEAR)
				fwprintf(fp, L"%d yes\n", i+1);
			else
				fwprintf(fp, L"%d no\n", i+1);
		}
	}

	fclose(fp);
}


void LoadData(const WCHAR* pFileName)
{
	WCHAR					FileNameBuffer[256];
	WCHAR					m_cLine[100];
	WCHAR					ctemp[100];
	WCHAR					cLine[100];
	WCHAR					m_cString[100];
	FILE*	fp = NULL;

#pragma warning ( disable : 4996)

	fp	= _wfopen(FileNameBuffer, L"rt");

	while(!feof(fp))
	{
		fgetws(m_cLine, sizeof(m_cLine), fp);
		swscanf(m_cLine, L"%s", m_cString);

		if(wcscmp(m_cString, L"//") == 0)
			continue;

		if(wcscmp(m_cString, L"[List]") == 0)
		{ 
			WCHAR cStageRoot[LARGE_SIZE];

			int nNumber		= 0;
			int nListCount		= 0;

			memset(cLine, 0, sizeof(cLine));
			memset(ctemp, 0, sizeof(ctemp));
			fgetws(cLine, sizeof(cLine), fp);
			swscanf(cLine, L"%d", &nNumber); 

			for( int i = 0 ; i < nNumber; i++ )
			{
				memset(cLine, 0, sizeof(cLine));
				fgetws(cLine, sizeof(cLine), fp);
				swscanf(cLine, L"%s %d", cStageRoot, nListCount); //Stage Number StageName 읽음
			}
		}
	}
	fclose(fp);
}