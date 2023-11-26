#include "image8bit.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>

#define NUM_TESTS 20

void runTests() {
    FILE *file = fopen("./locate/results.csv", "w");
    fprintf(file, "Size,Best,Worst\n");

    for (int i = 1; i <= NUM_TESTS; i++) {
        char subimagePath[32], imagePath[32], not_subimagePath[32];

        // Construct the file paths
        sprintf(subimagePath, "./locate/%d/subimage.pgm", i);
        sprintf(imagePath, "./locate/%d/image.pgm", i);
        sprintf(not_subimagePath, "./locate/%d/not_subimage.pgm", i);

        // Load the images
        Image image = ImageLoad(imagePath);
        Image subimage = ImageLoad(subimagePath);
        Image not_subimage = ImageLoad(not_subimagePath);
        assert(subimage != NULL);
        assert(image != NULL);

        int x, y;

        printf("[%d00%%]\n", i);

        // Best case scenario
        clock_t start = clock();
        int result = ImageLocateSubImage(image, &x, &y, subimage);
        clock_t end = clock();
        double time_taken_best = ((double)end - start) / CLOCKS_PER_SEC;
        printf("%f\n", time_taken_best);

        // Worst case scenario
        start = clock();
        result = ImageLocateSubImage(image, &x, &y, not_subimage);
        end = clock();
        double time_taken_worst = ((double)end - start) / CLOCKS_PER_SEC;
        printf("%f\n", time_taken_worst);

        fprintf(file, "%d00%%,%f,%f,%f\n", i, time_taken_best, time_taken_worst);
    }
}

int main() {
    runTests();
    return 0;
}
