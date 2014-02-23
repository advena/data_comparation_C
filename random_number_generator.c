#include <stdlib.h>
#include <stdio.h>
#define SIZE 50000000
#include "random_number_generator.h"

FILE *file;

void randomGenerator() {
    char path[30];
    char even_path[30];
    int i;
    static int nums[SIZE], even_nums[SIZE];
    arrayGen(SIZE, nums);
    evenArrayGen(SIZE, even_nums);
    shuffle(nums);
    shuffle(even_nums);
    printf("numbers has been generated \n");
//    for(i=0; i< SIZE; i++) {
//        printf("%d ", nums[i]);
//    }
//    path[30] = "numbers.data";
//    save_to_file(nums, "numbers1.txt");
    even_path[30] = "even_numbers";
    saveToFile(even_nums, "numbers4.txt");
    return;
}


/** Generates array of ordered numbers from 1 to the one that was provided
 *
 * @param num number of unique digits
 * @param array of size equal to the number
 *
 */


void arrayGen(int num, int nums[]) {
    int i;
    for(i=1; i<=num; i++) {
        nums[i] = i;
    }
    return;
}


/** Generates array of ordered even numbers from 2
 *
 * @param num number of uniqe even digits
 * @param array of size equal to the number
 *
 */

void evenArrayGen(int num, int even_nums[]) {

    int i, current;
    i = current = 0;
    for(; i<num; i++) {
        even_nums[i] = current += 2;
    }
    return;
}

/** Shuffle the array in random order. Radomly gets the index between 0 and
 *  current last index. Swaps number at random index with last one and
 *  decreses the current_last index by 1.
 *
 * @param array of numbers to be shuffled
 *
 */

void shuffle(int nums[]) {

    int i, len, current_last, index, temp;
    ///set the current_last to length of the array to track index for
    ///swaping nums
    current_last = len = SIZE;
    for (i=0; i<len; i++) {
        srand(time(NULL));
        index = rand()%(current_last);
        temp = nums[index];
        nums[index] = nums[current_last];
        nums[current_last] = temp;
        current_last--;
    }
    return;

}


/** Saves the generated number into the file with given path
 *
 * @param array of numbers that are going to be saved
 *
 */

void saveToFile(int nums[], char path[]) {

    int i;
    file = fopen(path, "w");
    for(i=0; i<SIZE; i++) {
        fprintf(file, "%d\n", nums[i]);
    }
    fclose(file);
    return;
}

/** Randomly generates numbers from one to given boundary
 *
 * @param boundary value
 * @return random number from 0 to boundary range
 *
 */
 int randomNum(int boundary) {

    return rand()%(boundary);
 }
