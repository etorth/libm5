#pragma once
#include "_inc.h"
#include <vector>
#include <set>
#if defined(ccc_date)
using namespace std;
class MyTest
{
public:
	static MyTest* getInstance();
	void switch�ӵ㷽��();
	// Ѫ��
	bool isShowBloodBar = true;
	// ˲��
	bool isTeleporting = false;
	int juQing = 0;
	int mapSpeed = 2;
	int isClassical = 1;
	int per�ӵ� = 10;
	int perLvup = 1;
	bool isEnemyPKMode = false;
	bool isAutoAtkMode = true;
//	bool isAddPoint50 = false;
	bool isAutoBattle = false;
	bool isControl = false;
	static const int lvFor�ɽ�ͷ�� = 95;
	static const int minRoleLv = 5;
	static const int maxRoleLv = 175;
	static const int maxBabyLv = 180;
	static const int lv���������� = 25;
	static const int lvGapFromRoleAndBaby = 10;
	static const int point���� = 0;
	static const int maxXiuLian = 30;
	static const int maxSkillLv = 200;
	static const int per���� = 45;
	static const int ҩƷ���� = 5;
	std::set<int> newBabys;
	std::vector<int> putMenpaiSkills;
	std::vector<int> putPetSkills;
	string strDescTemp;
	bool isPushRole15 = false;
	std::set<string> mapNames;
	std::vector<std::string> friendNames;
	void pushZuoqi(const string &desc, unsigned long id);
	void pushZuoqiHead(const string &desc, unsigned long id);
	void pushHome(const string &desc, unsigned long id);
	void pushHomeHead(const string &desc, unsigned long id);
	void pushItem(const string &desc, unsigned long id);
	void pushItemHead(const string &desc, unsigned long id);
	void pushChat(const string &desc, unsigned long id);
	void pushOther(const string &desc, unsigned long id);
	void pushNpc(const string &desc, unsigned long id);
	void pushNpcHead(const string &desc, unsigned long id);
	void pushMpSkill(const string &desc, unsigned long id);
	void pushMpSkillHead(const string &desc, unsigned long id);
	void pushMpHead(const string &desc, unsigned long id);
	void pushBabySkill(const string &desc, unsigned long id);
	void pushBabySkillHead(const string &desc, unsigned long id);
	void pushSpecialSkill(const string &desc, unsigned long id);
	void pushSpecialSkillHead(const string &desc, unsigned long id);
	void pushFuzhuSkillHead(const string &desc, unsigned long id);
	void pushBabyHead(const string &desc, unsigned long id);
	void pushBaby(const string &desc, unsigned long id);
	void pushRoleHead(const string &desc, unsigned long id);
	void pushRole(const string &desc, unsigned long id);
	void pushRoleZuoqi(const string &desc, unsigned long id);
	void pushWeapon(const string &desc, unsigned long id);
	void pushWeaponHead(const string &desc, unsigned long id);
	void saveMyWdf();


	void pushWdf(const string &desc, unsigned long id);
	void pushWdf2(const string &desc, unsigned long id);
	void pushWdf3();
	void saveWdf();
	void saveWdf3();
	void pushTable(unsigned long id, unsigned long idNew);
	unsigned long getUid(unsigned long id);
	void pushIgnore(unsigned long id);
	int isIgnore(unsigned long id);
	// ���Բ�֪��, ��������ֻ��ҩƷ��
	void playerNormalize(int lv);
	void initControl();
	void init();
	int getBabyLv();
	// 0~161
	void useCard();
	void addMoney(int money);
	// ������PKս��
	void PK();
	void PK(int state);
	void PKinit();
	void PKover();
	void PKNpc();
	void ���׳�������ս��();
	bool isInBattle();
	void set�ɵ�(int lv);
	bool isAtkMode(int id);
	bool isSpecialOrZZ(int zz);
	// �������ɷ��� �ؼ�*10+ʯͷ
	int getDesbinOfͷ��(int e, int teji = 0);
	int getDesbinOf����(int e, int teji = 0);
	int getDesbinOf����(int e, int teji = 0);
	int getDesbinOf����(int e, int teji = 0);
	int getDesbinOf����(int e, int teji = 0);
	int getDesbinOfЬ��(int e, bool isAtk = false, int teji = 0);
	int getJinjie(int lv);
};
#endif


// 1470854			�����Թ�
// 64379937			С����
// 742230768		������1
// 85077806			������2
// 406097195		���ٽ���
// 538028226		С������
// 557996108		����«��
// 566146437		����ɽ
// 640111112		������
// 644754520		����Ұ��
// 790546186		���ٴ�
// 890606953		������
// 939562604		ʨ����
// 1248131261		ħ��կ
// 1256371635		���ƹٸ�
// 1262960812		������
// 1405279831		����ɽ
// 3551908874		�����Թ�
// 1518748497		�����Թ�2
// 1527631065		�¹�
// 2928358529		����
// 1706625738		����2
// 1761009057		������
// 1880023811		���ܵظ�
// 949968628		ս������1
// 2663553693		ս������2
// 2029784250		ս������3
// 4077106857		ս������4
// 4212547124		ս������5
// 2043826402		����
// 2073070538		��ս�볡
// 2220736812		ս��BOSS
// 2229463928		����
// 2261053509		�η�
// 2298843722		ս��1
// 2991105991		ս��2
// 3238412417		ս��3
// 2353332476		����ɽ
// 2360055652		Ů����
// 2398410866		��������
// 2463963770		������
// 2801018603		δ֪���
// 2805137540		��
// 2852135814		ս��ɽ
// 2889442616		��˿��
// 2967073802		�ﳲ
// 3007230343		�ﳲ2
// 3201585121		���䳡
// 3597537448		���ƾ���
// 3825823042		Ů���
// 3889067580		�칬
// 3928368410		���ƹ���
// 3956019824		�����Թ�5
// 4246654863		��ׯ��
// 2454059136		δ֪
