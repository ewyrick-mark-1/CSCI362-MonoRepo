                       A                                //23 to the left
                      / \
                     /   \
                    /     \
                   /       \
                  /         \
                 /           \
                /             \
               /               \
              /                 \
             /                   \
            /                     \
           A                       B                    //23 in between (2*height + 1)       
          / \                     / \
         /   \                   /   \
        /     \                 /     \
       /       \               /       \
      /         \             /         \
     A           B           C           D              //11 in between (2*height + 1)
    / \         / \         / \         / \
   /   \       /   \       /   \       /   \
  A     B     C     D     E     F     G     H
 / \   / \   / \   / \   / \   / \   / \   / \ 
A   B C   D E   F G   H I   J K   L M   N O   P

AABACBDAECFBGDHAIEJCKFLBMGNDOHP

height functions:
f(31) = 5
f(15) = 4
f(7) = 3
f(3) = 2
f(1) = 1

f(n) = floor(log2(n)) + 1

                       16
                      / \
                     /   \
                    /     \
                   /       \
                  /         \
                 /           \
                /             \
               /               \
              /                 \
             /                   \
            /                     \
           8                       B                    //23 in between (2*height + 1)       
          / \                     / \
         /   \                   /   \
        /     \                 /     \
       /       \               /       \
      /         \             /         \
     4           12          C           D              //11 in between (2*height + 1)
    / \         / \         / \         / \
   /   \       /   \       /   \       /   \
  2     6     10    14    E     F     G     H
 / \   / \   / \   / \   / \   / \   / \   / \ 
1   3 5   7 9  11 13 15 I   J K   L M   N O   P