#pragma once
#include <iostream>
#include <stdexcept>
#include <limits>
#include <iterator>

template<typename T>
class Allocator {
    using value_type = T;
    using pointer = T*;
    using const_reference = const T&;

public:
    Allocator() = default;
    Allocator(Allocator&&) = default;
    Allocator& operator=(const Allocator&) = default;
    Allocator& operator=(Allocator&&) = default;
    ~Allocator() = default;

    pointer allocate(size_t n) {
        if(n == 0) {
            return nullptr;
        }
        pointer ptr = static_cast<pointer>(::operator new[](sizeof(value_type) * n));
        return ptr;
    }

    void deallocate(pointer ptr) {
        if(ptr == nullptr)
            return;
        ::operator delete[](ptr);
    }

    template<typename... Args>
    void construct(pointer ptr, Args&&... args) {
        ::new((void *)ptr) value_type(std::forward<Args>(args)...);
    }

    void destroy(pointer ptr) {
        ptr->~value_type();
    }

};

template<typename T>
class Iterator {
    using pointer = T*;
    using reference = T&;
    using value_type = T;
    using difference_type = int64_t;
    pointer ptr = nullptr;
    bool reverse = false;
public:
    Iterator() = default;

    Iterator(const Iterator&) = default;

    Iterator(pointer ptr, bool rev = false) : ptr(ptr), reverse(rev) {}

    Iterator& operator=(const Iterator&) = default;

    ~Iterator() = default;

    reference operator*() { return *ptr;}

    Iterator& operator++() {
        reverse ? --ptr : ++ptr;
        return *this;
    }

    Iterator operator++(int) {
        Iterator it = (*this);
        reverse ? --ptr : ++ptr;
        return it;
    }

    Iterator& operator--() {
        reverse ? ++ptr : --ptr;
        return *this;
    }

    Iterator operator--(int) {
        Iterator it = (*this);
        reverse ? ++ptr : --ptr;
        return it;
    }

    reference operator[](const difference_type dif) { return *((*this) + dif); }

    Iterator& operator+=(const difference_type dif) {
        difference_type m = dif;
        if (m >= 0) {
            while(m--) 
                reverse ? --ptr : ++ptr;
        }
        else
            while(m++)
                reverse ? ++ptr : --ptr;
        return *this;
    }

    Iterator& operator-=(const difference_type dif) { return operator+=(-dif); }

    Iterator operator+(int64_t n) const { Iterator it = (*this); return (it += n); }

    friend Iterator operator+(int64_t n, const Iterator& a) {
        Iterator it = a;
        return (it += n);
    }

    Iterator operator-(int64_t n) const { Iterator it = (*this); return (it -= n); }

    difference_type operator-(const Iterator& a) const {
        Iterator it = a;
        if( reverse != it.reverse)
            throw std::logic_error("Subtraction of differrent types of iterators!");
        int64_t n = 0;
        if(a == (*this))
            return n;
        return (ptr - a.ptr);
    }

    bool operator<(const Iterator& a) const {
        if(reverse != a.reverse)
            throw std::logic_error("Comparing of different types of iterators!");
        return ((*this) - a > 0);
    }

    bool operator>(const Iterator& a) const { return (a < (*this)); }

    bool operator<=(const Iterator& a) const { return !((*this) > a); }

    bool operator>=(const Iterator& a) const { return !((*this) < a); }

    bool operator==(const Iterator& a) const { return (ptr == a.ptr) && (reverse == a.reverse); }

    bool operator!=(const Iterator& a) const { return !((*this) == a); }
};

template<typename T, typename Alloc = Allocator<T>>
class Vector {
public:
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using allocator_type = Alloc;
    using iterator = Iterator<T>;
    using value_type = T;
private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    pointer ptr = nullptr;
    allocator_type allocator;
public:
    Vector() {
        allocator = allocator_type();
        capacity_ = 2;
        ptr = allocator.allocate(capacity_);
    }

    explicit Vector(size_t count) {
        size_ = count;
        capacity_ = 2 * size_;
        allocator = allocator_type();
        ptr = allocator.allocate(capacity_);
        for(size_t i = 0; i < size_; ++i)
            allocator.construct(ptr + i, value_type());
    }

    Vector(size_t count, const_reference value) {
        size_ = count;
        capacity_ = 2 * size_;
        allocator = allocator_type();
        ptr = allocator.allocate(capacity_);
        for(size_t i = 0; i < size_; ++i)
            allocator.construct(ptr + i, value);
    }

    ~Vector() {
        if (ptr != nullptr) {
            for(size_t i = 0; i < size_; ++i)
                allocator.destroy(ptr + i);
            allocator.deallocate(ptr);
        }
    }

    Vector(const Vector& a) {
        size_ = a.size_;
        capacity_ = a.capacity_;
        allocator = a.allocator;
        ptr = allocator.allocate(capacity_);
        for(size_t i = 0; i < a.size_; ++i) {
            allocator.construct(ptr + i, *(a.ptr + i));
        }
    }

    Vector( Vector&& a) noexcept : size_(std::move(a.size_)), capacity_(std::move(a.capacity_)), allocator(std::move(a.allocator)) {
        ptr = a.ptr;
        a.ptr = nullptr;
        a.size_ = 0;
    }

    Vector& operator=(Vector&& a) {
        if(this == &a)
            return (*this);
        for(size_t i = 0; i < size_; ++i) {
            allocator.destroy(ptr + i);
        }
        allocator.deallocate(ptr);
        size_ = std::move(a.size_);
        capacity_ = a.capacity_;
        allocator = std::move(a.allocator);
        ptr = a.ptr;
        a.ptr = nullptr;
        a.size_ = 0;
        return (*this);
    }

    Vector& operator=(const Vector& a) {
        if((*this) == a)
            return (*this);
        for(size_t i = 0; i < size_; ++i)
            allocator.destroy(ptr + i);
        allocator.deallocate(ptr);
        allocator = a.allocator;
        size_ = a.size_;
        capacity_ = a.capacity_;
        ptr = allocator.allocate(capacity_);
        for(size_t i =0; i < size_; ++i)
            allocator.construct(ptr + i, *(a.ptr + i));
        return (*this);
    }

    reference operator[](size_t pos) { return *(ptr + pos); }

    const_reference operator[](size_t pos) const { return *(ptr + pos); }

    void push_back(const_reference a) {
        if(size_ == capacity_)
            reserve(2 * capacity_);
        allocator.construct((ptr + (size_++)), a);
    }

    void push_back(value_type&& a) {
        if(size_ == capacity_)
            reserve(2 * capacity_);
        allocator.construct((ptr + (size_++)), std::forward<value_type>(a));
    }

    void pop_back() {
        if(size_ == 0)
            throw std::out_of_range("Pop back on an empty vector!");
        allocator.destroy(ptr + (--size_));
    }

    template<typename... Args>
    reference emplace_back(Args&&... args) {
        if(size_ == capacity_)
            reserve(2 * capacity_);
        allocator.construct((ptr + (size_++)), std::forward<Args>(args)...);
        return *(ptr + size_ - 1);
    }

    void reserve(size_t new_cap) {
        if(new_cap <= capacity_)
            return;
        pointer tmp = allocator.allocate(new_cap);
        for(size_t i = 0; i < size_; ++i)
            allocator.construct(tmp + i, std::move(*(ptr + i)));
        for(size_t i = 0; i < size_; ++i)
            allocator.destroy(ptr + i);
        allocator.deallocate(ptr);
        ptr = tmp;
        capacity_ = new_cap;
    }

    void resize(size_t count, const_reference value) {
        if(count <= size_) {
            size_ = count;
            return;
        }
        if(capacity_ < count)
            reserve(2 * count);
        for(size_t i = size_; i < count; ++i)
            allocator.construct(ptr + i, value);
        size_ = count;
    }

    void resize(size_t count) {
        if(count <= size_) {
            size_ = count;
            return;
        }
        if(capacity_ < count)
            reserve(2 * count);
        for(size_t i = size_; i < count; ++i)
            allocator.construct(ptr + i, value_type());
        size_ = count;
    }

    void clear() noexcept {
        for(size_t i = 0; i < size_; ++i)
            allocator.destroy(ptr + i);
        size_ = 0;
    }

    iterator begin() noexcept {
        return iterator(ptr);
    }

    iterator rbegin() noexcept {
        return iterator(ptr + size_ - 1, true);
    }

    iterator end() noexcept {
        return iterator(ptr + size_);
    }

    iterator rend() noexcept {
        return iterator(ptr - 1, true);
    }

    size_t size() const noexcept { return size_; }

    size_t capacity() const noexcept { return capacity_; }

    bool empty() const noexcept { return size_ == 0; }
};