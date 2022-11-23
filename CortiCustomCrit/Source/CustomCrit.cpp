namespace CustomCrit
{
// Contains Configuration. Loaded onStartup
std::map<std::string, std::string> configMap;

// Common Functions
#include "Common/Dialog.cpp"
#include "Common/Helper.cpp"

#include "Configuration//Configuration.cpp"
#include "Configuration//ConfigSkills.cpp"
#include "Configuration//ConfigType1.cpp"
#include "Configuration//ConfigType2.cpp"
#include "Configuration//ConfigType3.cpp"
#include "Configuration//ConfigMonsterCrit.cpp"
#include "Configuration//ConfigVisualEffects.cpp"

#include "Calculations//LevelInfluence.cpp"
#include "Calculations//CritCalcType1.cpp"
#include "Calculations//CritCalcType2.cpp"
#include "Calculations//CritCalcType3.cpp"
#include "Calculations//Calculations.cpp"
#include "Calculations//RandomNumbers.cpp"

#include "VisualEffects/CustomAnimation.cpp" // Class to custom-render a RPG::Animation.
#include "VisualEffects/CustomAnimationPopup.cpp"
#include "VisualEffects/DrawCritSplash.cpp"

#include "CriticalStrikes//HeroAttackBonus.cpp"
#include "CriticalStrikes//MonsterAttackBonus.cpp"
#include "CriticalStrikes//CritCommands.cpp"

//! Gibt an, ob 'onDoBattlerAction' bereits gerufen wurde um sicherzustellen, dass die Critberechnung nur einmal ausgeführt wird.
bool isOnDoBattlerActionCalledOnce = false;

//! Function Pointer to chosen CritCalculation that takes a Battler* and returns an int.
int ( *critFunction ) ( RPG::Battler* );

int GetZero ( RPG::Battler *battler )
{
    return 0;
}

void OnHeroAction ( RPG::Battler *battler )
{
    if ( Calculations::CanHeroCrit ( battler ) )
    {
        LOGINFO ( "HeroId " << battler->id << " DoBattlerAction - Action can crit" );

        // Calling the configured crit calculation to calculate the hero based crit chance
        int currentCritChance = critFunction ( battler );
        LOGINFO ( "HeroId " << battler->id << " Critchance.Hero: " << currentCritChance );

        // Adding the weapon CritBonus based chance.
        currentCritChance += Calculations::ApplyWeaponCritBonus ( battler );
        LOGINFO ( "HeroId " << battler->id << " Critchance.WithWeapon: " << currentCritChance );

        // When using skills, calculate skillspecific factors.
        if ( battler->action->kind == RPG::AK_SKILL )
        {
            currentCritChance = Calculations::ApplySkillspecific ( currentCritChance, battler->action->skillId );
            LOGINFO ( "HeroId " << battler->id << " Critchance.AfterSkillModifier: " << currentCritChance );
        }

        // Roll the dice and compare to calculated crit value.
        int randomValue = RandomNumbers::GetRandomNumberHeroFromDeck();
        LOGINFO ( "HeroId " << battler->id << " Roll: " << randomValue );
        if ( currentCritChance > 0 && randomValue <= currentCritChance )
        {
            LOGINFO ( "HeroId " << battler->id << " Action CRITICAL" );

            // Action is critical, so set Attack bonus for battler.
            HeroAttackBonus::AddCritBonus ( battler->id );
            // Add Splash-Effect to the action target.
            if ( ConfigVisualEffects::isSplashEffectEnabled )
            {
                DrawCritSplash::AddEffects ( battler->action , ConfigVisualEffects::delayFramesHeroes);
            }
            else if ( ConfigVisualEffects::isCustomAnimationEnabled )
            {
                CustomAnimationPopup::AddEffects ( battler->action, ConfigVisualEffects::delayFramesHeroes );
            }
        }
        else
        {
            // Action did not roll crit, so reset crit status.
            LOGINFO ( "HeroId " << battler->id << " Action does NOT crit" );
            HeroAttackBonus::ResetCritBonus ( battler->id );
        }
    }
    else
    {
        LOGINFO ( "HeroId " << battler->id << " DoBattlerAction - Action can not crit" );
        HeroAttackBonus::ResetCritBonus ( battler->id ); // Action can't crit, so reset crit status.
    }
}

void OnMonsterAction ( RPG::Battler *battler )
{
    if ( Calculations::CanMonsterCrit ( battler ) )
    {
        LOGINFO ( "Monster " << battler->id << " DoBattlerAction - Action can crit" );

        // Calling the configured crit calculation to calculate the hero based crit chance
        int currentCritChance = Calculations::CalculateMonsterCrit ( battler );
        LOGINFO ( "Monster " << battler->id << " Critchance.Monster: " << currentCritChance );

        // When using skills, calculate skillspecific factors.
        if ( battler->action->kind == RPG::AK_SKILL )
        {
            currentCritChance = Calculations::ApplySkillspecific ( currentCritChance, battler->action->skillId );
            LOGINFO ( "Monster " << battler->id << " Critchance.AfterSkillModifier: " << currentCritChance );
        }

        // Hero AntiCrit by Items.
        currentCritChance = Calculations::ApplyAntiCrit ( currentCritChance, battler->action );

        // Roll the dice and compare to calculated crit value.
        int randomValue = RandomNumbers::GetRandomNumberMonsterFromDeck();
        LOGINFO ( "Monster " << battler->id << " Roll: " << randomValue );
        if ( currentCritChance > 0 && randomValue <= currentCritChance )
        {
            LOGINFO ( "Monster " << battler->id << " Action CRITICAL" );

            // Action is critical, so set Attack bonus for battler.
            MonsterAttackBonus::AddCritBonus ( battler->id - 1 );

            // Add Splash-Effect to the action target.
            if ( ConfigVisualEffects::isSplashEffectEnabled )
            {
                DrawCritSplash::AddEffects ( battler->action, ConfigVisualEffects::delayFramesMonsters );
            }
            else if ( ConfigVisualEffects::isCustomAnimationEnabled )
            {
                CustomAnimationPopup::AddEffects ( battler->action, ConfigVisualEffects::delayFramesMonsters );
            }
        }
        else
        {
            // Action did not roll crit, so reset crit status.
            LOGINFO ( "Monster " << battler->id << " Action does NOT crit" );
            MonsterAttackBonus::ResetCritBonus ( battler->id - 1 );
        }
    }
    else
    {
        LOGINFO ( "Monster " << battler->id << " DoBattlerAction - Action can not crit" );
        MonsterAttackBonus::ResetCritBonus ( battler->id - 1 ); // Action can't crit, so reset crit status.
    }
}

//! Called from callback 'onDoBattlerAction'
    void CallbackOnDoBattlerAction ( RPG::Battler * battler )
    {
        if ( isOnDoBattlerActionCalledOnce )
        {
            return;
        }

        isOnDoBattlerActionCalledOnce = true;
        LOGINFO ( "----------------------------------------------------------------------" );

        if ( battler->isMonster() && ConfigMonsterCrit::monsterCritOnAttack )
        {
            OnMonsterAction ( battler );
        }
        else if ( Configuration::isValidSettings )
        {
            OnHeroAction ( battler );
        }
    }

//! Called from callback 'onBattlerActionDone'
void CallbackOnBattlerActionDone ( RPG::Battler * battler, bool success )
{
    if ( success )
    {
        isOnDoBattlerActionCalledOnce = false;
    }
}

//! Called from callback 'OnFrame' when the Scene is entered or when the frameCounter is lower than before.
// Difference between OnResetGame and OnSceneChange:
// in OnResetGame only the flags get resettet. The ATK values get automatically reset by the game.
void OnResetGame()
{
    HeroAttackBonus::OnResetGame();
    MonsterAttackBonus::OnResetGame();
    DrawCritSplash::ResetFrames();
    CustomAnimationPopup::ResetFrames();
}

//! Called by 'onBattlerDrawn' callback after a battler was drawn (or supposed to be drawn).
void CallbackOnBattlerDrawn ( RPG::Battler *battler, bool isMonster, int id )
{
    if ( isMonster )
    {
        if ( ConfigVisualEffects::isSplashEffectEnabled )
        {
            DrawCritSplash::OnMonsterDrawn ( id, battler );
        }
        else if ( ConfigVisualEffects::isCustomAnimationEnabled )
        {
            CustomAnimationPopup::OnMonsterDrawn ( id, battler );
        }
    }
    else
    {
        if ( ConfigVisualEffects::isSplashEffectEnabled )
        {
            DrawCritSplash::OnHeroDrawn ( id, battler );
        }
        else if ( ConfigVisualEffects::isCustomAnimationEnabled )
        {
            CustomAnimationPopup::OnHeroDrawn ( id, battler );
        }
    }
}

//! Called from callback 'OnFrame' when the player has entered or left the battle.
void OnSceneChange()
{
    HeroAttackBonus::OnSceneChange();
    MonsterAttackBonus::OnSceneChange();
    DrawCritSplash::ResetFrames();
    CustomAnimationPopup::ResetFrames();
}

//! Called from callback 'onComment'.
bool CallBackOnComment ( const RPG::ParsedCommentData *parsedData )
{
    if ( !strcmp ( parsedData->command, "ccrit_getstatus" ) )
    {
        CritCommands::HeroGetStatus ( parsedData );
        return false;
    }
    else if ( !strcmp ( parsedData->command, "ccrit_resetstatus" ) )
    {
        CritCommands::HeroResetStatus ( parsedData );
        return false;
    }
    else if ( !strcmp ( parsedData->command, "ccrit_monster_getstatus" ) )
    {
        CritCommands::MonsterGetStatus ( parsedData );
        return false;
    }
    else if ( !strcmp ( parsedData->command, "ccrit_monster_resetstatus" ) )
    {
        CritCommands::MonsterResetStatus ( parsedData );
        return false;
    }
    else if ( !strcmp ( parsedData->command, "ccrit_skill_addcon" ) )
    {
        CritCommands::AddSkillData ( parsedData, 1 );
        return false;
    }
    else if ( !strcmp ( parsedData->command, "ccrit_skill_addvar" ) )
    {
        CritCommands::AddSkillData ( parsedData, 2 );
        return false;
    }
    else if ( !strcmp ( parsedData->command, "ccrit_skill_mulcon" ) )
    {
        CritCommands::AddSkillData ( parsedData, 3 );
        return false;
    }
    else if ( !strcmp ( parsedData->command, "ccrit_skill_mulvar" ) )
    {
        CritCommands::AddSkillData ( parsedData, 4 );
        return false;
    }
    else if ( !strcmp ( parsedData->command, "ccrit_skill_delay" ) )
    {
        CritCommands::AddSkillData ( parsedData, 5 );
        return false;
    }
    return true;
}

//! Called from callback 'onStartup'.
void CallbackOnStartup()
{
    std::map<std::string, std::string> configMapX = RPG::loadConfiguration ( ( char * ) "CortiXCustomCrit" );
    int stuff = configMapX.size();
    if(stuff > 0)
    {
        LOGERROR("Configuration contains section [CortiXCustomCrit] ( with an X ). In the current version, the section name is [CortiCustomCrit] ( without the X ).")
    }

    // We load the configuration from the DynRPG.ini file here
    configMap = RPG::loadConfiguration ( ( char * ) "CortiCustomCrit" );
}

//! Called from callback 'onInitFinished'.
void CallbackOnInitFinished()
{
    LOGINFO ( "------------------------------------------" );
    LOGINFO ( "CortiCustomCrit: Initializing.Started" );
    CustomCrit::Configuration::Load();
    CustomCrit::ConfigVisualEffects::Load();
    LOGINFO ( "------------------------------------------" );
    CustomCrit::ConfigSkills::Load();
    LOGINFO ( "------------------------------------------" );

    if ( CustomCrit::Configuration::critCalcType == 1 )
    {
        CustomCrit::critFunction = CustomCrit::CritCalcType1::CalculateCritFix;
        CustomCrit::ConfigType1::Load();
    }
    else if ( CustomCrit::Configuration::critCalcType == 2 )
    {
        CustomCrit::critFunction = CustomCrit::CritCalcType2::CalculateCritRaw;
        CustomCrit::ConfigType2::Load();
    }
    else if ( CustomCrit::Configuration::critCalcType == 3 )
    {
        CustomCrit::critFunction = CustomCrit::CritCalcType3::CalculateCritByRating;
        CustomCrit::ConfigType3::Load();
    }
    else
    {
        CustomCrit::critFunction = CustomCrit::GetZero;
        LOGERROR ( "CritCalcType is not validly set" );
    }

    CustomCrit::ConfigMonsterCrit::Load();
    CustomCrit::HeroAttackBonus::Load();
    CustomCrit::DrawCritSplash::OnInit();
    CustomCrit::CustomAnimationPopup::OnInit();
    CustomCrit::RandomNumbers::InitializeRandomSeed();
    LOGINFO ( "CortiCustomCrit: Initializing.Completed" );
    LOGINFO ( "------------------------------------------" );
}

//! Called from callback 'onExit'.
void CallbackOnExit()
{
    HeroAttackBonus::Unload();
    CustomCrit::DrawCritSplash::OnExit();
    CustomCrit::CustomAnimationPopup::OnExit();
}
}
