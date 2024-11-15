Movie Data Processor

##Overview
This program enables users to interact with and process CSV files containing movie data. It allows users to select, organize, and manage files
and directories based on specific criteria. The program reads the CSV data, categorizes movies by their release year, and generates year-based text files.
Additionally, it handles file permissions and directory creation.

##Project Outcomes
Describe the API for file and directory operations.
Understand file and directory permission scopes.
Work with directory structures and file processing on Unix.

##Features
Directory Creation:
Create directories with specified permissions (rwxr-x---).
Organize files within newly created directories.
File Processing:

Read and process CSV files containing movie data.
Parse data and categorize movies by release year.
Write titles of movies for each year into separate text files.
File and Directory Permissions:

Set appropriate file permissions (rw-r-----) for year-based text files.
User Interaction:

Present a main menu to select a file to process or exit.
Allow users to choose the largest, smallest, or a user-specified CSV file.
Program Flow
Main Menu
Select file to process
Exit the program
File Selection
If the user selects option 1 to process a file, they will be presented with three options:

Largest File: Automatically selects the largest CSV file with a movies_ prefix.
Smallest File: Automatically selects the smallest CSV file with a movies_ prefix.
User-Specified File: Prompts the user to enter a file name manually.
Once a file is selected, the program will confirm with:

Now processing the chosen file named <filename>

##Processing the File
The program reads the selected file and processes the data to categorize movies by release year.
It creates a new directory in the format: <your_onid>.movies.<random_number>, with permissions rwxr-x---.
For each release year, the program:
Creates a text file named YYYY.txt.
Writes the titles of movies released in that year, one title per line.


##File Permissions
Directory: rwxr-x--- — owner has full access; group has read and execute permissions.
Yearly Movie Files: rw-r----- — owner has read/write access; group has read access.
CSV File Format
The CSV file should contain the following columns:

Title: String containing the movie title (e.g., "Iron Man 2").
Year: Four-digit integer (e.g., 2010).
Languages: Languages in square brackets, separated by semicolons (e.g., [English;Portuguese]).
Rating Value: Numeric value between 1 and 10 (e.g., 8.7 or 5).

##Technologies Used
C
Unix/Linux for file and directory management
MobaXterm for terminal operations (optional)
Visual sstudio code
I/O system calls

Getting Started
Clone the Repository
bash
Copy code
git clone https://github.com/yourusername/MovieDataProcessor.git

##Compile the Program
bash
Copy code
gcc -o movie_data_processor main.c
Run the Program
bash
Copy code
./movie_data_processor
Sample Program Execution
In a directory with:

Existing file: great_movies.csv
Largest file with prefix movies_: movies_1.csv
Smallest file with prefix movies_: movies_2.csv
Execution steps:

plaintext
Copy code
Main Menu
1. Select file to process
2. Exit the program
Enter a choice (1 or 2): 1

Which file you want to process?
1. Pick the largest file
2. Pick the smallest file
3. Specify the name of a file
Enter a choice (1 to 3): 1

Now processing the chosen file named movies_1.csv
