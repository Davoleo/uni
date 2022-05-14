// Manual_Generator.hh -----------------------------
#include <string>

class Manual_Generator {
public:
    virtual void put(const std::string& s) = 0;
    virtual void set_boldface() = 0;
    virtual void reset_boldface() = 0;
    // ...
    virtual void hyperlink(const std::string& uri, const std::string& text) = 0;
    virtual void page_break() = 0;

    virtual ~Manual_Generator() { }
};

// codice utente ----------------------------------
void f(Manual_Generator* mg_p)
{
    // ...
    mg_p->hyperlink("http://www.cs.unipr.it/ppl", "PPL");
    // ...
    mg_p->page_break();
    // ...
}

/////////////////////////////////////////////////////

//HTML_Generator.hh

class HTML_Generator : public Manual_Generator {
public:
    void put(const std::string& s) override;
    void set_boldface() override;
    void reset_boldface() override;
    void hyperlink(const std::string& uri, const std::string& text) override;

	void page_break() override {
		//Nota: Usare il tag HR per simulare il cambio pagina in HTML
		this->put("<HR>");
	}
    // ...
};

/////////////////////////////////////////////////////

//HTML_Generator.hh

class ASCII_Generator : public Manual_Generator {
public:
    void put(const std::string& s) override;
    void set_boldface() override;
    void reset_boldface() override;
    void page_break() override;
    // ... 
	void hyperlink(const std::string& uri, const std::string& text) override {
		this->put(text);
		this->put(" (");
		this->put(uri);
		this->put(")");
	}
};
