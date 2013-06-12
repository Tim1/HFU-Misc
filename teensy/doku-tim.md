Teensy Doku
===========

Windows shutdown
--------------------
#### Idee
- Potenzial zeigen
- Eindruck ohne Schaden 


##### Hinführung
?

#### Probleme & Lösung
- sehr simpel (keine Probleme)
- Windows muss Treiber installieren -.-


#### Ergebnis
- Teensy wird eingesteckt, öffnet cmd, fährt Computer runter
- Code: siehe `win_shutdown.ino`
 


"Linux" auf dem Teensy
-----------------------
#### Idee
- serielle Kommunikation
- SD Kartenzugriff ohne als Speichermedium erkannt zu werden
- Linux-artige Shell haben (alle Befehle selbst implementiert)
- Beschäftigung mit: Seriell, ASCII (Zeichencodierung, Steuerzeichen...), Linux, arduino-Bibliotheken (z.B. für SD)


#### Hinführung
Das war die Hinführung


#### Probleme & Lösung
**Probleme:**
- Schwierigkeiten bei Entwicklung: alle Eingaben müssen wieder ausgegeben werden
- serieller Port unter Windows belegt solange Monitor (Putty) läuft

**Lösung:**
- senden von Keys einzelnd (gut) testen vor implementieren von Befehlen
- Putty muss beendet werden, bevor upgeloaded 

#### Ergebnis
- sofort funktionierende, einfache, strukturierte serielle Kommunikation (z.B. mit putty)
- linux-artige Bediehnung (viele Befehle)
- zugriff auf SD-Karte ohne für Host als Speichermedium erkannt zu werden.

**Ausblick:**
- evtl. serielle Kommunikation über Kommandozeile (ohne putty)
















 
