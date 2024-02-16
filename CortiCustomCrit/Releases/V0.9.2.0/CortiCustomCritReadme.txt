CortiCustomCrit DynRPG PlugIn V0.9.0
	by Corti ( 2013-2024 )
	for unofficial RPG Maker 2003 with DynRPG v0.20 or higher

https://github.com/CortiWins/CortiPluginCollection
*******************************************************************
*                     Versions
*******************************************************************
(V0.1.0) [22.12.2013] Testversion
(V0.2.0) [29.12.2013] Advanced configuration
(V0.3.0) [28.01.2014] Error on reset fixed
(V0.4.0) [30.01.2015] Skillspecific modification of critchances
(V0.5.0) [11.09.2015] Restructured, translated. New setting: CritCalcOnSkillsDisabled
(V0.6.0) [13.09.2015] Fixed bug that prevent reenabling of specific skill if crit is disabled on skills. Improved documentation for Skillspecific Modifications. Translated DynRPG.ini lines.
(V0.7.0) [13.09.2015] Skillspecific delay for <CRIT!> Icon!
(V0.8.0) [18.08.2022] Missing return value on callback fixed.
(V0.8.1) [29.08.2022] Critmultiplier of '0' allowed to disable crit on certain skills.
(V0.8.2) [24.10.2022] Removed old Debug Outputs in favor of LogFile and Console. See Documentation further down.
(V0.8.3) [25.10.2022] Added Item/Weapon CritBonus and added more configurations possibilities. Added hack to disable RPG Maker standard crit. HeroDb Crit is not a possible stat source for CalculationType2.
(V0.9.0) [06.11.2022] Added battle animation as Crit!-Splash.
(V0.9.0) [06.11.2022] Added critical strikes for monsters
(V0.9.0) [06.11.2022] Added random number generation through shuffled deck of values for more consistent numbers.
(V0.9.0) [07.11.2022] Parameter 'CritCalcOnHerosLevel' removed. It was complicated and of little value.
(V0.9.0) [07.11.2022] No criticals on skills with no damage ( Decrease HP -Setting not set in DB )
(V0.9.0) [07.11.2022] Documentation updated
(V0.9.1) [22.11.2022] A whole bunch of documentation typos and small errors. Thx Boulon@RMN.net Added section 'Technical Limitations'.
(V0.9.1) [23.11.2022] VisualEffect.CustomAnimation: Fixed two bugs. One with cel offset in y and magnification was missing as well.
(V0.9.1) [23.11.2022] VisualEffect: added parameter for a delay by frames before the Crit!-Icons or Animation is shown.
(V0.9.2) [16.02.2024] Fixed possible NullReference Exception after leaving combat.

*******************************************************************
*                     Todo
*******************************************************************
- handle "miss". Not yet sure how.

*******************************************************************
*                     Content
*******************************************************************
Using the plugin
Chosing the right stat for critical strike chance
Configuration Parameters
Calculating the critical hit chance
    Type 1: Fixed Value
    Type 2: Raw Stat
    Type 3: Rating to Chance
Calculating power of critical strikes
Calculating the level influence
Monsters: Calculating the critical hit chance
Monsters: Calculating power of critical strikes
Skillspecific Modifications
VisualEffect
Technical Limitations
Debug outputs
Comment commands
For Developers

*******************************************************************
*                     Using the plugin
*******************************************************************
Implements the possibility to deal critical strikes with attacks and
skills in a way that ismore flexible than the rpg makers own crit calculations.

Landing a critical means that an attack randomly deals more damage.
This plugin simulates that by increasing the respective heros attack
value before the attack. Since there is no callback that is called after
the attack is done, the attack bonus can not be immediatley reset,
but it is updated when the next action is done and can also be manually reset
with a comment commmand. When an attack lands a critical strike,
a symbol is shown on top of the target. The symbol can be replaced with your own.

The plugin has quite a few different settings that can or need to be set.
Please read this document carefully.

*******************************************************************
*          Chosing the right stat for critical strike chance
*******************************************************************

There are different possible sources of crit-chance for heros and monsters.
* The Databases Crit-Stat ( 1 in N )
* Constant value configured in the DynRPG.ini
* From from a variable
* Using the int stat
* Using the agi stat

Chosing INT as the crit stat:
The heart of this plugin is to replace the crippled magic-off/def with something useful and way more cool.
Using the int stat is practical because you can use items and conditions to influence the critchance.

"But without int, how is magic improved then?"

Use attack and rename it to power or anything else that can be both physical and magical. The int formular is so bad, you can't do good power scaling with it anyway.

With int as the crit stat you have:
* Attack: Stronger at what you do
* Defense: live longer
* Agility: Do things more often
* Krit/Ex-Int: Chance to deal more damage

Chosing AGI as the crit stat:
Though i'd recommend to use int, agi is also possible to use agility, but only when using Type 3 right now.
This cam be useful, if you are using int for something else, like regeneration or if you hacked the formular and made int useful.

*******************************************************************
*                     Configuration Parameters
*******************************************************************
The important configuration settings are...
- Calculating the critical hit CHANCE
- Calculating the critical hit DAMAGE BONUS
- Level of player level vs monster level
- The monsters critical attacks
- the visual effect

All configuration is done in the DynRPG.ini file. See the TestProject for an example.

*******************************************************************
*                     Calculating the critical hit chance
*******************************************************************
This parameter determines the way the critical strike chance is calculated.
The critical strike chance can be calculated in three different ways.
* Type 1: Fixed Value
* Type 2: Raw Stat
* Type 3: Rating to Chance

CritCalcType=1

-------------------------------------------------------------------

The RPG Maker has a standard crit system, that only works on weapon attacks.
By adding this plugin, you now have two crit systems in place, so you need to decide which one to use.

CritCalcWeaponCriticalType=1
1 = Use plugin criticals. The standard crit system is disabled with a memory-hack.
2 = Use plugin criticals. The standard crit system will not be disabled.
3 = The plugin does not work on weapon attacks.

-------------------------------------------------------------------

If this parameter is set, critical strikes can only be done by certain skills.
If you want to disable crits on skill use, set this to one.

0 = Not disabled, skills can be critical strikes
1 = Disabled, skills can not be critical strikes
CritCalcOnSkillsDisabled=0

If you want to enable crit for certain spells, refer to section "Skillspecific Modifications".
By setting the Constant multiplicative chance, the skill is recognized as a exception for this rule.

-------------------------------------------------------------------

If this parameter is set, critical strikes by heroes can only be dealt against monsters.
Use this if you do not want critical healing skills.

0 = Not disabled, healing skills can be critical strikes
1 = Disabled, healing skills can not be critical strikes
CritCalcOnHerosDisabled=0

-------------------------------------------------------------------

Weapons can have a CritBonus value that is configured in the ItemDatabase.
The value is taken as additional critical strike percentage and
is added to the heros critical strike chance before applying skillspecific modifiers.

CritCalcWeaponCritBonusApplication=1
1 = Weapon crit Bonus is applied to weapon attacks and skills
2 = Weapon crit Bonus is applied only to weapon attacks

*******************************************************************
*                     Type 1: Fixed Value
*******************************************************************
No stats from the hero are used to calculate the crit chance.
The crit chance for each hero is configured in the configuration file.

This is for users that don't want to override one of the base stats and users who just like it very simple.
The default critical strike chance is 20%. This can be changed and every hero can be configured individually.

========= CONFIGURATION ====================
; CalculationType1 : DefaultCritChance for all heroes that are not specifically set
t1CritChanceDefault=20

; Hero with database ID 5 gets a 25% chance to crit.
t1HeroCritHero_1_Id=5
t1HeroCritHero_1_FixCrit=25

; Hero with database ID 3 gets his crit chance from variable 345
t1HeroCritHero_2_Id=3
t1HeroCritHero_2_Variable=345

*******************************************************************
*                     Type 2: Raw Stat
*******************************************************************

In this type, the critical strike chance equals one of the heroes stats.
Select a stat that is used as critical strike chance.

t2CritSourceStat=1
1 = int is used.
2 = agi is used.
3 = HeroCrit is used as a 1 in N calculation
4 = HeroCrit is used as a percentage

*******************************************************************
*                    Type 3: Rating to Chance
*******************************************************************
In this type, the critical strike chance does not equal int or agility value.
The stat values is taken as a rating value that is calculated into the chance division with a coefficient that depends on player and enemy level.

For this it is required to deposit an unused hero in the database whose maximum life curve is used as the coefficient.
Stat curves are quite abstract and hard to get for people who don't get well with mathematics.

This type of calculcation can be used to achieve best stat equivalency, but in most cases, the games don't require that.

Basics to stat curves ( in german ):
http://www.multimediaxis.de/threads/134909-RM-2k-2K3-Zahlen-und-Werteprogress
http://www.multimediaxis.de/threads/139514-Rm2k-2k3-Statkurven-als-Wertetemplate

========= CONFIGURATION ====================
Since coeffients are often floating point numbers, the max life alues from the stat curss is coefficient 100.

Example:
3 Int should be 14% Crit.
3 Int = 14% -> 3/14Int = 1% -> 0,214 Int -> 1% critical strike chance.

This 0,21 are now deposited in the stat curve as 21.

Select a stat that is used as critical strike rating
1 = Plugin uses intellect for Type 3 calculations ( Default )
2 = Plugin uses agility for Type 3 calculations
t3CritSourceStat=0

This parameter sets the database id of the hero whose max life curve if taken as a coeffient
t3RatingCoefficientHeroId=11

*******************************************************************
*            Calculating power of critical strikes
*******************************************************************
When a critical strike is dealt, the atk of the hero is increased before the action is executed.
Select a way the critical strike damage bonus is calculated.

0 = Invalid! Chose a better one!
1 = Atk is increased by a percentage of the heros atk. The percentage is configured i the CritAttackBonusTypeValue parameter.
2 = Atk is taken from the atk stat curve of a hero in the database. The database id of that hero is configured as the CritAttackBonusTypeValue parameter.
CritAttackBonusType=1

Example:
CritAttackBonusTypeValue=33
When using CritAttackBonusType 1, this increases atk by 33%.
When using CritAttackBonusType 2, this increases atk by the atk value of hero 33 on current hero level.

*******************************************************************
*                     Calculating the level influence
*******************************************************************
Calculating the heros and enemies level into the equation is required for type 3 stat equavalency.
If you are using type 1 or type 2 crit calculation, you don't need this and you can use standard values.
This can also be used to mimic the way crit is done by setting player agility off against enemy agility like it is done in a lot of jRPGs and the rpg makers own crit formular.

Parameter:
0 = No changes based on level, the heros own level is used as a coefficient in type 3.
1 = The enemies int value is taken as his level.
2 = A variable holds all enemies level.
CritCalcWithLevel=1

If CalcWithLevel=2, then this parameter determines the variable that holds the moblevel.
Set the enemy level to one that matches your heroes level when you first encounter the monster type.
CritCalcWithLevelVariable=256

*******************************************************************
*        Monsters: Calculating the critical hit chance
*******************************************************************
Select which stat is used to calculate the monster crit chance

1 = int is used.
2 = agi is used.
3 = MonsterCrit is used as a 1 in N calculation
4 = MonsterCrit is used as a percentage
MonsterCritSourceStat=3

-------------------------------------------------------------------

Select if monsters are able to deliver critical strikes on attacks, which includes double and charged attacks.
The default attack of monsters can crit für 3X damage based in the monsters crit setting in the database.
You can chose between 3 settings

1 = No Plugin-Crits for Monster-Standard-Attacks
2 = Plugin-Crits for Monster-Standard-Attacks active. 2k3 standard crits deactived by memory-hack.
3 = Plugin-Crits for Monster-Standard-Attacks active. 2k3 standard crits stay active. Not recommended, as it's dumb for gameplay.
MonsterCritOnAttack=1

-------------------------------------------------------------------

Select if monsters are able to deliver critical strikes on skill.
You can chose between 3 settings
1 = No Plugin-Crits for Monster Skills.
2 = Plugin-Crits for Monster Skills but only attacks.
3 = Plugin-Crits for Monster Skills both attacks and healing.
MonsterCritOnSkills=1

*******************************************************************
*         Monsters: Calculating power of critical strikes
*******************************************************************

Select how the attack bonus for critical strikes is calculated.
You can chose between 2 settings

1 = Increase ATK by N% of the MonsterDatabaseATK value.
2 = Increase ATK by N% of the ATK of a hero in the database at a calculated level ( see other CritCalcWithLevel setting )
MonsterCritAttackBonus=1

If MonsterCritAttackBonus is set to 1 a constant atk scale value is required.
Remember that the formular is (ATk/2-Def/4) so a 100% more atk, is very likely not just a 100% more damage but may be much more.
MonsterCritAttackBonusPercentage=50

If MonsterCritAttackBonus is set to 2 and thus refers to a hero atk curve, a hero database ID is required.
MonsterCritAttackBonusHeroDbId=11

*******************************************************************
*                     Skillspecific Modifications
*******************************************************************
This settings allow to influence the critical strike chance of certain specific skills that can be configured.
There are four possible modifications. Lets pretend the basic critchance is 10%.

* Constant multiplicative chance
Example: 50 = 10 * 50 / 100 = 15% critical strike chance

* Multiplicative chance from variable
Example: 123 = 10 * \v[123] / 100

* Constant additive chance
Example: 20 = 10 +20% critical strike chance

* Additive chance from variable
Example: 123 = + \v[123] critical strike chance

* Delay to show the > CRIT! < Icon in frames. To delay the effect on all actions, see section 'VisualEffect'
Example: 25 = showing the icon is delayed by 25 frames.

Formular for Hero (H) with Weapons (W) using Skill (S)
CritChance = ( [CritChance(H) + CritChance(W)] * MultiConst(S) /100  * MultiVar(S) / 100 ) + AddConst(S) + AddVar(S)

SkillIdX=123
SkillMulConX=0
SkillMulVarX=0
SkillAddConX=0
SkillAddVarX=04
SkillDelayX=25

========= CONFIGURATION ====================
The X is a number. Use "SkillId1" for the first skill, "SkillId2" for the second.
Parsing the parameters stops when a number is not found.

How to set up different skills:

; Skill 123 does have his crit chance doubled
SkillId1=123
SkillMulCon1=200

; Skill 11 does have his crit chance set to 0.
SkillId1=11
SkillMulCon1=0

; Skill 19 does have his crit chance increased by the value in variable 4200
SkillId2=19
SkillAddVar2=4200

; Skill 23 will not be configured because there is no skill configured with "SkillId3=..."
SkillId4=23
SkillAddCon4=30

*******************************************************************
*                     VisualEffect
*******************************************************************
Select a type of effect that is displayed when a critical strike is executed on a target.

1 = SplashEffect. Pops the #include "DynRessource\\Splash.png" graphic on top of the battler.
2 = CustomAnimation. Shows an animation, which mimics a battleAnimation with a given database ID.
VisualEffectType=1

If VisualEffectType is set to 2, an animation database ID is required.
VisualEffectAnimationDatabaseId=1

Important note:
The battle animation is not shown with the rpg makers default function,
but with an a custom script that tries to be close to the default behaviour,
but is not exactly matching. Some battle-animation features are currently not supported.

These settings allow to delay the showing of icon/animation the given number of frames.
To delay the effect on a single skill only, see section 'Skillspecific Modifications'
DelayFramesHeroes = 0
DelayFramesMonsters = 0

*******************************************************************
*                     Technical Limitations
*******************************************************************
Some actions in combat likes double attacks, combos, two weapons, and
weapons with two attacks are techncally one action,
so the plugin can only roll crit for the whole sequence of actions.

Currently "Miss" is calculated independently after the onActionCallback
and there's no way to work that in, so you can get critical misses.

*******************************************************************
*                     Debug outputs
*******************************************************************
All previous debug functions have been removed in favour of a new system which outputs all
settings an calculations to a file and/or a console window.

To active tracing, set the following entries in your DynRPG.ini
[CortiLog]
LogToConsole=1,
LogToFile=1,

The console logging requires the DebugConsole.exe the projects main folder.

*******************************************************************
*                     Comment commands
*******************************************************************
Use of comment commands: https://www.rewking.com/dynrpg/guidelines.html
You can use this commands in event scripts to request and reset a heros critical strike status for things like building an effect that happens after dealing a critical strike.

// Request crit status
@ccrit_getstatus heroId, switchId
heroId = Heros Database ID
switchId = ID of the switch that is set according to crit status.

// Manual reset of the heros crit status
@ccrit_resetstatus heroId
heroId = Heros Database ID

// Add and change skillspecific modifiers
@ccrit_skill_addcon skillId, value
@ccrit_skill_addvar skillId, value
@ccrit_skill_mulcon skillId, value
@ccrit_skill_mulvar skillId, value
@ccrit_skill_delay skillId, value

// Request monster crit status
@ccrit_monster_getstatus monsterGroupId, switchId
monsterGroupId = a value between 1 and 8.
switchId = ID of the switch that is set according to crit status.

// Manual reset of the monster crit status
@ccrit_monster_resetstatus monsterGroupId
monsterGroupId = a value between 1 and 8.

*******************************************************************
*                     For Developers
*******************************************************************
GCC compiler optimizations will destroy this plugins functionality.
If you recompile, make sure to deal with this.
http://rpgmaker.net/forums/topics/10254/?post=674082#post674082
