# LazyPy Example 3: #
# Testing numbers (e.g., factorial) #

def main():
    # Data section #
    i = 1
    n = 0
    f = 1
    
    # Code section #
    print('Write a number:')
    n = int(input())
    
    while i <= n:
        f = f * i
        i = i + 1
    
    print('Factorial:')
    print(f)
    return f

if __name__ == "__main__":
    main()
