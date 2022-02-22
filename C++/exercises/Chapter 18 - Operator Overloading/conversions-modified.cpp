struct X
{
    int i;
    X(int ii) : i{ii} {}
    X operator+(int a) { return X{i+a}; };
};

struct Y
{
    int i;
    Y(X x) : i{x.i} {}
    Y operator+(X x) { return Y{i + x.i}; }
    explicit operator int() const { return i; }
};

extern X operator*(X x, Y y)
{
    return X{x.i * y.i};
}

extern int f(X x)
{
    return x.i;
}

X x = 1; // X(int)
Y y = x; // Y(X)
int i = 2;

int main()
{
    i + 10; // int + int
    y + 10; // ambiguous: y.int() + 10 or y.operator+(X{10}) ?
    y + 10 * y; // ambiguous: operator*(int, int) <built-in> or operator*(X{10}, Y)
    
    x + int{y} + i; // x.operator+(y.int()) + i
               // x.operator+(y.int()).operator+(i)
    x * x +i; // operator*(x, Y{x}) + i
              // x.operator+(int)
    
    f(7); // f(X{7})
    f(int{y}); // error: can't convert Y to X (in one implicit step)
    
    int{y} + int{y}; // y.int() + y.int() operator+(int, int) <built-in>
    106 * y; // ambiguous: operator*(int, int) <built-in> or X operator*(X{106}, Y) ?
    
    return 0;
}