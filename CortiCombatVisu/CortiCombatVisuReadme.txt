CortiCombatVisu DynRPG PlugIn V0.2

 ========== Author: ==========
Corti: Plugin 19.12.2013 für Innocentia.

 ========== Versionen: ==========
(V0.1) 19.12.13 - Erste Version. tut was es soll
(V0.2) 30.12.13 - Weiterentwickelt
    * Grafiken in Unterordner verschoben
    * einige Parameter deprecated
(V0.3) 11.05.14 - Spezialfeatures für Innocentia's Dark Sword
(V0.4) 24.02.15 - Animierter Monster & Heldenselektor
(V0.5) 18.08.22 - Refactoring

 ========== Zweck und Nutzen: ==========
Anzeige der Schlagreihenfolge im Kampfsystem
* In brauchbarem Maße präzise
* Position, Orienterung, und vieles mehr konfigurierbar. Bau deine eignen Grafiken ein für den einzigartigen Look

Zuerst die wichtigste Frage: Was ist es NICHT? Velsarbor, FF10, ein CTB-Kampfsystem. Mit aktuellen Mitteln ist CTB mit Vorschau der Schlagfolgenänderung nicht möglich.
Das Kampfsystem wird dadurch auch kein CTB System, es bleibt im Hintergrund ATB.
Ein 2k3-Kampfsystem ohne Plugins ist unglaublich lahmarschig, die ATB-Balken zu entfernen würde also zu langen, für den Spieler unergründlichn Wartezeiten führen.
Aus diesem und anderen Gründen empfehle ich wärmstens das CortiAtbSpeed-Plugin zu verwenden und damit die Schläge schnell nacheinander folgen zu lassen.

Da das Plugin nur auf Basis der ATB-Werte des Makers und der Agilität die Schlagfolge schätzt, kann es dazu kommen, dass sich die Reihenfolge ändert, was logisch erstmal nach einem Fehler aussieht.
Das liegt daran, dass der Maker die ATB-Leisten von Helden und Monstern nicht alle gleichzeitig füllt, sondern sich in den Momenten wenn Helden oder Monster dran sind Aussetzer genehmigt.
Diese Phänomene können durch das SlowWithinTurn-Feature meines CortiAtbSpeed-Plugins größtenteils umgangen werden, weshalb ich dieses Plugin anderen Speedplugins aus dem Netz gegenüber vorziehen würde.

 ========== Wichtiger Hinweis #1: ==========
Eure RPG_RT.exe sollte mit dem Fix "dynrpg_normal_skill_window_duration.ips" bearbeitet sein.
Erklärung: Das ursprüngliche DynRPG hat eine Verschlimmbesserung, bei der die Textbox [Skillname] wenn Monster Skills verwenden längen angezeigt wird. Diese Funktion korrumpiert die Eventverabreitung und sorgt für komische Effekte wenn Monster nacheinander dran sind.
Bei Verwendung von CortiAtbSpeed und CortiCombatVisu sollte der Fix auf jeden Fall installiert sein.

Link:
http://share.cherrytree.at/showfile-12977/dynrpg_normal_skill_window_duration.ips

Der Fix kann per DynPatches oder über ein IPS-Tool installiert werden.

 ========== Wichtiger Hinweis #2: ==========

Der ATB-Mode wird von diesem Plugin automatisch auf WAIT gesetzt und die Regelung verhindert eine effektive ACTIVE-Nutzung sowieso.
Um den Spieler und das System nicht unnötig zu verwirren, sollte das Umschalten des ATB-Modes im Menü deaktiviert sein.
-> System2 in der Makerdatenbank.

 ========== Grafische Daten: ==========

>>>>> Frage: Wie bekomme ich den freien Platz unten am Bildrand, ich hab da die ATB-Leisten der Helden und höhere Portraits?
>>>>> Antwort: Ein eigenes System2-Set auf dem die ATB-Sachen leer sind und kleinere Facesets.

Alle Ressourcen sind im Ordner "Projekt\DynRessource\CortiCombatVisu"

>> Hintergrund:
Es ist möglich eine Grafik als Rahmen anzuzeigen. Der Name der Grafik und ihre Position kann konfiguriert werden.
>> Heldenicons:
Die Grafik HeldenCombatVisu.png enthält die Portraits der Helden in der Reihenfolge die der Datenbank entspricht.
>> Monstericons
Im Unterordner \Monster befinden sich Icons für spezielle Monster. Der Name enthält die Datenbank-Id.
Wenn für ein Monster keine spezielle Datei vorhanden ist, wird die DefaultDatei verwendet.
>> Monsterzahlen
Um die Monster unterscheiden zu können, wird über dem Monstericon eine Zahl angezeigt. Die Zahlen eins bis acht sind in der MonsterNumbers.png hinterlegt. Die Position der Zahl auf dem Monster ist konfigurierbar.
>> Selektor / Highlight des ausgewählten Helden/Monsters
Es kann eine Grafik dafür konfiguriert werden. Siehe Konfiguration.

>>>>> Frage: Darf ich die Grafiken benutzen?
>>>>> Antwort: Sind Velsarbor-Plagiate im RTP-Look, warum solltest du es wollen?

 ========== Besonderes zu Conditions: ==========
Conditions, die dem Spieler die Kontrolle über die Helden entziehen ( Schlaf, Betäubung etc. ), frieren die Atb-Leiste des Helden ein. Bei Monstern ist dies nicht der Fall. Ihre (unsichtbaren) Atb-Leisten füllen sich weiter und ihre Handlung wird automatisch als "no Action" abgewickelt. Dadurch, dass Helden einfrieren kann es vorkommen, dass ein Held, der fast volles ATB hat er wesentlich später dran kommt.
Da es nicht möglich ist, zu schätzen, wann ein Held der aktuell ausgeknockt ist wieder an der Reihe ist, werden Helden mit kontrollentziehenden Conditions ans Ende der Leiste sortiert.
Zum jetzigen Stand von DynRPG ist es nicht möglich, die Einstellungen von Conditions auszulesen. Aus diesem Grund ist es notwendig, die IDs von Conditions, die dem Spieler die Kontrolle entziehen manuell aufzulisten.
-> Siehe Konfiguration:

 ========== Konfiguration: ==========
Die Anzahl anzuzeigender Icons. Minimum sind 6. Maximal 4 können davon Helden mit Kontrollverlust zugeordnet werden.
    NumberOfShownIcons=10

Position des ersten unverschobenen Icons in X und Y.
    PositionXOriginal=6
    PositionYOriginal=224

Das Icon der Kampfteilnehmers, der als nächster dran ist kann ein paar Pixel von den anderen abgesetzt werden. Bedenke diese Einstellungen, wenn du das Gefühl hast die Positionseinstellung würde dich irreführen. Der Positionsurpsrung bezieht sich auf den unverschobenen Ort vom ersten Icon.

Verschiebung des ersten Icons in X zu den anderen
    IconsOffsetX=-2
Verschiebung des ersten Icons in Y zu den anderen
    IconsOffsetY=0

Diese Einstellungen beschreiben den Abstand zwischen den Icons in der Auflistung

Abstand zwischen den Icons in X
    IconSpaceBetweenX=31
Abstand zwischen den Icons in X
    IconSpaceBetweenY=0

Die Größe der Heldenicons kann frei gewählt werden. Wichtig ist nur, dass sie wie im Beispiel in aufsteigender Datenbank-ID ohne Lücken in der Grafik sind.

Größe der Heldenicons in der Grafik
    HeroIconSizeX=24
    HeroIconSizeY=15
Abstand in der Grafik in Y zwischen den Icons der Helden
    HeroIconOffsetY=16

Position der Zahlen der Monster-Id auf den Monstericons relativ zur Position des Monstericons
    NumberOffsetToIconX=22
    NumberOffsetToIconY=4

Ausmaße einzelner Zahlenicons in der Grafik
    NumberSizeX=7
    NumberSizeY=7
Abstand der Zahlenicons zueinander
    NumberOffsetInImage=8

Dateiname der Datei, die als Hintergrund dienen soll
    BackgroundFile=DynRessource\CortiCombatVisu\CortiCombatVisuBG.png
Position des Hintergrundes
    BackgroundPositionX=0
    BackgroundPositionY=224

Cursor auf ausgewählten Monstern:
Zu zeigende Grafik.
    MonsterSelectorFile=DynRessource\CortiCombatVisu\Selektor.png

Offset der Grafik zum Slot auf dem sie gezeigt werden in Pixeln.
    MonsterSelectorOffsetX=0
    MonsterSelectorOffsetY=0

Anzahl Animationsframes in der Grafik. Die Frames müssen in einer Reihe von oben nach unten angeordnet sein.
    MonsterSelectorFramesMax=11;

Die Icons von Helden mit Kontrollverlust können optisch etwas von den anderen weggerückt sein.

Verschiebung der CC-Icons in X zu den anderen
    ConditionAfflictedOffsetX=10
Verschiebung der CC-Icons in Y zu den anderen
    ConditionAfflictedOffsetY=0

Auflistung aller Conditions, die Helden handlungsunfähig machen
    Condition1=9
    Condition2=11
    Condition4=1
Die Auflistung muss lückenlos sein. Der Condition4 - Parameter wird ignoriert, weil die 3 fehlt.

  ========== ConditionX: ==========
Die Condition mit der Datenbank-ID "X" hat die Einstellung "Action Restriction : No Action allowed".
Die Nummerierung muss mit 1 beginnen und durchgängig sein. Wenn Condition12 nicht vorhanden ist wird nach Condition13 und höher nicht mehr gesucht.
Diese Konfiguration sollte entsprechend der Conditioneinstellungen gesetzt werden. Die höchste erlaubte Condition-ID ist 500. Es findet keine Prüfung statt, ob die ID in der Makerdatenbank vorhanden ist.

 ========== Probleme / Feedback: ==========
Bei Problemen, Fragen, Rückmeldungen etc. wende dich einfach an mich, den Corti, am besten im RPG-Atelier per Privatnachricht
http://www.multimediaxis.de/members/4806-Corti

 ========== Todo: ==========
FF10-artige visualisierung des ATB-Fortschrittes durch Verschiebung des Icons in X/Y

* CC-Draw               - Icon zufügen
* Hero's Turn'          - Icon zufügen
* Selektiertes Monster  - Icon zufügen
