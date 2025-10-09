#include <stdio.h>

int main() {
    FILE* fp;
    int a[] = {0, 1, 2}, ra[3];
    char b[] = "ABC", rb[3];
    float c[] = {1.1, 1.2, 1.3}, rc[3];

    fp = fopen("a.bin", "wb");
    fwrite(a, sizeof a, 1, fp);
    fwrite(b, sizeof b - 1, 1, fp); 
    fwrite(c, sizeof c, 1, fp);
    fclose(fp);

    fp = fopen("a.bin", "rb");
    fread(ra, sizeof ra, 1, fp);
    fread(rb, sizeof rb, 1, fp);
    fread(rc, sizeof rc, 1, fp);
    fclose(fp);

    for (int i = 0; i < 3; i++) printf("%d ", ra[i]);
    printf("\n");
    for (int i = 0; i < 3; i++) printf("%c ", rb[i]);
    printf("\n");
    for (int i = 0; i < 3; i++) printf("%.6f ", rc[i]);
    printf("\n");

    return 0;
}
