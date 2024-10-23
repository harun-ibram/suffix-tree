## This project implements a suffix compression tree for strings.

## The files Queue.h and Queue.c represent the implementation of the queue data structure.

    The queue is the struct queue, with pointers to the first and last element of the queue.

    The elements of the queue are struct CompTree.

    Q initQ() is the function that initializes an empty queue by allocating memory for the struct queue. 
    It returns a pointer to the allocated structure.

    QNptr CreateQNode(Tree *) is the function through which a queue element of atomic tree type is initialized.

    Tree front(Q) is the function that retrieves the first element from the queue. It receives the queue as 
    a parameter and returns a pointer to the first element.

    Q enq(Q, Tree) is the function that adds an element to the queue. It receives pointers to the queue and 
    the node to be added as parameters. The addition is made at the end of the queue. The links between the
    received element and the last element are updated, and then the pointer to the end of the queue in the
    structure is modified. It returns a pointer to the queue structure.

    Q deq(Q) is the function that removes an element from the queue. It receives a pointer to the queue as
    a parameter and removes the first element. The removal is done by retaining a pointer to the element
    that needs to be deleted, moving the pointer in the structure to the next element in the queue. If we
    are not trying to remove from a queue with only one element, the link to the new first element is
    updated so that its prev points to NULL. The memory for the removed element is freed, and a pointer
    to the queue is returned.

    Q destroyQ(Q) is the queue destructor. It frees the memory for all elements in the queue, then frees
    he memory for the queue structure itself. It returns a pointer to NULL.

    The copyQueue function copies the data from the given queue into a new one.

    The printQueue function prints the data from the given queue.

    The functions createCompQueueNode, compFront, enqComp, copyCompQueue, and printCompQueue are the
    versions for compressed trees of the existing functions for atomic trees.

## The files Tree.c and Tree.h represent the implementation of the tree data structure.

    isEmpty and isCompEmpty check if the tree is empty or has no children.
    
    createTree allocates memory for an empty atomic tree.
    
    whichChild determines which index from 0 to 26 corresponds to a character 'a'-'z' and '$'.
    
    whichChar determines which character 'a'-'z' or '$' corresponds to an index from 0 to 26.
    
    insert checks if the tree has allocated memory and allocates it if necessary. The function inserts
    each suffix, iterates through the characters in the suffix and through the tree, allocating the
    corresponding children if they don't exist and inscribing the corresponding character in the node
    for later display.
    
    weirdBFS traverses and constructs each level of the tree and prints the elements from it in the
    next iteration. The next level is built based on the level retained from the previous iteration,
    which is about to be printed.
    
    destroyTree deallocates the memory for the atomic tree.
    
    countLeaves counts the leaves in the tree based on the number of suffix terminators.
    
    KLengthSuffix recursively searches for suffixes of length K in the tree. The third parameter is
    to store the length already found.
    
    mostDescendants recursively searches for the maximum number of descendants of a node, comparing
    the number of children of the node with the number of children of each descendant.
    
    containsSuffix iterates through the suffix and the tree until they stop matching.
    
    countChildren counts how many children the node received as a parameter has.
    
    compressTree retains the prefix formed up to the first bifurcation and places it in the compressed
    tree. Then it continues to compress further down.
    
    compTreeWeirdBFS is the breadth-first traversal version for the compressed tree of the atomic tree's
    breadth-first traversal. The only difference is that it prints strings of characters.
    
    isCompEmpty and destroyCompTree are the versions for the compressed tree of the functions described above.