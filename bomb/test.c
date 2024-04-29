#include <stdio.h>
#include <stdlib.h>


// Returns the number of numbers read
int read_six_numbers(char *input, int *nums){

}

int string_length(char *input){
    int length = 0;

    /* A simpler and more direct implementation */
    while (*input != 0x0) {
        input++;
        length++;
    }

    return length;
}


/*
 * @return 0     equal
 * @return 1 not equal
*/
int strings_not_equal(char *input, char *key){
    int input_length = string_length(input);
    int key_length = string_length(key);

    int res = 1;

    if (input_length == key_length) {
        while (*input != 0x0) {
            if (*input != *key) {
                break;
            }
            input++;
            key++;
        }

        if (*input == 0x0) {
            res = 0;
        }
    }

    return res;
}

int func4(int arg1, int arg2, int arg3){
    int res = arg3 - arg2;
    int temp = res >> 31;

    res += temp;
    res >>= 1;

    temp = res + arg2;

    if (temp > arg1) {
        arg3 = temp - 1;

        res = func4(arg1, arg2, arg3);

        res *= 2;
    } else {
        res = 0;

        if (temp < arg1) {
            arg2 = temp + 1;

            res = func4(arg1, arg2, arg3);

            res = 2 * res + 1;
        }
    }
    

    return res;
}

void phase_6(char *input){
    int nums[6];
    long *pointers_of_num[12] = {};
    long **selected_pointers[6];

    if (read_six_numbers(input, nums) < 6) {
        explode_bomb();
    }

    if (nums[0] > 6) {
        explode_bomb();
    }

    for (int i = 1; i < 6; i++) {
        if (nums[i] > 6) {
            explode_bomb();
        }
        for (int j = i; j < 6; j++) {
            if (nums[j] == nums[i - 1]) {
                explode_bomb();
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        nums[i] = 7 - nums[i];
    }


    for (int i = 0; i < 6; i++) {
        // if(nums[i] > 1)
        int *p = pointers_of_num[0];

        p = *(p + 8);
        for (int j = 2; j < nums[i]; j++) {
            p = *(p + 8);
        }

        selected_pointers[i] = p;
    }

    for (int i = 0; i < 5; i++) {
        *(selected_pointers[i] + 8) = selected_pointers[i + 1];
    }
    *(selected_pointers[5] + 8) = 0;

    for (int i = 0; i < 6; i++) {
        if (*selected_pointers[i] < **(selected_pointers[i] + 8)) {
            explode_bomb();
        }
    }
}

void phase_5(char *input){
    char *input_strings = input;
    char *key = "maduiersnfotvbylSo you think you can stop the bomb with ctrl-c, do you?";
    char c[32];
    c[24] = 0;

    if (string_length(input) != 6) {
        explode_bomb();
    }

    for (int i = 0; i < 6; i++) {
        char arg3 = input_strings[i];
        arg3 &= 0xf;
        arg3 = key[arg3];

        c[16 + i] = arg3;
    }

    char *arg2 = "flyers";

    if (strings_not_equal(c + 16, arg2)) {
        explode_bomb();
    }
}

void phase_4(char *intput){
    int nums[2];

    if (scanf("%d %d", &nums[0], &nums[1]) != 2 || nums[0] > 14) {
        explode_bomb();
    }

    if (func4(nums[0], 0, 14) != 0) {
        explode_bomb();
    }

    if (nums[1] != 0) {
        explode_bomb();
    }
}

void phase_3(char *input){
    int nums[2];

    if (scanf("%d %d", &nums[0], &nums[1]) != 2) {
        explode_bomb();
    }

    if (nums[0] > 7 || nums[1] != 311) {
        explode_bomb();
    }
}

void phase_2(char *input){
    int nums[6];

    if (read_six_numbers(input, nums) < 6) {
        explode_bomb();
    }

    if (nums[0] != 1) {
        explode_bomb();
    }

    for (int i = 1; i < 6; i++) {
        if (nums[i] != nums[i - 1] * 2) {
            explode_bomb();
        }
    }
}

void phase_1(char *input){
    char *key = "Border relations with Canada have never been better.";

    if (strings_not_equal(input, key)) {
        explode_bomb();
    }
}

int main(){
    char *input = "test";

    int length = string_length(input);
    printf("length: %d\n", length);
    
    return 0;
}