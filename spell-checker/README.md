# Spell Checker
Elliot Wyrick - 11/11/25

Spell checker and word suggestion program using custom hash table implementation with keyboard-distance-based similarity detection.


### To run:

- initialize CMake in build directory 
```
cmake ..
```
- run the makefile it creates
```
make
```
- run the executable with dictionary file
```
./spell-checker ../resources/Dictionary.txt
or
./spell-checker ../resources/Dictionary_large.txt
```
### What It Does

- Loads dictionary into custom hash table with 676 buckets (26x26 based on first two letters)
- Accepts user word input and checks against dictionary
- Supports three cases:
    - **Case 1:** Word exists - returns "True" and suggests words with same first two letters
    - **Case 2:** Word misspelled - suggests closest match using keyboard distance algorithm, prompts user confirmation
    - **Case 3:** Word not found - returns "False"
- Interactive loop allows multiple word lookups without restarting


## [Demo video:](https://youtu.be/zyrsu9PjLn0)

[![Watch the demo](https://img.youtube.com/vi/zyrsu9PjLn0/maxresdefault.jpg)](https://youtu.be/zyrsu9PjLn0)

### Hash Table Implementation

- Custom hash function: `hash(word) = first_letter * 26 + second_letter`
- 676 buckets distribute words evenly by first two letters
- Average lookup time significantly faster than linear search through entire dictionary
- Limits suggestions to top 5 words with matching first two letters

### Closest Word Calculation

Uses keyboard-distance algorithm to find best match for misspellings:
- Vectorizes input word to character indices (A=0, B=1, ... Z=25)
- Calculates Euclidean distance based on physical keyboard layout
- Distance between 'e' and 'r' is small (adjacent keys)
- Distance between 'a' and 'p' is larger (far apart)
- Penalizes extra/missing characters with modifier
- Only searches words with matching first letter for efficiency
- Returns single closest match when suggesting corrections

### Edge Cases

- Single-letter words: simple hash lookup, returns "True" or "False"
- Words with non-alphabetic characters: filtered during vectorization
- Empty input: returns "False"
- Exit commands: type "quit" or "exit" to terminate program

## Example use [Dictionary.txt]:

### Case 1: Word Found
```
./spell-checker ../resources/Dictionary.txt

Enter a word (or 'quit' to exit): sentence
True
Words starting with the same first two letters (top 5):
  sentence
  set
  see

```

### Case 2: Misspelling Detected
```
Enter a word (or 'quit' to exit): snetence
Do you mean sentence? (yes/no): yes
True
Words starting with the same first two letters (top 5):
  sentence
  set
  see

Enter a word (or 'quit' to exit): setnence
Do you mean sentence? (yes/no): yes
True
Words starting with the same first two letters (top 5):
  sentence
  set
  see

Enter a word (or 'quit' to exit): sentens
Do you mean sentence? (yes/no): yes
True
Words starting with the same first two letters (top 5):
  sentence
  set
  see

Enter a word (or 'quit' to exit): fwrejio[fio[j[iojr[
Do you mean first? (yes/no): yes
True
Words starting with the same first two letters (top 5):
  first
  find

```

### Case 2: No Match Found
```

Enter a word (or 'quit' to exit): zzzzzzzz
False

Enter a word (or 'quit' to exit): exit
```

## Example use [Dictionary_large.txt]:

### Case 1: Word Found
```
./spell-checker ../resources/Dictionary_large.txt 

Enter a word (or 'quit' to exit): snetence
Do you mean sistence? (yes/no): yes
True
Words starting with the same first two letters (top 5):
  sistence
  sisten
  sistency
  sistent
  sithence
```

### Case 2: Misspelling Detected
```
Enter a word (or 'quit' to exit): fvrduipjonfvsfviojnp[fviojn
Do you mean far-shooting? (yes/no): yes
True
Words starting with the same first two letters (top 5):
  far-shooting
  fat-shunning
  far-about
  Farah
  fardh

Enter a word (or 'quit' to exit): exit
```

## Data Sources

- **Dictionary_large.txt**: Word list sourced from [dwyl/english-words](https://github.com/dwyl/english-words) - A comprehensive collection of English words for dictionary projects

