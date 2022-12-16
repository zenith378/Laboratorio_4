# Logbook esperienza effetto Compton

## 17 novembre 2022

Iniziamo posizionando il PMT1 davanti al collimatore, nel punto più vicino. 
- distanza NaI - scintillatore plastico: 14 cm
- spessore scintillatore: 2.6 cm
- distanza scintillatore plastico (dal punto più vicino alla sorgente)  - collimatore: 3.3 cm

V_alim_1 = 709 V
trg level: -42.4 mV



### Punto di lavoro preliminare
Cerchiamo un punto di lavoro preliminare che consenta di osservare delle coincidenze tra i due PMT.\ Ci siamo messi nella situazione in cui il collimatore è estratto al massimo (arriva davanti allo scintillatore plastico).
Consideriamo l'uscita non amplificata del PMT1
- PMT1: thr -20.6 mV 
- PMT2: thr discriminatore -20.7 mV
(le teniamo basse perchè tanto ci interessa vedere la coincidenza, che quindi pulisce da sola il segnale, non mi serve tenere la soglia alta)

- V_alim,1 = 671 [V] 
- V_alim,2 = 1796 [V]
- guadagno PMT1 = 10\
a 60 gradi: rate di coincidenze di 5 Hz?


Prossima volta:
- vediamo comportamento del PMT1 al variare dell'angolo
- fissiamo un angolo e variamo la posizone del PMT1 (più o meno vicino alla sorgente)

## 22 novembre 2022

### Misura dell'asse del fascio 
Lavoriamo con gli stessi punti di lavoro della volta scorsa
-distanza sorgente - uscita fascio (cioè la lunghezza di cui sporge il collimatore) = 4.1 [cm]

Lavoriamo con tutto il collimatore allungato perchè poi quando metteremo lo scintillatore plastico avremo sempre il collimatore allungato. 

- ricerchiamo il massimo rate in singola del PMT1, avendo tolto il PMT2, al variare dell'angolo tra 80 e 100. Mi aspetto che la direzione del fascio sia quella che massimizza il rate.(tempo di acquisizione = 30 s)\

- Vediamo che il massimo rate si ha a 94° (rate superiore di qualche sigma rispetto a quello che ho a 90°), perciò ci posizioniamo qui e variamo la distanza del PMT1 dal collimatore e vediamo come varia il suo rate. Ci muoviamo a passi di 1 cm. Lunghezza della barra su cui scorre il PMT1 è di 39.7 [cm] (tempo di acquisizione di 30 [s])

### Segnale di gate usando il solo PMT1
Aumentiamo V_alim del PMT1  a 60 [V] in modo da spostare di poco verso dx i picchi

V_{thr} del discriminatore = -20.2 mV
Alzando e abbassando la tensione di soglia del discriminatore ho un taglio nello spettro che visuaalizzo. Il taglio si sposta sempre più a destra all'aumentare della soglia in valore assoluto.
Variamo la soglia:
-20.2 [mV]
-25.5  taglio inizia a 3000 ua
-30.1
-40.0, taglio inzia a 4000 circa
-50.1, taglio inizia a circa 5000 (il primo picco è a 6000 circa u.a.)

Il CAEN prende l'altezza massima, all'interno del gate, del segnale shapato (è una tensione) e me lo converte in un'energia (lo spettro che vedo)


### Segnale di gate sulle coincidenze
Stesse condizioni di lavoro del 17/11, V_alim1 = 680 V, V_alim2 = 1796 V
V_thr1 = -20.7 [mV]
V_thr2 = -20.9 [mV]


Pt. 4 della scheda: otteniamo un angolo di 0.02 (abbiamo imposto che la differenza tra l'energia del fotone diffuso e l'energia iniziale del fotone fosse 0.277 KeV)

Da fare giovedì 24 novembre:
- segnale di gate sulle coincidenze (vedere se va bene come fatto la volta scorsa, altrimenti allarghiamo il gate)
- determiniamo come varia il rate delle coincidenze al variare dell'angolo, per trovare l'angolo di lavoro (quello che massimizza il rate di coincidenze). Al tempo stesso osserviamo i rate in singola e gli spettri, per assicurarsi che non ci sia saturazione (tutto questo con gate sulle coincidenze)
- trovato il range di angoli su cui operare proviamo a variare la soglia del discirminatore del PMT2, fissato l'angolo in quel range  e vediamo 

- calibrazione

- divergenza angolare: vediamo come varia il rate del PMT1 (senza metetre lo scintillatore plastico) al variare dell'angolo, per vedere la divergenza angolare del fascio
- vedere come varia il rate al variare della distanza del PMT1 dalla sorgente (ad angolo fissato)

## 24 novembre 2022
angolo: 21
il segnale del discriminatore del PMT1 va prima allungato per evitare le ripartenze del discriminatore stesso e poi di nuovo ridotto per farlo essere pari a quello del discriminatore del PMT2

Ci siamo accorti che il segnale discriminato del PMT2 ripartiva poichè la soglia era troppo bassa (la durata del segnale balllava). Abbiamo alzato la soglia a -31.0 mV per evitare le ripartenze.

allunghiamo il segnale discriminato di entrambi i PMT per evitare le ripartenze dei discriminatori e poi li riaccorciamo

Stima delle accidentali:
n1 = 92985
n2 = 232874
n1,2 circa 495 (non ho segnato)
Delta_t = 100 s
tau_1 \sim 150 ns
tau_2 \sim 150 ns
Così abbiamo 65 accidentali (stima con la formula), cioè il 14%

Riduciamo i segnali discriminati a 100 ns per diminuire il rate delle accidentali (scende al 10%)




Osserviamo segnali in cui prima abbiamo il segnale discirminato 1 e poi quello 2. Forse sono dovuti al seguente caso: arrivano due fotoni dalla sorgente, il primo triggera lo scintillatore e va dritto (o comunque non arriva nel cristallo), mentre il secondo viene perso dallo scintillatore (perchè?) e invece lo rivela il cristallo

## 29 novembre 2022
Non possiamo stimare la divergenza angolare come avevamo detto di fare poichè il cristallo è largo e non riusciremmo ad avere una stima della divergenza, a meno di metetrlo molto distante dal collimatore. Possiamo provare a fare misure di rate per vari angoli, variando per ciascun angolo anche la posizone del cristallo (vicino, nel mezzo e lontano) per vedere se in effetti da lontano otteniamo una stima della divergenza. Confrontando con quanto ottenuto da vicino potremmo fare considerazioni sulle dimensioni del cristallo

CALIBRAZIONI
- cesio 137
- stronzio 90
- sodio 22
- cobalto-60

- lunghezza collimatore: 11.35 cm, misurato con calibro
- 0.99 cm diametro interno del collimatore


Acquisiamo uno spettro con gate e stessi punti di lavoro delle altre volte a dun angolo di 15°

Punti di lavoro:
PMT1: 680 V, V_thr discriminatore -20.6 mV
PMT2: 1795 V, V_thr discriminatore -30.6 mV (l'avevamo alzata la volta scorsa per tagliare il rumore)


## 1 dicembre 2022
acquisiamo a 20 gradi, salviamo l'acquisizione in prova20gradi.dat (è durata 1 ora e mezzo circa). 
Misuriamo i rate in singola e le coincidenze per un tempo di 1000 secondi:
#1 = 403505
#2 = 2367097
#1,2 = 4372

la temperatura del NAI è di:  18.5 (misurata con il termometro) 
Posizioniamo tutte le varie sorgenti davanti al cristallo (lo tocca), al centro
### Stronzio
#1 = 38827
tempo = 104308
### Sodio
#1 = 21392
tempo = 208556

### Cesio
#1 = 99588
tempo= 50269

### Cobalto
#1 = 66007
tempo = 97096

le calibrazioni sono salvate tutte in "nomesorgente"1dicembre.dat


## 6 dicembre 2022
Facciamo un'acquisizione con angolo di 15 gradi, dalla mattina alle 9.30 alle 15 e non vediamo i due picchi "15gradi6dicembre.dat". Il problema stava nel fatto che usavamo come gate il segnale dall'uscita negata del modulo DualTimer, perciò acquisivamo tutto tranne che le coincidenze. Abbiamo sistemato il agte (consideriamo l'usicta OUT) e acquisiamo a 15 gradi. La temperatura è di 20.3°.
Ancora non osserviamo i picchi. (salviamo l'acquisizione appena fatta in 15gradi6dicembredebug.dat) Proviamo a debuggare il setuo mettendoci ad angolo più grande in modo da avere segnali più grandi dal plastico. Abbiamo notato che anche a 15° ci sono segnali dal plastico, ma hanno per lo più ampiezza minore di 30 mV (si confondono con il rumore), periò i perdiamo dato che abbiamo una soglia sul discriminatore 2 di -30.8 mV. Quindi quando vorremmo acquisire ad angoli così piccoli dobbiamo o abbassare la soglia (stando attenti alle ripartenze) oppure alzare l'alimentazione.
Per adesso acquisiamo a 30° e salviamo in 6dicembre30.dat. Acquisiamo per mezz'ora crca a 25° (6dicembre25.dat). Visualizziamo con root gli spettri ottenuti in entrambi i casi per vedere se si vedono i due picchi e capire a che angolo fare la prima presa dati lunga. Alla fine della giornata la temperatura è scesa di 1 °.

## 7 dicembre 2022
Acquisiamo ad un angolo di 22° per capire a che angoli afre poi la presa dati più lunga. La temperatura di oggi è 19.4. Vediamo che con questo angolo e la soglia del discriminatore 2 a -30.8 mV stiamo tagliando parte del segnale. Ce ne siamo accorti poichè la spalla compton era più alta dei presunti picchi). Il relativo file è 7dicembre22.dat Dobbiamo quindi abbassare la soglia del discriminatore 2. Vediamo che scendendo a -25.1 mV continuiamo a prendere solo segnale buono e non rumore.Aggiustiamo i segnali discriminati in modo che siano perfettamente sovrapposti, per evitare che la coincidenza duri meno di 100 ns. Per renderli il più sovrapposti possibile riatrdiamo il segnale discriminato 2 usando cavi di 16 e 10 ns. Prendiamo uno screenshot (foto con il telefono di Alessia) dei segnali in queste condizioni (in giallo pmt1, in celeste pmt2).\
Acquisiamo, ma continuiamo a vedere che l'altezza della spalla è di poco inferiore a quella dei picchi. L'acquisizione è 7dicembrebis22.dat. Confrontando i due spettri si vede comunque un migliroamento nell'acquisizione, dovuto all'abbasamento dell tensione di soglia del discriminatore 2.  Acquisiamo sempre ad un angolo di 22°, ma uamnetiamo la tensione di alimentazione del PMT2 in modo da avere segnali più ampi e quindi ver una maggior probbailità che superino la soglia del discriminatore 2 (non possiamo aumentare troppo perchè sennò con la soglia a -25.1 mV rischiamo di acquisire anche il rumore).L'acquisizione è 7dicembretris.dat. 

Impostiamo: 
- V_alim_2 = 1883 V\
#1 ordine di 4 x 1e4\
#2 ordine di 3x1e6\
Delta_t = 100 s\
#1,2 ? forse erano 1000-2000.\
Con questa tensione abbiamo un rate di doppie accidentali del 10%, ma non sappiamo quanto fosse con l'alimentazione precedente. Si vede chiaramente che il PMT2 è più rumoroso. Quando vediamo i segnali discriminati, triggerando sul pmt1, vediamo che ci sono molti casi in cui il segnale discriminato 2 cade molto lontano (da circa 50-100 ns fino ad oltre 300 ns) da quello del discriminatore 1. Queste sono tutti segnali accidentali che dobbiamo evitare.\ Riduciamo l'alimentazione del PMT2 a:
- V_alim_2 = 1837 V\
Il rate del 2 decresce di un fattore 10 (da 3 x 1e6 a 6 x 1e5)\
#1 = 39896\
#2 = 658227\
#1,2 = 1254\
Delta_t = 100 s\
Le coincidenze accidentali ora sono lo 0.4 % (ricontrollare).\
Facciamo foto (telefono di Giulio) al contatore in queste condizioni.


### Cose da fare:
- fit agli spettri delle sorgenti di calibrazione
- curva di calibrazione (trovare modello più adatto) -> vedere curva dell'eenrgia emessa in funzione del dE/dx VEDERE SLIDES LEZIONI SCINTILLATORI PLASTICI (c'è saturazione, dunque l'approssimazione lineare funziona solo in prima approssimazione)
- stima della divergenza angolare del fascio e dell'angolo che lo scintillatore ad NaI "vede" (se sappiamo che copre un angolo di 3° ad esempio, non ha senso prendere acquisizioni ad angoli che difefriscono per 3° o meno)

### Programma per i prossimi giorni
- nei giorni di presa dati lunga (3) andiamo la mattina, segnamo la temperatura, calibriamo a quella temperatura e poi facciamo partire l'acquisizione. Quando torniamo alle 14.30 stoppiamo l'acquisizione, misuriamo la T, calibriamo e prendiamo un'altra acquisizione. Analogamente alle 16.30 e 18. Così abbiamo calibrazioni a diverse ore del giorno e per diverse temperature. I dati per le 4 acquisizioni fatte andranno poi sommate (TENENDO CONTO DI COME LA CALIBRAZIONE È CAMBIATA CON LA TEMEPRATURA?)
- nei giorni di presa dati breve (mercoledì) troviamo punto di lavoro ottimale per gli angoli piccoli (15°) e poi per quelli grandi (30°)

La presa dati a 30° del 6 dicembre la teniamo? Non abbiamo calibrazioni di quel giorno però.


### IMPORTANTE: ricordiamoci che per ottenere gli angoli "veri" dobbiamo sottrarre (o aggiungere) 3 gradi (orientazione asse del fascio) a qelli misurati. Dobbiamo fare prima un' analisi della curva rate(angolo) per determinarne il massimo, che ci aspettiamo corrisponda ala direzione del fascio.



## 13 dicembre 2022
Temperatura: 18.2°, ore: 11:00
Calibriamo con le sorgenti (nere): TROVARE ATTIVITÀ
- Cesio-137: "13dicembre11cesio.dat"
- Sr-90: "13dicembre11stronzio.dat"
- Na-22, "13dicembre11sodio.dat"
- Co-60, ""13dicembre11cobalto.dat"

Facciamo partire l'acquisizione del Compton con stessi punti di lavoro della volta scorsa e angolo di 20° (ore: 11:10)

Stoppiamo l'acquisizione alle 16.26 (salviamo in "13dicembre20gradi.dat") e facciamo altre calibrazioni, usando le sorgenti "bianche". Adesso la temperatura è di 19.2°. Salviamo tutto in "13dicembre16nomesorgente.dat".

Fonti di errori sistematici nella posizion dei picchi nella calibrazione:
- posizione dei picchi che varia con rate (da testare)-> si può vedere cambiando la distanza della sorgente o variando l'alimentazione del PMT
- dipendenza dalla temperatura della risposta del NaI -> calibrare ad intervalli regolari



Effetti che contribuiscono agli errori sistematici sui picchi delle calibrazioni:
- quantum efficiency dei PMT
- numero di fotoni prodotti per MeV di energia rilasciata nello scintillatore
- non tutti i fotoni prodotti dallo scintillatore arrivano al fotocatodo, non tutti danno elettroni nel PMT (rientra nella quantum efficiency?)

Acquisiamo a 15°, cambiando il punto di lavoro del PMT2 e salviamo in "13dicembre15gradiprova1.dat"
- V_thr_2 = -22 mV
- V_alim_2 = 1837 V
Qui abbiamo un numero di coincidenze di 952 in 100 s, con #1 dell'ordine di 5x1e4, #2 di 6x1e5, tau = 100 ns


Acquisiamo così:
- V_thr_2 = -25 mV
- V_alim_2 = 1860 V
Salviamo in "13dicembre15gradiprova2.dat". Qui abbiamo un numero di coincidenze di 1149 in 100 s, con #1 di 50407, #2 di 877920, tau = 100 ns. Aumenta il rate di accidentali (circa 8%), ma aumenta anche il rate di coincidenze (da 952 a 1149). Bisogna capire cosa aumenta "di più" e confronrare gli spettri acquisiti.

## 14 dicembre 2022
Temperatura: 18.7°, Ore 09:36
Calibriamo con ciascuna delle quattro sorgenti (quelle "scure") per 100 secondi ciascuna. Salviamo i dati per ciascuna in "14dicembre9nomesorgente.dat"

Sodio:
#1 = 20213

Cobalto-60:
#1 = 90080

Stronzio-90:
#1 =38734

Cesio-137:
#1 = 229550

La temperatura alle 09:48 è salita a 18.9°.

Iniziamo l'acquisizione vera e propria ad una ngolo di 15° con i seguenti punti di lavoro:
PMT1:
- V_alim_1 = 679 V
- V_thr_1 = -20.6 mV

PMT2:
- V_alim_2 = 1860 V
- V_thr_1 = -25.2 mV
Alle 11.14 sono 19.6° (-0.3% per C° vedi slides ottava lezione)

Cose da fare giovedì in laboratorio:
- acquisire ad angolo di 25°
- terminata l'acquisizione (alle 14.30):
    1. calibriamo con le sorgenti di calibrazione a diverse ore (3/4), segnandosi la temperatura
    2. calibriamo a T fissata variando la distanza della sorgente dal PMT1, in modo da avere rate diversi e vediamo se la posizione dei picchi cambia 
    3. acquisiamo con il solo PMT1, togliendo il plastico, ad angolo di 0°, con gate esterno, fatto però sul solo PMT1 e non sulle coincidenze (dato che non ci sono) per 3/4 distanze diverse del PMT1 dalla sorgente e vediamo se e di quanto si sposta la posizone dei picchi



## 15 dicembre 2022
Acquisiamo ad un angolo di 25°, iniziamo alle 9:30
V_alim_1= 680 V
V_thr_1 = -20.6 mV
V_alim_1= 1840 V
V_thr_1 = -25.2 mV

La temperatura è di 19.1°.

Stima degli angoli:
- correggere per l'asse del fascio
- associare un errore dovuto alla copertuta angolare del cristallo
- errore di lettura dell'angolo (probabilmente rientra nella copertura angolare)

Cose da fare oggi in laboratorio:
- acquisire ad angolo di 25°
- terminata l'acquisizione (alle 14.30):
    1. calibriamo con le sorgenti di calibrazione a diverse ore (3/4), segnandosi la temperatura
    2. calibriamo a T fissata variando la distanza della sorgente dal PMT1, in modo da avere rate diversi e vediamo se la posizione dei picchi cambia 
    3. acquisiamo con il solo PMT1, togliendo il plastico, ad angolo di 0°, con gate esterno, fatto però sul solo PMT1 e non sulle coincidenze (dato che non ci sono) per 3/4 distanze diverse del PMT1 dalla sorgente e vediamo se e di quanto si sposta la posizone dei picchi
    4. misuriamo la geometria per stimare la copertura angolare del plastico

Misuriamo con il metro a nastro:
- diametro del cristallo: 5.8 cm
- spessore plastico: 2.7 cm
- larghezza plastico: 5.4 cm

Terminiamo l'acquisizione alle 14:56. Salviamo i dati in "15dicembre25gradi.dat". (i rate sono su telegram)

Facciamo la calibrazione per questa giornata, che useremo per calibrare i picchi ottenuti oggi, sia come calibrazione delle ore 15:00 (poi ne prendiamo una ogni ora circa o meno per vedere se i picchi di ciascuna sorgente si spostano o no al variare della temperatura).

Vediamo come e se cambia la posizone dei picchi delle sorgenti di calibrazione al variare della temeratura. Per farlo calibriamo in 3/4 momenti della giornata, segnandoci ora e temperatura.\
### Prima calibrazione della giornata: 
ore 15:00, temperatura 19.8°\
Delta_t=100 s per tutte le sorgenti, nome file "15dicembre15nomesorgente.dat"\
- Sodio: #conteggi =20021
- Cobalto: #conteggi = 90015
- Cesio: #conteggi = 230907
- Stronzio: #conteggi = 38839


Per vedere se la posizone dei picchi varia con il rate: usiamo solo il PMT1 posizionato ad angolo di -3° (senso antiorario) (93°), in modo da allinearlo con l'asse del fascio. Acquisiamo gli spettri della sorgente grande di Cobalto-60, usando gate esterno, fatto solo sul PMT1 e non sulle coincidenze come nelle acquisizioni tradizionali. Annotiamo il rate e acquisiamo gli spettri per ciascuna distanza. Facciamo variare la distanza tra cristallo e plastico da un minimo di 21.0 cm ad un massimo di 43.0 cm. Queste misure possono sostituire quelle fatte all'inizio, in cui eravamo arrivati ad una distanza massima lungo la guida di 14 cm. 21 cm è la distanza tra l'inizio della guida e l'uscita del collimatore cilindrico (tirato fuori di 4.1 cm)

Delta_t = 100 s
Distanza| #conteggi|
:------|:-------|
21.0 | 589883|
21.0 + 22.0 | 348656|
21.0 + 21.0 | 362830|
21.0 + 20.0 | 379978|
21.0 + 19.0| 393893|
21.0 + 18.0| 407052|
21.0 + 17.0| 424660|
21.0 + 16.0| 439373|
21.0 + 15.0| 456203|
21.0 + 14.0| 484983|
21.0 + 13.0| 499272|
21.0 + 12.0| 507842|
21.0 + 11.0 | 517545|
21.0 + 10.0 | 529431|
21.0 + 9.0| 538151|
21.0 + 8.0| 549863
 Mentre prendevamo queste misure la temperatura è variata da 19.8 a 20.4°, perciò decidiamo di prendere misure di rate per sole 5 posizioni, in modo da velocizzare la presa dati e mantenere la temperatura costante durante l'acquisizione, in modo che a avriare sia solo il rate. 

Distanza dal| #conteggi| temperatura
:------|:-------|:------|
21.0 + 20.0| 388031| 20.5|
21.0 + 15.0| 455054| 20.4|
21.0 + 10.0 | 529431| 20.4|
21.0 + 5.0 |565582| 20.4|
21.0 |587169| 20.4|



Con le misure appena fatte varia anche l'angolo coperto dal cristallo, poichè cambiamo la sua distanza dalla sorgente. Per tenere fissato l'angolo fissiamo la distanza a (21.0 + 0.0) cm e variamo la tensione di alimentazione del PMT, in modo che a cambaire sia solo il rate. NO! se cambiamo la tensione di alimentazione cambia la posizone dei picchi. Dovremmo ripetere le misure fatte al variare della distanza, usando però un collimatore, in modo che l'angolo coperto dal cristallo sia sempre lo stesso.

Riprendiamo le misure, usando questa volta un collimatore (con foro di 0.97 cm, misurato con il calibro) posizionato davanti al cristallo (attaccato al cristallo - vedi foto fatte oggi), in modo da avere sempre lo stesso angolo coperto al varaiare della distanza cristallo-sorgente:
La distanza è tra l'usicta del collimatore cilindrico (tirato fuori di 4.1 cm) e l'inizio del cristallo). Per fare queste misure usiamo sempre gate ext, fatto solo sul PMT1 e non sulle coincidenze

Distanza| #conteggi| temperatura
:------|:-------|:------|
17.3 | 364665| 20.5|
17.3 + 5|  293743 |  20.6  |
17.3 + 10| 270329    |  20.6  |
17.3 + 15|  238417   |  20.7 |
17.3 + 20|  202024  | 20.7|



### Seconda calibrazione: 
ore 16:00, temperatura 20.4°, acquisiamo sempre con gate automatico e sempre con la sorgente che tocca il cristallo (vedi foto fatta oggi). Salviamo le acquisizioni in "15dicembre16nomesorgente.dat".\ Per tutte le sorgenti: Delta_t = 100 s

- Sodio: #conteggi = 19269
- Cesio: #conteggi = 227077
- Stronzio: #conteggi = 39062
- Cobalto: #conteggi = 85989

La temperatura alla fine della calibrazione è rimasta a 20.4°

### Terza calibrazione:
Ore: 17.14, temperatura 20.9° (usiamo sempre gate auto). salviamo in "16dicembre17nomesorgente.dat". Delta_t = 100 s per tutte.

- Sodio: #conteggi = 19697
- Cesio: #conteggi = 226260
- Cobalto: #conteggi = 89263
- Stronzio: #conteggi = 38636

Distanza PMT-plastico = 14 cm


Cerchiamo il punto di lavoro per un angolo di 10°. 


Acquisiamo così:
- PMT1:
    -  V_thr_1 = 20.8 mV
    - V_alim_1 = 680 V

- PMT2:
    - V_alim_2 = 1865 V
    - V_thr_2 = 28.7 mV

#1 = 55118\
#2 = 378364\
#1,2 = 486\
Delta_t = 100 s

PRENDERE FOTO COINCIDENZE ALL'OSCILLOSCOPIO! Fatta per un angolo di 10°, con i punti di lavoro descritti sopra

IMPORTANTE: proviamo a ridurre ulteriormente l'nagolo e vediamo quando i rate esplodono. In quel caso significa che stiamo prendendo il fascio diretto. Tutto ciò per essere sicuri che a 10° prendiamo solo il Compton. \

Ci mettiamo ad un angolo di 5°. I rate esplodono, quindi stiamo prendendo il fascio diretto. Abbiamo (con i punti di lavoro definiti per angolo di 10°):

#1 = 268472\
#2 = 360284\
#1,2 = 503\
Delta_t = 100 s

Ad un angolo di 7°:
- #1 = 149571
- #2 = 356721
- #1,2 = 432
- Delta_t = 100 s

Ad un angolo di 8°:
- #1 = 97566
- #2 = 349576
- #1,2 = 398
- Delta_t = 100 s

Ad un angolo di 9°:
- #1 = 64627
- #2 = 358525
- #1,2 = 469
- Delta_t = 100 s

### Quarta calibrazione:
Ore: 18.0, temperatura 21.1° (usiamo sempre gate auto). salviamo in "16dicembre18nomesorgente.dat". Delta_t = 100 s per tutte.

- Sodio: #conteggi = 20295
- Cesio: #conteggi = 230533
- Cobalto: #conteggi = 90823
- Stronzio: #conteggi = 39022


Possiamo misurare l'efficienza del PMT1, da considerare come sistematico. Considerazioni sulla distribuzione in energia al variare dell'angolo, visto che ogni volta acquisiamo a più angoli (angolo letto +- copertura del cristallo, vedi appunti tablet)

Ragionare sul fatto che usare sorgenti che decadono beta è un rischio perchè non sono una riga, ma hanno uno spettro continuo



