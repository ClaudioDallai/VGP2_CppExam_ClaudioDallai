# VGP2_CppExam_ClaudioDallai
 
ESAME C++ - VGP2 - CLAUDIO DALLAI

Buonasera professore. 
Volevo solo avvisare che, tra tutte le richieste del progetto, non sono riuscito pienamente a sfruttare un Custom Movement Component ereditando poi il Player da Pawn.
Ho lasciato comunque la classe C++ di questo, e alcune parti del Player commentate e non più usate, perchè ho trovato difficoltà poi nel ragionare a livello Pawn e soprattutto a livello PawnMovementComponent.
Quest'ultimo comunque era funzionante, anche se con molte limitazioni. Il principio era praticamente identico a quello svolto in classe, per motivi anche di tempo, oltre a quelli sopra elencati, ho ereditato da Character.
Il resto delle richieste spero invece che siano state affrontate in maniera corretta: Checkpoint, Delegate, Interface, Linetrace, Timeline... 
Ho cercato di svolgere praticamente tutto in C++, compresa la creazione di componenti. L'unica parte in Engine, oltre alla mappa, è solo l'assegnazione di alcuni assets e valori.

Le features del progetto sono quindi:
- Nuovo Player, che viene spawnato dalla GameMode;
- Assegnazione Input di quest'ultimo;
- SaveSystem;
- Relativo al SaveSystem ho costruito CheckPoint e LoadGame che salvano/ricaricano il salvataggio alla collisione (impostando i vari valori);
- Piattaforme mobili (totalmente fatte da C++, compresa Timeline);
- Piattaforma di lancio per un salto molto grosso. La direzione del salto è proprio la direzione della freccia rossa che compare;
- WinTrigger che alla collisione resetta il salvataggio e la mappa;
- Sistema di Interaction con LMB attraverso un LineTrace, se questo hitta un Interactable viene chiamato il suo metodo interfaccia Interact;
- PowerUp per un salto maggiorato (derivante da una classe base PowerUpBase, che avrei voluto fare abstract ma per cui avevo ricevuto errori che non sono riuscito a risolvere, dove quindi alla fine ho tolto l'abstract);
- Il PowerUpJump ha una durata limitata fatta attraverso dei Timer in C++, inoltre qualora il Player cada di sotto dalla mappa mentre il PowerUp è attivo, attraverso un DYNAMIC_MULTICAST viene avvertito ed il PowerUp si interrompe.
