def iterateString():
        word = "hello"
        for c in word:
            print(c)

        for index, character in enumerate(word):
            print("Index {0} character {1}". format(index, character))

#

#iterateString()

def remove_chars(sentence):
    return sentence[1:len(sentence)-1]

#

assert remove_chars("country") == "ountr", "Failed test case"
assert remove_chars("Tieto") == "iet", "Failed test case"

def return_half(senstence):
    return  senstence[0:len(senstence)//2]

#

assert return_half("Tieto") == "Ti", "Wrong."
assert return_half("Work") == "Wo", "Wrong."
assert return_half("Academy") == "Aca", "Wrong."

def append_string(sentence):
    if len(sentence) >= 5:
        sentence += " World"
    else:
        sentence = "Welcome, " + sentence
    return  sentence

#

assert append_string("Hello") == "Hello World", "Wrong."
assert  append_string("Hi") == "Welcome, Hi", "Wrong."

def Comparer(str1, str2):
    return str1 > str2
#

def filter_list(my_list):
    return [item for item in my_list if type(item) is int]

#
assert filter_list([1, 5, 'a', 30, 'hello', 50, 2.75]) == [1, 5, 30, 50], "Bad filtering!"

def who_likes_it(lista):
    if len(lista) == 0:
        return  "no one likes this"
    elif len(lista) == 1:
        return lista[0] + " likes this"
    elif len(lista) == 2:
        return lista[0] + " and " + lista[1] + " like this"
    elif len(lista) == 3:
        return lista[0] + ", " + lista[1] + " and " + lista[2] + " like this"
    elif len(lista) > 3:
        return lista[0] + ", " + lista[1] + " and " + str(len(lista) - 2) + " others like this"
    return None


assert who_likes_it([]) == "no one likes this", "Wrong like count!"
assert who_likes_it(["Ryszard"]) == "Ryszard likes this", "Wrong like count!"
assert who_likes_it(["Marcin", "Michal"]) == "Marcin and Michal like this", "Wrong like count!"
assert who_likes_it(["Edyta", "Igor", "Kamil"]) == "Edyta, Igor and Kamil like this", "Wrong like count!"
assert who_likes_it(["Michal", "Maciej", "Bartosz", "Przemek"]) == "Michal, Maciej and 2 others like this", "Wrong like count!"

import collections

def count_duplicates(sentence, how_many_times):
    '''
    Function checks how many times a letter is present in a string.
    Return only those letters.
    See test cases for examples
    '''
    string = ""
    for ch in sentence:
        if sentence.count(ch) == how_many_times:
            string += ch
    sentence = ''.join(collections.defaultdict.fromkeys(string).keys())
    return sentence


assert count_duplicates("aabcdddee", 2) == "ae", "Failed to count!" # only 'a' end 'e' were present 2 times.
assert count_duplicates("indivisibility", 6) == "i", "Failed to count!"
assert count_duplicates("Karima", 1) == "Krim", "Failed to count!"




def reorder_substrings(sentence):
    '''
    Your task is to sort a given string. Each word in the String will contain a single number.
    This number is the position the word should have in the result.
    Note: Numbers can be from 1 to 9. So 1 will be the first word (not 0).
    '''
    strings = sentence.split(" ")
    d = collections.defaultdict()
    strr = ""
    for word in strings:
        lista = list(word)
        for ch in lista:
            if(ch.isdigit()):
                d[ch] = word
    for key in sorted(d.keys()):
        strr += d[key]
        strr += " "

    return strr[:-1]


assert reorder_substrings("is2 Thi1s T4est 3a") == "Thi1s is2 3a T4est", "Failed!"

def Dict():
     Dictio = {"Michal": 3, "Tristan": 8, "Edyta" : -1}
     print(Dictio)
     del Dictio["Tristan"]
     if "Najlepszy Przemek" in Dictio:
        Dictio["Najlepszy Przemek"] += 100
     else:
         Dictio["Najlepszy Przemek"] = 100
     Dictio.pop("Edyta", None)
     print(Dictio)

#

#Dict()


# Write a Python program to count the occurrences of each word in a given sentence.
def word_counter(sentence):
    strings = sentence.split(" ")
    Dictio = {}
    for word in strings:
        if not word[-1].isalnum():
            if word[-1] in Dictio:
                Dictio[word[-1]] += 1
            else:
                Dictio[word[-1]] = 1
            if word[:-1] in Dictio:
                Dictio[word[:-1]] += 1
            else:
                Dictio[word[:-1]] = 1
        else:
            if word in Dictio:
                Dictio[word] += 1
            else:
                Dictio[word] = 1
    return Dictio

answer = {"Ala": 2, "ma": 2, ".": 2, "kota": 1, "psa": 1}
assert word_counter("Ala ma kota. Ala ma psa.") == answer

import re

def regexes(word):
    #only_numbers = re.search(r'[\d]', word)
    only_numbers = re.findall(r'[\d]', word)
    if only_numbers:
        print(only_numbers)

#

#regexes("Hello 12 Worlds and 24 planets")


def validatePIN(PIN):
    # ATM machines allow 4 digit PIN codes and PIN must contain only digits.
    # Validate if input is correct
    return bool(len(PIN) == 4 and not len(re.findall(r'[^\d]',PIN)))
#

assert validatePIN("1234") == True, "Wrong validation!"
assert validatePIN("12345") == False, "Wrong validation!"
assert validatePIN("a234") == False, "Wrong validation!"



def validate_input(word):
    # Write a simple regex to validate a username. Allowed characters are:
    # lowercase letters, numbers, underscore
    # Length should be between 5 and 20 characters (both included).
    return  not bool(len(re.findall(r'[^a-z0-9_]', word)) and len(word) >= 5 and len(word) <= 20)
#

assert validate_input("Summer Academmy") == False, "Bad validation!"
assert validate_input("Summer_Academmy") == False, "Bad validation!"
assert validate_input("summer_academmy") == True, "Bad validation!"



import omdb
import operator
import ast
import datetime
API_KEY = "ed573f66"

omdb.set_default('apikey', API_KEY)

print("Write movie titles: ")
titles = input()
rating = ''
title = []
while titles != 'end':
    if re.findall(r',', titles):
        if re.findall(r':', titles):
            title = titles.split(' : ')
            rating = title[1]
            titles = title[0]
        title = titles.split(', ')

        if not rating:
            for movie in title:
                results = omdb.title(movie)
                if not results:
                    print("Wrong movie")
                    continue
                print("Title: " + results['title'])
                print("Rating: " + results['imdb_rating'])
                print("Runtime: " + results['runtime'])
                if results['released'] == "N/A":
                    print("Released: N/A")
                else:
                    print(
                        f"Released:  {datetime.datetime.strptime(results['released'],'%d %b %Y').strftime('%d.%m.%Y')}")
                print("Popularity: " + results['imdb_votes'])
                print("--------------------------------------------------------------------")
        else:
            MovieBase = {}
            MovieDickt = {}
            for movie in title:
                results = omdb.title(movie)
                if not results:
                    print("Wrong movie")
                    continue
                MovieDickt[movie] = results
                if rating == "Rating":
                    if results['imdb_rating'] ==  "N/A":
                        MovieBase[movie] = 0
                    else:
                        MovieBase[movie] = ast.literal_eval(results['imdb_rating'])
                elif rating == "Length":
                    if results['runtime'] == "N/A":
                        MovieBase['runtime'] = 0
                    else:
                        MovieBase[movie] = int(results['runtime'].split()[0])
                elif rating == "Release date":
                    if results['released'] == "N/A":
                        MovieBase[movie] = datetime.datetime.strptime("15 Jul 1410",'%d %b %Y').strftime('%d.%m.%Y')
                    else:
                        MovieBase[movie] = datetime.datetime.strptime(results['released'],'%d %b %Y').strftime('%d.%m.%Y')
                elif rating == "Popularity":
                    if results['imdb_votes'] == "N/A":
                        MovieBase[movie] = 0
                    else:
                        MovieBase[movie] = 0
                        i = 1
                        pop = results['imdb_votes'].split(",")
                        for vote in reversed(pop):
                            MovieBase[movie] += int(vote) * i
                            i *= 1000
                else:
                    rating == "Wrong"
                    continue
            if not rating == "Wrong":
                SortedMovies = sorted(MovieBase.items(), key=operator.itemgetter(1), reverse=True)
                for tit, mov in SortedMovies:
                    results = MovieDickt[tit]
                    if not results:
                        print("Wrong movie")
                        continue
                    print("Title: " + results['title'])
                    print("Rating: " + results['imdb_rating'])
                    print("Runtime: " + results['runtime'])
                    if results['released'] == "N/A":
                        print("Released: N/A")
                    else:
                        print(
                            f"Released:  {datetime.datetime.strptime(results['released'],'%d %b %Y').strftime('%d.%m.%Y')}")
                    print("Popularity: " + results['imdb_votes'])
                    print("--------------------------------------------------------------------")
            else:
                print("Wrong preferences")
                continue
    else:
        results = omdb.title(titles)
        if not results:
            print("Wrong movie try again: ")
            titles = input()
            continue
        print("Title: " + results['title'])
        print("Rating: " + results['imdb_rating'])
        print("Runtime: " +results['runtime'])
        if results['released'] == "N/A":
            print("Released: N/A")
        else:
            print(f"Released:  {datetime.datetime.strptime(results['released'],'%d %b %Y').strftime('%d.%m.%Y')}")
        print("Popularity: " + results['imdb_votes'])
        print("--------------------------------------------------------------------")

    print("Write movie titles: ")
    titles = input()


#
print("End")
