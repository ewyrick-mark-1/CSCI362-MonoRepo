Basic AVL Tree builder with support for insertion and deletion.
Elliot Wyrick - 10/18/25

To run:

- initialize CMake in project directory         "cmake .."
- run the makefile it creates                   "make"
- run the executable made by the makefile       "./AVL-trees"

What It Does

- Builds balanced AVL tree from array
- Prints tree including height values. 
- uses a CLI for interacting with the tree
- supports insertion and deletion

Known Issues

- subpar tree visual. Current implementation is generic and ...
- not useful when determining the shape of specific branches

example use:

```
Tree:
   Height : 5, Keys : 12  
   Height : 4, Keys : 6  13  
   Height : 3, Keys : 4  10  14  
   Height : 2, Keys : 2  8  15  
   Height : 1, Keys : 1  3  5  7  9  11  16  

   commands:
   <add/delete> <key>
   print
   exit
>> add 6
   Inserted 6 (if it was not there before)
>> add 19
   Inserted 19 (if it was not there before)
>> print
   Tree:
   Height : 5, Keys : 12  
   Height : 4, Keys : 6  16  
   Height : 3, Keys : 4  10  13  
   Height : 2, Keys : 2  8  14  
   Height : 1, Keys : 1  3  5  7  9  11  15  19  
>> delete 12
   Deleted 12 (if it existed)
>> print
   Tree:
   Height : 5, Keys : 13  
   Height : 4, Keys : 6  
   Height : 3, Keys : 4  10  16  
   Height : 2, Keys : 2  8  14  
   Height : 1, Keys : 1  3  5  7  9  11  15  19  
>> delete 9
   Deleted 9 (if it existed)
>> print
   Tree:
   Height : 5, Keys : 13  
   Height : 4, Keys : 6  
   Height : 3, Keys : 4  10  16  
   Height : 2, Keys : 2  8  14  
   Height : 1, Keys : 1  3  5  7  11  15  19  
>> exit
   Exiting...
```

[DEMO](https://youtu.be/EK3UwtQUEEQ):

[![Watch the demo](https://img.youtube.com/vi/EK3UwtQUEEQ/maxresdefault.jpg)](https://youtu.be/EK3UwtQUEEQ)
