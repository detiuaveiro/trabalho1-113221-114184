#include "image8bit.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>

#define NUM_TESTS 20

void runTests() {
    FILE *file = fopen("./locate/results.csv", "w");
    fprintf(file, "Size,Locate,Match,Fail\n");

    for (int i = 1; i <= NUM_TESTS; i++) {
        char subimagePath[32], imagePath[32], not_subimagePath[32];

        // Construct the file paths
        sprintf(subimagePath, "./locate/%d/subimage.pgm", i);
        sprintf(imagePath, "./locate/%d/image.pgm", i);
        sprintf(not_subimagePath, "./locate/%d/not_subimage.pgm", i);

        // Load the images
        Image subimage = ImageLoad(subimagePath);
        Image image = ImageLoad(imagePath);
        Image not_subimage = ImageLoad(not_subimagePath);
        assert(subimage != NULL);
        assert(image != NULL);

        int x, y;

        printf("[%d00%%]\n", i);

        // Test ImageLocateSubImage for a match
        clock_t start = clock();
        int result = ImageLocateSubImage(image, &x, &y, subimage);
        clock_t end = clock();
        double time_taken_locate = ((double)end - start) / CLOCKS_PER_SEC;
        printf("%f\n", time_taken_locate);

        // Test ImageMatchSubImage for a match
        start = clock();
        result = ImageMatchSubImage(image, x, y, subimage);
        end = clock();
        double time_taken_match = ((double)end - start) / CLOCKS_PER_SEC;
        printf("%f\n\n", time_taken_match);

        // Test ImageLocateSubImage for a fail
        start = clock();
        result = ImageLocateSubImage(image, &x, &y, not_subimage);
        end = clock();
        double time_taken_fail = ((double)end - start) / CLOCKS_PER_SEC;
        printf("%f\n", time_taken_fail);

        fprintf(file, "%d00%%,%f,%f,%f\n", i, time_taken_locate, time_taken_match, time_taken_fail);

        // // Test ImageMatchSubImage for a fail
        // start = clock();
        // result = ImageMatchSubImage(image, x, y, not_subimage);
        // end = clock();
        // time_taken = ((double)end - start) / CLOCKS_PER_SEC;
        // printf("%f\n\n", time_taken);
    }
}

int main() {
    runTests();
    return 0;
}
