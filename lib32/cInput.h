#pragma once
#include <windows.h>
#include "_inc.h"

class cInputDx;
class cInputDevice;
// ����(���)
class cInput
{
public:
	cInput();
	static cInput* getInstance();

	bool init(HWND hwnd, HINSTANCE hinst);

	// ����¼�: �������
	bool isLdown(bool lock = true);
	void lockLdown();
	void unlockLdown();
	// ����¼�: �����ס
	bool isLkeep();
	bool isLup(bool lock = true);
	void lockLup();
	// ����¼�: �Ҽ�����
	bool isRup(bool lock = true);
	void lockRup();
	// �����¼�: ���̰���
	bool isKdown(unsigned char key, bool lock = true);
	bool isAlt();
	// ����¼�: ȡ������
	int getWheel(bool lock = true);
	void lockWheel();

	// ����¼�: ȡ���λ��
	const cocos2d::Vec2& getMouse();
	// ����¼�: ȡ��������һ֡��ƫ��
	const cocos2d::Vec2& getMouseDelta();

private:
	HWND _hwnd;
	cInputDx* _input;
	cInputDevice* _mouse;
	cInputDevice* _keybord;
	bool _islup;
	bool _isluplock;
	bool _islkeep;
	bool _islkeepLast;

	bool _isrup;
	bool _isruplock;
	bool _isrkeepLast;

	bool _iswheellock;

	cocos2d::Vec2 _vCursor, _vDelta;
public:
	void update();
};