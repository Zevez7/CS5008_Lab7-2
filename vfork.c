#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Global array
// This is our 'canvas' we are painting on.
// It is 64 rows by 64 columns (each pixel stores 3 color components, R,G,B)
int colors[64][64 * 3];

int genRandoms() {
    return rand() % (256);
}

int savePMMFile(){

    FILE *fp;
    fp = fopen("vfork.ppm","w+");
    fputs("P3\n",fp);
    fputs("64 64\n",fp);
    fputs("255\n",fp);
    for(int i =0; i < 64;i++){
        for(int j =0; j < 64*3; j++){
            fprintf(fp,"%d",colors[i][j]);
            fputs(" ",fp);
        }
        fputs("\n",fp);
    }
    fclose(fp);
}
// Paint function called from each child
void paint(int workID) {
    printf("Artist %d is painting\n", workID);

    // workID corresponds to the 'artist'
    // Each artist owns one row to paint on.
    // An artist paints along each pixel 1 at a time, painting an
    // R,G,B value (that is why it is 64*3)
//    printf("random %d", printRandoms());
    for (int i = 0; i < 64 * 3; i++) {
        colors[workID][i] = genRandoms(); // Try doing something more interesting with the colors!
    }
}

int main(int argc, char **argv) {

    // Represents how many child processes we want.
    // In this case--64.
    int numberOfArtists = 64;
    // Store the process id.
    pid_t pid;

    for (int i = 0; i < numberOfArtists; i++) {
        pid = vfork();
        // Work that each child does
        if (pid == 0) {
            paint(i);
            exit(0);
        }
        // Question, why do I log which thread executed here?
        // Log some information in a parent.
        printf("Child created: %d\n", pid);
    }

    // Parent
    printf("Masterpiece(vfork.ppm) is being assembled\n");

    // Write out the PPM file
    // You have to do this!
    // TODO: (See task 6)

    savePMMFile();



    return 0;
}