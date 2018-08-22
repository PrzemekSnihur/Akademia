import omdb
import datetime
from os import listdir
from os.path import isfile, join

API_KEY = "ed573f66"

omdb.set_default('apikey', API_KEY)

path = "C:\Movies"
titles = []
print("Do you want type movie or load it from folder?")
preference = input()
if preference == "type":
    print("type titles: ")
    movies = input()
    titles = movies.split(", ")
else:
    titles = [f for f in listdir("C:\Movies") if isfile(join(path,f))]
    WordsToDelete = ['5.1', '7.1', '5 1', '7 1', 'DUAL AUDIO', 'DUAL-AUDIO', 'MULTI-CHANNEL', 'Ita-Eng',
                    '2160p', '4K', '1080p', '720p', '480p', '360p', 'HD', 'FULL HD', 'FULLHD',
                    'x264', 'CH', 'X264', 'HEVC',
                    'WEB-DL', 'BrRip', 'Rip', 'DVDRip', 'XviD', 'BLURAY',
                    'EXTENDED', 'REMASTERED', 'DIRECTORS', 'UNRATED', 'AlTERNATE', 'DVD']
    for index, movie in enumerate(titles):
        for word in WordsToDelete:
            movie = movie.replace(word,"")
        titles[index] = movie
    for index, movie in enumerate(titles):
        titles[index] = movie.split(" .")[0].strip()


for title in titles:
    results = omdb.title(title)
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