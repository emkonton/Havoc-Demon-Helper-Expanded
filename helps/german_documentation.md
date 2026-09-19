# Havoc Demon - Erweiterte Befehlsdokumentation (Deutsch)

Originalprojekt-Link: [https://github.com/havocframework/havoc](https://github.com/havocframework/havoc)

---

*(Hinweis: Diese Dokumentation folgt der Struktur der englischen Basisdokumentation. Um die Länge übersichtlich zu halten, sind hier die Kernbefehle ausführlich auf Deutsch übersetzt. Alle Befehle teilen dieselbe Syntax.)*

### help
Zeigt die Hilfemeldung des angegebenen Befehls an.
**Verwendung:** `help [befehl]`
Listet systeminterne Hilfe- und Verwendungsdetails für jeden im Demon-Agenten vorhandenen Befehl auf. Wenn kein Parameter eingegeben wird, wird die Liste aller Befehle zurückgegeben.
**Beispiele:**
- `help`
- `help token`

### sleep
Legt die Schlafverzögerung und den Jitter fest.
**Verwendung:** `sleep [verzögerung] (jitter)`
Bestimmt das Check-in-Intervall des Demons beim Teamserver. Der Parameter "Jitter" wird in Prozent angegeben und hilft, sich vor Sicherheitssystemen zu verbergen, indem er das regelmäßige Verkehrsmuster stört.
**Beispiele:**
- `sleep 10`
- `sleep 60 15`

### proc list
Zeigt eine Liste der laufenden Prozesse auf dem Zielsystem an.
**Verwendung:** `proc list`
Listet detailliert die derzeit aktiven Prozesse (Prozess-ID, Name, Architektur usw.) auf dem Zielcomputer auf.
**Beispiele:**
- `proc list`

### shell
Führt cmd.exe-Befehle aus und ruft die Ausgabe ab.
**Verwendung:** `shell [befehle]`
Führt Befehle über die Windows-Eingabeaufforderung (cmd.exe) aus. Die Ausgabe wird direkt an den Operator zurückgeleitet.
**Beispiele:**
- `shell dir c:\windows\system32`

### token steal
Stiehlt ein Token aus dem angegebenen Prozess.
**Verwendung:** `token steal [pid] (handle)`
Stiehlt das Token eines hochprivilegierten Prozesses und speichert es zur späteren Verwendung im Identitätstresor (Vault).
**Beispiele:**
- `token steal 1337`

---
Originalprojekt-Link: [https://github.com/havocframework/havoc](https://github.com/havocframework/havoc)