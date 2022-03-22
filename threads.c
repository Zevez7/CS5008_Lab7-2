// Implement your part 2 solution here
// gcc -lpthread threads.c -o threads

#include <pthread.h>


// Implement your part 2 solution here
// gcc -lpthread threads.c -o threads

#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int colors[64][64 * 3];

//void *thread(void *vargp) {
//    printf("Hello Thread %d, %ld \n", count, pthread_self());
//    count++;
//
//return NULL;
//}

int genRandoms() {
    return rand() % (256);
}

int counter = 0;

void *paint() {
    printf("Artist is painting %ld \n", pthread_self());

    // workID corresponds to the 'artist'
    // Each artist owns one row to paint on.
    // An artist paints along each pixel 1 at a time, painting an
    // R,G,B value (that is why it is 64*3)
//    printf("random %d", genRandoms());
    for (int i = 0; i < 64 * 3; i++) {
        colors[counter][i] = genRandoms(); // Try doing something more interesting with the colors!
//        printf("random %d", genRandoms());
    }
    counter = counter + 1;
}

int savePPMFile() {
    printf("run savePPMfile");
    FILE *fp;
    fp = fopen("pthread.ppm", "w+");
    fputs("P3\n", fp);
    fputs("64 64\n", fp);
    fputs("255\n", fp);
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64 * 3; j++) {
            fprintf(fp, "%d", colors[i][j]);
            fputs(" ", fp);
        }
        fputs("\n", fp);
    }
    fclose(fp);
}

int main() {

    pthread_t tid[64];

    int numberOfArtists = 64;

    for (int i = 0; i < numberOfArtists; i++) {
        printf("number of Artists %d \n", i);
        pthread_create(&tid[i], NULL, paint, NULL);
    }


    for (int i = 0; i < numberOfArtists; ++i) {
        pthread_join(tid[i], NULL);
    }

    printf("color numbers %d \n", colors[62][23]);
    printf("Back to main function %ld \n", pthread_self());

    savePPMFile();


    return 0;
};