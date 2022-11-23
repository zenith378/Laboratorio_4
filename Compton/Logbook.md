# Compton

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


### SEgnale di gate sulle coincidenze
Stesse condizioni di lavoro del 17/11, V_alim1 = 680 V, V_alim2 = 1796 V
V_thr1 = -20.7 [mV]
V_thr2 = -20.9 [mV]




