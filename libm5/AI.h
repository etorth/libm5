#pragma once
#include "_inc.h"

enum eAIUseItemType
{
	eAIUseItemTypeHP,
	eAIUseItemTypeHPALL,
	eAIUseItemTypeMP,
	eAIUseItemTypeMPALL,
	eAIUseItemTypeHPHurt,
	eAIUseItemTypelive,
	eAIUseItemTypeUnseal,
	eAIUseItemTypeCP,
	eAIUseItemType����
};
struct sFightList;
class cAttackAI
{
public:
	cAttackAI();
	
	int m_ButtonSelect=-1;
	int m_ObjSelectid=-1;
	BOOL m_bPKMode = FALSE;//��������,�ѶȽ�����
	void Reset();
	void Run();

#if !defined(ccc_date)
	void RunZhiHui(int start, int end, int mode, int select);
#endif
	void GetNeed(int start,int end);//����,����Ѫ������,Ҫ���Ѫ
	void PreRun(int start, int end);//��������
	BOOL SaveOneself(int start, int end);//�Ծ�
	
	int FindCpMaxTarget(int num=100);//Ѱ�ҵз�CP>num�Ķ���
#if !defined(ccc_date)
	int FintTarget(int i);
	int FindAtkTarget(int rate, BOOL ATKOrMagic=TRUE);
	int FindDefminTarget(int start, int end, eProPerty prop,BOOL maxormin=FALSE);
#else
	int FindAtkTarget(int ��������ڹ����ļӳ�, BOOL ATKOrMagic, int userID = -1);
	
	int FindDefminTarget(int start, int end, eProPerty prop,BOOL maxormin, int userID = -1);
	int FindDefminTarget(eProPerty prop, bool isMax){ return FindDefminTarget(m_UserID < 10 ? 10 : 0, m_UserID < 10 ? 20 : 10, prop, isMax, m_UserID); }
	int findʬ��������();
	int find��ȫ��();
	// 0�� 1�� 2�ؼ�  
	int FindUnSeal(char &isMorA);
	bool FindUnSeal(int id, char &isMorA);
#endif
	int FindUnSeal(int num = 10);
	int FindUnSeal(int start, int end);

	void AutoRunAi(int id);//,int targetid);
	void AutoRunEnemyAi(int id);
	BOOL CheckHaveState(int userid,int skillid);
	void NormalAtk();
	void Summon(int id);//�ٻ�

	void UseMagic(int id);
	void NpcTryMagic(int id);//�����Ƿ����㹻������ħ��,�����������
	void Escape(int userID);//����
	void Def(int userID);//��  
	BOOL UseItem(eAIUseItemType mode);
	BOOL CheckItem(eAIUseItemType mode);
	int m_HPLimit = 60;//1-99 HP���� 100-m_HPLimitʱ��Ѫ
	void ResetNeed();
	int m_bNeedAddHp[20];//���غϸö����Ƿ���Ҫ��Ѫ
	BOOL m_bNeedAddHpHurt[20];
	BOOL m_bNeedUnSeal[20];//���غϸö����Ƿ���Ҫ���
	BOOL m_bNeedlive[20];
	int m_bNeedAddMp[20];
	BOOL m_bBeSeal[20];//�Ƿ񱻷�
	BOOL  m_bSeal[20];//
	BOOL  m_bAtk[20];//
#if defined(ccc_date)
	BOOL  _isShiFudu[20];
#endif
	//BOOL  m_bBeLive[20];//�Ƿ񱻸���
	//BOOL m_bCure[20];//������
	//BOOL m_bCureMP[20];//����MP
	////void CoutIdleList(int start,int end);
	
	void SetUser(int userid);
	int m_UserID = -1;
	sFightList* pUserList=0;
	cObj* m_pUser=0;
	cCharacter* m_pUserPc=0;
	cPetData* m_pUserPetData=0;

	void SetTarget(int target);
	int m_TargetID=-1;
	sFightList* m_pTargetList=0;
	cObj* m_pTarget=0;
	cPetData* m_pTargetPetData=0;
	int m_FightTarget[20];
	void ZhiHui(BOOL bOut);//
private:
	void ContentLive(int start,int end);
	void ContentLive2(int start,int end);
	void ContentHP(int start, int end);
	void ContentHP2(int start, int end);
	void ContentUnSeal(int start, int end);
	void ContentUnSeal2(int start, int end);
	BOOL CheckCanSkill(int skillid);
#if defined(ccc_date)
public:
	bool isHadPetSkill(cPetData *data, vector<int> &buffSkills, vector<int> &pSkills, vector<int> &mSkills, vector<int> &m2Skills);
	bool isHadPetSkill(const vector<sSkill*> &skills, vector<int> &buffSkills, vector<int> &pSkills, vector<int> &mSkills, vector<int> &m2Skills);
private:
	int getVisibleNO(int userID, bool userTeam, bool isCheckPeopleSpecial);
	int getVisibleNO(){ return getVisibleNO(m_UserID, false, true); }
	bool runPoxueAtk();
	bool runSelfunseal();
	bool isAtkMode(){ return MyTest::getInstance()->isAtkMode(m_UserID); }
	bool isCanAtk(){ return !m_pUserPetData->m_FightProperty.cannotAttack; }
	bool isCanMag(){ return !m_pUserPetData->m_FightProperty.cannotMagic; }
	bool isCanSpec(){ return !m_pUserPetData->m_FightProperty.cannotSkill; }
	bool isPut(){ return m_pUserPetData->m_ZiZhi.m_Growing < (int)MyTest::getInstance()->putMenpaiSkills.size(); }
	bool isPutRate();
	bool isPetRate(){ return rand() % 100 < 38; }
	bool isUseOtherRate(){ return rand() % 100 < 62; }
	bool selectAtk();
	// 0����
	// 1����
	// 2״̬
	// 3����
	// 4����
	int RunPet();
	bool RunLH();
#else
	void RunPet();
#endif
	void RunDT();
	void RunHS();
	void RunNR();
	void RunFC();
	void RunLG();
	void RunWZ();
	void RunPT();
	void RunTG();
	void RunDF();
	void RunPS();
	void RunMW();
	void RunST();
	void SaveOneself2(int id);
	BOOL resurgence(int user, int target);
	void resurgence2(vector<POINT>& user, vector<POINT>& target,int targetID);
	BOOL Cure(int user, int target,BOOL toall=FALSE);
	void Cure2(vector<POINT>& tlist, int start, int end);
	void UnSeal2(vector<POINT>& tlist, int start, int end);
	BOOL UnSeal(int user, int target);

	BOOL CureMP(int user, int target, BOOL toall = FALSE);
	void CureMP2(vector<POINT>& tlist, int start, int end);
public:
	enum eEnemyType
	{
#if !defined(ccc_date)
		eET����ϵ,    //����1������
		eET��ϵ,	  //����1������
		eET��ϵ,	  //FC NR PS WZ TG
		eET��Ҫ��ϵ, // ��DT
		eETҽ��ϵ, //HS  PT Ѫ��
		eET����,
		eET����,
		eETѪ��,
		eETѪ����,
		eET����������,
		eET�����,
		eET�����,
		eET��������,
		eET���ⷨ��,
		eET������,
		eET���ٻ���,
		eET��������,
		eET�ٶ����,
		eET��Ѫ,
		eET���
#else
		// �з�����
		eET�Ͻ��33,    //����1������
		eET���鶯112,	  //����1������
		eET�ɷ�ϵ,	  //FC NR PS WZ TG
//		eET��Ҫ��ϵ, // ��DT
		eETҽ��ϵ, //HS  PT Ѫ��
//		eET����,
//		eET����,
//		eETѪ��,
		eETѪ����,
//		eET����������,
		eET�����,
		eET�����,
//		eET��������,
//		eET���ⷨ��,
//		eET������,
		eET���ٻ���,
		eET��������,
		eET�ٶ����,
		eET�ٶ����2,
		eET��ӡ����,
		eET��Ѫ,
		eET������ϵ,
		eET�ɷ�ϵ,
		eET����6,
		eET�ߵ�����113,
		eET���ޱ�46,
		eET������ɽ95,
		eET���ݻ���99,
		eET������129,
		eET��Ȫ֮Ϣ126,
		eET�����ɢ127,
		eET����120,
#endif
	};
	int FindEnemy(BOOL CheckDie,BOOL bCheckWork, vector<POINT>& out, eEnemyType type, int userid, int data = -1, int data2 = -1);//Ѱ���ض�����
#if defined(ccc_date)
	vector<int> check����(vector<POINT>& out, int user);
#endif
	enum eEnemyCorrect
	{
		eEC����
	};
	void CorrectEnemy(vector<POINT>& out,eEnemyCorrect typ);
};
class cAI
{
public:
#if !defined(ccc_date)
	int  AutoFindTarget(int userID, int SelectType);
	int  GetNear(int ID, int Num,int bLive);
#else
	int  AutoFindTarget(int userID, int SelectType, bool isCheckPeopleSpecial);
	int  GetNear(int userid, int ID, int Num,int bLive);
#endif

	int  GetNextPos(int ID, int Num, int bLive);
#if !defined(ccc_date)
	//int  GetIdle(int ID);
	BOOL RunDT(int userID);
	BOOL RunHS(int userID);
	BOOL RunFC(int userID);
	BOOL RunNR(int userID);
	BOOL RunWZ(int userID);
	BOOL RunPT(int userID);
	BOOL RunLG(int userID);
	BOOL RunTG(int userID);
	BOOL RunMW(int userID);
	BOOL RunPS(int userID);
	BOOL RunST(int userID);
	BOOL RunDF(int userID);
	BOOL RunNULL(int userID);

	int  FindDieFight(int start = 0, int end = 5);
#endif	
	
	cAttackAI m_AttackAI;
};


