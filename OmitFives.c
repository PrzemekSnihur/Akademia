#include <assert.h>
#include <stdbool.h>
#include<stdio.h>

/**
* Function takes a 'start' and 'end' number of a range, and should return the count of all numbers except numbers with 5 in it.
* For example: start = 4, end = 8. It should return 4, because: 4, 6, 7, 8
*/
int numbers_without_five(int start, int end)
{
    int total = 0;
    int currVal;
    bool isFive;
    while(start <= end)
    {
        isFive = false;
        currVal = start;
        while(currVal > 0)
        {
            if(currVal % 10 == 5)
                isFive = true;
            currVal /= 10;
        }
        if(isFive){
            start++;
        }
        else{
            total++;
            start++;
        }
    }
	return total;
}

void test_cases()
{
	int answer = numbers_without_five(4, 8);
	assert(answer == 4);

	answer = numbers_without_five(1, 51);
	assert(answer == 44);

	answer = numbers_without_five(4, 17);
	assert(answer == 12);
}

int main(int argc, char *argv[])
{
	test_cases();

	return 0;
}
