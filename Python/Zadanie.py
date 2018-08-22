import omdb
import omdb
import os
import re
import urllib
import requests
import datetime

API_KEY = "ed573f66"

omdb.set_default('apikey', API_KEY)

forbiddenCharacters = [':', '?', '<', '>', '|', '"', '\\', '/', '*']
print("Write movie titles: ")
title = input()
titles = []
if re.findall(r',', title):
    titles = title.split(", ")
else:
    titles.append(title)
for movie in titles:
    results = omdb.title(movie)
    title = results['title']
    for character in title:
        if character in forbiddenCharacters:
           title = title.replace(character,"")
    if not len(title):
        print("Write name of your folder: ")
        title = input()
    newpath = f"C:/Movies/{title}"
    if not os.path.exists(newpath):
        os.makedirs(newpath)
    fout = open(f"{newpath}/{title}.txt",'w')
    fout.write("Title: " + results['title'] + "\n")
    fout.write("Rating: " + results['imdb_rating']+ "\n")
    fout.write("Runtime: " + results['runtime']+ "\n")
    if results['released'] == "N/A":
        fout.write("Released: N/A"+ "\n")
    else:
        fout.write(f"Released:  {datetime.datetime.strptime(results['released'],'%d %b %Y').strftime('%d.%m.%Y')}"+ "\n")
    fout.write("Popularity: " + results['imdb_votes']+ "\n")
    poster = results['poster']
    if not poster == "N/A":
        urllib.request.urlretrieve(poster, f"{newpath}/{title}.jpg")