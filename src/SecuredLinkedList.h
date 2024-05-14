// Created by Steven Cybinski
// GitHub: https://github.com/StevenCyb/SecuredLinkedList

#ifndef SecuredLinkedList_h
#define SecuredLinkedList_h

#include <mutex>

template<class T>
struct SecuredLinkedListNode {
	T data;
	SecuredLinkedListNode<T> *next;
};

template<class T>
class SecuredLinkedList {
	private:
		std::mutex *mtx;
		unsigned int listSize;
		SecuredLinkedListNode<T> *root;
		SecuredLinkedListNode<T> *leaf;
		virtual unsigned int sizeUnsecured();
		virtual void pushUnsecured(T t);
		virtual T popUnsecured();
		virtual void addUnsecured(unsigned int index, T t);
		virtual T getUnsecured(unsigned int index);
		virtual void removeUnsecured(unsigned int index);
		virtual void unshiftUnsecured(T t);
		virtual T shiftUnsecured();
		virtual void clearUnsecured();
	public:
		SecuredLinkedList(void);
		~SecuredLinkedList(void);
		virtual unsigned int size();
		virtual void push(T t);
		virtual T pop();
		virtual void add(unsigned int index, T t);
		virtual T get(unsigned int index);
		virtual void remove(unsigned int index);
		virtual void unshift(T t);
		virtual T shift();
		virtual void clear();
};

template<typename T>
SecuredLinkedList<T>::SecuredLinkedList() {
	listSize = 0;
	mtx = new std::mutex();
}

template<typename T>
SecuredLinkedList<T>::~SecuredLinkedList() {
	listSize = 0;
	delete root;
	delete leaf;
	delete mtx;
}

template<typename T>
unsigned int SecuredLinkedList<T>::size() {
	std::lock_guard<std::mutex> locker (*mtx);
	return sizeUnsecured();
}
template<typename T>
unsigned int SecuredLinkedList<T>::sizeUnsecured() {
	return listSize;
}

template<typename T>
void SecuredLinkedList<T>::push(T t) {
	std::lock_guard<std::mutex> locker (*mtx);
	pushUnsecured(t);
}
template<typename T>
void SecuredLinkedList<T>::pushUnsecured(T t) {
	SecuredLinkedListNode<T> *cache = new SecuredLinkedListNode<T>();
	cache->data = t;
	if(listSize <= 0) {
		root = cache;
		leaf = cache;
		listSize += 1;
	} else if(listSize == 1) {
		root->next = cache;
		leaf = cache;
		listSize += 1;
	} else {
		leaf->next = cache;
		leaf = cache;
		listSize += 1;
	}
}

template<typename T>
T SecuredLinkedList<T>::pop() {
	std::lock_guard<std::mutex> locker (*mtx);
	return popUnsecured();
}
template<typename T>
T SecuredLinkedList<T>::popUnsecured() {
	if(listSize <= 0) {
		return T();
	} else if(listSize > 1) {
		SecuredLinkedListNode<T> *toRemove = leaf;
		T cache = leaf->data;
		SecuredLinkedListNode<T> *previous = root;
		while(previous->next->next != NULL) {
			previous = previous->next;
		}
		leaf = previous;
		leaf->next = NULL;
		listSize -= 1;
		delete toRemove;
		return cache;
	} else {
		T cache = root->data;
		delete root;
		root = NULL;
		leaf = NULL;
		listSize -= 1;
		return cache;
	}
}

template<typename T>
void SecuredLinkedList<T>::add(unsigned int index, T t) {
	std::lock_guard<std::mutex> locker (*mtx);
	addUnsecured(index, t);
}
template<typename T>
void SecuredLinkedList<T>::addUnsecured(unsigned int index, T t) {
	if(index <= 0) {
		unshiftUnsecured(t);
	} else if (index >= (listSize - 1)) {
		pushUnsecured(t);
	} else {
		SecuredLinkedListNode<T> *previous = root;
		for(unsigned int i = 1; i < index; i++) {
			previous = previous->next;
		}
		SecuredLinkedListNode<T> *cache = new SecuredLinkedListNode<T>();
		cache->data = t;
		cache->next = previous->next;
		previous->next = cache;
		listSize += 1;
	}
}

template<typename T>
T SecuredLinkedList<T>::get(unsigned int index) {
	std::lock_guard<std::mutex> locker (*mtx);
	return getUnsecured(index);
}
template<typename T>
T SecuredLinkedList<T>::getUnsecured(unsigned int index) {
	if(index <= 0) {
		return root->data;
	} else {
		SecuredLinkedListNode<T> *previous = root;
		for(unsigned int i = 0; i < index; i++) {
			previous = previous->next;
		}
		return previous->data;
	}
}

template<typename T>
void SecuredLinkedList<T>::remove(unsigned int index) {
	std::lock_guard<std::mutex> locker (*mtx);
	return removeUnsecured(index);
}
template<typename T>
void SecuredLinkedList<T>::removeUnsecured(unsigned int index) {
	if(listSize <= 0 || index >= listSize) {
		return;
	} else if(index == 0) {
		shiftUnsecured();
		return;
	} else if(index == listSize - 1) {
		popUnsecured();
		return;
	}

	SecuredLinkedListNode<T> *beforePrevious; // A
	SecuredLinkedListNode<T> *previous = root; // B
	for(unsigned int i = 0; i < index; i++) {
		beforePrevious = previous;
		previous = previous->next;
	}
	SecuredLinkedListNode<T> *toRemove = previous;
	beforePrevious->next = previous->next;
	listSize -= 1;
	delete toRemove;
}

template<typename T>
void SecuredLinkedList<T>::unshift(T t) {
	std::lock_guard<std::mutex> locker (*mtx);
	unshiftUnsecured(t);
}
template<typename T>
void SecuredLinkedList<T>::unshiftUnsecured(T t) {
	if(listSize <= 0) {
		pushUnsecured(t);
	} else {
		SecuredLinkedListNode<T> *cache = new SecuredLinkedListNode<T>();
		cache->data = t;
		cache->next = root;
		root = cache;
		listSize += 1;
		if(listSize == 2) {
			leaf = root->next;
		}
	}
}

template<typename T>
T SecuredLinkedList<T>::shift() {
	std::lock_guard<std::mutex> locker (*mtx);
	return shiftUnsecured();
}
template<typename T>
T SecuredLinkedList<T>::shiftUnsecured() {
	if(listSize <= 0) {
		return T();
	}
	if(listSize > 1) {
		SecuredLinkedListNode<T> *toRemove = root;
		T cache = root->data;
		root = root->next;
		listSize -= 1;
		delete toRemove;
		return cache;
	} else {
		return popUnsecured();
	}
}

template<typename T>
void SecuredLinkedList<T>::clear() {
	std::lock_guard<std::mutex> locker (*mtx);
	clearUnsecured();
}
template<typename T>
void SecuredLinkedList<T>::clearUnsecured() {
	while(listSize > 0) {
		shiftUnsecured();
	}
}

#endif