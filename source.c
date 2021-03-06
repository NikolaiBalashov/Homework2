#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    int n;
    int k = 0;
    int f = 0;
    int t = 1;
    int l = 0;
    bool flag = false;
    bool prov = false;
    scanf_s("%d", &n);
    int* arr = (int*)malloc(n * n * sizeof(int));

    for (int i = 0; i < n; i++) {
        printf("%d:", i);

        for (int j = 0; j < n; j++) {
            scanf_s("%d", (arr + i * n + j));
        }
    }
    printf("\n");

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if ((i == j) && (arr[i * n + j] != 0)) {    //diagonal check
                prov = true;
            }

            if (arr[i * n + j] != arr[j * n + i]) {     //diagonal symmetry check
                prov = true;
            }

            if ((arr[i * n + j] != 0) && (arr[i * n + j] != 1)) {      //check connections 
                prov = true;
            }

            if (arr[i * n + j] == 1) {      //check if each point has exactly 2 connections
                k++;
            }

            if (k > 2) {
                prov = true;
            }
        }
        k = 0;
    }

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if ((arr[k * n + j] == 1) && (j != t) && (flag == false)) {     //depth-first search
                t = k;
                k = j;
                flag = true;
            }
        }
        flag = false;

        if ((k == 0) && (i != n - 1)) {
            prov = true;
        }

        if ((i == n - 1) && (k != 0)) {
            prov = true;
        }
    }
    if (prov == false) {
        printf("simple cycle");
    }
    else
        printf("not a simple cycle");

    // visualisation //

    FILE* file;

    if ((file = fopen("Dot_file.txt", "w")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    fprintf(file, "graph G{\n");

    for (int i = 0; i < n; i++) {

        for (int j = 0; j <= i; j++) {

            if (arr[i * n + j] != 0) {

                for (int g = 0; g < arr[i * n + j]; g++) {
                    fprintf(file, "%d -- %d;\n", (i + 1), (j + 1));
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((arr[i * n + j]) == 0) {
                l++;
            }
        }
        if (l == n) {
            fprintf(file, "%d;\n", (i + 1));
        }
        l = 0;
    }

    fprintf(file, "}");
    fclose(file);
    system("dot C:\\Users\\Admin\\source\\repos\\C\\Project1\\Project1\\Dot_file.txt -Tbmp -o dot_file.bmp");
    system("rundll32 \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen C:\\Users\\Admin\\source\\repos\\C\\Project1\\Project1\\Dot_file.bmp");
    return (0);
}
