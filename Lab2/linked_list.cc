
template<typename T>
struct Node {
        T data;
        Node<T>* next;
        Node<T>* prev;
    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};


template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail; 

public:
    LinkedList();
    LinkedList(const LinkedList<T>& other);
    LinkedList(std::size_t count, int minValue, int maxValue);
    ~LinkedList();
    LinkedList<T>& operator=(const LinkedList<T>& other);
    void push_tail(const T& value);
    void push_tail(const LinkedList<T>& other);
    void push_head(const T& value);
    void push_head(const LinkedList<T>& other);
    void pop_head();
    void pop_tail();
    void delete_node(const T& value);
    const T& operator[](std::size_t index);
    T& operator[](std::size_t index);
    void clear();

private:
    // Помощник для копирования списка
    void copyFrom(const LinkedList<T>& other);
};

