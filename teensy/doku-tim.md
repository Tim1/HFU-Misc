Teensy Doku
===========

Windows shutdown
--------------------
#### Idee
Die Idee entwickelte sich beim ausprobieren der Features des Teensy. Nachdem Tastatureingaben ohne Probleme mithilfe von sehr wenig Programmcode möglich waren, stellte sich die Frage wie man damit einfach eine vorzeigbare Aktion machen könnte.
Da ein Öffnen der Kommandozeile sehr einfach ist, war die Idee den Windowsrechner über die Befehler herunterzufahren.
Dadurch ist gut präsentierbares und vor allem schadfreies Verhalten des Teensy geschaffen.


##### Hinführung
Wie schon oben erwähnt hatte kam die Idee beim Ausprobieren des Teensy zustande. 
Dazu hatte ich versucht verschiedene Dinge mithilfe der Tastatureingaben zu simulieren (Schreiben im Editor, Drücken von "Spezialtasten" wie STRG oder Windows-Taste)
Über die Tastenkombination WIN+R wird unter Windows das "Ausführen-Fenster" geöffnet. Hier kann über den Befehl "cmd" und bestätigung durch Enter, die Kommandozeile geöffnet werden.
Nun kann das Teensy jegliche Befehle ausführen, unter anderem auch "shutdown", welcher zum Herunterfahren des Rechners führt. Über die Parameter `???` wird dies auch erzwungen ohne auf die Bestätigung des Users zu warten.

Für diesen kleinen Sketch muss das Teensy in der Arduino-IDE lediglich auf Eingabemodus "USB-Tastatur" eingestellt sein.


#### Probleme & Lösung
Da diese Aufgabe sehr simpel war gab es hier keine ernsthafen Probleme.
Der einzige Wehrmutstropfen bei der Präsentation dieses Sketches ist, dass unter Windows erst recht lange Tastatur-Treiber für das Teensy installiert werden. Das schadet natürlich den Effekt beim Vorstellen. Sobald das Teensy jedoch einmal initialisiert wurde, fällt dieser Schritt jedoch weg.


#### Ergebnis
Als Ergebnis haben wir nun einen Szenario, indem das Teensy eingesteckt wird, danach eine Kommandozeile öffnet und den Rechner herunterfährt.
Der Code befindet sich im Anhang unter `win_shutdown.ino`
 


"Linux" auf dem Teensy
-----------------------
#### Idee
- serielle Kommunikation
- SD Kartenzugriff ohne als Speichermedium erkannt zu werden
- Linux-artige Shell haben (alle Befehle selbst implementiert)
- Beschäftigung mit: Seriell, ASCII (Zeichencodierung, Steuerzeichen...), Linux, arduino-Bibliotheken (z.B. für SD)


#### Hinführung
**Ursprung**
- Vorhaben serielle Kommunikation ausprobieren
- Da serieller Monitor von Arduino IDE nicht so gut --> Putty
- Putty erinnert an remote-shell --> Idee genau das zu bauen

**Vorgehen:**
- Entwicklung direkt mit Putty
- serielle Kommunikation gut testen, zeichen für zeichen lesen:
```
		while (Serial.available()) {
			// get the new byte
			char inChar = (char)Serial.read();
			...
		}
```
- eingebene Zeichen `inChar` über `Serial.print(inChar)` ausgeben. Achtung bei Backspace (ASCII 127), löscht alles in Putty / Steuerzeichen bestehend aus Zeichenfolge, siehe unten
- einkommende Zeichen immer an String `input` appenden, bei Newline (`\n` oder `\r` input auswerten)
- String auswerten in `processCmd()` Beispiel: _mkdir testdir_:
	- parsen: in CMD und argumente einteilen (bei Leerzeichen splitten: eigene Funktion `splitString` da von Arduino nicht bereitgestellt)
	- CMD mit vorhandenen Befehlen vergleichen (switch artiger Konstrukt mit vielen if, else if bedingungen) und dann den entsprechenden if-Block ausführen bzw. eigene funktion aufrufen + argumente (Übersicht), "unknown command" wenn nicht bekannt
	- nach befehl abarbeitung evtl. entsprechende Rückmeldung an den user
	- wenn fertig: aktuellen `input` löschen und in neuer Zeile den Promt anzeigen `newCmd()`
- LED blinkt 1ms bei jedem Zeichen `blink(1)` als zusätzliche rückmeldung für user
- besonderes Handeling für Steuerzeichen, Beispiel Strg^C oder Pfeiltasten
	- es werden 3 ASCII zeichen pro aktion gesende, für Pfeiltaste: ESC(27) + "[" (91) + A,B,C,D [1]
	- Zeichen müssen in while-schleife abgefangen werden und nicht weiter verarbeitet werden. (sonst z.B. mit pfeiltaste in Console rumfahren) 


#### Probleme & Lösung
**Probleme:**
- Schwierigkeiten bei Entwicklung: alle Eingaben müssen wieder ausgegeben werden
- serieller Port unter Windows belegt solange Monitor (Putty) läuft
- manchmal char* gefragt meistens aber String vorhanden

**Lösung:**
- senden von Keys einzelnd (gut) testen vor implementieren von Befehlen
- Putty muss beendet werden, bevor upgeloaded 
- Funktion `char* toChar(String str)` zum Umwandeln von String --> char*

#### Ergebnis
- sofort funktionierende, einfache, strukturierte serielle Kommunikation (z.B. mit putty)
- linux-artige Bediehnung (viele Befehle)
- zugriff auf SD-Karte ohne für Host als Speichermedium erkannt zu werden.

**Ausblick:**
- evtl. serielle Kommunikation über Kommandozeile (ohne putty)
- erweitern des "Linux": mehr befehle, tab-vervollständigung, fehler finden/beheben. Weitere Anwendungsfälle finden, vieles mit Arduino möglich: auf Boards mit Ethernet z.B. Webserver möglich [2]

[1] http://ascii-table.com/ansi-escape-sequences.php
[2] http://arduino.cc/en/Tutorial/WebServer









