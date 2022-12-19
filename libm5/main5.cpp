#include <time.h>
#include "global.h"
#include "../libfolder/cFolder.h"
#include "../lib5/resource.h"

std::string g_ScriptPath, g_ScenePath, g_MediaPath, g_DLC, g_WdfPath, g_MusicPath;
int nScreenWidth, nScreenHeight, g_StateType, g_xMouse, g_yMouse;
static int g_StateTypeOld;
int g_FPS = 60, g_640 = 640, g_480 = 480, g_320 = 320, g_240 = 240, g_360 = 360;
CMainState* g_pMainState;
cCharacter* g_pCharacter;
cObj* g_pHeroObj;
HBRUSH  g_redbrush,  g_blackbrush,  g_whitebrush, g_bluebrush;
HPEN  g_WhitePen, g_BWhitePen;

BOOL g_bFillScreen;
HDC g_DC,  g_DC2, g_ShowDC;
HBITMAP g_MemBitmap;
LPDIRECTSOUND8	 g_pDirectSound = 0;
BITMAPINFO * g_pBmpinfo;
HWND  g_hWnd;
HINSTANCE g_hInst;
#if defined(ccc_date)
std::string g_strExpandPath, g_strPKPath, g_strNewBabyPath,g_strFriendPath, g_strSavePath, g_strCommonPath;
sAddPoint g_addPointAtk, g_addPointMag, g_addPointSpd,  g_addPointDef;
int g_fntSize = 16;
#endif

std::mutex renderMutex;
std::thread renderThread;
std::condition_variable renderCondition;
static cWindSoul* s_windsoul = nullptr;
static void renderWindsoul() {
	while (true) {
		std::unique_lock<std::mutex> lock(renderMutex);
		while (s_windsoul == nullptr) renderCondition.wait(lock);
		s_windsoul->clear();
		s_windsoul->blit();
		s_windsoul = nullptr;
	}
}


static auto app = cApp::getInstance();
void SetFullScreen(BOOL bFill) { 
	app->switchScreen(); 
	g_pMainState->m_Channel.m_NeedShow = g_bFillScreen || !cGame::getInstance()->isChatShown();
}

void Init()
{
	g_hWnd = app->getHwnd();
	app->initBmpInfo();
	g_pBmpinfo = app->getBmpInfo();
	//////////////////////////////////////////////////////////////////////////
	srand((unsigned int)time(0));
	//////////////////////////////////////////////////////////////////////////
	static CMainState MainState;
	static cFightState FightState;
	static cEndState EndState;
	static cMenuState MenuState;
	g_pMainState = &MainState;
	g_pMainState->m_pEndState = &EndState;
	g_pMainState->m_pMenuState = &MenuState;
	g_ShowDC = GetDC(g_hWnd);
	g_DC = CreateCompatibleDC(g_ShowDC);
	g_DC2 = CreateCompatibleDC(g_ShowDC);
	HPEN  oldpen = (HPEN)SelectObject(g_DC2, g_WhitePen);
	COLORREF oldcolor = SetTextColor(g_DC2, RGB(255, 255, 255));
	//////////////////////////////////////////////////////////////////////////
	g_WhitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	g_BWhitePen = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));
	//设置文本的混合模式
	SetBkMode(g_DC2, TRANSPARENT);
	//SetBkColor(g_DC2, RGB(8, 0, 0));
	//////////////////////////////////////////////////////////////////////////
	g_MemBitmap = CreateCompatibleBitmap(g_ShowDC, g_640, g_480);
	HBITMAP oldmap = (HBITMAP)SelectObject(g_DC, g_MemBitmap);
	//////////////////////////////////////////////////////////////////////////
	g_pMainState->m_pFightState = &FightState;
	g_pMainState->m_SkillManager.m_pFightState = &FightState;
	//////////////////////////////////////////////////////////////////////////
	int addtime = 1000 / g_FPS;
	//////////////////////////////////////////////////////////////////////////
	SetBkMode(g_DC, TRANSPARENT);//设置文本的混合模式
}

void firstMainState()
{
	g_pMainState->m_Tags.Add("空格键");
	g_pMainState->m_Channel.AddNewString("空格键");
}

void spaceTest()
{
	g_pMainState->m_Instructions.OnOff();
//	g_pCharacter->m_PCData.LeveUp(100, false, false);
// 	g_pCharacter->m_PCData.AddExp(1000000000);
// 	g_pCharacter->AddMoney(1000000000);
// 	sJob job;
// 	job.m_pTask = &g_pMainState->m_ZhuXian;
// 	job.m_Title = "剧情";
// 	job.m_Context = "去战神山找蚩尤#R(BOSS战斗)#R"; // 不能换行
// 	g_pMainState->m_Job.AddaJob(job);
// 	g_pMainState->m_ZhuXian.SetChapter(9);
// 	g_pMainState->m_TriggerObj.AddTask("蚩尤", "战神山", &g_pMainState->m_ZhuXian, 100);
 	return;
	if (g_StateType == STATE_FIGHT)
	{
		g_pMainState->m_pFightState->SuccessFight();
		return;
	}
//	return;
	// 拜师
	g_pMainState->m_ZhuXian.SetChapter(0);
	g_pMainState->m_ZhuXian.Process(23);
	return;
	// 抓鬼
	g_pMainState->m_ZhuXian.SetChapter(2);
	g_pMainState->m_ZhuXian.Process(28);
	return;
	// 门派闯关
	g_pMainState->m_ZhuXian.SetChapter(7);
	g_pMainState->m_ZhuXian.Process(26);
	return;
	// 神秘刺客
	g_pMainState->m_TaskFB.Start(3);
	g_pMainState->m_TaskFB.Process(-13);
	g_pMainState->m_TaskFB.Process(15);
	return;
	// 燕子大雁塔
	g_pMainState->m_ZhuXian.SetChapter(0);
	g_pMainState->m_ZhuXian.Process0(34);
}

bool firstMain = true;
bool Frame()
{
	switch (g_StateType)
	{
	case STATE_MAIN:
		g_pMainState->Frame();
		if (firstMain)
		{
			firstMain = false;
			firstMainState();
		}
		break;
	case STATE_FIGHT:
		g_pMainState->m_pFightState->Frame();
		break;
	case STATE_MENU:
		g_pMainState->m_pMenuState->Frame();
		break;
	case STATE_GAMEOVER:
		g_pMainState->m_pEndState->Frame();
		break;
// 	default:
// 		PostQuitMessage(1);
// 		break;
	}
	if (g_StateType == g_StateTypeOld)
	{
		return false;
	}
	g_StateTypeOld = g_StateType;
	return true;
}

LRESULT CALLBACK  WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		if (g_StateType == STATE_MENU)
		{
			break;
		}
#if !defined(ccc_date)
		g_pMainState->m_InterfaceSystem.OnOff(TRUE);
#else
		g_pMainState->m_InterFaceConfig.OnOff();
#endif
		return TRUE;
	case WM_DESTROY:
		g_StateType = STATE_EXT;
		// PostQuitMessage(0);
		// quick_exit(0);
		break;
	case WM_MOVE:
		if (hWnd == app->getHwnd())
		{
			app->resize();
		}
		break;
	case WM_KEYUP:
		if (wParam == VK_SPACE)
		{
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int PASCAL WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
#ifdef TESTDEBU
	g_MediaPath = "..\\..\\Media\\";
#else
	g_MediaPath = "media.5/";
#endif
	std::string g_strRoot = "media.date/";

	srand((uint)&hInstance);
	//////////////////////////////////////////////////////////////////////////


	auto game = cGame::getInstance();
#if !defined(ccc_date)
	game->load(g_MediaPath, "config.exe", "config");
#else
	game->load(g_strRoot, "config.exe", "config");
#endif
	g_640 = game->getw();
	g_480 = game->geth();
	g_320 = g_640 / 2;
	g_240 = g_480 / 2;
	if (!game->isChatShown()) {
		g_360 = 0;
	}
	auto eiter = game->isIter();
	auto eui = game->getui();

	//////////////////////////////////////////////////////////////////////////
#if !defined(ccc_date)
	int icon = IDI_ICON1;
#else
	int icon = IDI_ICON2;
#endif
	auto class_proc = app->initClass(hInstance, "狼总最帅", icon);
	class_proc.lpfnWndProc = WindowProc;
	if (!RegisterClass(&class_proc)) {
		return 0;
	}
	app->setSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), g_640, g_480, g_360);
	unsigned long long style = game->isEdge() ? (WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX) : WS_POPUP;
	if (!app->init(hInstance, class_proc.lpszClassName, style)) {
		return 0;
	}
	app->start();

#if !defined(ccc_date)
	g_ScenePath = g_MediaPath + "scene/";//地图的路径
	g_ScriptPath = g_MediaPath + "script/1/"; //角色脚本的路径
	g_WdfPath = g_MediaPath + "wdfs/";
	g_MusicPath = g_MediaPath + "music/";
#else	
	
	g_strPKPath = g_strRoot + "擂台/";
	g_MediaPath = g_strRoot + "data/";
	g_strCommonPath = g_MediaPath + "common/";
	g_strFriendPath = g_strRoot + "队友/";
	g_strSavePath = g_strRoot + "存档/";
	g_strExpandPath = g_strRoot + "拓展/";
	g_strNewBabyPath = g_strExpandPath + "newbb/";
	g_ScenePath = g_MediaPath + "scene/";
	g_WdfPath = g_strRoot + "wdfs/";
	g_MusicPath = g_strRoot + "music/";

	g_addPointAtk.Set(5, 0, 0, 0, 0);
	g_addPointMag.Set(0, 0, 5, 0, 0);
	g_addPointDef.Set(0, 5, 0, 0, 0);
	g_addPointSpd.Set(0, 3, 0, 0, 2);
	for (auto name : cc::efolder(g_strNewBabyPath, true, 0))
	{
		name.pop_back();
		name.pop_back();
		name.pop_back();
		name.pop_back();
		int i = atoi(name.c_str());
		if (i >= 0 && i <= 162)
		{
			MyTest::getInstance()->newBabys.insert(i);
		}
	}
	for (auto name : cc::efolder(g_strFriendPath, true, 0))
	{
		name.pop_back();
		name.pop_back();
		name.pop_back();
		name.pop_back();
		if (name == "队长")
		{
			continue;
		}
		MyTest::getInstance()->friendNames.push_back(name);
	}
#endif
	//////////////////////////////////////////////////////////////////////////
	g_hWnd = app->getHwnd();


	std::string caption = string("正在寻找 ") + "资料片DLC" + "，需要几分钟，请耐心等待...";
	SetWindowText(g_hWnd, caption.c_str());
#if defined(ccc_date)
	g_DLC = getDLC(g_strRoot + "client");
#else
	g_DLC = getDLC(g_MediaPath + "client");
#endif
	if (g_DLC.empty()) {
		caption = string("找不到 ") + "资料片DLC";
		g_DLC = "请解压资料片";
		MessageBox(nullptr, g_DLC.c_str(), caption.c_str(), MB_OK);
		return 0;
	}
	g_MusicPath = g_DLC + "music/";

	auto wdfs = cWdfs::getInstance()->getCurrReader();
	auto path = g_DLC + "scene.wd/";

	if (eiter) {
		wdfs->loadRoot(path + "shape.wd1");
		wdfs->loadRoot(path + "shape.wd3");
	}
	wdfs->loadRoot(path + "baby.wdf");
	wdfs->loadRoot(path + "shape.wdf");
	wdfs->loadRoot(path + "shape.wd2");

	auto ui = g_DLC + "scene.ui/";
	vector<string> uis = { "uijd.wdf", "uigy.wdf", "uisj.wdf", "uiyz.wdf" };
	wdfs->loadRoot(ui + uis[(int)eui]);
	wdfs->loadRoot(ui + "ui.wdf");
	wdfs->loadRoot(ui + "ui.wd1");

#if defined(ccc_date)
	wdfs->loadRoot(g_WdfPath + "yutu.wd5");
#else
	wdfs->loadRoot(g_WdfPath + "chiyou.wd5");
#endif

	cWdf::getColor()->loadRoot(g_WdfPath + "color.wd5");
//	cWdf::getMp3()->loadRoot(path + "music.wdf");
	cWdf::getWav()->loadRoot(path + "sound.wdf");

	if (cGame::getInstance()->isMaper()) {
		cWdfs::getInstance()->getSmap()->loadRoot(path + "smap.wd1");
	}
	cWdfs::getInstance()->getSmap()->loadRoot(path + "smap.wdf");





	int tick = 0;
	float inv = 1.0f / g_FPS;
	auto loop = cLoop::getInstance();
	loop->init(inv);

	auto windsoul = cWindSoul::getInstance();
	auto chwnd = app->getChildHwnd();
	windsoul->create(app->getHwnd(), chwnd, g_640, g_480, g_360);
	if (chwnd != nullptr && g_360 > 0)
	{
		::SetWindowText(app->getChildHwnd(), "v220901");
	}

	cInput::getInstance()->init(app->getHwnd(), g_hInst = hInstance);
//	getWeimei();
	Init();
#if !defined(ccc_date)
	g_pMainState->Init();
	g_StateTypeOld = g_StateType = STATE_MENU;
#else
	g_StateTypeOld = g_StateType = STATE_MAIN;
#endif
	Frame();
	g_pMainState->m_Channel.m_NeedShow = !cGame::getInstance()->isChatShown();

	int threadsCount = 1; std::thread::hardware_concurrency();
	if (threadsCount > 1) {
		renderThread = std::thread(&renderWindsoul);
	}
	while (true)
	{
		if (loop->peek())
		{
			if (loop->isBreak())
			{
				break;
			}
			continue;
		}
		if (!loop->loop())
		{
			continue;
		}
		if ((++tick) > g_FPS)
		{
			tick = 0;
#if !defined(ccc_date)
			::SetWindowText(g_hWnd, "梦幻群侠传5");
#else
			::SetWindowText(g_hWnd, "日期版");
#endif
		}
		cInput::getInstance()->update();
		if (Frame())
		{
			g_pMainState->m_Canvas._canvas.clear();
			g_pMainState->m_Canvas.push();
		} else if (threadsCount == 1) {
			windsoul->clear();
			windsoul->blit();
		} else {
			std::unique_lock<std::mutex> lock(renderMutex);
			s_windsoul = windsoul;
			renderCondition.notify_one();
		}
		if (g_StateType == STATE_EXT) break;
	}

//	if (threadsCount > 1) {
// 		std::unique_lock<std::mutex> lock(renderMutex);
// 		g_StateType = STATE_EXT;
// 		renderCondition.notify_one();
//		renderThread.join();
//	}
	
	quick_exit(0);
	return 0;
}

