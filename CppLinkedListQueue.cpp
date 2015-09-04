class Node {
protected:
	int data;
	Node *next;
public:
	Node(int d) {data = d};
	friend class Queue;
};

class Queue {
private:
	Node *front;
	Node *rear;
public:
	Queue(){front = NULL, rear = NULL};
	void enqueue(int d) {
		Node *newNode = new Node(d);
		newNode->next = NULL;
		if (front == NULL) {
			front = newNode;
		} else {
			rear->next = newNode;
		}
		rear = newNode;
	}
	void dequeue() {
		if (front == NULL) {
			std::cout << "Nothing in Queue\n";
		} else {
			Node *tmp = front;
			front = front->next;
			delete tmp;
		}
	}
}