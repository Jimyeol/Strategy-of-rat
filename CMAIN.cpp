#include "MyInclude.h"

using namespace KG;

IMPLEMENT_MAIN(cmain);

cmain::cmain() : KG::KGEmotion(L"StrategyOfRat", 900, 600)
{
	m_pMain					= this;
	m_nCurrentStage			= -1;
	m_nDialogID				=  0;
	m_bMusicOn				= true;
	m_bEffectOn				= true;

#if defined(NDEBUG)
	SetFullScreenBackBufferWidthAtModeChange(900);
	SetFullScreenBackBufferHeightAtModeChange(600);
	SetOverrideWidth(900);
	SetOverrideHeight(600);
	SetOverrideFullScreen(false);
	SetHandleAltEnter(false);
	SetHandleDefaultHotkeys(false);
	SetShowMsgBoxOnError(true);
	SetShowCursorWhenFullScreen(false);
#endif
}


cmain::~cmain()
{
}

void cmain::Create()
{
	Entry(L"map", new cMapMng);
	Entry(L"selectstage", new cSelectStage);
	Entry(L"logo", new cLogo);
	Entry(L"menu", new cMenu);
}

void cmain::Init()
{
	Trans(L"logo");
}
