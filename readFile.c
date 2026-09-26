#include <stdio.h>   // Provides standard input/output functions (e.g., printf, fgets, fopen)
#include <stdlib.h>  // Provides standard utility functions (e.g., exit, malloc)
#include <ctype.h>   // Provides character handling functions (e.g., isdigit, isspace, isalpha)
#include <string.h>  // Provides string manipulation utilities

// Buffer size constant defining the maximum bytes read per line by fgets
#define BUFFER_SIZE 4096

// Struct entity holding all counters and frequency metrics for text analysis
typedef struct {
    int char_count;          // Total character count including spaces
    int char_count_no_space; // Total character count excluding spaces
    int word_count;          // Total word count
    int line_count;          // Total line count (tracks newline characters)
    int sentence_count;      // Total sentence count (tracks '.', '!', '?')
    int digit_count;         // Total numeric digit count ('0'-'9')
    int space_count;         // Total whitespace character count
    int vowel_count;         // Total vowel count ('a', 'e', 'i', 'o', 'u')
    int uppercase_count;     // Total uppercase letter count ('A'-'Z')
    int lowercase_count;     // Total lowercase letter count ('a'-'z')
    int letter_counts[26];   // Frequency array mapping letters 'a' through 'z' (indices 0 to 25)
} TextStats;

// Analyzes a single string buffer and updates the passed TextStats structure instance
void analyze_text(const char *text, TextStats *stats) {
    int in_word = 0; // State flag tracking whether the loop is currently inside a word
    
    // Iterate over each character in the string until the null terminator ('\0')
    for (int i = 0; text[i] != '\0'; i++) {
        // Cast to unsigned char to prevent undefined behavior in ctype functions
        unsigned char c = (unsigned char)text[i];
        
        // Increment total character count
        stats->char_count++;

        // Process whitespace characters
        if (isspace(c)) {
            stats->space_count++; // Increment whitespace counter
            in_word = 0;          // Exit word state when encountering whitespace
        } else {
            stats->char_count_no_space++; // Increment non-whitespace character counter
            
            // If transition from whitespace to non-whitespace occurs, mark start of a new word
            if (!in_word) {
                in_word = 1;         // Set in_word flag
                stats->word_count++; // Increment word counter
            }
        }

        // Check for line breaks
        if (c == '\n') {
            stats->line_count++; // Increment line counter
        }

        // Check for numeric digits
        if (isdigit(c)) {
            stats->digit_count++; // Increment digit counter
        }

        // Check for sentence termination punctuation
        if (c == '.' || c == '!' || c == '?') {
            stats->sentence_count++; // Increment sentence counter
        }

        // Process alphabetic letters
        if (isalpha(c)) {
            // Track uppercase vs lowercase character counts
            if (isupper(c)) {
                stats->uppercase_count++; // Increment uppercase counter
            } else if (islower(c)) {
                stats->lowercase_count++; // Increment lowercase counter
            }

            // Convert character to lowercase for normalized indexing and vowel detection
            unsigned char lower_c = tolower(c);
            
            // Map character to frequency array index: 'a' -> 0, 'b' -> 1, ..., 'z' -> 25
            stats->letter_counts[lower_c - 'a']++;

            // Check for English vowels
            if (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || 
                lower_c == 'o' || lower_c == 'u') {
                stats->vowel_count++; // Increment vowel counter
            }
        }
    }
}

// Formats and prints the analysis metrics into a structured table format to the specified stream
void output_stats(FILE *out_fp, const TextStats *stats) {
    // Print table header and primary text metrics
    fprintf(out_fp, "+-----------------------------------+--------+\n");
    fprintf(out_fp, "| METRIC                            | VALUE  |\n");
    fprintf(out_fp, "+-----------------------------------+--------+\n");
    fprintf(out_fp, "| Total Characters (incl. spaces)   | %-6d |\n", stats->char_count);
    fprintf(out_fp, "| Total Characters (excl. spaces)   | %-6d |\n", stats->char_count_no_space);
    fprintf(out_fp, "| Word Count                        | %-6d |\n", stats->word_count);
    fprintf(out_fp, "| Line Count                        | %-6d |\n", stats->line_count);
    fprintf(out_fp, "| Sentence Count                    | %-6d |\n", stats->sentence_count);
    fprintf(out_fp, "| Vowel Count                       | %-6d |\n", stats->vowel_count);
    fprintf(out_fp, "| Uppercase Letters                 | %-6d |\n", stats->uppercase_count);
    fprintf(out_fp, "| Lowercase Letters                 | %-6d |\n", stats->lowercase_count);
    fprintf(out_fp, "| Digit Count                       | %-6d |\n", stats->digit_count);
    fprintf(out_fp, "| Space Count                       | %-6d |\n", stats->space_count);
    fprintf(out_fp, "+-----------------------------------+--------+\n");
    fprintf(out_fp, "| LETTER FREQUENCIES                | COUNT  |\n");
    fprintf(out_fp, "+-----------------------------------+--------+\n");

    int max_freq = 0;              // Variable to track the highest frequency count
    char most_frequent_letter = '\0'; // Variable to track the letter with highest frequency

    // Iterate through all letter frequency buckets
    for (int i = 0; i < 26; i++) {
        char letter = 'a' + i;
        
        // Print letters that appear at least once
        if (stats->letter_counts[i] > 0) {
            fprintf(out_fp, "|  %c / %c                            | %-6d |\n", 
                    'A' + i, letter, stats->letter_counts[i]);
        }
        
        // Track the letter with the maximum frequency
        if (stats->letter_counts[i] > max_freq) {
            max_freq = stats->letter_counts[i];
            most_frequent_letter = letter;
        }
    }

    // Print summary footer displaying the most frequent letter
    fprintf(out_fp, "+-----------------------------------+--------+\n");
    if (max_freq > 0) {
        fprintf(out_fp, "| Most Frequent Letter: '%c'          | %-6d |\n", 
                most_frequent_letter, max_freq);
    } else {
        fprintf(out_fp, "| Most Frequent Letter              | None   |\n");
    }
    fprintf(out_fp, "+-----------------------------------+--------+\n");
}

// Processes input from a file and optionally writes formatted results to an output file
void process_file(const char *input_filename, const char *output_filename) {
    // Attempt to open input file in read mode
    FILE *file = fopen(input_filename, "r");
    if (!file) {
        perror("Error opening input file"); // Print system error message if file opening fails
        return;
    }

    TextStats stats = {0};   // Initialize all struct counters to zero
    char buffer[BUFFER_SIZE]; // Temporary buffer array for chunk reading

    // Read file line-by-line using buffer size chunking
    while (fgets(buffer, sizeof(buffer), file)) {
        analyze_text(buffer, &stats); // Update statistics with current buffer content
    }
    fclose(file); // Close input file handle

    // Output formatted results to terminal standard output stream
    output_stats(stdout, &stats);

    // If an output filename was provided, save the results into that file
    if (output_filename != NULL) {
        FILE *out_file = fopen(output_filename, "w"); // Open/create output file in write mode
        if (!out_file) {
            perror("Error creating output file");
            return;
        }

        output_stats(out_file, &stats); // Write formatted results to the output file
        fclose(out_file);               // Close output file handle
        printf("\nAnalysis successfully saved to: %s\n", output_filename);
    }
}

// Reads and analyzes multi-line text input directly from standard input (stdin)
void process_user_input(void) {
    printf("Input text (press Ctrl+D on Linux/macOS or Ctrl+Z on Windows to finish):\n\n");

    TextStats stats = {0};   // Initialize all struct counters to zero
    char buffer[BUFFER_SIZE]; // Temporary buffer array for user input

    // Read user input continuously until EOF (Ctrl+D or Ctrl+Z) is encountered
    while (fgets(buffer, sizeof(buffer), stdin)) {
        analyze_text(buffer, &stats); // Update statistics with entered text
    }

    // Output formatted table results to standard output
    output_stats(stdout, &stats);
}

// Interactive main entry point that prompts the user for file paths
int main(void) {
    char input_filename[256];
    char output_filename[256];

    printf("Enter the input filename to read (or '0' to type text directly): ");
    if (scanf("%255s", input_filename) != 1) {
        printf("Invalid input error.\n");
        return 1;
    }

    // Check if the user chose interactive keyboard typing mode
    if (strcmp(input_filename, "0") == 0) {
        process_user_input(); // Allows typing directly in the terminal
    } else {
        printf("Enter the output filename to save results (or '0' to output to terminal only): ");
        if (scanf("%255s", output_filename) != 1) {
            printf("Invalid input error.\n");
            return 1;
        }

        // Process file: pass NULL if output choice is '0'
        if (strcmp(output_filename, "0") == 0) {
            process_file(input_filename, NULL);
        } else {
            process_file(input_filename, output_filename);
        }
    }

    return 0;
}
