# C2Assembly

For certain C programs the translation to assembly is rather straightforward, for example [Fibonacci sequence](https://github.com/msztylko/python-extensions/blob/master/fibonacci/c_fib.c) and its [assembly version](https://github.com/msztylko/python-extensions/blob/master/fibonacci/asm_fib.asm). This is not as easy for more complicated programs as [palindrome](https://github.com/msztylko/python-extensions/blob/master/palindrome/c_palindrome.c). 
And even if it were, it is still useful to consider how given algorithm is going to be realized in the machine code. This can guide it towards more compact/efficient version.

Let's discuss process of translating C to Assembly with Palindrome example.

### C Palindrome first version

```C
bool ispalindrome(char s[], int linelen) {
    int l = 0;
    int h = linelen - 1;

    while (l < h) {
        while (!isalnum(s[l]) && l<h) 
            l++;
        while (!isalnum(s[h]) && l<h) 
            h--;
        if (tolower(s[l++]) != tolower(s[h--]))
            return false;
    }
    return true;
    
}
```

This code is quite compact, but it's due to the usage of functions from the C library. Our handwritten Assembly will not use these functions so let's start by replacing them. 
