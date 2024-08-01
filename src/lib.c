#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "linkedlist.h"

// Initialize an empty list
void initList(List* list_pointer){
	list_pointer->head = NULL;
	list_pointer->tail = NULL;
}

// Create node containing item, return reference of it.
Node* createNode(void* item){
	Node* node = (Node *) malloc(sizeof(Node)); // malloc
	node->item = item; // set item
	node->next = NULL; // set next to be null
	return node;
}

// Insert new item at the end of list.
int insertAtTail(List* list_pointer, void* item){
	Node* new = createNode(item); // use createNode function
	if(list_pointer->head == NULL){ //list is empty
		list_pointer->head = (Node*) new;
		list_pointer->tail = (Node*) new;
	}
	else{ //insert at tail
		list_pointer->tail->next = new;
		list_pointer->tail = (Node*) new;
	}
	return 0;
}

// Insert item at start of the list.
int insertAtHead(List* list_pointer, void* item){
	Node* new = createNode(item);
	if(list_pointer->head == NULL){
		list_pointer->head = (Node*) new;
		list_pointer->tail = (Node*) new;
	}
	else{
		new->next = list_pointer->head;
		list_pointer->head = (Node*) new;
	}
	return 0;
}

// Insert item at a specified index.
int insertAtIndex(List* list_pointer, int index, void* item){
	if(list_pointer->head == NULL) {
		printf("\nEmpty List\n");
		return 1;
	}
	Node* node = (Node*) list_pointer->head;
	Node* node2 = (Node*) node->next;
	Node* new = createNode(item);
	int s = size(list_pointer); 
	if(index > s){ //index out of bounds
		printf("\nIndex Not In Bounds.\n");
		return 1;
	}
	if(index == s){ //index is last in list
		insertAtTail(list_pointer,item);
		return 0;
	}
	if(index == 0){ //index is first
		insertAtHead(list_pointer, item);
		return 0;
	}

	int counter = 1;
	while(counter != index){
		node = node->next;
		node2 = node2->next;
		counter++;
	}
	node->next = new;
	new->next = node2;
	return 0;
}

// Remove item from the end of list and return a reference to it
void* removeTail(List* list_pointer){
	void* reference = list_pointer->tail->item;
	if(list_pointer->head == NULL) { //check if empty
		printf("\nEmpty List\n");
		return NULL;
	}
	if(list_pointer->head == list_pointer->tail){
		Node* node = (Node*) list_pointer->head;
		list_pointer->head = node->next;
		free(node);
		return reference;
	}

	Node* node = (Node*) list_pointer->head;
	while(node->next != NULL){
		Node* node2 = (Node*) node->next;
		if(node2->next == NULL){
			break;
		}
		node = node->next;	
	}
	list_pointer->tail = node;
	free(node->next);
	node->next = NULL;
	
	return reference;
}

// Remove item from start of list and return a reference to it
void* removeHead(List* list_pointer){
	if(list_pointer->head == NULL){
		printf("Linked List is empty.");
		return NULL;
	}
	Node* node = (Node*) list_pointer->head;
	void* reference = node->item;
	list_pointer->head = node->next;
	free(node);
	return reference; 
}

// Insert item at a specified index and return a reference to it
void* removeAtIndex(List* list_pointer, int index){
	if(list_pointer->head == NULL) {
		printf("\nEmpty List\n");
		return NULL;
	}
	int s = size(list_pointer); 
	if(index > s){
		printf("Index is out of bounds.\n");
		return NULL;
	}
	if(index == s){
		return removeTail(list_pointer);
	}
	if(index == 0){
		return removeHead(list_pointer);
	}
	int counter = 1;
	Node* node = (Node*) list_pointer->head;
	Node* node2;
	while(node->next != NULL){ 
		node2 = (Node*) node->next;
		if(counter == index){
			break;
		}
		node = node->next;	
		counter++;
	}
	void* ref = node2->item;
	node->next = node2->next;
	free(node2);
	return ref;
}

// Return item at index
void* itemAtIndex(List* list_pointer, int index){
	if(list_pointer->head == NULL) { // empty list
		printf("\nEmpty List\n");
		return NULL;
	}
	int s = size(list_pointer); 
	if(index >= s){
		printf("Index is out of bounds.\n");
		return NULL;
	}
	if(index == (s-1)){
		return list_pointer->tail->item;
	}
	if(index == 0){
		return list_pointer->head->item;
	}
	int counter = 1;
	Node* node = (Node*) list_pointer->head;
	Node* node2;
	while(node->next != NULL){
		node2 = (Node*) node->next;
		if(counter == index){
			break;
		}
		node = node->next;	
		counter++;
	}
	return node2->item;
}

// Return true if the list contains the given item at least once, false otherwise.
bool contains(List* list_pointer, void* item){
	if(list_pointer->head == NULL) {
		printf("\nEmpty List\n");
		return false;
	}
	Node* node = (Node*) list_pointer->head;
	while(node != NULL) {
		if(node->item == item){
			return true;
		}
		node = (Node*) node->next;
	}
	return false;

}

// Returns the size of the list, measured in nodes.
int size(List* list_pointer){
	if(list_pointer->head == NULL) {
		printf("\nEmpty List\n");
		return 0;
	}
	int counter = 0;
	Node* node = (Node*) list_pointer->head;
	while(node != NULL) {
		node = (Node*) node->next;
		counter++;
	}
	return counter;
}

// Print List
void printList(List* list) {
	Node* node;

  	// Handle an empty node. Just print a message.
	if(list->head == NULL) {
		printf("\nEmpty List\n");
		return;
	}
	
  	// Start with the head.
	node = (Node*) list->head;

	printf("\nList: \n\n\t"); 
	while(node != NULL) {
		printf("[ %d ]", node->item);

		// Move to the next node
		node = (Node*) node->next;

		if(node !=NULL) {
			printf("-->");
		}
	}
	printf("\n\n");
}

//get the number of the index or value back from the test file
int* parse(char* line, int counter){
	char* num = malloc(sizeof(char));
	int i = 0;
	while(isdigit(line[counter])){
		num[i] = line[counter];
		i++;
		num = realloc(num, (i+1)*sizeof(char));
		counter++;
	};
	int value = atoi(num);
	int* arr = malloc(2 * sizeof(int));
	arr[0] = i;
	arr[1] = value;
	free(num);
	return arr;
}

//if statements for each command in the test file
int* command(char *line, List* list, int counter){
	if(line[counter] == 'N'){
		int dif = counter;
		counter++;
		int* p = parse(line, counter);
		int index = p[1];
		counter += p[0];
		free(p); 
		counter ++; // comma
		p = parse(line, counter);
		int value = p[1];
		counter+= p[0];
		free(p);
		insertAtIndex(list,index,value);
		counter -= dif;
		int* arr = malloc(2 * sizeof(int));
		arr[0] = counter;
		arr[1] = 0;
		return arr;
	}
	if(line[counter] == 'H'){
		int dif = counter;
		counter++;
		int* p = parse(line, counter);
		int value = p[1];
		counter += p[0];
		free(p);
		insertAtHead(list, value);
		counter -= dif;
		int* arr = malloc(2 * sizeof(int));
		arr[0] = counter;
		arr[1] = 0;
		return arr;
	}
	if(line[counter] == 'T'){
		int dif = counter;
		counter++;
		int* p = parse(line, counter);
		int value = p[1];
		counter += p[0];
		free(p);
		insertAtTail(list, value);
		counter -= dif;
		int* arr = malloc(2 * sizeof(int));
		arr[0] = counter;
		arr[1] = 0;
		return arr;
	}
	if(line[counter] == 'E'){
		int dif = counter;
		counter++;
		int* p = parse(line, counter);
		int index = p[1];
		counter += p[0];
		free(p);
		removeAtIndex(list, index);
		counter -= dif;
		int* arr = malloc(2 * sizeof(int));
		arr[0] = counter;
		arr[1] = 0;
		return arr;
	}
	if(line[counter] == 'D'){
		removeHead(list);
		int* arr = malloc(2 * sizeof(int));
		arr[0] = 1;
		arr[1] = 0;
		return arr;
	}
	if(line[counter] == 'C'){
		removeTail(list);
		int* arr = malloc(2 * sizeof(int));
		arr[0] = 1;
		arr[1] = 0;
		return arr;
	}
	if(line[counter] == 'Q'){
		int dif = counter;
		counter++;
		int* p = parse(line, counter);
		int index = p[1];
		counter += p[0];
		free(p); 
		counter ++; // for the comma
		p = parse(line, counter);
		int value = p[1];
		counter+= p[0];
		free(p);
		int item = itemAtIndex(list,index);
		counter -= dif;
		int* arr = malloc(2 * sizeof(int));
		arr[0] = counter;
		if(item == value){
			arr[1] = 0;
		}else{
			arr[1] = 1;
		}
		return arr;
	}
	if(line[counter] == 'A'){
		int dif = counter;
		counter++;
		int* p = parse(line, counter);
		int value = p[1];
		counter += p[0];
		free(p); 
		counter -= dif;
		int* arr = malloc(2 * sizeof(int));
		arr[0] = counter;
		if(list->head->item == value){
			arr[1] = 0;
		}else{
			arr[1] = 1;
		}
		return arr;
	}
	if(line[counter] == 'Z'){
		int dif = counter;
		counter++;
		int* p = parse(line, counter);
		int value = p[1];
		counter += p[0];
		free(p); 
		counter -= dif;
		int* arr = malloc(2 * sizeof(int));
		arr[0] = counter;
		if(list->tail->item == value){
			arr[1] = 0;
		}else{
			arr[1] = 1;
		}
		return arr;
	}
	if(line[counter] == 'S'){
		int dif = counter;
		counter++;
		int* p = parse(line, counter);
		int s = p[1];
		counter += p[0];
		free(p); 
		counter -= dif;
		int* arr = malloc(2 * sizeof(int));
		arr[0] = counter;
		if(size(list) == s){
			arr[1] = 0;
		}else{
			arr[1] = 1;
		}
		return arr;
	}
	if(line[counter] == 'W'){
		int dif = counter;
		counter++;
		int* p = parse(line, counter);
		int value = p[1];
		counter += p[0];
		free(p); 
		counter -= dif;
		int* arr = malloc(2 * sizeof(int));
		arr[0] = counter;
		if(contains(list,value)){
			arr[1] = 0;
		}else{
			arr[1] = 1;
		}
		return arr;
	}
	return NULL;
}

//free the list after used
void freeList(List* list){
	Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
	free(list);
}

