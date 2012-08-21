#include "ScriptPCH.h"

enum eNums
{
	SPELL_ICEARMOR = 36881,
	SPELL_FROSTBOLT = 59251,
	SPELL_FIREBOLT = 57628,
    SPELL_REINCARNATION = 20608,
	SPELL_FIREBALL = 11
};

class Skeletal : public CreatureScript {
public: Skeletal() : CreatureScript("Skeletal") { }

	CreatureAI* GetAI_Example(Creature* pCreature) const
	{ return new SkeletalAI(pCreature); }

	struct SkeletalAI : public ScriptedAI
	{
		SkeletalAI(Creature *c) : ScriptedAI(c) {}

		uint32 IceArmor_Timer;
		uint32 Frostbolt_Timer;
		uint32 Firebolt_Timer;
		uint32 Fireball_Timer;

		uint32 Phase;

		void Reset()
		{
		  IceArmor_Timer = 0;
		  Frostbolt_Timer = 0;
		  Firebolt_Timer = 5000;

		  Phase = 1;
		}
		
		void KilledUnit(Unit *)
		{
			me->MonsterYell("Hahaha, one down!", LANG_UNIVERSAL, NULL);
		}

		void JustDied(Unit *)
		{
			me->MonsterYell("This ain't over yet!", LANG_UNIVERSAL, NULL);
			if (me->GetMaxHealth() == 0) DoCast(me, SPELL_REINCARNATION);
		}

		void EnterCombat(Unit *)
		{
			me->MonsterYell("How dare you defile my sleep?!", LANG_UNIVERSAL, NULL);
			void Reset();
		}

		void UpdateAI(const uint32 uiDiff)
		{
			if (!me->getVictim())
			{
				if (IceArmor_Timer <= uiDiff)
				{
					DoCast(me, SPELL_ICEARMOR);
					IceArmor_Timer = 18000000;
				}
				else 
					IceArmor_Timer -= uiDiff;
			}
			

			if(!UpdateVictim())
				return;

			if (!HealthAbovePct(55) && (Phase == 1))
			{
				Phase = 2;
			}

			if (Phase == 1)
			{

		    if(Frostbolt_Timer <= uiDiff)
			{
				DoCast(me->getVictim(), SPELL_FROSTBOLT);
				Frostbolt_Timer = 3000;
			}
			else
				Frostbolt_Timer -= uiDiff;
			
			if(Fireball_Timer <= uiDiff)
			{
				if (Unit * pTarget = (SELECT_TARGET_RANDOM, 0))
					                 DoCast(pTarget, SPELL_FIREBALL);
			
				Fireball_Timer = 10000;
			}
			else
				Fireball_Timer -= uiDiff;
			}

			if (Phase == 2)
			{
				if(Fireball_Timer <= uiDiff)
				{
					DoCast(me->getVictim(), SPELL_FIREBALL);
					Fireball_Timer = 3000;

				}
				else
					Fireball_Timer -= uiDiff;
			}
			DoMeleeAttackIfReady();
		}
	};
};

void AddSC_Skeletal()
{
	new Skeletal();
}