#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class LinkedList {
    private:
        struct Node {
            int item;
            Node* next;
        };

        Node* head;
        Node* tail;
        int size;

    public:
        LinkedList();
        ~LinkedList();
        void add(int item);
        bool remove(int item);
        bool contains(int item);
        int itemAtIndex(int index);
        void printList();
        int getHead();
        int getSize() const;
        bool isEmpty();
};

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

int LinkedList::getHead(){
    return head->item;
}

void LinkedList::add(int item) {
    Node* new_node = new Node{ item, nullptr };

    if (head == nullptr) {
        head = new_node;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
    size++;
}


bool LinkedList::remove(int item) {
    if (head == nullptr) {
        return false;
    }
    if (head->item == item) {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }
    Node* current = head;
    while (current->next != nullptr && current->next->item != item) {
        current = current->next;
    }
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        size--;
        return true;
    }
    return false;
}

bool LinkedList::contains(int item){
    if (head == nullptr) {
        return false;
    }
    if (head->item == item) {
        return true;
    }

    Node* current = head;
	while(current != nullptr) {
		if(current->item == item){
			return true;
		}
		current = current->next;
	}

    return false;
}

int LinkedList::itemAtIndex(int index){
    if(index == 0){
        return head->item;
    }
    int counter = 1;
    Node* current = head;
    Node* nextNode;
    while(current->next != nullptr){
        nextNode = current->next;
        if(counter == index){
            break;
        }
        current = current->next;
        counter++;
    }
    return nextNode->item;
}

void LinkedList::printList() {
	Node* node;

	if(this->head == NULL) {
		printf("Empty List\n");
		return;
	}
	
  	// Start with the head.
	node = (Node*) this->head;

	while(node != NULL) {
		printf("[ %x ]", node->item);

		// Move to the next node
		node = (Node*) node->next;

		if(node !=NULL) {
			printf("-->");
		}
	}
	printf("\n\n");
}

int LinkedList::getSize() const {
    return size;
}

bool LinkedList::isEmpty(){
    if(this->head == nullptr){
        return true;
    }
    return false;
}