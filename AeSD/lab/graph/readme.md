# Grafi

Componenti: Vertici e Archi
$$
G = \braket{V, A}\\
V = \{ Vertici \}\\
A \subseteq V \times V\\
$$

Esempio Grafo Diretto:
$$
G = \{ 1, 2, 3 \}\\
A = \{ (1,2), (2,3)  \}\\					% Single-linked
A = \{ (1,2), (2,1), (2,3), (3,2) \}\\		% Double-linked
$$

Esempio Grafo indiretto:
$$
V = \{Vertici\}\\
A = \{\{a,b\} : a,b \in V\}\\
A = \{\{1,2\}, \{2,3\}\}
$$

Numero di Nodi e Archi:
- Grafo Diretto:
  - Nodi: 4 : n
  - Archi: 16 : $n^2$
    - Perché $\sum(x,y)$
- Grafo Indiretto:
  - Nodi: 4 : n
  - Archi: 10 : $\frac{n^2 + n}{2} = \frac{n (n+1)}{2}$

## Implementazione
- Nodi = array di chiavi
- Archi 
  - array di archi uscenti | (lista di adiacenza)
  ![adjacent list](adjacent_list.png)
  - Altrimenti: Matrice esplicita di valori logici per ogni 2 nodi: 0/1 arco no/si