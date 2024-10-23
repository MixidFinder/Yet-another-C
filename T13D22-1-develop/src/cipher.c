#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENG 26

char *input(int *err);
void menu(int *choice, int *err, int *exit, char **buffer, int *buffer_size, char **name);
void readFile(char *name, char **buffer, int *buffer_size);
void input_choice(int *choice, int *err);
void writeFile(char *name, char *stringa);
void clearFile(char *path, int *err);
void encryptFile(char *path, int *err, int shift);
int input_shift(int *err);

int main(void) {
    int err = 0, exit = 0, choice;
    char *buffer = NULL, *name = NULL;
    int buffer_size = 0;

    while (!err && !exit) {
        input_choice(&choice, &err);
        menu(&choice, &err, &exit, &buffer, &buffer_size, &name);
    }

    if (err) {
        printf("n/a");
    } else {
        printf("%s", buffer);
    }

    if (buffer) {
        free(buffer);
    }
    if (name) {
        free(name);
    }

    return 0;
}

char *input(int *err) {
    int cap = 10, len = 0, ch;
    char *name = malloc(cap);

    if (!name) {
        *err = 1;
        return NULL;
    }

    while ((ch = getchar()) != EOF && ch != '\n' && !*err) {
        if (len >= cap) {
            char *temp = realloc(name, cap *= 2);
            if (!temp) {
                if (name) {
                    free(name);
                }
                *err = 1;
                return NULL;
            }
            name = temp;
        }
        name[len++] = ch;
    }

    if (len == 0 && ch == EOF) {
        if (name) {
            free(name);
        }
        *err = 1;
        return NULL;
    }

    name[len] = '\0';
    char *temp = realloc(name, len + 1);
    if (!temp) {
        if (name) {
            free(name);
        }
        *err = 1;
        return NULL;
    }

    name = temp;
    if (temp) {
        free(temp);
    }

    return name;
}

void input_choice(int *choice, int *err) {
    if (scanf("%d", choice) != 1 || *choice < -1 || *choice > 3 || *choice == 0) {
        *err = 1;
    }
    while (getchar() != '\n')
        ;
}

int input_shift(int *err) {
    int shift;
    if (scanf("%d", &shift) != 1) {
        *err = 1;
        return 0;
    }
    return shift;
}

void menu(int *choice, int *err, int *exit, char **buffer, int *buffer_size, char **name) {
    char *stringa = NULL;
    char *path = NULL;
    if (*choice == 1 && !*err) {
        *name = input(err);
        if (!*err) {
            readFile(*name, buffer, buffer_size);
        }
    } else if (*choice == 2) {
        stringa = input(err);
        if (!*err) {
            writeFile(*name, stringa);
            readFile(*name, buffer, buffer_size);
        }
    } else if (*choice == 3) {
        printf("Input path\n");
        path = input(err);
        printf("Input shift\n");
        int shift = input_shift(err);
        if (!*err) {
            clearFile(path, err);
            encryptFile(path, err, shift);
        }
    } else if (*choice == -1) {
        if (stringa) {
            free(stringa);
        }
        if (path) {
            free(path);
        }
        *exit = 1;
    }
}

void readFile(char *name, char **buffer, int *buffer_size) {
    FILE *file = fopen(name, "r");
    int ch, local_buffer_size = 0;
    char *local_buffer = NULL;
    int is_empty = 1;

    if (!file) {
        char *temp = realloc(*buffer, (*buffer_size + 4));
        if (!temp) {
            free(*buffer);
            *buffer = NULL;
            return;
        }
        *buffer = temp;
        strcpy(*buffer + *buffer_size, "n/a\n");
        *buffer_size += 4;
        return;
    }

    while ((ch = getc(file)) != EOF) {
        is_empty = 0;
        char *temp = realloc(local_buffer, local_buffer_size + 1);
        if (!temp) {
            free(local_buffer);
            local_buffer = NULL;
            break;
        }
        local_buffer = temp;
        local_buffer[local_buffer_size++] = ch;
    }

    if (is_empty) {
        char *temp = realloc(*buffer, (*buffer_size + 4));
        if (!temp) {
            free(*buffer);
            *buffer = NULL;
            return;
        }
        *buffer = temp;
        strcpy(*buffer + *buffer_size, "n/a\n");
        *buffer_size += 4;
    } else if (local_buffer) {
        local_buffer[local_buffer_size] = '\0';
        char *temp = realloc(*buffer, *buffer_size + local_buffer_size + 1);
        if (!temp) {
            free(*buffer);
            free(local_buffer);
            *buffer = NULL;
            return;
        }
        *buffer = temp;
        strcpy(*buffer + *buffer_size, local_buffer);
        *buffer_size += local_buffer_size;
        free(local_buffer);
    }

    if (!is_empty) {
        char *temp = realloc(*buffer, *buffer_size + 1);
        if (!temp) {
            free(*buffer);
            *buffer = NULL;
            return;
        }
        *buffer = temp;
        (*buffer)[(*buffer_size)++] = '\n';
    }

    fclose(file);
}

void writeFile(char *name, char *stringa) {
    FILE *file = fopen(name, "a");
    fputs(stringa, file);
    fclose(file);
}

void clearFile(char *path, int *err) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (dir == NULL) {
        *err = 1;
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char *ext = strrchr(entry->d_name, '.');
            if (ext && strcmp(ext, ".h") == 0) {
                char full_path[1000];
                snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
                FILE *file = fopen(full_path, "w");
                if (file == NULL) {
                    *err = 1;
                    closedir(dir);
                    return;
                }
                printf("Clearing file: %s\n", full_path);

                fclose(file);
            }
        }
    }

    closedir(dir);
}

void encryptFile(char *path, int *err, int shift) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (dir == NULL) {
        *err = 1;
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char *ext = strrchr(entry->d_name, '.');
            if (ext && strcmp(ext, ".c") == 0) {
                char full_path[1000];
                snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
                FILE *file = fopen(full_path, "r+");
                if (file == NULL) {
                    *err = 1;
                    closedir(dir);
                    return;
                }

                printf("Encrypting file: %s\n", full_path);
                char ch;
                long pos;
                while ((ch = getc(file)) != EOF) {
                    pos = ftell(file) - 1;
                    if (ch >= 'A' && ch <= 'Z') {
                        ch = ch + (shift % ENG);
                        if (ch > 'Z') {
                            ch = 'A' + (ch - 'Z') - 1;
                        }
                    } else if (ch >= 'a' && ch <= 'z') {
                        ch = ch + (shift % ENG);
                        if (ch > 'z') {
                            ch = 'a' + (ch - 'z') - 1;
                        }
                    }
                    fseek(file, pos, SEEK_SET);
                    fprintf(file, "%c", ch);
                    fseek(file, pos + 1, SEEK_SET);
                }

                fclose(file);
            }
        }
    }

    closedir(dir);
}