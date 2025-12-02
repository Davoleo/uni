# Assignment 6 - TL FE

Estrazione delle feature da 3 layer diversi della rete:
1. `relu2`: Vicino all'input
2. `relu4`: Al centro della rete
3. `relu6`: Vicino all'output della rete

L'estrazione ha mostrato i seguenti risultati di accuracy di classificazione:

|                           | `relu2` | `relu4 `| `relu6`|`relu7` (lab)|
|---------------------------|---------|---------|--------|-------------|
| **Normalized (1-NN)**     | 75.67%  | 83.33%  | 93.67% |    94.33%   |
| **Not Normalized (1-NN)** | 49.33%  | 48.00%  | 82.00% |    89.67%   |
| **Normalized (SVM)**      | 82.67%  | 88.67%  | 95.00% |     ---     |
| **Not Normalized (SVM)**  | 83.33%  | 88.33%  | 95.00% |     ---     |


Possiamo notare che in entrambi i casi (feature normalizzate e non) 
i risultati mostrano un miglioramento notevole di accuracy estraendo le feature dagli ultimi layer di `alexnet` (I layer più vicini alla classificazione originale);
Da questo, e in luce dell'estrazione fatta durante il lab (`relu7`) che offriva accuracy ancrora migliori, possiamo dedurre che il dataset che si sta classificando ("Simplicity") sia molto simile al dataset ImageNet su cui è stata allenata la rete originalmente.