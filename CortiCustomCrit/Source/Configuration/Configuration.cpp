namespace Configuration
{
// Is set if the settings are valid.
bool isValidSettings = false;

//! Typ der Critberechnung
int critCalcType = 0; // 1 bis 3.

/* Typ der Berechnung des kritischen Trefferbonuses
0 = Keine Variante. Anderen Parameter angeben.
1 = Es wird ein Prozentsatz der aktuellen ATK als Bonus hinzugefügt. Der Prozentsatz ist im Value-Parameter eingestellt.
2 = Es wird ein ATK Wert der Statkurve eines Helden entnommen. Die Datenkbank-ID des Helden ist im Value-Parameter eingestellt. */
int critAttackBonusType = 1;

// Zusatzparameter. Prozentsatz der Atk oder Helden Id
int critAttackBonusTypeValue = 50;

//! CritCalcWithLevel
// 0 = keine Adaption auf Basis des Levels, für die Umrechnung in Berechnungstyp 3 wird der Heldenlevel genutzt
// 1 = der Int-Wert des Gegners wird als dessen Levelstufe angenommen
// 2 = eine Variable enthält den Level der Gegner, dieser Wert wird als Level für alle Gegner angenommen
int critCalcWithLevel = 0;

//! Index der Variable für Type2 der Levelberechnung
int critCalcWithLevelVariable = 0;

//! Wenn dieser Parameter gesetzt ist, können kritische Treffer nur gegen Feinde ausgeführt werden
bool critCalcOnHerosDisabled = false;

//! Tells if critical strikes are disabled for all skills except those especially configured.
bool disabledSkillCrit = false;

//! Decides if and how weapon attacks are calculated.
int critCalcWeaponCriticalType;

//! Decides which actions do apply the weapon crit bonus.
int critCalcWeaponCritBonusApplication;

//! Changes a few bytes in memory to disable standard critical strikes.
void DisableStandardHeroCritInMemory()
{
    // KotatsuAkira [PyroPrincess] 24.10.2022
    // [004B979Bh/000B8B9Bh] Probably Hero Crit
    // Before:   741E (JE __004B97BBh)
    // After:    EB1E (JMP __004B97BBh)

    // [004BD880h/000BCC80h] Probably Monster Crit
    // Before:   7421 (JE __004BD8A3h)
    // After:    EB21 (JMP __004BD8A3h)

    // [004B97D7h/000B8BD7h] Probably Hero-Weapon Crit
    // Before:   763B (JBE __004B9814h)
    // After:    EB3B (JMP __004B9814h)

    // Notiz: ByteOrder ist zur Laufzeit invertiert.

    unsigned short previous1 = *reinterpret_cast<unsigned short *>(0x004B979B); // Before: 0x1E74
    unsigned short previous3 = *reinterpret_cast<unsigned short *>(0x004B97D7); // Before: 0x3B76

    if(previous1 != 0x1E74)
    {
        LOGERROR("Disable default crit: Value at 0x004B979B is '" << previous1 << "' should be '0x1E74'");
    }

    if(previous3 != 0x3B76)
    {
        LOGERROR("Disable default crit: Value at 0x004B979B is '" << previous3 << "' should be '0x3B76'");
    }

    *reinterpret_cast<unsigned short *>(0x004B979B) = 0x1EEB; // HeroCrit
    *reinterpret_cast<unsigned short *>(0x004B97D7) = 0x3BEB; // WeaponCrit
}

//! Changes a few bytes in memory to disable standard critical strikes.
void DisableStandardMonsterCritInMemory()
{
    // KotatsuAkira [PyroPrincess] 24.10.2022
    // [004B979Bh/000B8B9Bh]
    // Before:   741E (JE __004B97BBh)
    // After:    EB1E (JMP __004B97BBh)

    // [004BD880h/000BCC80h]
    // Before:   7421 (JE __004BD8A3h)
    // After:    EB21 (JMP __004BD8A3h)

    // [004B97D7h/000B8BD7h]
    // Before:   763B (JBE __004B9814h)
    // After:    EB3B (JMP __004B9814h)

    // Notiz: ByteOrder ist zur Laufzeit invertiert.
    unsigned short previous2 = *reinterpret_cast<unsigned short *>(0x004BD880); // Before: 0x2174
    if(previous2 != 0x2174)
    {
        LOGERROR("Disable default crit: Value at 0x004B979B is '" << previous2 << "' should be '0x2174'");
    }

    *reinterpret_cast<unsigned short *>(0x004BD880) = 0x21EB; // MonsterCrit
}


void Load()
{
    isValidSettings = true;

    // Kritberechnungstyp ( 1,2,3)
    critCalcType = Helper::GetValueFromConfig("CritCalcType");
    if(critCalcType <= 0 || critCalcType > 3 )
    {
        LOGERROR("CritCalcType:" << critCalcType << " Try to add a configuration");
        isValidSettings = false;
    }
    else
    {
        LOGINFO("CritCalcType:" << critCalcType);
    }

    // CritAttackBonusType ( 1, 2 )
    critAttackBonusType = Helper::GetValueFromConfig("CritAttackBonusType");
    if(critAttackBonusType <= 0 || critAttackBonusType > 2 )
    {
        LOGERROR("CritAttackBonusType:" << critAttackBonusType);
        isValidSettings = false;
    }
    else
    {
        LOGINFO("CritAttackBonusType:" << critAttackBonusType);
    }

    // ATK Bonus % oder Helden-ID, je nach 'CritAttackBonusType'
    critAttackBonusTypeValue = Helper::GetValueFromConfig("CritAttackBonusTypeValue");
    int numberOfActors = RPG::actors.count();
    if(critAttackBonusTypeValue <= 0)
    {
        LOGERROR("CritAttackBonusTypeValue:" << critAttackBonusTypeValue);
        isValidSettings = false;
    }
    else if(critAttackBonusType == 2 && critAttackBonusTypeValue > numberOfActors)
    {
        LOGERROR("CritAttackBonusTypeValue: HeroId " << critAttackBonusTypeValue << " Invalid");
        isValidSettings = false;
    }
    else
    {
        LOGINFO("CritAttackBonusTypeValue:" << critAttackBonusTypeValue);
    }

    // Leveladaptives System
    /* Parameter:
    0 = keine Adaption auf Basis des Levels, für die Umrechnung in Berechnungstyp 3 wird der Heldenlevel genutzt
    1= der Int-Wert des Gegners wird als dessen Levelstufe angenommen.
    2 = eine Variable enthält den Level der Gegner, dieser Wert wird als Level für alle Gegner angenommen*/
    critCalcWithLevel = Helper::GetValueFromConfig("CritCalcWithLevel");
    if(critCalcWithLevel < 0 || critCalcWithLevel > 2 )
    {
        LOGERROR("CritCalcWithLevel:" << critCalcWithLevel);
        isValidSettings = false;
    }
    else
    {
        LOGINFO("CritCalcWithLevel:" << critCalcWithLevel);
    }

    // LevelAdaptation
    critCalcWithLevelVariable = Helper::GetValueFromConfig("CritCalcWithLevelVariable");
    if(critCalcWithLevel == 2) // Nur wenn Typ2 der Levelanpassung -> Quellvariable einlesen...
    {
        if(critCalcWithLevelVariable <= 0)
        {
            LOGERROR("CritCalcWithLevelVariable:" << critCalcWithLevelVariable << " invalid");
            isValidSettings = false;
        }
        else
        {
            LOGINFO("CritCalcWithLevelVariable:" << critCalcWithLevelVariable);
        }
    }

    // 1 = Use plugin criticals. The standard crit system is disabled with a memory-hack.
    // 2 = Use plugin criticals. The standard crit system will not be disabled.
    // 3 = The plugin does not work on weapon attacks.
    critCalcWeaponCriticalType = Helper::GetValueFromConfig("CritCalcWeaponCriticalType");
    if (critCalcWeaponCriticalType == 0)
    {
        LOGERROR("CritCalcWeaponCriticalType:" << critCalcWeaponCriticalType << " invalid.");
        isValidSettings = false;
    }
    else if (critCalcWeaponCriticalType == 1)
    {
        LOGINFO("CritCalcWeaponCriticalType:" << critCalcWeaponCriticalType << " Standard weapon crit system is disabled with a memory-hack.");
        DisableStandardHeroCritInMemory();
    }
    else if (critCalcWeaponCriticalType == 2)
    {
        LOGINFO("CritCalcWeaponCriticalType:" << critCalcWeaponCriticalType << " Standard weapon crit system will not be disabled.");
    }
    else if (critCalcWeaponCriticalType == 3)
    {
        LOGINFO("CritCalcWeaponCriticalType:" << critCalcWeaponCriticalType << " CustomCrit disabled on standard weapon attacks.");
    }

    // CritCalcWeaponCritBonusApplication
    // 1 = Weapon crit Bonus is applied to weapon attacks and skills
    // 2 = Weapon crit Bonus is applied only to weapon attacks
    critCalcWeaponCritBonusApplication = Helper::GetValueFromConfig("CritCalcWeaponCritBonusApplication");
    if(critCalcWeaponCritBonusApplication == 1)
    {
        LOGINFO("CritCalcWeaponCritBonusApplication:" << critCalcWeaponCritBonusApplication << " Weapon CritBonus used on Skills & Weapon Attacks.");
    }
    else  if(critCalcWeaponCritBonusApplication == 2)
    {
        LOGINFO("CritCalcWeaponCritBonusApplication:" << critCalcWeaponCritBonusApplication << " Weapon CritBonus used on Weapon Attacks only.");
    }
    else
    {
        LOGERROR("CritCalcWeaponCritBonusApplication:" << critCalcWeaponCritBonusApplication << " invalid.");
        isValidSettings = false;
    }

    // If this parameter is set, critical strikes can only be done by certain skills.
    disabledSkillCrit = Helper::GetValueFromConfig("CritCalcOnSkillsDisabled") > 0;
    LOGINFO("CritCalcOnSkillsDisabled:" << disabledSkillCrit);

    // Wenn dieser Parameter gesetzt ist, können kritische Treffer nur gegen Feinde ausgeführt werden
    critCalcOnHerosDisabled = Helper::GetValueFromConfig("CritCalcOnHerosDisabled") > 0;
    LOGINFO("CritCalcOnHerosDisabled:" << critCalcOnHerosDisabled);

    // Parameter entfernt
    int deprecatedCritCalcOnHerosLevel = Helper::GetValueFromConfig("CritCalcOnHerosLevel");
    if(deprecatedCritCalcOnHerosLevel != 0)
    {
        LOGERROR("CritCalcOnHerosLevel:" << deprecatedCritCalcOnHerosLevel << " Parameter was removed in 0.9");
    }
}
}
