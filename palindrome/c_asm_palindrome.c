#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// extern ispalindrome(char *s, int linelen);

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


int main() {
  size_t len;
  ssize_t read;
  char *line = NULL;
  while ((read = getline(&line, &len, stdin)) != -1) {
    
    if (ispalindrome(line, read))
      printf("%s", line);
  }

  if (ferror(stdin))
    fprintf(stderr, "Error reading from stdin");

  free(line);
  fprintf(stderr, "ok\n");
}
