CortiLogs DynRPG PlugIn V0.2

 ========== Author: ==========
Corti 16.02.2015

 ========== Versionen: ==========
(V0.1) 16.02.2015 - Beginn des Projektes
(V0.1) 23.02.2015 - Aufsplittung des Projektes in CortiLogs und CortiEventTrace. Die Event-Trace-Funktion hat eher Debugging-Natur und sollte zum Release nicht mitveröffentlicht werden. CortiLogs hingegen taugt als Fehlerdiagnose- und Feedbackinstrument.

 ========== Funktionen: ==========
Eigene Logzeilen per Kommentarkommando aus dem EventCode in eine Textdatei schreiben. Dabei können die Inhalte von Variablen mit raus gegeben werden. 

Hin und wieder kann es in jeder Software passieren, dass Fehler auftreten. Falsche Parameter, falsche Aufrufe, falsche Reihenfolge. Üblicherweise sind es eher die Tester als der Entwickler, die das Spiel auf eine Weise benutzen, die den Fehler auslöst. Ich empfinde es als ungünstig, einem Spieler eine MessageBox mit der Aussage "Hey, wir haben ein Fehler, sag mal dem Entwickler bescheid!" vor die Nase zu setzen. Komfortabler wäre es doch, solche Ereignisse automatisch zu protokollieren. Tester des Spieles müssten dann nur noch die LogDatei an den Entwickeler schicken. Besonders nützlich ist das Plugin natürlich, wenn ein Entwickler nicht nur das Auftreten eines Fehlers protokolliert, sondern auch gleich die Werte von im EventScript benutzten Variablen mit rauszuschreiben. 

Selbstverständlich ist auch Fehler-Logging kein Ersatz dafür, Code ausgiebig zu testen, sowohl auf Funktion, also auch darauf, gezielt Fehler auszulösen wenn der Code mit falschen Daten gefüttert wird.

Eine weitere Anwendung ist es, um zu schauen, wie Tester das Spiel spielen, zB welchen Level sie an gewissen Stellen haben, wieviel Gold sie besitzen. Mit einer kleinen Kommentarzeile wird jeder Testspieler zu einem Stück Statistik und kann helfen, das Spiel zu verbessern, ohne dabei selbst viel selber tun zu müssen, sofern entsprechend LogEinträge gesetzt werden.

Die Datei ist unter dem Namen "CortiLogs.txt" zu finden.

Systemeintragungen:
Spielstart, Spielende, Speichern und Laden.

 ========== Anwendung: ==========
Es gibt bisher zwei Kommentarkommandos. @corti_log und @corti_error. Diese unterscheiden sich nur über das Prefix in der Logzeile, um nachher besser nach Error-Einträgen suchen zu können.

Beispiele:

@corti_log "Number input into Variable 20 is:", V20
2015.02.24-23:56:56 [LOG] Number input into Variable 20 is: 33

@corti_error "Number input into Variable 20 is bad value:", V20
2015.02.24-23:56:53 [ERROR] Number input into Variable 20 is bad value: 0

DynRPG unterstützt maximal 100 Kommentarkommandoparameter. Dieses Plugin liest diese aus und schreibt sich in die Datei. Parameter werden durch Kommas voneinander abgegrenzt.

Beispiel:
@corti_log "ich bin ein text", 123, Ich bin Token, V123.

Parameter 1 ist eine Zeichenkette, die als "ich bin ein text" rausgeschrieben wird.
Parameter 2 ist die Zahl 123.
Parameter 3 ist ein Token. Dieses wird als Zeichenkette "ichbintoken" rausgeschrieben.
Parameter 4 ist die Zahl, die in Variable 123 zu finden ist.

 ========== Dokumentation DynRPG Special Comments: ==========
Quelle: http://rpg-maker.cherrytree.at/dynrpg/guidelines.html

Example for a "special" comment:
@FooBar 123, "abc", V55, VV66, N7, NV8, Nothing

The command name is foobar.
The first parameter is numerical.
The second parameter is a string.
The third parameter is a numerical value read from variable #55.
The fourth parameter is a numerical value read from the variable whose ID is stored in variable #66.
The fifth parameter is a string, read from the name of actor #7.
The sixth parameter is a string, read from the name of the actor whose ID is stored in variable #8.
The seventh parameter is a token named nothing.
