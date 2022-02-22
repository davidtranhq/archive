name = input("What's your name? ")
age = input("How old are you? ")

with open("docs/who_you_is.txt", "a") as f:
    f.write("%s %s" % (name, age))

print("Your name is %s and you are %s years old." % (name, age))