void f1(char *, int &);
void (*f2)(char *, int &);
void f4(void (*f3)(char *, int &));
void (*f6)();

int main()
{
    return 0;
}
