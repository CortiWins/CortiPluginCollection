CortiSkillTracking DynRPG PlugIn V0.2

 ========== Author: ==========
Corti 26.01.2014 UseTracking f�r goldenroy
      13.02.2014 SkillTracking f�r Innocentia

 ========== Versionen: ==========
V0.1 (26.01.2014) Bei Verwendung konfigurierter Skills wird eine Variable erh�ht
V0.2 (13.02.2014) �bertr�gt die ID und Anwendungsziele der genutzen Skills.
                  Dokumentation �ber notwendige Eventstruktur ist noch nicht enthalten.

 ========== Zweck: ==========
Das Plugin hat seit Version 0.2 mehrfache Funktion.

 ========== Zweck: Skillnutzungen z�hlen ==========
Zu z�hlen, wie oft ein Skill verwendet wurde, kann helfen um in einem Skillsystem die Skills selber Stufen gewinnen k�nnen.
Beispielsweise: Feuer I 20 mal verwenden -> Feuer II

 ========== Zweck: Skillnutzung nachverfolgen ==========
Hierbei wird nach Ende des Heldenzuges in die Variablen �bertragen, welcher Skill benutzt wurde und auf wen.

Wenn die Variable N als VariableBegin-Wert gegeben wird, dann werden diese Variable und die folgenden beschrieben:

Variable[N+0] = DatabaseId des ausf�hrenden Helden
Variable[N+1] = Skill-ID oder -1 wenn kein Skill genutzt
Variable[N+2] = Zieltypus, 0 = Nix, 1 = einHeld, 2 = alle Helden, 3 = Monster, 4 = Alle Monster
Variable[N+3] = Wenn einzelnes Monster oder einzelner Held angezielt: ID des Zieles, Onebased, Helden oder Gegnergruppen-ID, sonst -1

Nat�rlich h�te man hier die kompletten Inhalte der in DynRPG verf�gbaren Battler->Action �bertragen k�nnen, aber das lohnt nicht, da man diese nicht nutzen kann.

Lass mich erkl�ren:
Die Eventseiten im Kampfsystem, z.B. "[Hero] uses [Attack] Command" tun nicht das, was sie verk�nden. Sie werden nicht ausgel�st, wenn ein held etwas getan hat, sondern wenn er beginnt etwas zu tun.

* Spieler gibt Helden Kommando, zB [Attack]
* Eventseite "[Hero] uses [Attack] Command" wird ausgel�st
* Der Held greift an

Nun angenommen, man w�rde in der "[Hero] uses [Attack] Command"-Eventseite ein Switch setzen, dass eine andere Seite schaltet, dann w�rde dies niht sofort, sondern erst nach dem Angriff aufgerufen werden.

* Spieler gibt Helden Kommando, zB [Attack]
* Eventseite "[Hero] uses [Attack] Command" wird ausgel�st, Set Switch 1:ON
* Der Held greift an
* Eventseite "Switch [1] ON" wird ausgel�st , Set Switch 1:OFF

Die Daten einer Heldenhandlung werden erst nach Abschluss der Handlung in Variablen �bertragen, stehen also in der Eventseite "Switch [1] ON" zu Verf�gung.
Leider kann man sich auf diese Abfolge nicht verlassen, es gibt n�mlich Ausnahmen.
* LinkToEvent
* Defend
* Item
* Skills, die Conditions auf den ausf�hrenden Helden setzen

Wenn eine dieser Handlungen ausgef�hrt wird, dann wird der Maker die Eventseite "Switch [1] ON" nicht wie zu erwarten ausf�hren. Statt dessen wird diese erst dann ausgef�hrt, wenn das n�chste mal ein Akteur einen nicht mit Absonderlichketen behafteten Zug ausf�hrt, das kann ein Monster sein, oder ein anderer Held, es eignet sich also nicht, um verl�sslich direkt als Reaktion auf die Handlung Code auszuf�hren. Mir ist derzeit kein Fix bekannt, der dieses Problem behebt.
Auch das Normalverhalten ist nur dann verl�sslich, wenn genug Zeit bleibt und die Monsterz�ge oder Heldenbereitshaften nicht dazwischen funken. Dieser Zustand l�sst sich durch das CortiAtb-Speed-plugin allerdings gut und leicht erreichen.

####### Anmerkung: ########
Es gibt die M�glichkeit, mit einer Kombination aus Eventcode und Dyn-Plugin trotzdem etwas zu konstruieren, dass sich dazu eignet, auf Skillnutzungen und Kampfhandlungen angemessen zu reagieren. Ein Beispiel daf�r werde ich in der Zukunft diesem Projekt beilegen, sobald ich derartiges konstruiert habe.

 ========== Anwendung der Skillnutzungen : ==========
Skill-Variablen-Paare m�ssen in der DynRPG.ini hinterlegt werden.

Beispielkonfiguration:
[CortiSkillTracking]
SkillUsesId1=123
SkillUsesVar1=1601
SkillUsesId2=100
SkillUsesVar2=101
SkillUsesId3=25
SkillUsesVar3=0
SkillUsesId5=125
SkillUsesVar5=10003

Skill Nr 120 anzuwenden erh�ht Variable 1601 um einen Z�hler.
Skill Nr 100 anzuwenden erh�ht Variable 101 um einen Z�hler.
Skill Nr 25 anzuwenden erh�ht keine Variable, da der Variablenwert ung�ltig ist.
Skill Nr 125 anzuwenden erh�ht nichts, da kein Skill4 Eintrag existiert. Die Nummerierung muss durchgehend sein und bricht beim ersten fehlenden ab.

 ========== Anwendung des Skilltrackings : ==========

HeldenDatenbankID-Variablen-Paare m�ssen in der DynRPG.ini hinterlegt werden.

Beispielkonfiguration:
[CortiSkillTracking]
OtherHeroesVariableBegin=71
HeroId1=2
HeroIdVariableBegin1=66

Held mit der Datenbank-Id 2 schreibt seine Daten in die Variablen ab 66.
Alle anderen in Variablen ab 71. Wenn "OtherHeroesVariableBegin" mit 0 parametriert ist oder fehlt, wird f�r nichtspezifisch hinterlegte Helden keine Verarbeitung durchgef�hrt.

 ========== Notiz: ==========
Dem Plugin wird in der Zukunft ein umfangreicheres SkillTracking zugef�gt.

 ========== Probleme / Feedback: ==========
Bei Problemen, Fragen, R�ckmeldungen etc. wende dich einfach an mich, den Corti, am besten im RPG-Atelier per Privatnachricht
http://www.multimediaxis.de/members/4806-Corti
