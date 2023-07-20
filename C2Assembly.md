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

### C Palindrome second version

Function calls replaced by primitive operations.

```C
int ispalindrome(char *s, int linelen) {
    int l = 0;
    int h = linelen - 1;

    while (l < h) {
        while (!(('A' <= s[l] && s[l] <= 'Z') || ('a' <= s[l] && s[l] <= 'z')) && l<h)
            l++;
        while (!(('A' <= s[h] && s[h] <= 'Z') || ('a' <= s[h] && s[h] <= 'z')) && l<h)
            h--;
        // both uppper
        if (('A' <= s[l] && s[l] <= 'Z') && ('A' <= s[h] && s[h] <= 'Z')) {
            if (s[l] != s[h])
                return 0;
        }   
        // first upper, second lower
        if (('A' <= s[l] && s[l] <= 'Z') && ('a' <= s[h] && s[h] <= 'z')) {
            if (s[l] != (s[h] - 32))
                return 0;
        }   
        // first lower, second upper
        if (('a' <= s[l] && s[l] <= 'z') && ('A' <= s[h] && s[h] <= 'Z')) {
            if ((s[l] - 32) != s[h])
                return 0;
        }   
        // both lower
        if (('a' <= s[l] && s[l] <= 'z') && ('a' <= s[h] && s[h] <= 'z')) {
            if (s[l] != s[h])
                return 0;
        }   
        h--;
        l++;
    }   
    return 1;
}
```

This version is more mechanistic so it will be easier to translate to Assembly. However, it is clear that there is a lot of redundant computations so let's start by simplifying them.
