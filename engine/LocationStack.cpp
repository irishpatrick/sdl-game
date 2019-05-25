#include "LocationStack.hpp"
#include <iostream>

namespace engine {

	LocationStack::LocationStack() {

	}

	LocationStack::~LocationStack() {

	}

	template<typename T>
	void pop_front(std::vector<T>& v) {
		if (!v.empty()) {
			v.erase(v.begin());
		}
		else {
			std::cout << "stack empty" << std::endl;
		}
	}

	void LocationStack::push(Point p) {
		stack.push_back(p);
	}

	Point& LocationStack::pop() {
		Point& p = stack[0];
		pop_front(stack);
		return p;
	}

	bool LocationStack::isEmpty() {
		return stack.size() == 0;
	}

	void LocationStack::clear() {
		stack.clear();
	}

}
