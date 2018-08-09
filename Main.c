#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/**
* Function returns true if word_1 and word_2 are anagrams to each other. Otherwise false.
* Case sensitivity doesn't matter.
*/
bool check_if_anagram(const char* word_1, int length_1, const char* word_2, int length_2)
{
    if((length_1 == 0 && length_2 > 0 )|| (length_1 > 0 && length_2 == 0))
        return false;
    bool *isAnagram = malloc(length_2 * sizeof(bool));
    bool anagram = true;
    for(int i = 0; i < length_1;i++) {
        if(word_1[i] == ' ')
                continue;
        for(int j = 0; j < length_2;j++) {
            if(tolower(word_1[i]) == tolower(word_2[j]))
                isAnagram[j] = true;
            if(word_2[j] == ' ')
                isAnagram[j] = true;
        }
    }
    for(int i = 0; i < length_2; i++)
        if(isAnagram[i] == false)
            return false;
    free(isAnagram);
	return anagram;
}

void test_cases()
{
	bool answer = check_if_anagram("LordVader", strlen("LordVader"), "VaderLord", strlen("VaderLord"));
	assert(answer == true);

	answer = check_if_anagram("silent", strlen("silent"), "listen", strlen("listen"));
	assert(answer == true);

	answer = check_if_anagram("funeral", strlen("funeral"), "real fun", strlen("real fun"));
	assert(answer == true);

	answer = check_if_anagram("Elon Musk", strlen("Elon Musk"), "Muskmelon", strlen("Muskmelon"));
	assert(answer == true);

	answer = check_if_anagram("Tieto", strlen("Tieto"), "Tietonator", strlen("Tietonator"));
	assert(answer == false);

	answer = check_if_anagram("Football", strlen("Football"), "Basketball", strlen("Basketball"));
	assert(answer == false);

	answer = check_if_anagram("F", strlen("F"), "", strlen(""));
	assert(answer == false);
}

int main()
{
	test_cases();
}
