import omdb
import operator
import ast
import datetime
import re

API_KEY = "ed573f66"

omdb.set_default('apikey', API_KEY)

print("Write movie titles: ")
title = input()
rating = ''
titles = []#
MovieDickt = {}
SortedMovies = []

while title != 'end':
    if re.findall(r',', title):
        if re.findall(r':', title):
            titles = title.split(' : ')#
            rating = titles[1]#
            title = titles[0]#
        titles = title.split(', ')#
        for movie in titles:#
            SortedMovies.append(movie)
            results = omdb.title(movie)#
            if not results:
                print("Wrong movie")
                continue
            MovieDickt[movie] = results

    else:
        results = omdb.title(title)#
        MovieDickt[title] = results
        SortedMovies.append(title)
    if not rating == '':
        MovieBase = {}
        for movie, results in MovieDickt.items():
            if rating == "Rating":
                if results['imdb_rating'] == "N/A":
                    MovieBase[movie] = "None"
                else:
                    MovieBase[movie] = ast.literal_eval(results['imdb_rating'])
            elif rating == "Length":
                if results['runtime'] == "N/A":
                    MovieBase['runtime'] = 0
                else:
                    MovieBase[movie] = int(results['runtime'].split()[0])
            elif rating == "Release date":
                if results['released'] == "N/A":
                    MovieBase[movie] = datetime.datetime.strptime("15 Jul 1410", '%d %b %Y').strftime('%d.%m.%Y')
                else:
                    MovieBase[movie] = datetime.datetime.strptime(results['released'], '%d %b %Y').strftime('%d.%m.%Y')
            elif rating == "Popularity":
                if results['imdb_votes'] == "N/A":
                    MovieBase[movie] = 0
                else:
                    MovieBase[movie] = int(results['imdb_votes'].replace(",",""))
            else:
                rating == "Wrong"
                continue
        if not rating == "Wrong":
            SortedMovies = sorted(MovieBase.items(), key=operator.itemgetter(1), reverse=True)
            for index, val in enumerate(SortedMovies):
                SortedMovies[index] = val[0]
    for tit in SortedMovies:
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

    print("Write movie titles: ")
    title = input()


    #Deadpool, Emoji, Matrix