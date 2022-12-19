#include "cGame.h"
#include <fstream>

cGame* cGame::getInstance()
{
	static cGame* s_game = new cGame();
	return s_game;
}

static const char* s_space = " ", *s_enter = "\n";
bool cGame::save()
{
	return false;
	if (_config.empty()) return false;
	std::ofstream ofile(_config);
	if (!ofile.is_open()) return false;
	ofile << _w << s_space << "//��Ļ���\n" << _h << s_space << "//��Ļ�߶�\n";
	ofile << (int)_eiter << s_space << "//��Դ����(0Ψ��,1����,2����)\n";
//	ofile << (int)_emap << s_space << "//��ͼ����(0Ψ��,1����,2����)\n";
	ofile << (int)_eui << s_space << "//ui����(0����,1����,2ˮ��,3����)\n";
	ofile << _isChatShown << s_space << "//���촰��(0����ʾ,1��ʾ)\n";
//	ofile << _isMp3 << s_space << "//����\n" << _volume << s_space << "//����\n" << _isWav << s_space << "//��Ч\n";

	ofile.close();
	return true;
}

bool cGame::load(const std::string& path, const std::string& exe, const std::string& config){
	_path = path;
	_exe = exe;
	_config = config;
	std::ifstream ifile(_path + config);
	if (!ifile.is_open()){
		return false;
	}
	std::string  line;
	ifile >> _w;
//	getline(ifile, line);
	ifile >> _h;
//	getline(ifile, line);
	int e;
	ifile >> e;
//	getline(ifile, line);
	_eiter = (bool)e;
	ifile >> e;
//	getline(ifile, line);
	_maper = (bool)e;
	ifile >> e;
//	getline(ifile, line);
	_eui = (euiType)e;
	ifile >> _isChatShown;
// 	getline(ifile, line);
// 	ifile >> _isMp3;
// 	getline(ifile, line);
// 	ifile >> _volume;
// 	getline(ifile, line);
// 	ifile >> _isWav;
	ifile >> _isEdge;

	ifile.close();
	return true;
}
