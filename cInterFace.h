#ifndef _CINTERFACE_H
#define _CINTERFACE_H

#include "MyInclude.h"
#include <KGEmotion.h>

using namespace KG;

class cInterFace
{

private:
	KGDialog*				m_pZoneDialog;
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	WCHAR					m_cZoneName[255];
	WCHAR					m_cRenderZoneName[255];

public:
	int						m_nZoneKind;
	int						m_nZoneCount;
	int						m_nOrgZoneCount;

	int						m_nInterFaceY;

	int						m_nPositionSetting;
	int						m_nNumberCheck;

	int						m_nDialogNumber;
	KGRenderMulti*			m_pMultiParticle;

	//값을 더이상 안바꿈. 초기에만 바꿈.


public:
	cInterFace( KGAnimate* pAnimate, KGDialog* pZoneDialog, WCHAR* cZoneName, int nZoneCount, int nNumber );
	~cInterFace();

public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);

public:
	void					OnRenderKindZoneSwitch( int nZoneKind, WCHAR* cZoneName );
	int						OnPositionSetting( int nMapCount, int nInterFaceY );

};

#endif