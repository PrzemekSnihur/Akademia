#include <string.h>
#include <assert.h>
#include <ctype.h>
/**
* Function duplicates letters based on their index. Each index means how many times the letter needs to be duplicated.
* See test cases for examples.
*/

char* accumulate(const char *word, const int length)
{
    int totaLength = 2*length-1;
    for(int i = 0; i <length; i++)
        totaLength += i;
    char * mumble = malloc(totaLength * sizeof(char));
    int index = 0;
    char letter;
    for(int i = 0; i < length; i++)
    {
        letter = toupper(word[i]);
        mumble[index] = letter;
        index++;
        letter = tolower(word[i]);
        for(int j = 0; j < i; j++)
        {
            mumble[index] = letter;
            index++;
        }
        if(letter != tolower(word[length-1])){
            mumble[index] = '-';
            index++;
        }

    }
    return mumble;
}

void test_cases()
{
	char* result = accumulate("abcd", strlen("abcd"));
	assert(strcmp(result, "A-Bb-Ccc-Dddd") == 0);
	free(result);

	result = accumulate("cwAt", strlen("cwAt"));
	assert(strcmp(result, "C-Ww-Aaa-Tttt") == 0);
    free(result);
}

int main(int argc, char *argv[])
{
    test_cases();
	return 0;
}
