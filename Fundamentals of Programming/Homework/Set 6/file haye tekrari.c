#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <openssl/sha.h>

#define MAX_FILES 10000
#define MAX_PATH 4096
#define NAME_LEN 256

typedef struct {
    char name[NAME_LEN];
    char path[MAX_PATH];
    unsigned char hash[SHA256_DIGEST_LENGTH];
} FileInfo;

FileInfo files[MAX_FILES];
int file_count = 0;

void compute_sha256(const char *path, unsigned char *out) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        memset(out, 0, SHA256_DIGEST_LENGTH);
        return;
    }

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    unsigned char buffer[8192];
    size_t n;

    while ((n = fread(buffer, 1, sizeof(buffer), f)) > 0)
        SHA256_Update(&ctx, buffer, n);

    SHA256_Final(out, &ctx);
    fclose(f);
}

void scan_dir(const char *dir) {
    DIR *dp = opendir(dir);
    if (!dp) return;

    struct dirent *entry;

    while ((entry = readdir(dp))) {

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        char full[MAX_PATH];
        snprintf(full, sizeof(full), "%s/%s", dir, entry->d_name);

        DIR *sub = opendir(full);
        if (sub) {
            closedir(sub);
            scan_dir(full);
        } else {
            if (file_count >= MAX_FILES) continue;

            FileInfo *f = &files[file_count++];

            strncpy(f->name, entry->d_name, NAME_LEN - 1);
            f->name[NAME_LEN - 1] = '\0';

            strncpy(f->path, full, MAX_PATH - 1);
            f->path[MAX_PATH - 1] = '\0';

            compute_sha256(full, f->hash);
        }
    }

    closedir(dp);
}

int cmp_files(const void *a, const void *b) {
    const FileInfo *fa = a;
    const FileInfo *fb = b;

    int name_cmp = strcmp(fa->name, fb->name);
    if (name_cmp != 0) return name_cmp;

    return memcmp(fa->hash, fb->hash, SHA256_DIGEST_LENGTH);
}

int cmp_paths(const void *a, const void *b) {
    const char *pa = *(const char **)a;
    const char *pb = *(const char **)b;
    return strcmp(pa, pb);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <folder_path>\n", argv[0]);
        return 1;
    }

    scan_dir(argv[1]);

    qsort(files, file_count, sizeof(FileInfo), cmp_files);

    printf("Duplicated Files List:\n");

    int index = 1;
    int i = 0;

    while (i < file_count) {

        int j = i + 1;

        while (j < file_count &&
               strcmp(files[i].name, files[j].name) == 0 &&
               memcmp(files[i].hash, files[j].hash, SHA256_DIGEST_LENGTH) == 0)
            j++;

        int count = j - i;

        if (count > 1) {

            printf("%d.(%s)\n", index++, files[i].name);

            char **paths = malloc(count * sizeof(char *));
            for (int k = 0; k < count; k++)
                paths[k] = files[i + k].path;

            qsort(paths, count, sizeof(char *), cmp_paths);

            for (int k = 0; k < count; k++)
                printf("%s\n", paths[k]);

            free(paths);
        }

        i = j;
    }

    return 0;
}