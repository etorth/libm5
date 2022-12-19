#pragma once
#include "global.h"
class cCanvas5;

class cAccelator:public cInterfaceFather
{
public:
	BOOL CheckRB();
	void Init();
	BOOL ProcessAccelator();
	virtual BOOL ProcessInput();
	virtual BOOL Show(cCanvas5* pCanvas);
	virtual BOOL CheckL();
	void OnOff(BOOL NeedShow);
private:
	BOOL UseSkill(int id);
	int m_AccelatorSelect=-1;
	cDescribe m_Describe;
	int m_Mode=0;
	BOOL m_bInit=FALSE;
	CWFile m_Accelatorback; //��ݼ��ı�����
	cWfileP m_Accelatorbackp[8];
	CWFile  m_AccelatorSkill[8];
	cText5   m_tAccelatorSkill[8];
	int		m_AccelatorSkillid[8];

	RECT m_redrawrect;
	int m_NumofSkill=0;
	cWfileP m_MagicBack;
	CWFile m_SkillHead[30];
	sSkill* m_pSkillShow[30];
	void MoveMagicBack(int x,int y);
	cText5 m_TitleT;
	int m_SkillSelect;

};

class cPCHead :public cInterfaceFather
{
public:

	BOOL CheckL();

	int m_MouseOn;
	int m_MouseOnPre = -1;
	//��¼��һ�εĽ�ɫѪ��,�����һ��,�ټ���
	//�ܱ�ÿ֡������˷�������
	

	void UpdatePcHp();
	void UpdatePcMp();
	void UpdatePcCp();
	void UpdatePcExp();
	void UpdatePetHp();
	void UpdatePetMp();
	void UpdatePetExp();

	BOOL UpDateHead();
	CWFile m_PetFaceBack; //�ٻ���ͷ�񱳾�
	CWFile m_PCFace;
	vector<CWFile> m_TeamFace;
	vector<CWFile> m_TeamBack;
	vector<CWFile> m_TeamPetFace;
	CWFile m_PetFace;
	
	cPet*       m_pPet = 0;      //��ѡ��ʱ���ٻ���
	void SetPetHead(DWORD head);
	void UpdateDate();
	BOOL UpdatePet();
	void Init();
	void MoveTeamHead(BOOL mode);
	BOOL SetPcID(int id );
	BOOL Show(cCanvas5* pCanvas);
	BOOL ProcessInput();
	virtual void OnOff(BOOL NeedShow){};
	BOOL CheckRB();
	
	vector<cWfileP> m_EmptyLinep;
	CWFile m_EmptyLine;


	vector<cWfileP> m_HPlinep;
	vector<cWfileP> m_HeartHurtp;
	vector<cWfileP> m_MPlinep;
	vector<cWfileP> m_EXPlinep;

	CWFile m_MPline;
	CWFile m_CPline;
	CWFile m_HeartHurt;
	CWFile m_EXPline;
	CWFile m_HPline;

	CWFile m_Heart;
	CWFile m_PetHead;
	CWFile m_CharacterHead;
	cText5 m_TMouseOnLine;
private:
	BOOL m_bPetHeadMode[5];
	BOOL m_bInit = FALSE;
};
class cFullMagic
{
public:
	BOOL SetMagicUp(int dataid,DWORD id,int x,int y);
	vector<CWFile> m_FullSkilUP;
	vector<CWFile> m_SufferMagic;
	cFullMagic();
};


// enum eChannel5
// {
// 	ec��ǰ, //0
// 	ec����,    //1
// 	ec����,
// 	ecϵͳ,
// 	ec˽��
// };
class cInterfaceChannel :public cInterfaceFather
{
public:
	void OnOff(BOOL NeedShow){};
	CWFile m_MoveIcon;
	CWFile* m_pCurrentChannel;
	CWFile m_Channel[5];
	CWFile m_Face[129];
	sFaceText m_ContextList[30];
	int     m_ContextStart;  //��1����λ��
	int     m_ContextNum;//�ܹ��ж�����
	int     m_ContextShowStart;//��������ʼ��ʾ
	int    m_ContextShowNum;
	BOOL AddNewString( string str,string name="",int channel=3);
	void addNewStringWithoutChat(const std::string& text, const std::string& name = "", int channel = 3);
	void addChat(const std::string& text, const std::string& name = "", int channel = 3);
	void UpDateShow();
	void SetPos();
	int m_WidthChannel;
	int m_HeightChannel;

	int m_HeightCube;//�о�
	cSprite9 m_Back;
	// cWfileP m_BackP[4];
	BOOL Init();
	DWORD m_FaceId[129];
	virtual BOOL ProcessInput();
	virtual BOOL CheckL();
	BOOL Show(cCanvas5* pCanvas);
	BOOL Move(int x,int y);

	int _contextListY = 0;
	struct sFaceTextY {
		sFaceText* c;
		int y;
	};
	std::vector<sFaceTextY> _contextList;

};
struct sMapselect
{
	DWORD m_SmallMap;
	string m_Name;
	vector<int> m_x, m_y;
	vector<int> m_xorg, m_yorg;
	int m_num;
	int m_Height;
	float m_bili;
};
class cCanvas5;
class cInterfaceItem :public cInterfaceFather
{
public:
	
	cDescribe m_Describe;
	void  SetEquipSpecial(sItem2& ProPerty, int ID);
	
	void  SetEquipSpecial2(sItem2& ProPerty, int ID);//������Ч
	void  SetHaveZuoQi(BOOL b);
	void  SetEquipZuoQiZhuangShi(BOOL b);
	
	BOOL Move(int x, int y);
	int   m_ItemPage=0;

	BOOL   CheckZuoQi();
	CWFile m_EquipBack;  //��װ����װ��ʱ�ı���
	

	CWFile m_BigHead;
	BOOL   m_bXianJin;
	CWFile m_XianJin;   //�ֽ�ť
	
	BOOL   UseItem(int ID, cPCData& pcData);
	BOOL   UseItem(int ID,int TargetID);
	RECT m_rectEquip;
	RECT m_rectPetEquip;
	RECT m_rectItem;

	BOOL   m_SwapMode;
	CWFile m_SelectMark;
	CWFile m_MouseOnMark;
	vector<cWfileP> m_EquipBackP;
	vector<cWfileP> m_PetEquipBackP;
	vector<CWFile> m_ItemHead;
	vector<CWFile> m_EquipHead;//��ɫ���ٻ���װ��
	vector<CWFile> m_PetEquipHead;
	CWFile m_SwapItemSelect;
	//��ɫװ��ģʽ
	CWFile m_BigBigHead;
	CWFile m_Headback;
	//�ٻ���װ��ģʽ
	CWFile m_PetHeadback;
	cWfileP m_ButtonPetMode;
	cText5 m_tButtonPetMode;
	cPet* pPet;
	cText5 m_PetName;
	//
	DWORD m_PetID;
	CWFile m_Item;
	CWFile m_ItemButton;
	CWFile m_ItemButton2;
	CWFile m_ZuoQiB;
	CWFile m_ZuoQiZhuangShiB;
	DWORD m_BackID;
	DWORD m_FabaoID;
	CWFile m_FabaoButton;
	DWORD m_ZuoQiID;
	int  m_SwapID;
	BOOL SetItemPage(int page);
	BOOL SwapItem(const int ID, const int IDTarget, cPCData* pcdata = 0);
	BOOL GetItem(int CharID, sItem2* pItem);  //�õ���Ʒ
	void OnOff(BOOL NeedShow=FALSE);
	BOOL Overlay(int Pos, int CharID, sItem2* item);//������Ʒ
	int  FindSame(int itemID, int itemType, int StartPos = 9, int EndPos = 28, int PcID = 2); //Ѱ�ҿɵ�����Ʒ
	int  FindIdle(int StartPos, int EndPos, cPCData& pcdata);//Ѱ�ҿո� 
	int  FindIdle(int StartPos = 0, int EndPos = 60, int PcID = 0);//Ѱ�ҿո� 
	BOOL Add(int Pos,int CharID,sItem2* item);//�ڿ�λ�ü���Ʒ
	BOOL Add(int Pos, cPCData& pcData, sItem2* item);//�ڿ�λ�ü���Ʒ
	void Set(int Num){ m_Select = Num; };
	BOOL ProcessInput();
	BOOL CheckL();
	BOOL CheckRB();
	void UpdateData();
	BOOL UpDateItemDate(cDescribe& Describe);//������Ʒ��Ϣ
	BOOL UpDateItemDate(cDescribe& Describe,sItem2* pItem);
	void Init();
	BOOL Show(cCanvas5* pCanvas);
	BOOL LoadSmallMap(int ID);
	BOOL SetXianJin(BOOL b);
	~cInterfaceItem();
	cText5 m_TCunYingN;
	cText5 m_TXianJin;
	cText5 m_TXianJinN;
	cText5 m_TZuoQi;
	cText5 m_TZhuangShi;
	cText5 m_TItemNum[20];

	int m_NowSelect;
	//���з�
	CWFile m_WorldMap;
	CWFile m_MapSelect;
	int    m_NumMapSelect;
	int    m_Mode;
	RECT   m_MapRect[7];
	DWORD  m_MapID[7];
	
	//������
	BOOL ProcessSelectMap();
	BOOL ProcessSelectMap2();
	BOOL ProcessSelectMapMoon();
	CWFile m_MapBack;
	cText5 m_MousePos;
	CWFile m_MousePosBack;
	void UpdateMousePosBack();
	//string  m_WorldName;
	CWFile m_PathPoint;
	cWfileP m_PathPointp[30];//���30��
	sMapselect*  m_pMapSelect = 0;
	sMapselect m_sMapSelect[5];
	BOOL ShowSelectMap();
	BOOL ShowSelectMap2();
	void InitMode(int id);
	int* pItemnum;
private:
	cObj m_Obj;
	BOOL m_bInit = FALSE;
	BOOL  m_bCharHaveZuoQi;
	void  UpdateItemNum(int ID);
};
enum eFormation  //����
{
	normal,//��ͨ��
	land,//������
	wind,//������
	tiger,//������
	dragon,//������
	bird,//������
	snake,//�����
	sky,//�츲��
	cloud,//�ƴ���
	thunder,//�׾���
	eagle//ӥХ��
};
class cInterfaceTeam :public cInterfaceFather
{
public:

	~cInterfaceTeam();
	void FreeFighter(int id);
	cText5 m_lineupName;
	int   m_ilineupSelect;
	cWfileP m_lineupSelectB;
	vector<cWfileP> m_lineupSelectBP;//һ����11����
	cWfileP m_SetFriend;
	cText5 m_tSetFriend;
	vector<cText5>   m_lineupSelectBPT;
	cText5 m_lineupSelectBT;
	vector<cText5> m_Describe;
	CWFile m_lineupB;
	/*cWfileP m_ControlB;
	cText  m_ControlBT;*/
	CWFile m_lineupSelectBack;
	BOOL   m_bLiineupSelect;
	cWfileP m_lineupCancelB;
	CWFile m_lineupPeople;
	vector<cWfileP*>  m_lineupPeoplepp;
	void  SortLineupPeople();
	vector<cWfileP> m_lineupPeoplep;
	vector<cText5> m_lineupPeoplepT;
	void  SetlineupPeople(eFormation select);
	cText5  m_lineupBT;
	cText5  m_tSmall;
	cText5  m_tBig;
	eFormation  m_eLineupSelect;
	CWFile m_FighterSelect;
	int  m_FighterSelectid;
	CWFile m_Back;
	RECT m_FightRect;
	void Move(int x, int y);
	void OnOff(BOOL NeedShow);
	void MoveLineSelect(int x, int y);
	BOOL Init();
	
	vector<cObj> m_Fighter;
	vector<cText5> m_tName;
	vector<cText5> m_tLv;
	vector<cText5> m_tMengPai;
	
	BOOL ProcessInput();
	BOOL ProcessSelectLineup(int xMouse, int yMouse);
	BOOL CheckL();
	cWfileP* m_plineupButton=0;
	BOOL CheckRB();
	DWORD GetSmallHead(int id);
	DWORD GetPetHead(int id);
	BOOL Show(cCanvas5* pCanvas);
	BOOL ShowSelectLineup(cCanvas5* pCanvas);
	BOOL UpDate();
	void SetupOneFormationEffect(int Pos, cPetData* pPetData, BOOL UporDown);
	void SetFighterPos(BOOL enemy);
	vector<int> m_xPosList;
	vector<int> m_yPosList;
	inline int GetXPos(int id);
	inline int GetYPos(int id);
	int  GetReTramTrun(int id);
	int GetTeamTurn(int id){ return m_TeamTurn[id]; }
	void SetTeamTurn(int id,int turn){ m_TeamTurn[id]=turn; }
	void SwapTeamTurn(int id1, int id2);
	void SetFormation(eFormation format, BOOL enemy = FALSE,BOOL updatetext=FALSE);
	
	void UpdatePos();
	void Save(ofstream& File);

	void Load(ifstream& File);
	eFormation m_eEnemyFormation;
	eFormation m_eOurFormation;
private:
	
	BOOL AutoSwap(int i);
	BOOL m_bInit = FALSE;
	vector<int> m_TeamTurn;//������������λ��
	cFightState* m_pFightState;
	void SetFighterPos2(int** px,int** py,int xOf1,int yOf1 ,BOOL enemy);
};
struct sTags
{
	cSprite9 sprite;
	cText5 text;
	int m_time;
};
class cTags
{
public:
	void GetMoneyAndExp(int money, INT64 exp = 0, int chubei = 0,INT64 expbb=0,BOOL needtag=TRUE);
	void GetItem(string itemname);
	int m_Sleeptime;
	CWFile m_Back;
	BOOL Init();
	BOOL Add(string str,int time = 270);
	BOOL Show(cCanvas5* pCanvas);
	void Process();
	int  m_TagNum, _tagMax;
	static const int c10 = 64;
	sTags m_tags[c10];//�����ʾ5��
	cText5 m_Text;
	~cTags();
private:
	BOOL m_bInit = FALSE;
};

class cWorldMap:public cInterfaceFather
{
public:
	enum  eMap
	{
		eMapWorld,	
		eMapWorldEast,
		eMapWorldWest,
		eMapWorldSouth,
		eMapWorldNorth,
		eMapWorldLG,
		eMapWorldTG,
		eMapWorldYG,
		eMapWorldPTY,
		eMapSouth,
		eMapNorth,
		eMapEast,
		eMapWest,
		eMapFenChao, //����«�� 13-16
		eMapLongKu,
		eMapNvWa,
		eMapAL,		//��ʤ���� 16-20
		eMapHGS,
		eMapNR,
		eMapPengLai,
		eMapCA,		//�� 20-38
		eMapDT,
		eMapDF,
		eMapGLZ,
		eMapHZ,
		eMapHS,
		eMapJY,
		eMapJZ,
		eMapLG,
		eMapMW,
		eMapPS,
		eMapPT,
		eMapSML,
		eMapST,
		eMapD5,
		eMapWZ,
		eMapXXT,	
		eMapMJC,
		eMapBX,		//��  38-45
		eMapBQ,
		eMapCS,
		eMapFC,
		eMapZZ,
		eMapXL,
		eMapQLS
	};
	BOOL CheckRB();
	int m_xPre=0;
	int m_yPre=0;
	cText5 m_text;
	void OnOff(BOOL bShow);
	BOOL  MoveTest(CWFile& Target);
	virtual BOOL ProcessInput();
	BOOL ProcessInput0(); //����
	BOOL ProcessInput1(); //��
	BOOL ProcessInput2(); //��
	BOOL ProcessInput3(); //��
	BOOL ProcessInput4(); //��
	virtual BOOL Show(cCanvas5* pCanvas);
	BOOL	Show0(cCanvas5* pCanvas);
	BOOL	Show1(cCanvas5* pCanvas);
	BOOL	Show2(cCanvas5* pCanvas);
	BOOL	Show3(cCanvas5* pCanvas);
	BOOL	Show4(cCanvas5* pCanvas);
	virtual BOOL CheckL();
	int m_Mode;
	CWFile m_Data[45];
	string m_MapName[45];
	void Init();
	void InitPos();
	CWFile* m_pShow = 0;
private:
	BOOL m_bInit = FALSE;
};

class cInterfaceRanSe:public cInterfaceFather
{
public:
	BOOL CheckRB();
	void UpdateColor();
	BOOL CheckL();
	void OnOff(BOOL NeedShow);
	void Init();
	BOOL Show(cCanvas5* pCanvas);
	void Move(int x, int y);
	void SetMode(int mode, int Characterid);//sFriendList* plist=0);//0 ��ɫȾɫ  1����Ⱦɫ  2 ����װ��Ⱦɫ 3 �ٻ���Ⱦɫ
	void SetPet(int part, cCharacter* pc);
	BOOL ProcessInput();
	int m_Mode;
	CWFile m_Back;
	cText5 m_Title;
	cText5 m_tBuy;
	CWFile m_btBuy;
	cText5 m_Cost;
	CWFile m_Target;
	CWFile m_btSelect[4];
	cText5  m_tSelect[4];
	DWORD  m_ColorID;
	int m_NowPart=0;
	sChangeColorData m_ChangeColorData;
	
private:
	CWFile m_NextPage;
	cObj m_Obj;
	sFriendList* m_plist = 0;
	BOOL m_bInit = FALSE;
};


class cBangPaiJiNengXueXi:public cInterfaceFather
{
public:
	BOOL Leveupskill(int lvup);
	void Init();
	void OnOff(BOOL NeedShow);
	virtual BOOL ProcessInput();
	virtual BOOL Show(cCanvas5* pCanvas);
	virtual BOOL CheckL();
	BOOL CheckRB();
	void Move(int x, int y);
	void UpDate();
	void SetSkillSelect(int select);
	CWFile m_Back;


	CWFile m_SkillHead[14];
	cText5 m_tSkillHead[14];
	CWFile m_Button[2];
	cText5 m_tButton[2];
	cText5 m_tExp;
	cText5 m_tNeedBangGong;
	cText5 m_tNeedExp;
	cText5 m_tNeedMoney;
	cText5 m_tXueFei;
	cText5 m_tChuBei;
	cText5 m_tMiaoShu;
	CWFile m_SelectMark;

	int m_SkillSelect;
	
	INT64 m_NeedExp;
	INT64 m_NeedMoney;
	int m_NeedBangGong;

private:
	int m_BangpaiSkilllv=180;
	BOOL m_bInit = FALSE;
};


class cInterfaceChallange : public cInterfaceFather
{
public:
	void init();
	CWFile* getBack() { return &m_Back; }
	void move(int x, int y);
 	BOOL Show(cCanvas5* pCanvas);
	void add(const std::string& name, int chapter, int stage);
	void onChallange(const std::string& name, int chapter, int stage);

	cSprite9 m_Back;
	int _index = -1;
};



class cInterfaceInstructions : public cInterfaceFather
{
public:
	void init();
	void initShow();
	CWFile* getBack() { return &m_Back; }
	void move(int x, int y);
	BOOL Show(cCanvas5* pCanvas);
	void add(int index, const std::string& str);
	int _page = 0;
	cText5* _title = nullptr;
	cText5* _text = nullptr; // ��¼λ��
	std::vector<sFaceText> _ftexts;
	std::vector<std::string> _titles;

	// ������
	cGame _game;
	const int cTagCfg = INT_MIN;
	cSprite9 m_Back;
};


// ���ڰ�
class cInterfaceConfig :public cInterfaceFather
{
public:
	void init();
	void initShow();
	bool ProcessInputMore();
	std::string getString(int i);
	void onClick(int i);
protected:
	std::array<cText5*, 15> _ts;
	int _012 = 0;
};