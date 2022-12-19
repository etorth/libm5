#include "global.h"

// ���ѡ��Ŀ��
// SelectType �Ƿ���������
// 0 ƽʱ�Լ�
// 1 ƽʱ����
// 2 ս���Լ�
// 3 ս������
// 4 ս���з�
// 5 ƽʱս���Լ�
// 6 ƽʱս������
// 7 ����
// 8 δ
// 9 ս������but�Լ�
#if defined(ccc_date)
int cAI::AutoFindTarget(int userID, int SelectType, bool isCheckPeopleSpecial)
{
	//�������п�ѡ��ID
	int k = 10;
	switch (SelectType)
	{
	case 2: //ֻ�ܶ��Լ�ʹ�õķ���
	case 5:
		return  userID;
	case 3: //ֻ�ܶ��ҷ�ʹ�õķ���ww
	case 6:
		if (userID < 10)k = 0;
		break;
	case 4: //�Ե���ʹ��
		if (userID > 9)	k = 0;
		break;
	}
	int existNum = 0;
	int idlist[10];
	sFightList* pList;
	int i2;
	cPetData *data = nullptr;
	g_pMainState->m_FightList[userID].m_pData->GetDateP(data);
	int peopleSpecail = data->PeopleSpecial.d1;
	for (int i = 0; i < 10; i++)
	{
		i2 = i + k;
		pList = &g_pMainState->m_FightList[i2];
		if (i2 == userID)
		{
			if (SelectType == 3 || SelectType == 6)
			{
				continue;
			}
		}
		//Ŀ���Ƿ����
		if (userID!=i2)
		if (pList->isLive)
		{
			//Ŀ���Ƿ����
			if (!pList->CheckDie())
			{
				cPetData *data2 = nullptr;
				pList->m_pData->GetDateP(data2);
				if (!isCheckPeopleSpecial || (isCheckPeopleSpecial && peopleSpecail >= data2->PeopleSpecial.d2))
				{
					idlist[existNum] = i2;
					existNum += 1;
				}
			}
		}
	}
	//
	if (SelectType == 3 || SelectType == 6)
	{
		if (0 == existNum)return userID;
	}
	else
	if (0 == existNum)return -1;
	g_pMainState->m_InterfaceDoor.m_TimeShiCheng.UpdateTime();
	int select = idlist[rand() % existNum];

	return select;
}

int cAI::GetNextPos(int ID, int Num, int bLive)
{
	if (Num < 0 || Num >19)
	{
		ERRBOX(Num);
		return -1;
	}
	int start, end;
	if (ID < 10)start = 0;
	else start = 10;
	end = start + 10;
	for (int i = start; i < end; i++)
	{
		sFightList& list = g_pMainState->m_FightList[i];
		switch (bLive)
		{
		case 0://ֻ�ҿ�λ
			if (!list.isLive)return i;
			break;
		case 1://ֻ�һ���
			if ((0 == list.isLive) || list.CheckDie())
			{
			}
			else return i;
			break;
		case 2://ֻҪ���ھ���
			if (list.isLive)
			{
				return i;
			}
			break;
		}
	}
	return -1;
}

int cAI::GetNear(int usetId, int ID, int Num,int bLive)
{
	if (Num < 0 || Num >19)
	{
		ERRBOX(Num);
		return -1;
	}
	int start, end;
	if (ID < 10)start = 0;
	else start = 10;
	end =start+ 10;

	int xpos = g_pMainState->m_pFightState->m_xPosList[ID];
	int ypos = g_pMainState->m_pFightState->m_yPosList[ID];
	int gaplist[10];
	int idlist[10];
	for (int i = 0; i < 10; i++)
	{
		idlist[i] = start+i;
	}
	int startgap = 0;
	cPetData *data = nullptr;
	g_pMainState->m_FightList[usetId].m_pData->GetDateP(data);
	int peopleSpecail = data->PeopleSpecial.d1;
	for (int i = start; i < end; i++)
	{
		sFightList& list = g_pMainState->m_FightList[i];
		switch (bLive)
		{
		case 0://ֻ�ҿ�λ
			if (list.isLive)
			{
				gaplist[startgap] = 999999;;
				startgap += 1;	
				continue;
			}
			break;
		case 1://ֻ�һ���
			if ((0 == list.isLive) || list.CheckDie())
			{
				gaplist[startgap] = 999999;;
				startgap += 1;
				continue;
			}
			break;
		case 2://ֻҪ���ھ���
			if (!list.isLive)
			{
				gaplist[startgap] = 999999;;
				startgap += 1;
				continue;
			}
			break;
		case 3: // ���ü��Ļ���
			if ((0 == list.isLive) || list.CheckDie())
			{
				gaplist[startgap] = 999999;;
				startgap += 1;
				continue;
			}
			cPetData *data2 = nullptr;
			g_pMainState->m_FightList[i].m_pData->GetDateP(data2);
			if (peopleSpecail < data2->PeopleSpecial.d2)
			{
				gaplist[startgap] = 999999;;
				startgap += 1;
				continue;
			}
			break;
		}
		
		int xpos2 = g_pMainState->m_pFightState->m_xPosList[i];
		int ypos2 = g_pMainState->m_pFightState->m_yPosList[i];
		gaplist[startgap] = abs(xpos - xpos2) + ((abs(ypos - ypos2))<<1);
		startgap += 1;
	}
	int pa, pb;
	for (int a = 0; a < startgap-1; a++)
	for (int b = a + 1; b<startgap; b++)
	{
		pa = gaplist[a];
		pb = gaplist[b];
		if (pa>pb)//ǰ�����ں���
		{
			swap(gaplist[a], gaplist[b]);
			swap(idlist[a], idlist[b]);
		}
	}//����������ǰλ��YС����ǰ��
	if (999999 == gaplist[Num])return -1;
	return idlist[Num];

}


void cAttackAI::Escape(int userID)
{
// 	if (MyTest::getInstance()->isForceEspace)
// 	{
// 		g_pMainState->m_pFightState->m_bEscape = TRUE;
// 		return;
// 	}

	sFightList& list = g_pMainState->m_FightList[userID];
	list.m_WorkType = WORKTYPE_MAGIC;
	list.m_SkillSelect.Lv = 0;
	list.m_SkillSelect.SkillID = 1006;
	list.targetID = userID;
	list.m_SkillSelect.TargetID = userID;
}

void cAttackAI::Def(int userID)
{
	if (!g_pMainState->m_FightList[userID].isLive)return;
	cPetData* petdata;
	g_pMainState->m_FightList[userID].m_pData->GetDateP(petdata);
	if (petdata->m_FightProperty.cannotAll)return;
//	g_pMainState->m_AI.m_AttackAI.m_FightTarget[userID] = userID;
	sBuff buf;
	buf.times = 1;
	g_pMainState->m_SkillManager.SetDateBuffUp(userID, userID, 1002, buf);
	g_pMainState->m_FightList[userID].m_WorkType = -2;
}

BOOL cAttackAI::UseItem(eAIUseItemType mode)
{
	if (m_TargetID == -1)return FALSE;
	int ItemOwnerID = m_UserID;
	if (g_pMainState->m_FightList[ItemOwnerID].m_pData->m_IndexType == INDEXTYEP_PET)
	{
		if ((m_UserID % 10) >= 5)
			ItemOwnerID = m_UserID - 5;
		if (g_pMainState->m_FightList[ItemOwnerID].m_pData->m_IndexType == INDEXTYEP_PET)
		{
			return FALSE;
		}
	}
	cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[ItemOwnerID].m_pData->m_pIndex;
	if (!pc)
	{
		return FALSE;
	}
	sFightList& list = g_pMainState->m_FightList[m_UserID];
	if (pc->m_PCData.m_Item[mode].GetNum() < 2)
		return FALSE;
	list.m_ItemSelectID = mode;
	list.m_SkillSelect.SkillID = 1003;
	if (mode == eAIUseItemType����)
		list.m_SkillSelect.SkillID = 1005;
	list.m_SkillSelect.Lv = 0;
	list.m_SkillSelect.TargetID = m_TargetID;
	list.m_WorkType = WORKTYPE_MAGIC;


	int start, end;
	if (m_TargetID < 10)start = 0;
	else start = 10;
	end = start + 10;
	switch (mode)
	{
	case eAIUseItemTypeHP:
		m_bNeedAddHp[m_TargetID] -= 50;
		break;
	case eAIUseItemTypeHPALL:
		if (1)
		{
			for (int i = start; i < end;i++)
				m_bNeedAddHp[m_TargetID] -= 30;
		}
		break;
	case eAIUseItemTypeMP:
		m_bNeedAddMp[m_TargetID] = 0;
		break;
	case eAIUseItemTypeMPALL:
		if (1)
		{
			for (int i = start; i < end; i++)
				m_bNeedAddMp[m_TargetID] = 0;
		}
		break;
	case eAIUseItemTypelive:
		m_bNeedlive[m_TargetID] = 0;
		break;
	case eAIUseItemTypeUnseal:
		m_bNeedUnSeal[m_TargetID] = 0;
		break;
	case eAIUseItemType����:
		m_bAtk[m_TargetID] += 20;
		break;
	}
	return TRUE;
	
	
}

// 
// 
// int cAI::FindDieFight(int start /*= 0*/, int end /*= 5*/)
// {
// 
// 
// 	for (int i = start; i < end; i++)
// 	{
// 		if (g_pMainState->m_FightList[i].isExist)
// 		if (g_pMainState->m_FightList[i].CheckDie())
// 		{
// 			return i;
// 		}
// 	}
// 	return -1;
// }
// 


int cAttackAI::getVisibleNO(int userID, bool our, bool isCheckPeopleSpecial)
{
	int star;
	if (our && userID < 10 || (!our && userID >= 10))
	{
		star = 0;
	}
	else
	{
		star = 10;
	}
	int num = 0;
	for (int i = star; i < star + 10; ++i)
	{
		if (g_pMainState->m_FightList[i].isLive && !g_pMainState->m_FightList[i].CheckDie())
		{
			cPetData *data = nullptr;
			g_pMainState->m_FightList[userID].m_pData->GetDateP(data);
			cPetData *data2 = nullptr;
			g_pMainState->m_FightList[i].m_pData->GetDateP(data2);
			if (data && data->PeopleSpecial.d1 < data2->PeopleSpecial.d2)
			{
				continue;
			}
			++num;
		}
	}
	return num;
}

bool cAttackAI::runPoxueAtk()
{
	if (m_pUserPetData->m_ProPertyAtk >= m_pUserPetData->m_LV * 3)
	{
		if (!m_pUserPetData->m_FightProperty.cannotSkill)
		{
			if (CheckCanSkill(3034))
			{
				if (m_TargetID < 0)
				{
					SetTarget(FindAtkTarget(300, TRUE, m_UserID));
				}
				if (m_TargetID >= 0)
				{
					UseMagic(3034);
					return true;
				}
			}
		}
		if (!m_pUserPetData->m_FightProperty.cannotAttack)
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(100, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				NormalAtk();
				return true;
			}
		}
	}
	return false;
}

bool cAttackAI::runSelfunseal()
{
	if (isCanAtk() && isPut() && selectAtk())
	{
		return true;
	}
	if (m_pUserPetData->m_FightProperty.cannotMagic || m_pUserPetData->m_FightProperty.cannotSkill)
	{
		if (!m_pUserPetData->PeopleSpecial.d2)
		{
			if (!m_pUserPetData->m_FightProperty.cannotUseItem)
			{
				if (m_bNeedUnSeal[m_UserID])
				{
//					if (CheckItem(eAIUseItemTypeUnseal))
					{
						SetTarget(m_UserID);
						if (UseItem(eAIUseItemTypeUnseal))
						{
							m_bNeedUnSeal[m_UserID] = FALSE;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool cAttackAI::isPutRate()
{
	if (isAtkMode())
	{
		return (isCanAtk() && isPut() && rand() % 100 < 15) || !isCanMag();
	}
	return isCanAtk() && isPut() && !isCanMag();
}

bool cAttackAI::selectAtk()
{
	if (!isCanAtk())
	{
		return false;
	}
	if (m_TargetID < 0)
	{
		SetTarget(FindAtkTarget(100, TRUE, m_UserID));
	}
	if (m_TargetID >= 0)
	{
		NormalAtk();
		return true;
	}
	return false;
}

bool cAttackAI::RunLH()
{
	int self = m_UserID < 10 ? 10 : 0;
	vector<POINT>out;
	FindEnemy(TRUE, FALSE, out, eET�ɷ�ϵ, self);
	if (out.size() > 2 && !m_pUser->CheckHaveState(3025) && CheckCanSkill(3025))
	{
		SetTarget(m_UserID);
		UseMagic(3025);
		return true;
	}
	return false;
}

void cAttackAI::RunDT()
{
	SetTarget(m_FightTarget[m_UserID]);
	bool isTasrget = (m_TargetID >= 0);
	int self = m_UserID < 10 ? 10 : 0;
	auto runPoxue = [&]()
	{
		if (isCanSpec() && CheckCanSkill(3034))
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(300, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(3034);
				return true;
			}
		}
		return false;
	};

	auto isBlood10 = [&]()
	{
		return m_pUserPetData->m_HP > m_pUserPetData->m_HPMax.GetData() / 10;
	};
	
	auto isPofuBlood = [&]()
	{
		return m_pUserPetData->m_ATK.GetData() - m_pTargetPetData->m_DEF.GetData() > m_pTargetPetData->m_HP;
	};

	auto runPofuOfNoTarget = [&]()
	{
		if (isBlood10())
		{
			SetTarget(FindAtkTarget(150, TRUE, m_UserID));
			if (m_TargetID >= 0)
			{
				UseMagic(7);
				return true;
			}
		}
		return false;
	};

	auto runHengsao = [&]()
	{
		if (isBlood10())
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(400, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(0);
				return true;
			}
		}
		return false;
	};


	if (m_TargetID >= 0)
	{
		if (isCanMag())
		{
			if (isPofuBlood() && isBlood10() && getVisibleNO() > 2)
			{
				return UseMagic(7);
			}
			if (!isAtkMode() && runHengsao())
			{
				return;
			}
			if (isBlood10() && getVisibleNO() > 2)
			{
				return UseMagic(7);
			}
		}
		if (isCanAtk() && isPut() && selectAtk())
		{
			return;
		}
		if (runPoxue())
		{
			return;
		}
	}

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (m_TargetID < 0 && isCanMag())
		{
			vector<POINT> out;
			if (g_pMainState->m_pFightState->_turn < 5)
			{
				FindEnemy(TRUE, FALSE, out, eET�ɷ�ϵ, m_UserID);
				auto out2 = check����(out, m_UserID);
				if (!out2.size() && rand() % 100 < 20)
				{
					out.clear();
					FindEnemy(TRUE, FALSE, out, eET����6, self);
					out2 = check����(out, m_UserID);
					if (out2.size())
					{
						SetTarget(out2.front());
						return UseMagic(6);
					}
				}
			}

			FindEnemy(TRUE, FALSE, out, eET�ɷ�ϵ, self);
			if (out.size() > 2 && !m_pUser->CheckHaveState(8) &&
				!m_pUser->CheckHaveState(113) &&
				!m_pUser->CheckHaveState(2097) &&
				!m_pUser->CheckHaveState(3024) && 
				!m_pUser->CheckHaveState(3025))
			{
				if (isUseOtherRate())
				{
					SetTarget(m_UserID);
					return UseMagic(8);
				}
			}
		}
	}
	if (runPoxue())
	{
		return;
	}
	if (isPutRate() && selectAtk())
	{
		return;
	}
	int t = m_TargetID;
	if (RunPet() == 3 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag() && getVisibleNO() > 2)
	{
//		if (m_UserID < 10 || (m_UserID >= 10 && rand() % 100 < 70))
		if ((isAtkMode() && (m_UserID < 10 || (m_UserID >= 10 && rand() % 100 < 70))) || (!isAtkMode() && isPofuBlood()))
		{
			if (runPofuOfNoTarget())
			{
				return;
			}
		}
	}
	if (isCanMag() && runHengsao())
	{
		return;
	}

	if (runSelfunseal())
	{
		return;
	}
	if (!m_pUser->CheckHaveState(0) && !m_pUser->CheckHaveState(7))
	{
		return Def(m_UserID);
	}
}
void cAttackAI::RunNR()
{
	SetTarget(m_FightTarget[m_UserID]);
	int tOld = m_TargetID;
// 	BOOL bConduct = FALSE;
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
// 		SetTarget(m_FightTarget[m_UserID]);
// 		bConduct = TRUE;
// 	}
// 	else SetTarget(-1);

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (isCanMag())
		{
			//���ָ��Ŀ�������²���Ŀ��û�б��� ���Է�ӡĿ��
			char isM = -1;
			if (m_TargetID < 0 || (m_TargetID >= 0 && !FindUnSeal(m_TargetID, isM)))
			{
				SetTarget(FindUnSeal(isM));
			}
			if (m_TargetID >= 0 && (isM == 0 || isM == 1))
			{
				m_bSeal[m_TargetID] = TRUE;
				return UseMagic(54);
			}
		}

// 		if (!m_bSeal[m_TargetID])
// 		{
// 			if (!m_pTargetPetData->m_FightProperty.cannotMagic)
// 			{
// 				m_bSeal[m_TargetID] = TRUE;
//  				if (m_pUserPetData->m_LV > 129)
//  				{
//  					return UseMagic(59);
//  				}
// 				return UseMagic(54);
// 			}
// 		}

	}
// 	if ((MyTest::getInstance()->isAtkMode(m_UserID) || (!MyTest::getInstance()->isAtkMode(m_UserID) && rand() % 100 < 60)) && !m_pUserPetData->m_FightProperty.cannotUseItem)
// 	{//ʹ�ð���
// 		if (m_TargetID < 0)
// 		{
// 			SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, true));
// 		}
// 		if (m_TargetID >= 0 && UseItem(eAIUseItemType����))
// 		{
// 			return;
// 		}
// 	}

	int told = m_TargetID;
	m_TargetID = tOld;
	if (isPutRate() && selectAtk())
	{
		return;
	}
	m_TargetID = told;
	
	int t = m_TargetID;
	if (RunPet() == 3 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag() && rand() % 100 < 30)
	{
		if (m_TargetID < 0)
		{
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		}
		if (m_TargetID >= 0)
		{
			return UseMagic(50);
		}
	}
	if (!m_pUserPetData->m_FightProperty.cannotUseItem)
	{
		if (m_TargetID < 0)
		{
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		}
		if (m_TargetID >= 0 && UseItem(eAIUseItemType����))
		{
			return;
		}
	}

// 	if (!m_pUserPetData->m_FightProperty.cannotMagic)
// 	{
// 		if (m_TargetID < 0)
// 		{
// 			SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, true));
// 		}
// 		if (m_TargetID >= 0)
// 		{
// 			return UseMagic(50);
// 		}
// 	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
	
}
void cAttackAI::RunFC()
{
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 	SetTarget(m_FightTarget[m_UserID]);
// 	}
// 	else SetTarget(-1);
// 	if (m_pUserPetData->m_AiLv > 80)
// 	if (!m_pUserPetData->m_FightProperty.cannotSkill)
// 	{
// 		if (m_pUserPetData->m_StrongLv > 70)
// 		{//Ц��
// 
// 			if (m_FightTarget[m_UserID] == -1)
// 			{
// 				int target = FindCpMaxTarget();
// 				if (target > -1)
// 				{
// 					SetTarget(target);
// 
// 					if (m_pTarget->m_IndexType == INDEXTYEP_CHARACTER)
// 					{
// 						cCharacter* pc = (cCharacter*)m_pTarget->m_pIndex;
// 						if (pc->m_PCData.m_CP > 100)
// 						{
// 
// 							if (CheckCanSkill(3016))return UseMagic(3016);//Ц��
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}

	auto runLuoleifu = [&]()
	{
		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			if (m_TargetID < 0)
			{
//				SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, true));
				SetTarget(FindAtkTarget(100, FALSE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(28);
				return true;
			}
		}
		return false;
	};

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		int self = m_UserID < 10 ? 10 : 0;
		if (isCanMag())
		{
			if (m_TargetID < 0)
			{
				vector<POINT> out;
				FindEnemy(TRUE, FALSE, out, eET�ɷ�ϵ, self);
				if (out.size() > 2 && !m_pUser->CheckHaveState(26) && !m_pUser->CheckHaveState(113))
				{
					if (isUseOtherRate())
					{
						SetTarget(m_UserID);
						return UseMagic(26);
					}
				}
			}
			char isM = -1;
			if (m_TargetID < 0 || (m_TargetID >= 0 && !FindUnSeal(m_TargetID, isM)))
			{
				SetTarget(FindUnSeal(isM));
			}
			if (m_TargetID >= 0 && isM >= 0)
			{
				m_bSeal[m_TargetID] = TRUE;
				return UseMagic(isM == 1 ? 15 : (isM == 0 ? 21 : 17));
			}
			vector<POINT> out;
			FindEnemy(TRUE, FALSE, out, eET��ӡ����, self, 27);
			auto out2 = check����(out, m_UserID);
			if (out2.size() > 2)
			{
				SetTarget(out2.front());
				return UseMagic(27);
			}
		}
	}
// 		if (m_pUserPetData->m_LV >= 120 && !m_pUser->CheckHaveState(26))
// 		{
// 			SetTarget(m_UserID);
// 			return UseMagic(26);
// 		}

	int t = m_TargetID;
	if (RunPet() == 4 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		if (runLuoleifu())
		{
			return;
		}
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
	

// 			if (target2 == -1)
// 			{//�з�ȫ��������.........
// 				if (m_bPKMode)
// 				{
// 					if (m_pUserPetData->m_LV>129)
// 					{
// 						if (!m_pUser->CheckHaveState(26))
// 							return UseMagic(26);
// 						if (!m_pTarget->CheckHaveState(27))
// 							return UseMagic(27);
// 						return defense(m_UserID);
// 					}
// 				}
// 				else
// 					return UseMagic(28);
// 			}
// 			SetTarget(target2);
// 		}
// 	
// 		if (m_FightTarget[m_UserID] == -1)
// 		{
// 			if (!m_pTarget->CheckHaveState(15))
// 				return UseMagic(15);
// 		}
// 		else
// 		{
// 			//����ҷ��������͵Ķ໹�Ƿ����͵Ķ�
// 			int ouratknum = 0;
// 			int start, end;
// 			if (m_UserID < 10)start = 0;
// 			else start = 10;
// 			end = start + 10;
// 			cPetData* pPetdata;
// 			for (int i = start; i < end; i++)
// 			{
// 				g_pMainState->m_FightList[i].m_pData->GetDateP(pPetdata);
// 				if (pPetdata->m_AddPoint.atk> 2)
// 				{
// 					ouratknum += 1;
// 					continue;
// 				}
// 				if (pPetdata->m_AddPoint.mp > 2)
// 				{
// 					ouratknum -= 1;
// 					continue;
// 				}
// 			}
// 			if (ouratknum > 1)
// 			{
// 				return UseMagic(20);
// 			}
// 			else return UseMagic(14);
// 		}
// 		if (!m_pUserPetData->m_FightProperty.cannotUseItem)
// 		{
// 			if (CheckItem(eAIUseItemTypeMP)) { UseItem(eAIUseItemTypeMP); return; }
// 			if (CheckItem(eAIUseItemTypeMPALL)) { UseItem(eAIUseItemTypeMPALL); return; }
// 		}
// 	}else
// 	if (!m_pUserPetData->m_FightProperty.cannotUseItem)
// 	{
// 		if (CheckItem(eAIUseItemTypeUnseal)){ UseItem(eAIUseItemTypeUnseal); return; }
// 	}
}
void cAttackAI::RunHS()
{
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 		SetTarget(m_FightTarget[m_UserID]);
// 	}
// 	else SetTarget(-1);
	//��˫ר��

		auto runjjyy = [&]()
		{
			if (!m_pUserPetData->m_FightProperty.cannotMagic)
			{
				if (m_TargetID < 0)
				{
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
				}
				if (m_TargetID >= 0)
				{
					UseMagic(31);
					return true;
				}
			}
			return false;
		};

	if (!isAtkMode())
	{
		//ʹ�÷���
		vector<POINT> tList;

		auto hf = [&](int i)
		{
			//��ջ���
			int rr = FindEnemy(TRUE, FALSE, tList, eET�Ͻ��33, m_UserID, 33);
			if (rr > i && tList.size())
			{
				SetTarget(tList[0].x);
				UseMagic(33);
				return true;
			}
			return false;
		};

		int self = m_UserID < 10 ? 10 : 0;
		auto ht = [&](int i)
		{
			//���Է�����
			FindEnemy(TRUE, FALSE, tList, eET������ϵ, self);
			if (tList.size() >= 2)
			{
				tList.clear();
				//��ջ���
				FindEnemy(TRUE, FALSE, tList, eET�����, m_UserID, 35);
				if (tList.size() > i)
				{
					SetTarget(tList[0].x);
					UseMagic(35);
					return true;
				}
			}
			return false;
		};
		if (isCanMag())
		{
			if (hf(2))
			{
				return;
			}
		}

		if (isCanSpec() && RunLH())
		{
			return;
		}

		if (isCanMag())
		{
			if (ht(2))
			{
				return;
			}

			// ���ޱ�
			FindEnemy(TRUE, FALSE, tList, eET���ޱ�46, m_UserID, 46);
			if (tList.size())
			{
				SetTarget(tList[0].x);
				return UseMagic(46);
			}

			//Τ�ӻ���
			FindEnemy(TRUE, FALSE, tList, eET������ϵ, m_UserID, 34);
			if (tList.size() > 2)
			{
				SetTarget(tList[0].x);
				return UseMagic(34);
			}

			if (hf(0))
			{
				return;
			}

			if (ht(0))
			{
				return;
			}
		}
	}
	int t = m_TargetID;
	if (RunPet() == 4 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		if (runjjyy())
		{
			return;
		}
	}

	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
}
void cAttackAI::RunLG()
{
	if (!isAtkMode() && isCanSpec() && RunLH())
	{
		return;
	}
	int t = m_TargetID;
	if (RunPet() == 4 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (m_FightTarget[m_UserID] >= 0)
	{
		SetTarget(m_FightTarget[m_UserID]);
	}
	else
	{
		SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
	}
	if (m_TargetID >= 0 && !m_pUserPetData->m_FightProperty.cannotMagic)
	{
		int n = getVisibleNO();
		if (n > 2)
		{
			if (m_UserID >= 10 && rand() % 100 < 20)
			{
				return UseMagic(88);
			}
			return UseMagic(80);
		}
		return UseMagic(88);
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
	
// 	int start, end;
// 	if (m_UserID<10)start = 10;
// 	else start = 0;
// 	end = start + 10;
// 	switch (g_pMainState->GetLiveNum(start, end))
// 	{
// 	case 1://����
// 		if (m_pUserPetData->m_AiLv > 90)
// 		if (m_pUserPetData->CheckHavePetSkill(2101))
// 		{
// 			return UseMagic(2101);
// 		}
// 		return UseMagic(79);
// 		break;
// 	case 2://����
// 		if (m_pUserPetData->m_LV > 109)
// 			return UseMagic(88);
// 	default://����
// 		return UseMagic(80);
// 		break;
// 	}
}
void cAttackAI::RunTG()
{
	// 	if (m_FightTarget[m_UserID] > -1)
	// 	{
	SetTarget(m_FightTarget[m_UserID]);
	// 	}
	// 	else SetTarget(-1);
	// 	if (!m_pUserPetData->m_FightProperty.cannotSkill)
	// 	{
	// 	}

	auto runLeitingwanjun = [&]()
	{
		if (m_pUserPetData->m_ProPertyMag >= m_pUserPetData->m_ProPertyAtk)
		{
			if (m_TargetID < 0)
			{
//				SetTarget(FindDefminTarget(eProPerty����, false));
				SetTarget(FindAtkTarget(100, FALSE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(74);
				return true;
			}
		}
		else
		{
			if (m_TargetID < 0)
			{
//				SetTarget(FindDefminTarget(eProPerty����, false));
				SetTarget(FindAtkTarget(100, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(71);
				return true;
			}
		}
		return false;
	};

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (isCanMag())
		{
			if (rand() % 100 < 20)
			{
				if (m_TargetID < 0)
				{
					SetTarget(FindDefminTarget(eProPerty��Ѫ, TRUE));
				}
				if (m_TargetID >= 0 && m_pTargetPetData->m_HP > m_pUserPetData->m_LV * 50 && m_pTargetPetData->m_HP > 6000)
				{
					return UseMagic(72);
				}
			}
			char isM = -1;
			if (m_TargetID < 0 || (m_TargetID >= 0 && !FindUnSeal(m_TargetID, isM)))
			{
				SetTarget(FindUnSeal(isM));
			}
			if (m_TargetID >= 0 && isM >= 0)
			{
				m_bSeal[m_TargetID] = TRUE;
				return UseMagic(isM == 1 ? 68 : (isM == 0 ? 69 : 67));
			}
		}
	}
	int t = m_TargetID;
	int p = RunPet();
	if ((p == 3 || p == 4) && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		if (runLeitingwanjun())
		{
			return;
		}
	}

	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
// 
// 	if (!m_pUserPetData->m_FightProperty.cannotMagic)
// 	{
// 		if (g_pMainState->m_FightList[10].isExist)
// 		{
// 			cPetData* ppetdata;
// 			g_pMainState->m_FightList[10].m_pData->GetDateP(ppetdata);
// 			if (ppetdata->m_HP > m_pUserPetData->m_LV * 200)
// 			{
// 				SetTarget(10);
// 				if (!CheckCanSkill(72))
// 				{
// 					SetTarget(m_UserID);
// 					if (CheckItem(eAIUseItemTypeMP)) { UseItem(eAIUseItemTypeMP); return; }
// 					if (CheckItem(eAIUseItemTypeMPALL)){ UseItem(eAIUseItemTypeMPALL); return; }
// 
// 					if (m_pUserPetData->m_ProPertyMag >= m_pUserPetData->m_LV * 2)//ħ�칬
// 						return UseMagic(74);
// 					return defense(m_UserID);
// 				}
// 				return UseMagic(72);
// 			}
// 		}
// 		if (m_pUserPetData->m_ProPertyMag >= m_pUserPetData->m_LV * 2)//���칬
// 		{
// 			if (m_FightTarget[m_UserID] == -1)
// 				SetTarget(FindAtkTarget(130));
// 			return  UseMagic(74);
// 		}
// 		else
// 		{
// //			if (m_pUserPetData->m_LV > 129)
// 			{
// 				if (m_FightTarget[m_UserID] == -1)
// 					SetTarget(FindAtkTarget(110,FALSE));
// 				return UseMagic(74);
// 			}
// //			else
// 			{
// 				if (m_FightTarget[m_UserID] == -1)
// 				{
// 					int start, end;
// 					if (m_UserID < 10)start = 10;
// 					else start = 0;
// 					end = start + 10;
// 					SetTarget(FindDefminTarget(start,end,eProPerty��Ѫ,TRUE));
// 				}
// 				if (m_pTargetPetData->m_HP > m_pUserPetData->m_LV * 200)
// 					return UseMagic(71);
// 				else
// 				{
// 					m_bSeal[m_TargetID] = TRUE;
// 					return UseMagic(68);
// 				}
// 			}
// 		}
// 	}
// 	if (!m_pUserPetData->m_FightProperty.cannotMagic)
// 	{
// // 		if (m_pUserPetData->m_AddPoint.atk > 2)//���칬
// // 		{
// // 			if (m_FightTarget[m_UserID] == -1)
// // 				SetTarget(FindAtkTarget(100));
// // 			return NormalAtk();
// // 
// // 		}
// 
// 		if (m_pUserPetData->m_ProPertyMag >= m_pUserPetData->m_LV * 2)//���칬
// 		{
// 			if (m_FightTarget[m_UserID] == -1)
// 				SetTarget(FindAtkTarget(130));
// 			return  UseMagic(74);
// 		}
// 	}
// 	defense(m_UserID);
}
void cAttackAI::RunWZ()
{	
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 	SetTarget(m_FightTarget[m_UserID]);
// 	}
// 	else SetTarget(-1);
	auto runYanyujianfa = [&]()
	{
		if (m_pUserPetData->m_HP > m_pUserPetData->m_HPMax.GetData() / 10)
		{
			if (m_TargetID < 0)
			{
//				SetTarget(FindDefminTarget(eProPerty����, false));
				SetTarget(FindAtkTarget(200, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(97);
				return true;
			}
		}
		return false;
	};

	auto runPiaomiaoshi = [&]()
	{
		if (m_TargetID < 0)
		{
//			SetTarget(FindDefminTarget(eProPerty����, false));
			SetTarget(FindAtkTarget(100, TRUE, m_UserID));
		}
		if (m_TargetID >= 0)
		{
			UseMagic(98);
			return true;
		}
		return false;
	};

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (isCanMag())
		{
			char isM = -1;
			if (m_TargetID < 0 || (m_TargetID >= 0 && !FindUnSeal(m_TargetID, isM)))
			{
				SetTarget(FindUnSeal(isM));
			}
			else
			{
				isM = 0;
			}
			if (m_TargetID >= 0 && isM >= 0)
			{
				m_bSeal[m_TargetID] = TRUE;
				return UseMagic(89);
			}
		}
	}
	int t = m_TargetID;
	if (RunPet() == 3 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		int n = getVisibleNO();
		if (m_TargetID >= 0 || n < 3 || (m_UserID >= 10 && rand() % 100 < 30))
		{
			if (runYanyujianfa())
			{
				return;
			}
			
		}
		if (runPiaomiaoshi())
		{
			return;
		}
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
	
// 		m_bSeal[m_TargetID] = TRUE;
// 		if (m_pUserPetData->m_ProPertyAtk >= m_pUserPetData->m_LV * 2)//�ǲ��ǽ���ׯ
// 		{
// 			int n = g_pMainState->GetLiveNum(m_UserID < 10 ? 10 : 0, m_UserID < 10 ? 20 : 10);
// 			if (n > 2 || (n <= 2 && (rand() & n) > 0))
// 			{
// 				SetTarget(FindDefminTarget(m_UserID < 10 ? 10 : 0, m_UserID < 10 ? 20 : 10, eProPerty��Ѫ, TRUE));
// 				return UseMagic(98);
// 			}
// 			else if (m_pUserPetData->m_HP > m_pUserPetData->m_HPMax.GetData() * 50 / 100)
// 			{//����
// 				if (m_TargetID == -1)SetTarget(FindAtkTarget(200));
// 				if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 				if (m_pTargetPetData->m_HP < m_pUserPetData->m_ATK.GetData() - m_pTargetPetData->m_DEF.GetData())
// 					return NormalAtk();
// 				return UseMagic(97);
// 			}
// 			else
// 			{
// 				//����֮Ȫ
// 				if (m_pUser->CheckHaveState(91))
// 				{
// 					SetTarget(m_UserID);
// 					return UseMagic(91);
// 				}
// 				else return NormalAtk();
// 			}
// 		}
// 		if (m_TargetID == -1)
// 		{
// 			int start, end;
// 			if (m_UserID < 10)start = 11;
// 			else start = 1;
// 			end = start + 9;
// 			if (m_bPKMode)//�չ�Ǭ���ڷ�PKʱ�޷�������
// 			{
// 				start -= 1;
// 				end -= 5;
// 			}
// 			int target2= FindUnSeal(start, end);
// 			if (target2 == -1)
// 			{
// 				SetTarget(m_UserID);
// 				if (m_pUser->CheckHaveState(91))return UseMagic(91);
// 				SetTarget(FindAtkTarget(200));
// 				if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 				if (m_pTargetPetData->m_HP < m_pUserPetData->m_ATK.GetData() - m_pTargetPetData->m_DEF.GetData())
// 					return NormalAtk();
// 				return UseMagic(97);
// 			}
// 			SetTarget(target2);
// 		}
// 		m_bSeal[m_TargetID] = TRUE;
// 		return UseMagic(89);//����
// 	}
// 	
// 	if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 	{
// 		if (m_pUserPetData->m_AddPoint.atk > 2)
// 		{
// 			if (m_TargetID == -1)SetTarget(FindAtkTarget(100));
// 			return NormalAtk();
// 		}
// 	}
// 
// 	if (!m_pUserPetData->m_FightProperty.cannotUseItem)
// 	{
// 		if (CheckItem(eAIUseItemTypeHP)){ UseItem(eAIUseItemTypeHP); return; }
// 	}
// 	return defense(m_UserID);

}
void cAttackAI::RunPT()
{
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 	SetTarget(m_FightTarget[m_UserID]);
// 	}
// 	else SetTarget(-1);
// 	if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 	{
// 	}
// 	if (!m_pUserPetData->m_FightProperty.cannotSkill)
// 	{
// 	}

	auto runWuxing = [&]()
	{
		if (m_TargetID < 0)
		{
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		}
		if (m_TargetID >= 0)
		{
			UseMagic(105 + rand() % 5);
			return true;
		}
		return false;
	};

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
	}
	int self = m_UserID < 10 ? 10 : 0;
	if (!isAtkMode() && isCanMag())
	{
		vector<POINT> outMself;
		FindEnemy(TRUE, FALSE, outMself, eET�ɷ�ϵ, self);

		vector<POINT> outMuser;
		FindEnemy(TRUE, FALSE, outMuser, eET�ɷ�ϵ, m_UserID);

		vector<POINT> outLd;
		int rr = FindEnemy(TRUE, FALSE, outLd, eET���鶯112, m_UserID, 112);
		auto out2 = check����(outLd, m_UserID);
// 		if (out2.size() < rr)
// 		{
// 			rr = out2.size();
// 		}

		if (outMself.size() > 2 || outMuser.size()/* || rr > 2*/)
		{
			if (out2.size())
			{
				SetTarget(out2.front());
				return UseMagic(112);
			}
		}

		vector<POINT> out;
		FindEnemy(TRUE, FALSE, out, eET�ߵ�����113, m_UserID, 113);
		auto out3 = check����(out, m_UserID);
		if (out3.size() && outMself.size())
		{
			SetTarget(out3.front());
			return UseMagic(113);
		}

		if (out2.size())
		{
			SetTarget(out2.front());
			return UseMagic(112);
		}
		if (runWuxing())
		{
			return;
		}
	}	
	int t = m_TargetID;
	if (RunPet() == 4 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		if (runWuxing())
		{
			return;
		}
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
}
void cAttackAI::RunDF()
{
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 	SetTarget(m_FightTarget[m_UserID]);
	int tOld = m_TargetID;
// 	}
// 	else SetTarget(-1);
// 	if (!m_pUserPetData->m_FightProperty.cannotSkill)
// 	{
// 		if ((!m_pUserPetData->m_FightProperty.cannotSkill) && m_pUserPetData->m_AiLv > 90)
// 		{
// 			if (m_pUserPetData->m_ProPertyAtk >= m_pUserPetData->m_LV * 2)//���ظ�
// 			{
// 				if (CheckCanSkill(3034))
// 				{
// 					if (m_FightTarget[m_UserID] == -1)
// 						SetTarget(FindAtkTarget(200));
// 					return UseMagic(3034);
// 				}
// 			}
// 		}
// 	}
// 	if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 	{
// 		if (m_pUserPetData->m_AddPoint.atk > 2)//���ظ�
// 		{
// 			if (m_FightTarget[m_UserID] == -1)
// 				SetTarget(FindAtkTarget(150));
// 			return NormalAtk();
// 		}
// 	}

	auto runYanluoling = [&]()
	{
		if (m_TargetID < 0)
		{
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		}
		if (m_TargetID >= 0)
		{
			UseMagic(getVisibleNO() > 1 ? 116 : 117);
			return true;
		}
		return false;
	};

	int self = m_UserID < 10 ? 10 : 0;

	auto runGuiyan = [&](int n)
	{
		vector<POINT> outMself;
		FindEnemy(TRUE, FALSE, outMself, eET�ٶ����2, self);
		auto out2 = check����(outMself, m_UserID);
		if (outMself.size() != out2.size())
		{
			FindEnemy(TRUE, FALSE, outMself, eET����120, m_UserID);
			if (outMself.size() > n)
			{
				SetTarget(outMself.front().x);
				UseMagic(120);
				return true;
			}
		}
		return false;
	};

	auto runGuiyanSeal = [&](int n)
	{
		vector<POINT> outMself;
		FindEnemy(TRUE, FALSE, outMself, eET�ɷ�ϵ, self);
		auto out2 = check����(outMself, m_UserID);
		if (out2.size() > 1)
		{
			FindEnemy(TRUE, FALSE, outMself, eET����120, m_UserID);
			if (outMself.size() > n)
			{
				SetTarget(outMself.front().x);
				UseMagic(120);
				return true;
			}
		}
		return false;
	};

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (isCanMag())
		{
			if (runGuiyanSeal(5))
			{
				return;
			}

			if (runGuiyan(5))
			{
				return;
			}

			// 		int yinshen = 0;
			// 		//		int guiyan = 0;
			// 		int star = m_UserID < 10 ? 10 : 0;
			// 		for (int i = star; i < star + 10; ++i)
			// 		{
			// 			if (!g_pMainState->m_FightList[i].isExist || g_pMainState->m_FightList[i].CheckDie())
			// 			{
			// 				continue;
			// 			}
			// 			cPetData *data = nullptr;
			// 			g_pMainState->m_FightList[i].m_pData->GetDateP(data);
			// 			if (!data)
			// 			{
			// 				continue;
			// 			}
			// 			if (data->PeopleSpecial.d2 > 0)
			// 			{
			// 				++yinshen;
			// 			}
			// 		}
			// 		int star = m_UserID < 10 ? 0 : 10;
			// 		for (int i = star; i < star + 10; ++i)
			// 		{
			// 			if (!g_pMainState->m_FightList[i].isExist || g_pMainState->m_FightList[i].CheckDie())
			// 			{
			// 				continue;
			// 			}
			// 			cPetData *data = nullptr;
			// 			g_pMainState->m_FightList[i].m_pData->GetDateP(data);
			// 			if (!data)
			// 			{
			// 				continue;
			// 			}
			// 			if (data->PeopleSpecial.d1 > 0)
			// 			{
			// 				++guiyan;
			// 			}
			// 		}
			// 		if (yinshen > 0 && !m_pUserPetData->PeopleSpecial.d1)
			// 		{
			// 			SetTarget(m_UserID);
			// 			return UseMagic(120);
			// 		}

			if (m_TargetID < 0)
			{
				vector<POINT> out;
				int rr = FindEnemy(TRUE, FALSE, out, eET�����ɢ127, self);
				auto out2 = check����(out, m_UserID);
				if (rr > 0 && out2.size())
				{
					SetTarget(out2.front());
					return UseMagic(127);
				}

				FindEnemy(TRUE, FALSE, out, eET������129, self);
				out2 = check����(out, m_UserID);
				if (out2.size())
				{
					SetTarget(out2.front());
					return UseMagic(129);
				}

				if (runGuiyanSeal(1))
				{
					return;
				}
				if (runGuiyan(1))
				{
					return;
				}

				FindEnemy(TRUE, FALSE, out, eET��Ȫ֮Ϣ126, self, 126);
				out2 = check����(out, m_UserID);
				if (out2.size() > 3)
				{
					SetTarget(out2.front());
					return UseMagic(126);
				}
			}
		}
	}
	int told = m_TargetID;
	m_TargetID = tOld;
	if (isPutRate() && selectAtk())
	{
		return;
	}
	m_TargetID = told;
	int t = m_TargetID;
	if (RunPet() == 3 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		if (runYanluoling())
		{
			return;
		}
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}

// 		int start, end;
// 		if (m_TargetID<10)start = 0;
// 		else start = 10;
// 		end = start + 10;
// 		if (g_pMainState->GetLiveNum(start, end) > 1)
// 		{
// 			SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4));
// 			return UseMagic(116);
// 		}
// 		else
// 		{
// 			SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4));
// 			UseMagic(117);
// 		}
// 	}
// 
// 
// 	if (!m_pUserPetData->m_FightProperty.cannotSkill && m_pUserPetData->m_ProPertyAtk > m_pUserPetData->m_LV * 2)
// 	{
// 		if (CheckCanSkill(3034))
// 		{
// 			if (m_TargetID < 0)
// 			{
// 				SetTarget(FindAtkTarget(300, TRUE, m_UserID));
// 				if (m_TargetID >= 0)
// 				{
// 					return UseMagic(3034);
// 				}
// 			}
// 		}
// 	}
// 
// 	if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 	{
// 		if (m_TargetID < 0)
// 		{
// 			SetTarget(FindAtkTarget(100, TRUE, m_UserID));
// 			if (m_TargetID >= 0)
// 			{
// 				return NormalAtk();
// 			}
// 		}
// 	}
// 
// 	if (m_pUserPetData->m_FightProperty.cannotMagic &&
// 	return defense(m_UserID);
}
void cAttackAI::RunPS()
{
// 	BOOL bConduct = FALSE;
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 	SetTarget(m_FightTarget[m_UserID]);
	int tOld = m_TargetID;
// 		bConduct = TRUE;
// 	}
// 	else SetTarget(-1);

	auto runTianluodiwang = [&]()
	{
		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			if (m_TargetID < 0)
			{
				SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(162);
				return true;
			}
		}
		return false;
	};

	auto runGouhun = [&]()
	{
		if (m_pUserPetData->m_HP * 100 / m_pUserPetData->m_HPHurtMax < 60)
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindDefminTarget(eProPerty��Ѫ, true));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(154);
				return true;
			}
		}
		return false;
	};

	int self = m_UserID < 10 ? 10 : 0;
	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (isCanMag())
		{
			if (m_TargetID < 0)
			{
				vector<POINT> outMself;
				FindEnemy(TRUE, FALSE, outMself, eET�ɷ�ϵ, self);
				if (outMself.size() > 2 && isUseOtherRate() &&
					!m_pUser->CheckHaveState(166) &&
					!m_pUser->CheckHaveState(2097) &&
					!m_pUser->CheckHaveState(3024) &&
					!m_pUser->CheckHaveState(3025))
				{
					SetTarget(m_UserID);
					return UseMagic(166);
				}
			}

			char isM = -1;
			if (m_TargetID < 0 || (m_TargetID >= 0 && !FindUnSeal(m_TargetID, isM)))
			{
				SetTarget(FindUnSeal(isM));
			}
			if (m_TargetID >= 0 && (isM == 0 || isM == 1))
			{
				m_bSeal[m_TargetID] = TRUE;
				return UseMagic(159);
			}

			//		if (m_pUser->CheckHaveState(166))
			// 		{
			// 
			// 		}
			// 		if (m_pUserPetData->m_LV >= 120)
			// 		{
			// 			SetTarget(m_UserID);
			// 			return UseMagic(166);
			// 		}

			vector<POINT> outMself;
			FindEnemy(TRUE, FALSE, outMself, eET������129, self);
			auto out2 = check����(outMself, m_UserID);
			if (out2.size())
			{
				SetTarget(out2.front());
				return UseMagic(156);
			}

			if (runGouhun())
			{
				return;
			}

			if (m_TargetID < 0)
			{
				vector<POINT> outMself;
				FindEnemy(TRUE, FALSE, outMself, eET������ϵ, self);
				if (outMself.size() > 2 && !m_pUser->CheckHaveState(160))
				{
					SetTarget(m_UserID);
					return UseMagic(160);
				}
			}
		}

		// 		if ((m_pUserPetData->m_MP * 100 / m_pUserPetData->m_MPMax.GetData() < 5) || (m_pUserPetData->m_MP < 80))
		// 		{
		// 			if (m_TargetID < 0)
		// 			{
		// 				SetTarget(FindDefminTarget(eProPertyħ��, true));
		// 			}
		// 			if (m_TargetID >= 0)
		// 			{
		// 				return UseMagic(155);
		// 			}
		// 		}


	}

	int told = m_TargetID;
	m_TargetID = tOld;
	if (isPutRate() && selectAtk())
	{
		return;
	}
	m_TargetID = told;
	int t = m_TargetID;
	if (RunPet() == 3 && isPetRate())
	{
		return;
	}
	m_TargetID = t;

	if (isCanMag() && runGouhun())
	{
		return;
	}

	if (runTianluodiwang())
	{
		return;
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}

// 	BOOL bCanMagic, bCanAtk,bCanSkill;
// 	bCanMagic = !m_pUserPetData->m_FightProperty.cannotMagic;
// 	bCanAtk = !m_pUserPetData->m_FightProperty.cannotAttack;
// 	bCanSkill = !m_pUserPetData->m_FightProperty.cannotSkill;
// 	if (m_pUserPetData->m_ProPertyAtk >= m_pUserPetData->m_LV * 2)//����˿
// 	{
// 		if (m_FightTarget[m_UserID] == -1)
// 			SetTarget(FindAtkTarget(150));
// 		if (bCanAtk)
// 		{
// 			if(!bCanMagic)return NormalAtk();
// 			if (m_pUserPetData->m_ATK.GetData() - m_pTargetPetData->m_DEF.GetData() > m_pUserPetData->m_LV * 5)
// 				return NormalAtk();
// 			else
// 				return UseMagic(162); //���޵���
// 		}
// 		else
// 		{
// 			if (bCanMagic)UseMagic(162); //���޵���
// 		}
// 		
// 	}
// 
// 	if (bCanMagic)
// 	{//����ʹ��ħ���������
// 		if (bConduct)
// 		{//���ָ��Ŀ�������²���Ŀ��û�б��� ���Է�ӡĿ��
// 			if (!m_bSeal[m_TargetID])
// 			{
// 				if (!m_pTargetPetData->m_FightProperty.cannotMagic)
// 				{
// 					m_bSeal[m_TargetID] = TRUE;
// 					return UseMagic(159);
// 				}
// 
// 			}
// 			else
// 			{
// 				if (!m_bPKMode)
// 					return UseMagic(162); //���޵���
// 				else
// 					return UseMagic(155);//����
// 			}
// 		}
// 		if (!m_bPKMode)
// 		{
// 			if (m_FightTarget[m_UserID] == -1)
// 				SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4));
// 			return UseMagic(162); //���޵���
// 		}
// 		//PK
// 		if (m_FightTarget[m_UserID] == -1)
// 		{
// 			int unsealtarget = FindUnSeal(5);
// 			if (unsealtarget == -1)
// 			{//���еĵ��˶�������?
// 				SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4));
// 			}
// 			else
// 			{
// 				SetTarget(unsealtarget);
// 				return UseMagic(159);
// 			}
// 		}
//	}
//	return defense(m_UserID);
}
void cAttackAI::RunMW()
{
	if (!isAtkMode() && isCanSpec() && RunLH())
	{
		return;
	}
	int t = m_TargetID;
	if (RunPet() == 4 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (m_FightTarget[m_UserID] > -1)
	{
		SetTarget(m_FightTarget[m_UserID]);
	}
	else SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));

	int self = m_UserID < 10 ? 10 : 0;
	if (!m_pUserPetData->m_FightProperty.cannotMagic)
	{
		if (!m_pUserPetData->PeopleSpecial.d1)
		{
			vector<POINT> outMself;
			FindEnemy(TRUE, FALSE, outMself, eET�ٶ����2, self);
			auto out2 = check����(outMself, m_UserID);
			if (outMself.size() != out2.size())
			{
				if (out2.size() < 3)
				{
					SetTarget(m_UserID);
					return UseMagic(133);
				}
			}
		}
		return UseMagic((getVisibleNO() <= 1 || (m_UserID >= 10 && rand() % 100 < 20)) ? 132 : 131);
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}


// 	int start, end;
// 	if (m_UserID<10)start = 10;
// 	else start = 0;
// 	end = start + 10;
// 	if (g_pMainState->GetLiveNum(start, end) > 1)
// 	{//��ɰ��ʯ	
// 		return UseMagic(131);
// 	}
// 	else
// 	{//��ζ���
// 		return UseMagic(132);
// 	}
}
void cAttackAI::RunST()
{
	if (!isAtkMode() && isCanSpec() && RunLH())
	{
		return;
	}
	SetTarget(m_FightTarget[m_UserID]);

	auto get145Times = [&]()
	{
		for (list<sBuff>::iterator it = m_pUser->m_StateList.begin(); it != m_pUser->m_StateList.end(); it++)
		{
			if (it->ID == 145)
				return it->times;
		}
		return -1;
	};

	auto isYingji = [&]()
	{
		int n = getVisibleNO();
		return n > 3 || (n == 3 && rand() % 100 < 35);
	};
		

	auto runYingji = [&]()
	{
		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(100, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(142);
				return true;
			}
		}
		return false;
	};

	auto runShibo = [&]()
	{
		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(250, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(143);
				return true;
			}
		}
		return false;
	};

	auto runLianhuanji = [&]()
	{
		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(500, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(148);
				return true;
			}
		}
		return false;
	};

	int t = get145Times();
	if (m_TargetID >= 0 && t >= 0 && runLianhuanji())
	{
		return;
	}
	if (MyTest::getInstance()->isAtkMode(m_UserID))
	{
		if (t >= 0 && m_UserID >= 10 && rand() % 100 < 30 && runLianhuanji())
		{
			return;
		}
	}

	if (t >= 0 && isYingji() && runYingji())
	{
		return;
	}
	if (t >= 0)
	{
		if (t > 0 && runShibo())
		{
			return;
		}
		else if (t == 0 && runLianhuanji())
		{
			return;
		}
	}
	if (!m_pUserPetData->m_FightProperty.cannotSkill)
	{
		if (CheckCanSkill(3034))
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(300, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				return UseMagic(3034);
			}
		}
	}
	if(!m_pUserPetData->m_FightProperty.cannotMagic)
	{
		SetTarget(m_UserID);
		return UseMagic(145);
	}

	if (!m_pUserPetData->m_FightProperty.cannotAttack)
	{
		if (m_TargetID < 0)
		{
			SetTarget(FindAtkTarget(100, TRUE, m_UserID));
		}
		if (m_TargetID >= 0)
		{
			return NormalAtk();
		}
	}

	if (!m_pUser->CheckHaveState(142)/* && !m_pUser->CheckHaveState(148)*/)
	{
		return Def(m_UserID);
	}
}


void cAttackAI::UseMagic(int id)
{
	if (m_TargetID == -1)return;
	sFightList& list = g_pMainState->m_FightList[m_UserID];
	list.m_WorkType = WORKTYPE_MAGIC;
// 	list.m_SkillSelect.Lv = m_pUserPetData->m_LV + m_pUserPetData->m_StrongLv/5-10;
// 	if (list.m_SkillSelect.Lv < 0)list.m_SkillSelect.Lv = 0;
// 	if (list.m_SkillSelect.Lv>180)list.m_SkillSelect.Lv = 180;
	list.m_SkillSelect.Lv = list.m_pData->GetSkillLv(0);
	list.m_SkillSelect.SkillID = id;
	list.m_SkillSelect.TargetID = m_TargetID;
}

void cAttackAI::NormalAtk()
{
	sFightList& list = g_pMainState->m_FightList[m_UserID];
	list.m_WorkType = WORKTYPE_ATTACK;
	list.m_SkillSelect.Lv = 0;
	list.m_SkillSelect.SkillID = 1000;
	list.m_SkillSelect.TargetID = m_TargetID;
}

void cAttackAI::ResetNeed()
{
	for (int i = 0; i < 20; i++)
	{
		m_bNeedUnSeal[i] = 0;
		m_bNeedAddHp[i] = 0;
		m_bNeedAddMp[i] = 0;
		m_bNeedlive[i] = 0;
		m_bNeedAddHpHurt[i] = 0;
	}
}

// ����+2
BOOL cAttackAI::SaveOneself(int start,int end)
{
	for (int i = start; i < end; i++)
	{
		if (i == g_pMainState->m_HeroID)continue;
		SaveOneself2(i);
	}
	return FALSE;
}
void cAttackAI::SaveOneself2(int i)
{
	if (!g_pMainState->m_FightList[i].isLive)return;
	if (g_pMainState->m_FightList[i].CheckDie())return;
	if (g_pMainState->m_FightList[i].m_WorkType != -1)return;
	SetUser(i);
	SetTarget(i);
	if (m_pUserPc)
		if (!m_pUserPetData->m_FightProperty.cannotSkill)
		{
		//		if (m_pUserPetData->m_StrongLv > 90 - 50)
			{
				if (m_bNeedAddHp[i] > 0 || m_bNeedAddHpHurt[i] > 0)
				{
					if (CheckCanSkill(3006))
					{
						m_bNeedAddHp[i] = FALSE;
						m_bNeedAddHpHurt[i] = FALSE;
						return UseMagic(3006);//����
					}
				}
				if (m_bNeedAddMp[i])
				{
					if (CheckCanSkill(3004))
					{
						m_bNeedAddMp[i] = FALSE;
						return UseMagic(3004);//�����  
					}
				}
			}
		//		else
		//		if (m_pUserPetData->m_StrongLv > 50)
		{
			if (m_bNeedAddHp[i] || m_bNeedAddHpHurt[i])
			{
				if (CheckCanSkill(3005))
				{
					m_bNeedAddHp[i] = FALSE;
					m_bNeedAddHpHurt[i] = FALSE;
					return UseMagic(3005);//����

				}
			}
			if (m_bNeedAddMp[i])
			{
				if (CheckCanSkill(3003))
				{
					m_bNeedAddMp[i] = FALSE;
					return UseMagic(3003);//������
				}
			}
		}
		}
	if (m_pUserPetData->m_FightProperty.cannotUseItem)return;
	if (m_bNeedAddHpHurt[i])
	{
		if (CheckItem(eAIUseItemTypeHPHurt))
		{
			UseItem(eAIUseItemTypeHPHurt);
		}
		return;
	}
	if (m_bNeedAddHp[i])
	{
		if (CheckItem(eAIUseItemTypeHP))
		{
			UseItem(eAIUseItemTypeHP);
		}
		return;
	}
	if (m_bNeedUnSeal[i])
	{
		if (CheckItem(eAIUseItemTypeUnseal))
			UseItem(eAIUseItemTypeUnseal);//���
		return;
	}
	if (m_bNeedAddMp[i])
	{
		if (CheckItem(eAIUseItemTypeMP))
			UseItem(eAIUseItemTypeMP);
		return;
	}
}


void cAttackAI::GetNeed(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		if (!g_pMainState->m_FightList[i].isLive)continue;
		SetUser(i);
		//����
		if (m_pUserPetData->m_HP == 0)
		{
			if (!m_pUserPetData->m_FightProperty.cannotLive)
			{
				m_bNeedlive[i] = TRUE;
			}
		}
		int limit = m_pUserPc ? m_HPLimit : m_HPLimit / 2 + 50;
		//Ѫ����
		if (m_pUserPetData->m_HP < (m_pUserPetData->m_HPMax.GetData() * limit) / 100)
		{
			//Ѫ��,Խ��Ҫ��Ѫ
			int k = (m_pUserPetData->m_HP * 100) / m_pUserPetData->m_HPMax.GetData() + 1;
			k = k * limit / m_HPLimit;
			k = 100 - k;
			if (m_pUserPetData->m_HPHurtMax < m_pUserPetData->m_HPMax.GetData())

				m_bNeedAddHpHurt[i] = TRUE;

			m_bNeedAddHp[i] = k;
	
			if (m_pUserPc && m_pUserPetData->m_FightProperty.cannotAddHP)//����Ҳ���
			{
				m_bNeedUnSeal[i] = TRUE;
			}
		}

		m_bNeedAddMp[i] = TRUE;
		vector<int> ms, m2s, ps, bs;
		isHadPetSkill(m_pUserPetData, bs, ps, ms, m2s);
		if (m_pUserPetData->m_LiveMpLv || (!m_pUserPc && !bs.size() && !ps.size() && !ms.size() && !m2s.size()))
		{
			m_bNeedAddMp[i] = FALSE;
		}
		else if (m_pUserPetData->m_MP >= m_pUserPetData->m_LV + 10 ||
			m_pUserPetData->m_MP >= m_pUserPetData->m_MPMax.GetData() - 30)
		{
			m_bNeedAddMp[i] = FALSE;
		}
		else if (m_pUserPc && !m_pUserPc->m_PCData.m_MengPaiID)
		{
// 			m_bNeedAddMp[i] = (m_pUserPetData->m_MP * 100) / m_pUserPetData->m_MPMax.GetData();
// 			m_bNeedAddMp[i] = 100 - m_bNeedAddMp[i];
			m_bNeedAddMp[i] = FALSE;
		}
		if (m_pUser->CheckHaveState(6))	
		{
			//���˷���
			m_bNeedUnSeal[i] = TRUE;
		}
		if (m_pUserPetData->m_FightProperty.cannotMagic)//����ʹ��ħ��
		{
			if (!m_pUser->m_StateList.size())
			{
				continue;
			}
			if (m_pUser->m_StateList.back().times < 3)
			{
				continue;//3�غ����µ�BUFF���ù�
			}
			if (i % 10 > 4)
			{
				if (m_pUserPetData->m_ProPertyHP >= m_pUserPetData->m_LV * 3)
				{
					continue;//Ѫ�費�þ�
				}
				if (m_pUserPetData->m_ProPertyAtk > m_pUserPetData->m_LV)
				{
					continue;//����ⷨ��Ҫ��
				}
			}
			m_bNeedUnSeal[i] = TRUE;
		}
		
		if (m_pUserPetData->m_FightProperty.cannotAttack)//���ܹ���
		{
			if (!m_pUser->m_StateList.size())
			{
				continue;
			}
			if (m_pUser->m_StateList.back().times < 3)
			{
				continue;//3�غ����µ�BUFF���ù�
			}
			if (!m_pUserPc)
			{
				if (m_pUserPetData->m_ProPertyAtk > m_pUserPetData->m_LV)
				{
					if (!ps.size())
					{
						m_bNeedUnSeal[i] = TRUE;
					}					
				}
			}
		}
		if (m_pUserPetData->m_FightProperty.cannotSkill)//����
		{
			if (m_pUserPc && m_pUserPetData->m_CP > 80)
			{
				m_bNeedUnSeal[i] = TRUE;
			}
		}

		if (m_pUserPetData->PeopleSpecial.d2 || 
			m_pUserPetData->restoreRate ||
			m_pUser->CheckHaveState(0) ||
			m_pUser->CheckHaveState(7) ||
			m_pUser->CheckHaveState(142))
		{
			m_bNeedUnSeal[i] = FALSE;
		}

// 		if (m_bNeedlive[i])
// 		{
// 			m_bNeedUnSeal[i] = FALSE;
// 			m_bNeedAddHp[i] = FALSE;
// 			m_bNeedAddHpHurt[i] = FALSE;
// 			m_bNeedAddMp[i] = FALSE;
// 		}
	}
}

void cAttackAI::SetTarget(int target)
{
	if (m_TargetID == target)return;
	m_TargetID = target;
	if (target < 0)
	{
		m_pTarget = nullptr;
		m_pTargetPetData = nullptr;
		return;
	}
	if (!g_pMainState->m_FightList[target].isLive)
	{
		m_TargetID = -1;
		m_pTarget = nullptr;
		m_pTargetPetData = nullptr;
		return;
	}
	m_pTargetList = &g_pMainState->m_FightList[m_TargetID];
	m_pTarget= g_pMainState->m_FightList[m_TargetID].m_pData;
	m_pTarget->GetDateP(m_pTargetPetData);
	if (0 == m_pTargetPetData)
	{
		ERRBOX(target);
	}
}

void cAttackAI::SetUser(int userid)
{
	if (m_UserID == userid)return;
	m_UserID = userid;
	pUserList = &g_pMainState->m_FightList[userid];
	m_pUser = g_pMainState->m_FightList[userid].m_pData;
	if (m_pUser->m_IndexType==INDEXTYEP_CHARACTER)
		m_pUserPc=(cCharacter*)m_pUser->m_pIndex;
	else m_pUserPc = 0;
	m_pUser->GetDateP(m_pUserPetData);
} 

void cAttackAI::Run()
{
//	Reset();
//	GetNeed(0, 20);
	for (int i = 0; i < 10; i++)
	{
		break;
		if ((i%5)==g_pMainState->m_HeroID)
		{
			if (g_pMainState->m_FightList[i].isLive)
			{
				SetUser(i);
				if (m_pUserPc)
				{
					if (pUserList->m_WorkType == WORKTYPE_MAGIC)
					{
						//������� ��ӡ
						if (pUserList->m_SkillSelect.TargetID > 9)
						{
							m_bNeedUnSeal[pUserList->m_SkillSelect.TargetID] = TRUE;
						}
						else
						{
							m_bNeedAddHp[pUserList->m_SkillSelect.TargetID] -= 50;
						}
					}
				}
				if (pUserList->m_WorkType == WORKTYPE_ITEM)
				{	//������Ǽ�Ѫ
					if (pUserList->m_SkillSelect.TargetID < 10)
					{
					//	sItem2* pItem = &m_pUserPc->m_PCData.m_Item[pUserList->m_ItemSelectID];
						m_bNeedAddHp[pUserList->m_SkillSelect.TargetID] -= 20;
					}
				}
			}
		}
	}
//	ZhiHui(FALSE);
//	ZhiHui(TRUE);
// 	PreRun(0,10);
// 	if (m_bPKMode)
// 	{
// 		ZhiHui(FALSE);
// 	}
// 
// 
// 	for (int i = 0; i < 10; i++)
// 	{
// 		g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 		if (g_pMainState->m_FightList[i].isExist)
// 		if (g_pMainState->m_FightList[i].m_WorkType == -1)
// 		{
// 			g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 			AutoRunAi(i);
// 		}
// 	}
//	if (m_bPKMode)
// 	{
// 		for (int i = 10; i < 20; i++)
// 		{
// 			g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 			if (g_pMainState->m_FightList[i].isExist)
// 			if (g_pMainState->m_FightList[i].m_WorkType == -1)
// 			{
// 				g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 				AutoRunAi(i);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		for (int i = 10; i < 20; i++)
// 		{
// 			g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 			if (g_pMainState->m_FightList[i].isExist)
// 			if (g_pMainState->m_FightList[i].m_WorkType == -1)
// 			{
// 				g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 				AutoRunEnemyAi(i);
// 			}
// 		}
// 	}



// 	vector<POINT>out;
// 	FindEnemy(FALSE, TRUE, out, eET�ٶ����, 10);
// 	forv(out, i)
// 	{
// 		g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 		AutoRunAi(out[i].x);
// 	}
// 	out.clear();
// 	FindEnemy(FALSE, TRUE, out, eET�ٶ����, 0);
// 	forv(out, i)
// 	{
// 		g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 		AutoRunAi(out[i].x);
// 	}


	for (int i = 0; i < 20; i++)
	{
//		m_FightTarget[i] = -1;
		m_bSeal[i] = FALSE;
		m_bAtk[i] = 0;
	}
}


// ����
void cAttackAI::PreRun(int start, int end)
{
	//CoutIdleList(start,end);
	GetNeed(start, end);
	ContentLive(start,end);
	ContentHP(start, end);
	ContentUnSeal(start, end);
	SaveOneself(start, end);
}

void cAttackAI::AutoRunAi(int i)
{
	SetUser(i);	
	if (getVisibleNO() < 1)
	{
		return Def(m_UserID);
	}
	if (!m_pUserPc)//�ٻ���
	{
		if (g_pMainState->m_FightList[m_UserID].isLive)
		{
			if (!RunPet())
			{
				Def(i);
			}
		}
		return;
	}
// 	if (m_pUserPetData->m_LV < 25)
// 	{
// 		if (m_FightTarget[m_UserID] > -1)
// 		{
// 			SetTarget(m_FightTarget[m_UserID]);
// 		}
// 		else
// 		{
// 			SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, true));
// 			if (m_TargetID < 0)
// 			{
// 				SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, false));
// 			}
// 		}
// 		return	NormalAtk();
// 	}
	

	eMengPai emngpaiid = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
	switch (emngpaiid)
	{
	case eMP_���ƹٸ�:return RunDT();
	case eMP_����ɽ:return RunFC();
	case eMP_������:return RunHS();	
	case eMP_Ů����:return RunNR();	
	case eMP_�칬:return RunTG();
	case eMP_��������:return RunLG();
	case eMP_��ׯ��:return RunWZ();
	case eMP_����ɽ:return RunPT();
	case eMP_���ܵظ�:return RunDF();
	case eMP_ħ��կ:return RunMW();
	case eMP_ʨ����:return RunST();
	case eMP_��˿��:return RunPS();
	default:
		break;
	}
}

void cAttackAI::AutoRunEnemyAi(int i)
{
	vector<POINT> tlist;
	SetUser(i);
	if (m_pUserPetData->m_FightProperty.cannotAll)return;
	if (m_FightTarget[i] > -1)
	{
		SetTarget(m_FightTarget[i]);
	}
	else
		SetTarget(g_pMainState->m_AI.AutoFindTarget(i, 4, true));
	
//	int ailv = m_pUserPetData->m_AiLv;
	if (m_pUserPetData->m_FightProperty.cannotMagic)//���ⷨ��ʱ������
	{
		return NormalAtk();
	}
	if (!m_pUserPc)//�ٻ���
	{
		vector<int> skilllist;
		//Ѱ���ٻ��޵���������
		for (int j = 0; j < m_pUserPetData->m_NumofBBSkill; j++)
		{
			if (m_pUserPetData->m_pPetSkill[j]->m_SkillType == 4)
			{
				skilllist.push_back(m_pUserPetData->m_pPetSkill[j]->m_Id);
			}
		}
		if (skilllist.size())
		{//�����
			int skilluse = 2000 + skilllist[rand() % skilllist.size()];
			if (CheckCanSkill(skilluse))
				return UseMagic(skilluse);
		}
		return	NormalAtk();
	}
	eMengPai emngpaiid = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
	if (m_pUserPetData->m_FightProperty.cannotMagic)
	{
		switch (emngpaiid)
		{
		case eMP_Ů����:
			if (!m_pUserPetData->m_FightProperty.cannotUseItem)
			 UseItem(eAIUseItemType����);
			else NormalAtk();
			return;
		default:
			NormalAtk();
			return;
		}
	}
	switch (emngpaiid)
	{
	case eMP_���ƹٸ�:
			switch (rand() % 7)
			{
			case 0:return NormalAtk();
			case 1:
				if (m_pUserPetData->m_HP<5000)
				{
					if (m_pUserPetData->m_LV > 129)
					{
						return NpcTryMagic(7);
					}
				}
				if (m_pUserPetData->m_FightProperty.cannotAttack)return NpcTryMagic(0);
				return NormalAtk();
				break;
			case 2:return NpcTryMagic(1);
			case 3:
				if (!CheckHaveState(i, 4))
				{
					if (CheckCanSkill(4))
					{
						SetTarget(i);
						return UseMagic(4);
					}
					else
						return NormalAtk();
				}
				else
				{
					if (m_pUserPetData->m_FightProperty.cannotAttack)return NpcTryMagic(0);
					return NormalAtk();
				}
			case 4:return NpcTryMagic(6);
			default:return NpcTryMagic(0);
			}
			break;
	case eMP_����ɽ:
		switch (rand() % 4)
		{
		case 0:
			if (m_pUserPetData->m_FightProperty.cannotAttack)
			{
				return NpcTryMagic(11);
			}
			else
			return NormalAtk();
		case 1:
			if (1)
			{
				int start, end;
				if (m_UserID < 10)start = 10;
				else start = 0;
				end = start + 10;
				int target2 = FindUnSeal(start, end);
				if (target2 == -1)return NormalAtk();
				SetTarget(target2);
				m_bSeal[m_TargetID] = TRUE;
				switch (rand() % 5)
				{
				case 1:return NpcTryMagic(14);
				case 2:return NpcTryMagic(15);
				case 3:return NpcTryMagic(19);
				case 4:return NpcTryMagic(20);
				default:return NpcTryMagic(21);
				}
			}
		default:return NpcTryMagic(11);
		}
		break;
	case eMP_������:
			switch (rand() % 7)
			{
			case 0:
				return UseMagic(31);
			case 1:
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(40);
				}
				else
				return NormalAtk();
			case 2:
				if (1)
				{
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true));
					switch (rand() % 5)
					{
					case 0: return NpcTryMagic(42);
					case 1:return NpcTryMagic(33);
					case 2: return NpcTryMagic(35);
					case 3: return NpcTryMagic(39);
					case 4: return NpcTryMagic(40);
					}
				}
				break;
			default:
				SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true));
				if (rand() % 2)return NpcTryMagic(40);
				else  return NpcTryMagic(42);
			}
			break;
	case eMP_Ů����:
			switch (rand() % 4)
			{
			case 0:
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					 UseItem(eAIUseItemType����);
					 return;
				}
				else
				return NormalAtk();
			case 1:
				if (1)
				{
					int start, end;
					if (m_UserID < 10)start = 10;
					else start = 0;
					end = start + 10;
					int target2 = FindUnSeal(start, end);
					if (target2 == -1)return NormalAtk();
					SetTarget(target2);
					m_bSeal[m_TargetID] = TRUE;
					if (m_pUserPetData->m_LV > 129)return NpcTryMagic(54);
					return NpcTryMagic(54);
				}
			default:
				UseItem(eAIUseItemType����);
				return;
			
			}
		break;
	case eMP_�칬:
			switch (rand() % 10)
			{
			case 1:
			case 2:
				if (1)
				{
					int start, end;
					if (m_UserID < 10)start = 10;
					else start = 0;
					end = start + 10;
					int target2 = FindUnSeal(start, end);
					if (target2 == -1)return NormalAtk();
					SetTarget(target2);
					m_bSeal[m_TargetID] = TRUE;
					if (rand() % 2)
					{
						return NpcTryMagic(68);
					}
					else return NpcTryMagic(69);
				}
				return;
			case 3:
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(71);
				}
				else
				return NormalAtk();
			case 4:return NpcTryMagic(72); 
			case 5: 
				if (m_pUserPetData->m_LV > 129)return NpcTryMagic(74);
			default:return NpcTryMagic(71);
			}
		break;
	case eMP_��������:
			switch (rand()%7)
			{
			case 0:return NpcTryMagic(84);
			case 1:return NpcTryMagic(79);
			case 2:
				if (m_pUserPetData->m_LV > 129)return NpcTryMagic(88);
				else 
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(80);
				}
				else
					return NormalAtk();
			case 3:
				if (!CheckHaveState(m_UserID,147))
				{
					if (CheckCanSkill(147))
					{
						SetTarget(m_UserID);
						return UseMagic(147);
					}
				}
				return NpcTryMagic(80);
			default:return NpcTryMagic(80);
			}
		break;
	case eMP_��ׯ��:
			switch (rand() % 7)
			{
			case 0: 
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(97);
				}
				else
				return NormalAtk();
			case 2: 
				if (1)
				{
					int start, end;
					if (m_UserID < 10)start = 11;
					else start = 1;
					end = start + 9;
					if (m_bPKMode)//�չ�Ǭ���ڷ�PKʱ�޷�������
					{
						start -= 1;
						end -= 5;
					}
					int target2 = FindUnSeal(start, end);
					if (target2 == -1)return NormalAtk();
					SetTarget(target2);
					m_bSeal[m_TargetID] = TRUE;
					return NpcTryMagic(89);
				}
			case 3: 
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true));
					return NpcTryMagic(91);
			default: 
				return NpcTryMagic(97);
			}
		break;
	case eMP_����ɽ:
		if (rand() % 3)
		{
			return NpcTryMagic(105 + rand() % 5);
		}
		else
		{
			int targetid = g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true);
			switch (rand() % 5)
			{
			case 0: 
				if (CheckCanSkill(113))
				{//�ߵ�����
					SetTarget(targetid);
					if (m_pTarget->CheckHaveState(113))
					{
						SetTarget(g_pMainState->m_AI.AutoFindTarget(i, 4, true));
						return NpcTryMagic(105 + rand() % 5);
					}
					return  NpcTryMagic(113);
				}
				return NpcTryMagic(105 + rand() % 5);
			case 1:
				if (CheckCanSkill(102))//�ն�
				{
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true));
					if (tlist.size())
					{
						SetTarget(tlist[0].x);
						return NpcTryMagic(102);
					}
				}
				SetTarget(g_pMainState->m_AI.AutoFindTarget(i, 4, true));
				return NpcTryMagic(105 + rand() % 5);
			case 2: 
				if (CheckCanSkill(103))
				return UseMagic(103);
				return NormalAtk();
			case 3: 
				if (CheckCanSkill(112))
				{
					SetTarget(targetid);
					return UseMagic(112);
				}
				return NpcTryMagic(105 + rand() % 5);
			case 4:
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(105 + rand() % 5);
				}
				else
				return NormalAtk();
			}
		}
		break;
	case eMP_���ܵظ�:
		if (1)
		{
			
			switch (rand() % 6)
			{
			case 0: 
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(117);
				}
				else
				return NormalAtk();
			case 1:return NpcTryMagic(117);
			case 3: return NpcTryMagic(122);
			case 4: 
				if (CheckCanSkill(123))
				{
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true));
					return NpcTryMagic(123);
				}
				else return NpcTryMagic(116);
			default: return NpcTryMagic(116);
			}
		}
		break;
	case eMP_ħ��կ:
		if (1)
		{
			switch (rand() % 6)
			{
			case 0: 
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(131);
				}
				else
				return NormalAtk();
			case 1:return NpcTryMagic(132);
			case 2:
				if (!m_pUser->CheckHaveState(133))
				{
					if (CheckCanSkill(133))
					{
						SetTarget(m_UserID);
						return NpcTryMagic(133);
					}
				}
				return NpcTryMagic(131);
			default:  return NpcTryMagic(131);
			}
		}
		break;
	case eMP_ʨ����:
		if (1)
		{
			if (m_pUser->CheckHaveState(145))
			{
				switch (rand() % 5)
				{
				case 0:return NpcTryMagic(143);
				case 1:return NpcTryMagic(148);
				case 2:return NpcTryMagic(141);
				default: return NpcTryMagic(142);
				}
			}
			else
			{
				switch (rand() % 3)
				{
				case 0:
					if (m_pUserPetData->m_FightProperty.cannotAttack)
					{
						SetTarget(m_UserID);
						return NpcTryMagic(145);
					}
					else
					return NormalAtk();
				default:
					SetTarget(m_UserID);
					return NpcTryMagic(145);
				}
			}
		}
		break;
	case eMP_��˿��:
		switch (rand() % 6)
		{
		case 0:
			if(rand()%2)
			return NpcTryMagic(154);
			return NpcTryMagic(155);
		case 1:return NpcTryMagic(156);
		case 2:
			if (1)
			{
				int start, end;
				if (m_UserID < 10)start = 10;
				else start = 0;
				end = start + 10;
				int target2 = FindUnSeal(start, end);
				if (target2 == -1)return NormalAtk();
				SetTarget(target2);
				m_bSeal[m_TargetID] = TRUE;
				return NpcTryMagic(159);
			}
		case 3:
			if (!CheckHaveState(m_UserID, 160))
			{
				if (CheckCanSkill(160))
				{
					SetTarget(m_UserID);
					return UseMagic(160);
				}
				
			}
			if (m_pUserPetData->m_FightProperty.cannotAttack)
			{
				return NpcTryMagic(162);
			}
			else
			return NormalAtk();
		case 4:return NpcTryMagic(164);
		default:return NpcTryMagic(162);
		}
		break;
	 default:
		 ERRBOX;
		break;
	}
}

// ����+4
void cAttackAI::ContentHP(int start, int end)
{
	
	for (int i = start; i < end; i++)
	{
		if (!m_bNeedlive[i])//ȷ��Ӧ�û���
		if (m_bNeedAddHp[i]>0 || m_bNeedAddHpHurt[i]>0)
		{
			SetTarget(i);
			ContentHP2(start, end);
			if (m_bNeedAddHp[i]<0)
			m_bNeedAddHp[i] = 0;
			if (m_bNeedAddHpHurt[i]<0)
			m_bNeedAddHpHurt[i] = 0;
		}
	}
}
void cAttackAI::ContentHP2(int start, int end)
{
	vector<int> list;
	int id2 = -1;
	int id;
	int firstpos = -1;
	for (int i = 19; i >-1; i--)
	{
		id = g_pMainState->m_pFightState->m_SpeedListPos[i];
		if (id < start || id >= end)continue;
		if (!g_pMainState->m_FightList[id].isLive)continue;
		if (g_pMainState->m_FightList[id].CheckDie())continue;
		if (g_pMainState->m_FightList[id].m_WorkType != -1)continue;

		if (-1 == id2)
		if (g_pMainState->m_FightList[id].m_pData->m_IndexType == INDEXTYEP_CHARACTER)
		{//
			cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[id].m_pData->m_pIndex;
			if (!pc->m_PCData.m_FightProperty.cannotMagic)
			{
				switch (pc->m_PCData.m_MengPaiID)
				{
				case eMP_����ɽ:
				case eMP_������:
				case eMP_��ׯ��:
					id2 = id;
					firstpos = list.size();
					break;
				}
			}
		}
		cPetData* pPet;
		g_pMainState->m_FightList[id].m_pData->GetDateP(pPet);
		if (!pPet->m_FightProperty.cannotUseItem)
			list.push_back(id);
	}
	if (!list.size())return;
	if (-1 == id2)
	{
		id2 = list[0];
		firstpos = 0;
	}
	SetUser(id2);
	//BOOL bUse = FALSE;

		int num = 0;//��Ҫ���ƵĶ�����
		for (int i2 = start; i2 < end; i2++)
		if (m_bNeedAddHp[i2]>0 || m_bNeedAddHpHurt[i2]>0)
			num += 1;
		if (m_pUserPc)
		{
			eMengPai mengpai = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
			switch (mengpai)
			{
			case eMP_������:
				if (1)
				{
					if (num == 1)
					{
// 						switch (m_pUserPetData->m_StrongLv >> 5)
 						{
// 						case 3:
							if (CheckCanSkill(39))
							{
								m_bNeedAddHpHurt[m_TargetID] = -20;
								m_bNeedAddHp[m_TargetID] = -20;
								return UseMagic(39);
							}
							else 
//						case 2:
							if (CheckCanSkill(3002))
							{
								m_bNeedAddHpHurt[m_TargetID] = -15;
								m_bNeedAddHp[m_TargetID] = -15;
								return UseMagic(3002);
							}
//						case 1:
							else 
							if (CheckCanSkill(3001))
							{
								m_bNeedAddHpHurt[m_TargetID] = -10;
								m_bNeedAddHp[m_TargetID] = -10;
								return UseMagic(3001);
							}
// 							break;
 						}
					}
					//����
					if (!m_pUserPetData->m_FightProperty.cannotMagic)
					{
						int skillid;
						if (num > 1)
						{
							if (m_bNeedAddHpHurt>0)skillid = 42;
							else skillid = 40;
						}
						else
						{
							
							if (m_bNeedAddHpHurt>0)skillid = 38;
							else
							{
								if (m_pUserPetData->m_LV > 129)
									skillid = 45;
								else
									skillid = 39;
							}

						}
						if (CheckCanSkill(skillid))
						{
							m_bNeedAddHpHurt[m_TargetID] = -10;
							m_bNeedAddHp[m_TargetID] = -10;
							return UseMagic(skillid);
						}
					}
				}
				break;
			case eMP_���ܵظ�:
				if (num > 1) //�ĺ�
				{
//					if (m_pUserPetData->m_StrongLv > 90)
					{
						if (CheckCanSkill(7))
						{
							m_bNeedAddHpHurt[m_TargetID] = -20;
							m_bNeedAddHp[m_TargetID] = -20;
							return UseMagic(39);
						}
					}
				}
				break;
			case eMP_����ɽ:
				if (1)
				{
					if (num > 1) //�ĺ�
					{
//						if (m_pUserPetData->m_StrongLv >90)
						{
							if (CheckCanSkill(7))
							{
								m_bNeedAddHpHurt[m_TargetID] = -20;
								m_bNeedAddHp[m_TargetID] = -20;
								return UseMagic(39);
							}
						}
					}
					//����
					if (!m_pUserPetData->m_FightProperty.cannotMagic)
					{
						if (CheckCanSkill(102))
						{
							m_bNeedAddHpHurt[m_TargetID] = -30;
							m_bNeedAddHp[m_TargetID] = -30;
							return UseMagic(102);
						}
					}
				}
				break;
			}
		}
		//����

		if (m_bNeedAddHp[m_TargetID]>0)
		{
			if (num > 3)
			{
				if (CheckItem(eAIUseItemTypeHPALL))
				{
					for (int i2 = start; i2 < end;i2++)
						m_bNeedAddHp[i2] =0;
					  UseItem(eAIUseItemTypeHPALL);
					  return;
				}
			}
			if (CheckItem(eAIUseItemTypeHP))
			{
				m_bNeedAddHp[m_TargetID] = 0;
				  UseItem(eAIUseItemTypeHP);
				  return;
			}
		}
		if (CheckItem(eAIUseItemTypeHPHurt))
		{
			m_bNeedAddHpHurt[m_TargetID] = 0;
			  UseItem(eAIUseItemTypeHPHurt);
			  return;
		}
	
}
void cAttackAI::ContentLive(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		if (m_bNeedlive[i])
		{
			SetTarget(i);
			ContentLive2(start, end);
		}
	}
}
void cAttackAI::ContentLive2(int start, int end)
{
	vector<int> list;
	int id2=-1;
	int id;
	int firstpos=-1;
	for (int i = 0; i < 20; i++)
	{
		id= g_pMainState->m_pFightState->m_SpeedListPos[i];
		if (id < start || id >= end)continue;
		if (!g_pMainState->m_FightList[id].isLive)continue;
		if (g_pMainState->m_FightList[id].CheckDie())continue;
		if (g_pMainState->m_FightList[id].m_WorkType != -1)continue;

		if (-1==id2)
		if (g_pMainState->m_FightList[id].m_pData->m_IndexType == INDEXTYEP_CHARACTER)
		{//
			cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[id].m_pData->m_pIndex;
			if (!pc->m_PCData.m_FightProperty.cannotMagic)
			{
				switch (pc->m_PCData.m_MengPaiID)
				{
				case eMP_����ɽ:
				case eMP_������:
					id2 = id;
					firstpos = list.size();
					break;
				case eMP_���ܵظ�:
					if (pc->m_PCData.m_LV > 128)
					{
						id2 = id;
						firstpos = list.size();
					}
				}
			}
		}
		cPetData* pPet;
		g_pMainState->m_FightList[id].m_pData->GetDateP(pPet);
		if (!pPet->m_FightProperty.cannotUseItem)
			list.push_back(id);
	}
	if (!list.size())return;
	if (-1 == id2)
	{
		id2 = list[0];
		firstpos =0;
	}
	SetUser(id2);
	BOOL bUse = FALSE;
	if (m_pUserPc)
	{
		eMengPai mengpai = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
		switch (mengpai)
		{
		case eMP_����ɽ:
			if (1)
			{
				//�ؼ�   �����дȺ�
//				if (m_pUserPetData->m_StrongLv > 95)
				{
					int num = 0;
					for (int i2 = start; i2<end; i2++)
					if (m_bNeedlive[i2])num += 1;
					if (num > 2)
					{
						if (CheckCanSkill(3048))
						{
							for (int i2 = start; i2 < end; i2++)
								m_bNeedlive[i2] = FALSE;
							UseMagic(3048);
							bUse = TRUE;
						}
					}
				}
				if (!bUse)
				//����
				if (!m_pUserPetData->m_FightProperty.cannotMagic)
				{
					if (CheckCanSkill(102))
					{
						m_bNeedlive[id2] = FALSE;
						 UseMagic(102);
						 bUse = TRUE;
					}
				}
			}
			break;
		case eMP_������:
			//����
			if (!m_pUserPetData->m_FightProperty.cannotMagic)
			{
				if (CheckCanSkill(37))
				{
					m_bNeedlive[id2] = FALSE;
					UseMagic(37);
					bUse = TRUE;
				}
			}
			break;
		case eMP_���ܵظ�:
			//����
			if (m_pUserPetData->m_LV > 129)
			if (!m_pUserPetData->m_FightProperty.cannotMagic)
			{
				if (CheckCanSkill(37))
				{
					m_bNeedlive[id2] = FALSE;
					UseMagic(37);
					bUse = TRUE;
				}
			}
			break;
		}
	}
	if (!bUse)
	//����
	if (!m_pUserPetData->m_FightProperty.cannotUseItem)
	if (CheckItem(eAIUseItemTypelive))
	{
		m_bNeedlive[m_TargetID] = FALSE;
		 UseItem(eAIUseItemTypelive);
		 bUse = TRUE;
	}
	if (!bUse)return;
	for (int i = firstpos + 1; i < list.size(); i++)
	{
		SetUser(list[firstpos + 1]);
		//����
		if (!m_pUserPetData->m_FightProperty.cannotUseItem)
		if (CheckItem(eAIUseItemTypelive))
		{
			m_bNeedlive[m_TargetID] = FALSE;
			m_bNeedAddHp[m_TargetID] = FALSE;
			m_bNeedAddHpHurt[m_TargetID] = FALSE;
			 UseItem(eAIUseItemTypeHPHurt);
			 return;
		}

	}
}

BOOL cAttackAI::CheckCanSkill(int skillid)
{//���һ�������Ƿ����,���編��,MP����,�򷵻�0
	int dubstbin;
	int skilllv = 0;
	if (skillid < 1000)
	{
		sSkill *skill = g_pMainState->m_SkillManager.GetMengPaiSkill(skillid);
		skilllv = m_pUserPc->m_PCData.m_MengPaiSkillLV[skill->m_Owner];
	}
	return g_pMainState->m_SkillManager.Cost(dubstbin, skilllv, skillid, m_UserID, 5, FALSE);
}

//void cAttackAI::CoutIdleList(int start, int end)
//{
//	int needlist[10];
//	for (int i = start; i < end; i++)
//	{
//		m_IdleList[i] = i;
//	}
//	for (int i = 0; i < 10; i++)
//	{
//		SetUser(i);
//		if (!m_pUserPc)
//		{
//			if (m_pUserPetData->m_AddPoint.hp>1 || m_pUserPetData->m_AddPoint.spd>1)
//			{
//				needlist[i] = 80;
//			}
//			else
//				needlist[i] = 10;
//		}
//		else
//		{
//			eMengPai mp = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
//			switch (mp)
//			{
//			case eMP_���ƹٸ�:
//				needlist[i] = 1;
//				break;
//			case eMP_������:
//				needlist[i] = 99;
//				break;
//			case eMP_Ů����:
//				needlist[i] = 10;
//				break;
//			case eMP_����ɽ:
//				needlist[i] = 10;
//				break;
//			case eMP_ʨ����:
//				needlist[i] = 1;
//				break;
//			case eMP_ħ��կ:
//				needlist[i] = 1;
//				break;
//			case eMP_��˿��:
//				needlist[i] = 10;
//				break;
//			case eMP_���ܵظ�:
//				if (m_pUserPetData->m_AddPoint.atk > 2)
//				{
//					needlist[i] = 10;
//				}
//				else
//				{
//					needlist[i] = 98;
//				}
//				break;
//			case eMP_��������:
//				needlist[i] = 1;
//				break;
//			case eMP_��ׯ��:
//				needlist[i] = 90;
//				break;
//			case eMP_����ɽ:
//				needlist[i] = 95;
//				break;
//			case eMP_�칬:
//				needlist[i] = 80;
//				break;
//			default:
//				needlist[i] = 0;
//				break;
//			}
//		}
//		if (m_pUserPetData->m_FightProperty.cannotMagic)
//		{
//			needlist[i] += 10;
//		}
//		if (m_pUserPetData->m_FightProperty.chaos)
//		{
//			needlist[i] -= 100;
//			continue;
//		}
//		if (g_pMainState->m_FightList[i].m_bDie)
//		{
//			needlist[i] -= 100;
//			continue;
//		}
//	}
//	for (int a = 0; a < 9; a++)
//	for (int b = a + 1; b<10; b++)
//	{
//		if (needlist[a]<needlist[b])//ǰ�����ں���
//		{
//			swap(needlist[a], needlist[b]);
//			swap(m_IdleList[a+start], m_IdleList[b+start]);
//		}
//	}//����	
//}

void cAttackAI::Reset()
{
	cPetData* pPetdata;
	for (int i = 0; i < 20; i++)
	{

		m_bNeedAddHp[i] = 0;//���غϸö����Ƿ���Ҫ��Ѫ
		m_bNeedAddHpHurt[i] = 0;
		m_bNeedUnSeal[i] = 0;//���غϸö����Ƿ���Ҫ���
		m_bNeedlive[i] = 0;
		m_bNeedAddMp[i] = 0;
		//����ɫ�Ƿ񱻷�
		m_bBeSeal[i] = FALSE;
		_isShiFudu[i] = FALSE;
		if (g_pMainState->m_FightList[i].isLive)
		{
			g_pMainState->m_FightList[i].m_pData->GetDateP(pPetdata);
			if (pPetdata->m_FightProperty.cannotMagic && !pPetdata->PeopleSpecial.d2)
				m_bBeSeal[i] = TRUE;
			if (g_pMainState->m_FightList[i].m_pData->CheckHaveState(122))
			{
				_isShiFudu[i] = TRUE;
			}
		}
		
	}
}

BOOL cAttackAI::CheckItem(eAIUseItemType mode)
{
	if (m_UserID % 10 < 5)
	{
		if (m_pUserPc)
		if (m_pUserPc->m_PCData.m_Item[mode].GetNum())
			return TRUE;
	}
	else
	{
		if (INDEXTYEP_CHARACTER == g_pMainState->m_FightList[m_UserID - 5].m_pData->m_IndexType)
		{
			cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[m_UserID - 5].m_pData->m_pIndex;
			if (pc)
			{
				if (pc->m_PCData.m_Item[mode].GetNum())
					return TRUE;
			}

		}
	}
	return FALSE;
}
// ����+2
void cAttackAI::ContentUnSeal(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		if (m_bNeedUnSeal[i])
		{
			SetTarget(i);
			ContentUnSeal2(start, end);
			m_bNeedUnSeal[i] = FALSE;
		}
	}
}
void cAttackAI::ContentUnSeal2(int start, int end)
{
	vector<int> list;
	int id2 = -1;
	int id;
	int firstpos = -1;
	for (int i = 19; i > -1; i--)
	{
		id = g_pMainState->m_pFightState->m_SpeedListPos[i];
		if (id < start || id >= end)continue;
		if (!g_pMainState->m_FightList[id].isLive)continue;
		if (g_pMainState->m_FightList[id].CheckDie())continue;
		if (g_pMainState->m_FightList[id].m_WorkType != -1)continue;
		cPetData* pPet;
		g_pMainState->m_FightList[id].m_pData->GetDateP(pPet);
		if (!pPet->m_FightProperty.cannotUseItem)
			list.push_back(id);
	}
	if (!list.size())return;
	if (-1 == id2)
	{
		id2 = list[0];
		firstpos = 0;
	}
	SetUser(id2);
//	BOOL bUse = FALSE;
	
	int num = 0;
	for (int i2 = start; i2 < end; i2++)
	if (m_bNeedUnSeal[i2])num += 1;
		
		if (m_pUserPc)
		{
			eMengPai mengpai = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
			switch (mengpai)
			{
			case eMP_����ɽ:
			case eMP_��˿��:
			case eMP_���ܵظ�:
			case eMP_��ׯ��:
			case eMP_�칬:
			case eMP_Ů����:
				if (1)
				{
					if (num > 2)
					{
//						switch (m_pUserPetData->m_StrongLv >> 6)
						{
//						case 1:
							if (CheckCanSkill(3013))
							{
								for (int i2 = start; i2 < end; i2++)
								{
									m_bNeedUnSeal[i2] = FALSE;
									if (m_bNeedAddHp[i2]>0)
									{
										m_bNeedAddHp[i2] -= 20;
									}
								}
								return UseMagic(3013);
							}
//						case 0: 
							else 
							if (CheckCanSkill(3012))
							{
								for (int i2 = start; i2 < end; i2++)
									m_bNeedUnSeal[i2] = FALSE;
								return UseMagic(3012);
							}
//							break;
						}
					}
					else
					//�ؼ�   
//					switch (m_pUserPetData->m_StrongLv >> 6)
					{
//					case 1:
						if (CheckCanSkill(3011))
						{
							m_bNeedUnSeal[m_TargetID] = FALSE;
							if (m_bNeedAddHp[m_TargetID]>0)
							m_bNeedAddHp[m_TargetID] -= 20;
							return UseMagic(3013);
						}
						else 
//					case 0:
						if (CheckCanSkill(3010))
						{
								m_bNeedUnSeal[m_TargetID] = FALSE;
							return UseMagic(3012);
						}
//						break;
					}
				}
				break;
			
			}
		}
		//����
		if (!m_pUserPetData->m_FightProperty.cannotUseItem)
		if (CheckItem(eAIUseItemTypeUnseal))
		{
			m_bNeedUnSeal[m_TargetID] = FALSE;
			  UseItem(eAIUseItemTypeUnseal);
			  return;
		}
}

cAttackAI::cAttackAI()
{
	for (int i = 0; i < 20; i++)
	{
		m_FightTarget[i] = -1;
		m_bSeal[i] = FALSE;
		m_bNeedAddHp[i] = 0;//���غϸö����Ƿ���Ҫ��Ѫ
		m_bNeedAddHpHurt[i] = 0;
		m_bNeedUnSeal[i] = 0;//���غϸö����Ƿ���Ҫ���
		m_bNeedlive[i] = 0;
		m_bNeedAddMp[i] = 0;
		m_bBeSeal[i] = 0;//�Ƿ񱻷�
		m_bAtk[i] = 0;//
		_isShiFudu[i] = 0;
	}
}

//int cAttackAI::FintTarget(int id)
//{
//	int targetid;
//	int start, end;
//	if (id < 10)start = 10;
//	else start = 0;
//	end = start + 10;
//
//	if (-1 == m_FightTarget[id])
//	{
//		SetUser(id);
//		if (m_pUserPc)
//		{
//
//			eMengPai mengpai = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
//			switch (mengpai)
//			{
//			case eMP_��ׯ��:
//				if (m_pUserPetData->m_AddPoint.atk < 3)
//				{
//					return FindUnSeal(start, end);
//				}
//			case eMP_���ƹٸ�:
//			case eMP_ʨ����:
//			case eMP_�칬:
//				switch (rand() % 3)
//				{
//				case 0:
//					return FindDefminTarget(start, end, eProPerty����);
//				case 1:
//					return FindDefminTarget(start, end, eProPerty�˺�, 1);
//				case 2:
//					return FindDefminTarget(start, end, eProPerty����, 1);
//				}
//				break;
//			case eMP_������:
//				if (id < 10)start = 0;
//				else start = 10;
//				end = start + 10;
//				return FindDefminTarget(start, end, eProPerty����);
//				break;
//			case eMP_����ɽ:
//					return FindUnSeal(start, end);
//				break;
//			case eMP_ħ��կ:
//			case eMP_��������:
//					return FindDefminTarget(start, end, eProPerty����);
//				break;
//			case eMP_��˿��:
//				if (m_pUserPetData->m_AddPoint.atk > 2)
//					return FindDefminTarget(start, end, eProPerty����);
//				else
//					return FindUnSeal(start, end);
//			case eMP_���ܵظ�:
//				if (m_pUserPetData->m_AddPoint.atk>2)
//					return FindDefminTarget(start, end, eProPerty����);
//			case eMP_����ɽ:
//				switch (rand() % 3)
//				{
//				case 0:
//					return FindDefminTarget(start, end, eProPerty����, 1);
//				case 1:
//					return FindDefminTarget(start, end, eProPerty�˺�, 1);
//				case 2:
//					return FindDefminTarget(start, end, eProPerty����, 1);
//				}
//				break;
//			case eMP_Ů����:
//					return FindUnSeal(start, end);
//			}
//		}
//		else
//		{
//			if (m_pUserPetData->m_AddPoint.atk>2)
//				return FindDefminTarget(start, end, eProPerty����);
//			else
//				return FindDefminTarget(start, end, eProPerty����);
//		}
//	}
//	else
//	{
//		if (!g_pMainState->m_FightList[m_FightTarget[id]].isLive)
//		{
//			return FintTarget(id);
//		}
//		else targetid = m_FightTarget[id];
//	}
//	if (targetid == -1)return -1;
//	SetTarget(targetid);
//	return targetid;
//}

int cAttackAI::FindDefminTarget(int start, int end, eProPerty prop,BOOL maxormin, int userID)
{
	int id=-1;
	for (int i = start; i < end; i++)
	{
		if (g_pMainState->m_FightList[i].isLive)
		{
			id = i;
			break;
		}
	}
	if (-1 == id)return id;
	cPetData *pP1;
	cPetData* pP2;
	for (int i = id + 1; i < end; i++)
	{

		g_pMainState->m_FightList[id].m_pData->GetDateP(pP1);
		if (!g_pMainState->m_FightList[i].isLive)continue;
		g_pMainState->m_FightList[i].m_pData->GetDateP(pP2);
		if (userID != -1)
		{
			cPetData *data = nullptr;
			g_pMainState->m_FightList[userID].m_pData->GetDateP(data);
			if (data && data->PeopleSpecial.d1 < pP2->PeopleSpecial.d2)
			{
				continue;
			}
		}
		if (maxormin)
		{
			switch (prop)
			{
			case eProPerty�˺�:if (pP1->m_ATK.GetData() < pP2->m_ATK.GetData())id = i; break;
			case eProPerty����:if (pP1->m_DEF.GetData() < pP2->m_DEF.GetData())id = i; break;
			case eProPerty����:if (pP1->m_Wakan.GetData() < pP2->m_Wakan.GetData())id = i; break;
			case eProPerty�ٶ�:if (pP1->m_SPD.GetData() < pP2->m_SPD.GetData())id = i; break;
			case eProPerty��Ѫ:	if (pP1->m_HP < pP2->m_HP)id = i;	break;
			}
		}
		else
		{
			switch (prop)
			{
			case eProPerty�˺�:if (pP1->m_ATK.GetData() > pP2->m_ATK.GetData())id = i; break;
			case eProPerty����:if (pP1->m_DEF.GetData() > pP2->m_DEF.GetData())id = i; break;
			case eProPerty����:if (pP1->m_Wakan.GetData() > pP2->m_Wakan.GetData())id = i; break;
			case eProPerty�ٶ�:if (pP1->m_SPD.GetData() > pP2->m_SPD.GetData())id = i; break;
			case eProPerty��Ѫ:	if (pP1->m_HP > pP2->m_HP)id = i;	break;
			}
		}
	}
	return id;
}

int cAttackAI::findʬ��������()
{
	int id = -1;
	int start = m_UserID < 10 ? 10 : 0;
	int end = start + 10;
	cPetData *data = nullptr;
	g_pMainState->m_FightList[m_UserID].m_pData->GetDateP(data);
	for (int i = start; i < end; i++)
	{
		if (_isShiFudu[i])continue;
		if (!g_pMainState->m_FightList[i].isLive)continue;
		if (g_pMainState->m_FightList[i].m_pData->CheckHaveState(122))continue;
		cPetData *data2 = nullptr;
		g_pMainState->m_FightList[i].m_pData->GetDateP(data2);
		if (data2->m_race >= 1000 || data->PeopleSpecial.d1 < data2->PeopleSpecial.d2)continue;
		id = i;
		break;
	}
	if (-1 == id)
		return -1;
	cPetData *pP1;
	cPetData* pP2;
	for (int i = id + 1; i < end; i++)
	{
		if (_isShiFudu[i])continue;
		g_pMainState->m_FightList[id].m_pData->GetDateP(pP1);
		if (!g_pMainState->m_FightList[i].isLive)continue;
		if(g_pMainState->m_FightList[i].m_pData->CheckHaveState(122))continue;
		g_pMainState->m_FightList[i].m_pData->GetDateP(pP2);
		if (data->PeopleSpecial.d1 < pP2->PeopleSpecial.d2 || pP2->m_race >= 1000)
		{
			continue;
		}
		if (pP1->m_HP < pP2->m_HP)id = i;
	}
	return id;
}

int cAttackAI::FindUnSeal(int start, int end)
{
	int num = end - start;
	int id = rand()%num+start;
	for (int i = 0; i < num+1; i++)
	{
		if (g_pMainState->m_FightList[id].isLive)
		{
			if ((!m_bBeSeal[id]) && (!m_bSeal[id]))
			{
//				m_bSeal[id] = TRUE;
				return id;
			}
		}
		id += 1;
		if (id == end)
			id = start;
	}

	return -1;
}

int cAttackAI::FindUnSeal(int num)
{
	int start, end;
	if (m_UserID < 10)
		start = 10;
	else start = 0;
	end = start + num;
	return FindUnSeal(start, end);
}

int cAttackAI::FindUnSeal(char &isMorA)
{
	vector<POINT> out;
	FindEnemy(TRUE, FALSE, out, eET��ӡ����, m_UserID < 10 ? 10 : 0);
// 	int star = m_UserID < 10 ? 10 : 0;
// 	for (int i = star; i < star + 10; ++i)
	forv(out, i)
	{
		if (FindUnSeal(out[i].x, isMorA))
		{
			return out[i].x;
		}
	}
	return -1;

// 	auto func = [&](const std::function<bool(int, bool, const cPetData*)> &f)
// 	{
// 		int star = m_UserID < 10 ? 10 : 0;
// 		for (int i = star; i < star + 10; ++i)
// 		{
// 			if (!g_pMainState->m_FightList[i].isExist)
// 			{
// 				continue;
// 			}
// 			if (m_bBeSeal[i] || m_bSeal[i])
// 			{
// 				continue;
// 			}
// 			cPetData *data = nullptr;
// 			g_pMainState->m_FightList[i].m_pData->GetDateP(data);
// 			if (!data)
// 			{
// 				continue;
// 			}
// 			if (data->PeopleSpecial.d2 > 0 || data->m_race >= 1000 ||
// 				g_pMainState->m_FightList[i].m_pData->CheckHaveState(0)|| 
// 				g_pMainState->m_FightList[i].m_pData->CheckHaveState(7) ||
// 				g_pMainState->m_FightList[i].m_pData->CheckHaveState(142)||
// 				g_pMainState->m_FightList[i].m_pData->CheckHaveState(148))
// 			{
// 				continue;
// 			}	
// 			if (f(i, g_pMainState->m_FightList[i].m_pData->m_IndexType == INDEXTYEP_CHARACTER, data))
// 			{
// 				return i;
// 			}
// 		}
// 		return -1;
// 	};
// 
// 	int id = func([&](int i, bool isPc, const cPetData *data)
// 	{
// 		isMorA = 1;
// 		return isPc && !data->m_FightProperty.cannotMagic;
// 	});
// 	if (id < 0)
// 	{
// 		id = func([&](int i, bool isPc, const cPetData *data)
// 		{
// 			if (!isPc && data->m_ProPertyAtk >= data->m_LV * 3)
// 			{
// 				vector<int> ms, m2s, ps, bs;
// 				if (isHadPetSkill((cPetData*)data, bs, ps, ms, m2s))
// 				{
// 					if (ps.size() && !data->m_FightProperty.cannotMagic)
// 					{
// 						isMorA = 1;
// 						return true;
// 					}
// 					
// 					if (!ps.size() && !data->m_FightProperty.cannotAttack)
// 					{
// 						isMorA = 0;
// 						return true;
// 					}
// 				}
// 			}
// 			return false;
// 		});
// 	}
// 	if (id < 0)
// 	{
// 		id = func([&](int i, bool isPc, const cPetData *data)
// 		{
// 			if (isPc && !data->m_FightProperty.cannotSkill && data->m_CP >= 80)
// 			{
// 				isMorA = 2;
// 				return true;
// 			}
// 			return false;
// 		});
// 	}
// 
// 	return id;
}

bool cAttackAI::FindUnSeal(int i, char &isMorA)
{
	if (i < 0)
	{
		return false;
	}
	if (!g_pMainState->m_FightList[i].isLive)
	{
		return false;
	}
	if (m_bBeSeal[i] || m_bSeal[i])
	{
		return false;
	}
	cPetData *data = nullptr;
	g_pMainState->m_FightList[i].m_pData->GetDateP(data);
	if (!data)
	{
		return false;
	}
	if (data->PeopleSpecial.d2 > 0 || data->m_race >= 1000 ||
		g_pMainState->m_FightList[i].m_pData->CheckHaveState(0) ||
		g_pMainState->m_FightList[i].m_pData->CheckHaveState(7) ||
		g_pMainState->m_FightList[i].m_pData->CheckHaveState(142))// ||
// 		g_pMainState->m_FightList[i].m_pData->CheckHaveState(148))
	{
		return false;
	}
	if (rand() % 100 < data->restoreRate)
	{
		return false;
	}

	bool isPc = g_pMainState->m_FightList[i].m_pData->m_IndexType == INDEXTYEP_CHARACTER;

	if (isPc && !data->m_FightProperty.cannotMagic)
	{
		isMorA = 1;
		return true;
	}


	if (!isPc && data->m_ProPertyAtk >= data->m_LV * 3)
	{
		vector<int> ms, m2s, ps, bs;
		if (isHadPetSkill((cPetData*)data, bs, ps, ms, m2s))
		{
			if (ps.size() && !data->m_FightProperty.cannotMagic)
			{
				isMorA = 1;
				return true;
			}

			if (!ps.size() && !data->m_FightProperty.cannotAttack)
			{
				isMorA = 0;
				return true;
			}
		}
	}

	if (isPc && !data->m_FightProperty.cannotSkill && data->m_CP >= 80)
	{
		isMorA = 2;
		return true;
	}

	return false;
}

int cAttackAI::FindAtkTarget(int rate, BOOL ATKOrMagic, int userID /* = -1 */)
{ 
	//Ѱ����������������м�ֵ�Ķ���
	int start, end;
	if (m_UserID < 10)start = 10;
	else start = 0;
	end = start + 10;
	int num = end - start;
	int id = rand() % num+start;
	int idret = -1;
	int damage = 0;
	int damage2;
	int DamageAddPercent;
	int DamageDefAddPercent;
	for (int i = 0; i < num+1; i++)
	{
		if (g_pMainState->m_FightList[id].isLive)
		if (!g_pMainState->m_FightList[id].CheckDie())
		{
			if (userID != -1)
			{
				cPetData *data = nullptr;
				g_pMainState->m_FightList[userID].m_pData->GetDateP(data);
				cPetData *data2 = nullptr;
				g_pMainState->m_FightList[id].m_pData->GetDateP(data2);
				if (data && data->PeopleSpecial.d1 < data2->PeopleSpecial.d2)
				{
					if (++id >= end)
					{
						id = start;
					}
					continue;
				}
			}
			SetTarget(id);
			int targethp = m_pTargetPetData->m_HP - m_bAtk[id];
			if (ATKOrMagic)
			{
				DamageAddPercent = m_pUserPetData->m_DamagePercent.d1; //����������
				DamageDefAddPercent = m_pTargetPetData->m_DamagePercent.d2;   //Ŀ���������
				damage2 = (m_pUserPetData->m_ATK.GetData() - m_pTargetPetData->m_DEF.GetData()) * rate / 100;
// 				int prr =  m_pTargetPetData->m_ParryRate.d1 - m_pUserPetData->m_ParryRate.d2;
// 				if (prr > 100)
// 				{
// 					prr = 100;
// 				}
// 				damage2 = damage2 * prr / 200;
			}
			else
			{
				DamageAddPercent = m_pUserPetData->m_DamageAddPercentMagic.d1; //��������������
				DamageDefAddPercent = m_pTargetPetData->m_DamageAddPercentMagic.d2;   //Ŀ�귨����������
				damage2 = (m_pUserPetData->m_LV * 3 + m_pUserPetData->m_ATK.GetData() / 6 + m_pUserPetData->m_Wakan.GetData() - m_pTargetPetData->m_Wakan.GetData()) * rate / 100;
			}
			damage2 = damage2 * (100 + DamageAddPercent - DamageDefAddPercent) / 100;//��������
			if (damage2 > targethp)
			{
				//���ֵ�HPԽ��Խ��    �ҷ����˺�Խ��Խ��
				damage2 = (targethp << 2) - damage2;
			}
			
			if (-1 == idret)
			{
				idret = id;
				damage = damage2;
			}
			else
			{
				if (m_pTargetPetData->m_HP - m_bAtk[id] < 1)
				{
					continue;
				}
				if (damage2 > damage)
				{
					idret = id;
					damage = damage2;
				}
			}
		}
		id += 1;
		if (id >= end)
		{
			id = start;
		}
	}
	if (idret > -1)
	{
		m_bAtk[idret] += damage; //��¼���󵥻غ��ܵ����˺���Ԥ��ֵ
	}
	return idret;
}

int cAttackAI::FindCpMaxTarget(int num/*=100*/)
{
	int start, end;
	if (m_UserID < 10)start = 10;
	else start = 5;
	end = start + 5;
	cPetData* petdata;
	int id = rand() % 5 + start;
	for (int i = 0; i < 5; i++)
	{
		if (!g_pMainState->m_FightList[id].isLive)continue;
		g_pMainState->m_FightList[id].m_pData->GetDateP(petdata);
		if (petdata->m_CP>num)
		{
			return id;
		}
		id += 1;
		if (id >= end)id = start;
	}
	return -1;
}

BOOL cAttackAI::CheckHaveState(int userid, int skillid)
{
	return g_pMainState->m_FightList[userid].m_pData->CheckHaveState(skillid);
}

void cAttackAI::NpcTryMagic(int id)
{
	if (CheckCanSkill(id))
	{
		return UseMagic(id);
	}
	else
	{
		if (m_UserID<10 && m_TargetID<10)
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		else
		if (m_UserID > 9 && m_TargetID > 9)
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		if(m_TargetID < 0)
		{
			if (m_UserID < 10 && m_TargetID < 10)
				SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, false));
			else
				if (m_UserID > 9 && m_TargetID > 9)
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, false));
		}
		return NormalAtk();
	}
}

bool cAttackAI::isHadPetSkill(cPetData *data, vector<int> &buffSkills, vector<int> &pSkills, vector<int> &mSkills, vector<int> &m2Skills)
{
// 	if (!g_pMainState->m_FightList[userID].isExist)return false;
// 	cPetData *data = nullptr;
// 	g_pMainState->m_FightList[userID].m_pData->GetDateP(data);
	if (!data)return false;
	vector<sSkill*> skills;
	for (int j = 0; j < data->m_NumofBBSkill; j++)
	{
		skills.push_back(data->m_pPetSkill[j]);
		continue;
		sSkill *skill = data->m_pPetSkill[j];
		int id = skill->m_Id;
		switch (skill->m_SkillType)
		{
		case 4:
			if (id == 92 || id == 93 || id == 94 || id == 95 || id == 96 || id == 98 || id == 99 || id == 100 || id == 102)
			{
				pSkills.push_back(id + 2000);
			}
			else if (g_pMainState->m_SkillManager.GetPetSkill(id)->m_TargetNum > 1)
			{
				m2Skills.push_back(id + 2000);
			}
			else
			{
				mSkills.push_back(id + 2000);
			}
			break;
		case 7:continue;
		default:
			buffSkills.push_back(id + 2000);
			break;
		}
	}
	return isHadPetSkill(skills, buffSkills, pSkills, mSkills, m2Skills);
}

bool cAttackAI::isHadPetSkill(const vector<sSkill*> &skills, vector<int> &buffSkills, vector<int> &pSkills, vector<int> &mSkills, vector<int> &m2Skills)
{
	for (const auto &skill : skills)
	{
//		sSkill *skill = data->m_pPetSkill[j];
		int id = skill->m_Id;
		switch (skill->m_SkillType)
		{
		case 4:
			if (id == 92 || id == 93 || id == 94 || id == 95 || id == 96 || id == 98 || id == 99 || id == 100 || id == 102)
			{
				pSkills.push_back(id + 2000);
			}
			else if (g_pMainState->m_SkillManager.GetPetSkill(id)->m_TargetNum > 1)
			{
				m2Skills.push_back(id + 2000);
			}
			else
			{
				mSkills.push_back(id + 2000);
			}
			break;
		case 7:continue;
		default:
			buffSkills.push_back(id + 2000);
			break;
		}
	}
	return true;
}

int cAttackAI::RunPet()
{
	bool isAtk = m_pUserPetData->m_ProPertyMag == m_pUserPetData->m_LV;
	SetTarget(m_FightTarget[m_UserID]);
	bool isTar = true;
	if (m_TargetID < 0)
	{
		isTar = false;
		SetTarget(FindAtkTarget(100, isAtk, m_UserID));
	}
	if (m_pUserPetData->m_FightProperty.cannotMagic)
	{
		if (isAtk && m_TargetID >= 0)
		{
			NormalAtk();
			return 1;
		}
		return 0;
		Def(m_UserID);
	}

// 	//Ѱ��Ŀ��
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
// 		
// 	}
// 	else
// 	{
// //		int targetid = g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, true);
// 		int targetid = FindAtkTarget(100, isAtk, m_UserID);
// 		if (targetid == -1)
// 		{
// 			if (runSelfunseal())
// 			{
// 				return;
// 			}
// 			return defense(m_UserID);
// 		}
// 		SetTarget(targetid);
// 	}

	vector<int> ms, m2s, ps, bs;
	if (!isHadPetSkill(m_pUserPetData, bs, ps, ms, m2s))
	{
		return 0;
	}
	if (!MyTest::getInstance()->isAtkMode(m_UserID) && bs.size())
	{
		int s = bs[rand() % bs.size()];
		if (!m_pUser->CheckHaveState(s) && CheckCanSkill(s))
		{
			SetTarget(m_UserID);
			UseMagic(s);
			return 2;
		}
	}

	if (!m2s.size() && !ps.size() && !ms.size())
	{
		if (MyTest::getInstance()->isAtkMode(m_UserID) || isAtk)
		{
			NormalAtk();
			return 1;
		}
		return 0;
		Def(m_UserID);
		
	}

	auto isCan = [&](const vector<int> &ss)
	{
		if (!ss.size())
		{
			return -1;
		}
		bool isCan = false;
		int s;
		for (int i = 0; i < 99; ++i)
		{
			s = ss[rand() % ss.size()];
			if (CheckCanSkill(s))
			{
				isCan = true;
				break;
			}
		}
		if (isCan)
		{
			return s;
		}
		return -1;
	};

	auto runM2s = [&]()
	{
		if (!m2s.size())
		{
			return false;
		}

		int s = -1;
		if (getVisibleNO() < 2)
		{
			forr(m2s, i)
			{
				if (m2s[i] == 2105 && CheckCanSkill(2105))
				{
					s = 2105;
					break;
				}
			}
		}
		if (s == -1)
		{
			s = isCan(m2s);
		}
		if (s >= 0)
		{
			UseMagic(s);
			return true;
		}
		return false;
	};

	auto runPs = [&]()
	{
		int s = isCan(ps);
		if (s >= 0)
		{
			if (isTar)
			{
				UseMagic(s);
				return true;
			}
			int self = m_UserID < 10 ? 10 : 0;
			if (s == 2095)
			{
				vector<POINT> out;
				FindEnemy(TRUE, FALSE, out, eET������ɽ95, self);
				auto out2 = check����(out, m_UserID);
				if (out2.size())
				{
					SetTarget(out2.front());
				}
// 				int id = -1;
// 				int start = m_UserID < 10 ? 10 : 0;
// 				for (int i = start; i < start + 10; i++)
// 				{
// 					if (g_pMainState->m_FightList[i].isExist)
// 					{
// 						id = i;
// 						break;
// 					}
// 				}
// 				if (id >= 0)
// 				{
// 					cPetData *pP1;
// 					cPetData* pP2;
// 					for (int i = id + 1; i < start + 10; i++)
// 					{
// 
// 						g_pMainState->m_FightList[id].m_pData->GetDateP(pP1);
// 						if (!g_pMainState->m_FightList[i].isExist)continue;
// 						g_pMainState->m_FightList[i].m_pData->GetDateP(pP2);
// 						if (m_pUserPetData->PeopleSpecial.d1 < pP2->PeopleSpecial.d2)
// 						{
// 							continue;
// 						}
// 						if (pP1->m_ATK.GetData() + pP1->m_DEF.GetData() > pP2->m_ATK.GetData() + pP2->m_DEF.GetData())
// 						{
// 							id = i;
// 						}
// 					}
// 				}
// 				if (id >= 0)
// 				{
// 					SetTarget(id);
// 				}
			}
			else if (s == 2099)
			{
				vector<POINT> out;
				FindEnemy(TRUE, FALSE, out, eET���ݻ���99, self);
				auto out2 = check����(out, m_UserID);
				if (out2.size())
				{
					SetTarget(out2.front());
				}
			}
			else if (s == 2094)
			{
				SetTarget(FindDefminTarget(eProPerty��Ѫ, false));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(s);
				return true;
			}
		} 
		return false;
	};

	auto runMs = [&]()
	{
		int s = isCan(ms);
		if (s >= 0)
		{
			UseMagic(s);
			return true;
		}
		return false;
	};

	if (isAtk)
	{
		if (runPs())
		{
			return 3;
		}
		NormalAtk();
		return 1;
	}
	if (getVisibleNO() > 1 || !ms.size())
	{
		if (runM2s())
		{
			return 4;
		}
	}
	if (runMs())
	{
		return 4;
	}

	return 0;

// 
// 	//Ѱ�Ҽ���
// 	vector<sSkill*> skilllist;
// 	BOOL bHaveBuff=FALSE;//�Ƿ��״̬����
// 	BOOL bHaveMagic=FALSE;//�Ƿ�ᵥ��
// 	BOOL bHaveMagic2=FALSE;//�Ƿ��Ⱥ��
// 	for (int j = 0; j < m_pUserPetData->m_NumofBBSkill; j++)
// 	{
// 		switch (m_pUserPetData->m_pPetSkill[j]->m_SkillType)
// 		{
// 		case 4:
// 			if (1)
// 			{
// 				if (1<g_pMainState->m_SkillManager.GetPetSkill(m_pUserPetData->m_pPetSkill[j]->m_Id)->m_TargetNum)
// 				{
// 					bHaveMagic2 = TRUE;
// 				}
// 				else bHaveMagic = TRUE;
// 			}
// 			break;
// 		case 7:continue;
// 		default:
// 			bHaveBuff = TRUE;
// 			break;
// 		}
// 		skilllist.push_back(m_pUserPetData->m_pPetSkill[j]);
// 	}
// 	//�������������
// 	if (skilllist.size())
// 	{
// 		if (bHaveBuff)
// 		{
// 			if (rand() % 3 == 1)
// 			{
// 				//״̬�෨��
// 				for (int i = 0; i < skilllist.size(); i++)
// 				{
// 					if (skilllist[i]->m_SkillType == 2)
// 					{
// 						int skillid = skilllist[i]->m_Id + 2000;
// 						if (!m_pUser->CheckHaveState(skillid))
// 						{
// 							if (CheckCanSkill(skillid))
// 							{
// 								SetTarget(m_UserID);
// 								return UseMagic(skillid);
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 		if (bHaveMagic && (0 == bHaveMagic2))
// 		{
// 			for (int i = 0; i < skilllist.size(); i++)
// 			{//����
// 				if (g_pMainState->m_SkillManager.m_PetSkillList[skilllist[i]->m_Id].m_EffectType == 0)
// 				{
// 					return NpcTryMagic(2000 + skilllist[i]->m_Id);
// 				}
// 			}
// 		}
// 		else
// 		if ((0==bHaveMagic) && bHaveMagic2)
// 		{
// 			for (int i = 0; i < skilllist.size(); i++)
// 			{//��Ⱥ��
// 				if (g_pMainState->m_SkillManager.m_PetSkillList[skilllist[i]->m_Id].m_EffectType == -3)
// 				{
// 					return NpcTryMagic(2000 + skilllist[i]->m_Id);
// 				}
// 			}
// 		}
// 		else
// 		if (bHaveMagic&& bHaveMagic2)
// 		{
// 			//ʹ�õ�����Ⱥ��
// 			int start, end;
// 			if (m_UserID<10)start = 10;
// 			else start = 0;
// 			end = start + 10;
// 			if (g_pMainState->GetLiveNum(start, end) > 1)
// 			for (int i = 0; i < skilllist.size(); i++)
// 			{//��Ⱥ��
// 				if (g_pMainState->m_SkillManager.m_PetSkillList[skilllist[i]->m_Id].m_EffectType == -3)
// 				{
// 					return NpcTryMagic(2000 + skilllist[i]->m_Id);
// 				}
// 			}
// 
// 			for (int i = 0; i < skilllist.size(); i++)
// 			{//����
// 				if (g_pMainState->m_SkillManager.m_PetSkillList[skilllist[i]->m_Id].m_EffectType == 0)
// 				{
// 					return NpcTryMagic(2000 + skilllist[i]->m_Id);
// 				}
// 			}
// 		}
// 		
// 	}
// 	if (m_pUserPetData->m_ProPertyAtk < m_pUserPetData->m_LV * 2)
// 		return defense(m_UserID);
// 	return	NormalAtk();

}

void cAttackAI::Summon(int id)
{
	g_pMainState->m_FightList[m_UserID].m_SkillSelect.SkillID = 1004;
	g_pMainState->m_FightList[m_UserID].m_SkillSelect.TargetID = g_pMainState->m_FightList[m_UserID].m_FriendListid + 5;
	g_pMainState->m_FightList[m_UserID].m_SkillSelect.Lv = id;
	g_pMainState->m_FightList[m_UserID].m_WorkType = WORKTYPE_SUMMON;
}

int cAttackAI::FindEnemy(BOOL CheckDie,BOOL bCheckWork,vector<POINT>& out, eEnemyType type, int userid, int data, int data2)
{
	out.clear();
	int ret=0;
	vector<POINT> out2;
	cPetData* pPet;
	POINT pt;
	cCharacter* pc;
	int randstart, randend;
	if (userid<10)randstart = 0; else randstart = 10;
	randend = randstart + 10;
	for (int i = randstart; i < randend; i++)
	{
		sFightList& list = g_pMainState->m_FightList[i];

		if (list.m_pData->m_IndexType == INDEXTYEP_CHARACTER)pc = (cCharacter*)list.m_pData->m_pIndex;
		else pc = 0;
		if (!list.isLive)continue;
		list.m_pData->GetDateP(pPet);
		if (bCheckWork)if (list.m_WorkType!=-1)continue;
		if (CheckDie)if (pPet->m_HP < 1)continue;
		
		if (-1 < data)
		if (list.m_pData->CheckHaveState(data))
			continue;
		if (-1 < data2)
		if (list.m_pData->CheckHaveState(data2))
			continue;
			switch (type)
			{
// 			case cAttackAI::eET����:
// 				if (pc)continue;
			case cAttackAI::eET�Ͻ��33:
//				if (pPet->m_AddPoint.atk >= 1)//����1�����ϵĶ���Ϊ����ϵ
				if( (!pc && pPet->m_ProPertyAtk > pPet->m_LV) || (pc && 
					pc->m_PCData.m_MengPaiID != eMP_����ɽ && 
					pc->m_PCData.m_MengPaiID != eMP_������ &&
					pc->m_PCData.m_MengPaiID != eMP_����ɽ &&
					pc->m_PCData.m_MengPaiID != eMP_�������� &&
					pc->m_PCData.m_MengPaiID != eMP_ħ��կ))
				{

					pt.x = i;
					pt.y = pPet->m_ATK.GetData();
					out.push_back(pt);
					ret += 1;
				}
				else
				{
					pt.x = i;
					pt.y = list._speedOfBattle;
					out2.push_back(pt);
				}
				break;

			case cAttackAI::eET���鶯112:
				if (!pc && pPet->m_ProPertyMag > pPet->m_LV)
				{
					pt.x = i;
					pt.y = pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
				}
				else if (pc && pc->m_PCData.m_MengPaiID != eMP_���ƹٸ� &&
					pc->m_PCData.m_MengPaiID != eMP_Ů���� &&
					pc->m_PCData.m_MengPaiID != eMP_����ɽ &&
					pc->m_PCData.m_MengPaiID != eMP_��ׯ�� &&
					pc->m_PCData.m_MengPaiID != eMP_���ܵظ� && 
					pc->m_PCData.m_MengPaiID != eMP_ʨ����)
				{
					pt.x = i;
					pt.y = pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
				}
				else
				{
					pt.x = i;
					pt.y = list._speedOfBattle;
					out2.push_back(pt);
				}
				break;

			case cAttackAI::eET��ӡ����:
// 					eMP_���ƹٸ�,
// 					eMP_������,
// 					eMP_Ů����,
// 					eMP_����ɽ,
// 					eMP_ʨ����,
// 					eMP_ħ��կ,
// 					eMP_��˿��,
// 					eMP_���ܵظ�,
// 					eMP_��������,
// 					eMP_��ׯ��,
// 					eMP_����ɽ,
// 					eMP_�칬,
				if (pc && (pc->m_PCData.m_MengPaiID == eMP_����ɽ ||
					pc->m_PCData.m_MengPaiID == eMP_Ů���� ||
					pc->m_PCData.m_MengPaiID == eMP_��˿�� ||
					pc->m_PCData.m_MengPaiID == eMP_��ׯ�� ||
					pc->m_PCData.m_MengPaiID == eMP_�칬))
				{
					pt.x = i;
					pt.y = 20 - list._speedOfBattle;
					out.push_back(pt);
					ret += 1;
				}
				else
				{
					pt.x = i;
					pt.y = list._speedOfBattle;
					out2.push_back(pt);
				}
				break;

// 			case cAttackAI::eET����:
// 				if (pc)continue;
			case cAttackAI::eET�ٶ����2:
// 				if (pPet->m_AddPoint.mp >= 1)//����1ħ���ϵĶ���Ϊ��ϵ
// 				if ((!pc && pPet->m_ProPertyMag > pPet->m_LV) || 
// 					(pc
// 					pc->m_PCData.m_MengPaiID != eMP_���ƹٸ� &&
// 					pc->m_PCData.m_MengPaiID != eMP_Ů���� &&
// 					pc->m_PCData.m_MengPaiID != eMP_����ɽ &&
// 					pc->m_PCData.m_MengPaiID != eMP_��ׯ�� &&
// 					pc->m_PCData.m_MengPaiID != eMP_���ܵظ� && 
// 					pc->m_PCData.m_MengPaiID != eMP_ʨ����))
// 				if (!pc)
// 				{
// 					continue;
// 				}
				pt.x = i;
				pt.y = list._speedOfBattle; // pPet->m_SPD.GetData();
				out.push_back(pt);
				ret += 1;
				break;
			case cAttackAI::eET�ɷ�ϵ:
				if (!pc)continue;
				if (pPet->m_FightProperty.cannotMagic)continue;
				switch (pc->m_PCData.m_MengPaiID)
				{
				case eMP_Ů����:
				case eMP_����ɽ:
				case eMP_��˿��:
				case eMP_��ׯ��:
				case eMP_�칬:
					pt.x = i;
					pt.y = list._speedOfBattle;
					out.push_back(pt);
					ret += 1;
					break;
				}
				break;
			case cAttackAI::eET�ɷ�ϵ:
				if (pPet->m_FightProperty.cannotMagic)continue;
				if ((pc && (pc->m_PCData.m_MengPaiID == eMP_�������� || pc->m_PCData.m_MengPaiID == eMP_ħ��կ)) ||
					(!pc && pPet->m_ProPertyMag > pPet->m_LV * 3))
				{
					pt.x = i;
					pt.y = pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
					break;
				}
				break;
			case cAttackAI::eET������ϵ:
				if (pPet->m_FightProperty.cannotMagic && pPet->m_FightProperty.cannotSkill)continue;
				if ((pc && (pc->m_PCData.m_MengPaiID == eMP_���ƹٸ� || pc->m_PCData.m_MengPaiID == eMP_ʨ����)) ||
					(!pc && pPet->m_ProPertyAtk > pPet->m_LV * 3))
				{
					pt.x = i;
					pt.y = pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
					break;
				}
				break;
			case cAttackAI::eETѪ����:
				if (pPet->m_HP < 1)
					pt.y = 100;
				else
				{
					pt.y = (100 * pPet->m_HP) / pPet->m_HPMax.GetData();
					if (pt.y < m_HPLimit)ret += 1;
					pt.y = -pt.y;
				}
				pt.x = i;
				out.push_back(pt);
				break;
// 			case cAttackAI::eET��Ҫ��ϵ:
// 				if (pc)
// 				{
// 					switch (pc->m_PCData.m_MengPaiID)
// 					{
// 					case eMP_���ƹٸ�:continue;
// 					case eMP_��������:continue;
// 					case eMP_ħ��կ:continue;
// 					default:
// 						pt.y = -(100 * pc->m_PCData.m_MP) / pc->m_PCData.m_MPMax.GetData();
// 						pt.x = i;
// 						out.push_back(pt);
// 						break;
// 					}
// 				}
// 				break;
			case cAttackAI::eETҽ��ϵ:
				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
				if (!pc)continue;
				if (pc->m_PCData.m_HP < 1)continue;
				switch (pc->m_PCData.m_MengPaiID)
				{
//				case eMP_��ׯ��:
				case eMP_������:
				case eMP_����ɽ:
				case eMP_���ܵظ�:
					pt.y = list._speedOfBattle; // pPet->m_SPD.GetData();
					pt.x = i;
					out.push_back(pt);
					ret += 1;
					break;	
				}
				break;
// 			case cAttackAI::eETѪ��:
// 				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
// 				if (pc)continue;		
// 				if (pPet->m_ProPertyHP > pPet->m_LV * 2)
// 				{
// 					pt.x = i;
// 					pt.y = list._speedOfBattle; // pPet->m_SPD.GetData();
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
// 			case cAttackAI::eET����������:
// 				if (!pc)continue;
// 				if (list.m_pData->CheckHaveState(2094) || list.m_pData->CheckHaveState(129))
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}	
// 				break;
			case cAttackAI::eET�����:
				pt.x = i;
				pt.y = -pPet->m_DEF.GetData();
				out.push_back(pt);
				ret += 1;
				break;
			case cAttackAI::eET�����:
				pt.x = i;
				pt.y = -pPet->m_Wakan.GetData();
				out.push_back(pt);
				ret += 1;
				break;
// 			case cAttackAI::eET��������:
// 				if (!pc)continue;
// 				if (pc->m_PCData.m_FightProperty.cannotAttack && !pc->m_PCData.PeopleSpecial.d2)
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
// 			case cAttackAI::eET���ⷨ��:
// 				if (!pc)continue;
// 				if (pc->m_PCData.m_FightProperty.cannotMagic)
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
// 			case cAttackAI::eET������:
// 				if (!pc)continue;
// 				if (pc->m_PCData.m_FightProperty.cannotAddHP)
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
			case cAttackAI::eET���ٻ���:
				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
				if (i > 14)continue;
				if (!pc)continue;
				if (!g_pMainState->m_FightList[i + 5].isLive)
				{
					for (int i2 = 0; i2 < pc->m_PCData.m_NumofBB; i2++)
					if (pc->m_PCData.m_pPetDataList[i2]->m_PetDataZZ.m_HP > 1)
					{
						pt.x = i;
						pt.y = 1;
						out.push_back(pt);
						ret += 1;
					}
				}
				break;
			case cAttackAI::eET��������:
				if (!pc)continue;
				if (0 == pPet->m_HP)
				{
					if (list.m_pData->CheckHaveState(2094))continue;//����
					if (list.m_pData->CheckHaveState(129))continue;//������
					pt.x = i;
					pt.y = 1;
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAttackAI::eET�ٶ����:
				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
// 				if (pc)
// 				{
// 					switch (pc->m_PCData.m_MengPaiID)
// 					{
// 					case eMP_������:
// 					case eMP_���ܵظ�:
// 					case eMP_����ɽ:
// 						pt.y = pPet->m_SPD.GetData() * 5 / 4;
// 						break;
// 					case eMP_��ׯ��:
// 					case eMP_Ů����:
// 					case eMP_����ɽ:
// 					case eMP_��˿��:
// 					case eMP_�칬:
// 						pt.y = pPet->m_SPD.GetData() * 6 / 4;
// 						break;
// 					default:
// 						pt.y = pPet->m_SPD.GetData() * 4 / 4;
// 						break;
// 
// 					}
// 				}
// 				else
// 				{
// 					pt.y = pPet->m_SPD.GetData() * 7 / 4;
// 				}

				pt.x = i;
				pt.y = list._speedOfBattle;
				out.push_back(pt);
				ret += 1;
				break;
			case eET��Ѫ:
				if (list.CheckDie())continue;
				if (pPet->m_FightProperty.cannotAll)continue;
				if (pPet->PeopleSpecial.d2)continue;
				if (pc)
				{
					switch (pc->m_PCData.m_MengPaiID)
					{
					case eMP_������:
					case eMP_���ܵظ�:
					case eMP_����ɽ:
						pt.y = 10;			
						break;
					case eMP_��ׯ��:
						pt.y = 9;
						break;
					case eMP_Ů����:
					case eMP_����ɽ:
					case eMP_��˿��:
					case eMP_�칬:
						pt.y = 5;
						break;
					default:
						pt.y = 4;
						break;

					}
				}
				else
				{
					pt.y = 5 + pPet->m_ProPertyHP / (pPet->m_LV + 1);
// 					if (pPet->m_ProPertyMag / pPet->m_LV > pPet->m_ProPertyAtk / pPet->m_LV)
// 					{
// 						pt.y = 14 - pPet->m_ProPertyMag / pPet->m_LV;
// 					}
// 					else
// 					{
// 						pt.y = 14 - pPet->m_ProPertyAtk / pPet->m_LV;
// 					}
				}
				pt.x = i;
				out.push_back(pt);
				ret += 1;
				break;
// 			case eET���:
// 				if (list.CheckDie())break;
// 				if (pPet->m_FightProperty.cannotAll)break;
// 				if (pc)
// 				{
// 					pt.y = 1;
// 				}
// 				else
// 				{
// 					pt.y = 2 + pPet->m_ProPertyHP / (pPet->m_LV + 1);
// 
// 					if (pPet->m_AddPoint.mp > 0 || pPet->m_AddPoint.atk > 0)
// 					{
// 						if (pPet->m_AddPoint.mp > 2 || pPet->m_AddPoint.atk > 2)
// 						{
// 							if (pPet->m_AddPoint.mp > 4 || pPet->m_AddPoint.atk > 4)
// 							{
// 								pt.y = 5;
// 							}
// 							else
// 							{
// 								pt.y = 4;
// 							}
// 						}
// 						else
// 						{
// 							pt.y = 3;
// 						}
// 						out.push_back(pt);
// 					}
// 					else
// 					{
// 						pt.y = 2;
// 					}
// 					break;
// 				}
// 				pt.x = i;
// 				out.push_back(pt);
// 				ret += 1;
// 				break;

			case cAttackAI::eET���ޱ�46:
				if (pc && (pc->m_PCData.m_MengPaiID == eMP_�������� || pc->m_PCData.m_MengPaiID == eMP_ħ��կ))
				{
					pt.x = i;
					pt.y = pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;

			case cAttackAI::eET�ߵ�����113:
				if (pc)
				{
					pt.x = i;
					pt.y = 0xffff - pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAttackAI::eET������ɽ95:
				{
					pt.x = i;
					pt.y = 0xffff - pPet->m_ATK.GetData() - pPet->m_DEF.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAttackAI::eET���ݻ���99:
				{
					pt.x = i;
					pt.y = pPet->m_ParryRate.d1;
					if (pt.y > 100)
					{
						pt.y = 100;
					}
					pt.y = pt.y * 10 + 0xffff - pPet->m_DEF.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAttackAI::eET������129:
				if (!pPet->m_Controler.GetFly())
				{
					int r = pPet->m_HP * 100 / pPet->m_HPMax.GetData();
					if (r < 20)
					{
						pt.x = i;
						pt.y = 100 - r;
						out.push_back(pt);
						ret += 1;
					}
				}
				break;

			case cAttackAI::eET�����ɢ127:
				if (pc)
				{
					int r = pPet->m_HP * 100 / pPet->m_HPMax.GetData();
					bool isok = false;
					for (std::list<sBuff>::iterator Iterator = list.m_pData->m_StateList.begin(); Iterator != list.m_pData->m_StateList.end();)
					{
						if (Iterator->times > 2)
						{
							int id = Iterator->ID;
							if (id == 26 || id == 49 || id == 112 || id == 113 || id == 120 || id == 133)
							{
								isok = true;
							}
							if (id == 102 && r < 80)
							{
								isok = true;
							}
						}
						++Iterator;
					}
					
					if (isok)
					{
						pt.x = i;
						pt.y = 100 - r;
						out.push_back(pt);
						ret += 1;
					}
				}
				else
				{
					pt.x = i;
					pt.y = list._speedOfBattle;
					out2.push_back(pt);
//					ret += 1;
				}
				break;
			case cAttackAI::eET��Ȫ֮Ϣ126:
				if (pc)
				{			
					pt.x = i;
					pt.y = list._speedOfBattle;
					out.push_back(pt);
					ret += 1;
				}
				break;

			case cAttackAI::eET����6:
				if (!pPet->m_FightProperty.cannotAll && 
					!pPet->m_FightProperty.cannotAttack && 
					!pPet->m_FightProperty.cannotMagic &&
					!pPet->m_FightProperty.chaos)
				{
					pt.x = i;
					pt.y = pPet->m_ATK.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;


			case cAttackAI::eET����120:
				if (!pPet->PeopleSpecial.d1)
				{
					pt.x = i;
					pt.y = list._speedOfBattle;
					out.push_back(pt);
					ret += 1;
				}
				break;

			default:ERRBOX(0);
				return -1;
				}
		
	}
	if (out.size()>1)
	{//���������ŵ���ǰ��
		for (int i = 0; i < out.size()-1;i++)
		for (int j = i+1; j < out.size(); j++)
		{
			if (out[i].y < out[j].y)
			{
				swap(out[i].x, out[j].x);
				swap(out[i].y, out[j].y);
			}
		}
	}
	if (out2.size())
	{
		forv(out2, i)
		{
			out.push_back(out2[i]);
			if (type != eET�Ͻ��33 && type != eET���鶯112 && type != eET�����ɢ127)
			{
				++ret;
			}
		}
	}
	return ret;
}

void cAttackAI::ZhiHui(BOOL bOur)
{
	int start = 10;
	int end;
	if (bOur)start = 0;
	end = start + 10;
	vector<POINT> tList;
	vector<POINT> tList2;
	//�ٻ�������,������
	int num2;
	int num = FindEnemy(TRUE,TRUE,tList, eET���ٻ���, start);
	for (int i = 0; i < num; i++)
	{	
		if (!g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
		SetUser(tList[i].x);
		for (int j = 0; j < m_pUserPc->m_PCData.m_NumofBB; j++)
		{
			if (m_pUserPc->m_PCData.m_pPetDataList[j]->m_PetDataZZ.m_HP > 0)
			if (m_pUserPc->m_PCData.m_pPetDataList[j]->GetData()->m_LVLimit <= m_pUserPc->m_PCData.m_LV)
			{
				 Summon(j);
			}
		}
	}
	//��������,����
	num = FindEnemy(FALSE, FALSE, tList2, eET��������, start);
	if (num)
	{
		// 6 ���䲻��
		num2 = FindEnemy(TRUE, TRUE, tList, eETҽ��ϵ, start, 6);
		if (!num2)
		{
			num2 = FindEnemy(TRUE, TRUE, tList, eET�ٶ����, start, 6);
		}

		if (num2)
		{
			resurgence2(tList, tList2, 0);
		}
	}

	//���
	FindEnemy(FALSE, TRUE, tList, eET�ٶ����, start, 6);
	UnSeal2(tList, start, end);

	//�����Ѫ
	if (FindEnemy(FALSE, TRUE, tList, eET��Ѫ, start))
	{
		Cure2(tList, start, end);
	}

	CureMP2(tList,start,end);
}

BOOL cAttackAI::resurgence(int user, int target)
{
	if (!m_bNeedlive[target])
	{
		return TRUE;
	}
	SetUser(user);
	if (pUserList->m_WorkType > -1)return FALSE;
	SetTarget(target);
	if (INDEXTYEP_CHARACTER == m_pUser->m_IndexType)
	{
		if (!m_pUserPetData->m_FightProperty.cannotSkill)
		{
			if (CheckCanSkill(3048))
			{
				UseMagic(3048);
				vector<int> ts;
				int star = target < 10 ? 0 : 10;
				for (int i = star; i < star + 10; ++i)
				{
					if (!g_pMainState->m_FightList[i].isLive)
					{
						continue;
					}
					if (g_pMainState->m_FightList[i].m_pData->m_IndexType != INDEXTYEP_CHARACTER)
					{
						continue;
					}
					if (!g_pMainState->m_FightList[i].CheckDie())
					{
						continue;
					}
					cPetData *data = nullptr;
					g_pMainState->m_FightList[i].m_pData->GetDateP(data);
					if (!data)
					{
						continue;
					}
					if (m_pUserPetData->PeopleSpecial.d1 < data->PeopleSpecial.d2)
					{
						continue;
					}
					ts.push_back(i);
				}
				if (ts.size() > 2)
				{
					for (int i : ts)
					{
						m_bNeedUnSeal[i] = FALSE;
						m_bNeedlive[i] = FALSE;
						m_bNeedAddHpHurt[i] -= 100;
						m_bNeedAddHp[i] -= 100;
					}
					return TRUE;
				}
			}
		}

		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			switch (m_pUserPc->m_PCData.m_MengPaiID)
			{
			case eMP_����ɽ:
				if (CheckCanSkill(104))
				{
					UseMagic(104);
					m_bNeedlive[target] = FALSE;
					m_bNeedAddHpHurt[target] -= 40;
					m_bNeedAddHp[target] -= 40;
					return TRUE;
				}
				break;
			case eMP_������:
				if (CheckCanSkill(37))
				{
					UseMagic(37);
					m_bNeedlive[target] = FALSE;
					m_bNeedAddHpHurt[target] -= 30;
					m_bNeedAddHp[target] -= 30;
					return TRUE;
				}
				break;
			case eMP_���ܵظ�:
				if (m_pUserPc->m_PCData.m_LV >= 120)
				{
					if (CheckCanSkill(125))
					{
						UseMagic(125);
						m_bNeedlive[target] = FALSE;
						m_bNeedAddHpHurt[target] -= 25;
						m_bNeedAddHp[target] -= 25;
						return TRUE;
					}
				}
				break;
			}
		}

	}
	if (UseItem(eAIUseItemTypelive))
	{
		m_bNeedlive[target] = FALSE;
		return TRUE;
	}
	if (INDEXTYEP_CHARACTER == m_pUser->m_IndexType)
	{
		if (!m_pUserPetData->m_FightProperty.cannotSkill)
		{
			if (CheckCanSkill(3009))
			{
				UseMagic(3009);
				m_bNeedlive[target] = FALSE;
				m_bNeedAddHpHurt[target] -= 60;
				m_bNeedAddHp[target] -= 60;
				return TRUE;
			}
			else if (CheckCanSkill(3008))
			{
				UseMagic(3008);
				m_bNeedlive[target] = FALSE;
				m_bNeedAddHpHurt[target] -= 30;
				m_bNeedAddHp[target] -= 30;
				return TRUE;
			}
		}
	}

	return FALSE;

}

void cAttackAI::resurgence2(vector<POINT>& user, vector<POINT>& target, int targetID)
{
	if (target.size() <= targetID)return;
	BOOL blist=TRUE;//�Ƿ�A��B B��C
	int i;
	for (i = 0; i < user.size(); i++)
	{
		if (target[targetID].x == user[i].x)
		{//������ٶ�̫��
			blist = FALSE;
			continue;
		}
		if (resurgence(user[i].x, target[targetID].x))
			break;
	}
	if (!blist)return resurgence2(user,target,targetID+1);
	//A��B B��C C��D
	if (i == g_pMainState->m_HeroID)return;
	if (i == g_pMainState->m_HeroID+5)return;
	i = targetID;
	for (; i < target.size() - 1; i++)
	{
		if (!resurgence(target[i].x, target[i+1].x))break;
	}
	//D��BB
	if (target[i].x % 10 < 5 && !g_pMainState->m_FightList[target[i].x + 5].isLive)
	{
		SetUser(target[i].x);
		int j = 0;
		for (; j < m_pUserPc->m_PCData.m_NumofBB; j++)
		{
			if (m_pUserPc->m_PCData.m_pPetDataList[j]->m_PetDataZZ.m_HP>0)
			if (m_pUserPc->m_PCData.m_pPetDataList[j]->GetData()->m_LVLimit <= m_pUserPc->m_PCData.m_LV)
			{
				Summon(j);
			}
		}
		//û��BB,�Լ���ҩ
		if (j == m_pUserPc->m_PCData.m_NumofBB)
		{
			SetTarget(target[i].x);
			if (!UseItem(eAIUseItemTypeHPHurt))
			{
				//�����κδ���
			}
		}
	}
}

void cAttackAI::CorrectEnemy(vector<POINT>& out, eEnemyCorrect typ)
{
	BOOL bFind = FALSE;
	int i;
	for (i = 0; i < out.size(); i++)
	{
		SetTarget(out[i].x);
		switch (typ)
		{
		case cAttackAI::eEC����:
			if (!m_pTargetList->isLive)bFind = TRUE;
			if (m_pTargetList->CheckDie() && (!m_bNeedlive[m_TargetID]))bFind = TRUE;
			if (m_pTargetPetData->m_FightProperty.cannotUseItem)bFind = TRUE;
			break;
		default:
			break;
		}
		if (bFind)
		{
			out.erase(out.begin() + i);
			return CorrectEnemy(out, typ);
		}
	}
	return;
}

BOOL cAttackAI::Cure(int user, int target,BOOL toall)
{
	if (m_bNeedAddHp[target] < 100 - m_HPLimit)
	{
		return TRUE;
	}

	SetUser(user);
	if (pUserList->m_WorkType > -1)return FALSE;
	SetTarget(target);
	BOOL bHurt = FALSE;
	if (m_pTargetPetData->m_HPHurtMax < m_pTargetPetData->m_HPMax.GetData())
		bHurt = TRUE;
	int start = 10;
	int end;
	if (target<10)start = 0;
	end = start + 10;

	if (m_pUserPc)
	{
		if (!m_pUserPetData->m_FightProperty.cannotSkill)
		{
			if (CheckCanSkill(3013))
			{
				UseMagic(3013);
				int star = target < 10 ? 0 : 10;
				for (int i = star; i < star + 10; ++i)
				{
					m_bNeedAddHp[i] -= 20;
					m_bNeedUnSeal[i] = FALSE;
				}
				return TRUE;
			}
			else if (CheckCanSkill(3007))
			{
// 				m_bNeedAddHpHurt[m_TargetID] -= 30;
// 				m_bNeedAddHp[m_TargetID] -= 30;
				UseMagic(3007);
				int star = target < 10 ? 0 : 10;
				for (int i = star; i < star + 10; ++i)
				{
					m_bNeedAddHp[i] -= 30;
				}
				return TRUE;
			}
		}

		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			switch (m_pUserPc->m_PCData.m_MengPaiID)
			{
			case eMP_������:
//			if (bHurt)
			{
				if (toall)
				{
					UseMagic(42);
					for (int i = start; i < end; i++)
						m_bNeedAddHp[i] -= 15;
					return TRUE;
				}
				else
				{
					if (m_pUserPetData->m_LV >= 120)
					{
						UseMagic(45);
						m_bNeedAddHp[target] = 0;
					}
					else
					{
						UseMagic(38);
						m_bNeedAddHp[target] -= 20;
					}
					return TRUE;
				}
			}
// 			else
// 			{
// 				if (toall)
// 				{
// 					UseMagic(40);
// 					for (int i = start; i < end; i++)
// 						m_bNeedAddHp[i] -= 30;
// 					return TRUE;
// 				}
// 				else
// 				{
// 					UseMagic(39);
// 					m_bNeedAddHp[target] -= 60;
// 					return TRUE;
// 				}
// 			}
				break;
			case eMP_���ܵظ�:
			{
				SetTarget(findʬ��������());
				if (m_TargetID >= 0)
				{
					_isShiFudu[m_TargetID] = TRUE;
					UseMagic(122);
					for (int i = start; i < end; i++)
						m_bNeedAddHp[i] -= 15;
					return TRUE;
				}
			}
				break;
			case eMP_����ɽ:
				if (!m_pTarget->CheckHaveState(102))
				{
					UseMagic(102);
					m_bNeedAddHp[target] -= 15;
					return TRUE;
				}
				else
				{
					UseMagic(115);
					m_bNeedAddHp[target] -= 45;
					return TRUE;
				}
				break;
			case eMP_��ׯ��:
				if (!m_pTarget->CheckHaveState(91))
				{
					UseMagic(91);
					for (int i = start; i < end; i++)
						m_bNeedAddHp[i] -= 5;
					return TRUE;
				}
				break;
			}
		}
	}

	if (!m_pUserPetData->m_FightProperty.cannotUseItem && !MyTest::getInstance()->isAtkMode(m_UserID))
	{
		BOOL haveall=FALSE;
		if (m_pUserPc)
		{
			if (m_pUserPc->m_PCData.m_Item[1].GetNum())haveall = TRUE;
		}
		else
		{
			if (!m_pUserPetData->m_Controler.CheckBB())return FALSE;
			if (user - 5 < 0){
				ERRBOX(user - 5);
				return FALSE;
			}
			cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[user-5].m_pData->m_pIndex;
			if (pc)
			{
				if (pc->m_PCData.m_Item[1].GetNum())haveall = TRUE;
			}

		}
// 		if (toall&&haveall)
// 		{	
// 			UseItem(eAIUseItemTypeHPALL);
// 			for (int i = start; i < end; i++)
// 				m_bNeedAddHp[i] -= 40;
// 			return TRUE;
// 		}
// 		else
		{
			if (bHurt)
			{
				if (UseItem(eAIUseItemTypeHPHurt) || UseItem(eAIUseItemTypeHP))
				{
					m_bNeedAddHp[target] -= 30;
					return TRUE;
				}
			}
			else
			{
				if (UseItem(eAIUseItemTypeHP) || UseItem(eAIUseItemTypeHPHurt))
				{
					m_bNeedAddHp[target] -= 50;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}


BOOL cAttackAI::CureMP(int user, int target, BOOL toall /*= FALSE*/)
{
// 	if (!m_bNeedAddMp[target])
// 	{
// 		return TRUE;
// 	}
	SetUser(user);
	SetTarget(target);
	if (m_pUserPc)
	{
		if (m_pUserPetData->m_FightProperty.cannotMagic)
			switch (m_pUserPc->m_PCData.m_MengPaiID)
		{
			case eMP_��ׯ��:
				if (!m_pTarget->CheckHaveState(90))
				{
					UseMagic(90);
					m_bNeedAddMp[target] = FALSE;
					return TRUE;
				}
				else
				{
					if (target == user)
					{
						UseMagic(94);
						m_bNeedAddMp[target] = FALSE;
						return TRUE;
					}
				}
				break;
			case eMP_����ɽ:
				if (target == user)
				{
					if (m_pUserPetData->m_HP > 100)
					{
						UseMagic(23);
						m_bNeedAddMp[target] = FALSE;
						return TRUE;
					}
				}
				break;
		}
	}
	if (!m_pUserPetData->m_FightProperty.cannotUseItem)
	{
// 		if (toall)
// 		{
// 			UseItem(eAIUseItemTypeMPALL);
// 			return TRUE;
// 		}
// 		else
		{
			if (UseItem(eAIUseItemTypeMP))
			{
				m_bNeedAddMp[target] = FALSE;
				return TRUE;
			}
		}
	}
	return FALSE;
}

void cAttackAI::UnSeal2(vector<POINT>& tlist, int start, int end)
{
	UINT start1 = 0;
	for (int i = start; i < end; i++)
	{
		if (!m_bNeedUnSeal[i])
		{
			continue;
		}
		if (g_pMainState->m_FightList[i].m_pData->m_IndexType != INDEXTYEP_CHARACTER)
		{
			continue;
		}
		for (int j = start1; j < tlist.size(); j++)
		{
			if (UnSeal(tlist[j].x, i))
			{
				start1 += 1;
				if (start1 == tlist.size())
				{
					return;
				}
				break;
			}
		}
	}

	for (int i = start; i < end; i++)
	{
		if (!m_bNeedUnSeal[i])
		{
			continue;
		}
		for (int j = start1; j < tlist.size(); j++)
		{
			if (UnSeal(tlist[j].x, i))
			{
				start1 += 1;
				if (start1 == tlist.size())
				{
					return;
				}
				break;
			}
		}
	}
}

void cAttackAI::Cure2(vector<POINT>& tlist, int start, int end)
{
	BOOL toall = TRUE;
	int start1 = 0;
	for (int i = start; i < end; i++)
	{
		if (m_bNeedAddHp[i] > (100 - m_HPLimit) && g_pMainState->m_FightList[i].m_pData->m_IndexType != INDEXTYEP_PET)
		{
			for (int j = start1; j < tlist.size(); j++)
			{
				if (toall)
				{
					int num = 0;
					int limit2 = m_HPLimit / 2 + 50;
					for (int k = start; k < end; k++)
					{
						if (m_bNeedAddHp[k] > 100 - limit2)
							num += 1;
					}
					if (num < 2)toall = FALSE;
				}
				if (Cure(tlist[j].x, i, toall))
				{
					start1 += 1;
					if (start1 == tlist.size())return;
					break;
				}
			}

		}
	}
}

BOOL cAttackAI::UnSeal(int user, int target)
{
// 	if (!m_bNeedUnSeal[target])
// 	{
// 		return TRUE;
// 	}
	SetUser(user);
	if (!pUserList->isLive)return FALSE;
	if (pUserList->CheckDie())return FALSE;
	if (pUserList->m_WorkType > -1)return FALSE;
	if (m_pUserPc && !m_pUserPetData->m_FightProperty.cannotSkill)
	{
		if (CheckCanSkill(3013))
		{
// 			m_bNeedAddHpHurt[target] -= 20;
// 			m_bNeedAddHp[target] -= 20;
			SetTarget(target);
			UseMagic(3013);
			int star = target < 10 ? 0 : 10;
			for (int i = star; i < star + 10; ++i)
			{
				m_bNeedUnSeal[i] = FALSE;
				m_bNeedAddHp[i] -= 20;
			
			}
			return TRUE;
		}
	}
	if (m_pUserPetData->m_FightProperty.cannotUseItem)
		return FALSE;
	SetTarget(target);
	if (UseItem(eAIUseItemTypeUnseal))
	{
		m_bNeedUnSeal[target] = FALSE;
		m_bNeedAddHp[target] -= 10;
		return TRUE;
	}
	return FALSE;
}

void cAttackAI::CureMP2(vector<POINT>& tlist, int start, int end)
{
	BOOL toall = TRUE;
	int start1 = 0;
	for (int i = start; i < end; i++)
	{
		if (m_bNeedAddMp[i])
		{
			for (int j = start1; j < tlist.size(); j++)
			{
				if (toall)
				{
					int num = 0;
					for (int k = start; k < end; k++)
					{
						if (m_bNeedAddMp[k])
							num += 1;
					}
					if (num < 3)toall = FALSE;
				}
				if (CureMP(tlist[j].x, i, toall))
				{
					start1 += 1;
					if (start1 == tlist.size())return;
					break;
				}
			}

		}
	}
}

vector<int> cAttackAI::check����(vector<POINT>& out, int user)
{
	cPetData *data;
	g_pMainState->m_FightList[user].m_pData->GetDateP(data);
	vector<int> out2;
	forv(out, i)
	{
		cPetData *data2;
		g_pMainState->m_FightList[out[i].x].m_pData->GetDateP(data2);
		if (data->PeopleSpecial.d1 >= data2->PeopleSpecial.d2)
		{
			out2.push_back(out[i].x);
		}
	}
	return out2;
}

#endif