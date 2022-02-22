class X
{
    public:
    void destroy() { this->~X(); }
    
    private:
    ~X();
};

int main()
{
    X x; // can't construct because destructor is unavailable 
         // for it's destruction at the end of main()
         // https://stackoverflow.com/questions/8824339/destructor-call-during-object-initialization
    X *p = new X;
    delete p; // destructor is private
    p->destroy();
    return 0;
}