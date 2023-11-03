# Secured Linked List
The `SecuredLinkedList` is a library that provides the functionality of a linked list (like in Java or C#). Furthermore, the implementation is thread-safe, see demo `two_core_demo.ino`.
The following figure illustrates the available functions. A detailed description of the functions can be found below.
![Operations](/media/operations_illustration.png)
# Functions
- [SecuredLinkedList()](#SecuredLinkedList)
- [void push(T t)](#Push)
- [T pop()](#Pop)
- [void add(unsigned int index, T t)](#Add)
- [void remove(unsigned int index)](#Remove)
- [T get(unsigned int index)](#Get)
- [void unshift(T t)](#Unshift)
- [T shift()](#Shift)
- [unsigned int size()](#Size)
- [void clear()](#Clear)
<a name="InstantiateAndConstructor"></a>
## SecuredLinkedList()
The `SecuredLinkedList` can be instantiated as follows.
```
SecuredLinkedList<int> listA = SecuredLinkedList<int>();
SecuredLinkedList<int> *listB = new SecuredLinkedList<int>();
```
<a name="Push"></a>
## void push(T t)
Adds an element to the end of the list.
```
int t = 4;
listA.push(t);
listB->push(t);
```
<a name="Pop"></a>
## T pop()
Takes the last element from the list.
The list no longer contains the element.
```
Serial.println(listA.pop());
Serial.println(listB->pop());
```
<a name="Add"></a>
## void add(unsigned int index, T t)
Inserts an element into the according index.
```
int t = 2;
listA.push(3, t);
listB->push(3, t);
```
<a name="Remove"></a>
## void remove(unsigned int index)
Remove an element on index.
```
listA.remove(3);
listB->remove(3);
```
<a name="Get"></a>
## T get(unsigned int index)
Fetches the element from the according index.
The list still contains the element.
```
Serial.println(listA.get(2));
Serial.println(listB->get()2);
```
<a name="Unshift"></a>
## void unshift(T t)
Adds an element to the beginning of the list.
```
int t = 3;
listA.unshift(t);
listB->unshift(t);
```
<a name="Shift"></a>
## T shift()
Takes the first element from the list.
The list no longer contains the element.
```
Serial.println(listA.shift());
Serial.println(listB->shift());
```
<a name="Size"></a>
## unsigned int size()
Returns the number of elements.
```
Serial.println(listA.size());
Serial.println(listB->size());
```
<a name="Clear"></a>
## void clear()
Deletes all items from the list.
```
listA.clear();
listB->clear();
```
