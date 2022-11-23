CortiAnalysis DynRPG PlugIn V0.1

 ========== Author: ==========
Corti, auf besonderen Wunsch von G-Brothers

 ========== Versionen: ==========
(V0.1) 27.12.13 Erste Version - tut was es soll

 ========== Zweck: ==========
Umsetzen von Analysezaubern im 2k3. Als solche gekennzeichnete Analysezauber, ob als Skill oder als Item-Scroll, können folgende Dinge:
* Automatisch einen Eintrag in einem VariablenArray flaggen.
* Eine Eventseite durch ein Switch freischalten, in der man dann Informationen zum Monster anzeigen kann
* Es synchronisiert Daten zum verwendeten Analysezauber und zum Ziel in Variablen

Zusammenarbeit mit CortiMonsterHud durch Verwenden des selben Switcharrays
 ========== Ein Wort in eigener Sache: ==========
Ich hatte ernsthaft Hemmungen dieses Plugin zu bauen, weil ich fürchte, dass Leute ein Analysefeature einbauen, die sonst von der
schlechten Umsetzbarkeit abgeschreckt werden würden.

Lasst mich erklären:
Spiele sind Rätsel, es ist das Spielprinzip etwas rauszufinden, z.B., dass der Pflanzengegner gegen Feuer anfällig ist.
Wenn das nicht erschließbar ist, z.B. weil die Monster zu freaky werden und die Elemente zu viele, dann wird Analyse eingebaut.
Somit ist der Analysezauber wie im Internet nachlesen, wogegen der Feind allergisch ist. Es ist ein Umgehen des Rätsels.
Das beschissene Rätsel wird aber nicht plötzlich ein gutes Rätsel weil man die Lösung vorgesetzt bekommt ohne das Gehirn zu benutzen.

 ========== Konfiguration: ==========
Die Konfiguration ist in die DynRPG.ini einzutragen. Eine Konfiguration kann wie folgt aussehen.

[CortiAnalysis]
; Skill 10 und 11 haben Analysefunktion
AnalysisSkill_1=10
AnalysisSkill_2=11
; MonsterArray beginnt ab Switch61 fürMonster 1
AnalysisArraySwitchId=61
; Bei Verwendung eines Analyseitems/Skills automatisch Switch20 aktivieren,  0 = Deaktiviert
AutoActivateSwitch=20
; Bei Verwendung eines AnalyseItems/Skills die ID des genutzen Skills in Variable 41 schreiben, 0 = Deaktiviert
TrackingSkillUsed=41
; Bei Verwendung eines Analyseitems die ID des genutzen Items in Variable 41 schreiben, 0 = Deaktiviert
TrackingItemUsed=42
; Variable 43 enthält die MonsterGroup-ID  (1 bis 8 ) wenn Analyse auf einen Feind angewendet wurde.
; Variable 43 enthält die Zahl 99 wenn Analyse auf eine Gruppe angewendet wurde.  0 = Deaktiviert
TrackingGroupTargetId=43
; Variable 44 enthält die Datenbank-ID wenn Analyse auf einen Feind angewendet wurde. 0 = Deaktiviert
TrackingDatabaseId=44
; Variable 44 bis 51 enthalten die Datenbank-IDs wenn Analyse auf eine Gruppe angewendet wurde. 0 = Deaktiviert
TrackingDatabaseIdArray=44

 ========== Probleme / Feedback: ==========
Bei Problemen, Fragen, Rückmeldungen etc. wende dich einfach an mich, den Corti, am besten im RPG-Atelier per Privatnachricht
http://www.multimediaxis.de/members/4806-Corti
