// Implement your part 2 solution here
// gcc -lpthread threads.c -o threads

#include <pthread.h>


// Implement your part 2 solution here
// gcc -lpthread threads.c -o threads

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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

void *paint(int workID) {
    printf("Artist %d is painting\n", workID);

    // workID corresponds to the 'artist'
    // Each artist owns one row to paint on.
    // An artist paints along each pixel 1 at a time, painting an
    // R,G,B value (that is why it is 64*3)
//    printf("random %d", printRandoms());
    for (int i = 0; i < 64 * 3; i++) {
        colors[workID][i] = genRandoms(); // Try doing something more interesting with the colors!
//        printf("%d \n", colors[workID][i]);
    }
}

int main() {
    // create thread storage;
//    pthread_t tid[10000];

//    printf("count %d", count);
//    for (int i = 0; i < 10000; ++i) {
//        pthread_create(&tid[i], NULL, thread, NULL);
//
//    }

    pthread_t tid[64];

    int numberOfArtists = 64;

    for (int i = 0; i < numberOfArtists; i++) {
        pthread_create(&tid[i], NULL, paint(i), NULL);
    }


    for (int i = 0; i < 64; ++i) {
        pthread_join(tid[i], NULL);
    }

    printf("Back to main function %ld \n", pthread_self());


    return 0;
};