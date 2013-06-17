## Von serieller Kommunikation zum "Linux" auf dem Teensy

### Aufgabe 1 - serielle Kommuikation
- serielle Schnittstelle identifizieren / wie benutzen (Windows/Linux)
- Teensy als serielles Ger�t einstellen
- verbinden �ber putty (Port, baut-rate) 
- �bertragen von einzelnen Tastatureingaben (Buchstaben, evtl STRG+C, Pfeiltasten)
- Ziel: remote LED ein/ausschalten

### Aufgabe 2 - Eingabeverarbeitung und SD-Karte
- Arduino-Bibliothek f�r SD-Karte anschauen
- Beispiele ausprobieren: anlegen einer Datei, reinschreiben, l�schen

- mehrere Tastatureingaben in String zusammenfassen
- Befehle erkennen
- Ausnahmen erkennen: Backspace, ESC-Tasten, Pfeiltasten...
- Besonderheiten in Konsole: Farben, clear
- Ziel: console clear und in Farbe ausgeben


### Aufgabe 3 - "Linux" auf dem Teensy
- Implementierung anschauen & verstehen
- Ausprobieren, Grenzf�lle/Bugs/Issues finden
- neue Befehle, evtl grafische Ausgabe?
- Ziel: Tab-vervollst�ndigung






------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------


#### Vorbedinung:
	Teensy 2.0 mit SD Karte
	Source-Code "linux-challenge.ino"

#### Beschreibung:
	Dateien und Ordner auf der SD-Karte des Teensys k�nnen ausgelesen werden, ohne dass das Teensy als USB-Speicherger�t erkannt wird.
	Dies ist durch eine "Remote-Shell" �ber den COM-Port m�glich (z.B. mit dem Programm Putty).
	Wurde die Verbindung aufgebaut k�nnen �ber einige wenige Kommandos mit dem Teensy kommuniziert werden. (Beipiel: "ls","pwd","clear")
	
#### Aufgabe:
	- Verstehen wie die serielle Kommunikation funktioniert (alles innerhalb von "linux-challenge.ino")
	- Sich mit der SD-API des Teensys bekannt machen (SD.begin(), SD.open() ...)
	- Erweitern der Funktionalit�t durch folgende Befehle: 
		- "rm" - l�schen von Dateien
		- "mkdir" - anlegen von Ordnern
		- "touch" - anlegen von Dateien
		- "cat"   - ausgeben von Dateiinhalten
		
#### Ziel:
	- Proof of Concept: Dateien auf dem Teensy k�nnen bearbeitet werden, ohne dabei als USB-Speicherger�t zu fungieren
	- Kennenlernen von serieller Kommunikation sowie direktes Arbeiten einem Seriellen-Monitor (z.B. Putty)
	- Vertiefung von Linux/Unix "Datei-Befehlen" durch direkte Implementierung
	

#### Tipps:
	- http://ascii-table.com/ansi-escape-sequences.php
	- http://arduino.cc/de/Reference/SD
