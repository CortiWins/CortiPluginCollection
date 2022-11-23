CortiItemSkillHealing DynRPG PlugIn V0.2

 ========== Author: ==========
Corti 07.03.2013 für Davias & Elektra Kingdom

 ========== Versionen: ==========
(V0.1) Erste Version - tut was es soll
(V0.2) In neue Projektstruktur übernommen, umbenannt. Inlines weg.

 ========== Zweck und Nutzen: ==========

Bei Heilitems kann eingestellt werden, dass eine Gesamtmenge oder ein Anteil der Gesamt-HP des Ziels geheilt werden. Bei Skills ist es nicht möglich, einen Prozentsatz der Gesamt-HP als Heilmenge anzugeben. Skills können eigene Animationen haben, aber Items besitzen lediglich die Standarditemanimation.

Möchte man nun sowohl eigene Animationen als auch Heilung entsprechend eines Prozentsatzes der Gesamt-HP des Ziels, so kann dieses Plugin aushelfen.

 ========== Anwendung: ==========
Das Plugin zieht die Information, wieviel geheilt werden soll aus der Beschreibung des Skills, der an das Item gebunden ist.
Bei Skills, die nicht als Skill sondern nur als Itemeffekt vorhanden sind ist die Description für den Spieler nie sichtbar.

Die folgenden Codestrings können in der Skilldescription eingefügt sein:
Codestring: "DAVHP666"   : Heilung entsprechend 666% der Gesamtlebenspunkte ( 3 Ziffern ), für 22% entsprechend DAVHP022
Codestring: "DAVMP444"  : Mana entsprechend 444% des Gesamtmanas ( 3 Ziffern )

Die Heilung/das Mana zielt auf einen Helden oder auch alle, wenn der entsprechende Skill ein Multitarget-Skill ist.
Die Kürzel enthalten DAV, da das Plugin im Original für Davias war.
Anwendung von, oder auf Monster nicht vorgesehen. Dann passiert gar nichts.
Die Menge der Heilung/des Manas wird als Standard-Popupzahl angezeigt.
Wird sowohl Mana als auch Heilung zugefügt, ist nur das HeilungsPopUp zu sehen. (Technisch bedingt )
Die Popup-Zahl für Heilung wird in Farbe 18 des Systemsets angezeigt.
Die Popup-Zahl für Mana wird in Farbe 1 des Systemsets angezeigt.
Dies kann durch Einträge in der DynRPG.ini geändert werden

[CortiItemSkillHealing]
HealColor=18
ManaColor=1

 ========== Probleme / Feedback: ==========
Bei Problemen, Fragen, Rückmeldungen etc. wende dich einfach an mich, den Corti, am besten im RPG-Atelier per Privatnachricht
http://www.multimediaxis.de/members/4806-Corti
