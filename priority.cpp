#include <iostream>
#include <vector>
#include <algorithm> // for std::swap

class PriorityQueue {
private:
    std::vector<int> heap;

    void heapifyDown(int i) {
        int largest = i;   // Initialize largest as root
        int left = 2 * i;  // left child
        int right = 2 * i + 1; // right child

        // If left child is larger than root
        if (left <= heap.size() - 1 && heap[left] > heap[largest])
            largest = left;

        // If right child is larger than largest so far
        if (right <= heap.size() - 1 && heap[right] > heap[largest])
            largest = right;

        // If largest is not root
        if (largest != i) {
            std::swap(heap[i], heap[largest]);

            // Recursively heapify the affected sub-tree
            heapifyDown(largest);
        }
    }

    void heapifyUp(int i) {
        while (i > 1 && heap[i / 2] < heap[i]) {
            std::swap(heap[i], heap[i / 2]);
            i = i / 2;
        }
    }

public:
    PriorityQueue() {
        heap.push_back(0); // Dummy element to make the index 1-based
    }

    void push(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.size() == 1) {
            std::cout << "Heap is empty, cannot delete root.\n";
            return;
        }

        // Move the last element to the root
        heap[1] = heap.back();
        heap.pop_back();

        // Heapify the root element to maintain the heap property
        heapifyDown(1);
    }

    int top() {
        if (heap.size() > 1) {
            return heap[1];
        } else {
            throw std::out_of_range("Priority queue is empty");
        }
    }

    bool empty() {
        return heap.size() <= 1;
    }

    int size() {
        return heap.size() - 1;
    }
};

int main() {
    PriorityQueue pq;

    pq.push(12);
    pq.push(11);
    pq.push(13);
    pq.push(5);
    pq.push(6);
    pq.push(7);

    std::cout << "Priority Queue top element: " << pq.top() << "\n";

    pq.pop();

    std::cout << "Priority Queue top element after pop: " << pq.top() << "\n";

    std::cout << "Priority Queue elements: ";
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "\n";

    return 0;
}
