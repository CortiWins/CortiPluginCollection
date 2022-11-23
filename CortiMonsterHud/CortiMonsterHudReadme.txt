CortiMonsterHud DynRPG PlugIn V0.5

 ========== Author: ==========
Corti ( Auf Basis von Corti's SD3x aka. "Untitled" Projekt )

Todo: Transparenz auf Basis von Variable

 ========== Versionen: ==========
V0.1 (06.12.13) Erste Version - tut was es soll
V0.2 (09.12.13) Fix: Crash division by zero wenn Monster 0 MaxMana haben, Code zum Abfangen war defekt.
V0.3 (12.12.13) Zusätzliche Ausgabe für nix existierende Konfig oder fehlende Grafikdate
V0.4 (27.12.13) Zusätzliche Option: Nur Anzeige des HUDs bei analysierten Feinden.
                Zusätzliche Option: Nur Anzeige des HUDs bei Feinden, die grad ausgewählt sind
V0.5 (24.02.15) Fix: GlobalOffsetPercOfSizeY wurde auf X-Achse angewandt.

 ========== Zweck und Nutzen: ==========

Das Plugin dient dazu Leben, Mana und Atb als Leiste über den Köpfen der Gegner anzuzeigen.
Bei Veränderung des HP und Manastandes wird die grafische Änderung als flüssige kleine Animation dartgestellt.
Smoothes ein- und ausblenden.
Keines der drei Dinge MUSS angezeigt werden, alles ist separat (de)aktivierbar.
Es besteht die Möglichkeit von nur analysierten oder gerade fokussierten Zielen die HP anzuzeigen.
Die Darstellung ist recht frei konfigurierbar. Vom Starcraft-Blockbalken zum typischen Farbverlaufstrich, beides möglich.

 ========== Konfiguration: ==========
Die Konfiguration ist in die DynRPG.ini einzutragen. Eine Konfiguration kann wie folgt aussehen.

 ========== Neu![V0.4] Zusätzliche Option:  ==========
Nur Anzeige des HUDs bei analysierten Feinden.
Hierzu ist der Konfigeintrag "AnalysisRequiredSwitchId" zu verwenden. Der verwendete Parameter ist der erste Slot in dem SwitchArray das den MonsterAnalysestatus enthält.
D.h. Bei z.B. 61 ist der Zustand von Monstertyp1 auf Variable 61,  von Monstertyp2 auf Variable 62.

 ========== Wichtig:  ==========
 Das Plugin kann nicht erkennen, ob die Switches anderswo verwendet werden, wenn also die Monsterdatenbank 200 Einträge hat,  dann sollten Switch 61 bis 261 für Monsterflags reserviert sein.
-> Zusammenarbeit mit CortiAnalyse durch verwenden des selben Switcharrays bietet sich an.

[CortiMonsterHud]
; 1 = Hud wird nur bei den vom Zielcursor ausgewählten Monstern angezeigt, 0 = the other way
SelectionRequired=1
; 1= HUD-Element werden auf dem Monster gezeichnet 0 = Anzeigen im Overlay.
DrawOnMonsters=0
; ACHTUNG: Wenn diese Einstellung >1 ist, werden Anzeigen nur gezeigt, wenn das Monster schon analysiert wurde. Siehe Readme.
AnalysisRequiredSwitchId=0
; Dient dazu zu steuern, wie schnell sich die Life und Manabalken dem Istwert anpassen. Dieser Wert bestimmt die Geschwindigkeit der Animation
BarPartFrameChangeDelay=3
; Das Hud wird in die obere Linke Ecke der Monstergrafik gezeichnet. Die folgenden Settings beeinflussen das. Negative Werte verwenden für andere Richtung.
; Absolute Verschiebung nach Rechts in Pixeln
GlobalOffsetX=0
; Absolute Verschiebung nach Unten in Pixeln
GlobalOffsetY=0
; Absolute Verschiebung nach Rechts in Prozent der Breite der Monstergrafik
GlobalOffsetPercOfSizeX=20
; Absolute Verschiebung nach Unten in Prozent der Höhe der Monstergrafik
GlobalOffsetPercOfSizeY=10
; Lebensbalken anzeigen (1) oder nicht zeigen (0)
ShowLife=1
; Manabalken anzeigen (1) oder nicht zeigen (0)
ShowMana=1
; Atkbalken anzeigen (1) oder nicht zeigen (0)
ShowAtb=1
; Dateiname der Grafik, die alle Hud-Elemente enthält
GraphicsFile=DynRessource\\MonsterHudPlugin.png
; // Hintergrund. Grafische Elemente um die Anzeigebalken herum können als Hintergrund angezeigt werden.
; Verschiebung nach Rechts in Pixeln, relativ zu der vorher berechneten Position
BackgroundPositionOffsetX=0
; Verschiebung nach Unten in Pixeln, relativ zu der vorher berechneten Position
BackgroundPositionOffsetY=0
; Position des grafischen Elementes in der Grafikdatei
BackgroundXinImage=0
BackgroundYinImage=5
; Ausmaße des grafischen Elementes in der Grafikdatei
BackgroundWidthInImage=1
BackgroundHeightInImage=13
; // Lifebar
; Verschiebung in Pixeln, relativ zu der vorher berechneten Position
LifebarPositionOffsetX=1
LifebarPositionOffsetY=0
; Position der gefüllten Hp-Leiste auf der Grafik
LifebarFilledXinImage=1
LifebarFilledYinImage=5
; Position der leeren Hp-Leiste auf der Grafik
LifebarEmptyXinImage=1
LifebarEmptyYinImage=0
; Höhe der HP-Leisten
LifebarHeightInImage=4
; Anzahl an Abschnitten im Lebenspunktebalken
LifebarPartsMax=15
; Breite eines an Abschnittes im Lebenspunktebalken
LifebarPartWidthPx=3
; INFO: Die Breite der HP-Leiste auf der Grafik sollte ( LifebarPartsMax * LifebarPartWidthPx ) sein.
; Beispiel 1 zeigt eine Starcraft-Artige HP-Leiste
; Beispiel 2 zeigt eine eher Makermässige HP-Leiste

; // Manabar
ManabarPositionOffsetX=1
ManabarPositionOffsetY=5
ManabarFilledXinImage=1
ManabarFilledYinImage=10
ManabarEmptyXinImage=1
ManabarEmptyYinImage=0
ManabarHeightInImage=4
ManabarPartsMax=15
ManabarPartWidthPx=3
; // AtbBar
AtbbarPositionOffsetX=1
AtbbarPositionOffsetY=10
AtbbarFilledXinImage=1
AtbbarFilledYinImage=15
AtbbarEmptyXinImage=1
AtbbarEmptyYinImage=0
AtbbarHeightInImage=4
AtbbarPartsMax=15
AtbbarPartWidthPx=3

 ========== How to test it: ==========
Im Testprojekt sind zwei Varianten hinterlegt. Um zwischen ihnen zu wechseln muss in der DynRPG.ini der einer der Konfigblöcke in [CortiMonsterHud] und der andere in etwas anderes benannt werden.

 ========== Probleme / Feedback: ==========
Bei Problemen, Fragen, Rückmeldungen etc. wende dich einfach an mich, den Corti, am besten im RPG-Atelier per Privatnachricht
http://www.multimediaxis.de/members/4806-Corti
