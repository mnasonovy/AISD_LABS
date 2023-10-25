#include <iostream>
#include <random>
#include <stdexcept>


template<typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    explicit Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template<typename T>
class LinkedList {
public:
    LinkedList()
        : head_(nullptr), tail_(nullptr) {}

    explicit LinkedList(const LinkedList<T>& other)
        : head_(nullptr), tail_(nullptr) {
        CopyFrom(other);
    }

    LinkedList(std::size_t count, int min_value, int max_value)
        : head_(nullptr), tail_(nullptr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> dist(min_value, max_value);
        for (std::size_t i = 0; i < count; ++i) {
            T value = dist(gen);
            PushTail(value);
        }
    }

    ~LinkedList() {
        Clear();
    }

    Node<T>* GetHead() const {
        return head_;
    }

   
    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            Clear();
            CopyFrom(other);
        }
        return *this;
    }

    void PushTail(const T& value) {
        Node<T>* temp = new Node<T>(value);
        if (IsEmpty()) {
            head_ = temp;
            tail_ = temp;
        }
        else {
            tail_->next = temp;
            temp->prev = tail_;
            tail_ = temp;
        }
    }

    void PushTail(const LinkedList<T>& other) {
        Node<T>* temp = other.head_;
        while (temp != nullptr) {
            PushTail(temp->data);
            temp = temp->next;
        }
    }

    void PushHead(const T& value) {
        Node<T>* temp = new Node<T>(value);
        if (IsEmpty()) {
            head_ = temp;
            tail_ = temp;
        }
        else {
            temp->next = head_;
            head_->prev = temp;
            head_ = temp;
        }
    }

    void PushHead(const LinkedList<T>& other) {
        Node<T>* temp = other.tail_;
        while (temp != nullptr) {
            PushHead(temp->data);
            temp = temp->prev;
        }
    }

    void PopHead() {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* temp = head_;
        head_ = head_->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        }
        else {
            tail_ = nullptr;
        }
        delete temp;
    }

    void PopTail() {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* temp = tail_;
        tail_ = tail_->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        }
        else {
            head_ = nullptr;
        }
        delete temp;
    }

    void DeleteNode(const T& value) {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* temp = head_;
        while (temp != nullptr) {
            if (temp->data == value) {
                if (temp == head_) {
                    head_ = head_->next;
                    if (head_ != nullptr) {
                        head_->prev = nullptr;
                    }
                }
                else if (temp == tail_) {
                    tail_ = tail_->prev;
                    if (tail_ != nullptr) {
                        tail_->next = nullptr;
                    }
                }
                else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }
                Node<T>* node_to_delete = temp;
                temp = temp->next;
                delete node_to_delete;
            }
            else {
                temp = temp->next;
            }
        }
    }

    const T& operator[](std::size_t index) const {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* current = head_;
        std::size_t iter = 0;
        while (current != nullptr && iter < index) {
            current = current->next;
            ++iter;
        }
        if (current == nullptr) {
            throw std::out_of_range("Index out of range.");
        }
        return current->data;
    }

    T& operator[](std::size_t index) {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* current = head_;
        std::size_t iter = 0;
        while (current != nullptr && iter < index) {
            current = current->next;
            ++iter;
        }
        if (current == nullptr) {
            throw std::out_of_range("Index out of range.");
        }
        return current->data;
    }

    void Clear() {
        Node<T>* current = head_;
        while (current != nullptr) {
            Node<T>* node_to_delete = current;
            current = current->next;
            delete node_to_delete;
        }
        head_ = nullptr;
        tail_ = nullptr;
    }

    bool IsEmpty() const {
        return head_ == nullptr && tail_ == nullptr;
    }

private:
    // Helper for copying the list.
    void CopyFrom(const LinkedList<T>& other) {
        Node<T>* temp = other.head_;
        while (temp != nullptr) {
            PushTail(temp->data);
            temp = temp->next;
        }
    }

private:
    Node<T>* head_;
    Node<T>* tail_;
};

// Template class HappyNumbers.
template<typename T>
class HappyNumbers {
public:
    static T SquareDigits(T num) {
        T sum = 0, rem;
        while (num > 0) {
            rem = num % 10;
            sum += (rem * rem);
            num /= 10;
        }
        return sum;
    }

    static bool IsHappyNumber(T num) {
        int max_iterations = 1000;
        int iterations = 0;

        while (true) {
            if (num == 1) {
                return true;
            }
            if (num <= 0 || iterations >= max_iterations) {
                return false;
            }
            num = SquareDigits(num);
            ++iterations;
        }
    }

    static void PrintUnhappyNumbers(const LinkedList<T>& list) {
        if (list.IsEmpty()) {
            throw std::runtime_error("List is empty.");
        }
        Node<T>* current = list.GetHead();
        while (current != nullptr) {
            if (!IsHappyNumber(current->data)) {
                std::cout << current->data << " ";
            }
            current = current->next;
        }
        std::cout << "\n";
    }
};