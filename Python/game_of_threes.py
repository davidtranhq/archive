x = int(input("Enter a number: "))
while x > 1:
    t = (0, -1, 1)[x%3]
    print(x, t)
    x //= 3 if x%3 else x+t
    
print(x)