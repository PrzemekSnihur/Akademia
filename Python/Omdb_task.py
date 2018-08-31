import omdb
import datetime
import os
from os import listdir
from os.path import isfile, join
import operator
import ast
import re
import urllib
import requests


API_KEY = "ed573f66"

omdb.set_default('apikey', API_KEY)

path = "C:\Movies"
TitleFromFIle = False
rating = ''
titles = []#
MovieDickt = {}
SortedMovies = []
forbiddenCharacters = [':', '?', '<', '>', '|', '"', '\\', '/', '*']
WordsToDelete = ['5.1', '7.1', '5 1', '7 1', 'DUAL AUDIO', 'DUAL-AUDIO', 'MULTI-CHANNEL', 'Ita-Eng',
                    '2160p', '4K', '1080p', '720p', '480p', '360p', 'HD', 'FULL HD', 'FULLHD',
                    'x264', 'CH', 'X264', 'HEVC',
                    'WEB-DL', 'BrRip', 'Rip', 'DVDRip', 'XviD', 'BLURAY',
                    'EXTENDED', 'REMASTERED', 'DIRECTORS', 'UNRATED', 'AlTERNATE', 'DVD']

def SortMovies():
    MovieBase = {}
    for movie, results in MovieDickt.items():
        if rating == "Rating":
            if results['imdb_rating'] == "N/A":
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
                MovieBase[movie] = datetime.datetime.strptime("15 Jul 1410", '%d %b %Y') #Add date when movies didnt exist
            else:
                MovieBase[movie] = datetime.datetime.strptime(results['released'], '%d %b %Y')
        elif rating == "Popularity":
            if results['imdb_votes'] == "N/A":
                MovieBase[movie] = 0
            else:
                MovieBase[movie] = int(results['imdb_votes'].replace(",", ""))
        else:
            rating == "Wrong"
            continue
    if not rating == "Wrong":
        Sorted = sorted(MovieBase.items(), key=operator.itemgetter(1), reverse=True)
        for index, val in enumerate(Sorted):
            Sorted[index] = val[0]
        return Sorted
    print("Wrong sorting command")
    return []

def writeMoviesToFile(title):
    for tit in SortedMovies:
        for character in title:
            if character in forbiddenCharacters:
                title = title.replace(character, "")
        if not len(title):
            print("Write name of your folder: ")
            title = input()
        newpath = f"C:/Movies/{title}"
        if not os.path.exists(newpath):
            os.makedirs(newpath)
        fout = open(f"{newpath}/{title}.txt", 'w')
        fout.write("Title: " + results['title'] + "\n")
        fout.write("Rating: " + results['imdb_rating'] + "\n")
        fout.write("Runtime: " + results['runtime'] + "\n")
        if results['released'] == "N/A":
            fout.write("Released: N/A" + "\n")
        else:
            fout.write(
                f"Released:  {datetime.datetime.strptime(results['released'],'%d %b %Y').strftime('%d.%m.%Y')}" + "\n")
        fout.write("Popularity: " + results['imdb_votes'] + "\n")
        poster = results['poster']
        if not poster == "N/A":
            urllib.request.urlretrieve(poster, f"{newpath}/{title}.jpg")

def printMovie(movie):
    print("Title: " + movie['title'])
    print("Rating: " + movie['imdb_rating'])
    print("Runtime: " + movie['runtime'])
    if movie['released'] == "N/A":
        print("Released: N/A")
    else:
        print(
            f"Released:  {datetime.datetime.strptime(movie['released'],'%d %b %Y').strftime('%d.%m.%Y')}")
    print("Popularity: " + movie['imdb_votes'])
    print("--------------------------------------------------------------------")

print("Do you want type movie?('yes' to type)")
preference = input()

while preference != 'end':
    if preference == "yes":
        print("type titles: ")
        title = input()
    else:
        TitleFromFIle = True
        titles = [f for f in listdir("C:\Movies") if isfile(join(path, f))]
        for index, movie in enumerate(titles):
            for word in WordsToDelete:
                movie = movie.replace(word, "")
            titles[index] = movie
        for index, movie in enumerate(titles):
            titles[index] = movie.split(" .")[0].strip()

    if not TitleFromFIle and re.findall(r',', title):
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
    elif TitleFromFIle:
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
        SortedMovies = SortMovies()
    for tit in SortedMovies:
        results = MovieDickt[tit]
        if not results:
            print("Wrong movie")
            continue
        title = results['title']
        writeMoviesToFile(title)
        printMovie(results)
    MovieDickt.clear()
    SortedMovies.clear()
    TitleFromFIle = False
    print("Do you want type movie?('yes' to type)")
    preference = input()

print("Have a nice day!")

    #Deadpool, Emoji, Matrix