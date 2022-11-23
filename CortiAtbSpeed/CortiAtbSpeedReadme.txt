CortiAtbSpeed DynRPG PlugIn V0.8.1

 ========== Author: ==========
Corti ( Auf Basis von Corti's SD3x aka. "Untitled" Projekt )

 ========== ACHTUNG!: ==========
 * Ab V0.8.1 verändert sich die Berechnung der Atb-Geschwindigkeit. Der Parameter "SpeedPerBattler" sollte halbiert werden.

 ========== Versionen: ==========
(V0.1) Erste Version - tut was es soll
(V0.2) 07.08.2013 Restrukturiert und überarbeitet, bugfreier.
        * Neues Feature: AccelerationAfterTurn
        * Neues Feature: BrakeBeforeTurn
        * Neues Feature: SlowWithinTurn

(V0.3)  08.08.2013  * Neues Feature: Zusatzfunktion "ConditionFilter" um einen möglichen spieleinfrierenden Bug zu beseitigen
(V0.4)  30.12.2013  * Update:   SlowWithinTurn-Feature optimiert. Notwendig damit CortiCombatVisu ordnungsgemäß funktioniert.
                                Parameter zum Deaktivieren funktioniert nun auch.
(V0.5)  09.02.2014  * Update:   SlowWithinTurn-Feature nochmals optimiert. Readme umstrukturiert.
                    * Neu:      Parameter zum SlowWithinTurn-Framezähler.
                    * Neu:      Automatik-Enter wenn Held dran ist, ist per Default deaktiviert und muss manuell aktiviert werden
                    * Neu:      Different ATB Init - Funktion hinzugefügt.
(V0.51) 10.02.2014  * Fix:      HP,MP,Facesets etc. im Kampfsystem wurden aufgrund einen kleinen Fehlers nicht mehr angezeigt.
(V0.6)  14.02.2014  * Fix:      Chance auf Einfrieren des Spieles durch simulierten Tastendruck in Kombination mit LinkToEvent-Kommandos im Kampf.
                    * Neues Feature: SlowSwitches. Ermöglicht, das ATB-System zu "pseudo"-pausieren indem beliebige Switches gesetzt werden.
(V0.6)  11.04.2014  * Fixed baaaad mistake
(V0.7)  08.05.2014  * Zugefügt: Neuer Parameter um simulierten Enterdruck durch setzen eines Switches zu unterdrücken
(V0.8)  30.01.2015  * Neue Debugmöglichkeiten. See Tracking Errors at the bottom of this file.
(V0.81) 30.01.2015  * Fehler in interner Berechnung der Geschwindigkeitswerte beseitigt.

========== Todo: ==========
Automatisches Defaultsetzen des Atb-Modes scheint nicht zu funktionieren.

 ========== Zweck und Nutzen: ==========

Findest du das 2k3-KS lahmarschig? Das ist für dich!
Das Plugin regelt die Geschwindigkeit des Atb-Systemes des RPG Maker 2003 auf Basis der Anzahl aktiver Kampfteilnehmer. Das beseitigt den Nachteil des Standardsystemes, bei mehr als zwei/drei Teilnehmern im Kampf eklig langsam zu werden. Sobald ein Kampfteilnehmer zudem seine Atb-Leiste voll hat, wird das System temporär ausgebremst. Dadurch verliert ein Spieler nicht mehr wertvolle Zeit zwischen dem Moment in dem das ActionCommand-Fenster verfügbar wird, und der Bestätigungstaste des Spielers. Damit wird die standardmässig gegebene Möglichkeit weg, bei nicht selektiertem Helden, auf andere Kampfteilnehmer zu warten, was bei stark erhöhter Atb-Geschwindigkeit sich eher anfühlte als ob die Feinde einfach mehr Agilität hätten und öfter drankommen.

 ========== Wichtiger Hinweis #1: ==========

Der ATB-Mode wird von diesem Plugin automatisch auf WAIT gesetzt und die Regelung verhindert eine effektive ACTIVE-Nutzung sowieso.
Um den Spieler und das System nicht unnötig zu verwirren, sollte das Umschalten des ATB-Modes im Menü deaktiviert sein.
-> System2 in der Makerdatenbank.

 ========== Wichtiger Hinweis #2: ==========
Eure RPG_RT.exe sollte mit dem Fix "dynrpg_normal_skill_window_duration.ips" bearbeitet sein.
Erklärung: Das ursprüngliche DynRPG hat eine Verschlimmbesserung, bei der die Textbox [Skillname] wenn Monster Skills verwenden längen angezeigt wird. Diese Funktion korrumpiert die Eventverabreitung und sorgt für komische Effekte wenn Monster nacheinander dran sind.
Bei Verwendung von CortiAtbSpeed und CortiCombatVisu sollte der Fix auf jeden Fall installiert sein.

Link:
http://share.cherrytree.at/showfile-12977/dynrpg_normal_skill_window_duration.ips

Der Fix kann per DynPatches oder über ein IPS-Tool installiert werden.

 ========== Besonderes zu Conditions: ==========
Conditions, die dem Spieler die Kontrolle über die Helden entziehen ( Schlaf, Betäubung etc. ), frieren die Atb-Leiste des Helden ein. Bei Monstern ist dies nicht der Fall. Ihre (unsichtbaren) Atb-Leisten füllen sich weiter und ihre Handlung wird automatisch als "no Action" abgewickelt. Dadurch, dass Helden einfrieren kann es vorkommen, dass ein Held, der beispielweise bei vollem Atb-Wert handlungsunfähig gemacht durch die "Slowdown bei vollem Atb"-Funktion das ganze Kampfsystem einfriert. Zum jetzigen Stand von DynRPG ist es nicht möglich, die Einstellungen von Conditions auszulesen. Aus diesem Grund ist es notwendig, die IDs von Conditions, die dem Spieler die Kontrolle entziehen manuell aufzulisten.
-> Siehe Konfiguration:

 ========== Besonderes zu toten Kampfteilnehmern: ==========
Toten Helden wird im Moment ihres Ablebens der Atb-Wert auf Null gesetzt. Somit können tote Helden nicht bei voller Atb-Leiste einfrieren und das Kampfsystem ausbremsen.

 ========== F E A T U R E S ==========
Zusätzlich existieren vier Features die an dieser Stelle erläutert werden. Hohe Atb-Geschwindigkeiten können auch Nebeneffekte/Nachteile haben.
Diese vier Features dienen dazu, diese ungewünschten Nebeneffekte abzuschwächen.

 ========== SpeedPerBattler: ==========
Geschwindigkeit pro Kampfteilnehmer. Werte zwischen 100 und 300 sind super, je nach dem wie fix man es haben will. Wesentlich größere Werte halte ich für unsinnig. Diese Konfigurationszeile ist nicht notwendig.

[CortiAtbSpeed]
SpeedPerBattler=200

 ========== Feature: SlowWhenFilled ==========

Das Atb-System wird gedrosselt sobald ein Held oder Monster einen vollen Atb-Balken hat. Ohne dieses Feature wäre das Kampfsystem sehr hektisch. Dieses Feature kann per Parameter deaktiviert werden, auch wenn das NICHT empfohlen ist.
Per Default ist das Feature aktiviert. Diese Konfigurationszeile ist nicht notwendig.

[CortiAtbSpeed]
DisableSlowWhenFilled=0

 ========== Feature: AccelerationAfterTurn ==========

Nach dem Zug eines Kampfteilnehmers wird der Geschwindigkeitswert der Atb-Leisten nicht sofort wieder auf Maximum gesetzt, sondern mit jedem Frame (60/Sek.) wieder ein wenig zum Maximalwert beschleunigt.

Bei hohen Speedwerten kann das Kampfgeschehen sonst sehr hektisch wirken.
Dieses Feature kann per Parameter deaktiviert und konfiguriert werden, auch wenn das NICHT empfohlen ist. Per Default ist das Feature aktiviert und mit empfohlenen Werten versehen. Die Anzahl Frames, über die das System hat einem Zug wieder beschleunigt wird. 60 Frames entsprechen einer Sekunde. 0 deaktiviert die Funktion. Man kann es erhöhen wenn man es smoother will. Diese Konfigurationszeile ist nicht notwendig.

[CortiAtbSpeed]
AccelerationAfterTurnFrames=60

 ========== Feature: BrakeBeforeTurn ==========

Ähnlich dem vorherigen Feature reduziert dies die Atb-Geschwindigkeit, allerdings je näher ein Kampfteilnehmer der Füllung seiner Atb-Leiste kommt, es ist quasi eine Art "Bremsen" zum Ende hin. Dabei wird die Geschwindigkeit auf bis zu 20% reduziert.
Dies macht Sinn, weil bei hohen Atb-Geschwindigkeiten die chance erhöht wird, dass Helden und Monster zeitgleich und im selben Atb-Tick am Zug sind. Dies wiederum kann bei der Verarbeitung von Eventseiten störend sein und die Kampfabläufe hektisch, undurchsichtig und zuweilen buggy wirken lassen. Dieses Feature kann per Parameter deaktiviert und konfiguriert werden, auch wenn das NICHT empfohlen ist.

Per Default ist das Feature aktiviert und mit empfohlenen Werten versehen.

Der Atb-Wert vor dem Maximum ab dem gebremst wird. Maximum des Atb-Wertes ist 300000.
Werte von ca. 10k bis 15k sorgen für einen unauffälligen smoothen Bremsvorgang, der das System nicht spürbar verlangsamt. 0 deaktiviert die Funktion. Diese Konfigurationszeile ist nicht notwendig.

[CortiAtbSpeed]
BrakeBeforeTurn=15000

 ========== Feature: SlowWithinTurn ==========

Bremst das Atb-System für einen Moment, wenn ein Kampfteilnehmer eine Handlung vollzieht.
Dieses Feature macht die Schlagabfolge also weniger hektisch, chaotisch, undurchsichtig und fehlerträchtig für die Eventseiten wenn viele Monster und Helden nahezu zeitgleich an der Reihe sind.  Dieses Feature zu deaktivieren ist ab Version 0.5 ausdrücklich NICHT empfohlen.

Seit dieser Version funktioniert die SlowWithinTurns-Funktion über einen Frametimer und nicht mehr über die handlungsbasierten Callbacks. Die Änderung wurde gemacht um Kritik bzüglich hektischen Zugverhaltens entgegen zu kommen. 0 deaktiviert die Funktion. Diese Konfigurationszeile ist nicht notwendig.

[CortiAtbSpeed]
SlowWithinTurnsEnable=1

Die folgenden Einstellungen sind OPTIONAL und nur für den Fall notwendig, dass man mit dem Standardverhalten unzufrieden ist. Wild dran rumspielen macht das Spiel nicht besser.

Für diese Anzahl Frames wird ein SlowDown ausgelöst, wenn ein Kampfteilnehmer volles ATB erreicht.
DerMinimalwert beträgt 15, 25 wird empfohlen.
HitsFullSlowdownMax=25

Für diese Anzahl Frames wird ein SlowDown ausgelöst, wenn ein Kampfteilnehmer eine Handlung beginnt bzw. abschließt, wobei mit abschließen die makerinterne Berechnung gemeint ist und NICHT das optische Ende der Animation.
Der Minimalwert beträgt jeweils 40 bzw. 30
WithinActionSlowdownMax=60
WithinActionSlowdownMaxDone=40

Für diese Anzahl Frames wird ein SlowDown ausgelöst, wenn ein Kampfteilnehmer sich verteidigt. Diese Handlung ist kürzer als die anderen, daher wird hier ein anderer Framewert verwendet.
Der Minimalwert beträgt 15
WithinActionSlowdownDefenseMax=30

 ========== Feature: Automatik-Enter ==========
Sobald ein Held volles ATB hat, erscheint das Kommandoauswahlfenster. Hier muss der Spieler einmal Enter drücken, damit ein Cursor erscheint und eine Handlungsauswahl getroffen werden kann. Dieser unnötige Druck auf die Entertaste kann mit diesem Feature erspart werden.

Per Default ist das Feature deaktiviert, mit dieser Zeile in der Konfiguration kann es aktiviert werden.

[CortiAtbSpeed]
EnableSimulatedReturnKey=1
EnableSimulatedReturnKeyDisableSwitch=112

Technisch: Hierbei wird wenn das entsprechende Fenster gezeigt wird, automatisch ein virtueller Tastendruck an das Spielfenster gesendet.

Mit dem konfigurierbaren Switch kann das Feature im Spiel temporär deaktiviert werden, z.B. wenn MessageBoxen bei offenem Kommandofenster an gezeigt werden sollen.

 ========== Feature: Different ATB Init ==========
Normalerweise haben Helden und Monster zu Beginn des Kampfes alle den selben ATB-Wert. Wenn Kampfteilnehmer identische Werte haben kann es vorkommen, dass diese im selben ATB-Tick an der Reihe sind, es kann zu Komplikationen in der Eventseitenverarbeitung kommen, sowie komischen Eindrücken in der Schlagfolge. Diese Funktion ändert das.

Per Default ist das Feature aktiviert, mit dieser Zeile in der Konfiguration kann es deaktiviert werden.
[CortiAtbSpeed]
DisableDifferentAtbInit=1

 ========== Feature: SlowSwitches ==========
Ermöglichten, das ATB-System zu "pseudo"-pausieren indem beliebige Switches gesetzt werden. Pseudopausieren, weil das System auf den minimalen Geschwindigkeitswert 1 gesetzt wird. Praktisch bedeutet dies, dass das System im Hintergrund weiter läuft, also keine wirkliche Pause ist. Allerdings funktioniert die Eventverarbeitung besser wenn das ATB nicht ganz deaktiviert ist.
Die Nummerierung muss mit 1 beginnen und durchgängig sein. Wenn SlowSwitch2 nicht vorhanden ist wird nach SlowSwitch3 und höher nicht mehr gesucht.

SlowSwitch1=1021
SlowSwitch2=1022
SlowSwitch3=1023

 ========== ConditionX: ==========
Die Condition mit der Datenbank-ID "X" hat die Einstellung "Action Restriction : No Action allowed".
Die Nummerierung muss mit 1 beginnen und durchgängig sein. Wenn Condition12 nicht vorhanden ist wird nach Condition13 und höher nicht mehr gesucht.
Diese Konfiguration sollte entsprechend der Conditioneinstellungen gesetzt werden. Die höchste erlaubte Condition-ID ist 500. Es findet keine Prüfung statt, ob die ID in der Makerdatenbank vorhanden ist.

 ========== Konfiguration: ==========

Die Konfiguration ist in die DynRPG.ini einzutragen. Eine Konfiguration kann wie folgt aussehen.

[CortiAtbSpeed]
SpeedPerBattler=400
AccelerationAfterTurnFrames=60
BrakeBeforeTurn=15000
SlowWithinTurnsEnable=1
EnableSimulatedReturnKey=0
DisableDifferentAtbInit=1
Condition1=23
Condition2=12
Condition3=2
SlowSwitch1=1021
SlowSwitch2=1022
SlowSwitch3=1023
SlowSwitch4=1024

 ========== Tracking Errors: ==========
This means: setting switch 301 to ON will write data into a file.
Give that data to me, User: "Corti" in the multimediaxis.de forums.

DebugFileSwitchId=301
DebugFileName=d:\donkey.txt

 ========== Probleme / Feedback: ==========
"Mein Spiel friert ein!" -> Siehe Conditions und Konfiguration




Bei Problemen, Fragen, Rückmeldungen etc. wende dich einfach an mich, den Corti, am besten im RPG-Atelier per Privatnachricht: http://www.multimediaxis.de/members/4806-Corti
