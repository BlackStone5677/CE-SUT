#include <stdio.h>
#include <stdlib.h>

int mandelbrot(float real, float imag, int max_iter) {
    float r = 0.0f, i = 0.0f;
    float r2 = 0.0f, i2 = 0.0f;
    int iter = 0;

    while (r2 + i2 <= 4.0f && iter < max_iter) {
        i = 2.0f * r * i + imag;
        r = r2 - i2 + real;

        r2 = r * r;
        i2 = i * i;

        iter++;
    }
    return iter;
}

int main() {
    long width = 1024;
    long height = width / 3;
    int max_iter = 100;

    FILE *f = fopen("mandelbrot.txt", "w");
    if (!f) {
        printf("Failed to open file.\n");
        return 1;
    }

    // allocate one row at a time
    char *line = malloc(width + 2); // +1 for newline, +1 for null terminator
    if (!line) {
        printf("Failed to allocate memory for line buffer.\n");
        fclose(f);
        return 1;
    }

    float real_scale = 2.5f / width;
    float imag_scale = 2.5f / height;

    for (long y = 0; y < height; y++) {
        float imag = y * imag_scale - 1.25f;
        for (long x = 0; x < width; x++) {
            float real = x * real_scale - 2.0f;
            int iter = mandelbrot(real, imag, max_iter);

            // simple ASCII shading
            if (iter == max_iter) line[x] = '#'; // inside Mandelbrot
            else if (iter > max_iter / 2) line[x] = '.';
            else if (iter > max_iter / 4) line[x] = '-';
            else if (iter > max_iter / 8) line[x] = '+';
            else if (iter > max_iter / 16) line[x] = '*';
            else if (iter > max_iter / 32) line[x] = '@';
            else if (iter > max_iter / 64) line[x] = '%';
            else if (iter > max_iter / 128) line[x] = '=';
            else if (iter > max_iter / 256) line[x] = ':';
            else line[x] = ' ';                    // escapes quickly
        }

        line[width] = '\n';
        line[width + 1] = '\0';
        fputs(line, f);
    }

    free(line);
    fclose(f);
    return 0;
}
