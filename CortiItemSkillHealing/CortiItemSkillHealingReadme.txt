CortiItemSkillHealing DynRPG PlugIn V0.2

 ========== Author: ==========
Corti 07.03.2013 f�r Davias & Elektra Kingdom

 ========== Versionen: ==========
(V0.1) Erste Version - tut was es soll
(V0.2) In neue Projektstruktur �bernommen, umbenannt. Inlines weg.

 ========== Zweck und Nutzen: ==========

Bei Heilitems kann eingestellt werden, dass eine Gesamtmenge oder ein Anteil der Gesamt-HP des Ziels geheilt werden. Bei Skills ist es nicht m�glich, einen Prozentsatz der Gesamt-HP als Heilmenge anzugeben. Skills k�nnen eigene Animationen haben, aber Items besitzen lediglich die Standarditemanimation.

M�chte man nun sowohl eigene Animationen als auch Heilung entsprechend eines Prozentsatzes der Gesamt-HP des Ziels, so kann dieses Plugin aushelfen.

 ========== Anwendung: ==========
Das Plugin zieht die Information, wieviel geheilt werden soll aus der Beschreibung des Skills, der an das Item gebunden ist.
Bei Skills, die nicht als Skill sondern nur als Itemeffekt vorhanden sind ist die Description f�r den Spieler nie sichtbar.

Die folgenden Codestrings k�nnen in der Skilldescription eingef�gt sein:
Codestring: "DAVHP666"   : Heilung entsprechend 666% der Gesamtlebenspunkte ( 3 Ziffern ), f�r 22% entsprechend DAVHP022
Codestring: "DAVMP444"  : Mana entsprechend 444% des Gesamtmanas ( 3 Ziffern )

Die Heilung/das Mana zielt auf einen Helden oder auch alle, wenn der entsprechende Skill ein Multitarget-Skill ist.
Die K�rzel enthalten DAV, da das Plugin im Original f�r Davias war.
Anwendung von, oder auf Monster nicht vorgesehen. Dann passiert gar nichts.
Die Menge der Heilung/des Manas wird als Standard-Popupzahl angezeigt.
Wird sowohl Mana als auch Heilung zugef�gt, ist nur das HeilungsPopUp zu sehen. (Technisch bedingt )
Die Popup-Zahl f�r Heilung wird in Farbe 18 des Systemsets angezeigt.
Die Popup-Zahl f�r Mana wird in Farbe 1 des Systemsets angezeigt.
Dies kann durch Eintr�ge in der DynRPG.ini ge�ndert werden

[CortiItemSkillHealing]
HealColor=18
ManaColor=1

 ========== Probleme / Feedback: ==========
Bei Problemen, Fragen, R�ckmeldungen etc. wende dich einfach an mich, den Corti, am besten im RPG-Atelier per Privatnachricht
http://www.multimediaxis.de/members/4806-Corti
