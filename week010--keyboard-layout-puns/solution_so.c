#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

const int Q_TO_D[26] = { 0, 23, 9, 4, -1, 20, 8, 3, 2, 7, 19, 13, 12, 1, 17, 11, -1, 15, 14, 24, 6, 10, -1, 16, 5, -1 };

void puns();
void traverse(int **nodeQwerrty, int **nodeDvorak, char *wordQwerrty, char *wordDvorak, int wordLength);

void puns() {
  int  **pages = malloc(sizeof(int*) * 27 * 500000);
  int **root = pages;
  memset(root, 0, sizeof(int*) * 27);
  pages = pages + 27;
  char buffer[BUFFER_SIZE];
  FILE *file;
  size_t nread;
  file = fopen("/usr/share/dict/words", "r");
  if(file) {
    int **currentLetter = root;
    int skipa = 0;
    int skipb = 0;
    int skip = 0;
    while ((nread = fread(buffer, 1, sizeof buffer, file)) > 0) {
      for(int i = 0; i < nread; i++) {
        int c = (int)buffer[i];
        if(c == 10) {
          if(!skip) {
            currentLetter[26] = (int*)1;
          }
          currentLetter = root;
          skip = 0;
          skipa = 0;
          skipb = 0;
        } else {
          if(c >= 65 && c <= 90) {
            c += 32;
          }
          c -= 97;
          if(c == 22 || c == 25) {
            skip = 1;
          } else if(c == 4 || c == 16) {
            skipa = 1;
          } if(c == 18 || c == 21) {
            skipb = 1;
          }
          if(skipa && skipb) {
            skip = 1;
          }
          if(!skip){
            if((!(currentLetter[c]))) {
              currentLetter[c] = (int*)pages;
              pages = pages + 27;
            }
            currentLetter = (int**)currentLetter[c];
          }
        }
      }
    }
    fclose(file);
    char wordQwerrty[50] = {0};
    char wordDvorak[50] = {0};
    traverse(root, root, wordQwerrty, wordDvorak, 0);
  }
}

void traverse(int **nodeQwerrty, int **nodeDvorak, char wordQwerrty[], char wordDvorak[], int wordLength) {
  if(nodeQwerrty[26] && nodeDvorak[26]) {
    printf("q:%s|d:%s\n", wordQwerrty, wordDvorak);
  }
  for(int i = 0; i < 26; i++) {
    if(Q_TO_D[i] != -1 && nodeQwerrty[i] && nodeDvorak[Q_TO_D[i]]) {
      char newWordQwerrty[50] = {0};
      char newWordDvorak[50] = {0};
      strcpy(newWordQwerrty, wordQwerrty);
      strcpy(newWordDvorak, wordDvorak);
      newWordQwerrty[wordLength] = (char)(i + 97);
      newWordDvorak[wordLength] = (char)(Q_TO_D[i] + 97);
      traverse((int**)nodeQwerrty[i], (int**)nodeDvorak[Q_TO_D[i]], newWordQwerrty, newWordDvorak, wordLength + 1);
    }
  }
}

int main(int argc, char **argv) {
  const float startTime = (float)clock()/CLOCKS_PER_SEC;
  puns();
  const float endTime = (float)clock()/CLOCKS_PER_SEC;
  const float timeElapsed = endTime - startTime;
  printf("%.5f\n", timeElapsed);
  return 0;
}