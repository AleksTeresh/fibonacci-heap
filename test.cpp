#include "fibonacci_heap.cpp"

// insert
void insertToEmptyHeap() {
    FibonacciHeap<int> f1;
    f1.insert(2);

    assert(f1.extractMin() == 2);
}

void insertLargerValueToNonEmptyHeap() {
    FibonacciHeap<int> f1;
    f1.insert(2);
    f1.insert(6);

    assert(f1.extractMin() == 2);
}

void insertNewMinToNonEmptyHeap() {
    FibonacciHeap<int> f1;
    f1.insert(2);
    f1.insert(6);
    f1.insert(1);

    assert(f1.extractMin() == 1);
}


// merge

void merge2FullHeaps() {
    FibonacciHeap<int> f1;
    f1.insert(2);
    f1.insert(4);
    FibonacciHeap<int> f2;
    f2.insert(1);
    f2.insert(3);
    f2.insert(0);

    f1.merge(f2);

    assert(f1.extractMin() == 0);
}

void merge2SingleNodedHeaps() {
    FibonacciHeap<int> f1;
    f1.insert(2);
    FibonacciHeap<int> f2;
    f2.insert(3);

    f1.merge(f2);

    assert(f1.extractMin() == 2);
}

void mergeFullAndEmpty() {
    FibonacciHeap<int> f1;
    f1.insert(2);
    f1.insert(4);
    FibonacciHeap<int> f2;

    f1.merge(f2);

    assert(f1.extractMin() == 2);
}

void mergeEmptyAndFull() {
    FibonacciHeap<int> f1;
    FibonacciHeap<int> f2;
    f2.insert(1);
    f2.insert(3);
    f2.insert(0);

    f1.merge(f2);

    assert(f1.extractMin() == 0);
}

void merge2EmptyHeaps() {
    FibonacciHeap<int> f1;
    FibonacciHeap<int> f2;

    f1.merge(f2);

    assert(f1.size() == 0);
}

// extractMin
void extractTheOnlyNode() {
    FibonacciHeap<int> f1;
    f1.insert(2);

    assert(f1.extractMin() == 2);
    assert(f1.size() == 0);
}

void extractNodeWithoutChildren() {
    FibonacciHeap<int> f1;
    f1.insert(1);
    f1.insert(2);
    f1.insert(3);
    f1.insert(4);
    f1.insert(5);
    f1.insert(6);
    f1.extractMin();

    assert(f1.extractMin() == 2);
}

void extractNodeWithChildren() {
    FibonacciHeap<int> f1;
    f1.insert(1);
    f1.insert(2);
    f1.insert(1);
    f1.insert(4);
    f1.insert(5);
    f1.insert(6);
    f1.extractMin();

    assert(f1.extractMin() == 1);
}

void extractMinAndMergeAllToOneRoot() {
    FibonacciHeap<int> f1;
    f1.insert(1);
    f1.insert(2);
    f1.insert(3);
    f1.insert(4);
    f1.insert(5);
    f1.extractMin();

    assert(f1.size() == 4);
    assert(f1.extractMin() == 2);
}

void extractMinAndDo4RecursiveMerges() {
    FibonacciHeap<int> f1;
    for (int i = 0; i < 17; i++) {
        f1.insert(i);
    }
    f1.extractMin();

    assert(f1.size() == 16);
    assert(f1.extractMin() == 1);
}

// decreaseKey
void decreaseKeyWhenAllNodesAreRoots() {
    FibonacciHeap<int> f1;
    f1.insert(1);
    f1.insert(2);
    Node<int>* n = f1.insert(3);
    f1.insert(4);
    f1.insert(5);
    f1.decreaseKey(n, 0);

    assert(f1.size() == 5);
    assert(f1.extractMin() == 0);
}

void decreaseKeyOfRoot() {
    FibonacciHeap<int> f1;

    Node<int>* nodeToDecrease;
    for (int i = 0; i < 17; i++) {
        Node<int>* n = f1.insert(i);

        if (i == 1) {
            nodeToDecrease = n;
        }
    }
    f1.extractMin();

    f1.decreaseKey(nodeToDecrease, 0);

    assert(f1.size() == 16);
    assert(f1.extractMin() == 0);
}

void decreaseKeyOfMinNode() {
    FibonacciHeap<int> f1;
    Node<int>* n = f1.insert(1);
    f1.insert(2);
    f1.insert(3);
    f1.insert(4);
    f1.insert(5);
    f1.decreaseKey(n, 0);

    assert(f1.size() == 5);
    assert(f1.extractMin() == 0);
}

void decreaseKeyOfLeaf() {
    FibonacciHeap<int> f1;

    Node<int>* nodeToDecrease;
    for (int i = 0; i < 17; i++) {
        Node<int>* n = f1.insert(i);

        if (i == 12) {
            nodeToDecrease = n;
        }
    }
    f1.extractMin();

    f1.decreaseKey(nodeToDecrease, 0);

    assert(f1.size() == 16);
    assert(f1.extractMin() == 0);
}

void decreaseKeyOfMinNodeWithMarkedParent() {
    FibonacciHeap<int> f1;

    Node<int>* nodeToDecrease1;
    Node<int>* nodeToDecrease2;
    for (int i = 0; i < 17; i++) {
        Node<int>* n = f1.insert(i);

        if (i == 14) {
            nodeToDecrease1 = n;
        }
        if (i == 15) {
            nodeToDecrease2 = n;
        }
    }
    f1.extractMin();

    f1.decreaseKey(nodeToDecrease1, 2);
    f1.decreaseKey(nodeToDecrease2, 3);

    assert(f1.size() == 16);
    assert(f1.extractMin() == 1);
}

void decreaseKeyOfMinNodeWithAllAncestorsMarked() {
    FibonacciHeap<int> f1;

    Node<int>* nodeToDecrease1;
    Node<int>* nodeToDecrease2;
    Node<int>* nodeToDecrease3;
    for (int i = 0; i < 17; i++) {
        Node<int>* n = f1.insert(i);

        if (i == 10) {
            nodeToDecrease1 = n;
        }
        if (i == 14) {
            nodeToDecrease2 = n;
        }
        if (i == 15) {
            nodeToDecrease3 = n;
        }
    }
    f1.extractMin();

    f1.decreaseKey(nodeToDecrease1, 2);
    f1.decreaseKey(nodeToDecrease2, 3);
    f1.decreaseKey(nodeToDecrease3, 0);

    assert(f1.size() == 16);
    assert(f1.extractMin() == 0);
}


// delete node
void deleteRoot() {
    FibonacciHeap<int> f1;
    Node<int>* root = f1.insert(2);
    f1.insert(6);
    f1.insert(1);

    f1.deleteNode(root);

    assert(f1.extractMin() == 1);
}

void deleteCurrentMin() {
    FibonacciHeap<int> f1;
    f1.insert(2);
    f1.insert(6);
    Node<int>* currMin = f1.insert(1);

    f1.deleteNode(currMin);

    assert(f1.extractMin() == 2);
}

void deleteNodeInTheMiddle() {
    FibonacciHeap<int> f1;
    f1.insert(1);
    f1.insert(2);
    f1.insert(3);
    f1.insert(4);
    Node<int>* midNode = f1.insert(5);
    f1.insert(6);
    f1.extractMin();
    f1.deleteNode(midNode);

    assert(f1.size() == 4);
    assert(f1.extractMin() == 2);
}

void deleteLeaf() {
    FibonacciHeap<int> f1;
    f1.insert(1);
    f1.insert(2);
    f1.insert(3);
    f1.insert(4);
    f1.insert(5);
    Node<int>* child = f1.insert(6);
    f1.extractMin();
    f1.deleteNode(child);

    assert(f1.size() == 4);
    assert(f1.extractMin() == 2);
}

// general tests
void basicTest1() {
    FibonacciHeap<int> fib;
    Node<int>* five = fib.insert(5);
    fib.insert(8);
    fib.insert(5);

    FibonacciHeap<int> fib1;
    fib1.insert(1);
    fib1.insert(2);
    fib1.insert(4);

    fib.merge(fib1);

    int extractedMin = fib.extractMin();
    assert(extractedMin == 1);
    fib.decreaseKey(five, 3);
    extractedMin = fib.extractMin();
    assert(extractedMin == 2);
    fib.deleteNode(five);
    extractedMin = fib.extractMin();
    assert(extractedMin == 4);
}

void basicTest2() {
    FibonacciHeap<int> fib;
    fib.insert(2);
    fib.insert(3);
    fib.insert(1);
    fib.insert(4);
    int extractedMin = fib.extractMin();
    extractedMin=  fib.extractMin();
    fib.insert(5);
    fib.insert(7);
    extractedMin = fib.extractMin();
    fib.insert(2);
    Node<int>* ninety = fib.insert(90);
    extractedMin = fib.extractMin();
    extractedMin = fib.extractMin();
    extractedMin =  fib.extractMin();

    Node<int>* first28;
    for(int i=0;i<20;i+=2) {
        Node<int>* n = fib.insert(30-i);

        if (30 - i == 28) {
            first28 = n;
        }
    }
    for(int i=0;i<4;i++) {
        extractedMin = fib.extractMin();
    }

    Node<int>* second28;
    for(int i=0;i<20;i+=2) {
        Node<int>* n = fib.insert(30-i);

        if (30 - i == 28) {
            second28 = n;
        }
    }
    Node<int>* last23 = fib.insert(23);
    for(int i=0;i<7;i++) {
        extractedMin = fib.extractMin();
    }
    fib.decreaseKey(ninety, 1);

    fib.decreaseKey(first28,2);
    fib.decreaseKey(second28,2);


    fib.decreaseKey(last23,3);

    for(int i=0;i<7;i++) {
        extractedMin = fib.extractMin();
    }

    assert(extractedMin == 24);
}

void runTests() {
    basicTest1();
    basicTest2();

    insertToEmptyHeap();
    insertNewMinToNonEmptyHeap();
    insertLargerValueToNonEmptyHeap();

    merge2FullHeaps();
    merge2EmptyHeaps();
    merge2SingleNodedHeaps();
    mergeFullAndEmpty();
    mergeEmptyAndFull();

    extractTheOnlyNode();
    extractNodeWithoutChildren();
    extractNodeWithChildren();
    extractMinAndMergeAllToOneRoot();
    extractMinAndDo4RecursiveMerges();

    decreaseKeyWhenAllNodesAreRoots();

    decreaseKeyOfRoot();
    decreaseKeyOfLeaf();
    decreaseKeyOfMinNode();
    decreaseKeyOfMinNodeWithMarkedParent();
    decreaseKeyOfMinNodeWithAllAncestorsMarked();

    deleteCurrentMin();
    deleteLeaf();
    deleteRoot();
    deleteNodeInTheMiddle();
}