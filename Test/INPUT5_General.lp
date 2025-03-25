# LazyPy Example 5
# The program is "lexically" correct and should not generate any error (based on Platypus from Svillen Ranev)

def main():
    # Data section
    i = 0
    a = 1.2
    sum008 = 7.87050
    text = ""
    
    # Code section
    a = 1.2
    sum008 = 7.87050
    a, sum008 = map(float, input().split())
    i = 0
    while i <= 32767:
        i = i + 2
        a = a * i / 0.5
        sum008 = sum008 + a - 1
    
    if text == "":
        text = 'prog' + 'ram'
    else:
        text = text + 'ram'
    
    print("\* This is a program -:)-<-<-- \*")
    print(text)
    
    if text != 'program' and sum008 == 8.0 or i > 10:
        print(sum008)
        print()

if __name__ == "__main__":
    main()
