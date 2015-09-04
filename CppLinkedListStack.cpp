#include <iostream>

class Node {
protected:
	Node *next;
	int data;
	int min; //In case ask to keep the min value in the stack
public:
	Node(int d) {data = d};
	friend class Stack;
};

class Stack {
private:
	Node *top;
	int length;
public:
	Stack(){top->next=NULL, length=0};
	~Stack(){
		while (top != NULL) {
			Node *toDelete = top;
			top = top->next;
			delete toDelete;
		}
	}

	void push(int d) {
		Node *n = new Node(d);
		if (top != NULL) {
			if (top->min < d) {
				n->min = top->min;
			} else {
				n->min = d;
			}
		} else {
			n->min = d;
		}
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