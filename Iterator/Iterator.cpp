#include <iostream>
#include <vector>
#include <Windows.h>


template <typename T>
class Iterator {
public:
    virtual T next() = 0;
    virtual bool hasNext() const = 0;
    virtual ~Iterator() = default;
};

template <typename T>
class Aggregate {
public:
    virtual Iterator<T>* createIterator() = 0;
    virtual ~Aggregate() = default;
};


template <typename T>
class ConcreteIterator : public Iterator<T> {
private:
    typename std::vector<T>::iterator current;
    typename std::vector<T>::iterator end;

public:
    ConcreteIterator(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
        : current(begin), end(end) {}

    T next() override {
        return *(current++);
    }

    bool hasNext() const override {
        return current != end;
    }
};


template <typename T>
class ConcreteAggregate : public Aggregate<T> {
private:
    std::vector<T> elements;

public:
    void addElement(const T& element) {
        elements.push_back(element);
    }

    Iterator<T>* createIterator() override {
        return new ConcreteIterator<T>(elements.begin(), elements.end());
    }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ConcreteAggregate<int> aggregate;

    
    aggregate.addElement(1);
    aggregate.addElement(2);
    aggregate.addElement(3);

   
    Iterator<int>* iterator = aggregate.createIterator();
    while (iterator->hasNext()) {
        std::cout << iterator->next() << " ";
    }

  
    delete iterator;

    return 0;
}
