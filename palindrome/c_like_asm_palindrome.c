#include <stdio.h>
#include <stdlib.h>

#define L_BIT 0x20

char ispalindrome(char *s, char linelen) {
    char l = 0;
    char h = linelen - 1;

    char sl, sh;

    while (l < h) {
        sl = s[l];
        sh = s[h];

        while (sl < '@')
            sl = s[++l];
        while (sh < '@')
            sh = s[--h];

        if ((sl & L_BIT) && (sh & L_BIT)) {
            if (sl != sh)
                return 0;
        }

        if (!(sl & L_BIT) && !(sh & L_BIT)) {
            if (sl != sh)
                return 0;
        }
        if ((sl & L_BIT) && !(sh & L_BIT)) {
            if (sl - 32 != sh)
                return 0;
        }
        if (!(sl & L_BIT) && (sh & L_BIT)) {
            if (sl != sh - 32)
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
