Basic BST builder with no AVL that determines kth smallest element.
Elliot Wyrick - 10/7/25

To run:

- initialize CMake in project directory         "cmake .."
- run the makefile it creates                   "make"
- run the executable made by the makefile       "./BST-NO-AVL"

What It Does

Builds balanced BST from array
Finds k-th smallest element
Prints visual tree

example:
```
int input[] = {6, 17, 20, 41, 45, 52, 57, 65, 71, 76, 79, 87, 92, 95, 99};
int k = 5;

otuput:

kth: 45
               65
              / \
             /   \
            /     \
           /       \
          /         \
         /           \
        /             \
       41              87
      / \             / \
     /   \           /   \
    /     \         /     \
   17      52      76      95
  / \     / \     / \     / \
  6  20  45  57  71  79  92  99

```

known problems:

tree display is not dynamic. Tree building is done correctly, but is not reflected accuratly in the visual.

[DEMO](https://youtu.be/FgQWdh2g1hM):

[![Watch the demo](https://img.youtube.com/vi/FgQWdh2g1hM/maxresdefault.jpg)](https://youtu.be/FgQWdh2g1hM)
