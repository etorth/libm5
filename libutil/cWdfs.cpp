#include "cWdfs.h"
#include "../libm5/global.h"
#include "../lib32/efolder.h"

cWdfs::cWdfs()
{
	_currSmaps = new cReader;
	_currReader = new cReader;
}


cWdfs* cWdfs::getInstance()
{
	static cWdfs* s_group = new cWdfs();
	return s_group;
}