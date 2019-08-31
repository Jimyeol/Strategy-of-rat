#include "cInterFace.h"
#include "CMAIN.h"

cInterFace::cInterFace( KGAnimate* pAnimate, KGDialog* pZoneDialog, WCHAR* cZoneName, int nZoneCount, int nNumber )
{

	m_pMultiParticle		= NULL;
	m_pSprite				= pAnimate->GetSprite();
	m_pAnimate				= pAnimate;
	m_pZoneDialog			= pZoneDialog;
	m_nInterFaceY			= 0;
	m_nPositionSetting		= 0;
	m_nDialogNumber			= nNumber;

	wcscpy(m_cZoneName, cZoneName);		//맵의 이름
	m_nZoneCount			= nZoneCount;
	m_nOrgZoneCount			= nZoneCount;

	m_pMultiParticle		= new KGRenderMulti(m_pAnimate);

	//=====================================================
	//값 한방에 찾는거
	//=====================================================
	WCHAR ColorName[MAX_COLOR][10]	= {L"RED", L"ORANGE", L"YELLOW", L"GREEN", L"BLUE", L"NAVY", L"PURPLE"};
	WCHAR ColorRender[MAX_COLOR][20] = {L"RedZoneI", L"OrangeZoneI", L"YellowZoneI", L"GreenZoneI", L"BlueZoneI", L"NavyZoneI",
		L"PurpleZoneI" };

	for( int i = 0; i < MAX_COLOR; i++ )
	{
		if(wcsstr(m_cZoneName, ColorName[i]))
		{
			m_nZoneKind = i;
			wcscpy(m_cRenderZoneName, ColorRender[i]);
			break;
		}
	}
}


cInterFace::~cInterFace()
{
	SAFE_DELETE(m_pMultiParticle);
}


void cInterFace::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	m_pZoneDialog->GetNumber(m_nDialogNumber)->SetNumber(m_nZoneCount);
	SAFE_ONFRAMEMOVE(m_pZoneDialog);

}


void cInterFace::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	OnRenderKindZoneSwitch(m_nZoneKind, m_cZoneName);
	SAFE_ONFRAMERENDER(m_pZoneDialog);
	SAFE_ONFRAMERENDER(m_pMultiParticle);


}


void cInterFace::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
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


void cInterFace::OnRenderKindZoneSwitch( int nZoneKind, WCHAR* cZoneName )
{
	WCHAR OncZoneName[255];

	wcscpy(OncZoneName, cZoneName);

	for( int i = 0; i < MAX_COLOR; i++ )
	{
		if( nZoneKind == i )
		{
			// 오른쪽 인터페이스에 존 출력
			m_pSprite->Render(m_cRenderZoneName, D3DXVECTOR3(770.f, (float)m_nInterFaceY, 0), D3DXCOLOR(1,1,1,1));
		}
	}
}


int cInterFace::OnPositionSetting( int nMapCount, int nInterFaceY )
{
	//자리 셋팅
	m_nInterFaceY = (SCREEN_HEIGHT / (nMapCount+1)) + nInterFaceY;
	m_pZoneDialog->AddNumber(m_nDialogNumber, L"InterFaceNumber_", D3DXVECTOR3((float)770 ,(float)m_nInterFaceY, 0));
	//오른쪽인터페이스 숫자임 ㅇㅋ?
	return m_nInterFaceY;

}