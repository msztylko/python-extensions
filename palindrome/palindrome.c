#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool ispalindrome(char s[]) {
    int l = 0;
    int h = strlen(s) -1; 
    // one for \n and one due to index from 0
    if (s[h] == '\n')
        h--;

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

int main() {
  size_t len;
  ssize_t read;
  char *line = NULL;
  while ((read = getline(&line, &len, stdin)) != -1) {
    
    if (ispalindrome(line))
      printf("%s", line);
  }

  if (ferror(stdin))
    fprintf(stderr, "Error reading from stdin");

  free(line);
  fprintf(stderr, "ok\n");
}
