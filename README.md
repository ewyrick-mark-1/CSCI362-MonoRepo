# Hashing Demo
Elliot Wyrick - 11/7/25

Basic Hash table builder with support for general dynamic operations.


### To run:

- initialize CMake in build directory           "cmake .."
- run the makefile it creates                   "make"
- run the executable made by the makefile       "./hashing-demo"

### What It Does

- Generates [1000] random ints that range between [10] to [99]
- Creates a linked list hash map of ints using the first value as the hash key.
- clears duplicate values
- supports various dynamic operations via commands including:
    - insertion
    - deletion
    - searching
    - printing
    - clearing duplicate values

## [Demo video:](https://youtu.be/sAmEMq4VhlE)

[![Watch the demo](https://img.youtube.com/vi/sAmEMq4VhlE/maxresdefault.jpg)](https://youtu.be/sAmEMq4VhlE)

## Example use:

### Running it
```
./hashing-demo
hash key: 1
16 11 10 15 14 17 19 13 12 18 
hash key: 2
28 23 20 25 22 26 27 21 29 24 
hash key: 3
31 33 32 34 38 37 30 35 36 39 
hash key: 4
40 47 49 44 46 42 48 41 43 45 
hash key: 5
52 58 55 51 54 59 53 56 50 57 
hash key: 6
61 68 66 69 63 65 67 62 60 64 
hash key: 7
79 71 74 78 77 73 76 70 75 72 
hash key: 8
82 80 86 89 88 84 81 85 87 83 
hash key: 9
96 95 90 97 93 91 98 92 94 99 
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
```
### Insert / Print
```
i
enter number to insert:
99
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
p
enter hash key to print. enter to print all:

hash key: 1
16 11 10 15 14 17 19 13 12 18 
hash key: 2
28 23 20 25 22 26 27 21 29 24 
hash key: 3
31 33 32 34 38 37 30 35 36 39 
hash key: 4
40 47 49 44 46 42 48 41 43 45 
hash key: 5
52 58 55 51 54 59 53 56 50 57 
hash key: 6
61 68 66 69 63 65 67 62 60 64 
hash key: 7
79 71 74 78 77 73 76 70 75 72 
hash key: 8
82 80 86 89 88 84 81 85 87 83 
hash key: 9
96 95 90 97 93 91 98 92 94 99 99 
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
i 
enter number to insert:
71
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
p
enter hash key to print. enter to print all:
7
hash key: 7
79 71 74 78 77 73 76 70 75 72 71 
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
```
### Clear
```
c
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
p
enter hash key to print. enter to print all:

hash key: 1
16 11 10 15 14 17 19 13 12 18 
hash key: 2
28 23 20 25 22 26 27 21 29 24 
hash key: 3
31 33 32 34 38 37 30 35 36 39 
hash key: 4
40 47 49 44 46 42 48 41 43 45 
hash key: 5
52 58 55 51 54 59 53 56 50 57 
hash key: 6
61 68 66 69 63 65 67 62 60 64 
hash key: 7
79 71 74 78 77 73 76 70 75 72 
hash key: 8
82 80 86 89 88 84 81 85 87 83 
hash key: 9
96 95 90 97 93 91 98 92 94 99 
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
```
### Delete
```
d
enter number to delete:
99
deleted 99
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
p
enter hash key to print. enter to print all:

hash key: 1
16 11 10 15 14 17 19 13 12 18 
hash key: 2
28 23 20 25 22 26 27 21 29 24 
hash key: 3
31 33 32 34 38 37 30 35 36 39 
hash key: 4
40 47 49 44 46 42 48 41 43 45 
hash key: 5
52 58 55 51 54 59 53 56 50 57 
hash key: 6
61 68 66 69 63 65 67 62 60 64 
hash key: 7
79 71 74 78 77 73 76 70 75 72 
hash key: 8
82 80 86 89 88 84 81 85 87 83 
hash key: 9
96 95 90 97 93 91 98 92 94 
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
d
enter number to delete:
99
could not find: 99
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
p
enter hash key to print. enter to print all:

hash key: 1
16 11 10 15 14 17 19 13 12 18 
hash key: 2
28 23 20 25 22 26 27 21 29 24 
hash key: 3
31 33 32 34 38 37 30 35 36 39 
hash key: 4
40 47 49 44 46 42 48 41 43 45 
hash key: 5
52 58 55 51 54 59 53 56 50 57 
hash key: 6
61 68 66 69 63 65 67 62 60 64 
hash key: 7
79 71 74 78 77 73 76 70 75 72 
hash key: 8
82 80 86 89 88 84 81 85 87 83 
hash key: 9
96 95 90 97 93 91 98 92 94 
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
```
### Search
```
s
enter number to search:
94
found it!
hash key: 9
96 95 90 97 93 91 98 92 94 
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
s
enter number to search:
99
you stupid
enter a command:
[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]
e
exiting...
```
