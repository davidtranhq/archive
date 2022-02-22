struct X
{
    int i;
    X(int);
    X operator+(int);
};

struct Y
{
    int i;
    Y(X);
    Y operator+(X);
    operator int();
};

extern X operator*(X, Y);
extern int f(X);

X x = 1; // X(int)
Y y = x; // Y(X)
int i = 2;

int main()
{
    i + 10; // int + int
    y + 10; // ambiguous: y.int() + 10 or y.operator+(X{10}) ?
    y + 10 * y; // ambiguous: operator*(int, int) <built-in> or operator*(X{10}, Y)
    
    x + y + i; // x.operator+(y.int()) + i
               // x.operator+(y.int()).operator+(i)
    x * x +i; // operator*(x, Y{x}) + i
              // x.operator+(int)
    
    f(7); // f(X{7})
    f(y); // error: can't convert Y to X (in one implicit step)
    
    y + y; // y.int() + y.int() operator+(int, int) <built-in>
    106 * y; // ambiguous: operator*(int, int) <built-in> or X operator*(X{106}, Y) ?
    
    return 0;
}