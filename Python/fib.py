def fib(x):
    l, h = 1, 1
    print(l)
    while h < int(x):
        print(h)
        l, h = h, l+h
        
    
if __name__ == "__main__":
    x = input("Fib limit: ")
    fib(x)
