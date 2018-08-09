#include <assert.h>
#include <stdlib.h>
/**
* Given a number, return the maximum number that could be formed with digits of the number given.
* For example: number = 7389, return 9873
*/
int Comparer( const void * first, const void * second)
{
    int First = *(int *)first;
    int Second = *(int *)second;
    if(First < Second) return 1;
    else if( Second > First) return -1;
    else return 0;
}
int form_the_largest_number(int number)
{
    int length = 1;
    int digits = 10;
    while(number/digits != 0)
    {
        length++;
        digits *= 10;
    }
    int numbers[length];
    for(int i = 0; i < length; i++)
    {
        numbers[i] = number%10;
        number /= 10;
    }
    qsort(numbers,length,sizeof(int),Comparer);
    int biggest = 0;
    for(int i = 0; i < length; i++)
    {
        digits /= 10;
        biggest += numbers[i] * digits;
    }
	return biggest;
}

void test_cases()
{
	int result = form_the_largest_number(213);
	assert(result == 321);

	result = form_the_largest_number(7389);
	assert(result == 9873);

	result = form_the_largest_number(63729);
	assert(result == 97632);

	result = form_the_largest_number(566797);
	assert(result == 977665);
}

int main()
{
	test_cases();
	test_cases();
}
