CortiAnalysis DynRPG PlugIn V0.1

 ========== Author: ==========
Corti, at a special wish from G-Brothers

 ========== Versionen: ==========
(V0.1) 27.12.13 First Version

 ========== Zweck: ==========
Creating analysis spells and items in 2k3. Flagged analysis spells, as a skill or item-scroll, can do the following things:
* Setting an entry in a variable array
* Setting a switch that allows to an event page to trigger, in which you can show the monster data
* sychronizes data of the analaysis-spell and it's target in variables

Works together with CortiMonsterHud by using the same SwitchArrays.

 ========== On a personal note: ==========
I had scruples to build this plugin, because i was afraid that people would build an analysis feature, who would otherwise be deterred by the bad 
practicability. 

Let me explain:
Games are a puzzle, a riddle. It's about guessing that the plantmonster is vulnerable to fire. If the monsters get too freaky and there are to many weird conditions and elements, it may get too hard to guess. Some designer solve that by giving an analysis spell to the player. 
To me, this is like a puzzle and a spell that solves the puzzle for you. If the player needs a spell because he can't solve the puzzle by himself, then the puzzle sucks. Like a crossword puzzle with words in swahili, which you obviously don't speak well enough to solve that crossword puzzle. Is a crossword puzzle in swahili suddenly fun when you get the solution for it? 

 ========== Konfiguration: ==========
The configuration has to be done in the DynRPG.ini. A configuration can look like this:

[CortiAnalysis]
; Skill 10 and 11 have analysis function
AnalysisSkill_1=10
AnalysisSkill_2=11
; MonsterArray begins at Switch61 for Monster 1
AnalysisArraySwitchId=61
; When using an analysis item/skill, switch 20 gets activated. 0=deactivated
AutoActivateSwitch=20
; When using an analysis item/skill, the id of the used skill is written to variable 41. 0=deactivated
TrackingSkillUsed=41
; When using an analysis item the id of the used item is written to variable 42. 0=deactivated
TrackingItemUsed=42
; Variable 43 will contain the monster group id( 1 to 8 ) when analysis was used on an enemy.
; Variable 43 will contain the number 99, if analaysis was used on the group of enemies. 0=deactivated
TrackingGroupTargetId=43
; Variable 44 will contain the database id of the analysed monster. 0=deactivated
TrackingDatabaseId=44
; Variables 44 to 51 will contain the database id of all monsters, when analyse is used on a group. 0=deactivated
TrackingDatabaseIdArray=44

 ========== Problems / Feedback: ==========
If you encounter a problems or a bug, if you have questions and/or just feedback, write me a Message in the forums.
Before doing that, please read the readme files carefully and check the example projekt.

http://rpgmaker.net/users/Corti/
http://www.multimediaxis.de/members/4806-Corti
