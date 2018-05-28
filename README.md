# avl-tree
C implementation of an integer multi-set using an AVL tree (height balanced) as the underlying data structure with support for a wide variety of operations including viewing the underlying tree at any state.

## Getting Started
Run the code using
```
sh run.sh
```
A menu-driven program with all the operations supported will run.
At any point executing the operation
> 5. Write tree to file

using ```5``` will write the underlying AVL tree into a file which can be viewed by opening a new terminal window and executing
```
sh viewtree.sh
```

### Prerequisites
[GCC](https://gcc.gnu.org/install/)
[Graphviz](https://graphviz.gitlab.io/download/) - for viewing the tree
