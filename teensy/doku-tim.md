Teensy Doku
===========

Windows shutdown
--------------------
### Idee
Die Idee entwickelte sich beim ausprobieren der Features des Teensy. Nachdem Tastatureingaben ohne Probleme mithilfe von sehr wenig Programmcode möglich waren, stellte sich die Frage wie man damit einfach eine vorzeigbare Aktion machen könnte.
Da ein Öffnen der Kommandozeile sehr einfach ist, war die Idee den Windowsrechner über die Befehler herunterzufahren.
Dadurch ist gut präsentierbares und vor allem schadfreies Verhalten des Teensy geschaffen.


### Hinführung
Wie schon oben erwähnt hatte kam die Idee beim Ausprobieren des Teensy zustande. 
Dazu hatte ich versucht verschiedene Dinge mithilfe der Tastatureingaben zu simulieren (Schreiben im Editor, Drücken von "Spezialtasten" wie STRG oder Windows-Taste)
Über die Tastenkombination WIN+R wird unter Windows das "Ausführen-Fenster" geöffnet. Hier kann über den Befehl "cmd" und bestätigung durch Enter, die Kommandozeile geöffnet werden.
Nun kann das Teensy jegliche Befehle ausführen, unter anderem auch "shutdown", welcher zum Herunterfahren des Rechners führt. Über die Parameter `???` wird dies auch erzwungen ohne auf die Bestätigung des Users zu warten.

Für diesen kleinen Sketch muss das Teensy in der Arduino-IDE lediglich auf Eingabemodus "USB-Tastatur" eingestellt sein.


### Probleme & Lösung
Da diese Aufgabe sehr simpel war gab es hier keine ernsthafen Probleme.
Der einzige Wehrmutstropfen bei der Präsentation dieses Sketches ist, dass unter Windows erst recht lange Tastatur-Treiber für das Teensy installiert werden. Das schadet natürlich den Effekt beim Vorstellen. Sobald das Teensy jedoch einmal initialisiert wurde, fällt dieser Schritt jedoch weg.


### Ergebnis
Als Ergebnis haben wir nun einen Szenario, indem das Teensy eingesteckt wird, danach eine Kommandozeile öffnet und den Rechner herunterfährt.
Der Code befindet sich im Anhang unter `win_shutdown.ino`
 


"Linux" auf dem Teensy
-----------------------
### Idee
Eine erste Idee entwickelte sich aus dem Testen der seriellen Schnittstelle und der Kommunikation mit einem Host-System. Als es schließlich bei der Entwicklung unter Verwendung von Windows immer wieder störende Meldungen gab, dass das Speichermedium nicht ordnungsgemäß entfernt wurde, kam die Idee das Teensy lediglich als serielles Gerät erkennen zu lassen.
Somit wird vom Host-System nicht erkannt, dass hier ein Speichermedium angeschlossen ist. Dennoch ist die SD-Karte programatisch auf dem Teensy ansprechbar.
Da nun die SD-Karte nur noch direkt vom Teensy selber bekannt ist muss jede Aktion mithilfe von Teensy-Programmcode realisiert werden. Nun lag es nahe sich an den von Unix/Linux bekannten Befehlen für die Nutzung eines Filesystems zu orientieren. Dabei wurden diese einzelnde Befehle ("ls" zum anzeigen des aktuellen Verzeichnisses, "cd <directory>" zum Navigieren innerhalb von Verzeichnissen, "pwd" zur Ausgabe des aktuellen Pfades u.v.m) mithilfe von Arduino-Code implementiert. 

Ziel dieses Szenarios ist eine 3-teilige Praktikumsreihe machen beidem sich der Student mit folgendem beschäftigen soll: 
- serielle Kommunikation mithilfe von Monitoren (z.B. putty)
- Zeichencodierung (ASCII, Steuerzeichen etc.)
- Verwendung von Arduino Bibliotheken für die Nutzung der SD-Karte
- Linux-Befehle


### Hinführung
#### Ursprung
Wie im obigen Abschnitt schon kurz erwähnt wurde entwickelte sich das nun recht umfangreiche Szenario ursprünglich aus dem Vorhaben die serielle Kommunikation zu testen. 
Da der in der Arduino IDE integrierte serielle Monitor leider nicht besonders gut war, wurde das bekannte Programm Putty als Ersatz getestet. Dies funktionierte auch gleich deutlich besser. 
Dabei erinnerte das Fenster stark an eine Remote-Shell Verbindung, was dann sofort zu der Idee führte genau eine solche "Shell" für das Teensy zu bauen.

#### Vorgehen
Die Entwicklung setzte ab diesem Zeitpunkt nur noch auf Putty als seriellen Monitor und die Arduino IDE als Umgebung.
Wichtig war es die serielle Kommunikation gut zu testen, da alles weitere darauf aufbauen sollte. 
Dazu wurde in einer while-schleife Zeichen für Zeichen aus der eingehenen Verbindung gelesen:

```
		while (Serial.available()) {
			// get the new byte
			char inChar = (char)Serial.read();
			...
		}
```

Um dem User bei seinen Eingaben Rückmeldung zu geben werden alle eingegeben Zeichen `inChar` über `Serial.print(inChar)` wieder ausgeben.
Doch jegliche Zeichen sofort wieder zum Host zu schicken ist jedoch auch problematisch. Beispielsweise für ASCII-Wert 127 "Backspace" dazu, das jegliches vorheriges Zeichen gelöscht wird. In den meisten Fällen sollen jedoch nur die direkt vom User eingegeben Buchstaben gelöscht werden, nicht jedoch die vom Teensy ausgegeben Zeichen, wie z.B. das Promt "Teensy / > ". Ähnliches gilt es bei vielen Steuerzeichen, z.B. führen die Pfeiltasten dazu den Curser frei im Fenster zu bewegen, was in unserem Fall auch nicht gewünscht war. Daher mussten für einige Eingaben spezielle Behandlungen geschaffen werden.

Doch im Allgemeinen werden die Eingaben des Users buchstabenweise an den String `input` angefügt (bei "Backspace" entsprechend gelöscht). Bei dem Senden von "Newline" (`\n` oder `\r`) wird dieser String dann in der Funktion `processCmd()` ausgewertet.
Nun wird der String erst in den Befehl und die Argumente geparst. Der Befehl-String wird dann mit den vordefinierten Strings in einem großen if-elseif-Block vergleichen. Nun wird der entsprechene if-Block ausgeführt welcher im Regelfall eine neue Funktion mit der implementierten Funktionität ausführt. Dies wird hoffentlich im folgenden Beispiel klarer:

```
if()
mkdir()
```

Nach der Abarbeitung des Befehls wird dem User in den meisten Fällen eine Rückmeldung über die durchgeführte Aktion gegeben und in einer neuen Zeile wird der Promt erneut angezeigt (`newCmd()`), der String `input` zurückgesetzt und die Konsole ist bereit für den nächsten Befehl.

Wird kann ein Eingabestring nicht zu einem Befehl zugeordnet werden so wird "unkown command: <eingabe>" ausgegeben. Als zusätzliche Rückmeldung für den User blinkt die LED bei jedem eingegeben Zeichen.


### Probleme & Lösung
#### Probleme
Schwierigkeiten gab es ganz am Anfang mit der grundlegenden seriellen Kommunikation. Da die Eingaben, welche innerhalb von Putty getätigt wurden, nicht von selbst angezeigt wurden, konnte man anfangs nur "blind" schreiben. Das daher alle Eingaben echoartig gleich wieder zurückgesendet wurden war zwar naheliegend, doch vor allem durch Sonder und Steuerzeichen ("Backspace", Pfeiltasten etc.) kam es anfänglich zu Irritationenen.

Genau diese Steuerzeichen waren auch für eine weitere Schwierigkeit verantwortlich, nämlich bei der Reaktion auf bestimmte Kommandos. Aus der Unix/Linux Umgebung ist beispielsweise die Tastenkombination "STRG+C" (STRG^C) zum Abbrechen oder Pfeiltaste-nach-Oben zur wiederholung der letzten Befehle bekannt. Beide genannten Befehle wurden implementiert, was dadurch verkompliziert wurde, dass jeweils 3 zusammengehörige Byte (char) gesendet wurden. Für die Pfeiltaste-nach-Oben sind das z.B. "ESC" (ASCII: 27) + "[" (ASCII: 91) + "A" (ASCII: 65). [1]
Das Abfangen dieser Steuerzeichen ist aber notwendig, da sonst hier beispielsweise mit den Pfeiltasten der Curser herumgefahren werden kann, was so natürlich nicht vorgesehen ist.

Ein weiteres Windows-spezifisches Problem war die blockierene Belegung des seriellen Ports durch Putty. Den solange der serielle Monitor läuft ist ein erneutes Kopilieren des Sketches nicht möglich. Unter Linux war das Problem insofern nicht vorhanden, da durch das neukompilieren Putty automatisch beendet wurde.

Eine kleine Progammiertechnische Hürde war das uneinheitliche Verwenden von `String` und `char*` in den Arduino-Bibliotheken. Dies wurde aber einfach mit der Implementierung einer kovertierenden Funtkion `char* toChar(String str)` gelöst.
- manchmal char* gefragt meistens aber String vorhanden


### Ergebnis
- sofort funktionierende, einfache, strukturierte serielle Kommunikation (z.B. mit putty)
- linux-artige Bediehnung (viele Befehle)
- zugriff auf SD-Karte ohne für Host als Speichermedium erkannt zu werden.

### Ausblick:
- evtl. serielle Kommunikation über Kommandozeile (ohne putty)
- erweitern des "Linux": mehr befehle, tab-vervollständigung, fehler finden/beheben. Weitere Anwendungsfälle finden, vieles mit Arduino möglich: auf Boards mit Ethernet z.B. Webserver möglich [2]

[1] http://ascii-table.com/ansi-escape-sequences.php
[2] http://arduino.cc/en/Tutorial/WebServer









