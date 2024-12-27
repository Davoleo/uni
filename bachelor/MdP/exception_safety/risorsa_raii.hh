#ifndef GUARDIA_risorsa_raii_hh
#define GUARDIA_risorsa_raii_hh 1

#include "risorsa_exc.hh"

// classe RAII-RRID (spesso detta solo RAII, per brevità)
// RAII: Resource Acquisition Is Initialization
// RRID: Resource Release Is Destruction
// Paradigma che sfruttta la OOP per creare codice exception safe

class Gestore_Risorsa {
private:
  Risorsa* res_ptr;
public:
  // Costruttore: acquisisce la risorsa (RAII)
  Gestore_Risorsa() : res_ptr(acquisisci_risorsa_exc()) { }

  // Distruttore: rilascia la risorsa (RRID)
  ~Gestore_Risorsa() {
    // Nota: si assume che restituisci_risorsa si comporti correttamente
    // quando l'argimento è il puntatore nullo; se questo non è il caso,
    // è sufficiente aggiungere un test prima dell'invocazione.
    restituisci_risorsa(res_ptr);
  }

  // Disabilitazione delle copie (C++11 only)
  // Prima si creava una definizione privata di questi metodi in modo che non potessero essere chiamati
  Gestore_Risorsa(const Gestore_Risorsa&) = delete;
  Gestore_Risorsa& operator=(const Gestore_Risorsa&) = delete;

  // Costruzione per spostamento (C++11)
  Gestore_Risorsa(Gestore_Risorsa&& y)
    : res_ptr(y.res_ptr) {
    y.res_ptr = nullptr;
  }

  // Assegnamento per spostamento (C++11)
  Gestore_Risorsa& operator=(Gestore_Risorsa&& y) {
    restituisci_risorsa(res_ptr);
    res_ptr = y.res_ptr;
    y.res_ptr = nullptr;
    return *this;
  }

  // Accessori per l'uso (const e non-const)
  const Risorsa* get() const { return res_ptr; }
  Risorsa* get() { return res_ptr; }

  // Alternativa agli accessori: operatori di conversione implicita
  // Permette di evitare di chiamare get() per ottenere il puntatore alla risorsa
  // operator Risorsa*() { return res_ptr; }
  // operator const Risorsa*() const { return res_ptr; }

}; // class Gestore_Risorsa

#endif // GUARDIA_risorsa_raii_hh