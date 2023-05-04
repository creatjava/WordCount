#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILENAME_LEN 256
#define MAX_BUFFER_LEN 1024

// 统计字符数或单词数
int wordCount(char* filename, char* param) {
    FILE* fp;
    int count = 0;
    char buffer[MAX_BUFFER_LEN];
    int in_word = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    while (fgets(buffer, MAX_BUFFER_LEN, fp) != NULL) {
        int len = strlen(buffer);
        for (int i = 0; i < len; i++) {
            if (param[1] == 'c') {  // 统计字符数
                count++;
            }
            else if (isspace(buffer[i]) || buffer[i] == ',' || buffer[i] == '.' || buffer[i] == '\n') {
                if (in_word) {  // 当前字符是分隔符并且上一个字符是单词字符
                    count++;
                    in_word = 0;
                }
            }
            else {
                in_word = 1;
            }
        }
    }

    fclose(fp);
    return count;
}

int main(int argc, char* argv[]) {
    char filename[MAX_FILENAME_LEN] = "input.txt";
    char param[3];
    int count;

    if (argc == 1) {
        printf("Usage: WordCount [-c | -w] [input_file_name]\n");
        return 0;
    }
    else if (argc == 2) {
        strcpy(param, argv[1]);
    }
    else if (argc == 3) {
        strcpy(param, argv[1]);
        strcpy(filename, argv[2]);
    }
    else {
        printf("Invalid arguments.\n");
        printf("Usage: WordCount [-c | -w] [input_file_name]\n");
        return 0;
    }

    if (strcmp(param, "-c") != 0 && strcmp(param, "-w") != 0) {
        printf("Invalid parameter.\n");
        printf("Usage: WordCount [-c | -w] [input_file_name]\n");
        return 0;
    }

    count = wordCount(filename, param);
    if (count == -1) {
        return 0;
    }

    if (param[1] == 'c') {
        printf("Characters: %d\n", count);
    }
    else {
        printf("Words: %d\n", count);
    }

    return 0;
}
