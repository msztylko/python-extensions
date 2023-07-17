#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int fib(int n) {
    if (n < 2)
        return n;
    else
        return fib(n-1) + fib(n-2);
}

int main() {
    size_t len;
    ssize_t read;
    char *line = NULL;
    char *number = NULL;
    int n;

    while ((read = getline(&line, &len, stdin)) != -1) {
        number = strtok(line, "\t");
        n = atoi(number);
        printf("%s\t%lld\n", number, fib(n));
    }
}
