#include <iostream>

#include "TokenStream.h"

TokenStream::TokenStream(istream &s)
    : ip {&s}, owns {false}
{}

TokenStream::TokenStream(istream *s)
    : ip {s}, owns {true}
{}

TokenStream::~TokenStream()
{
    close();
}

TokenStream::get()
{
    char ch = 0;
    *ip >> ch;
    
    switch (ch)
    {
        case 0:
        
}

TokenStream::set_input(istream &s)
{
    close();
    ip = &s;
    owns = false;
}

TokenStream::set_input(istream *s)
{
    close();
    ip = s;
    owns = true;
}

TokenStream::close()
{
    if (owns)
        delete ip;
}