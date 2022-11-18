

#ifndef __HEAP__
#define __HEAP__

#include <iostream>
#include <iomanip>
#include <vector>

template <typename T, typename CMP = std::less<T>>
class Heap {
public:
	Heap(); //empty constructor
	Heap(std::vector<T> v); //constructor
	void display(); // prints all elements in the order stored in the vector
	void push();  //push nothing
	void push(T); //place an object of type T into the heap
	template <typename T1, typename... Trest>
	void push(T1 param1, Trest... param); //place multiple objects into the data structure
	T top() const; //returns the maximum value from the heap (as defined by comparator)
	void pop();//removes the maximum value from the heap(as defined by comparator)
	void sift_up(size_t index); //A helper function that move the node with certain index up
	void sift_down(size_t index); //A helper function that move the node with certain index down
	bool empty(); //A helper function that makes the heap empty
private:
	std::vector<T> data;
	CMP comparator;
};


template <typename T, typename CMP>
Heap<T, CMP>::Heap() {
}

template <typename T, typename CMP>
bool Heap<T, CMP>::empty() {
	return data.empty(); //make the data empty
}

template <typename T, typename CMP>
Heap<T, CMP>::Heap(std::vector<T> v) {
	for (const auto e : v) {
		push(e);  //use the funtion push() to let the element in v be stored in data with order
	}
}

template <typename T, typename CMP>
void Heap<T, CMP>::display() {  //go through and print all the elements in the data vector
	for (const auto& d : data) {
		std::cout << d << "\t";
	}
	std::cout << std::endl;
}

template<typename T, typename CMP>
void Heap<T, CMP>::push() {
}

template <typename T, typename CMP>
void Heap<T, CMP>::push(T e) {
	data.push_back(e);  //first insert the new element e to the end of the vector
	sift_up(data.size() - 1);  //move the newly inserted element up to the correct position
}

template<typename T, typename CMP>
template<typename T1, typename... Trest>
void Heap<T, CMP>::push(T1 param1, Trest... param) { //variadic version of the function push()
	data.push_back(param1); //base case: insert the new element e (as the bottom child in the right side) to the end of the vector
	sift_up(data.size() - 1); //move the newly inserted element upwards to the correct position
	push(param...); //recursively reuse the push() function for the rest of the input arguments
}

template <typename T, typename CMP>
void Heap<T, CMP>::sift_up(size_t index) { //move the current node upwards
	size_t parent_index = (index - 1) / 2; //the parent node of the current node
	if (index && comparator(data[index], data[parent_index])) { //when this node is larger than its parent (this node also exists)
		std::swap(data[index], data[parent_index]); //change the position of node and its parent
		sift_up(parent_index); //recursively check the position of the current parent node. If it is larger than its parent, swap it with its parent node.
	}

}

template <typename T, typename CMP>
void Heap<T, CMP>::sift_down(size_t index) {  //move the current node downwards

	size_t left = index * 2 + 1; //the left child of the current node
	size_t right = index * 2 + 2; //the right child of the current node
	size_t largest = index; // temporarily consider the current node as the largest node

	//For maximum heap: compare the current node with its left and right child to figure out the node with largest value 
	if (left < data.size() && comparator(data[left], data[index])) { //if the left node is larger than the current node
		largest = left; // set the left node as the new largest node
	}
	if (right < data.size() && comparator(data[right], data[largest])) { //if the right node is larger than the current largest node
		largest = right; // set the right node as the new largest node
	}
	if (index != largest) {  //if the current node is not larger than its left or right child
		std::swap(data[largest], data[index]); // swap the current node with the largest node (move the current node downwards)
		sift_down(largest); //recursively check the position of the current largest node, if any of its child is larger than it, move it downwards  
	}

}

template <typename T, typename CMP>
T Heap<T, CMP>::top() const {
	return data.front();  //return the first(also the largest) element of the maximum heap vector
}

template <typename T, typename CMP>
void Heap<T, CMP>::pop() {
	if (empty()) {
		return;
	}
	data[0] = data.back(); //let the end element temporarily substitute the top root of the heap
	data.pop_back(); //delete the end
	if (!empty()) {
		sift_down(0); //let the temporary root node move downwards to the proper position
	}
}

template <typename T, typename CMP>
void print(Heap<T, CMP> copy) {
	while (!copy.empty()) {
		const auto& t = copy.top();  //print the newest maximum
		copy.pop(); // delete the newest maximum 
		std::cout << t << "\t";
	}
	std::cout << std::endl;
}

template<typename T, typename CMP, typename... Trest>
void print(Heap<T, CMP> param1, Trest... param) {
	print(param1); //call base case
	std::cout << std::endl;
	print(param...); //recursively call the print for the rest of the input arguments
}

#endif