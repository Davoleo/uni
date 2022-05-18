#ifndef EXCEPTION_SAFE_STACK_HH_INCLUDE_GUARD
#define EXCEPTION_SAFE_STACK_HH_INCLUDE_GUARD 1

#include <cassert>
// Contiene size_t (port di stddef.h)
#include <cstddef>
#include <iostream>
#include <string>

// new, delete, new[], delete[]

// Fasi di costruzione
// allocazione memoria agrezza senza costruzione:	operator new / operator new[]
// costruzione senza allocazione: 					new di piazzamento in ptr: new (ptr) T(...);

// Fasi di distruzione
// distruzione esplicita (senza deallocazione): vec_[i].~T();
// deallocazione memoria grezza: operator delete / operator delete[]

// Nota: tutti i dati e le funzioni membro sono pubblici:
//  Questa classe NON fornisce una interfaccia verso l'utente

// Mantiene al suo interno *esattamente* size_ elementi.
// Per le posizioni di indice i tali che size_ <- i < capacity_,
// Abbiamo memoria grezza allocata, ma non abbiamo oggetti costruiti
template <typename T>
struct Stack_Impl {
    using size_type = std::size_t;

    T* vec_;
    size_type size_;
    size_type capacity_;

    // Controllo invariante di classe: vogliamo consentire il caso dello staack di capacità 0
    //  Non è possibile controllare che lo stack contenga effettivamente size_ elementi
    bool check_inv() const
    {
        if (capacity_ == 0 && vec_ != nullptr) {
#ifndef NDEBUG
            std::cerr << "Lo stack è dichiarato avere una capacità nilla ma ha risorse allocate!" << std::endl;
#endif
            return false;
        }
        if (size_ > capacity_) {
#ifndef NDEBUG
            std::cerr << "Lo stack è dichiarato avere una dimensione superiore alla capacità!" << std::endl;
#endif
            return false;
        }
        if (capacity_ == 0 && vec_ == nullptr) {
#ifndef NDEBUG
            std::cerr << "Non ci sono risorse allocate per lo stack!" << std::endl;
#endif
            return false;
        }
        return true;
    }

    void make_empty() noexcept
    {
        // Distrugge esplicitamente gli elementi effettivamente presenti (senza deallocazione memoria grezza)
        for (size_type i = size_; i-- > 0;)
            vec_[i].~T();
        // dealloca la memoria grezza
        operator delete(vec_);
        vec_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    Stack_Impl() noexcept
        : vec_(nullptr)
        , size_(0)
        , capacity_(0)
    {
    }

    explicit Stack_Impl(size_type capacity)
        : Stack_Impl()
    {
        if (capacity == 0)
            return;

        // Allocazione memoria grezza
        vec_ = static_cast<T*>(operator new(sizeof(T) * capacity));
        capacity_ = capacity;
    }

    void swap(Stack_Impl& other) noexcept
    {
        using std::swap;
        swap(this->vec_, other.vec_);
        swap(this->size_, other.size_);
        swap(this->capacity_, other.capacity_);
    }

    // Disabilitazione operatori di copia
    Stack_Impl(const Stack_Impl&) = delete;
    Stack_Impl& operator=(const Stack_Impl&) = delete;

    // Move Constructor: Crea uno stack vuoto in this e lo scambia con other
    Stack_Impl(Stack_Impl&& other) noexcept
        : Stack_Impl()
    {
        this->swap(other);
    }

    // Move Assignment: rilascia le risorse dello stack (ripristina lo stato a vuoto) e ruba le risorse da other
    Stack_Impl& operator=(Stack_Impl&& other) noexcept
    {
        this->make_empty();
        this->swap(other);
        return *this;
    }

    // Distruttore svuota lo stack
    ~Stack_Impl()
    {
        this->make_empty();
    }
};

template <typename T>
class Stack {
public:
    using size_type = typename Stack_Impl<T>::size_type;

    // Costruttore di default.
    explicit Stack(size_type capacity = 16)
        : impl(capacity)
    {
        assert(check_inv());
    }

	// Costruttore di copia.
    Stack(const Stack& y) {
		//Copio solo gli size_ elementi effettivamente presenti
		for (size_type i = 0; i < y.impl.size_; ++i) {
			//new di piazzamento: costruisce T all'indirizzo specifico
			//Senza allocare nuova memoria
			new (impl.vec_ + i) T(y.impl.vec_[i]);
			//Aggiorno immediatamente il numero di elementi presenti
			//Essenziale per l'exception safety
			//Se non si sa il numero di elementi costruiti, se qualcosa va storto stack_impl non sa quanti elementi deve distruggere
			++impl.size_;
		}
		assert(check_inv());
	}

    void swap(Stack& y) noexcept {
		impl.swap(y.impl);
		assert(this->check_inv());
		assert(y.check_inv());
	}

	//Assegnamento per copia: costruttore per copia + swap
    Stack& operator=(const Stack& y) {
		Stack temp(y);
		swap(temp);
		return *this;
	}

    //Move Constructore e assignment e distruttore di default vanno bene (invocano le corrispondenti operazioni su Stack_Impl)
    Stack(Stack&& y) = default;
    Stack& operator=(Stack&& y) = default;
    ~Stack() = default;

    size_type size() const {
		return impl.size_;
	}

    bool is_empty() const {
		return size() == 0;
	}

    T& top() {
		assert(size() > 0);
		return impl.vec_[impl.size_ - 1];
	}
    const T& top() const {
		assert(size() > 0);
		return impl.vec_[impl.size_ - 1];
	}

	bool check_inv() const {
		return impl.check_inv();
	}

    void push(const T& elem) {
		if (impl.size_ == impl.capacity_)
			reallocate(impl.capacity_ * 2 + 1);
		//New Di piazzamento: una copia di T viene costruita direttamente all'indirizzo specificato (senza allocazione)
		new (impl.vec_ + impl.size_) T(elem);
		++impl.size_;
	}

	void push(T&& elem) {
		if (impl.size_ == impl.capacity_)
			reallocate(impl.capacity_ * 2 + 1);
		//New Di piazzamento: elem viene spostato direttamente all'indirizzo specificato (senza allocazione)
		new (impl.vec_ + impl.size_) T(std::move(elem));
		++impl.size_;
	}

    void pop() {
		assert(size() > 0);
		--impl.size_;
		//Distruzione esplicita (no deallocazione)
		impl.vec_[impl.size_].~T();
	}

private:
	Stack_Impl<T> impl;

	void reallocate(size_type new_capacity) {
		assert(impl.size_ <= new_capacity);
		Stack temp(new_capacity);
		for(size_type i = 0; i < impl.size_; ++i) {
			temp.push(std::move(impl.vec_[i]));
		}
		this->swap(temp);
	}
};

#endif //EXCEPTION_SAFE_STACK_HH_INCLUDE_GUARD