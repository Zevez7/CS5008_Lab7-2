//
// Created by datgu on 3/20/2022.
//

// Implement your part 1 solution here
// gcc vfork.c -o vfork

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
//#include <sys/wait.h> // Library with the 'wait' system call.

int colors[64][64 * 3];

// Modify your paint function here
void paint(int workID, struct _iobuf *fp) {
    printf("Artist %d is painting\n", workID);
//
//    FILE *fp;
//    fp = fopen("vfork.ppm", "w+");
//    fputs("P3\n", fp);
//    fputs("64 64\n", fp);
//    fputs("255\n", fp);

//    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64 * 3; j++) {
            fprintf(fp, "%d", colors[workID][j]);
            if ((j + 1) % 3 == 0) {
                fputs("space", fp);
                printf("space me");

            } else{

                fputs("2", fp);

            }
        }
        fputs("\n", fp);
//    }
//    fclose(fp);
}

int main(int argc, char **argv) {


//    int* integers = malloc(sizeof(int)*8000);
    int numberOfArtists = 64; // How many child processes do we want?

    pid_t pid;
    FILE *fp;
    fp = fopen("vfork.ppm", "w+");
    fputs("P3\n", fp);
    fputs("64 64\n", fp);
    fputs("255\n", fp);


    // main loop where we fork new threads
    for (int i = 0; i < numberOfArtists; i++) {
        // (1) Perform a fork
        pid_t vfork();


        // (2) Make only the child do some work (i.e. paint) and then terminate.
        if (pid == 0) {

            paint(i,fp);
            exit(0);

        }
    }

    fclose(fp);
//
//    pid_t wpid;
//    int status = 0;
//    while ((wpid = wait(&status)) > 0);

    printf("parent is exiting(last artist out!)\n");

//    free(integers);

    return 0;
}