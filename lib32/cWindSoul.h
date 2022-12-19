#pragma once
// �����Ʒ�ķ��++����:
/*
 "               ..;;;;,                     ;;;,
 '           ..;;;"` ;;:           ,;;;;;: ,;;;:.,;..          _/
 `     ,;..,;;"`    :;;'            :;;"`,;;;;;;"":;;         _/
	   ;;;"  `:;;. ;;'           ..;;:  .;;,.;;:',;;"    _/_/_/_/_/
	  .;;`   ,;;" .;"          ,;;;;;;" :;`',;",;;"         _/
	 ,;;,:.,;;;  ,;:          :" ,;:` , `:.;;;;;'`         _/
	 ;;"'':;;:. .;; .          ,;;;,;:;;,;;;, ,;             _/
	:;;..;;;;;; :;' :.        :;;;"` `:;;;;;,;,.;.          _/
  .;;":;;`  '"";;:  ';;       '""   .;;`.;";:;;;;` ;,  _/_/_/_/_/
 ;;;" `'       "::. ,;;:          .;"`  ::. '   .,;;;     _/
 ""             ';;;;;;;"        ""     ';;;;;;;;;;`     _/

						Windsoul++

				by �Ʒ� (Cloud Wu)  1999-2001

		http://member.netease.com/~cloudwu
		mailto:cloudwu@263.net

		���Ķ� readme.txt �еİ�Ȩ��Ϣ
		See readme.txt for copyright information.


.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
// 
// �����Ʒ�ԭ��:
// �����������Լ���������, ���������ʹ�÷����������һ�д���.�����Ҷ�ʹ����Щ����������κκ��������.�ҽ����ҿ��ܵķ��ֲ������������д��ڵ�Bug, �����µ�����, �ش�ʹ��������������.�����һ���ҶԴ�ʧȥ����Ȥ, ȴ�п��ܷ����Դ˴����ά������.�������Լ���Ҫ�е�ʹ����Щ������ܴ��ڵķ��ա�
// ��Ȩ
// ���ϵ�����Ʒ�����������, �Թ���Դ�������ʽ�������˿���ʹ��.������뽫�������һ���ִ���������ҵ���ʹ��, �뽫�Ʒ�������������.������ڵ��������Ӯ������, �������ʹ���߿��Կ����ĵط�ע��ʹ���˷��.����ֱ�ӽ�����Դ��������Ӯ����;(������¼�ڸ��ֹ���, ���뵽Ӯ�����ʵĳ�����ؼ�, ������ֳ�����ȵ�) ������Ⱥ��Ʒ���ϵ.

#include <windows.h>
#include <vector>
#include <map>

#undef MAX
#undef MIN
#include "../libwindsoul/windsoul.h"
#include "../libwindsoul/wsgeo.h"
#include "../libwindsoul/wsfont.h"
#include "../libwindsoul/wsalpha.h"
#include "../libwindsoul/wscanvas.h"
#include "../libwindsoul/wsurface.h"
#undef max
#undef min

typedef WBitmap cBmp;
typedef WAlphaBitmap cAlphaBmp;
typedef WFont cFont;
typedef WChar cChar;
typedef WLine cLine;
typedef WCanvas cCanvas;
//////////////////////////////////////////////////////////////////////////

// ��˳��
enum class eRender { norFont, nor, mapFont, mapMask, mapObj, map };
enum class eCanvas { nor, chat };
class cRender
{
public:
	cRender();
	~cRender();
	void setCanvas(eCanvas e);

	void setRender(eRender e) { _eRender = e; }

	void setRedraw(bool redraw) { _isDraw = redraw; }

	virtual void draw(cCanvas* canvas, const uint32_t& flags){}
protected:
	eRender _eRender = eRender::nor;

	eCanvas _eCanvas;
	cCanvas* _canvas = nullptr;

	uint32_t _flags;
	// �ػ�����: ����ı�(�Ƴ�,���,����,��֡),�����仯(λ��,��С,��ɫ(��ɫ),͸����)
	bool _isDraw = true;
	friend class cDraw;
};



class cDraw
{
public:
	cDraw();
	static cDraw* getInstance();

	void push(cRender* render, const uint32_t& flags);

	void onRemove(cRender* render);

	void render();

	void clear();

private:
	std::map<eRender, std::vector<cRender*>> _list;
	friend class cWindSoul;
};

enum class eFont { nor, big, smal, chat };
class cWindSoul
{
public:
	~cWindSoul();
	static cWindSoul* getInstance();

	static void drawSub(cCanvas* canvas, const cAlphaBmp* alphabmp, int x, int y, int w, int h, unsigned char opacity);

	bool create(HWND hwnd, HWND childhwnd, int w, int h, int cw);

	cCanvas* getCanvas(eCanvas e);

	cFont* getFont(eFont e);

	void clear();

	void blit();
private:
	std::map<eCanvas, cCanvas*> _canvas;

	WSurface* _surfaceChat = nullptr, _surface;
	WPixel _pixel;
	std::map<eFont, cFont*> _fonts;
};