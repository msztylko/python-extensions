#include <stdio.h>
#include <stdlib.h>

#define BOTH_UPPER          0x0A
#define FIRST_UP_SECOND_LOW 0x06
#define FIRST_LOW_SECOND_UP 0x09
#define BOTH_LOWER          0x05
#define L_ALNUM             0x03
#define H_ALNUM             0x0C

char ispalindrome(char *s, char linelen) {
    char l = 0;
    char h = linelen - 1;

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

        while (!(scase & L_ALNUM)) {
            sl = s[++l];
            if ('a' <= sl && sl <= 'z')
                scase |= (1 << 0);
            if ('A' <= sl && sl <= 'Z')
                scase |= (1 << 1);
        }
        while (!(scase & H_ALNUM)) {
            sh = s[--h];
            if ('a' <= sh && sh <= 'z')
                scase |= (1 << 2);
            if ('A' <= sh && sh <= 'Z')
                scase |= (1 << 3);
        }
    
        if ((scase == BOTH_UPPER) && (sl != sh))
            return 0;

        if ((scase == FIRST_UP_SECOND_LOW) && (sl != sh-32))
            return 0;

        if ((scase == FIRST_LOW_SECOND_UP) && (sl-32 != sh))
            return 0;

        if ((scase == BOTH_LOWER) && (sl != sh))
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
