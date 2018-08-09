#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

/**
* Function returns an array of 5 elements.
* Those 5 elements are created randomly in the range 1 - 49.
* Numbers can't repeat.
*/
int* Lotto_drawing()
{
    srand(time(0));
	int *array = malloc(5 * sizeof(int));
	int letter;
	for(int i = 0; i < 5; i++)
	{
        letter = (rand() % 49) + 1;
        for(int j = 0; j < i;)
            if(array[j] == letter)
                letter = (rand() % 49) + 1;
            else
                j++;
        array[i] = letter;
	}
	return array;
}
bool isUnique(int *array)
{
    for(int i = 0; i < 5; i++)
        for(int j = i; j < 5; j++)
            if(array[i] == array[j] && i != j)
                return false;
    return true;
}
bool isBetween(int *array)
{
    for(int i = 0; i < 5; i++)
        if(array[i] < 1 || array[i] > 49)
            return false;
    return true;
}
/* Please create test cases for this program. test_cases() function can return void, bool or int. */
void test_cases()
{
    for(int i = 0; i < 100; i++){
        int *numbers = Lotto_drawing();
        assert(isBetween(numbers) == true);
        assert(isUnique(numbers) == true);
        free(numbers);
    }
}


int main()
{
    test_cases();
    return 0;
}
