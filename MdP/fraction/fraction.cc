#include "fraction.hh"

#include <numeric>
#include <cassert>

namespace numbers {

	bool fraction::check_inv() const {
		if (num_ == 0)
			return den_ == 1;

		if (den_ <= 0)
			return false;

		if (std::gcd(num_, den_) != 1)
			return false;

		//A questo punto l'invariante è soddisfatta
		return true;
	}

	// Tramite fraction:: si rientra nello scope della classe -> integer è visibile
	fraction::fraction(const integer& num, const integer& den)
	: num_(num), den_(den) {
		assert(den != 0);
		if (den_ < 0) {
			num_ = -num_;
			den_ = -den_;
		}

		if (num_ == 0) {
			den_ = 1;
			assert(check_inv());
			return;
		}

		integer gcd = std::gcd(num_, den_);
		if (gcd != 1) {
			num_ /= gcd;
			den_ /= gcd;
		}

		//controlla che l'espressione check_inv sia true
		//altrimenti abort sulla linea -> Terminazione brutale
		assert(check_inv());
	}


	//-- Operatori --
	void fraction::operator+=(const fraction& other) {
		//controllo invarianti in ingresso
		assert(check_inv());
		assert(other.check_inv());

		//increment this with other's value
		this->num_ = this->num_ * other.den_ + this->den_ * other.num_;
		this->den_ = this->den_ * other.den_;

		//TODO Implement
		//simplify();

		//controllo invariante in uscita
		assert(check_inv());
	}

	void fraction::operator-=(const fraction& other) {
		//controllo invarianti in ingresso
		assert(check_inv());
		assert(other.check_inv());

		//increment this with other's value
		this->num_ = this->num_ * other.den_ - this->den_ * other.num_;
		this->den_ = this->den_ * other.den_;

		//TODO Implement
		//simplify();

		//controllo invariante in uscita
		assert(check_inv());
	}

	void fraction::operator*=(const fraction& other) {
		//controllo invarianti in ingresso
		assert(check_inv());
		assert(other.check_inv());

		//increment this with other's value
		this->num_ *= other.num_;
		this->den_ *= other.den_;

		//TODO Implement
		//simplify();

		//controllo invariante in uscita
		assert(check_inv());
	}

	void fraction::operator/=(const fraction& other) {
		//controllo invarianti in ingresso
		assert(check_inv());
		assert(other.check_inv());
		//Controllo Precondizioni del metodo
		assert(other.num_ != 0);

		//increment this with other's value
		this->num_ *= other.den_;
		this->den_ *= other.num_;

		//TODO Implement
		//simplify();

		//controllo invariante in uscita
		assert(check_inv());
	}

	fraction& fraction::operator++() {
		assert(this->check_inv());
		this->num_ += this->den_;
		assert(this->check_inv());
		return *this;
	}
	fraction& fraction::operator--() {
		assert(this->check_inv());
		this->num_ -= this->den_;
		assert(this->check_inv());
		return *this;
	}

	void fraction::negate() {
		assert(this->check_inv());
		this->num_ = -this->num_;
		assert(this->check_inv());
	}
	fraction fraction::operator-() const {
		assert(this->check_inv());
		
		fraction res = *this;
		//negazione
		res.negate();
		return res;
	}

	fraction fraction::operator+() const {
		return *this;
	}


	bool fraction::operator==(const fraction& other) const {
		assert(this->check_inv() && other.check_inv());
		return this->num_ == other.num_ && this->den_ == other.den_;
	}

	bool fraction::operator<(const fraction& other) const {
		assert(this->check_inv() && other.check_inv());
		assert(false); //TODO implement
		return false;
	}

	
	fraction operator+(const fraction& x, const fraction& y) {
		fraction res = x;
		res += y;
		return res;
	}

	fraction operator-(const fraction& x, const fraction& y) {
		fraction res = x;
		res -= y;
		return res;
	}

	fraction operator*(const fraction& x, const fraction& y) {
		fraction res = x;
		res *= y;
		return res;
	}

	fraction operator/(const fraction& x, const fraction& y) {
		fraction res = x;
		res /= y;
		return res;
	}

} //namespace numbers