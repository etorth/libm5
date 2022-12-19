#pragma once
#include <string>
#include <list>

struct IGraphBuilder;
struct IMediaControl;
struct IMediaPosition;
struct IMediaEvent;
class cMySound
{
public:
	cMySound();
	void Reset();
	void Load(std::string path);
	void play(std::string filename);
	void CheckEnd();
	void Free();
	void Stop();
	void Play();
	~cMySound(){ Free(); };
private:
	IGraphBuilder* m_pGraphBuilder = nullptr;
	IMediaControl* m_pMediaControl = nullptr;
	IMediaPosition* m_pMediaPosition = nullptr;
	IMediaEvent* m_media_event = nullptr;
};


struct IDirectSoundBuffer;
class cMyWav
{
public:
	~cMyWav(){ Free(); };
	void Load(const char* pdata,int size,int pos=0, bool bPlay=true);
	void Free();
	void SetPosition(int num);
	int GetNowPostion();
private:
	IDirectSoundBuffer* m_pPrimaryBuffer = nullptr;
	int m_size;
	bool bLoad = false;

	std::list<const char*> _caches;
};

