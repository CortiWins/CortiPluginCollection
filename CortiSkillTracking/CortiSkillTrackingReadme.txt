CortiSkillTracking DynRPG PlugIn V0.2

 ========== Author: ==========
Corti 26.01.2014 UseTracking für goldenroy
      13.02.2014 SkillTracking für Innocentia

 ========== Versionen: ==========
V0.1 (26.01.2014) Bei Verwendung konfigurierter Skills wird eine Variable erhöht
V0.2 (13.02.2014) Überträgt die ID und Anwendungsziele der genutzen Skills.
                  Dokumentation über notwendige Eventstruktur ist noch nicht enthalten.

 ========== Zweck: ==========
Das Plugin hat seit Version 0.2 mehrfache Funktion.

 ========== Zweck: Skillnutzungen zählen ==========
Zu zählen, wie oft ein Skill verwendet wurde, kann helfen um in einem Skillsystem die Skills selber Stufen gewinnen können.
Beispielsweise: Feuer I 20 mal verwenden -> Feuer II

 ========== Zweck: Skillnutzung nachverfolgen ==========
Hierbei wird nach Ende des Heldenzuges in die Variablen übertragen, welcher Skill benutzt wurde und auf wen.

Wenn die Variable N als VariableBegin-Wert gegeben wird, dann werden diese Variable und die folgenden beschrieben:

Variable[N+0] = DatabaseId des ausführenden Helden
Variable[N+1] = Skill-ID oder -1 wenn kein Skill genutzt
Variable[N+2] = Zieltypus, 0 = Nix, 1 = einHeld, 2 = alle Helden, 3 = Monster, 4 = Alle Monster
Variable[N+3] = Wenn einzelnes Monster oder einzelner Held angezielt: ID des Zieles, Onebased, Helden oder Gegnergruppen-ID, sonst -1

Natürlich häte man hier die kompletten Inhalte der in DynRPG verfügbaren Battler->Action übertragen können, aber das lohnt nicht, da man diese nicht nutzen kann.

Lass mich erklären:
Die Eventseiten im Kampfsystem, z.B. "[Hero] uses [Attack] Command" tun nicht das, was sie verkünden. Sie werden nicht ausgelöst, wenn ein held etwas getan hat, sondern wenn er beginnt etwas zu tun.

* Spieler gibt Helden Kommando, zB [Attack]
* Eventseite "[Hero] uses [Attack] Command" wird ausgelöst
* Der Held greift an

Nun angenommen, man würde in der "[Hero] uses [Attack] Command"-Eventseite ein Switch setzen, dass eine andere Seite schaltet, dann würde dies niht sofort, sondern erst nach dem Angriff aufgerufen werden.

* Spieler gibt Helden Kommando, zB [Attack]
* Eventseite "[Hero] uses [Attack] Command" wird ausgelöst, Set Switch 1:ON
* Der Held greift an
* Eventseite "Switch [1] ON" wird ausgelöst , Set Switch 1:OFF

Die Daten einer Heldenhandlung werden erst nach Abschluss der Handlung in Variablen übertragen, stehen also in der Eventseite "Switch [1] ON" zu Verfügung.
Leider kann man sich auf diese Abfolge nicht verlassen, es gibt nämlich Ausnahmen.
* LinkToEvent
* Defend
* Item
* Skills, die Conditions auf den ausführenden Helden setzen

Wenn eine dieser Handlungen ausgeführt wird, dann wird der Maker die Eventseite "Switch [1] ON" nicht wie zu erwarten ausführen. Statt dessen wird diese erst dann ausgeführt, wenn das nächste mal ein Akteur einen nicht mit Absonderlichketen behafteten Zug ausführt, das kann ein Monster sein, oder ein anderer Held, es eignet sich also nicht, um verlässlich direkt als Reaktion auf die Handlung Code auszuführen. Mir ist derzeit kein Fix bekannt, der dieses Problem behebt.
Auch das Normalverhalten ist nur dann verlässlich, wenn genug Zeit bleibt und die Monsterzüge oder Heldenbereitshaften nicht dazwischen funken. Dieser Zustand lässt sich durch das CortiAtb-Speed-plugin allerdings gut und leicht erreichen.

####### Anmerkung: ########
Es gibt die Möglichkeit, mit einer Kombination aus Eventcode und Dyn-Plugin trotzdem etwas zu konstruieren, dass sich dazu eignet, auf Skillnutzungen und Kampfhandlungen angemessen zu reagieren. Ein Beispiel dafür werde ich in der Zukunft diesem Projekt beilegen, sobald ich derartiges konstruiert habe.

 ========== Anwendung der Skillnutzungen : ==========
Skill-Variablen-Paare müssen in der DynRPG.ini hinterlegt werden.

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

Skill Nr 120 anzuwenden erhöht Variable 1601 um einen Zähler.
Skill Nr 100 anzuwenden erhöht Variable 101 um einen Zähler.
Skill Nr 25 anzuwenden erhöht keine Variable, da der Variablenwert ungültig ist.
Skill Nr 125 anzuwenden erhöht nichts, da kein Skill4 Eintrag existiert. Die Nummerierung muss durchgehend sein und bricht beim ersten fehlenden ab.

 ========== Anwendung des Skilltrackings : ==========

HeldenDatenbankID-Variablen-Paare müssen in der DynRPG.ini hinterlegt werden.

Beispielkonfiguration:
[CortiSkillTracking]
OtherHeroesVariableBegin=71
HeroId1=2
HeroIdVariableBegin1=66

Held mit der Datenbank-Id 2 schreibt seine Daten in die Variablen ab 66.
Alle anderen in Variablen ab 71. Wenn "OtherHeroesVariableBegin" mit 0 parametriert ist oder fehlt, wird für nichtspezifisch hinterlegte Helden keine Verarbeitung durchgeführt.

 ========== Notiz: ==========
Dem Plugin wird in der Zukunft ein umfangreicheres SkillTracking zugefügt.

 ========== Probleme / Feedback: ==========
Bei Problemen, Fragen, Rückmeldungen etc. wende dich einfach an mich, den Corti, am besten im RPG-Atelier per Privatnachricht
http://www.multimediaxis.de/members/4806-Corti
