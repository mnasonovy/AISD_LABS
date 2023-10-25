#include <iostream>
#include <random>
#include <stdexcept>

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
    Node<T>* head_;
    Node<T>* tail_;

public:
    LinkedList() : head_(nullptr), tail_(nullptr) {}

    LinkedList(const LinkedList<T>& other) : head_(nullptr), tail_(nullptr) {
        copyFrom(other);
    }

    LinkedList(std::size_t count, int minValue, int maxValue) : head_(nullptr), tail_(nullptr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> dist(minValue, maxValue);

        for (std::size_t i = 0; i < count; ++i) {
            T value = dist(gen);
            push_tail(value);
        }
    }

    ~LinkedList() {
        clear();
    }

    Node<T>* get_head()const {
        return head_;
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    void push_tail(const T& value) {
        Node<T>* tmp = new Node<T>(value);
        if (isEmpty()) {
            head_ = tmp;
            tail_ = tmp;
        }
        else {
            tail_->next = tmp;
            tmp->prev = tail_;
            tail_ = tmp;
        }
    }

    void push_tail(const LinkedList<T>& other) {
        Node<T>* tmp = other.head_;
        while (tmp != nullptr) {
            push_tail(tmp->data);
            tmp = tmp->next;
        }
    }

    void push_head(const T& value) {
        Node<T>* tmp = new Node<T>(value);
        if (isEmpty()) {
            head_ = tmp;
            tail_ = tmp;
        }
        else {
            tmp->next = head_;
            head_->prev = tmp;
            head_ = tmp;
        }
    }

    void push_head(const LinkedList<T>& other) {
        Node<T>* tmp = other.tail_;
        while (tmp != nullptr) {
            push_head(tmp->data);
            tmp = tmp->prev;
        }
    }

    void pop_head() {
        if (isEmpty()) {
            throw std::runtime_error("List is empty.");
        }

        Node<T>* tmp = head_;
        head_ = head_->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        }
        else {
            tail_ = nullptr;
        }
        delete tmp;
    }

    void pop_tail() {
        if (isEmpty()) {
            throw std::runtime_error("List is empty.");
        }

        Node<T>* tmp = tail_;
        tail_ = tail_->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        }
        else {
            head_ = nullptr;
        }
        delete tmp;
    }

    void delete_node(const T& value) {
        if (isEmpty()) {
            throw std::runtime_error("List is empty.");
        }

        Node<T>* tmp = head_;
        while (tmp != nullptr) {
            if (tmp->data == value) {
                if (tmp == head_) {
                    head_ = head_->next;
                    if (head_ != nullptr) {
                        head_->prev = nullptr;
                    }
                }
                else if (tmp == tail_) {
                    tail_ = tail_->prev;
                    if (tail_ != nullptr) {
                        tail_->next = nullptr;
                    }
                }
                else {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                }

                Node<T>* toDelete = tmp;
                tmp = tmp->next;
                delete toDelete;
            }
            else {
                tmp = tmp->next;
            }
        }
    }

    const T& operator[](std::size_t index) const {
        if (isEmpty()) {
            throw std::runtime_error("List is empty.");
        }

        Node<T>* current = head_;
        std::size_t i = 0;
        while (current != nullptr && i < index) {
            current = current->next;
            ++i;
        }

        if (current == nullptr) {
            throw std::out_of_range("Index out of range.");
        }

        return current->data;
    }

    T& operator[](std::size_t index) {
        if (isEmpty()) {
            throw std::runtime_error("List is empty.");
        }

        Node<T>* current = head_;
        std::size_t i = 0;
        while (current != nullptr && i < index) {
            current = current->next;
            ++i;
        }

        if (current == nullptr) {
            throw std::out_of_range("Index out of range.");
        }

        return current->data;
    }

    void clear() {
        Node<T>* current = head_;
        while (current != nullptr) {
            Node<T>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head_ = nullptr;
        tail_ = nullptr;
    }

    bool isEmpty() const {
        return head_ == nullptr && tail_ == nullptr;
    }
private:
    // Помощник для копирования списка
    void copyFrom(const LinkedList<T>& other) {
        Node<T>* otherNode = other.head_;
        while (otherNode != nullptr) {
            push_tail(otherNode->data);
            otherNode = otherNode->next;
        }
    }
};

template<typename T>
class HappyNumbers {
public:

    static T squareDigits(T num) {
        T sum = 0, rem;
        while (num > 0) {
            rem = num % 10;
            sum += (rem * rem);
            num /= 10;
        }
        return sum;
    }

    static bool isHappyNumber(T num) {
        int maxIterations = 1000; 
        int iterations = 0;

        while (true) {
            if (num == 1) {
                return true;
            }
            else if (num <= 0 || iterations >= maxIterations) {
                return false;
            }
            num = squareDigits(num);
            iterations++;
        }
    }


    static void printUnhappyNumbers(const LinkedList<T>& list) {
        if (list.isEmpty()) {
            throw std::runtime_error("List is empty.");
        }

        Node<T>* current = list.get_head();
        while (current != nullptr) {
            if (!isHappyNumber(current->data)) {
                std::cout << current->data << " ";
            }
            current = current->next;
        }
        std::cout << "\n";
    }
};

