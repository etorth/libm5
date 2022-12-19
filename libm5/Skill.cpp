#include "global.h"
#if defined(ccc_date)

BOOL cSkillManager::SetDateBuffUp(int userID, int targetID, int stateid, sBuff& buf, int skilllv)
{
	if (g_StateType != STATE_FIGHT)return TRUE;
	if (buf.times < 1)buf.times = 1;
	int MagicPos = 0;
	DWORD MagicID = 0; //BUFF ��ID
	BOOL MagicUpOrDown = FALSE; //����BUFF ��������ʾ����ʾ
//	int  magicType = 1; //Ĭ�Ϸ������� ��ӡ
	cObj* pTarget = m_pFightState->m_pList[targetID]->m_pData;
	cPetData* pTargetData;
	pTarget->GetDateP(pTargetData);
	sFightData& TargetFightP = pTargetData->m_FightProperty;
	//eBuffType EffectType = eBuffType��ӡ;


	for (list<sBuff>::iterator it = pTarget->m_StateList.begin(); it != pTarget->m_StateList.end(); it++)
	{
		if (it->ID == stateid)
		{
			it->times = buf.times;
			return TRUE;
		}
	}
	switch (stateid)
	{
	case 0: //��ɨǧ��
	case 7: //�Ƹ�����
		MagicID = 0xD9463A0C;
		//		TargetFightP.cannotAll += 1;
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicPos = -10;
		break;
	case 1://������
		MagicID = 0x2A2A0663;
		pTargetData->m_SPD.AddDataOriginal(80000);
		//		pTargetData->m_Pierce.d1 += 30;
		pTargetData->m_CriRate.d1 += 20;
		//		pTargetData->m_DamagePercent.d1 += 50;
		pTargetData->m_DEF.AddDataOriginal(buf.damage = skilllv * 3);
		pTargetData->m_Wakan.AddDataOriginal(buf.damage2 = skilllv * 2);
		MagicPos = -10;
		break;
	case 4://ɱ����
		MagicUpOrDown = TRUE;
		MagicID = 0x62EDD1CB;
		buf.damage = skilllv;
		pTargetData->m_HIT.AddDataOriginal(buf.damage * 3);
		pTargetData->m_ATK.AddDataOriginal(buf.damage);
		break;
	case 6://�����
		pTarget->SetShakeFor����(TRUE);
		TargetFightP.chaos += 1;
		break;
	case 8://�����
		MagicPos = -10;
		MagicUpOrDown = TRUE;
		MagicID = 3860707508;
		pTargetData->m_DamageAddPercentMagic.d2 += 30;
		break;
	case 14://����
		MagicPos = -10;
		TargetFightP.cannotAll += 1;
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicID = 3398426285;
		break;
	case 15://ʧ��
		MagicPos = -10;
		TargetFightP.cannotMagic += 1;
		pTargetData->m_DEF.AddDataAddPercent(-10);
		pTargetData->m_Wakan.AddDataAddPercent(-10);
		pTargetData->m_Evade.AddDataAddPercent(-20);
		MagicID = 3635978625;
		break;
	case 16://����
		MagicPos = -10;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotAttack += 1;
		//		pTargetData->m_Wakan.AddDataAddPercent(-20);
		pTarget->SetShakeFor����(TRUE);
		//		MagicID = 0x8B43833D;
		break;
	case 17://ʧ��
		MagicPos = -10;
		// 		TargetFightP.cannotAttack += 1;
		// 		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		MagicID = 3946646209;
		break;
	case 18://׷��
		MagicPos = -10;
		pTargetData->m_DEF.AddDataAddPercent(-20);
		TargetFightP.cannotAttack += 1;
		MagicID = 3655438388;
		break;
	case 19://���
		MagicPos = -10;
		TargetFightP.cannotMagic += 1;
		MagicID = 1214058823;
		break;
	case 20://ʧ��   
		MagicPos = -10;
		TargetFightP.cannotMagic += 1;
		MagicID = 2336457533;
		break;
	case 21://���� 
		MagicPos = -10;
		//		TargetFightP.cannotAll += 1;
		pTargetData->m_DEF.AddDataAddPercent(-10);
		pTargetData->m_Wakan.AddDataAddPercent(-10);
		TargetFightP.cannotAttack += 1;
		// 		TargetFightP.cannotMagic += 1;
		// 		TargetFightP.cannotSkill += 1;
		MagicID = 2461182746;
		break;
	case 26:
		pTarget->SetShadow(50);
		pTargetData->m_MagicHitRate.d2 += buf.damage = skilllv / 8;
		break;
	case 27: //��׷�
		pTargetData->m_DEF.AddDataAddPercent(-10);
		pTargetData->m_Wakan.AddDataAddPercent(-10);
		MagicID = 0x5525C5FB;
		MagicUpOrDown = TRUE;
		MagicPos = 10;
		break;
	case 33://��ջ���
		pTarget->SetTwinkle(TRUE);
		buf.damage = skilllv * 3 / 2;
		pTargetData->m_ATK.AddDataAdd(buf.damage);
		break;
	case 34: //Τ�ӻ���  
		pTargetData->m_HIT.AddDataAdd(buf.damage = skilllv * 3);
		MagicID = 0xF184BD59;
		MagicPos = -10;
		MagicUpOrDown = TRUE;
		break;
	case 35:  //��ջ���
		pTargetData->m_DEF.AddDataAdd(buf.damage = skilllv * 3 / 2);
		MagicID = 916220457;
		MagicUpOrDown = TRUE;
		break;
	case 36://һέ�ɽ�
		MagicID = 382287583;
		MagicPos = -10;
		pTargetData->m_SPD.AddDataAddPercent(buf.damage = skilllv / 3);
		break;
	case 46:    //���ޱ�
		pTargetData->m_MagicComboRate.d1 += 30;
		MagicID = 3930943562;
		MagicPos = -10;
		MagicUpOrDown = TRUE;
		break;
	case 49:    //��������
		MagicID = 0x72AD6DBA;
		MagicPos = -10;
		MagicUpOrDown = TRUE;
		// 		pTargetData->m_HitRate.d2 += 100;
		// 		pTargetData->m_MagicHitRate.d2 += 100;
		// 		pTargetData->m_SealRate.d2 += 100;
		// 		pTargetData->poisonRate.d2 += 100;
		TargetFightP.cannotMagic += 1;
		pTargetData->PeopleSpecial.d2 += 100;
		break;
	case 50: //���컨���ж�
		MagicID = 0xDBCEE32C;
		MagicPos = -10;
		MagicUpOrDown = 1;
		break;
	case 54://��������
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		MagicID = 0x59D77EF9;
		MagicPos = -10;
		break;
	case 59://һЦ���
		TargetFightP.cannotMagic += 1;
		MagicID = 3635978625;// 0x1E1AF8D9;
		MagicPos = -10;
		break;
	case 63://���񻤷�
		break;
	case 67:	//����
//		pTargetData->m_ATK.AddDataAddPercent(-30);
		TargetFightP.cannotSkill += 1;
		MagicID = 0x98753F94;
		MagicPos = -10;
		break;
	case 68:	//����
		pTargetData->m_HIT.AddDataAddPercent(-20);
		TargetFightP.cannotMagic += 1;
		MagicID = 0x2F78C46E;
		MagicUpOrDown = TRUE;
		MagicPos = -10;
		break;
	case 69:	//�������
		TargetFightP.cannotAttack += 1;
		MagicID = 0xC48ABA7B;
		MagicPos = -10;
		break;
	case 81:// ����
		pTarget->SetTwinkle(TRUE);
		buf.damage = skilllv;
		pTargetData->m_ATK.SetDataAdd(buf.damage);
		break;
	case 89:  //����Ǭ��
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		MagicID = 0x313BCC79;
		MagicUpOrDown = 1;
		MagicPos = -10;
		break;
	case 90:   //��������
		MagicID = 0x719D767F;
		MagicUpOrDown = 1;
		MagicPos = 10;
		//		buf.damage = skilllv;
		pTargetData->m_FightProperty.m_TurnMPAdd += buf.damage;
		AddMp(targetID, buf.damage);
		break;
	case 91:    //����֮Ȫ
		MagicID = 0xCB9CBB52;
		MagicUpOrDown = 1;
		MagicPos = 10;
		//		buf.damage = skilllv * 2 + 120;
		pTargetData->m_FightProperty.m_TurnHPAdd += buf.damage;
		AddHp(targetID, buf.damage);
		buf.damage2 = buf.damage;
		break;
	case 102: //�ն�����
		MagicID = 0xD8857128;
		MagicUpOrDown = 1;
		MagicPos = 10;
		buf.damage = skilllv * 4 + 50;
		buf.damage2 = buf.damage;
		pTargetData->m_FightProperty.m_TurnHPAdd += buf.damage;
		pTargetData->m_FightProperty.m_TurnHPHurtAdd += buf.damage2;
		break;
	case 103:// ������
		MagicID = 0xEFE73EB9;
		MagicUpOrDown = 1;
		MagicPos = 10;
		pTargetData->m_FightProperty.m_TurnHPHurtAdd -= buf.damage = skilllv * 2;
		break;
	case 112:// �鶯����
		MagicID = 0x95FF4460;
		MagicUpOrDown = 1;
		MagicPos = 0;
		pTargetData->m_Wakan.AddDataAdd(buf.damage = skilllv * 3 / 2);
		break;
	case 113:// �ߵ�����
		MagicID = 0x4DDF5690;
		MagicUpOrDown = 1;
		MagicPos = 0;
		// 		pTargetData->m_Wakan.AddDataAdd(buf.damage = skilllv);
		// 		pTargetData->m_ATK.AddDataAdd(buf.damage);
		// 		pTargetData->m_DEF.AddDataAdd(buf.damage);
		// 		pTargetData->m_SPD.AddDataAdd(buf.damage);
		// 		pTargetData->m_HIT.AddDataAdd(buf.damage);
		buf.damage = skilllv / 5 + 10;
		pTargetData->m_MagicThunder.d2 += buf.damage;
		pTargetData->m_MagicSoil.d2 += buf.damage; //��
		pTargetData->m_MagicFire.d2 += buf.damage; //��
		pTargetData->m_MagicWater.d2 += buf.damage; //ˮ
		pTargetData->m_MagicHitRate.d2 += buf.damage / 2;
		break;
	case 120://��ڤ����
		MagicID = 0x21435203;
		// 		pTargetData->m_HitRate.d1 += 100;
		pTargetData->m_SealRate.d2 += buf.damage = skilllv / 10;
		// 		pTargetData->poisonRate.d1 += 30;
		pTargetData->PeopleSpecial.d1 += 100;
		MagicUpOrDown = 1;
		MagicPos = 0;
		break;
	case 122:// ʬ����
		MagicID = 0x839CC29A;
		MagicUpOrDown = 1;
		MagicPos = -10;

		break;
	case 123://��������

	{
		pTarget->SetShadow(50);
		pTargetData->PeopleSpecial.d2 += 100;
		//			pTargetData->m_HitRate.d1 += 10;
		// 			pTargetData->m_HitRate.d2 += 100;
		// 			pTargetData->m_MagicHitRate.d2 += 100;
		// 			pTargetData->m_SealRate.d2 += 100;
		// 			pTargetData->poisonRate.d2 += 100;
		TargetFightP.cannotMagic += 1;
	}
	break;
	case 125:
		pTargetData->m_ATK.AddDataAdd(buf.damage = skilllv * 3 / 2);
		break;
	case 126:// ��Ȫ֮Ϣ
		MagicID = 0x5ECEBEDD;
		pTargetData->m_SPD.AddDataAddPercent(-20);
		MagicUpOrDown = 1;
		MagicPos = -10;
		break;
	case 129:// ������
		MagicID = 0x5C0073EE;
		MagicUpOrDown = 1;
		MagicPos = 1;
		pTargetData->m_FightProperty.cannotLive += 1;
		break;
	case 133://ţ��
		MagicID = 0x62EDD1CB;
		buf.damage = skilllv;
		MagicUpOrDown = 1;
		pTargetData->m_Wakan.AddDataAdd(buf.damage);
		//		pTargetData->m_MagicHitRate.d1 += 100;
		pTargetData->PeopleSpecial.d1 += 100;
		break;
	case 141://����
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicID = 0x3646A4D9;
		MagicPos = -10;
		break;
	case 148://������
	case 142://ӥ��
		stateid = 142;
		//		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicID = 0x58628406;
		MagicPos = -10;
		break;
	case 144:// ����
		MagicID = 0x20FCCE94;
		MagicPos = -10;
		pTargetData->m_ATK.AddDataAddPercent(-20);
		pTargetData->m_DEF.AddDataAddPercent(-10);
		pTargetData->m_Wakan.AddDataAddPercent(-10);
		break;
	case 145:// ����
		MagicID = 0x85C9AF08;
		pTargetData->m_ATK.AddDataAdd(buf.damage = skilllv);
		MagicUpOrDown = 1;
		break;
	case 147://������
		MagicID = 755485932;
		pTargetData->m_Wakan.AddDataAdd(buf.damage = skilllv * 3 / 2);
		MagicUpOrDown = 1;
		break;
	case 150://���ȷ��
		MagicID = 0xBBEA83F4;
		pTargetData->m_CounterRate.d1 += 100;
		MagicUpOrDown = 1;
		break;
	case 152://��ħ����
		MagicID = 0x3D3FA597;
		pTargetData->m_HPMax.AddDataAddPercent(30);

		{
			int dam = AddHp(targetID, 5, 10000);
			SetDamage(-dam, targetID);
		}
		MagicUpOrDown = 1;
		break;
	case 156://ħ�����
		MagicID = 0xAF07277F;
		MagicPos = -10;
		TargetFightP.cannotAddHP += 1;
		break;
	case 159://��������
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		MagicID = 0x8103AFD2;//0xC4AA8E18;
		MagicPos = -10;
		break;
	case 160:// ��˿��
		buf.damage = skilllv * 2;
		pTargetData->m_DEF.AddDataAdd(buf.damage);
		MagicID = 0x369C6A29;
		MagicUpOrDown = TRUE;
		break;
	case 161: break;//����	
	case 162:  //���޵���
		MagicPos = -10;
		MagicID = 0x8F3E73D5;
		TargetFightP.cannotAttack += 1;
		break;
	case 164:break;//����ͬ��	
	case 166://�þ���
		MagicID = 0x0B788E5A;
		MagicUpOrDown = TRUE;
		MagicPos = -10;
		pTargetData->m_StabRateMagic.d1 += 50;    //���������˺�
		pTargetData->m_StabDamageRateMagic.d1 += 50; //����������
		break;
	case 1002: //1�غϵĸ� BUFF
		pTargetData->m_ParryRate.d1 += 1000;
		break;
	case 1004://����
		break;
	case 2092://����һ��
//		pTargetData->m_ATK.AddDataAddPercent(-20);
		break;
	case 2093://ҹ�����
		pTargetData->m_ATK.AddDataAddPercent(-10);   //�˺�
		pTargetData->m_HIT.AddDataAddPercent(-10);   //����
		pTargetData->m_DEF.AddDataAddPercent(-10);   //����
		pTargetData->m_Wakan.AddDataAddPercent(-10); //����
		pTargetData->m_SPD.AddDataAddPercent(-10);   //�ٶ�
		pTargetData->m_Evade.AddDataAddPercent(-10); //����
		break;
	case 2094://�����ٻ�
		MagicID = 0x19182964;
		MagicPos = -10;
		pTargetData->m_FightProperty.cannotLive += 1;
		break;
	case 2095:
		pTargetData->m_HIT.AddDataAddPercent(200);   //����
		break;
	case 2097:// ��������
		MagicID = 0xDEDEE983;
		MagicUpOrDown = TRUE;
		pTargetData->m_DamageAddPercentMagic.d2 += 65;
		break;
	case 3024://̫������ 
	case 3025://�޺�
		MagicPos = -10;
		MagicID = 0xAF07277F;// 0x5CC81980;
		pTargetData->m_DamageAddPercentMagic.d2 += 50;
		break;
	case 3026://������
		pTargetData->m_StabRateMagic.d1 += 100;
		pTargetData->m_StabDamageRateMagic.d1 += 30;
		break;
	case 3027://�����޷�
		pTargetData->m_MagicHitRate.d2 += 50;
		break;
	case 3047://��������
		pTargetData->m_DamageAddPercentMagic.d2 += 50;//���������ӳ�
		pTargetData->m_DamagePercent.d2 += 50;//��������ӳ�
		pTarget->ReMoveState(eBuffType��ӡ);
		pTarget->ReMoveState(eBuffType��);
		pTarget->ReMoveState(eBuffType����);
		pTarget->ReMoveState(eBuffType����);
		break;
	default:
		ERRBOX2(stateid);
		return TRUE;
	}
	sSkill* pskill = g_pMainState->m_SkillManager.GetSkill(stateid);
	if (pskill)
	{
		buf.EffectType = (eBuffType)pskill->m_EffectType;
	}
	else buf.EffectType = eBuffType����;
	buf.skilllv = skilllv;
	buf.userID = userID;
	buf.targetID = targetID;
	buf.MagicID = MagicID;
	buf.bufPos = MagicPos;
	buf.bBuffup = MagicUpOrDown;
	buf.ID = stateid; //����BUFF  ID
	m_pFightState->AddState(targetID, buf);
	return TRUE;
}

BOOL cSkillManager::SetDateBuffDown(list<sBuff>::iterator& sbuf)//int targetID, int stateid)
{
	int targetID = sbuf->targetID;
	int stateid = sbuf->ID;
	cObj* pTarget = m_pFightState->m_pList[targetID]->m_pData;
	cPetData* pTargetData;
	pTarget->GetDateP(pTargetData);
	sFightData&  targetProperty = pTargetData->m_FightProperty;


	switch (stateid)
	{
	case 0://��ɨǧ��
	case 7://�Ƹ�����
//		targetProperty.cannotAll -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSkill -= 1;
		targetProperty.cannotUseItem -= 1;
		break;
	case 1: //������
		pTargetData->m_SPD.AddDataOriginal(-80000);
		//		pTargetData->m_DamagePercent.d1 -= 50;
		//		pTargetData->m_Pierce.d1 -= 30;
		pTargetData->m_CriRate.d1 -= 20;
		pTargetData->m_DEF.AddDataOriginal(-sbuf->damage);
		pTargetData->m_Wakan.AddDataOriginal(-sbuf->damage2);
		break;
	case 4:
		pTargetData->m_HIT.AddDataOriginal(-sbuf->damage * 3);
		pTargetData->m_ATK.AddDataOriginal(-sbuf->damage);
		break;
	case 6:
		pTarget->SetShakeFor����(FALSE);
		targetProperty.chaos -= 1;
		g_pMainState->m_FightList[pTarget->m_IDInFightlist].m_WorkType = -1;
		break;
	case 8://�����
		pTargetData->m_DamageAddPercentMagic.d2 -= 30;
		break;
	case 14://���߷�
		targetProperty.cannotAll -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSkill -= 1;
		targetProperty.cannotUseItem -= 1;
		break;
	case 15://ʧ��
		targetProperty.cannotMagic -= 1;
		pTargetData->m_DEF.AddDataAddPercent(10);
		pTargetData->m_Wakan.AddDataAddPercent(10);
		pTargetData->m_Evade.AddDataAddPercent(20);
		break;
	case 16://����
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotAttack -= 1;
		//		pTargetData->m_Wakan.AddDataAddPercent(20);
		pTarget->SetShakeFor����(FALSE);
		break;
	case 17://ʧ��
// 		targetProperty.cannotAttack -= 1;
// 		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSkill -= 1;
		break;
	case 18://׷��
		targetProperty.cannotAttack -= 1;
		pTargetData->m_DEF.AddDataAddPercent(20);
		break;
	case 19://���
		targetProperty.cannotMagic -= 1;
		break;
	case 20://ʧ��   
		targetProperty.cannotMagic -= 1;
		break;
	case 21://���� 
//		targetProperty.cannotAll -= 1;
		targetProperty.cannotAttack -= 1;
		// 		targetProperty.cannotMagic -= 1;
		// 		targetProperty.cannotSkill -= 1;
		pTargetData->m_DEF.AddDataAddPercent(10);
		pTargetData->m_Wakan.AddDataAddPercent(10);
		break;
	case 26:
		pTarget->SetShadow(FALSE);
		pTargetData->m_MagicHitRate.d2 -= sbuf->damage;
		break;
	case 27: //��׷�
		pTargetData->m_DEF.AddDataAddPercent(10);
		pTargetData->m_Wakan.AddDataAddPercent(10);
		break;
	case 33://��ջ���
		pTarget->SetTwinkle(FALSE);
		pTargetData->m_ATK.AddDataAdd(-sbuf->damage);
		break;
	case 34:   //Τ�ӻ���  
		pTargetData->m_HIT.AddDataAdd(-sbuf->damage);
		break;
	case 35:  //��ջ���
		pTargetData->m_DEF.AddDataAdd(-sbuf->damage);
		break;
	case 36:  //һέ�ɽ�
		pTargetData->m_SPD.AddDataAdd(-sbuf->damage);
		break;
	case 46:    //���ޱ�
		pTargetData->m_MagicComboRate.d1 -= 30;
		break;
	case 49:    //��������
// 		pTargetData->m_HitRate.d2 -= 100;
// 		pTargetData->m_MagicHitRate.d2 -= 100;
// 		pTargetData->m_SealRate.d2 -= 100;
// 		pTargetData->poisonRate.d2 -= 100;
		targetProperty.cannotMagic -= 1;
		pTargetData->PeopleSpecial.d2 -= 100;
		break;
	case 50: //���컨���ж�

		break;
	case 141://����
		targetProperty.cannotAll -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSkill -= 1;
		break;
	case 54://��������
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		break;
	case 59://һЦ���
		targetProperty.cannotMagic -= 1;
		break;
	case 63://���񻤷�

		break;
	case 67:	//����
//		pTargetData->m_ATK.AddDataAddPercent(30);
		targetProperty.cannotSkill -= 1;
		break;
	case 68:	//����
		pTargetData->m_HIT.AddDataAddPercent(20);
		targetProperty.cannotMagic -= 1;
		break;
	case 69:	//�������
		targetProperty.cannotAttack -= 1;
		break;
	case 81:// ����
		pTarget->SetTwinkle(FALSE);
		pTargetData->m_ATK.SetDataAdd(-sbuf->damage);
		break;
	case 89:  //����Ǭ��
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSkill -= 1;
		break;
	case 90:   //��������
		pTargetData->m_FightProperty.m_TurnMPAdd -= sbuf->damage;
		break;
	case 91:    //����֮Ȫ
		pTargetData->m_FightProperty.m_TurnHPAdd -= sbuf->damage;
		break;
	case 102: //�ն�����
		pTargetData->m_FightProperty.m_TurnHPAdd -= sbuf->damage;
		pTargetData->m_FightProperty.m_TurnHPHurtAdd -= sbuf->damage2;
		break;
	case 103://������
		pTargetData->m_FightProperty.m_TurnHPHurtAdd += sbuf->damage;
		break;
	case 112:// �鶯����
		pTargetData->m_Wakan.AddDataAdd(-sbuf->damage);
		break;
	case 113:// �ߵ����� 
// 		pTargetData->m_Wakan.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_ATK.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_DEF.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_SPD.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_HIT.AddDataAdd(-sbuf->damage);
		pTargetData->m_MagicThunder.d2 -= sbuf->damage;
		pTargetData->m_MagicSoil.d2 -= sbuf->damage; //��
		pTargetData->m_MagicFire.d2 -= sbuf->damage; //��
		pTargetData->m_MagicWater.d2 -= sbuf->damage; //ˮ
		pTargetData->m_MagicHitRate.d2 -= sbuf->damage / 2;
		break;
	case 120:
		// 		pTargetData->m_HitRate.d1 -= 100;
		pTargetData->m_SealRate.d2 -= sbuf->damage;
		// 		pTargetData->poisonRate.d1 -= 30;
		pTargetData->PeopleSpecial.d1 -= 100;
		break;
	case 122:
		break;
	case 123://��������

	{
		pTarget->SetShadow(FALSE);
		//			pTargetData->m_HitRate.d1 -= 10;
		// 			pTargetData->m_HitRate.d2 -= 100;
		// 			pTargetData->m_MagicHitRate.d2 -= 100;
		// 			pTargetData->m_SealRate.d2 -= 100;
		// 			pTargetData->poisonRate.d2 -= 100;
		targetProperty.cannotMagic -= 1;
		pTargetData->PeopleSpecial.d2 -= 100;
	}
	break;
	case 125:
		pTargetData->m_ATK.AddDataAdd(-sbuf->damage);
		break;
	case 126:// ��Ȫ֮Ϣ
		pTargetData->m_SPD.AddDataAddPercent(20);
		break;
	case 129:// ������
		targetProperty.cannotLive -= 1;
		break;
	case 133://ţ��
		pTargetData->m_Wakan.AddDataAdd(-sbuf->damage);
		//		pTargetData->m_MagicHitRate.d1 -= 100;
		pTargetData->PeopleSpecial.d1 -= 100;
		break;
	case 142://ӥ��
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotSkill -= 1;
		targetProperty.cannotUseItem -= 1;
		break;
	case 144:// ����
		pTargetData->m_ATK.AddDataAddPercent(20);
		pTargetData->m_DEF.AddDataAddPercent(10);
		pTargetData->m_Wakan.AddDataAddPercent(10);
		break;
	case 145:// ����
		pTargetData->m_ATK.AddDataAdd(-sbuf->damage);
		break;
	case 147://����
		pTargetData->m_Wakan.AddDataAdd(-sbuf->damage);
		break;
	case 150://���ȷ��
		pTargetData->m_CounterRate.d1 -= 100;
		break;
	case 152://��ħ����
		pTargetData->m_HPMax.AddDataAddPercent(-30);

		{
			int dam = AddHp(targetID, -5, 10000);
			SetDamage(-dam, targetID);
		}
		break;
	case 156://ħ�����
		pTargetData->m_FightProperty.cannotAddHP -= 1;
		break;
	case 159://��������
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		break;

	case 160:// ��˿��	
		pTargetData->m_DEF.AddDataAdd(-sbuf->damage);
		break;

	case 162:  //���޵���
		targetProperty.cannotAttack -= 1;
		break;
	case 166://�þ���
		pTargetData->m_StabRateMagic.d1 -= 50;    //���������˺�
		pTargetData->m_StabDamageRateMagic.d1 -= 50; //����������
		break;
	case 1002:
		pTargetData->m_ParryRate.d1 -= 1000;
		break;
	case 1004:
		break;
	case 2092://����һ��
//		pTargetData->m_ATK.AddDataAddPercent(20);
		break;
	case 2093://ҹ�����
		pTargetData->m_ATK.AddDataAddPercent(10);   //�˺�
		pTargetData->m_HIT.AddDataAddPercent(10);   //����
		pTargetData->m_DEF.AddDataAddPercent(10);   //����
		pTargetData->m_Wakan.AddDataAddPercent(10); //����
		pTargetData->m_SPD.AddDataAddPercent(10);   //�ٶ�
		pTargetData->m_Evade.AddDataAddPercent(10); //����
		break;
	case 2094://�����ٻ�
		pTargetData->m_FightProperty.cannotLive -= 1;
		break;
	case 2095:
		pTargetData->m_HIT.AddDataAddPercent(-200); //����
		break;
	case 2097:// ��������
		pTargetData->m_DamageAddPercentMagic.d2 -= 65;
		break;
	case 3024://̫������ �޺�
	case 3025:
		pTargetData->m_DamageAddPercentMagic.d2 -= 50;
		break;
	case 3026://������
		pTargetData->m_StabRateMagic.d1 -= 100;
		pTargetData->m_StabDamageRateMagic.d1 -= 30;
		break;
	case 3027://�����޷�
		pTargetData->m_MagicHitRate.d2 -= 50;
		break;
	case 3047://��������
		pTargetData->m_DamageAddPercentMagic.d2 -= 50;//���������ӳ�
		pTargetData->m_DamagePercent.d2 -= 50;//��������ӳ�
		break;
	default:
		ERRBOX2(stateid);
		return FALSE;
		break;
	}
	return TRUE;
}





BOOL cSkillManager::Use61����(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	if (!Skilllv)
	{
		Skilllv = g_pMainState->m_FightList[UserID].m_pData->GetSkillLv(0);
	}
	sFightList* pUserList = m_pFightState->m_pList[UserID];
	cObj* pUser = pUserList->m_pData;
	cPetData* pPet;
	pUser->GetDateP(pPet);
	int lv = pPet->m_LV;
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:

	{
		if (pUser->m_IndexType == INDEXTYEP_PET)
		{
			pUserList->m_work.pop_back();
			stage = -1;
			g_pMainState->m_Channel.AddNewString("�����޷�ʹ�ð���");
			return TRUE;
		}
		// 		sItem2* pItem = GetItem(UserID);
		// 		if (pItem->GetNum() < 1)
		// 		{
		// 			pUserList->m_work.pop_back();
		// 			stage = -1;
		// 			g_pMainState->m_Channel.AddNewString("û�е���");
		// 			return TRUE;
		// 		}
		// 		if (lv / 15 < pItem->GetID())
		// 		{
		// 			pUserList->m_work.pop_back();
		// 			stage = -1;
		// 			g_pMainState->m_Channel.AddNewString("��ɫ�ȼ�̫��,�޷�ʹ��");
		// 			return TRUE;
		// 		}
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		stage += 1;
	}
	return TRUE;
	case 1:

	{

		if (WaitForMagicPoint(UserID))
		{
			stage += 1;
			sItem2* pItem = GetItem(UserID);

			DWORD dateid = 0;
			int num = 0;
			switch (Skilllv / 20)
			{
			case 0://�ɵ�
				dateid = 0x44BE65A3;
				num = 1;
				break;
			case 1://�ɻ�ʯ
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 2://����޼
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 3://��Ӱ����
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 4://��ȸ��
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 5://��ɳ��Ӱ
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 6://��������
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 7://��������
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 8://ħ����
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 9://˳������
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			default:
				dateid = 0x44BE65A3;
				break;
				//				return FALSE;
			}
			num = Skilllv / 25 + 1;
			if (num > 7)
			{
				num = 7;
			}

			m_pFightState->m_HiddenWeapons.Load(dateid);
			int i = 0;
			for (; i < num; i++)
			{
				m_pFightState->m_HiddenWeaponsTargetID[i] = g_pMainState->m_AI.GetNear(UserID, TargetID, i, TRUE + 2);
				if (-1 == m_pFightState->m_HiddenWeaponsTargetID[i])
					break;
				m_pFightState->m_HiddenWeaponsp[i].m_NeedShow = TRUE;
				m_pFightState->m_HiddenWeaponsp[i].m_x = pUser->GetX();
				m_pFightState->m_HiddenWeaponsp[i].m_y = pUser->GetY() - 30;
			}
			m_pFightState->m_HiddenWeaponsUseNum = i;
		}
	}
	return TRUE;
	case 2:
		if (m_pFightState->WaitPosEnd(UserID) || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUser->Set(POS_FIGHT_STAND);
			stage += 1;
		}
	case 3:

	{
		int targetid;
		sItem2* pItem = GetItem(UserID);
		for (int i = 0; i < 10; i++)
		{
			if (TRUE == m_pFightState->m_HiddenWeaponsp[i].m_NeedShow)
			{
				if (m_pFightState->HiddenWeaponsMove(i))
				{
					targetid = m_pFightState->m_HiddenWeaponsTargetID[i];
					m_pFightState->m_HiddenWeaponsUseNum -= 1;
					m_pFightState->m_HiddenWeaponsp[i].m_NeedShow = FALSE;
					if (!g_pMainState->m_FightList[targetid].isLive)continue;
					cPetData* pTargetData;
					g_pMainState->m_FightList[targetid].m_pData->GetDateP(pTargetData);
					int damageup = pPet->m_HiddenWeaponDamagePercent.d1 - pTargetData->m_HiddenWeaponDamagePercent.d2;
					if (rand() % 100 >= 100 + pPet->m_HitRate.d1 - pTargetData->m_HitRate.d2)
					{
						m_pFightState->SetAvoid(targetid, pUser->GetDirection());
					}
					else
					{
						int dam, damh;
						switch (Skilllv / 20)
						{
						case 0://�ɵ�
							dam = 100;
							damh = 10;
							break;
						case 1://�ɻ�ʯ
							dam = 120;
							damh = 20;
							break;
						case 2://����޼
							dam = 200;
							damh = 50;
							break;
						case 3://��Ӱ����
							dam = 300;
							damh = 80;
							break;
						case 4://��ȸ��
							dam = 400;
							damh = 100;
							break;
						case 5://��ɳ��Ӱ
							dam = 500;
							damh = 150;
							break;
						case 6://��������
							dam = 800;
							damh = 200;
							break;
						case 7://��������
							dam = 1000;
							damh = 250;
							break;
						case 8://ħ����
							dam = 1500;
							damh = 300;
							break;
						default://˳������
							dam = 2000;
							damh = 400;
							break;
						}


						damh = dam = (Skilllv / 20 + 1) * 30;
						dam = (Skilllv * 2 + dam + 50);
						dam = dam * (100 + damageup) / 100;

						if (dam > 0)
						{
							CheckPoision(UserID, targetid);//�ж�����
							if ((TargetID < 10) || g_pMainState->m_AI.m_AttackAI.m_bPKMode)
							{//��ͨ����ʱ�˺���ʵ��2������
								// 									dam = dam >> 1;
								// 									damh = damh >> 1;
							}
							m_pFightState->SetSuffer(targetid, m_pFightState->m_HiddenWeaponsp[i].m_direction, UserID);
							AddHp(targetid, -dam);
							AddHpHurt(targetid, -damh);
							SetDamage(dam, targetid);
						}
						else
							m_pFightState->SetAvoid(targetid, m_pFightState->m_HiddenWeaponsp[i].m_direction);
					}
				}
			}
		}
		if (0 == m_pFightState->m_HiddenWeaponsUseNum)
		{
			if (3 == stage)
			{
				pUserList->m_work.pop_back();
				stage = -1;
			}
		}
	}
	break;
	}
	return TRUE;
}





BOOL cSkillManager::SetPetSkill1(cPetData* pPetDate, int ID, int lv)
{
	switch (ID)
	{
	case 0://����
		pPetDate->m_CounterRate.d1 += lv * 30;
		break;
	case 1://�߼�����
		pPetDate->m_CounterRate.d1 += lv * 45;
		break;
	case 2://����
		pPetDate->m_StabRate.d1 += lv * 30;
		pPetDate->m_StabDamageRate.d1 += lv * 30;
		break;
	case 3://�߼�����
		pPetDate->m_StabRate.d1 += lv * 30;
		pPetDate->m_StabDamageRate.d1 += lv * 50;
		break;
	case 4://��Ѫ
		pPetDate->m_SuckBloodRate.d1 += lv * 20;
		break;
	case 5://�߼���Ѫ
		pPetDate->m_SuckBloodRate.d1 += lv * 35;
		break;
	case 6://����
		pPetDate->m_Combo.d1 += lv * 15;
		break;
	case 7://�߼�����
		pPetDate->m_Combo.d1 += lv * 30;
		break;
	case 8://����
		pPetDate->m_HitRate.d1 += lv * 10;
		pPetDate->m_HitRate.d2 += lv * 10;
		pPetDate->m_HiddenWeaponDamagePercent.d2 -= lv * 50;
		break;
	case 9://�߼�����
		pPetDate->m_HitRate.d1 += lv * 20;
		pPetDate->m_HitRate.d2 += lv * 20;
		pPetDate->m_HiddenWeaponDamagePercent.d2 -= lv * 20;
		break;
	case 10://ҹս
//		pPetDate->m_Spurting.d2 += 20;
		pPetDate->m_DamagePercent.d1 += lv * 5;
		//		pPetDate->nightLv += lv *10;
		break;
	case 11://�߼�ҹս
//		pPetDate->m_Spurting.d2 += 30;
		pPetDate->m_DamagePercent.d1 += lv * 10;
		//		pPetDate->nightLv += lv * 20;
		break;
	case 12://����
// 		pPetDate->m_HitRate.d2 += lv*15;
// 		pPetDate->m_MagicHitRate.d2 += lv * 15;
// 		pPetDate->m_SealRate.d2 += lv * 15;
// 		pPetDate->poisonRate.d2 += lv * 15;
		pPetDate->m_StartMagic.d1 = lv > 0 ? 123 : 0;
		break;
	case 13://�߼�����
// 		pPetDate->m_HitRate.d2 += lv * 25;
// 		pPetDate->m_MagicHitRate.d2 += lv * 25;
// 		pPetDate->m_SealRate.d2 += lv * 25;
// 		pPetDate->poisonRate.d2 += lv * 25;
		pPetDate->m_StartMagic.d1 = lv > 0 ? 123 : 0;
		break;
	case 14://��֪
// 		pPetDate->m_HitRate.d1 += lv * 35;
// 		pPetDate->m_MagicHitRate.d1 += lv * 35;
// 		pPetDate->poisonRate.d1 += lv * 35;
		pPetDate->PeopleSpecial.d1 += 100;
		break;
	case 15://�߼���֪
		pPetDate->m_HitRate.d1 += lv * 25;
		// 		pPetDate->m_MagicHitRate.d1 += lv * 65;
		// 		pPetDate->poisonRate.d1 += lv * 65;
		pPetDate->PeopleSpecial.d1 += 100;
		break;
	case 16://����
		pPetDate->m_LiveHpLv += lv * 10;
		break;
	case 17://�߼�����
		pPetDate->m_LiveHpLv += lv * 20;
		break;
	case 18://ڤ˼
		pPetDate->m_LiveMpLv += lv * 5;
		break;
	case 19://�߼�ڤ˼
		pPetDate->m_LiveMpLv += lv * 10;
		break;
	case 20://�۸�
		pPetDate->mpsavepercent += lv * 25;
		break;
	case 21://�߼��۸�
		pPetDate->mpsavepercent += lv * 50;
		break;
	case 22://����
//		pPetDate->m_CriRate.d2   -= lv*10;
		pPetDate->m_CriRate.d2 -= lv * 10;
		break;
	case 23://��ɱ
		pPetDate->m_CriRate.d1 += lv * 10;
		break;
	case 24://�߼���ɱ
		pPetDate->m_CriRate.d1 += lv * 20;
		break;
	case 25://����
		pPetDate->m_CriRate.d2 += lv * 60;
		//		pPetDate->m_MagicCriRate.d2 -= lv * 60;
		break;
	case 26://�߼�����
		pPetDate->m_CriRate.d2 += lv * 200;
		//		pPetDate->m_MagicCriRate.d2 -= lv * 20;
		break;
	case 27://��
		pPetDate->restoreRate += lv * 60;
		break;
	case 28://�߼���
		pPetDate->restoreRate += lv * 200;
		break;
	case 29://�м�
		pPetDate->m_ParryRate.d1 += lv * 10;
		break;
	case 30://�߼��м�
		pPetDate->m_ParryRate.d1 += lv * 20;
		break;
	case 31://����
		pPetDate->buffAdd += lv * 1;
		break;
	case 32://�߼�����
		pPetDate->buffAdd += lv * 2;
		break;
	case 33://����
		pPetDate->m_SPD.AddDataAddPercent(lv * 10);
		break;
	case 34://�߼�����
		pPetDate->m_SPD.AddDataAddPercent(lv * 20);
		break;
	case 35://ǿ��
		pPetDate->m_ATK.AddDataAddPercent(lv * 5);
		break;
	case 36://�߼�ǿ��
		pPetDate->m_ATK.AddDataAddPercent(lv * 10);
		break;
	case 37://����
		pPetDate->m_DEF.AddDataAddPercent(lv * 5);
		break;
	case 38://�߼�����
		pPetDate->m_DEF.AddDataAddPercent(lv * 10);
		break;
	case 39://͵Ϯ  
		pPetDate->m_StabRate.d2 += lv * 50;//����������
		pPetDate->m_CounterRate.d2 += lv * 50;//����������
		pPetDate->m_ParryRate.d2 += lv * 50;//����
		break;
	case 40://�߼�͵Ϯ
		pPetDate->m_StabRate.d2 += lv * 100;//����������
		pPetDate->m_CounterRate.d2 += lv * 100;
		pPetDate->m_ParryRate.d2 += lv * 100;
		break;
	case 41://��
		pPetDate->poisonRate.d1 += lv * 10;
		break;
	case 42://�߼���
		pPetDate->poisonRate.d1 += lv * 20;
		break;
	case 43://����
		pPetDate->ghostSpecial.d1 += lv * 50;
		break;
	case 44://�߼�����
		pPetDate->ghostSpecial.d1 += lv * 100;
		break;
	case 45://�����
//		pPetDate->m_DamagePercent.d2 += lv*20;
		pPetDate->m_race += lv * 1020;
		// 		if (lv > 0)
		// 		{
		// 			pPetDate->m_race += 1020;
		// 		}
		// 		else
		// 		{
		// 			pPetDate->m_race -= 1020;
		// 		}
		break;
	case 46://�߼������
		pPetDate->m_race += lv * 1020;
		//		pPetDate->m_DamagePercent.d2 += lv*30;
		// 		if (lv > 0)
		// 		{
		// 			pPetDate->m_race += 1020;
		// 		}
		// 		else
		// 		{
		// 			pPetDate->m_race -= 1020;
		// 		}
		break;
	case 47://ħ֮��
		pPetDate->m_DamageAddPercentMagic.d1 += lv * 10;
		break;
	case 48://�߼�ħ֮��
		pPetDate->m_DamageAddPercentMagic.d1 += lv * 20;
		break;
	case 49://����
		pPetDate->GoldLivePercent.d1 += lv * 20;
		break;
	case 50://�߼�����
		pPetDate->GoldLivePercent.d1 += lv * 35;
		break;
	case 51://������
		pPetDate->m_SealRate.d2 += lv * 10;
		break;
	case 52://�߼�������
		pPetDate->m_SealRate.d2 += lv * 20;
		break;
	case 53://������
		pPetDate->GoldLivePercent.d2 += lv * 20;
		break;
	case 54://�߼�������
		pPetDate->GoldLivePercent.d2 += lv * 30;
		break;
	case 55://��������
		pPetDate->m_MagicComboRate.d1 += lv * 20;
		break;
	case 56://�߼���������
		pPetDate->m_MagicComboRate.d1 += lv * 30;
		break;
	case 57://��������
		pPetDate->m_MagicCriRate.d1 += lv * 10;
		break;
	case 58://�߼���������
		pPetDate->m_MagicCriRate.d1 += lv * 15;
		break;
	case 59://��������
		pPetDate->magicWavePercent += lv * 20;
		break;
	case 60://�߼���������
		pPetDate->magicWavePercent += lv * 35;
		break;
	case 61://�ٶ�
//		pPetDate->m_DEF.AddDataAddPercent(lv * 20);
		pPetDate->m_SPD.AddDataAddPercent(-lv * 50);
		//		pPetDate->m_HitRate.d2 -= lv * 20;
		//		pPetDate->m_ParryRate.d1 -= lv * 40;
		break;
	case 62://�����
		pPetDate->m_MagicFire.d2 -= lv * 30; //��	
		break;
	case 63://����ˮ
		pPetDate->m_MagicWater.d2 -= lv * 30;  //ˮ
		break;
	case 64://������
		pPetDate->m_MagicSoil.d2 -= lv * 30; //��
		break;
	case 65://������
		pPetDate->m_MagicThunder.d2 -= lv * 30;//��
		break;
	case 66://����������
		pPetDate->m_MagicThunder.d2 += lv * 20;//��
		break;
	case 67://�߼�����������
		pPetDate->m_MagicThunder.d2 += lv * 30;//��
		break;
	case 68://����������
		pPetDate->m_MagicSoil.d2 += lv * 20; //��
		break;
	case 69://�߼�����������
		pPetDate->m_MagicSoil.d2 += lv * 30; //��
		break;
	case 70://����������
		pPetDate->m_MagicFire.d2 += lv * 20; //��
		break;
	case 71://�߼�����������
		pPetDate->m_MagicFire.d2 += lv * 30; //��
		break;
	case 72://ˮ��������
		pPetDate->m_MagicWater.d2 += lv * 20;  //ˮ
		break;
	case 73://�߼�ˮ��������
		pPetDate->m_MagicWater.d2 += lv * 30;  //ˮ
		break;
	case 74://�ƻ���ľ 
		pPetDate->m_HiddenWeaponDamagePercent.d2 += lv * 95;
		break;
	case 75://����
		pPetDate->m_Spurting.d1 += lv * 15;
		break;
	case 76://��Ѫ׷��
		pPetDate->ShiXueAdd += lv * 5;
		break;
	case 77://���۷���(����)
//		pPetDate->m_DamageAddMagicLv.d2 += lv * 2;//�����˺����
// 		pPetDate->m_DamageAddLv.d2	+= lv * 2;  //�����˺����
// 		pPetDate->m_DamageAddPercentMagic2.d2 += 10;
// 		pPetDate->m_MagicWater.d2 += lv*20;  //ˮ
		break;
	case 78://�����ػ�(�߼�����)
//		pPetDate->m_DamageAddMagicLv.d2 += lv * 3;//�����˺����
// 		pPetDate->m_DamageAddLv.d2 += lv * 3;  //�����˺����
// 		pPetDate->m_DamageAddPercentMagic2.d2 += 15;
// 		pPetDate->m_MagicWater.d2 += lv * 30;  //ˮ
		break;
	case 79://�����ֿ�
		pPetDate->m_DamageAddPercentMagic.d2 += lv * 15;
		break;
	case 80://�߼������ֿ�
		pPetDate->m_DamageAddPercentMagic.d2 += lv * 25;
		break;
	case 81://ֱ��(���ݣ�С�绪)
//		pPetDate->m_Pierce.d1 += 20;//���ӷ�����
//		pPetDate->m_PierceMagic.d1+=30; //����������
		pPetDate->comboNumUp += lv * 1;
		//		pPetDate->m_Combo.d1 += lv * 15;
		break;
	case 82://�绪��ʥ
		pPetDate->comboNumUp += lv * 3;
		//		pPetDate->m_Combo.d1 += lv * 15;
		break;
	case 83://��������
		pPetDate->m_StabRateMagic.d1 += lv * 35;//����������
		pPetDate->m_StabDamageRateMagic.d1 += lv * 30;//���������˺���
		break;
	}
	return TRUE;
}



BOOL  cSkillManager::CountMagicDamage(int& dam, int UserID, int TargetID, int Damageup, eMagicWuXing wuxing)//���㷨���˺�
{
	cPetData*  pUserData;
	cPetData*  pTargetData;
	cObj* pUser = m_pFightState->m_pList[UserID]->m_pData;
	cObj* pTarget = m_pFightState->m_pList[TargetID]->m_pData;
	pUser->GetDateP(pUserData);
	pTarget->GetDateP(pTargetData);

	if (pTargetData->m_FightProperty.m_WallNum > 0)
	{//���֮ǽ
		pTargetData->m_FightProperty.m_WallNum -= 1;
		dam = 0;
		return TRUE;
	}
	int hit = 100 + pUserData->m_MagicHitRate.d1 - pTargetData->m_MagicHitRate.d2;
	if (rand() % 100 >= hit)//�����ر�
	{
		dam = 0;
		return TRUE;
	}

	int wakanUser = pUserData->m_Wakan.GetData();    //��������
	int  wakanTarget = pTargetData->m_Wakan.GetData(); //Ŀ������
//	wakanTarget -= pUserData->m_LV<<1;
	// ����
	int turn = m_pFightState->m_pList[TargetID]->_myTurn;
	if (pTargetData->CheckHavePetSkill(78) && turn < 5)
	{
		wakanTarget += (5 - turn) * pTargetData->m_LV * 2 / 5;
	}
	else if (pTargetData->CheckHavePetSkill(77) && turn < 5)
	{
		wakanTarget += (10 - turn) * pTargetData->m_LV / 5;
	}
	int& atknum = pTargetData->m_FightProperty.SufferNum;
	////////////////////////////////////////////////////////////////////////// �Ǻ��� ����Խ����Խ�޷�����
	int pierce = pUserData->m_PierceMagic.d1 + atknum/* * 3*/;
	if (pierce)
	{
		if (pierce > 100)pierce = 100;
		wakanTarget -= (wakanTarget* pierce) / 100; //��������
	}
	int DamageAddPercent = pUserData->m_DamageAddPercentMagic.d1; //��������������
	int DamageDefPercent = pTargetData->m_DamageAddPercentMagic.d2;   //Ŀ�귨����������
	if (DamageDefPercent > 9900)
	{
		DamageDefPercent = DamageAddPercent + DamageDefPercent - 9900;
	}
	dam = (wakanUser)-(wakanTarget)+pUserData->m_LV;

	int װ���˺����� = pUserData->m_LV;
	if (pUser->m_IndexType == INDEXTYEP_CHARACTER)
	{
		cCharacter *pc = (cCharacter*)pUser->m_pIndex;
		װ���˺����� = pc->m_PCData.getEquipAtk() / 5;
	}
	int skillLv = pUser->GetSkillLv(0);
	if (!skillLv)
	{
		skillLv = pUserData->m_LV;
	}
	int targetNum = g_pMainState->m_FightList[UserID].m_MaxTargetNum;
	if (targetNum < 1) targetNum = 1;
	dam = (skillLv * Damageup + wakanUser * 10 - wakanTarget * 10 + װ���˺����� * 10) * (21 - targetNum) / 200;
	if (dam < 1)
	{
		dam = 1;
	}
	if (pUserData->CheckHavePetSkill(103))
	{
		// ӵ����������,+ħ��*0.4���˺���
		dam += pUserData->m_ProPertyMag * 2 / 5;
	}
	Damageup = 0;
	int xiuliancha = pUserData->m_XiuLian.GetMag() - pTargetData->m_XiuLian.GetDMag();
	float damf = (float)dam;
	if (xiuliancha > 0)
	{
		for (int i = 0; i < xiuliancha; ++i)
		{
			damf = damf * 1.02f + 5;
		}
	}
	else
	{
		for (int i = 0; i < (-xiuliancha); ++i)
		{
			damf = damf * 0.98f - 5;
			if (damf < 1)
			{
				damf = 1;
				break;
			}
		}
	}
	dam = (int)damf;
	BOOL bCri = FALSE;
	// 	bool isPc = pUser->m_IndexType == INDEXTYEP_CHARACTER;
	// 	bool isPT = ((cCharacter*)pUser->m_pIndex)->m_PCData.m_MengPaiID == eMengPai::eMP_����ɽ;
	// 	if (!isPc || (isPc && isPT))
	// 	{
	// 
	// 	}
	int damageup = -CorrectWuXing(pUserData, pTargetData, wuxing);//�������� --> ��������
	if (rand() % 100 < damageup)
	{
		dam = -dam;
	}
	else
	{
		dam = dam * (100 - damageup) / 100;
	}
	if (dam > 1)
	{
		//		Damageup += CorrectWuXing(pUserData, pTargetData, wuxing);//��������	
		Damageup += CountSpecial(pUserData, pTargetData, pTarget->GetSex());//�ع�����
		bCri = CountCriMagic(pUserData, pTargetData, dam);//��������

		if (pUserData->magicWavePercent)
		{//��������
			dam = dam * (100 + (rand() % pUserData->magicWavePercent) - (rand() % (pUserData->magicWavePercent / 2))) / 100;
		}
		dam = dam * (100 + DamageAddPercent - DamageDefPercent + Damageup) / 100;
		dam += (pUserData->m_DamageAddMagicLv.d1 - pTargetData->m_DamageAddMagicLv.d2) * skillLv/*pUserData->m_LV*/;
		if (rand() % 100 < pUserData->m_XiangMoRate.d1 - pUserData->m_XiangMoRate.d2)dam /= 2;
		if (Damageup > -1)if (dam < 1)dam = 1;
		//	}
		//	else dam = 1;
		CheckFightStateOnLine(TargetID, dam);
		if (pTargetData->m_StabRateMagic.d1)
		{
			//int rate= pTargetData->m_StabRateMagic.d1 - pUserData->m_StabRateMagic.d2;
			if (rand() % 100 < dam)
			{
				int rate = pTargetData->m_StabDamageRateMagic.d1 - pUserData->m_StabDamageRateMagic.d2;
				int dam2 = dam * rate / 100;
				CheckGodLivePercent(dam2, UserID, TargetID); //����
				AddHp(UserID, -dam2);
				SetDamage(dam2, UserID);
			}
		}

		if (pTargetData->m_FightProperty.m_bDefend)dam = dam * 4 / 5;//����Ƿ����	

		//����
		int rate = pUserData->m_MagDownHPHurt.d1 - pTargetData->m_MagDownHPHurt.d2;
		if (rate > 0)AddHpHurt(TargetID, -(dam*rate) / 100);

		CheckGodLivePercent(dam, TargetID, UserID); //����
	}
//	asert(dam < 20000, "�����˺�����2��");
	AddHp(TargetID, -dam);
	SetDamage(dam, TargetID);
	pTargetData->m_FightProperty.SufferNum += 1;
	return bCri;
}
void cSkillManager::CountphysicalDamage(int& dam, int UserID, int TargetID, int Damageup/*=0*/)
{
	cObj* pUser;
	cObj* pTarget;
	cPetData* UserData;
	cPetData* TargetData;
	pUser = m_pFightState->m_pList[UserID]->m_pData;
	pUser->GetDateP(UserData);
	pTarget = m_pFightState->m_pList[TargetID]->m_pData;
	pTarget->GetDateP(TargetData);
	//sFightData& userFightData = UserData->m_FightProperty;
	sFightData& targetFightData = TargetData->m_FightProperty;
	if (TargetData->m_FightProperty.m_WallNum > 0)
	{
		TargetData->m_FightProperty.m_WallNum -= 1;
		dam = 0;
		return;
	}
	int userAtk = UserData->m_ATK.GetData();    //������
	int SufferDef = TargetData->m_DEF.GetData(); //Ŀ�����
	// ����
	int turn = m_pFightState->m_pList[TargetID]->_myTurn;
	if (TargetData->CheckHavePetSkill(78) && turn < 5)
	{
		SufferDef += (5 - turn) * TargetData->m_LV * 2 / 5;
	}
	else if (TargetData->CheckHavePetSkill(77) && turn < 5)
	{
		SufferDef += (10 - turn) * TargetData->m_LV / 5;
	}

	int& atknum = targetFightData.SufferNum;

	////////////////////////////////////////////////////////////////////////// �Ǻ��� Խ�����Խû��
	int picrcerate = UserData->m_Pierce.d1 - TargetData->m_Pierce.d2 + atknum/**3*/;
	bool is���� = false;
	bool is�ƶ� = false;
	bool is���� = false;
	if (Damageup == 10086)
	{
		is���� = true;
		Damageup = 0;
		picrcerate += 5;
	}
	if (Damageup == 10087)
	{
		Damageup = 0;
		picrcerate += 10;
		if (TargetData->m_FightProperty.m_bDefend)
		{
			is���� = true;
		}
	}
	if (Damageup == 10088)
	{
		is�ƶ� = true;
		Damageup = 0;
		picrcerate += 5;
	}
	if (picrcerate > 0)
	{
		SufferDef -= (SufferDef * picrcerate) / 100;//���ӷ���
	}

	if (is����)
	{
		// ������ɽ
		dam += userAtk * 3 - (SufferDef + TargetData->m_ATK.GetData()) * 3 / 2;
	}
	else
	{
		dam += (userAtk)-(SufferDef);
	}
	if (dam < 1)
	{
		dam = 1;
	}
	//�������˺�����
	int xiuliancha = UserData->m_XiuLian.GetAtk() - TargetData->m_XiuLian.GetDef();
	float damf = (float)dam;
	if (xiuliancha > 0)
	{
		for (int i = 0; i < xiuliancha; ++i)
		{
			damf = damf * 1.02f + 5;
		}
	}
	else
	{
		for (int i = 0; i < (-xiuliancha); ++i)
		{
			damf = damf * 0.98f - 5;
			if (damf < 1)
			{
				damf = 1;
				break;
			}
		}
	}
	dam = (int)damf;
	//	asert(dam < 50000, "�������˺���������");
	Damageup += CountSpecial(UserData, TargetData, pTarget->GetSex());//�ع�����

	int atk2345 = UserData->ShiXueAdd; //����������
	if (atk2345 >= 0xffffff)
	{
		atk2345 -= 0xffffff;
	}
	// 	while (atk2345 >= 0xffff)
	// 	{
	// 		atk2345 -= 0xffff;
	// 	}
	atk2345 *= atknum;
	Damageup += atk2345;

	int& userlv = UserData->m_LV;  //����ȼ�
	dam += dam * Damageup / 100;
	int damp = UserData->m_DamagePercent.d1 - TargetData->m_DamagePercent.d2;
	if (TargetData->m_DamagePercent.d2 > 9900)
	{
		damp = 9900 - TargetData->m_DamagePercent.d2;
	}
	dam = dam * (100 + damp) / 100;

	//��ɱ����
	CountCriDamage(UserData, TargetData, dam);
	if (!is�ƶ� && rand() % 100 < UserData->m_JinJiaRate.d1 - UserData->m_JinJiaRate.d2)dam /= 2;

	//�������
	dam += UserData->m_DamageAdd.d1 - TargetData->m_DamageAdd.d2;
	dam += (UserData->m_DamageAddLv.d1 - TargetData->m_DamageAddLv.d2) * userlv;
	if (dam < 1)dam = 1;
	int damSE = dam;
	if (is�ƶ�)
	{
		if (rand() % 100 < 75)
		{
			damSE *= 2;
		}
		else
		{
			damSE /= -2;
		}
	}
	else if (dam > 0 && TargetData->m_FightProperty.m_bDefend)
	{
		if (is����)
		{
			dam *= 2;
		}
		else
		{
			dam /= 2;
		}
	}
	if (damSE > 0)
	{
		CheckFightStateOnLine(TargetID, dam);
	}
	CheckPoision(UserID, TargetID);//�ж�����
	int damOld = dam;
	if (is�ƶ�)
	{
		dam = 0;
	}
	CountProtect(dam, pUser, pTarget);//�����˺�����
	if (is�ƶ�)
	{
		dam = damOld;
	}
	SuckBlood(dam, UserID, TargetData);//��Ѫ
	CheckFanZheng(UserID, TargetID, dam);//����
	//����
//	asert(dam < 50000, "�����󳬹�����");
	int rate = UserData->m_AtkDownHPHurt.d1 - TargetData->m_AtkDownHPHurt.d2;
	if (rate > 0)AddHpHurt(TargetID, -(dam*rate) / 100);
	//����
	rate = UserData->m_AtkDownMP.d1 - TargetData->m_AtkDownMP.d2;
	if (rate > 0)AddMp(TargetID, -(dam*rate) / 100);
	//����
	if (TargetData->m_AtkDownAtk.d1)
	{
		if (TargetData->m_ATK.GetData() > 1)
		{
			rate = UserData->m_AtkDownAtk.d1 - TargetData->m_AtkDownAtk.d2;
			if (rate > 0)
			{
				if (TargetData->m_ATK.GetData() <= rate)rate = TargetData->m_ATK.GetData() - 1;
				TargetData->m_ATK.AddDataAdd(-rate);
			}
		}
	}
	//����
	if (TargetData->m_AtkDownDef.d1)
	{
		if (TargetData->m_DEF.GetData() > 1)
		{
			rate = UserData->m_AtkDownDef.d1 - TargetData->m_AtkDownDef.d2;
			if (rate > 0)
			{
				if (TargetData->m_DEF.GetData() <= rate)rate = TargetData->m_DEF.GetData() - 1;
				TargetData->m_DEF.AddDataAdd(-rate);
			}
		}
	}
	//������
	if (TargetData->m_AtkDownHit.d1)
	{
		if (TargetData->m_HIT.GetData() > 1)
		{
			rate = UserData->m_AtkDownHit.d1 - TargetData->m_AtkDownHit.d2;
			if (rate > 0)
			{
				if (TargetData->m_HIT.GetData() <= rate)rate = TargetData->m_HIT.GetData() - 1;
				TargetData->m_HIT.AddDataAdd(-rate);
			}
		}
	}
	//����
	if (TargetData->m_AtkDownWakan.d1)
	{
		if (TargetData->m_Wakan.GetData() > 1)
		{
			rate = UserData->m_AtkDownWakan.d1 - TargetData->m_AtkDownWakan.d2;
			if (rate > 0)
			{
				if (TargetData->m_Wakan.GetData() <= rate)rate = TargetData->m_Wakan.GetData() - 1;
				TargetData->m_Wakan.AddDataAdd(-rate);
			}
		}
	}
	//����
	if (TargetData->m_AtkDownSpd.d1)
	{
		if (TargetData->m_SPD.GetData() > 1)
		{
			rate = UserData->m_AtkDownSpd.d1 - TargetData->m_AtkDownSpd.d2;
			if (rate > 0)
			{
				if (TargetData->m_SPD.GetData() <= rate)rate = TargetData->m_SPD.GetData() - 1;
				TargetData->m_SPD.AddDataAdd(-rate);
			}
		}
	}

	//��CP
	if (TargetData->m_AtkDownCP.d1)
	{
		rate = UserData->m_AtkDownCP.d1 - UserData->m_AtkDownCP.d2;
		if (rate > 0)UserData->m_CP -= rate;
		if (UserData->m_CP < 0)UserData->m_CP = 0;
	}

	if (is�ƶ�)
	{
		dam = damSE;
	}
	CheckGodLivePercent(dam, TargetID, UserID); //����
//	asert(dam < 35555, "�����˺�����3��");
	AddHp(TargetID, -dam);
	SetDamage(dam, TargetID);
	atknum += 1;
}



void cSkillManager::EffectSkill(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	if (TargetID == -1)return;
	sFightList* pUserList = m_pFightState->m_pList[UserID];
	cObj* pTarget = m_pFightState->m_pList[TargetID]->m_pData;
	cObj* pUser = m_pFightState->m_pList[UserID]->m_pData;
	cPetData* pTargetData;
	cPetData* pUserData;
	sBuff buf;
	buf.times = -999;

	pTarget->GetDateP(pTargetData);
	pUser->GetDateP(pUserData);
	int& userlv = pUserData->m_LV;
	int& targetlv = pTargetData->m_LV;
	int dam = 0;

	switch (sSkillID)
	{
	case 50:return;
		//	case 2095:return;
	case 1050:
		CountphysicalDamage(dam, UserID, TargetID/*, 30*/);
		if ((rand() % 100) < 80)
		{
			buf.times = 2 + rand() % 4;
			SetDateBuffUp(UserID, TargetID, 50, buf, Skilllv);
			buf.times = -999;
		}
		break;
	case 1095://����
	{
		CountphysicalDamage(dam, UserID, TargetID, 10086);
	}
	break;
	case 2101://�ռ���

	{
		pUserData->m_PierceMagic.d1 += 80;
		CountMagicDamage(dam, UserID, TargetID, 20, eMWX��);
		pUserData->m_PierceMagic.d1 -= 80;
	}
	break;
	case 3040://����
		CountphysicalDamage(dam, UserID, TargetID, 0);
		AddMp(TargetID, -dam);
		break;
	case 3035://����
		pUserData->m_Pierce.d1 += 40;
		CountphysicalDamage(dam, UserID, TargetID, 0);
		pUserData->m_Pierce.d1 -= 40;
		break;
	case 3043://����EX
		pUserData->m_Pierce.d1 += 80;
		CountphysicalDamage(dam, UserID, TargetID, 0);
		pUserData->m_Pierce.d1 -= 80;
		break;
	case 3034://��Ѫ
		pUserData->m_Pierce.d1 += 5;
		CountphysicalDamage(dam, UserID, TargetID, 50);
		pUserData->m_Pierce.d1 -= 5;
		break;
	case 3042://��Ѫ2
	case 3044://��ѪEX
		pUserData->m_Pierce.d1 += 5;
		CountphysicalDamage(dam, UserID, TargetID, 0);
		pUserData->m_Pierce.d1 -= 5;
		break;
	case 147://����
		buf.times = 8;
		break;
	case 1007://Ǭ����

	{
		cObj* target = g_pMainState->m_FightList[TargetID].m_pData;
		string targetname = target->m_TrueName.GetString();
		if (0 == targetname.compare(g_pMainState->m_taskSM.m_Npc.m_name))
		{
			cPetData* pData;
			target->GetDateP(pData);
			if (pData->m_HP < (pData->m_HPMax.GetData()) / 2)
			{
				if (rand() % 3 < 2)
				{
					dam = pData->m_HP;
					AddHp(TargetID, -dam);
					SetDamage(dam, TargetID);
					g_pMainState->m_taskSM.m_bXiangFuSuccess = TRUE;
				}
			}

		}
	}
	break;
	case 0://��ɨǧ��
	{
		int damageup;
		switch (pUserList->m_NowTarget)
		{
		case 0:
			damageup = 0;
			break;
		case 1:// �����߹���-Ŀ����� 120%���˺�
			damageup = 5;
			break;
		case 2:// �����߹���-Ŀ�����  ����10%�Ĳ���  150%���˺�
			damageup = 10;
			break;
		default:
			damageup = 15;
			break;
		}
		CountphysicalDamage(dam, UserID, TargetID, damageup);
	}
	break;
	case 1: // ��
		SetDateBuffUp(TargetID, UserID, sSkillID, buf, Skilllv);
		buf.times = -999;
		break;
	case 7: // �Ƹ�
	{
		CountphysicalDamage(dam, UserID, TargetID, -95);
	}
	break;
	case 1017:// �Ƹ�?????????????????
		CountphysicalDamage(dam, UserID, TargetID, 60);
		break;
	case 8://�����
		buf.times = 8;
		break;
	case 1010: // ��
	{
		CountphysicalDamage(dam, UserID, TargetID, 150);
		pUser->ReMoveStateID(1);
	}
	break;
	case 4://ɱ����
		buf.times = 8;
		break;
	case 11://������
	case 28://���׷�
	{
		pUserData->ghostSpecial.d1 += 100;
		int dadd = pUserData->m_DEF.GetData() >> 4;
		pUserData->m_Wakan.AddDataOriginal(dadd);
		CountMagicDamage(dam, UserID, TargetID, 20/*20 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 5,eMWX��*/);
		pUserData->ghostSpecial.d1 -= 100;
		pUserData->m_Wakan.AddDataOriginal(-dadd);
	}
	break;
	case 13:
	{
		m_pFightState->m_pList[UserID]->isLive = FALSE;
		if (UserID == g_pMainState->m_HeroID)
			m_pFightState->m_bEscape = TRUE;
	}
	break;
	case 6: //�����
	case 14://���߷�
	case 15://ʧ�ķ�
	case 17://ʧ��
	case 18://׷��
	case 19://���
	case 20://ʧ��
	case 21://����
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 16://����
		buf.times = 2;
		buf.times += (Skilllv - targetlv) / 10;
	case 22://��Ԫ��
		dam = Skilllv * 2 + 100;
		CorrectCureHP(dam, UserID, UserID);//��������
		SetDamage(-dam, TargetID);
		break;
	case 23://������
		SetDamage(-20, TargetID);
		CorrectCureMP(dam = Skilllv * 2, UserID, UserID);//��������
//		AddMp(TargetID, (Skilllv + 30));
		break;
	case 26://������
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 27://��׷�
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 31://��������

	{
		int dadd = pUserData->m_DEF.GetData() >> 4;
		pUserData->m_Wakan.AddDataOriginal(dadd);
		CountMagicDamage(dam, UserID, TargetID, 20/*15 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4*/);
		pUserData->m_Wakan.AddDataOriginal(-dadd);
	}
	break;
	case 33:  //��ջ���

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 34:    //Τ�ӻ���  
	case 35:  //��ջ���
	case 36:     //һέ�ɽ�

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	}
	case 37:     //�ҷ�ȱ�
		Resurgence(TargetID);
		AddHpHurt(TargetID, (Skilllv * 12));
		dam = (Skilllv * 10);
		CorrectCureHP(dam, UserID, TargetID);//��������
		break;
	case 38:     //����
		dam = Skilllv * 12;
		AddHpHurt(TargetID, dam);
		CorrectCureHP(dam, UserID, TargetID);//��������

		break;
	case 39:    //��Ѫ
		dam = Skilllv * 12;
		CorrectCureHP(dam, UserID, TargetID);//��������

		break;
	case 40:    //��������
		dam = Skilllv * 8;
		CorrectCureHP(dam, UserID, TargetID);//��������
		break;
	case 41:    //���ֻش�
		AddHpHurt(TargetID, (Skilllv * 8));
		break;
	case 42:    //��������
		AddHpHurt(TargetID, dam = Skilllv * 8);
		CorrectCureHP(dam, UserID, TargetID);//��������
		break;
	case 43://�ⶾ
		pTarget->ReMoveState(eBuffType��);
		dam = Skilllv * 3;
		//		AddHpHurt(TargetID, dam);
		CorrectCureHP(dam, UserID, TargetID);//��������
		break;
	case 45://����
		AddHpHurt(TargetID, 100, (1 << 14));
		dam = -AddHp(TargetID, 100, (1 << 14));
		SetDamage(dam, TargetID);
		break;
	case 46:    //���ޱ�

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 49:    //��������

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 54:    //��������

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 59:    //һЦ���

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 63:    //���񻤷�

	{
		buf.times = 5;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 66:	//����
		pUser->ReMoveState(eBuffType����);
		break;
	case 67:    //���� 

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 68:    //����
	case 69:    //�������

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 71://����ն
	case 98:
	{
		int dadd = pUserData->m_DEF.GetData() >> 3;
		pUserData->m_ATK.AddDataOriginal(dadd);
		CountphysicalDamage(dam, UserID, TargetID);
		pUserData->m_ATK.AddDataOriginal(-dadd);
	}
	break;
	case 72://���׺䶥

	{
		int rate = (pUserData->m_XiuLian.GetMag() - pTargetData->m_XiuLian.GetDMag())/**2*/;
		int offset = Skilllv - pTargetData->m_LV;
		rate = 70 + rate + offset;
		if (rand() % 100 < rate)
			dam = pTargetData->m_HP / 4;
		else dam = pTargetData->m_HP / 20;
		if (dam > (pUserData->m_LV * 50))dam = pUserData->m_LV * 50;
		AddHp(TargetID, -dam);
		SetDamage(dam, TargetID);
	}
	break;
	case 74://�������
	{
		int dadd = pUserData->m_DEF.GetData() >> 4;
		pUserData->m_Wakan.AddDataOriginal(dadd);
		CountMagicDamage(dam, UserID, TargetID, 25/*20 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 8,eMWX��*/);
		pUserData->m_Wakan.AddDataOriginal(-dadd);
	}
	break;
	case 119://������
	case 77: //���

	{
		m_pFightState->ReMoveSealState(TargetID);
	}
	break;
	case 79://����
		CountMagicDamage(dam, UserID, TargetID, 25/*40 + Skilllv / 5*/, eMWXˮ);
		break;
	case 80://�������
		CountMagicDamage(dam, UserID, TargetID, 20/*25 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4,eMWX��ˮ*/);
		break;
	case 81://����
		buf.times = 8;
		break;
	case 84: //����
		dam = Skilllv + 10;
		CountMagic2Damage(dam, UserID, TargetID/*, eMWXˮ*/);
		AddMp(TargetID, -dam);
		break;
	case 88://����
		CountMagicDamage(dam, UserID, TargetID, 30/*30 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4,eMWXˮ*/);
		break;
	case 89://����Ǭ��

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 90: //��������

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		dam = Skilllv;
		CorrectCureMP(dam, UserID, TargetID);
		buf.damage = dam;
		SetDamage(30, UserID);
	}
	break;
	case 91://����֮Ȫ

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		dam = Skilllv * 2 + 120;
		CorrectCureHP(dam, UserID, TargetID);//��������
		buf.damage = dam;
	}
	break;
	case 94:   //�����۶�
		dam = (Skilllv * 4 + 50);
		CorrectCureMP(dam, UserID, TargetID);
		//		SetDamage(30, UserID);
		break;
	case 97: //����
	{
		int dadd = pUserData->m_DEF.GetData() >> 3;
		pUserData->m_ATK.AddDataOriginal(dadd);
		CountphysicalDamage(dam, UserID, TargetID);
		pUserData->m_ATK.AddDataOriginal(-dadd);
	}
	break;
	case 102://�ն�����
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		dam = Skilllv * 5;
		buf.damage = dam;
		buf.damage2 = dam;
		AddHpHurt(TargetID, dam);
		CorrectCureHP(dam, UserID, TargetID);//��������
		break;
	case 103://������
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		buf.damage = (Skilllv * 3 + pTargetData->m_HPMax.GetData() / 20) * (100 + pUserData->m_DamageAddPercentMagic.d1) / 100;
		if (buf.damage > pUserData->m_LV * 15)
		{
			buf.damage = pUserData->m_LV * 15;
		}
		break;
	case 104://������¶
		Resurgence(TargetID);
		dam = Skilllv * Skilllv / 144 + Skilllv * 5;
		dam *= 2;
		AddHpHurt(TargetID, dam);
		CorrectCureHP(dam, UserID, TargetID);//��������
		break;
	case	105:// �չ⻪
		dam = (Skilllv * 4 + 100) * 13 / 10 * (23 - g_pMainState->m_FightList[UserID].m_MaxTargetNum) / 20;
		CountMagic2Damage(dam, UserID, TargetID, eMWX��);
		break;
	case	106:// ��׺�
		dam = (Skilllv * 4 + 100) * 13 / 10 * (23 - g_pMainState->m_FightList[UserID].m_MaxTargetNum) / 20;
		CountMagic2Damage(dam, UserID, TargetID, eMWXˮ);
		if (rand() % 20 == 0)
		{
			m_pFightState->m_pList[TargetID]->m_WorkType = -1;
		}
		break;
	case	107:// ������
		dam = (Skilllv * 4 + 100) * 13 / 10 * (23 - g_pMainState->m_FightList[UserID].m_MaxTargetNum) / 20;
		CountMagic2Damage(dam, UserID, TargetID, eMWX��);
		if (rand() % 8 == 0)
		{
			AddCp(TargetID, -dam / 30);
		}
		break;
	case	108:// ��ã��
		dam = (Skilllv * 4 + 100) * 13 / 10 * (23 - g_pMainState->m_FightList[UserID].m_MaxTargetNum) / 20;
		CountMagic2Damage(dam, UserID, TargetID);
		if (rand() % 10 == 0)
		{
			AddMp(UserID, -dam / 10);
		}
		break;
	case	109:// ���ѻ�
		dam = (Skilllv * 4 + 100) * 13 / 10 * (23 - g_pMainState->m_FightList[UserID].m_MaxTargetNum) / 20;
		CountMagic2Damage(dam, UserID, TargetID, eMWX��);
		if (rand() % 20 == 0)
		{
			AddHpHurt(TargetID, -dam / 10);
		}
		break;
	case 112://�鶯
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 113://���еߵ�
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 115://�����ķ�
		if (pTarget->m_StateList.size())
		{
			int d = 0;
			for (list<sBuff>::iterator Iterator = pTarget->m_StateList.begin(); Iterator != pTarget->m_StateList.end();)
			{
				// 				if (Iterator->ID == 102 || Iterator->ID == 91)
				// 				{
				// 					list<sBuff>::iterator it2 = Iterator;
				// 					Iterator++;
				// 					if (Iterator->ID == 91)
				// 					{
				// 						int hpadd = it2->damage2*it2->times;
				// 						AddHpHurt(TargetID, hpadd);
				// 					}
				// 					dam = -it2->damage*it2->times;
				// 					AddHp(TargetID, -dam);
				// 					g_pMainState->m_SkillManager.SetDateBuffDown(it2);// it2->targetID, it2->ID);
				// 					it2->data.Free();
				// 					pTarget->m_StateList.erase(it2);
				// 					break;
				// 				}
				// 				else 
				if (Iterator->ID == 102)
				{
					int mpadd = Iterator->times;
					if (mpadd <= 1)
					{
						mpadd *= Iterator->damage * 2;
					}
					else
					{
						mpadd *= Iterator->damage * 5 / 4;
					}

					if (mpadd > d) d = mpadd;
					g_pMainState->m_SkillManager.SetDateBuffDown(Iterator);// it2->targetID, it2->ID);
					Iterator->data.Free();
					pTarget->m_StateList.erase(Iterator++);
				}
				else
				{
					++Iterator;
				}
			}
			if (d > 0)
			{
				AddHpHurt(TargetID, d);
				AddHp(TargetID, d);
				SetDamage(-d, TargetID);
			}

		}
		break;
	case 116://������
		dam = (Skilllv * 3 / 2 + 30) * 13 / 10 * 2;
		CountMagic2Damage(dam, UserID, TargetID);
		AddHpHurt(TargetID, -(Skilllv * 3 / 2 + 30));
		break;
	case 117://�й���
		dam = (Skilllv * 3 + 75) * 13 / 10 * 3 / 2;
		CountMagic2Damage(dam, UserID, TargetID);
		AddMp(TargetID, -(Skilllv * 3 + 75));
		break;
	case 120://����
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 122://ʬ����
	{
		if (pTarget->CheckHaveState(sSkillID))return;
		if (pTargetData->m_race == 5 || pTargetData->m_race == 6 || pTargetData->m_race >= 1000)return;//��е�͹����ж�
// 			int Poision = pUserData->poisonRate.d1 - pUserData->poisonRate .d2 + 80; //�ж���
// 			if (rand() % 100 < Poision)
		{
			sBuff buf;
			buf.damage = pUserData->m_DamageAddPercentPoision.d1 - pTargetData->m_DamageAddPercentPoision.d2;//�ж��˺�����
			buf.times = 3 + (Skilllv - targetlv) / 25;
			SetDateBuffUp(UserID, TargetID, sSkillID, buf);
			buf.times = -999;
			dam = pTargetData->m_HP / 10 + Skilllv;
			if (dam > userlv * 15)
			{
				dam = userlv * 15;
			}
			AddHp(TargetID, -dam);
			SetDamage(dam, TargetID);

			cPetData* pPet;
			int randstart, randend;
			if (UserID < 10)randstart = 0; else randstart = 10;
			randend = randstart + 10;
			for (int i = randstart; i < randend; i++)
			{
				sFightList& list = g_pMainState->m_FightList[i];
				if (!list.isLive)continue;
				list.m_pData->GetDateP(pPet);

				if (pPet->m_HP < 1)continue;
				int d = dam * 4 / 5;
				if (d > Skilllv * 5 + 180)
				{
					d = Skilllv * 5 + 180;
				}
				AddHp(i, d);
				SetDamage(-d, i);
			}
		}
	}
	break;
	case 123:   //��������
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 125:
		Resurgence(TargetID);
		AddHpHurt(TargetID, Skilllv * 10);
		dam = Skilllv * 9;
		//		AddHp(TargetID, dam);
		CorrectCureHP(dam, UserID, TargetID);//��������
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 126:
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 127:// �����ɢ
		pTarget->ReMoveState(eBuffType����);
		break;
	case 129:
		buf.times = 5;
		buf.times += (Skilllv - targetlv) / 25;
		// ������
		break;
	case 131://��ɰ��ʯ
		CountMagicDamage(dam, UserID, TargetID, 30/*25 + Skilllv / 4 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4, eMWX��*/);
		break;
	case	132:// �������
		CountMagicDamage(dam, UserID, TargetID, 35/*70 + Skilllv / 4, eMWX��*/);
		break;
	case 133://ţ��
		buf.times = 8;
		break;
	case 141://����
		CountphysicalDamage(dam, UserID, TargetID, 50);
		pUser->ReMoveStateID(145);//ȡ������
		buf.times = 1;
		SetDateBuffUp(UserID, TargetID, sSkillID, buf);
		buf.times = -999;
		break;
	case 142://ӥ�� 
		CountphysicalDamage(dam, UserID, TargetID, 5);
		// 		if (pUserList->m_NowTarget == 0/*pUserList->m_MaxTargetNum - 1*/)
		// 		{
		// 			buf.times = 1;
		// 			SetDateBuffUp(UserID, UserID, sSkillID, buf);
		// 		}
		// 		buf.times = -999;
		break;
	case 143:// ʨ��
		CountphysicalDamage(dam, UserID, TargetID, 160);
		break;
	case	144:// ����
		buf.times = 5;
		buf.times += (Skilllv - targetlv) / 25;
		break;
	case 145://����
		buf.times = 5;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 148:// ������
		CountphysicalDamage(dam, UserID, TargetID, 15 - pUserData->m_FightProperty.AttackNum * 5);
		// 		if (pUserList->m_NowTarget == 0)
		// 		{
		//  			buf.times = 1;
		//  			SetDateBuffUp(UserID, UserID, sSkillID, buf);
		//  			buf.times = -999;
		// 			pUser->ReMoveStateID(145);//ȡ������
		// 			buf.times = 1;
		// 			SetDateBuffUp(UserID, TargetID, sSkillID, buf);
		// 			buf.times = -999;
		// 		}
		break;
	case 150://���ȷ��
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 152:
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 154://����
	{
		dam = pTargetData->m_HPMax.GetData() / 20;
		dam += Skilllv * 3;
		dam = dam * (100 - pTargetData->m_DamageAddPercentMagic2.d2) / 100;
		if (dam > userlv * 20)
		{
			dam = userlv * 20;
		}
		AddHp(TargetID, -dam);
		SetDamage(dam, TargetID);
		CorrectCureHP(dam, UserID, UserID);//��������
	}
	break;
	case 155://����
// 		dam = -AddMp(TargetID, -5, userlv * 100);
// 		dam += -AddMp(TargetID, -Skilllv * 2);
		dam = pTargetData->m_MPMax.GetData() / 20;
		dam += Skilllv * 3;
		// 		if (dam > userlv * 5)
		// 		{
		// 			dam = userlv * 5;
		// 		}

		AddMp(TargetID, -dam);
		//		dam /= 2;
		CorrectCureMP(dam, UserID, UserID);//��������
		dam = 0;
		break;
	case 156://ħ�����
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 159://��������
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 160:// ��˿��
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 161: //����
		m_pFightState->ReMoveSealState(UserID);
		m_pFightState->ReMoveDeBuffState(UserID);
		m_pFightState->ReMovePoisionState(UserID);
		break;
	case 162:  //���޵���
		dam = Skilllv * 2 + (pUserData->m_ATK.GetData() / 5);
		dam = dam * 5 / 3;
		CountMagic2Damage(dam, UserID, TargetID);
		if (rand() % 100 < 10)
		{
			buf.times = rand() % 3 + 1;
		}
		break;
	case 164://����ͬ��
		dam = AddMp(TargetID, -10, userlv * 100);
		dam += AddMp(TargetID, Skilllv * 5);
		dam = 0;
		break;
	case 166://�þ���
		buf.times = 3;
		buf.times += (Skilllv - userlv) / 5;
		break;
	case 1001://ץ��

	{
		if (!pTargetData->m_Controler.CheckGrab())
		{
			g_pMainState->m_Channel.AddNewString("�ö����޷�ץ��");
			return;
		}
		cCharacter* pc1 = (cCharacter*)pUser->m_pIndex;
		if (pc1->m_PCData.m_NumofBB > 7)
		{
			g_pMainState->m_Tags.Add("�ٻ��������ﵽ����");
			break;
		}
		if ((rand() % 100) > 50)
		{

			m_pFightState->BackFromFight(TargetID);
			cPet* pPet = (cPet*)pTarget->m_pIndex;
			pc1->m_PCData.GetPet(pPet);
			pTarget->m_pIndex = 0;
			pTarget->m_IndexType = 0;
		}
	}
	break;
	case 2084:  //�׻�
		CountMagicDamage(dam, UserID, TargetID, 20, eMWX��);
		break;
	case 2085://������
		CountMagicDamage(dam, UserID, TargetID, 20/*35 - pUserList->m_NowTarget * 5*/, eMWX��);
		break;
	case 2086: //����
		CountMagicDamage(dam, UserID, TargetID, 20, eMWX��);
		if (rand() % 5 == 0)
		{
			AddCp(TargetID, -20);
		}
		break;
	case 2087: //̩ɽѹ��
		CountMagicDamage(dam, UserID, TargetID, 20/*30 - pUserList->m_NowTarget * 5*/, eMWX��);
		if (rand() % 10 == 0)
		{
			AddCp(TargetID, -20);
		}
		break;
	case 2088: //ˮ��
		CountMagicDamage(dam, UserID, TargetID, 20, eMWXˮ);
		if (rand() % 15 == 0)
		{
			m_pFightState->m_pList[TargetID]->m_WorkType = -1;
		}
		break;
	case 2089: //ˮ����ɽ
		CountMagicDamage(dam, UserID, TargetID, 20/*30 - pUserList->m_NowTarget * 5*/, eMWXˮ);
		if (rand() % 30 == 0)
		{
			m_pFightState->m_pList[TargetID]->m_WorkType = -1;
		}
		break;
	case 2090: //�һ�
		CountMagicDamage(dam, UserID, TargetID, 20, eMWX��);
		if (rand() % 10 == 0)
		{
			AddHpHurt(TargetID, -dam / 10);
		}
		break;
	case 2091: //�����һ�
		CountMagicDamage(dam, UserID, TargetID, 20/*30 - pUserList->m_NowTarget * 5*/, eMWX��);
		if (rand() % 20 == 0)
		{
			AddHpHurt(TargetID, -dam / 10);
		}
		break;
	case 2092://����һ��
		CountphysicalDamage(dam, UserID, TargetID/*, -10*/);
		AddMp(TargetID, -dam / 4 - userlv / 3);
		buf.times = 1;
		break;
	case 2094://�����ٻ�
		CountphysicalDamage(dam, UserID, TargetID);
		if (rand() % 100 < 15)
			buf.times = 10;
		break;
	case 2093://ҹ�����
		buf.times = 3;
		dam = pUserData->m_ProPertyAtk * 3 / 2 + pUserData->m_SPD.GetData() / 3;
		AddHp(TargetID, -dam);
		SetDamage(dam, TargetID);
		break;
	case 2095://������ɽ
		SetDateBuffUp(UserID, UserID, sSkillID, buf, Skilllv);
		buf.times = -999;
		break;
	case 2096: //�����ķ�
		CountphysicalDamage(dam, UserID, TargetID, -35);
		break;
	case 2097:// ��������
		buf.times = 6;
		break;
	case 2098://�ƶ��б�
		CountphysicalDamage(dam, UserID, TargetID, 10088);
		break;
	case 2099://���ݻ���
		CountphysicalDamage(dam, UserID, TargetID, 10087);
		break;
	case 2100://���ŭ��
		CountphysicalDamage(dam, UserID, TargetID, 100);
		break;
	case 2105: //�¹�
		pUserData->m_DamageAddPercentMagic.d1 -= pUserData->m_FightProperty.AttackNum * 20;
		//		pUserData->m_MagicCriRate.d1 -= pUserData->m_FightProperty.AttackNum * 5;
		CountMagicDamage(dam, UserID, TargetID, 35);
		pUserData->m_DamageAddPercentMagic.d1 += pUserData->m_FightProperty.AttackNum * 20;
		//		pUserData->m_MagicCriRate.d1 += pUserData->m_FightProperty.AttackNum * 5;
		break;
	case 3000: //����
	{
		dam = CountHPPercent(pTargetData, 3, userlv);
		dam += 200;
		CorrectCureHP(dam, UserID, TargetID);//��������
	}
	break;
	case 3001: //����

	{
		dam = CountHPPercent(pTargetData, 6, userlv);
		dam += 400;
		CorrectCureHP(dam, UserID, TargetID);//��������
	}
	break;
	case 3002: //����

	{
		dam = CountHPPercent(pTargetData, 9, userlv);
		dam += 600;
		CorrectCureHP(dam, UserID, TargetID);//��������
	}
	break;
	case 3003: //����

	{
		dam = CountMPPercent(pTargetData, 10, userlv);
		dam += 240;
		CorrectCureMP(dam, UserID, TargetID);//��������
	}
	break;
	case 3004:  //����

	{
		dam = CountMPPercent(pTargetData, 15, userlv);
		dam += 240;
		CorrectCureMP(dam, UserID, TargetID);//��������
	}
	break;
	case 3006: //����
		dam = CountHPPercent(pTargetData, 50, userlv);
		CorrectCureHP(dam, UserID, TargetID);//��������
		break;
	case 3005:  //����
	case 3007: //�ĺ���ƽ
		dam = CountHPPercent(pTargetData, 30, userlv / 2);
		CorrectCureHP(dam, UserID, TargetID);//��������
		break;
	case 3008://�ػ���
		Resurgence(TargetID);
		dam = CountHPPercent(pTargetData, 20, userlv);
		CorrectCureHP(dam, UserID, TargetID);//��������
		AddHpHurt(TargetID, dam);
		break;
	case 3009: //��������
		Resurgence(TargetID);
		dam = CountHPPercent(pTargetData, 50, userlv);
		CorrectCureHP(dam, UserID, TargetID);//��������
		AddHpHurt(TargetID, dam);
		break;
	case 3012://����
	case 3010://ˮ��
		pTarget->ReMoveState(eBuffType��ӡ);
		pTarget->ReMoveState(eBuffType��);
		pTarget->ReMoveState(eBuffType����);
		break;
	case 3011://����
	case 3013://����
		dam = CountHPPercent(pTargetData, 20, userlv / 2);
		CorrectCureHP(dam, UserID, TargetID);//��������
		pTarget->ReMoveState(eBuffType��ӡ);
		pTarget->ReMoveState(eBuffType��);
		pTarget->ReMoveState(eBuffType����);
		break;
	case 3016://Ц��ص�
		AddCp(TargetID, -70);
		break;
	case 3017://����ħ��
		AddCp(TargetID, -30);
		break;
	case 3018://Ұ��	
		if (!(pTargetData->m_FightProperty.m_AtkIntensify && 2))
			pTargetData->m_ATK.AddDataAddPercent(10);
		break;
	case 3019://ħ��֮ӡ
		if (!(pTargetData->m_FightProperty.m_AtkIntensify && 1))
			pTargetData->m_ATK.AddDataAddPercent(5);
		break;
	case 3020://���
		if (!(pTargetData->m_FightProperty.m_DefIntensify && 2))
			pTargetData->m_DEF.AddDataAddPercent(10);
		break;
	case 3021://ʥ��
		if (!(pTargetData->m_FightProperty.m_DefIntensify && 1))
			pTargetData->m_DEF.AddDataAddPercent(5);
		break;
	case 3022://����
		if (!(pTargetData->m_FightProperty.m_SpdIntensify && 2))
			pTargetData->m_SPD.AddDataAddPercent(10);
		break;
	case 3023://Х��
		if (!(pTargetData->m_FightProperty.m_SpdIntensify && 1))
			pTargetData->m_SPD.AddDataAddPercent(5);
		break;
	case 3024://̫������
		buf.times = 4;
		break;
	case 3025://�޺�����
		buf.times = 4;
		break;
	case 3026://������
		buf.times = 4;
		break;
	case 3027://�����޷�
		buf.times = 4;
		break;
	case 3028://��������
		if (!(pTargetData->m_FightProperty.m_AtkIntensify && 8))
		{
			pTargetData->m_FightProperty.m_AtkIntensify += 8;
			pTargetData->m_ATK.AddDataAddPercent(-10);
		}
		break;
	case 3029://��ɽѹ��
		if (!(pTargetData->m_FightProperty.m_AtkIntensify && 4))
		{
			pTargetData->m_FightProperty.m_AtkIntensify += 4;
			pTargetData->m_ATK.AddDataAddPercent(-5);
		}
		break;
	case 3030://�Ƽ���
		if (!(pTargetData->m_FightProperty.m_DefIntensify && 8))
		{
			pTargetData->m_FightProperty.m_DefIntensify += 8;
			pTargetData->m_DEF.AddDataAddPercent(-10);
		}
		break;
	case 3031://�����
		if (!(pTargetData->m_FightProperty.m_DefIntensify && 4))
		{
			pTargetData->m_FightProperty.m_DefIntensify += 4;
			pTargetData->m_DEF.AddDataAddPercent(-5);
		}
		break;
	case 3032://������
		if (!(pTargetData->m_FightProperty.m_SpdIntensify && 8))
		{
			pTargetData->m_FightProperty.m_SpdIntensify += 8;
			pTargetData->m_SPD.AddDataAddPercent(-10);
		}
		break;
	case 3033://ͣ����
		if (!(pTargetData->m_FightProperty.m_SpdIntensify && 4))
			pTargetData->m_SPD.AddDataAddPercent(-5);
		break;
	case 3038://�Ǳ�ʥ��
		pTargetData->m_FightProperty.m_WallNum = 2;
		break;
	case 3039://������EX

	{
		dam = CountHPPercent(pTargetData, 50, userlv);
		dam += 1000;
		CorrectCureHP(dam, UserID, TargetID);//��������
	}
	break;
	case 3046://���֮ǽ
		pTargetData->m_FightProperty.m_WallNum = 1;
		break;
	case 3047://��������
		buf.times = 5;
		break;
	case 3048://�Ⱥ��ն�
		Resurgence(TargetID);
		dam = CountHPPercent(pTargetData, 100, userlv << 3);
		AddHpHurt(TargetID, 100, 10000);
		CorrectCureHP(dam, UserID, TargetID);//��������
		pTarget->ReMoveState(eBuffType��ӡ);
		pTarget->ReMoveState(eBuffType��);
		pTarget->ReMoveState(eBuffType����);
		// 		Resurgence(TargetID);
		// 		dam = CountHPPercent(pTargetData, 50, userlv);
		// 		CorrectCureHP(dam, UserID, TargetID);//��������
		// 		AddHpHurt(TargetID, dam);

		break;
	case 3049://Ѹ�����
		buf.times = 5;
		break;
	case 2102:
		CountParry(pUserData, pTargetData);//��
		CountCri(pUserData, pTargetData);//��ɱ
		CountphysicalDamage(dam, UserID, TargetID, 80);
		break;
	default:
		ERRBOX2(sSkillID);
		return;
	}
	if (buf.times != -999)
	{
		if (buf.times < 1)buf.times = 1;
		if (buf.times > 1)
		{
			if (UserID < 10 && TargetID < 10)
				buf.times += pTargetData->buffAdd;
			else
				if (TargetID > 9 && UserID > 10)
					buf.times += pTargetData->buffAdd;
		}
		SetDateBuffUp(UserID, TargetID, sSkillID, buf, Skilllv);
	}
}


BOOL cSkillManager::CheckMagicHit(int Skilllv, int sSkillID, int UserID, int TargetID)
{//����������
	cPetData* pUserData;
	cPetData* pTargetData;
	g_pMainState->m_FightList[UserID].m_pData->GetDateP(pUserData);
	g_pMainState->m_FightList[TargetID].m_pData->GetDateP(pTargetData);
	if (abs(UserID - TargetID) >= 10 && pUserData->PeopleSpecial.d1 - pTargetData->PeopleSpecial.d2 < 0)
	{
		return FALSE;
	}

	int rate = 0;
	auto func = [&]()
	{
		if (pTargetData->m_race >= 1000)
		{
			rate -= 999;
		}
		else
		{
			if (!Skilllv)
			{
				Skilllv = pUserData->m_LV;
			}
			rate += (pUserData->m_XiuLian.GetMag() - pTargetData->m_XiuLian.GetDMag());
			//��ӡ��������
			rate += pUserData->m_SealRate.d1 - pTargetData->m_SealRate.d2 + ((Skilllv - pTargetData->m_LV) >> 1);
		}
	};
	switch (sSkillID)
	{
		//�ٻ��޷���
	case 2084:
	case 2085:
	case 2086:
	case 2087:
	case 2088:
	case 2089:
	case 2090:
	case 2091:
		// ���׷�
	case 28:
		// ��������
	case 31:
		// �������
	case 74:
		//���η���
	case 105:
	case 106:
	case 107:
	case 108:
	case 109:
		// �����й�
	case 116:
	case 117:
		//ħ��
	case 131:
	case 132:
		// ���޵���
	case 162:
		rate += 100;
		//����������
		rate += pUserData->m_MagicHitRate.d1 - pTargetData->m_MagicHitRate.d2;
		break;
		//����
	case 6:
		rate += 50;
		func();
		break;
		//����
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
		rate += 50;
		func();
		break;
		//Ů��
	case 54:rate += 50; func(); break;//��������
	case 59:rate += 30; func(); break;
		//�칬
	case 67:rate += 50; func(); break;
	case 68:rate += 50; func(); break;
	case 69:rate += 50; func(); break;
		//��ׯ
	case 89:rate += 50; func(); break;
		//�ظ�
	case 122:rate += 85; func(); break;
	case 127:rate += 75; func(); break;
	case 129:rate += 35; func(); break;
		//ST
	case 144:rate += 50; func(); break;
		//PS
	case 154:rate += 95; func(); break; // ����
	case 155:rate += 95; func(); break; // ����
	case 156:rate += 50; func(); break; // ħ��
	case 159:rate += 50; func(); break; // ����
	case 164:rate += 50; func(); break; // ����
// 		if (pUserData->m_Popularity - pTargetData->m_Popularity >= 50)
// 		{
// 			rate += (pUserData->m_Popularity - pTargetData->m_Popularity) / 50;
// 		}
		break;
		// ���ֻ�����
	case 3:  //����   
	case 25: //����ɽ
	case 44: //������
	case 58: //Ů����
	case 70: //�칬
	case 83: //����
	case 93: //��ׯ��
	case 110: //����
	case 124: //�ظ�
	case 138: //ħ��
	case 149: //ʨ��
	case 163: //��˿��
	case 180: //�貨��
	case 192: //�޵׶�
	case 201: //Ҷ��
		rate = 60 + (Skilllv >> 1);
		break;
	default:
		return TRUE;
	}
	return (rand() % 100) < rate;
}



void cMengPaiManager::lvUpMainSkill(cPCData& pcDate, int lv, int ID, bool isHero /* = false */)
{
	if (ID > 7 || ID < 0)return;
	if (pcDate.m_MengPaiID < 0 || pcDate.m_MengPaiID>11)return;
	cZhuJiNeng* pZhuJiNeng = &m_MengPai[pcDate.m_MengPaiID].m_MainSkill[ID];
	int& skilllv = pcDate.m_MengPaiSkillLV[ID];
	int prelv = skilllv;
	int nextlv = prelv + lv;
	if (!ID && !isHero)
	{
		switch (pcDate.m_MengPaiID)
		{
		case 0://����
			//		switch (ID)
			//		{
			// 		case 0:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 1:pcDate.AddSpdZZ(lv);break;
			// 		case 2:pcDate.AddHpZZ(7 * lv); break;
			// 		case 3:pcDate.AddAvoidZZ(lv); break;
			// 		case 4:
			// 			pcDate.AddGrowing(-prelv/10);
			// 			pcDate.AddGrowing(nextlv /10); 
			// 			break;
			// 		case 5:pcDate.AddDefZZ(3 * lv); break;
			// 		case 6:pcDate.AddMagZZ(2 * lv); break;
			//		}
// 			pcDate.m_Spurting.d1 -= prelv / 10;
// 			pcDate.m_Spurting.d1 += nextlv / 10;
			pcDate.m_Pierce.d1 -= prelv / 13;
			pcDate.m_Pierce.d1 += nextlv / 13;
			break;
		case 1://����
			//		switch (ID)
			//		{
			// 		case 0:pcDate.AddSpdZZ( lv); break;
			// 		case 1:pcDate.AddAtkZZ( lv); break;
			// 		case 2:pcDate.AddMagZZ(3 * lv); break;
			// 		case 3:
			// 			pcDate.AddGrowing(-prelv /10);
			// 			pcDate.AddGrowing(nextlv /10);
			// 			break;
			// 		case 4:pcDate.AddDefZZ(3 * lv); break;
			// 		case 5:pcDate.AddHpZZ(10 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ( lv); break;
			//		}

			pcDate.m_CureCriRate.d1 -= prelv / 10;
			pcDate.m_CureCriRate.d1 += nextlv / 10;
			break;
		case 2://Ů��
			//		switch (ID)
			//		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 1:pcDate.AddAvoidZZ(3 * lv); break;
			// 		case 2:pcDate.AddDefZZ(2 * lv); break;
			// 		case 3:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 4:
			// 			pcDate.AddHpZZ(5 * lv);
			pcDate.m_SPD.AddDataAddPercent(-prelv / 20);
			pcDate.m_SPD.AddDataAddPercent(nextlv / 20);
			// 			break;
			// 		case 5:pcDate.AddMagZZ(2 * lv); break;
			// 		case 6:pcDate.AddSpdZZ(3 * lv); break;
			//		}
			break;
		case 3://����
			// 		switch (ID)
			// 		{
			// 		case 0:pcDate.AddDefZZ(lv); break;
			// 		case 1:
			// 			pcDate.AddAtkZZ(lv); 
			pcDate.ghostSpecial.d1 -= prelv / 4;
			pcDate.ghostSpecial.d1 += nextlv / 4;
			// 			break;
			// 		case 2:
			// 			pcDate.AddMagZZ(lv); 
			pcDate.MonsterSpecial.d1 -= prelv / 4;
			pcDate.MonsterSpecial.d1 += nextlv / 4;
			// 			break;
			// 		case 3:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 4:pcDate.AddHpZZ(7 * lv); break;
			// 		case 5:pcDate.AddSpdZZ(2 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ(2 * lv); break;
			// 		}
			break;
		case 4:  //ʨ��
			// 		switch (ID)
			// 		{
			// 		case 0:pcDate.AddDefZZ(lv); break;
			// 		case 1:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 2:pcDate.AddHpZZ(10 * lv); break;
			// 		case 3:pcDate.AddMagZZ(3 * lv); break;
			// 		case 4:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 5:pcDate.AddAvoidZZ(lv); break;
			// 		case 6:pcDate.AddSpdZZ(lv); break;
			// 		}
			pcDate.m_SuckBloodRate.d1 -= prelv / 20;
			pcDate.m_SuckBloodRate.d1 += nextlv / 20;
			break;
		case 5://ħ��
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			pcDate.m_MagicCriRate.d1 -= prelv / 15;
			pcDate.m_MagicCriRate.d1 += nextlv / 15;
			// 			break;
			// 		case 1:pcDate.AddMagZZ(5 * lv); break;
			// 		case 2:
			// 			pcDate.AddSpdZZ(-prelv / 2);
			// 			pcDate.AddSpdZZ(nextlv/2); 
			pcDate.m_MagicFire.d2 -= prelv / 10;
			pcDate.m_MagicFire.d2 += nextlv / 10;
			// 			break;
			// 		case 3:
			// 			pcDate.AddAtkZZ(2 * lv); 
			pcDate.m_MagicFire.d1 -= prelv / 10;
			pcDate.m_MagicFire.d1 += nextlv / 10;
			// 			break;
			// 		case 4:
			// 			pcDate.AddHpZZ(9 * lv);
			// 			break;
			// 		case 5:
			// 			pcDate.AddDefZZ(lv);
			pcDate.m_CounterRate.d1 -= prelv / 5;
			pcDate.m_CounterRate.d1 += nextlv / 5;
			// 			break;
			// 		case 6:
			// 			pcDate.AddAvoidZZ(-prelv / 2);
			// 			pcDate.AddAvoidZZ(nextlv/2); 
			// 			break;
			// 		}
			break;
		case 6://��˿
			// 			switch (ID)
			// 			{
			// 			case 0:
			// 				pcDate.AddDefZZ(2* lv); 
			pcDate.m_HiddenWeaponDamagePercent.d2 -= prelv / 4;
			pcDate.m_HiddenWeaponDamagePercent.d2 += nextlv / 4;
			// 				break;
			// 			case 1: pcDate.AddMagZZ(4 * lv); break;
			// 			case 2:pcDate.AddHpZZ(7 * lv); break;
			// 			case 3:
			// 				pcDate.AddGrowing(-prelv / 10);
			// 				pcDate.AddGrowing(nextlv / 10);
			// 				break;
			// 			case 4:
			// 				pcDate.AddAtkZZ(3 * lv); break;	
			// 				break;
			// 			case 5:pcDate.AddAvoidZZ(3 * lv); break;
			// 			case 6:pcDate.AddSpdZZ(2* lv); break;
			// 			}
			break;
		case 7://�ظ�
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			pcDate.m_SealRate.d2 -= prelv / 10;
			pcDate.m_SealRate.d2 += nextlv / 10;
			// 			break;
			// 		case 1:pcDate.AddAtkZZ(3 * lv); break;
			// 		case 2:pcDate.AddSpdZZ(1 * lv); break;
			// 		case 3:
			// 			pcDate.AddHpZZ(10 * lv); 
//			pcDate.nightLv -= prelv / 10;
//			pcDate.nightLv += nextlv / 10;
			// 			break;
			// 		case 4:pcDate.AddMagZZ(3 * lv); break;
			// 		case 5:
			// 			pcDate.AddDefZZ( lv);
//			pcDate.poisonRate.d1 -= prelv / 10;//����
//			pcDate.poisonRate.d1 += nextlv / 10;//����
			// 			break;
			// 		case 6:pcDate.AddAvoidZZ(lv); break;
			// 		}

			pcDate.m_DamageAddPercentMagic2.d1 -= prelv / 10;
			pcDate.m_DamageAddPercentMagic2.d1 += nextlv / 10;
			break;
		case 8://����
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 1:
			// 			pcDate.AddMagZZ(5 * lv); 
			pcDate.m_MagicWater.d2 -= prelv / 10;
			pcDate.m_MagicWater.d2 += nextlv / 10;
			// 			break;
			// 		case 2:pcDate.AddHpZZ(5* lv); break;
			// 		case 3:
			// 			pcDate.AddAtkZZ(lv); 
			pcDate.m_MagicWater.d1 -= prelv / 10;
			pcDate.m_MagicWater.d1 += nextlv / 10;

			pcDate.m_PierceMagic.d1 -= prelv / 13;
			pcDate.m_PierceMagic.d1 += nextlv / 13;

			pcDate.m_MagicCriRate.d1 -= prelv / 40;
			pcDate.m_MagicCriRate.d1 += nextlv / 40;

			// 			break;		
			// 		case 4:pcDate.AddDefZZ(3 * lv); break;
			// 		case 5:pcDate.AddAvoidZZ(-prelv/2); 
			// 			pcDate.AddAvoidZZ(nextlv / 2); break;
			// 		case 6:pcDate.AddSpdZZ(-prelv/2); 
			// 			pcDate.AddSpdZZ(nextlv/ 2); break;
			// 		}
			break;
		case 9://��ׯ
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 1:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 2:pcDate.AddHpZZ(6 * lv); break;
			// 		case 3:pcDate.AddMagZZ(2 * lv); break;
			// 		case 4:pcDate.AddDefZZ(2 * lv); break;
			// 		case 5:pcDate.AddSpdZZ(2 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ(2 * lv); break;
			// 		}

			pcDate.m_ParryRate.d1 -= prelv / 10;
			pcDate.m_ParryRate.d1 += nextlv / 10;
			break;
		case 10://����
			// 		switch (ID)
			// 		{
			// 		case 0:pcDate.AddMagZZ(3 * lv); break;
			// 		case 1:pcDate.AddHpZZ(6 * lv); break;
			// 		case 2:pcDate.AddSpdZZ(lv); break;
			// 		case 3:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 4:pcDate.AddDefZZ(3 * lv); break;
			// 		case 5:
			// 			if (1)
		{
			//				pcDate.AddAtkZZ(lv);
			int data = prelv / 20;
			pcDate.m_MagicFire.d2 -= data; //��
			pcDate.m_MagicSoil.d2 -= data; //��
			pcDate.m_MagicWater.d2 -= data;  //ˮ
			pcDate.m_MagicThunder.d2 -= data;//��
			data = nextlv / 20;
			pcDate.m_MagicFire.d2 += data; //��
			pcDate.m_MagicSoil.d2 += data; //��
			pcDate.m_MagicWater.d2 += data;  //ˮ
			pcDate.m_MagicThunder.d2 += data;//��
		}

		pcDate.m_DamageAddPercentCure.d1 -= prelv / 10;
		pcDate.m_DamageAddPercentCure.d1 += nextlv / 10;

		// 			break;
		// 		case 6:pcDate.AddAvoidZZ(lv); break;
		// 		}
		break;
		case 11://�칬
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddAtkZZ(lv); 
			pcDate.MonsterSpecial.d1 -= prelv / 4;
			pcDate.MonsterSpecial.d1 += nextlv / 4;

			pcDate.m_HitRate.d2 -= prelv / 8;
			pcDate.m_HitRate.d2 += nextlv / 8;
			// 			break;
			// 		case 1:pcDate.AddHpZZ(6 * lv); break;
			// 		case 2:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 3:pcDate.AddDefZZ(2 * lv); break;
			// 		case 4:pcDate.AddMagZZ(2 * lv); break;
			// 		case 5:pcDate.AddSpdZZ(2 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ(2 * lv); break;
			// 		}
			break;
		default:
			ERRBOX;
			return;
		}
	}
	skilllv += lv;
	//	if (lv>0)
	for (int i = 0; i < pZhuJiNeng->m_NumSkillInclude; i++)
	{
		if (isHero || prelv < pZhuJiNeng->m_Limit[i])
			if (skilllv >= pZhuJiNeng->m_Limit[i])
			{
				//���ڼ��
				for (int j = 0; j < pcDate.m_SkillEnablelist.size(); j++)
				{
					if (pcDate.m_SkillEnablelist[j]->m_Id == pZhuJiNeng->m_SkillIncludeID[i])
						return;
				}
				sSkill* pSkill = &m_SkillList[pZhuJiNeng->m_SkillIncludeID[i]];
				pcDate.m_SkillEnablelist.push_back(pSkill);

			}
	}
}



BOOL cSkillManager::Use����СAI(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sFightList* pUserList = &g_pMainState->m_FightList[UserID];
	cObj* pUser = pUserList->m_pData;
	cPetData* pUserData;
	cPetData* pTargetData;
	pUser->GetDateP(pUserData);
	cObj* pTarget = g_pMainState->m_FightList[TargetID].m_pData;
	pTarget->GetDateP(pTargetData);
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:

	{
		int hpout = 0;
		Cost(hpout, Skilllv, sSkillID, UserID, 1, TRUE);
		if (hpout)
		{
			SetDamage(hpout, UserID);
		}
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		stage = 1;
	}
	return TRUE;
	case 1:
		if (WaitForMagicPoint(UserID) || pUser->m_pShowData[0]->m_isStatic)
		{
			pUser->SetStatic(FALSE);
			pUser->SetMagicSound(sSkillID);//����

			DWORD MagicID;
			int MagicPos;
			BOOL MagicUporDown;
			BOOL  toAll;
			BOOL bAtk;
			int maxnum;
			GetMagicAndNum(Skilllv, sSkillID, UserID, TargetID, MagicID, maxnum, MagicPos, MagicUporDown, toAll);
			int magicspeed = GetSpeed(sSkillID);
			bAtk = GetSkillAtk(sSkillID);
			pUserList->m_MaxTargetNum = 0;
			if (toAll)	m_pFightState->m_FullSkill.SetMagicUp(0, MagicID, 0, 0);

			auto func = [&](bool isCheckDie, cAttackAI::eEnemyType type, int stateid)
			{
				vector<POINT> tList;
				g_pMainState->m_AI.m_AttackAI.FindEnemy(isCheckDie, FALSE, tList, type, TargetID, stateid);
				if (!tList.size())tList.push_back({ TargetID, 0 });
				if (tList.size() < maxnum)maxnum = tList.size();
				int i = 0;
				for (; i < maxnum; ++i)
				{
					if (tList[i].x == TargetID)break;
				}
				if (i == maxnum)tList[maxnum - 1].x = TargetID;
				for (int i = 0; i < maxnum; ++i)
				{
					pUserList->targetlist[i] = tList[i].x;
				}
				pUserList->m_MaxTargetNum = maxnum;
			};

			auto func2 = [&](bool isCheckDie, cAttackAI::eEnemyType type, int stateid)
			{
				vector<POINT> tList;
				g_pMainState->m_AI.m_AttackAI.FindEnemy(isCheckDie, FALSE, tList, type, TargetID, stateid);
				auto list2 = g_pMainState->m_AI.m_AttackAI.check����(tList, UserID);
				if (!list2.size())list2.push_back(TargetID);
				if (list2.size() < maxnum)maxnum = list2.size();
				int i = 0;
				for (; i < maxnum; ++i)
				{
					if (list2[i] == TargetID)break;
				}
				if (i == maxnum)list2[maxnum - 1] = TargetID;
				for (int i = 0; i < maxnum; ++i)
				{
					pUserList->targetlist[i] = list2[i];
				}
				pUserList->m_MaxTargetNum = maxnum;
			};


			if (maxnum < 2)
			{
				pUserList->targetlist[0] = TargetID;
				pUserList->m_MaxTargetNum = 1;
			}
			else
				switch (sSkillID)
				{
				case 27: // ���
				{
					func2(true, cAttackAI::eET��ӡ����, 27);
					break;
				}
				// ��ջ���
				case 33:
					func(true, cAttackAI::eET�Ͻ��33, 33);
					break;
					// ��Ѫ 91PT�������Լ��� �Ǻ��� Ŷ��AI ���弼�ܲ����㣬�ұ��˫�����
					// �Ҽ��ؼ�
				case 38:
				case 39:
				case 40:
				case 41:
				case 42:
				case 45:
					//			case 94:
				case 3007:
				case 3013:
					func(true, cAttackAI::eETѪ����, -1);
					// 				{
					// 					vector<POINT> tList;
					// 					g_pMainState->m_AI.m_AttackAI.find������͵ļ���(FALSE,FALSE,tList, cAttackAI::eETѪ����, UserID);
					// 					if (tList.size() < maxnum)maxnum = tList.size();
					// 					int i = 0;
					// 					for (; i < maxnum; i++)
					// 					{
					// 						if (tList[i].x == TargetID)break;
					// 					}						
					// 					if (i == maxnum)tList[maxnum - 1].x = TargetID;
					// 					for (i = 0; i < maxnum; i++)
					// 					{
					// 						pUserList->targetlist[i] = tList[i].x;
					// 					}
					// 					pUserList->m_MaxTargetNum = maxnum;
					// 				}
					break;
				case 91:
				case 102:
					func(true, cAttackAI::eETѪ����, sSkillID);
					// 			{
					// 				vector<POINT> tList;
					// 				g_pMainState->m_AI.m_AttackAI.find������͵ļ���(FALSE, FALSE, tList, cAttackAI::eETѪ����, UserID, 102);
					// 				if (!tList.size())tList.push_back({ TargetID, 0 });
					// 				if (tList.size() < maxnum)maxnum = tList.size();
					// 				int i = 0;
					// 				for (; i < maxnum; i++)
					// 				{
					// 					if (tList[i].x == TargetID)break;
					// 				}
					// 				if (i == maxnum)tList[maxnum - 1].x = TargetID;
					// 				for (i = 0; i < maxnum; i++)
					// 				{
					// 					pUserList->targetlist[i] = tList[i].x;
					// 				}
					// 				pUserList->m_MaxTargetNum = maxnum;
					// 			}
					break;
				case 112: // �鶯����
					func(true, cAttackAI::eET���鶯112, 112);
					// 				{
					// 					vector<POINT> tList;
					// 					g_pMainState->m_AI.m_AttackAI.find������͵ļ���(false, FALSE, tList, cAttackAI::eET���鶯112, UserID, 112);
					// 					if (!tList.size())tList.push_back({ TargetID, 0 });
					// 					if (tList.size() < maxnum)maxnum = tList.size();
					// 					int i = 0;
					// 					for (; i < maxnum; i++)
					// 					{
					// 						if (tList[i].x == TargetID)break;
					// 					}
					// 					for (int i = 0; i < maxnum; i++)
					// 					{
					// 						pUserList->targetlist[i] = tList[i].x;
					// 					}
					// 					pUserList->m_MaxTargetNum = maxnum;
					// 				}
					break;
				case 120: // ����
					func(true, cAttackAI::eET����120, -1);
					// 			{
					// 				int num = 1;
					// 				int star = UserID >= 10 ? 10 : 0;
					// 				for (int i = star; i < star + 10; ++i)
					// 				{
					// 					if (i == TargetID)continue;
					// 					if (!g_pMainState->m_FightList[i].isExist)
					// 					{
					// 						continue;
					// 					}
					// 					cPetData *data = nullptr;
					// 					g_pMainState->m_FightList[i].m_pData->GetDateP(data);
					// 					if (!data)
					// 					{
					// 						continue;
					// 					}
					// 					if (data->PeopleSpecial.d1 >= 100)
					// 					{
					// 						continue;
					// 					}
					// 					pUserList->targetlist[num] = i;
					// 					if (++num == maxnum)
					// 					{
					// 						break;
					// 					}
					// 				}
					// 				pUserList->targetlist[0] = TargetID;
					// 				pUserList->m_MaxTargetNum = num;
					// 			}
					break;
				case 126://��Ȫ
					func2(true, cAttackAI::eET��Ȫ֮Ϣ126, 126);
					break;
				case 127://�����ɢ
					func2(true, cAttackAI::eET�����ɢ127, -1);
					break;
				case 37: // ���˵�
				case 104:
				case 125:
				case 3008:
				case 3009:
					pUserList->m_MaxTargetNum = 0;
					for (int i = 0; i < maxnum; i++)
					{
						pUserList->targetlist[pUserList->m_MaxTargetNum] = g_pMainState->m_AI.GetNear(UserID, TargetID, i, 2);

						if (bAtk)
							if (UserID == pUserList->targetlist[pUserList->m_MaxTargetNum])
							{//��ֹ���󹥻��Լ�
								continue;
							}

						if (-1 == pUserList->targetlist[pUserList->m_MaxTargetNum])
						{
							break;
						}
						pUserList->m_MaxTargetNum += 1;
					}
					break;
				case 3048:
				{
					int num = 0;
					int star = UserID >= 10 ? 10 : 0;
					for (int i = star; i < star + 10; ++i)
					{
						//					if (i == TargetID)continue;
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
						if (pUserData->PeopleSpecial.d1 < data->PeopleSpecial.d2)
						{
							continue;
						}
						pUserList->targetlist[num] = i;
						if (++num == maxnum)
						{
							//						break;
						}
					}
					//				pUserList->targetlist[0] = TargetID;
					pUserList->m_MaxTargetNum = num;
					int d = pUserData->m_HP - pUserData->m_HPMax.GetData() / 10;
					if (d > 0)
					{
						AddHp(UserID, -d);
						SetDamage(d, UserID);
						pUserData->m_HPHurtMax = pUserData->m_HP;
						pUserData->m_MP = 0;
					}
				}
				break;
				default:
					for (int i = 0; i < maxnum; i++)
					{
						pUserList->targetlist[pUserList->m_MaxTargetNum] = g_pMainState->m_AI.GetNear(UserID, TargetID, i, 1 + 2);
						//GetTargetID(UserID, TargetID, i);

						if (bAtk)
							if (UserID == pUserList->targetlist[pUserList->m_MaxTargetNum])
							{//��ֹ���󹥻��Լ�
								continue;
							}

						if (-1 == pUserList->targetlist[pUserList->m_MaxTargetNum])
						{
							break;
						}
						pUserList->m_MaxTargetNum += 1;
					}
					break;
				}
			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
			{
				pUserList->m_NowTargetID = pUserList->targetlist[i];
				if (bAtk)m_pFightState->SetMagicSuffer(pUserList->m_NowTargetID, pUser->GetDirection());

				if (toAll)
				{
					m_pFightState->m_pList[pUserList->m_NowTargetID]->m_bSufferFullSkill = TRUE;
					m_pFightState->m_FullSkill.m_FullSkilUP[0].m_Picture.m_FrameGap = magicspeed;
				}
				else
				{
					m_pFightState->m_pList[pUserList->m_NowTargetID]->m_bSufferFullSkill = FALSE;
					m_pFightState->m_pList[pUserList->m_NowTargetID]->SetMagiSufferID(MagicID, MagicPos, &m_pFightState->m_FullSkill.m_SufferMagic[TargetID], MagicUporDown);
					m_pFightState->m_pList[pUserList->m_NowTargetID]->m_pData->m_MagicSuffer.m_FrameGap = magicspeed;
				}
			}
			stage += 1;
		}
		return TRUE;
	case 2:
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(FALSE);
			stage += 1;
		}
	case 3:  //����BUFF

	{
		DWORD MagicID;
		BOOL toAll = GetSkillToAll(sSkillID);
		int LateTime; //�˺�������ʱ
		BOOL bAtk;
		GetDelayAnd(sSkillID, LateTime, MagicID);
		bAtk = GetSkillAtk(sSkillID);
		BOOL bover = FALSE;
		if (toAll)
		{
			if (m_pFightState->m_FullSkill.m_FullSkilUP[0].GetNowFrame() == m_pFightState->m_FullSkill.m_FullSkilUP[0].GetMaxFrame() - LateTime)
			{
				bover = TRUE;
			}
		}
		else
		{
			if (!pTarget->m_MagicSuffer.m_NeedShow)bover = TRUE;
			else
			{
				if (LateTime >= pTarget->m_MagicSuffer.m_pFile->GetMaxFrame())LateTime = pTarget->m_MagicSuffer.m_pFile->GetMaxFrame() - 1;
				if (pTarget->m_MagicSuffer.GetFrame() == pTarget->m_MagicSuffer.m_pFile->GetMaxFrame() - LateTime)
				{
					bover = TRUE;
				}
			}
		}
		if (bover)
		{
			stage = 4;
			pUserList->m_NowTarget = -1;
			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
			{
				pUserList->m_NowTargetID = pUserList->targetlist[i];
				if (bAtk)
				{
					m_pFightState->SwitchMagicSuffer(pUserList->m_NowTargetID);
					m_pFightState->m_pList[pUserList->m_NowTargetID]->m_pData->SetSound(POS_SUFFER);//����

				}

				if (CheckMagicHit(Skilllv, sSkillID, UserID, pUserList->m_NowTargetID/*TargetID*/))
				{
					EffectSkill(Skilllv, sSkillID, UserID, pUserList->m_NowTargetID);
				}
			}
			cPetData* pPet;
			pUser->GetDateP(pPet);
			if (1 > pPet->m_HP)
			{
				if (UserID < 10)
					pUserList->m_sufferDirection = 3;
				else pUserList->m_sufferDirection = 7;
				g_pMainState->m_pFightState->SetDie(UserID);
				pTargetData->m_CP /= 2;
				return TRUE;
			}
		}
	}
	return TRUE;
	case 4://�ȴ����Ƕ������
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic)
		{
			switch (sSkillID)
			{
			case 7: // �Ƹ�����

			{
				pUserList->m_SkillSelect.SkillID = 1017;
				stage = 0;
			}
			return TRUE;
			case 50: // ���컨��

			{
				pUserList->m_SkillSelect.SkillID = 1050;
				stage = 0;
			}
			return TRUE;
			case 2095: // ������ɽ

			{
				pUserList->m_SkillSelect.SkillID = 1095;
				stage = 0;
			}
			return TRUE;
			}
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(FALSE);
			stage = 5;
		}
		return TRUE;
	case 5:StageWaitSleep(10, UserID, 6); break;
	case 6:

	{
		pUser->SetMagicSound(-1);//����
		pUserList->m_work.pop_back();

		if (g_pMainState->m_FightList[TargetID].isLive && (!g_pMainState->m_FightList[TargetID].CheckDie()))
		{
			CoutComboMagic(sSkillID, pUserData, UserID, pTargetData);
		}

	}
	break;

	}
	return TRUE;
}


#endif