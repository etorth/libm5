#pragma once
#include "cReader.h"

class cWdfs
{
public:
	cWdfs();
	static cWdfs* getInstance();
	cReader* getSmap() { return _currSmaps; }
	cReader* getCurrReader() { return _currReader; }
private:
	cReader* _currSmaps, *_currReader;
};