#include "global.h"
// wav
#include <dsound.h>
// mp3
#include <dshow.h>
#include <io.h>
// wav
#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>
#include <malloc.h>

// wav
#pragma comment(lib,"dsound")
// mp3
#pragma comment(lib,"ole32") 
#pragma comment(lib,"strmiids") 
#pragma comment(lib,"msacm32") 

cMySound::cMySound() {
//	CoInitialize(NULL);
}


static bool writeMp3(ulong uid) {
	int size;
	auto ptr = cWdf::getMp3()->getData(uid, size);
	if (!ptr) return false;
	auto path = g_DLC + "music/";
	static bool crd = true;
	if (crd) {
		crd = false;
		CreateDirectory(cc::replace(path, "/", "\\").c_str(), NULL);
	}
	std::ofstream ofile(path + toString("%08X.mp3", uid), std::ios::binary);
	if (!ofile.is_open()) return false;
	ofile.write(ptr, size);
	ofile.close();
	delete[] ptr;
	return true;
}



void cMySound::Load(std::string path)
{
	static std::map<std::string, std::string> s_transMap = {
		{"比武背景", "帮战入场"},
		{"比武2", "比武场"},
		{"凤巢3", "未知"},
		{"战斗_比武_DT", ""},
	};
	if (s_transMap.find(path) != s_transMap.end())
	{
		path = s_transMap.at(path);
	}

	if (path == "战斗4" || path == "战斗5")
	{
		path = toString("战斗%d", (rand() % 3) + 1);
	}
	if (path == "战斗比武" || path == "战斗_任务" || path == "战斗_任务2")
	{
		path = toString("战斗比武%d", (rand() % 4) + 1);
	}

	// 战斗比武没有5
	// 无名鬼蜮还是无名鬼城?
	static std::map<std::string, ulong> s_mapOri = {

		{"麒麟山",   0x012D9DD7}, // A6D10FCA
		{"神木林",   0x016F4476}, // 进口
		{"凌波城",   0x0B16F601}, // 进口
		{"蓬莱仙岛", 0x10DF6DF7}, // FEB35C13
		{"宝象国",   0x3127BBB8}, // 进口
		{"凌云渡",   0x3F24C153}, // 进口
		{"须弥东界", 0x41645B50}, // 进口
		{"丝绸之路", 0x52A0B4EE}, // A4F294AE
		{"柳林坡",   0x5B9DC400}, // 进口
		{"桃源村",   0x76C2A481}, // 进口
		{"墨家村",   0x7C4D04B2}, // 667C3FA5
		{"西梁女国", 0x8482AF70}, // 6B21CDAA
		{"碗子山",   0x88CD5404}, // 进口
		{"无底洞",   0x95C16AD7}, // 进口
		{"墨家禁地", 0x9E05AC95}, // 进口 声音不像
		{"朱紫国",   0xA602567C}, // 6C217432 79152F3F（正）
		{"比丘国",   0xA8A9DBB9}, // 进口
		{"子母河底", 0xAE8C1555}, // 691A8DE9
		{"波月洞",   0xCD525622}, // 进口
		{"解阳山",   0xDABAC06C}, // 3CBAA017
		//	{"太岁府", 0xEF2610F9} // 獬豸洞 bin播不了


	{"海底迷宫", 0x00167186},
	{"海底迷宫2",0x00167186},
	{"小西天",   0x03D65C21}, // 小雷音寺
	{"大雁塔2",  0x05122F2E},
	{"蟠桃园",   0xEEEA9BEA}, // 3AF41814 19C166F3 EEEA9BEA 01:22     05D78E1D 94C0F589 02:40 前缀好长
	{"长寿郊外", 0x18348D2B},
	{"小雷音寺", 0x2011A8C2},
	{"北俱芦洲", 0x2142584C},
	{"普陀山",   0x21BEB585},
	{"长安城",   0x26275208},
	{"江南野外", 0x266E2C58},
	{"大雁塔1",  0x2C3D8AF0},
	{"长寿村",   0x2F1EC70A},
	{"傲来国",   0x35159569},
	{"狮驼岭",   0x3800966C},
	{"战斗比武1",0x389F5EF4},
	{"魔王寨",   0x4A64F8BD},
	{"大唐官府", 0x4AE2B5B3},
	{"东海湾",   0x4B4740AC},
	{"方寸山",   0x53C2DE57},
	{"地狱迷宫2",0x5A864351},
	{"月宫",     0x5B0DCCD9},
	{"龙窟2",    0x65B90ACA},
	{"建邺城",   0x68F6DDA1},
	{"阴曹地府", 0x700EE303},
	{"",         0x78FC0CBA}, // 像大唐
	{"龙宫",     0x79D250E2},
	{"帮战入场", 0x7B908BCA},
	{"战斗BOSS", 0x845DC12C},
	{"帮派",     0x84E2EB78},
	{"监狱",     0x86C4F045}, // 牢房  地牢 
	{"战斗1",    0x8905924A},
	{"花果山",   0x8C4500FC},
	{"女儿村",   0x8CAB9764},
	{"东海海底", 0x8EF4D872},
	{"未知",     0x9245F880}, // 宏伟 佛系
	{"化生寺",   0x92DD1A7A},
	{"战斗比武2",0x9EC29A9D}, // 战斗5-草原
	{"未知鬼域", 0xA6F426EB},
	{"家",       0xA7330084},
	{"战神山",   0xAA002386},  // 33BE8E92? 
	{"盘丝岭",   0xAC396538},
	{"龙窟",     0xAE8B3481},
	{"凤巢",     0xB0D9F40A},
	{"战斗3",    0xB248A7C7}, // 战斗7-山地
	{"凤巢2",    0xB33EB187},
	{"比武场",   0xBED44FE1},
	{"战斗2",    0xC1064081}, // 战斗6-城市
	{"地狱迷宫", 0xD3B5D40A},
	{"大唐境外", 0xD66E10A8},
	{"女娲神迹", 0xE4096D42},
	{"天宫",     0xE7CE763C},
	{"大唐国境", 0xEA26251A},
	{"地狱迷宫5",0xEBCC1270}, // 无名鬼蜮
	{"无名鬼域", 0xEBCC1270}, // ?
	{"战斗比武3",0xF303B6A9},
	{"战斗比武4",0xFB165E34},
	{"五庄观",   0xFD1ECF8F},
	}; 
	// 6D3B2899 这啥 16702005 DC716156
	// auto it = s_map.find(path);
	// if (it != s_map.end()) {
	// 	// 附带音乐
	// 	path = g_MusicPath + toString("%08X.mp3", it->second);
	// 	std::ifstream ifile(path, std::ios::binary);
	// 	// 找不到
	// 	if (!ifile.is_open()) return;
	// 	ifile.close();
	// 	play(path);
	// 	return;
	// }

	const auto& it = s_mapOri.find(path);
	if (it != s_mapOri.end()) {
		// 自带音乐
		path = g_DLC + toString("music/%08X.mp3", it->second);
		if (::_access(path.c_str(), 0)) {
			path = g_DLC + toString("music/%08X.was", it->second);
			if (::_access(path.c_str(), 0)) {
				return;
			}
		}
		play(path);
		return;
	}
	// 战斗BOSS
	path = g_DLC + toString("music/%08X.was", 0x845DC12C);
	if (::_access(path.c_str(), 0)) {
		return;
	}
	play(path);
}


void cMySound::play(std::string filename)
{
	filename = cc::replace(filename, "/", "\\");
	std::wstring wstr;
	int nLen = (int)filename.length();
	wstr.resize(nLen, L' ');
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)filename.c_str(), nLen, (LPWSTR)wstr.c_str(), nLen);

	Free();
	Reset();
	if (m_pGraphBuilder == nullptr) {
		return;
	}
	// 加载MP3数据
	if (m_pGraphBuilder->RenderFile(wstr.c_str(), NULL)) {
		return;
	}
	Play();

// 	if (g_pMainState->m_GlobalButton[16] == 0) {
// 		// 播放mp3文件
// 		char* ptr = nullptr;
// 		int size;
// 		ifile.seekg(0, std::ios::end);
// 		size = ifile.tellg();
// 		ptr = new char[size];
// 		ifile.seekg(std::ios::beg);
// 		ifile.read(ptr, size);
// 		ifile.close();
// 		if (ptr != nullptr) {
// 			static ulong uid = 0;
// 			cBass::getInstance()->play(_uid = ++uid, ptr, size);
// 		}
// 	}
}

void cMySound::Free()
{
	if (!m_pMediaControl) {
		return;
	}

	m_pMediaControl->Stop();
	m_pMediaControl->Release();
	m_pMediaControl = nullptr;

	if (m_media_event != nullptr) {
		m_media_event->Release();
		m_media_event = nullptr;
	}

	if (m_pMediaPosition != nullptr) {
		m_pMediaPosition->Release();
		m_pMediaPosition = nullptr;
	}

	if (m_pGraphBuilder != nullptr) {
		m_pGraphBuilder->Release();
		m_pGraphBuilder = nullptr;
	}
}

void cMySound::CheckEnd()
{
	if (m_media_event == nullptr) {
		return;
	}

	long event_code, param1, param2;
	// retrieves the next notification event
	if (SUCCEEDED(m_media_event->GetEvent(&event_code, &param1, &param2, 0))) {
		if (event_code == EC_COMPLETE) {
			// frees resources associated with the parameters of an events.
			m_media_event->FreeEventParams(event_code, param1, param2);

			m_pMediaPosition->put_CurrentPosition(0);
		}
	}
}


void cMySound::Reset()
{
	if (m_pMediaControl != nullptr) {
		return;
	}
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraphBuilder);
	if (m_pGraphBuilder == nullptr) {
		return;
	}
	m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);
	m_pGraphBuilder->QueryInterface(IID_IMediaPosition, (void**)&m_pMediaPosition);
	m_pGraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&m_media_event);
}

void cMySound::Stop()
{
	if (m_pMediaControl != nullptr) {
		m_pMediaControl->Stop();
	}
//	cBass::getInstance()->setMp3(0);
}


void cMySound::Play()
{
	if (g_pMainState->m_GlobalButton[16] == 0)
	{
		if (m_pMediaControl != nullptr) {
			m_pMediaControl->Run();
		}
// 		cBass::getInstance()->setMp3(100);
// 		int size;
// 		auto ptr = cWdf::getMp3()->getData(_uid, size);
// 		if (ptr != nullptr)
// 		{
// 			cBass::getInstance()->play(_uid, ptr, size);
// 		}
	}

}


struct {
	unsigned long id;
	unsigned long size;
}
chunk;
void cMyWav::Load(const char* pdata,int size,int pos/* =0 */, bool bPlay/* =true */)
{
	Free();
	//////////////////////////////////////////////////////////////////////////
	_caches.push_back(pdata);
	if (_caches.size() >= 0x20) {
		delete[] _caches.front();
		_caches.pop_front();
	}
	//////////////////////////////////////////////////////////////////////////
	static LPDIRECTSOUND8 g_pDirectSound = nullptr;
	if (g_pDirectSound == nullptr) {
		DirectSoundCreate8(NULL, &g_pDirectSound, NULL);
		g_pDirectSound->SetCooperativeLevel(cApp::getInstance()->getHwnd(), DSSCL_NORMAL);
	}
	//////////////////////////////////////////////////////////////////////////


	memcpy(&chunk, pdata, sizeof(chunk));
	if (chunk.size > size) return;
	pdata += sizeof(chunk);
	if (chunk.id != 'FFIR')// WFourCC("RIFF"))
	{
		return;
	}
	memcpy(&chunk.id, pdata, sizeof(chunk.id));
	pdata += sizeof(chunk.id);
	if (chunk.id != 'EVAW'/*WFourCC("WAVE")*/) {
		return;
	}
	memcpy(&chunk, pdata, sizeof(chunk));
	pdata += sizeof(chunk);
	if (chunk.id != ' tmf'/*WFourCC("fmt ")*/) {
		return;
	}

	int SrcHeaderSize = chunk.size;
	if (SrcHeaderSize < sizeof(WAVEFORMATEX))SrcHeaderSize = sizeof(WAVEFORMATEX);
	WAVEFORMATEX *SrcHeader = (WAVEFORMATEX *)_alloca(SrcHeaderSize);
	ZeroMemory(SrcHeader, SrcHeaderSize);
	memcpy(SrcHeader, pdata, chunk.size);
	pdata += chunk.size;

	for (;;) {
		memcpy(&chunk, pdata, sizeof(chunk));
		pdata += sizeof(chunk);
		if (chunk.id == 'atad'/*WFourCC("data")*/) break;
		pdata += chunk.size;
	}
	if (SrcHeader->wFormatTag != WAVE_FORMAT_PCM) {
		// 准备变换后的handle
		WAVEFORMATEX *DstHeader = (WAVEFORMATEX *)_alloca(SrcHeaderSize);
		memcpy(DstHeader, SrcHeader, SrcHeaderSize);

		DstHeader->wFormatTag = WAVE_FORMAT_PCM;

		MMRESULT Result;
		Result = acmFormatSuggest(NULL, SrcHeader, DstHeader, SrcHeaderSize, ACM_FORMATSUGGESTF_WFORMATTAG);
		if (Result != 0) {
			return;
			//	ERRBOX;
		}

		// 准备ACM STREAM
		HACMSTREAM acm;
		Result = acmStreamOpen(&acm, NULL, SrcHeader, DstHeader, NULL, NULL, 0, 0);
		if (Result != 0) {
			return;
			//	ERRBOX;
		}

		// 对应输出Bytes获得输入Bytes
		unsigned long DefaultWriteSize;
		unsigned long DefaultReadSize = chunk.size;
		Result = acmStreamSize(acm, DefaultReadSize, &DefaultWriteSize, ACM_STREAMSIZEF_SOURCE);
		if (Result != 0) {
			acmStreamClose(acm, 0);
			return;
			//	ERRBOX;
		}
		DSBUFFERDESC dsbd;
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_STATIC;
		dsbd.dwBufferBytes = DefaultWriteSize;
		dsbd.dwReserved = 0;
		dsbd.lpwfxFormat = DstHeader;
		g_pDirectSound->CreateSoundBuffer(&dsbd, &m_pPrimaryBuffer, NULL);
		char *soundbuf;
		m_pPrimaryBuffer->Lock(0, 0, (void**)&soundbuf, &DefaultWriteSize, NULL, NULL, DSBLOCK_ENTIREBUFFER);
		// 准备变换buffer
		ACMSTREAMHEADER stream;
		ZeroMemory(&stream, sizeof(stream));
		stream.cbStruct = sizeof(stream);
		stream.pbSrc = new unsigned char[DefaultReadSize];
		stream.cbSrcLength = DefaultReadSize;
		stream.pbDst = (unsigned char*)soundbuf;
		stream.cbDstLength = DefaultWriteSize;
		Result = acmStreamPrepareHeader(acm, &stream, 0);
		if (Result != 0) {
			return;
			//	ERRBOX;
		}
		memcpy(stream.pbSrc, pdata, DefaultReadSize);
		pdata += DefaultReadSize;
		stream.cbSrcLength = DefaultReadSize;
		// 变换
		Result = acmStreamConvert(acm, &stream, 0);
		if (Result != 0) {
			return;
			//	ERRBOX;
		}
		m_pPrimaryBuffer->Unlock(soundbuf, DefaultWriteSize, NULL, 0);
		delete[] stream.pbSrc;
		acmStreamUnprepareHeader(acm, &stream, 0);
		Result = acmStreamClose(acm, 0);
		m_size = DefaultWriteSize;
	} else {
		DSBUFFERDESC dsbd;
		unsigned long size = chunk.size;

		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_STATIC;// WSSB_CAPS
		dsbd.dwBufferBytes = size;
		dsbd.dwReserved = 0;
		dsbd.lpwfxFormat = SrcHeader;

		g_pDirectSound->CreateSoundBuffer(&dsbd, &m_pPrimaryBuffer, NULL);
		if (!m_pPrimaryBuffer) {
			return;
		}
		char *soundbuf;
		m_pPrimaryBuffer->Lock(0, 0, (void**)&soundbuf, &size, NULL, NULL, DSBLOCK_ENTIREBUFFER);
		memcpy(soundbuf, pdata, size);
		pdata += size;
		m_pPrimaryBuffer->Unlock(soundbuf, size, NULL, 0);

	}
	bLoad = true;
	SetPosition(pos);
	if (bPlay) {
		m_pPrimaryBuffer->Play(0, 0, 0);
	}
}

void cMyWav::Free()
{
	if (!m_pPrimaryBuffer) {
		return;
	}
	m_pPrimaryBuffer->Release();
	m_pPrimaryBuffer = nullptr;
	bLoad = false;
}

void cMyWav::SetPosition(int num)
{
	if (num == 0) {
		m_pPrimaryBuffer->SetCurrentPosition(0);
	} else {
		m_pPrimaryBuffer->SetCurrentPosition((m_size * num) / 100);
	}

}

int cMyWav::GetNowPostion()
{
	return m_pPrimaryBuffer->GetCurrentPosition(0, 0);
}



