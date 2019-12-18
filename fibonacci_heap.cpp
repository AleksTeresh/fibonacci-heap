#include <vector>
#include <cmath>

using namespace std;

template <typename T>
class FibonacciHeap;

template <typename T>
struct Node {
private:
    T value;
    Node<T> *next = nullptr;
    Node<T> *prev = nullptr;
    Node<T> *child = nullptr;
    Node<T> *parent = nullptr;
    int childrenCount = 0;
    bool marked = false;
public:
    explicit Node(T initVal) {
        this->value = initVal;
    }

    friend class FibonacciHeap<T>;
};

template <typename T>
class FibonacciHeap {
public:
    ~FibonacciHeap() {
        destructNode(min);
    }

    bool isEmpty();
    T getMin();
    int size();
    Node<T>* insert(T el);
    void merge(FibonacciHeap<T> &fh);
    T extractMin();
    void decreaseKey(Node<T>* nodeToDecrease, T val);
    void deleteNode(Node<T>* nodeToDelete);
private:
    int count = 0;
    Node<T>* min = nullptr;
    Node<T>* insert(Node<T>* node);
    void moveRootToChildren(Node<T>* futureChild, Node<T>* futureParent);
    void removeMinNode();
    void findNewMin();
    void decreaseNumberOfRoots();
    void mergeNodesOfSameDegree(Node<T>* currNode, vector<Node<T>*> &degreeArr);
    void decreaseKey(Node<T>* nodeToDecrease, T val, bool setToMinusInf);
    void startCutOutProcess(Node<T>* nodeToCutOut);
    void cutOutNode(Node<T>* nodeToCutOut);
    void destructNode(Node<T>* startNode);
};

template <typename T>
void FibonacciHeap<T>::destructNode(Node<T>* currNode) {
    if (currNode == nullptr) {
        return;
    }

    Node<T>* initNode = currNode;
    do {
        destructNode(currNode->child);

        Node<T>* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    } while (currNode != initNode);
}

template <typename T>
T FibonacciHeap<T>::getMin() {
    return min->value;
}

template <typename T>
int FibonacciHeap<T>::size() {
    return count;
}

template <typename T>
bool FibonacciHeap<T>::isEmpty() {
    return min == nullptr;
}

template <typename T>
Node<T>* FibonacciHeap<T>::insert(T el) {
    auto* newNode = new Node(el);
    count++;
    return insert(newNode);
};

template <typename T>
void FibonacciHeap<T>::merge(FibonacciHeap<T> &fh) {
    Node<T>* min1 = min;
    Node<T>* min2 = fh.min;

    if (min1 == nullptr) {
        count = fh.count;
        min = min2;

        // set min pointer of fh to nullptr
        // to avoid destruction of nodes that were just merged
        fh.min = nullptr;
        return;
    }
    if (min2 == nullptr) {
        return;
    }

    Node<T>* min1Next = min1->next;
    Node<T>* min2Next = min2->next;

    min1->next = nullptr;
    min1Next->prev = nullptr;
    min2->next = nullptr;
    min2Next->prev = nullptr;

    min1->next = min2Next;
    min2->next = min1Next;
    min1Next->prev = min2;
    min2Next->prev = min1;

    if (min2->value < min1->value) {
        min = min2;
    }

    count = count + fh.count;

    // set min pointer of fh to nullptr
    // to avoid destruction of nodes that were just merged
    fh.min = nullptr;
}

template <typename T>
T FibonacciHeap<T>::extractMin() {
    if (count == 0) {
        throw std::logic_error("The heap is empty. Unable to extract min");
    }

    T minVal = min->value;
    // first phase
    removeMinNode();

    // if min has sibling nodes
    if (count != 0 && min->next != min) {
        // second phase
        decreaseNumberOfRoots();
        // 3rd phase
        findNewMin();
    }
    return minVal;
}

template <typename T>
void FibonacciHeap<T>::decreaseKey(Node<T> *nodeToDecrease, T val) {
    // make sure the key is not increased
    if (val > nodeToDecrease->value) {
        throw std::logic_error("Not able to increase the key using decreaseKey operation");
    }

    nodeToDecrease->value = val;
    Node<T>* parent = nodeToDecrease->parent;
    if (parent != nullptr && val < parent->value) {
        startCutOutProcess(nodeToDecrease);
    }

    if (val < min->value) {
        min = nodeToDecrease;
    }
}

template <typename T>
void FibonacciHeap<T>::deleteNode(Node<T> *nodeToDelete) {
    if (nodeToDelete->parent != nullptr) {
        startCutOutProcess(nodeToDelete);
    }
    min = nodeToDelete;
    extractMin();
}

template <typename T>
void FibonacciHeap<T>::startCutOutProcess(Node<T> *nodeToCutOut) {
    Node<T>* parent = nodeToCutOut->parent;
    cutOutNode(nodeToCutOut);

    while (parent->parent != nullptr) { // not a root
        Node<T>* currNode = parent;
        parent = currNode->parent;
        if (currNode->marked) {
            cutOutNode(currNode);
        } else {
            currNode->marked = true;
            break;
        }
    }
}

template <typename T>
void FibonacciHeap<T>::cutOutNode(Node<T> *nodeToCutOut) {
    Node<T>* parent = nodeToCutOut->parent;
    if (parent->child == nodeToCutOut) {
        if (nodeToCutOut->next == nodeToCutOut) {
            parent->child = nullptr;
        } else {
            parent->child = nodeToCutOut->next;
        }
    }

    parent->childrenCount--;
    insert(nodeToCutOut);
}

template <typename T>
Node<T>* FibonacciHeap<T>::insert(Node<T>* node) {
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    }
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    }

    node->parent = nullptr;
    node->marked = false;
    if (this->isEmpty()) {
        min = node;
        min->next = min;
        min->prev = min;
    } else {
        Node<T>* nextAfterMin = min->next;
        min->next = node;
        node->prev = min;

        node->next = nextAfterMin;
        nextAfterMin->prev = node;

        if (min->value > node->value) {
            min = node;
        }
    }

    return node;
}

template <typename T>
void FibonacciHeap<T>::moveRootToChildren(
        Node<T>* futureChild,
        Node<T>* futureParent
) {
    // the node is not a root anymore
    futureChild->prev->next = futureChild->next;
    futureChild->next->prev = futureChild->prev;

    // add a child
    if (futureParent->childrenCount == 0) {
        futureParent->child = futureChild;
        futureChild->prev = futureChild;
        futureChild->next = futureChild;
    } else {
        Node<T>* nextOfChildOfFutureParent = futureParent->child->next;
        futureParent->child->next = futureChild;
        futureChild->prev = futureParent->child;
        futureChild->next = nextOfChildOfFutureParent;
        nextOfChildOfFutureParent->prev = futureChild;
    }

    futureChild->parent = futureParent;
    futureParent->childrenCount++;
}

template <typename T>
void FibonacciHeap<T>::removeMinNode() {
    // make all children as roots
    Node<T>* toBeUplifted = nullptr;
    Node<T>* nextChild = min->child;
    while (nextChild != toBeUplifted) {
        toBeUplifted = nextChild;
        nextChild = toBeUplifted->next;

        insert(toBeUplifted);
    }

    Node<T>* minToBeDeleted = min;
    if (min->prev != min) { // min is not a single root element
        min->prev->next = min->next;
        min->next->prev = min->prev;
        min = min->next;// setup potential min for now
    } else {
        min = nullptr;
    }

    delete minToBeDeleted;
    count--;
}

template <typename T>
void FibonacciHeap<T>::mergeNodesOfSameDegree(
        Node<T>* currNode,
        vector<Node<T>*> &degreeArr
) {
    int currNodeDegree = currNode->childrenCount;
    Node<T>* sameDegreeNode = degreeArr[currNodeDegree];
    degreeArr[currNodeDegree] = currNode;

    while (sameDegreeNode != nullptr) {
        Node<T>* child = sameDegreeNode->value > currNode->value
                         ? sameDegreeNode
                         : currNode;
        Node<T>* parent = sameDegreeNode->value > currNode->value
                          ? currNode
                          : sameDegreeNode;

        if (child == min) {
            min = min->next;
        }

        moveRootToChildren(child, parent);

        int currNodeDegree = parent->childrenCount;
        sameDegreeNode = degreeArr[currNodeDegree];
        degreeArr[currNodeDegree] = parent;
        degreeArr[currNodeDegree-1] = nullptr;

        currNode = parent;
    }
}

template <typename T>
void FibonacciHeap<T>::decreaseNumberOfRoots() {
    // array with pointers to nodes of i'th degree
    vector<Node<T>*> degreeArr;
    degreeArr.resize(log2(count) + 1);
    // insert degree of the current min
    degreeArr[min->childrenCount] = min;
    // start the algorithm with the next node after the min
    Node<T>* currNode = min->next;
    // true when each of the initial roots is visited at least once
    bool allRootsSeen = false;

    // while not all initial roots are yet processed
    while (!allRootsSeen) {
        Node<T>* nextNode = currNode->next;
        if (nextNode == min)
            allRootsSeen = true;

        mergeNodesOfSameDegree(currNode, degreeArr);
        currNode = nextNode;
    }
}

template <typename T>
void FibonacciHeap<T>::findNewMin() {
    Node<T>* startRootNode = min;
    Node<T>* minPotential = startRootNode->next;

    while (minPotential != startRootNode) {
        if (minPotential->value < min->value) {
            min = minPotential;
        }
        minPotential = minPotential->next;
    }
}
