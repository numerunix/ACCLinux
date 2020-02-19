# ACCLinux
Assistant Computer Control for Linux

Assistant Computer Control è una Utility che consente tramite Google Assistant o Alexa di eseguire operazioni sul computer windows.
Sono diverse le operazioni supportate, tra cui spegnimento, ibernazione, blocco, riavvio e via discorrendo.

Si basa su IFTTT e Google Drive/Dropbox/OneDrive.

IFTTT permette di estendere le funzionalità dell'assistente, facendogli creare un file particolare, tale file viene sincronizzato col cloud e questo viene letto dal programma che esegue le operazioni.

Il problema è che AssistantComputerControl è solo per windows, non esiste né una versione mac né una versione per GNU/Linux, per cui pubblico un piccolo script c che se eseguito, permette di controllare la macchina GNU/Linux coi comandi vocali di AssistantComputerControl.

Per ulteriori info:
https://assistantcomputercontrol.com/

# Come Funziona

Il mio script C legge il file che i comandi vocali di Assistant Computer Control creano nel cloud, e basandosi su una sincronizzazione cloud, consente di:
- SPEGNERE
- RIAVVIARE
- METTERE IN SOSPENSIONE
- IBERNARE
- SLOGGARE
- BLOCCARE

Una macchina linux con su Cinnamon.

I file sincronizzati dal cloud vengono parsati ed in base al comando viene eseguita la relativa controparte sul pc.
Siccome ho una macchina Debian Buster con su Cinnamon, il sistema è basato su Cinnamon, ma nulla vieta di adattarlo con pochi click a gnome o kde.

# Parametri di avvio
acclinux è impostato per accettare due parametri di avvio:
i secondi in cui aspettare tra una parsata e l'altra
la directory in cui si trova la directory AssistantComputerControl che verrà sincronizzata dal cloud preferito.
Io uso OneDrive con OneDrive daemon, ma nulla vieta di avere una directory montata con rclone o con dropbox per GNU/Linux.

# Esempio di utilizzo
rclone mount onedrive /home/numerone/OneDrive

acclinux 180 /home/numerone/OneDrive

# Varie
Se il sistema monta systemd, è possibile utilizzare acclinux come demone di sistema.
Probabilmente domani o dopodomani farò la pubblicazione del file di sistema, per il momento prendetevi questo sorgente.

# Se si usa gnome

Il cuore del sistema sono le righe da 96 a 109, se si usa gnome basta sostituire cinnamon-session.quit e cinnamon-screensaver-command con gnome-session-quit e gnome-screensaver-command per ottenere uno script perfettamente funzionante.
