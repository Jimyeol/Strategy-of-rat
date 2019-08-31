#ifndef _CMAIN_H
#define _CMAIN_H

#include <KGEmotion.h>
#if defined(DEBUG)  ||  defined(_DEBUG)
#pragma comment(lib, "KGEmotionD.lib")
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#else
#pragma comment(lib, "KGEmotion.lib")
#endif

#include "MyInclude.h"

class cmain : public KG::KGEmotion
{
public:
	static cmain*			m_pMain;

public:
	int						m_nCurrentStage;		//현재스테이지
	int						m_nDialogID;
	bool					m_bMusicOn;
	bool					m_bEffectOn;
	

public:
	cmain();
	~cmain();


public:
	void			Create();
	void			Init();

};

inline cmain*      cMain()
{
	return cmain::m_pMain;
}
#endif