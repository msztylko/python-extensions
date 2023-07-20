#include <stdio.h>
#include <stdlib.h>

// extern ispalindrome(char *s, int linelen);

int ispalindrome(char *s, int linelen) {
    int l = 0;
    int h = linelen - 1;

    char scase = 0x00;
    char sl, sh;

    while (l < h) {
        sl = s[l];
        sh = s[h];
        if ('a' <= sl && sl <= 'z')
            scase |= (1 << 0);
        if ('A' <= sl && sl <= 'Z')
            scase |= (1 << 1);
        if ('a' <= sh && sh <= 'z')
            scase |= (1 << 2);
        if ('A' <= sh && sh <= 'Z')
            scase |= (1 << 3);

        while (!(scase & 0x03) && l<h) {
            l++;
            sl = s[l];
            if ('a' <= sl && sl <= 'z')
                scase |= (1 << 0);
            if ('A' <= sl && sl <= 'Z')
                scase |= (1 << 1);
        }
        while (!(scase & 0x0C) && l<h) {
            h--;
            sh = s[h];
            if ('a' <= sh && sh <= 'z')
                scase |= (1 << 2);
            if ('A' <= sh && sh <= 'Z')
                scase |= (1 << 3);
        }
    
        // both uppper
        if ((scase == 0x0A) && (sl != sh))
            return 0;

        // first upper, second lower
        if ((scase == 0x06) && (sl != sh-32))
            return 0;

        // first lower, second upper
        if ((scase == 0x09) && (sl-32 != sh))
            return 0;
        // both lower
        if ((scase == 0x05) && (sl != sh))
            return 0;
        h--;
        l++;
        scase = 0x00;
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
