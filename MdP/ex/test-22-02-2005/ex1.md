### Ex 1 Risoluzione Overloading w/ templates

_Ordinamento parziale template:_
- 3 << 4
- 5 << 6 << 4

**Chiamata #1**
- Candidate: #1, #2
- Utilizzabili: #2
- Migliore: #2

**Chiamata #2**
- Candidate: #1, #2
- Utilizzabili: #1, #2
- Migliore: #1

**Chiamata #3**
- Candidate: #1, #2
- Utilizzabili: #2
- Migliore: #2

**Chiamata #4**
- Candidate: #1, #3, #4
- Utilizzabili: #3, #4
- Migliore: #3 [4 scartata per ordinamento parziale]

**Chiamata #5**
- Candidate: #1, #4
- Utilizzabili: #4
- Migliore: #4

**Chiamata #6**
- Candidate: #1, #4, #5, #6
- Utilizzabili: #4, #5, #6
- Migliore: #5 [4 e 6 scartate per ordinamento parziale]

**Chiamata #7**
- Candidate: #1, #4
- Utilizzabili: #4
- Migliore: #4

**Chiamata #8**
- Candidate: #1, #6
- Utilizzabili: #6
- Migliore: #6

**Chiamata #9**
- Candidate: #7
- Utilizzabili: #7
- Migliore: #7

**Chiamata #10**
- Candidate: #7, #8
- Utilizzabili: #7, #8
- Migliore: #8

**Chiamata #11**
- Candidate: #7
- Utilizzabili: #7
- Migliore: #7

**Chiamata #12**
- Candidate: #7, #8
- Utilizzabili: #7, #8
- Migliore: ambiguous -> (errore)