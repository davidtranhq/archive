#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

enum class Symbol : char
{
    name, number, end,
    plus = '+', minus = "-", mul = '*', div = '/', print = ';', assign = '=',
    lp = '(', rp = ')'
};

struct Token
{
    Symbol symbol;
    std::string str;
    double num;
};

class TokenStream
{
    public:
        TokenStream(istream &s);
        TokenStream(istream *p);
        
        ~TokenStream();
    
        Token get(); // read and return next token
        const Token &current; // most recently read token
        
        void set_input(istream &s);
        void set_input(istream *s);
        
    private:
        void close();
        
        istream *ip; // pointer to an input stream
        bool owns; // does the ts own the istream?
        Token ct {Symbol::end}; // current Token
}

#endif