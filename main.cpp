#include "fibonacci_heap.cpp"

using namespace std;

int main() {
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

    fib.insert(2);
    fib.insert(3);
    fib.insert(1);
    fib.insert(4);
    extractedMin = fib.extractMin();
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

    assert(extractedMin == 22);

    return 0;
}