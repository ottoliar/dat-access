#include <iostream>

class Node {
protected:
	Node *next;
	int data;
public:
	Node(int d) {data = d;}
	friend class Stack;
};

class Stack {
private:
	Node *top;
	int length;
public:
	Stack(){top-=NULL, length=0};
	~Stack(){
		while (top != NULL) {
			Node *toDelete = top;
			top = top->next;
			delete toDelete;
		}
	}

	void push(int d) {
		Node *n = new Node(d);
		n->next = top;
		top = n;
		length++;
	}

	int pop() {
		Node *oldTop = top;
		top = top->next;
		int oldTopData = oldTop->data;
		delete(oldTop);
		length--;
		return oldTopData;
	}

	void displayStack() {
		Node *current = top;
		while(current->next != NULL) {
			std::cout << current->data << std::endl;
			current = current->next;
		}
	}

	int getLength() {
		return length;
	}
}
