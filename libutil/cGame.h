#pragma once
#include "_inc.h"
#include <functional>
#include <string>

enum class euiType { jd, gy, sj, yz };
class cGame
{
public:
	static const std::string cFilename;
	static cGame* getInstance();

	void setwh(int w, int h) { _w = w, _h = h; }
	int getw() { return _w; }
	int geth() { return _h; }
	int isChatShown() { return _isChatShown; }
	void switchChatShown() { _isChatShown = !_isChatShown; }

	bool isIter() { return _eiter; }
	void setIter(bool iter) { _eiter = iter; }
	euiType getui() { return _eui; }
	void setui(euiType ui) { _eui = ui; }

	bool isMp3() { return _isMp3; }
	void setMp3(bool mp3) { _isMp3 = mp3; }
	bool isWav() { return _isWav; }
	void setWav(bool wav) { _isWav = wav; }
	int getVolume() { return _volume; }
	void setVolume(int volume) { _volume = volume; }

	bool save();
	bool load(const std::string& path, const std::string& exe, const std::string& config);

	bool isMaper() { return _maper; }
	void setMaper(bool iter) { _maper = iter; }
	bool isEdge() { return _isEdge; }
	void setEdge(bool phone) { _isEdge = phone; }

	const std::string& getPath() { return _path; }
	const std::string& getExe() { return _exe; }
	const std::string& getConfig() { return _config; }
private:
	int _w = 800, _h = 600;
	bool _isChatShown = true;
	bool _eiter = false;
	bool _maper = false;
	euiType _eui = euiType::sj;
	int _volume = 100;
	bool _isMp3 = true;
	bool _isWav = true;
	bool _isEdge = true;
	std::string _path, _exe, _config;
};