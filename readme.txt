Christian Childress
IMDb Movie Database
CS201 - Dr. Monica Anderson
//-------------------------------------------------------
What is the Program Doing?
-The program is taking the title.basics.tsv file and reading eveything into an array
-of structs to hold the data so I can hash individual words of the title.
- In my opinion, a program that can search for all occurences of a word in a title is much more useful  than a program that can only tell you movies that start with that word.
-After The data is put into an array of structs, each word in every title is hashed into
-a specific slot relative to the letters in the word and the position in the word so when looking up a
-title there is a much smaller range of titles containing that word, giving you a relevant search time
-of O(1) and in the worst case where words are very most common O(n). All irrelevant words are not hashed
-such as the, and, or, it, ect. The hash function seperates pretty evenly with a couple index's having
-move titles in them because the words are more common than others, such as Love.
//-------------------------------------------------------
Where is the Video of me using the Project?
-The link to the video is here --https://www.youtube.com/watch?v=A8u9ZhXFuIg--
//-------------------------------------------------------
How do I use the program?
-There are a couple main steps to using the program.
-1. Open your terminal and make it half the size of your screen like shown in the Video.
-2. Open the folder the project is saved in, in a text editor and make that the other half of the screen.
---You will need to title.index.tsv file to look at what options to select from as far as movies go and see what is inside your movie file
-3. Run make and it should compile the program for you to make everything easy for you, the user
-4. Here you will be prompted to select from a couple choices. Add movie, update movie, remove movie.
ADD MOVIE - 1. It will prompt you to enter a single word to search the movie with. If the movie is a noun, capitalize it or
               you might not get any search results and will be redirected to the main menu.
            2. It will tell you there are results if there are any, if there are no results it will redirect you to the main menu to try again.
            3. After finding results if there are any, it will ask for the number of the movie you would like to add to your file.
            4. The number of this movie will be found in the title.index.tsv file. Enter the number to the left of the movie you would like to add into the terminal to add it to your file.
            5. It will then tell you if you have that movie or not. If you do it will prompt you to exit the porgram or quit to the main menu to try again.
            6. If you do not have that movie, it will prompt you to enter the date you aquired the movie in 00/00/0000 format.
            7. It will then prompt you to enter the object you have that contains the moive DVD, CD, Download etc.
            8. It will then prompt you of the movies addition into your file and prompt you to exit the program from there or quit and go back to the main menu to preform another operation.
REMOVE MOVIE - 1. It will prompt you to enter the exact title of the movie to remove it from your file.
               2. It will prompt you for the name of your file.
               3. If the movie is not in your file it will prompt you that it is not and will tell you to either quit and head back to the main menu to preform another operation or exit the Program.
               4. If the movie is found, it will remove it and prompt you of its removal from the file.
               5. It will then redirect you to quit to main menu to preform another operation or exit the program entirely.
UPDATE MOVIE - 1. It will prompt you to enter the exact title of the movie to update it from your file.
               2. It will prompt you for the name of your file.
               3. If the movie is not in your file it will prompt you that it is not and will tell you to either quit and head back to the main menu to preform another operation or exit the Program.
               4. If the movie is found, prompt you to select from, title, minutes, time, object.
               5. Enter any of these options.
               6. It will prompt you what you would like to change that category to which you will enter into the terminal.
               7. It will then prompt you that it has been successfully updated.
               8. It will then prompt you to either quit to main menu or exit the program.
//-------------------------------------------------------
-This program is very easy to use and is rather efficient for adding, removing, and updating titles from a user file
-Allowing you to know what is in your file and how to add and remove and update things rather quickly.
-Thank you for using my program!!! I hope you thought it was as easy to use as I did!!!
