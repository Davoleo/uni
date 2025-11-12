Object recognition:
- Object instances (riconoscimento dello specifico oggetto)
	- Ad esempio per sistemi di raccomandazione
	- Per catalogare libri
- Object classes (riconoscimento generico tipo di oggetto)

Object instance recognition:
Approccio template matching, o sliding window, si scorre sull'immagine finché non si trova una posizione in cui la differenza è 0.
Si ripete con scala diversa se non si trova.
Si ripete anche con rotazione diversa se non si trova.
Questo rende l'approccio molto oneroso computazionalmente.

In ogni punto facciamo la Sum of square differences, e registriamo il risultato nella mappa finale.
(no distanza euclidea [radice quadrata] perché è un operazione pesante e non cambia la funzione in quanto è monotona)
Inversione + treshold permette di trovare i true matching, o quasi true.
La sum of square differences risente di cambi locali di contrasto, che quindi influenzano la detection.

Altro approccio: Normalized Cross-correlation
Prendo il template e lo traslo in modo che abbia media 0.
Ogni volta che analizzo una posizione dell'immagine, normalizzo anche quella posizione (sottraendo alla finestra il valore medio per quella finestra).
Aggiunge robustezza alla formula della distanza, con un costo non indifferente per la sliding window sull'immagine.


SSD: più veloce ma sensibile al contrasto dell'immagine
Normalized Cross-correleation: più lenta ma invariante al contrasto locale e all'intensità di colore.

L'obbiettivo è un algoritmo indipendente da:
- scala,
- rotazione (verticale e orizzontale),
- luce della scena (intensità di luce, direzione luce, colore)
- Artefatti dell'immagine (noise, blur, compressione)

Metodi più utilizzati:
< 2004: early methods (e.g. sliding window)
> 2004: SIFT
~2007: learning based
~2015: CNN

Keypoint-based approach: Punti chiave dell'immagine (caratteristici)
- Keypoint detection
- Keypoint description
- Matching con l'immagine originale
- Similarity score (basata sui punti che fanno match)

SIFT (Scale invariant features transform)
- Handcrafted
Robusto a:
- scala
- rotazione
- illuminazione
- viewpoint (entro certi limiti)

First Step: Detection dei punti caratteristici.
Legati alla presenza di angoli all'interno dell'oggetto. 
Scale space: Si creano immagini sempre più blurrate per rimuovere dettagli fini e mantenere i dettagli più importanti. 
(come se vedessimo l'immagine da lontano)
Octaves: Si scala l'immagine su 4 ottave e con 5 livelli di blur diversi per simulare la distanza e la rappresentazione dei dattagli.

Differenza tra Gaussiane: Si fanno le differenze tra le gaussiane, 
se il punto rimane invariato significa che l'edge è molto importante perché viene mantenuto indipendentemente dal livello della gaussiana
Infine si mantengono solo le zone dove la differenza è alta sia verticalmente sia orizzontalmente.

Keypoint orientation:
Si analizzano i gradienti intorno ad un punto, e vengono riportati a 0 gradi per riuscire a normalizzare l'immagine rispetto alla rotazione.

Per ogni keypoint calcolo il descrittore. Capire la firma del keypoint e per farlo mi serve un contesto di 4x4x8 -> 128 bit. 
perché un pixel solo sarebbe troppo variante per cambiamenti di illuminazione ad esempio.

Keypoint matching: confronto le firme dei keypoint del template con quelle dell'immagine di input (se la score è troppo bassa si scarta il keypoint)
Costruiamo una omografia: esiste una rototraslazione che permetta di riadattare l'immagine per renderla uguale al template?
	Se si abbiamo trovato l'immagine, altrimenti nada 
RANSAC: provo a creare una trasformazione basata su intuizioni basate sui keypoint matching, poi si testa randomicamente 
quanti punti all'interno dell'immagine sono d'accordo con la trasformazione, 
e se sono sopra ad una certa soglia possiamo decidere la trasformazione adeguata.
(è comunque possibile trovare outliers rispetto all'immagine, e quindi bisogna essere un minimo flessibili.)

Applicazioni:
- Panorama stitching: Adatta le rotazioni dell'immagine per creare un immagine continua del panorama
- Video stabilization: Allineo i frame uno dopo l'altro.
- Tracking (sorveglianza)
- Augmented reality - IKEA