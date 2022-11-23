CortiSkillOverload DynRPG PlugIn V0.2

 ========== Author: ==========
Corti 02.07.2013 für MarcL

 ========== Versionen: ==========
0.1 Erste Version - tut was es soll
0.2 Funktion zugefügt, Selftarget-Skills werden nicht ersetzt. Siehe Konfiguration

 ========== Zweck: ==========

Skills bauen, die eigenen Helden Schaden und negative Effekte zufügen.
Skills bauen, mit denen Monster sich selbst Schaden und negative Effekte zufügen.
Skills bauen, mit denen man Monster heilen kann.

 ========== Anwendung: ==========
Das Überladen der Skills kann in der DynRPG.ini konfiguriert werden.

Beispielkonfiguration:
[CortiSkillOverload]
Skill1=15
SkillReplace1=16
Skill2=20
SkillReplace2=23
Skill3=44
SkillReplace3=deine Mudder
Skill5=50
SkillReplace5=45
DisableHeroSelftarget=0
DisableMonsterSelftarget=0

Skill Nr 15 in der Datenbank wird durch Skill Nummer 16 ersetzt.
Skill Nr 20 in der Datenbank wird durch Skill Nummer 23 ersetzt.
Skill Nr 44 in der Datenbank wird nicht ersetzt, da der Replacewert keiner gültigen Zahl entspricht.
Skill Nr 50 in der Datenbank wird nicht ersetzt, da kein Skill4 Eintrag existiert. Die Nummerierung muss durchgehend sein und bricht beim ersten fehlenden ab.
Valide SkillIds sind zwischen 1 und 9000;

DisableHeroSelftarget:
Deaktiviert das ersetzen der Skills wenn ein Held sich selbst anwählt.

DisableMonsterSelftarget:
Deaktiviert das ersetzen der Skills wenn ein Monster sich selbst anwählt.

 ========== Notiz: ==========
Es sollten nur Einzelzielskills mit Einzelzielskills und Mehrfachziel- durch Mehrfachzielskills ersetzt werden.
Keine Ahnung was passiert wenn man da was tauscht.

 ========== Bekannte Bugs: ==========
Bei Anwendung von Skills auf den ausführenden Charakter wird die Animation irregulär ein zweites Mal gespielt.
Wüsste nicht wie man es fixen kann. Wer was weiss möge es mir sagen.

 ========== Probleme / Feedback: ==========
Bei Problemen, Fragen, Rückmeldungen etc. wende dich einfach an mich, den Corti, am besten im RPG-Atelier per Privatnachricht
http://www.multimediaxis.de/members/4806-Corti
