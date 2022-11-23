CortiCombatVisu DynRPG PlugIn V0.2

 ========== Author: ==========
Corti: Plugin 19.12.2013 f�r Innocentia.

 ========== Versionen: ==========
(V0.1) 19.12.13 - Erste Version. tut was es soll
(V0.2) 30.12.13 - Weiterentwickelt
    * Grafiken in Unterordner verschoben
    * einige Parameter deprecated
(V0.3) 11.05.14 - Spezialfeatures f�r Innocentia's Dark Sword
(V0.4) 24.02.15 - Animierter Monster & Heldenselektor
(V0.5) 18.08.22 - Refactoring

 ========== Zweck und Nutzen: ==========
Anzeige der Schlagreihenfolge im Kampfsystem
* In brauchbarem Ma�e pr�zise
* Position, Orienterung, und vieles mehr konfigurierbar. Bau deine eignen Grafiken ein f�r den einzigartigen Look

Zuerst die wichtigste Frage: Was ist es NICHT? Velsarbor, FF10, ein CTB-Kampfsystem. Mit aktuellen Mitteln ist CTB mit Vorschau der Schlagfolgen�nderung nicht m�glich.
Das Kampfsystem wird dadurch auch kein CTB System, es bleibt im Hintergrund ATB.
Ein 2k3-Kampfsystem ohne Plugins ist unglaublich lahmarschig, die ATB-Balken zu entfernen w�rde also zu langen, f�r den Spieler unergr�ndlichn Wartezeiten f�hren.
Aus diesem und anderen Gr�nden empfehle ich w�rmstens das CortiAtbSpeed-Plugin zu verwenden und damit die Schl�ge schnell nacheinander folgen zu lassen.

Da das Plugin nur auf Basis der ATB-Werte des Makers und der Agilit�t die Schlagfolge sch�tzt, kann es dazu kommen, dass sich die Reihenfolge �ndert, was logisch erstmal nach einem Fehler aussieht.
Das liegt daran, dass der Maker die ATB-Leisten von Helden und Monstern nicht alle gleichzeitig f�llt, sondern sich in den Momenten wenn Helden oder Monster dran sind Aussetzer genehmigt.
Diese Ph�nomene k�nnen durch das SlowWithinTurn-Feature meines CortiAtbSpeed-Plugins gr��tenteils umgangen werden, weshalb ich dieses Plugin anderen Speedplugins aus dem Netz gegen�ber vorziehen w�rde.

 ========== Wichtiger Hinweis #1: ==========
Eure RPG_RT.exe sollte mit dem Fix "dynrpg_normal_skill_window_duration.ips" bearbeitet sein.
Erkl�rung: Das urspr�ngliche DynRPG hat eine Verschlimmbesserung, bei der die Textbox [Skillname] wenn Monster Skills verwenden l�ngen angezeigt wird. Diese Funktion korrumpiert die Eventverabreitung und sorgt f�r komische Effekte wenn Monster nacheinander dran sind.
Bei Verwendung von CortiAtbSpeed und CortiCombatVisu sollte der Fix auf jeden Fall installiert sein.

Link:
http://share.cherrytree.at/showfile-12977/dynrpg_normal_skill_window_duration.ips

Der Fix kann per DynPatches oder �ber ein IPS-Tool installiert werden.

 ========== Wichtiger Hinweis #2: ==========

Der ATB-Mode wird von diesem Plugin automatisch auf WAIT gesetzt und die Regelung verhindert eine effektive ACTIVE-Nutzung sowieso.
Um den Spieler und das System nicht unn�tig zu verwirren, sollte das Umschalten des ATB-Modes im Men� deaktiviert sein.
-> System2 in der Makerdatenbank.

 ========== Grafische Daten: ==========

>>>>> Frage: Wie bekomme ich den freien Platz unten am Bildrand, ich hab da die ATB-Leisten der Helden und h�here Portraits?
>>>>> Antwort: Ein eigenes System2-Set auf dem die ATB-Sachen leer sind und kleinere Facesets.

Alle Ressourcen sind im Ordner "Projekt\DynRessource\CortiCombatVisu"

>> Hintergrund:
Es ist m�glich eine Grafik als Rahmen anzuzeigen. Der Name der Grafik und ihre Position kann konfiguriert werden.
>> Heldenicons:
Die Grafik HeldenCombatVisu.png enth�lt die Portraits der Helden in der Reihenfolge die der Datenbank entspricht.
>> Monstericons
Im Unterordner \Monster befinden sich Icons f�r spezielle Monster. Der Name enth�lt die Datenbank-Id.
Wenn f�r ein Monster keine spezielle Datei vorhanden ist, wird die DefaultDatei verwendet.
>> Monsterzahlen
Um die Monster unterscheiden zu k�nnen, wird �ber dem Monstericon eine Zahl angezeigt. Die Zahlen eins bis acht sind in der MonsterNumbers.png hinterlegt. Die Position der Zahl auf dem Monster ist konfigurierbar.
>> Selektor / Highlight des ausgew�hlten Helden/Monsters
Es kann eine Grafik daf�r konfiguriert werden. Siehe Konfiguration.

>>>>> Frage: Darf ich die Grafiken benutzen?
>>>>> Antwort: Sind Velsarbor-Plagiate im RTP-Look, warum solltest du es wollen?

 ========== Besonderes zu Conditions: ==========
Conditions, die dem Spieler die Kontrolle �ber die Helden entziehen ( Schlaf, Bet�ubung etc. ), frieren die Atb-Leiste des Helden ein. Bei Monstern ist dies nicht der Fall. Ihre (unsichtbaren) Atb-Leisten f�llen sich weiter und ihre Handlung wird automatisch als "no Action" abgewickelt. Dadurch, dass Helden einfrieren kann es vorkommen, dass ein Held, der fast volles ATB hat er wesentlich sp�ter dran kommt.
Da es nicht m�glich ist, zu sch�tzen, wann ein Held der aktuell ausgeknockt ist wieder an der Reihe ist, werden Helden mit kontrollentziehenden Conditions ans Ende der Leiste sortiert.
Zum jetzigen Stand von DynRPG ist es nicht m�glich, die Einstellungen von Conditions auszulesen. Aus diesem Grund ist es notwendig, die IDs von Conditions, die dem Spieler die Kontrolle entziehen manuell aufzulisten.
-> Siehe Konfiguration:

 ========== Konfiguration: ==========
Die Anzahl anzuzeigender Icons. Minimum sind 6. Maximal 4 k�nnen davon Helden mit Kontrollverlust zugeordnet werden.
    NumberOfShownIcons=10

Position des ersten unverschobenen Icons in X und Y.
    PositionXOriginal=6
    PositionYOriginal=224

Das Icon der Kampfteilnehmers, der als n�chster dran ist kann ein paar Pixel von den anderen abgesetzt werden. Bedenke diese Einstellungen, wenn du das Gef�hl hast die Positionseinstellung w�rde dich irref�hren. Der Positionsurpsrung bezieht sich auf den unverschobenen Ort vom ersten Icon.

Verschiebung des ersten Icons in X zu den anderen
    IconsOffsetX=-2
Verschiebung des ersten Icons in Y zu den anderen
    IconsOffsetY=0

Diese Einstellungen beschreiben den Abstand zwischen den Icons in der Auflistung

Abstand zwischen den Icons in X
    IconSpaceBetweenX=31
Abstand zwischen den Icons in X
    IconSpaceBetweenY=0

Die Gr��e der Heldenicons kann frei gew�hlt werden. Wichtig ist nur, dass sie wie im Beispiel in aufsteigender Datenbank-ID ohne L�cken in der Grafik sind.

Gr��e der Heldenicons in der Grafik
    HeroIconSizeX=24
    HeroIconSizeY=15
Abstand in der Grafik in Y zwischen den Icons der Helden
    HeroIconOffsetY=16

Position der Zahlen der Monster-Id auf den Monstericons relativ zur Position des Monstericons
    NumberOffsetToIconX=22
    NumberOffsetToIconY=4

Ausma�e einzelner Zahlenicons in der Grafik
    NumberSizeX=7
    NumberSizeY=7
Abstand der Zahlenicons zueinander
    NumberOffsetInImage=8

Dateiname der Datei, die als Hintergrund dienen soll
    BackgroundFile=DynRessource\CortiCombatVisu\CortiCombatVisuBG.png
Position des Hintergrundes
    BackgroundPositionX=0
    BackgroundPositionY=224

Cursor auf ausgew�hlten Monstern:
Zu zeigende Grafik.
    MonsterSelectorFile=DynRessource\CortiCombatVisu\Selektor.png

Offset der Grafik zum Slot auf dem sie gezeigt werden in Pixeln.
    MonsterSelectorOffsetX=0
    MonsterSelectorOffsetY=0

Anzahl Animationsframes in der Grafik. Die Frames m�ssen in einer Reihe von oben nach unten angeordnet sein.
    MonsterSelectorFramesMax=11;

Die Icons von Helden mit Kontrollverlust k�nnen optisch etwas von den anderen wegger�ckt sein.

Verschiebung der CC-Icons in X zu den anderen
    ConditionAfflictedOffsetX=10
Verschiebung der CC-Icons in Y zu den anderen
    ConditionAfflictedOffsetY=0

Auflistung aller Conditions, die Helden handlungsunf�hig machen
    Condition1=9
    Condition2=11
    Condition4=1
Die Auflistung muss l�ckenlos sein. Der Condition4 - Parameter wird ignoriert, weil die 3 fehlt.

  ========== ConditionX: ==========
Die Condition mit der Datenbank-ID "X" hat die Einstellung "Action Restriction : No Action allowed".
Die Nummerierung muss mit 1 beginnen und durchg�ngig sein. Wenn Condition12 nicht vorhanden ist wird nach Condition13 und h�her nicht mehr gesucht.
Diese Konfiguration sollte entsprechend der Conditioneinstellungen gesetzt werden. Die h�chste erlaubte Condition-ID ist 500. Es findet keine Pr�fung statt, ob die ID in der Makerdatenbank vorhanden ist.

 ========== Probleme / Feedback: ==========
Bei Problemen, Fragen, R�ckmeldungen etc. wende dich einfach an mich, den Corti, am besten im RPG-Atelier per Privatnachricht
http://www.multimediaxis.de/members/4806-Corti

 ========== Todo: ==========
FF10-artige visualisierung des ATB-Fortschrittes durch Verschiebung des Icons in X/Y

* CC-Draw               - Icon zuf�gen
* Hero's Turn'          - Icon zuf�gen
* Selektiertes Monster  - Icon zuf�gen
