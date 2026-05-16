# B-trees

Basic AVL Tree builder with support for insertion and deletion.
Elliot Wyrick - 10/27/25

To run:

- initialize CMake in project directory         "cmake .."
- run the makefile it creates                   "make"
- run the executable made by the makefile       "./B-trees"

What It Does

- Builds balanced B tree given a max value N, of randomly generated ints between the values 0 and 4*N.
- Prints tree including level values. 
- uses a basic terminal interface for data 
- supports searching and general insertion

Known Issues

- subpar tree visual. Current implementation cannot handle large N cleanly.

example use:

```
./B-trees
25
generated keys: 25, 16, 47, 0, 69, 10, 66, 68, 53, 24, 43, 63, 36, 7, 33, 74, 36, 24, 1, 43, 9, 23, 5, 26, 29
tree built

B-Tree:
Level 0: [36]  
Level 1: [5,10,25]  [47,66]  
Level 2: [0,1]  [7,9]  [16,23,24,24]  [26,29,33,36]  [43,43]  [53,63]  [68,69,74]  

range Search [25, 50]
keys found in range: 25, 26, 29, 33, 36, 36, 43, 43, 47
```

[Demo video:](https://youtu.be/VAhF01_03Oo)

[![Watch the demo](https://img.youtube.com/vi/VAhF01_03Oo/maxresdefault.jpg)](https://youtu.be/VAhF01_03Oo)
