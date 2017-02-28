/* Copyright (C) 2009 - 2010 Nostalrius <http://nostalrius.org/>
 * Auteur        : Ner'zhul
 * All rights reserved */

#include "scriptPCH.h"
#include "ruins_of_ahnqiraj.h"

#define SPELL_BURROW 26381


struct npc_sandstalkerAI : public ScriptedAI
{
    npc_sandstalkerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiBurrow_Timer;

    void JustReachedHome()
    {
        m_creature->EnterVanish();
    }

    void Reset()
    {
        m_creature->EnterVanish();
        m_uiBurrow_Timer = 5000;
    }

    void Aggro(Unit* pWho)
    {
        Unit* pVanishTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
        m_creature->LeaveVanish();
        m_creature->Ambush(pVanishTarget, SPELL_BURROW);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->isInCombat())
            m_creature->EnterVanish();

        if (m_uiBurrow_Timer < uiDiff)
        {
            m_creature->EnterVanish();
            Unit* pVanishTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
            m_creature->LeaveVanish();
            m_creature->Ambush(pVanishTarget, SPELL_BURROW);
            m_uiBurrow_Timer = urand(5000, 10000);
        }
        else
            m_uiBurrow_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_sandstalker(Creature* pCreature)
{
    return new npc_sandstalkerAI(pCreature);
}

void AddSC_npc_sandstalker()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "npc_sandstalker";
    newscript->GetAI = &GetAI_npc_sandstalker;
    newscript->RegisterSelf();
}
