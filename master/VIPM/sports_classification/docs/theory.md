# Bag of Visual Words
[Reference Here](https://www.pinecone.io/learn/series/image-search/bag-of-visual-words/)

A differenza delle bag of word tradizionali che lavorano su sequenze di caratteri, qui prima di arrivare ad avere una
vera e propria BoVW dobbiamo prima ottenere delle visual feature:
Le immagini vengono divise in patch, ad ogni patch sono assegnati:
   1. **Keypoints**: punti fondamentali dell'immagine, invarianti rispetto a determinate caratteristiche in base al classificatore utilizzato (SIFT è invariante rispetto a rotazione, scala, cambi di luminosità e prospettiva).
   2. **Descriptors**: Creo (con SIFT) un vettore di 128 numeri che rappresenta cosa c'è nell'intorno del keypoint (es: intorno 16x16 pixel) attraverso lo studio dei gradienti dell'immagine (variazioni di illuminazione). Lo scopo principale di un descriptor è essere univoco e robusto. Per essere robusto deve assicurarmi che, se riprendo il soggetto da un'angolazione diversa, il suo descriptor deve essere idealmente identico (o quasi, nel pratico). 

Le visual feature vengono estratte tramite SIFT (Scale Invariant Feature Transform), ORB o SURF.

Una volta ottenute le visual features, l'obiettivo è creare un **vocabolario** che contenga 
le visual words. 
Si applica l'algoritmo K-Means sui descrittori per ottenere K visual words che andranno a formare il vocabolario.
Descrittori simili apparterranno allo stesso cluster.
La scelta del numero K di centroidi è magia nera, non c'è un metodo da seguire per scegliere il numero corretto. Quello che si può fare è 
cercare di ottenere un vocabolario che sia adatto alle immagini che si vogliono classificare: più il dataset è disparato, più il numero di visual words deve essere alto.

Il processo in cui si esegue un mapping fra una nuova visual feature e la visual words più vicina (centroide) è chiamato **vector quantization**.

Una volta che il dizionario è pronto, convertiamo ogni immagine in un vettore di lunghezza $k$, in cui in ogni cella si conta quante volte la visual feature $i \in \{1 \dots k\}$ appare nell'immagine.
Questi vettori sono chiamati **frequency vectors** e poiché non tutte le visual words sono presenti in tutte le immagini, i vettori spesso sono anche chiamati **sparse frequency vectors**.
Possiamo visualizzare questi vettori come istogrammi, dove ogni cella rappresenta una visual word e la altezza rappresenta quante volte la visual word appare nell'immagine.

Alcune visual words sono più importanti di altre, ad esempio una visual word che rappresenta il cielo deve essere meno importante di una visual word
con un soggetto chiaro, come il crocifisso di una chiesa. Per questo motivo, associamo alle visual words dei pesi tramite la formula
_term-frequency inverse document frequency_ (**TF-IDF**). Che pesa l'importanza di una visual word in base a quante volte appare nel dataset e quante volte appare nella stessa immagine.

### Differenza fra feature vector, frequency vector e visual word
* Il **feature vector** è un vettore di dimensione generalmente 128 (nel caso di SIFT) che codifica certe proprietà dell'immagine, 
* Una **visual word** fa riferimento a un elemento del vocabolario ottenuto con K-Means, per il quale rappresenta un centroide.
* Il **frequency vector** è un vettore di dimensione pari al numero di visual words nel vocabolario, che contiene il numero di volte che ogni visual word appare nell'immagine. Dal feature vector ricaviamo gli istogrammi. Nel caso di SPM, la sua dimensione aumenta in base ad $L$.

# SIFT
Nel nostro caso utilizziamo i Dense SIFT descriptors. In SIFT standard, l'algoritmo prima cerca dei keypoints nelle zone più interessanti (corners, edges etc.) quindi calcola i descrittori solo per queste zone, lasciandone altre, come il cielo o il prato, completamente prive di informazioni, ma nel nostro caso possono essere discriminanti.
Il dense SIFT usa uno step (per noi 8) per calcolare un keypoint a distanza fissata, ad esempio con step 8 e un immagine 224x224 (come il nostro dataset), ci saranno 784 keypoints, indipendentemente se la location è interessante o meno.
### Come SIFT tradizionale calcola i keypoints?
La scelta del keypoint in SIFT avviene guardando un intorno di pixel, il più rilevante di questi diventerà il descrittore.

# Spatial Pyramid Matching
[Reference Here](https://scispace.com/pdf/beyond-bags-of-features-spatial-pyramid-matching-for-4aa5cbe2fz.pdf)

Gli istogrammi della BoVW classica non tengono conto della posizione in cui una particolare visual word è stata trovata. Quindi due immagini possono avere istogrammi identici ma layout spaziali completamente diversi.
Nella classificazione degli sport, il layout spaziale conta moltissimo: una piscina si trova in genere nella parte inferiore dell'inquadratura, un canestro da basket in alto, il pubblico sullo sfondo. L'SPM consente al classificatore di sfruttare questi pattern di disposizione spaziale, e non solo la presenza di visual words.

In SPM abbiamo dei parametri fondamentali:
1. $L$ : numero di livelli della piramide spaziale (si conta da 0). Dice in quante celle l'immagine dev'essere divisa; nello specifico, indica quante divisioni laterali effettuiamo sull'immagine. Se abbiamo $L=2$, allora avremo 3 livelli, il primo $2^0=1$ è l'immagine originale, il secondo $2^1=2$ è l'immagine divisa in 4 celle (2x2), il terzo $2^2=4$ è l'immagine divisa in 16 celle (4x4).
2. **Il peso** associato ad ogni livello della piramide spaziale, che indica la importanza relativa di ogni livello nella rappresentazione finale. È dimostrato che i livelli più alti sono quelli più discriminativi, in quanto portano con loro anche le informazioni spaziali più fini, dunque dovrebbero tendere a pesi maggiori.

La dimensionalità dei feature vector aumenta esponenzialmente con $L$ crescente. ad esempio, se $L=0$ allora abbiamo l'equivalente esatto di una BoVW classica senza SPM, quindi con $K=500$ abbiamo feature vector di dimensione $500$. Con $L=2$ abbiamo feature vector di dimensione $500*(1+4+16)=10500$.
Nonostante l'aumento esponenziale, con $L$ ancora bassi come 2, la complessità computazionale aggiunta è trascurabile.

L'idea alla base di SPM è quella di calcolare un istogramma per ogni cella (in ogni livello) e non solo per l'immagine originale. Quello che si fa è poi fare un flattening degli istogrammi, ottenendo un singolo vettore di dimensione $500*(1+4+16)=10500$ come descritto sopra.
A questo punto abbiamo codificato le informazioni spaziali in un unico vettore, un qualsiasi classificatore è in grado, basandosi su un certo range di dimensioni del vettore, di imparare la spazialità delle immagini. Nel nostro caso un classificatore come una SVM è la scelta migliore, una rete neurale o convoluzionale richiederebbe troppo campioni per raggiungere un buon risultato.

# LinearSVC, confronto One-to-Rest
Generalmente Le SVM possono fare classificazione binaria, ma esistono estensioni dell'algoritmo che permettono di eseguire classificazione multi-classe, tra questi algoritmi ci sono One-to-One e **One-to-Rest (OvR)**, quello che usiamo qui.
OvR è utilizato dalla libreria _scikit-learn_ nella funzione _linearSVC_. Se si hanno $N$ classi, OvR addestra $N$ classificatori, ogni classificatore $i \in \{1 \dots N\}$ separa la classe $i$ da tutte le restanti $N-1$ classi raggruppate insieme. Ogni classificatore binario, sulla base della distanza fra il punto e l'iperpiano ottimale,
assegna un punteggio negativo (se il punto non è dal lato della classe corretta) o positivo all'istanza in esame. Il classificatore $i$ che ha associato il punteggio più alto, assegnerà rispettiva classe $i$ all'istanza.

# EfficientNet
Il nostro modello è **EfficientNet B3** trainato su **ImageNet21K** (1M+ immagini, e contiene una sotto categoria contenente degli sport). Scelta anche per l'efficienza.
A livello di freezing abbiamo allenato solo il classificatore e infine l'ultimo layer convoluzionale (conv head) e il classificatore (partial freezing, solo una parte dei layer convoluzionali è freezzata). Il classificatore l'abbiamo sostituito per predirre le nostre 100 classi + dropout dopo la conv head prima del classificatore.

# Batch Normalization
A ogni layer del modello rinormalizzo le feature tramite media e varianza, media e varianza diventano parametri allenabili, il training diventa più stabile e converge meglio.

# Adaptive Average Pooling
E' adattivo nel senso che ottengo la dimensione che voglio in output. La grandezza del pooling è quindi adattiva in base a che output vogliamo avere. Lo usiamo prima della parte Feed-Forward della rete.



