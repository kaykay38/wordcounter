/**
* wordcounter
*
* This program counts characters, words, lines and paragraphs
* Paragraphs are contiguous lines of text separated by one or more
* lines of blank lines (nothing, spaces, or \t ending with \n).
*
* @Author: Mia Hunt
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h> /* for exit */
#include <unistd.h>

extern int errno;
#define OUT 0;
#define IN 1;
static const char *USAGE = "USAGE: %s [-cwlp] <file>\n";

int main(int argc, char *argv[]) {

  int opt;
  int paraOpt = 0, lineOpt = 0, charOpt = 0, wordOpt = 0;
  int paraCount = 0, lineCount = 0, charCount = 0, wordCount = 0;
  int wordState = 0, paraState = 0, emptyState = 1, prevLineEmpty = 1,
      beginning = 1;
  int argInd = 1;

  while ((opt = getopt(argc, argv, "cwlp")) != -1) {
    switch (opt) {
    case 'c':
      charOpt = 1;
      break;
    case 'w':
      wordOpt = 1;
      break;
    case 'l':
      lineOpt = 1;
      break;
    case 'p':
      paraOpt = 1;
      break;
    default:
      fprintf(stdout, USAGE, argv[0]);
      exit(1);
    }

    argInd = optind ? optind : 1;
  }

  /* check for valid number of arguments and also
   * obtains file name arg index for dash separated flag input
   * i.e. wordcounter -l -p -c file.txt
   */
  char *fileName;
  if (argc >= 1 && argInd < argc) {
    fileName = argv[argInd];
  } else {
    fprintf(stdout, USAGE, argv[0]);
    exit(1);
  }

  FILE *filePtr;
  filePtr = fopen(fileName, "r");

  if (filePtr == NULL) {
    fprintf(stderr, "ERROR %d: file '%s' cannot be read.\n", errno, fileName);
    exit(1);
  } else {
    fprintf(stdout, "File: %s\n", fileName);

    // set all options if no flags are provided
    if (argc == 2 || (!charOpt && !wordOpt && !lineOpt && !paraOpt)) {
      charOpt = 1;
      wordOpt = 1;
      lineOpt = 1;
      paraOpt = 1;
    }
  }

  char ch;
  while ((ch = (getc(filePtr))) && ch != EOF) {

    // check if white space
    if (ch == ' ' || ch == '\t') {
      emptyState = IN;
      beginning = OUT;
    }

    // check if it's non-white space to begin word count
    if (ch != '\n' && ch != ' ' && ch != '\t') {
      if (prevLineEmpty) {
        paraCount++;
      }
      wordState = IN;
      emptyState = OUT;
      beginning = OUT;
      prevLineEmpty = 0;
    }

    // check if at end of line or a space for word count
    if (wordState &&
        (ch == '\n' || ch == ' ' || ch == '\t' || ch == '.' || ch == ',')) {
      wordState = OUT;
      wordCount++;
    }

    // check if new line symbol
    if (ch == '\n') {
      lineCount++;

      // if at beginning or the line is empty, set prevLineEmpty to true
      // for counting paragraphs
      if (beginning || emptyState) {
        prevLineEmpty = 1;
      }
      beginning = IN;
    }

    charCount++;
  }

  if (charOpt) {
    printf("Characters: %d\n", charCount);
  }
  if (wordOpt) {
    printf("Words: %d\n", wordCount);
  }
  if (lineOpt) {
    printf("Lines: %d\n", lineCount);
  }
  if (paraOpt) {
    printf("Paragraphs: %d\n", paraCount);
  }

  fclose(filePtr);

  exit(0);
}
