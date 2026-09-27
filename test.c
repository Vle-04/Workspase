#include <stdio.h>
#include <ctype.h>
 
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text-file>\n", argv[0]);
        return 1;
    }
 
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror(argv[1]);
        return 1;
    }
 
    unsigned long long frequency[26] = {0};
    unsigned long long vowels = 0, consonants = 0, words = 0;
    int ch, in_word = 0;
 
    while ((ch = fgetc(file)) != EOF) {
        int letter = (ch >= 'A' && ch <= 'Z') ||
                     (ch >= 'a' && ch <= 'z');
 
        if (letter) {
            int lower = tolower(ch);
            frequency[lower - 'a']++;
            if (lower == 'a' || lower == 'e' || lower == 'i' ||
                lower == 'o' || lower == 'u') {
                vowels++;
            } else {
                consonants++;
            }
            if (!in_word) {
                words++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
    }
 
    if (ferror(file)) {
        perror("Error reading file");
        fclose(file);
        return 1;
    }
    if (fclose(file) == EOF) {
        perror("Error closing file");
        return 1;
    }
 
    printf("Words: %llu\nVowels: %llu\nConsonants: %llu\n",
           words, vowels, consonants);
    puts("Letter frequency:");
    for (int i = 0; i < 26; i++) {
        printf("%c: %llu\n", 'a' + i, frequency[i]);
    }
    return 0;
}
