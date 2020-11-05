#include "BigInt.hpp"

BigInt::BigInt() : _data(nullptr), size(0), minus(false) {}

BigInt::BigInt(const int& a) {
    std::string str = std::to_string(a);
    size = str.size();
    _data = new char[size + 1];
    minus = a < 0 ? true : false;
    if (!minus) {
        for (size_t i = 0; i < size; ++i)
            _data[i] = str[i];
        _data[size] = '\0';
    }
    else {
        --size;
        for (size_t i = 0; i < size; ++i)
            _data[i] = str[i + 1];
        _data[size] = '\0';
    }
    SearchZero(*this);
}

BigInt::BigInt(const std::string& str) {
    if (str[0] != '-') {
        size = str.size();
        _data = new char[size + 1];
        for (size_t i = 0; i < size; ++i)
            _data[i] = str[i];
        minus = false;
    }
    else {
        size = str.size() - 1;
        _data = new char[size + 1];
        minus = true;
        for (size_t i = 0; i < size; ++i)
            _data[i] = str[i + 1];
    }
    _data[size] = '\0';
    SearchZero(*this);
}

BigInt::~BigInt() {
    if(_data)
        delete[] _data;
}

BigInt::BigInt(const BigInt& a) {
    _data = new char[a.size + 1];
    for (size_t i = 0; i <= a.size; ++i)
        _data[i] = a._data[i];
    size = a.size;
    minus = a.minus;
}

BigInt& BigInt::operator=(const BigInt& a) {
    size = 0;
    if (_data) {
        delete[] _data;
        _data = nullptr;
    }
    _data = new char[a.size + 1];
    for (size_t i = 0; i <= a.size; ++i)
        _data[i] = a._data[i];
    size = a.size;
    minus = a.minus;
    return *this;
}

void BigInt::SearchZero(BigInt& a) {
    size_t n = 0;
    for (size_t i = 0; i < a.size; ++i) {
        if (a._data[i] == '0') {
            ++n;
            continue;
        }
        break;
    }
    if (a.size != n) {
        char* ptr = new char[a.size - n + 1];
        for (size_t i = n; i <= a.size; ++i)
            ptr[i - n] = a._data[i];
        delete[] a._data;
        a._data = ptr;
        a.size -= n;
    }
    else {
        a.size = 1;
        delete[] a._data;
        a._data = new char[2];
        a._data[0] = '0';
        a._data[1] = '\0';
        a.minus = false;
    }
    return;
}

BigInt BigInt::operator+(const BigInt& a) {
    BigInt tmp;
    int term1, term2;
    bool per = false;
    if ((minus && a.minus) || (!minus && !a.minus)) {
        if (minus && a.minus)
            tmp.minus = true;
        else
            tmp.minus = false;
        if (size == a.size) {
            tmp.size = size;
            tmp._data = new char[size + 1];
            for (size_t i = size - 1; i > 0; --i) {
                term1 = _data[i] - '0';
                term2 = a._data[i] - '0';
                if (per) {
                    ++term1;
                    per = false;
                }
                if (term1 + term2 > 9) {
                    per = true;
                    tmp._data[i] = '0' + (term1 + term2) % 10;
                }
                else
                    tmp._data[i] = '0' + term1 + term2;
            }
            term1 = _data[0] - '0';
            term2 = a._data[0] - '0';
            if (per) {
                ++term1;
            }
            if (term1 + term2 > 9) {
                tmp._data[0] = '0' + (term1 + term2) % 10;
                tmp._data[size] = '\0';
                ++tmp.size;
                char* point = new char[tmp.size + 1];
                strcpy_s(point + 1, tmp.size, tmp._data);
                point[0] = '1';
                delete[] tmp._data;
                tmp._data = point;
                return tmp;
            }
            else {
                tmp._data[0] = '0' + term1 + term2;
                tmp._data[size] = '\0';
                return tmp;
            }
        }
        else {
            size_t min, max;
            char* ptr1, * ptr2;
            if (size > a.size) {
                min = a.size;
                max = size;
                ptr1 = _data;
                ptr2 = a._data;
            }
            else {
                min = size;
                max = a.size;
                ptr1 = a._data;
                ptr2 = _data;
            }
            tmp.size = max;
            tmp._data = new char[max + 1];
            for (size_t i = max - 1, j = min - 1; j > 0; --i, --j) {
                term1 = ptr1[i] - '0';
                term2 = ptr2[j] - '0';
                if (per) {
                    ++term1;
                    per = false;
                }
                if (term1 + term2 > 9) {
                    per = true;
                    tmp._data[i] = '0' + (term1 + term2) % 10;
                }
                else
                    tmp._data[i] = '0' + term1 + term2;
            }
            term1 = ptr1[max - min] - '0';
            term2 = ptr2[0] - '0';
            if (per) {
                ++term1;
            }
            if (term1 + term2 > 9) {
                tmp._data[max - min] = '0' + (term1 + term2) % 10;
                per = true;
            }
            else {
                tmp._data[max - min] = '0' + term1 + term2;
                per = false;
            }
            for (size_t i = max - min - 1; i > 0; --i) {
                term1 = ptr1[i] - '0';
                if (per)
                    ++term1;
                if (term1 == 10) {
                    per = true;
                    tmp._data[i] = '0';
                }
                else {
                    per = false;
                    tmp._data[i] = '0' + term1;
                }
            }
            tmp._data[max] = '\0';
            if (per) {
                tmp._data[0] = '0' + (ptr1[0] - '0' + 1) % 10;
                ++tmp.size;
                char* point = new char[tmp.size + 1];
                strcpy_s(point + 1, tmp.size, tmp._data);
                point[0] = '1';
                delete[] tmp._data;
                tmp._data = point;
            }
            else
                tmp._data[0] = ptr1[0];
            return tmp;
        }
    }
    else {
        if (minus) {
            BigInt tmp1 = a, tmp2 = *this;
            tmp2.minus = false;
            return tmp1 - tmp2;
        }
        else {
            BigInt tmp1 = a, tmp2 = (*this);
            tmp1.minus = false;
            return tmp2 - tmp1;
        }
    }
}

BigInt BigInt::operator-(const BigInt& a) {
    if (!minus && !a.minus) {
        BigInt tmp;
        int term1, term2;
        bool per = false;
        if (size == a.size) {
            tmp.size = size;
            tmp._data = new char[size + 1];
            for (size_t i = size - 1; i > 0; --i) {
                term1 = _data[i] - '0';
                term2 = a._data[i] - '0';
                if (per) {
                    --term1;
                    per = false;
                }
                if (term1 - term2 < 0) {
                    per = true;
                    tmp._data[i] = '0' - term1 + term2;
                }
                else
                    tmp._data[i] = '0' + term1 - term2;
            }
            term1 = _data[0] - '0';
            term2 = a._data[0] - '0';
            if (per) {
                --term1;
            }
            if (term1 - term2 < 0) {
                tmp._data[0] = '0' - term1 + term2;
                tmp._data[size] = '\0';
                tmp.minus = true;
                SearchZero(tmp);
                return tmp;
            }
            else {
                tmp._data[0] = '0' + term1 - term2;
                tmp._data[size] = '\0';
                if(tmp._data[0] == '0'){
                    --tmp.size;
                    char* ptr = new char[tmp.size + 1];
                    for (size_t i = 0; i <= tmp.size; ++i)
                        ptr[i] = tmp._data[i + 1];
                    delete[] tmp._data;
                    tmp._data = ptr;
                }
                tmp.minus = false;
                SearchZero(tmp);
                return tmp;
            }
        }
        else {
            size_t min, max;
            char* ptr1, * ptr2;
            if (size > a.size) {
                min = a.size;
                max = size;
                ptr1 = _data;
                ptr2 = a._data;
                tmp.minus = false;
            }
            else {
                min = size;
                max = a.size;
                ptr1 = a._data;
                ptr2 = _data;
                tmp.minus = true;
            }
            tmp.size = max;
            tmp._data = new char[max + 1];
            for (size_t i = max - 1, j = min - 1; j > 0; --i, --j) {
                term1 = ptr1[i] - '0';
                term2 = ptr2[j] - '0';
                if (per) {
                    --term1;
                    per = false;
                }
                if (term1 - term2 < 0) {
                    per = true;
                    tmp._data[i] = '0' - term1 + term2;
                }
                else
                    tmp._data[i] = '0' + term1 - term2;
            }
            term1 = ptr1[max - min] - '0';
            term2 = ptr2[0] - '0';
            if (per) {
                --term1;
            }
            if (term1 - term2 < 0) {
                tmp._data[max - min] = '0' - term1 + term2;
                per = true;
            }
            else {
                tmp._data[max - min] = '0' + term1 - term2;
                per = false;
            }
            for (size_t i = max - min - 1; i > 0; --i) {
                term1 = ptr1[i] - '0';
                if (per)
                    --term1;
                if (term1 == -1) {
                    per = true;
                    tmp._data[i] = term1;
                }
                else {
                    per = false;
                    tmp._data[i] = '0' + term1;
                }
            }
            tmp._data[max] = '\0';
            if (per) {
                tmp._data[0] = '0' + (ptr1[0] - '0' - 1);
                if (tmp._data[0] == '0') {
                    --tmp.size;
                    char* point = new char[tmp.size + 1];
                    strcpy_s(point, tmp.size, tmp._data + 1);
                    delete[] tmp._data;
                    tmp._data = point;
                }
            }
            else
                tmp._data[0] = ptr1[0];
            SearchZero(tmp);
            return tmp;
        }
    }
    else if (minus && !a.minus) {
        BigInt tmp1 = a, tmp2 = (*this);
        tmp1.minus = true;
        BigInt tmp = tmp1 + tmp2;
        SearchZero(tmp);
        return tmp;
    }
    else if (!minus && a.minus) {
        BigInt tmp1 = *this, tmp2 = a;
        tmp2.minus = false;
        return tmp1 + tmp2;
    }
    else {
        BigInt tmp1 = a, tmp2 = *this;
        tmp1.minus = false;
        tmp2.minus = false;
        BigInt tmp = tmp1 - tmp2;
        SearchZero(tmp);
        return tmp;
    }
}

BigInt BigInt::operator+(const BigInt& a) const {
    BigInt tmp;
    int term1, term2;
    bool per = false;
    if ((minus && a.minus) || (!minus && !a.minus)) {
        if (minus && a.minus)
            tmp.minus = true;
        else
            tmp.minus = false;
        if (size == a.size) {
            tmp.size = size;
            tmp._data = new char[size + 1];
            for (size_t i = size - 1; i > 0; --i) {
                term1 = _data[i] - '0';
                term2 = a._data[i] - '0';
                if (per) {
                    ++term1;
                    per = false;
                }
                if (term1 + term2 > 9) {
                    per = true;
                    tmp._data[i] = '0' + (term1 + term2) % 10;
                }
                else
                    tmp._data[i] = '0' + term1 + term2;
            }
            term1 = _data[0] - '0';
            term2 = a._data[0] - '0';
            if (per) {
                ++term1;
            }
            if (term1 + term2 > 9) {
                tmp._data[0] = '0' + (term1 + term2) % 10;
                tmp._data[size] = '\0';
                ++tmp.size;
                char* point = new char[tmp.size + 1];
                strcpy_s(point + 1, tmp.size, tmp._data);
                point[0] = '1';
                delete[] tmp._data;
                tmp._data = point;
                return tmp;
            }
            else {
                tmp._data[0] = '0' + term1 + term2;
                tmp._data[size] = '\0';
                return tmp;
            }
        }
        else {
            size_t min, max;
            char* ptr1, * ptr2;
            if (size > a.size) {
                min = a.size;
                max = size;
                ptr1 = _data;
                ptr2 = a._data;
            }
            else {
                min = size;
                max = a.size;
                ptr1 = a._data;
                ptr2 = _data;
            }
            tmp.size = max;
            tmp._data = new char[max + 1];
            for (size_t i = max - 1, j = min - 1; j > 0; --i, --j) {
                term1 = ptr1[i] - '0';
                term2 = ptr2[j] - '0';
                if (per) {
                    ++term1;
                    per = false;
                }
                if (term1 + term2 > 9) {
                    per = true;
                    tmp._data[i] = '0' + (term1 + term2) % 10;
                }
                else
                    tmp._data[i] = '0' + term1 + term2;
            }
            term1 = ptr1[max - min] - '0';
            term2 = ptr2[0] - '0';
            if (per) {
                ++term1;
            }
            if (term1 + term2 > 9) {
                tmp._data[max - min] = '0' + (term1 + term2) % 10;
                per = true;
            }
            else {
                tmp._data[max - min] = '0' + term1 + term2;
                per = false;
            }
            for (size_t i = max - min - 1; i > 0; --i) {
                term1 = ptr1[i] - '0';
                if (per)
                    ++term1;
                if (term1 == 10) {
                    per = true;
                    tmp._data[i] = '0';
                }
                else {
                    per = false;
                    tmp._data[i] = '0' + term1;
                }
            }
            tmp._data[max] = '\0';
            if (per) {
                tmp._data[0] = '0' + (ptr1[0] - '0' + 1) % 10;
                ++tmp.size;
                char* point = new char[tmp.size + 1];
                strcpy_s(point + 1, tmp.size, tmp._data);
                point[0] = '1';
                delete[] tmp._data;
                tmp._data = point;
            }
            else
                tmp._data[0] = ptr1[0];
            return tmp;
        }
    }
    else {
        if (minus) {
            BigInt tmp1 = a, tmp2 = *this;
            tmp2.minus = false;
            return tmp1 - tmp2;
        }
        else {
            BigInt tmp1 = a, tmp2 = (*this);
            tmp1.minus = false;
            return tmp2 - tmp1;
        }
    }
}

BigInt BigInt::operator-(const BigInt& a) const {
    if (!minus && !a.minus) {
        BigInt tmp;
        int term1, term2;
        bool per = false;
        if (size == a.size) {
            tmp.size = size;
            tmp._data = new char[size + 1];
            for (size_t i = size - 1; i > 0; --i) {
                term1 = _data[i] - '0';
                term2 = a._data[i] - '0';
                if (per) {
                    --term1;
                    per = false;
                }
                if (term1 - term2 < 0) {
                    per = true;
                    tmp._data[i] = '0' - term1 + term2;
                }
                else
                    tmp._data[i] = '0' + term1 - term2;
            }
            term1 = _data[0] - '0';
            term2 = a._data[0] - '0';
            if (per) {
                --term1;
            }
            if (term1 - term2 < 0) {
                tmp._data[0] = '0' - term1 + term2;
                tmp._data[size] = '\0';
                tmp.minus = true;
                size_t n = 0;
                for (size_t i = 0; i < tmp.size; ++i) {
                    if (tmp._data[i] == '0') {
                        ++n;
                        continue;
                    }
                    break;
                }
                if (tmp.size != n) {
                    char* ptr = new char[tmp.size - n + 1];
                    for (size_t i = n; i <= tmp.size; ++i)
                        ptr[i - n] = tmp._data[i];
                    delete[] tmp._data;
                    tmp._data = ptr;
                    tmp.size -= n;
                }
                else {
                    tmp.size = 1;
                    delete[] tmp._data;
                    tmp._data = new char[2];
                    tmp._data[0] = '0';
                    tmp._data[1] = '\0';
                    tmp.minus = false;
                }
                return tmp;
            }
            else {
                tmp._data[0] = '0' + term1 - term2;
                tmp._data[size] = '\0';
                if (tmp._data[0] == '0') {
                    --tmp.size;
                    char* ptr = new char[tmp.size + 1];
                    for (size_t i = 0; i <= tmp.size; ++i)
                        ptr[i] = tmp._data[i + 1];
                    delete[] tmp._data;
                    tmp._data = ptr;
                }
                tmp.minus = false;
                size_t n = 0;
                for (size_t i = 0; i < tmp.size; ++i) {
                    if (tmp._data[i] == '0') {
                        ++n;
                        continue;
                    }
                    break;
                }
                if (tmp.size != n) {
                    char* ptr = new char[tmp.size - n + 1];
                    for (size_t i = n; i <= tmp.size; ++i)
                        ptr[i - n] = tmp._data[i];
                    delete[] tmp._data;
                    tmp._data = ptr;
                    tmp.size -= n;
                }
                else {
                    tmp.size = 1;
                    delete[] tmp._data;
                    tmp._data = new char[2];
                    tmp._data[0] = '0';
                    tmp._data[1] = '\0';
                    tmp.minus = false;
                }
                return tmp;
            }
        }
        else {
            size_t min, max;
            char* ptr1, * ptr2;
            if (size > a.size) {
                min = a.size;
                max = size;
                ptr1 = _data;
                ptr2 = a._data;
                tmp.minus = false;
            }
            else {
                min = size;
                max = a.size;
                ptr1 = a._data;
                ptr2 = _data;
                tmp.minus = true;
            }
            tmp.size = max;
            tmp._data = new char[max + 1];
            for (size_t i = max - 1, j = min - 1; j > 0; --i, --j) {
                term1 = ptr1[i] - '0';
                term2 = ptr2[j] - '0';
                if (per) {
                    --term1;
                    per = false;
                }
                if (term1 - term2 < 0) {
                    per = true;
                    tmp._data[i] = '0' - term1 + term2;
                }
                else
                    tmp._data[i] = '0' + term1 - term2;
            }
            term1 = ptr1[max - min] - '0';
            term2 = ptr2[0] - '0';
            if (per) {
                --term1;
            }
            if (term1 - term2 < 0) {
                tmp._data[max - min] = '0' - term1 + term2;
                per = true;
            }
            else {
                tmp._data[max - min] = '0' + term1 - term2;
                per = false;
            }
            for (size_t i = max - min - 1; i > 0; --i) {
                term1 = ptr1[i] - '0';
                if (per)
                    --term1;
                if (term1 == -1) {
                    per = true;
                    tmp._data[i] = term1;
                }
                else {
                    per = false;
                    tmp._data[i] = '0' + term1;
                }
            }
            tmp._data[max] = '\0';
            if (per) {
                tmp._data[0] = '0' + (ptr1[0] - '0' - 1);
                if (tmp._data[0] == '0') {
                    --tmp.size;
                    char* point = new char[tmp.size + 1];
                    strcpy_s(point, tmp.size, tmp._data + 1);
                    delete[] tmp._data;
                    tmp._data = point;
                }
            }
            else
                tmp._data[0] = ptr1[0];
            size_t n = 0;
            for (size_t i = 0; i < tmp.size; ++i) {
                if (tmp._data[i] == '0') {
                    ++n;
                    continue;
                }
                break;
            }
            if (tmp.size != n) {
                char* ptr = new char[tmp.size - n + 1];
                for (size_t i = n; i <= tmp.size; ++i)
                    ptr[i - n] = tmp._data[i];
                delete[] tmp._data;
                tmp._data = ptr;
                tmp.size -= n;
            }
            else {
                tmp.size = 1;
                delete[] tmp._data;
                tmp._data = new char[2];
                tmp._data[0] = '0';
                tmp._data[1] = '\0';
                tmp.minus = false;
            }
            return tmp;
        }
    }
    else if (minus && !a.minus) {
        BigInt tmp1 = a, tmp2 = (*this);
        tmp2.minus = true;
        BigInt tmp = tmp1 + tmp2;
        size_t n = 0;
        for (size_t i = 0; i < tmp.size; ++i) {
            if (tmp._data[i] == '0') {
                ++n;
                continue;
            }
            break;
        }
        if (tmp.size != n) {
            char* ptr = new char[tmp.size - n + 1];
            for (size_t i = n; i <= tmp.size; ++i)
                ptr[i - n] = tmp._data[i];
            delete[] tmp._data;
            tmp._data = ptr;
            tmp.size -= n;
        }
        else {
            tmp.size = 1;
            delete[] tmp._data;
            tmp._data = new char[2];
            tmp._data[0] = '0';
            tmp._data[1] = '\0';
            tmp.minus = false;
        }
        return tmp;
    }
    else if (!minus && a.minus) {
        BigInt tmp1 = *this, tmp2 = a;
        tmp2.minus = false;
        return tmp1 + tmp2;
    }
    else {
        BigInt tmp1 = a, tmp2 = *this;
        tmp1.minus = false;
        tmp2.minus = false;
        BigInt tmp = tmp1 - tmp2;
        size_t n = 0;
        for (size_t i = 0; i < tmp.size; ++i) {
            if (tmp._data[i] == '0') {
                ++n;
                continue;
            }
            break;
        }
        if (tmp.size != n) {
            char* ptr = new char[tmp.size - n + 1];
            for (size_t i = n; i <= tmp.size; ++i)
                ptr[i - n] = tmp._data[i];
            delete[] tmp._data;
            tmp._data = ptr;
            tmp.size -= n;
        }
        else {
            tmp.size = 1;
            delete[] tmp._data;
            tmp._data = new char[2];
            tmp._data[0] = '0';
            tmp._data[1] = '\0';
            tmp.minus = false;
        }
        return tmp;
    }
}

BigInt BigInt::operator*(const BigInt& a) {
    BigInt tmp, tmp1;
    std::string help("0");
    tmp.size = size * a.size;
    tmp1.size = tmp.size;
    tmp._data = new char[tmp.size + 1];
    tmp1._data = new char[tmp1.size + 1];
    for (size_t i = 0; i < tmp.size; ++i) {
        tmp._data[i] = '0';
        tmp1._data[i] = '0';
    }
    tmp._data[tmp.size] = '\0';
    tmp1._data[tmp1.size] = '\0';
    tmp.minus = false;
    tmp1.minus = false;
    if (size > a.size) {
        for (size_t i = 0; i < size; ++i)
            help = help + _data[i];
        for (size_t i = a.size - 1; i > 0; --i) {
            BigInt help1(help);
            for(int j = 0; j < (a._data[i] - '0'); ++j)
                tmp = tmp + help1;
            help = help + '0';
        }
        BigInt help1(help);
        for (int j = 0; j < (a._data[0] - '0'); ++j)
            tmp = tmp + help1;
    }
    else {
        for (size_t i = 0; i < a.size; ++i)
            help = help + a._data[i];
        for (size_t i = size - 1; i > 0; --i) {
            BigInt help1(help);
            for (int j = 0; j < (_data[i] - '0'); ++j)
                tmp = tmp + help1;
            help = help + '0';
        }
        BigInt help1(help);
        for (int j = 0; j < (_data[0] - '0'); ++j)
            tmp = tmp + help1;
    }
    if ((a.minus && minus) || (!a.minus && !minus))
        tmp.minus = false;
    else
        tmp.minus = true;
    size_t n = 0;
    for (size_t i = 0; i < tmp.size; ++i) {
        if (tmp._data[i] == '0') {
            ++n;
            continue;
        }
        break;
    }
    if (tmp.size != n) {
        char* ptr = new char[tmp.size - n + 1];
        for (size_t i = n; i <= tmp.size; ++i)
            ptr[i - n] = tmp._data[i];
        delete[] tmp._data;
        tmp._data = ptr;
        tmp.size -= n;
    }
    else {
        tmp.size = 1;
        delete[] tmp._data;
        tmp._data = new char[2];
        tmp._data[0] = '0';
        tmp._data[1] = '\0';
        tmp.minus = false;
    }
    return tmp;
}

BigInt BigInt::operator-() const {
    BigInt tmp = (*this);
    tmp.minus = !tmp.minus;
    return tmp;
}

bool BigInt::operator<(const BigInt& a) const {
    if (minus && !a.minus)
        return true;
    else if (!minus && a.minus)
        return false;
    else if (minus && a.minus) {
        if (size > a.size)
            return true;
        else if (size < a.size)
            return false;
        else {
            for (size_t i = 0; i < size; ++i) {
                if (_data[i] > a._data[i])
                    return true;
                else if (_data[i] < a._data[i])
                    return false;
            }
            return false;
        }
    }
    else {
        if (size > a.size)
            return false;
        else if (size < a.size)
            return true;
        else {
            for (size_t i = 0; i < size; ++i) {
                if (_data[i] > a._data[i])
                    return false;
                else if (_data[i] < a._data[i])
                    return true;
            }
            return false;
        }
    }
}

bool BigInt::operator>(const BigInt& a) const {
    return (a < (*this));
}

bool BigInt::operator!=(const BigInt& a) const {
    return (((*this) > a)||((*this) < a));
}

bool BigInt::operator==(const BigInt& a) const {
    return (!((*this) != a));
}

bool BigInt::operator<=(const BigInt& a) const {
    return ((*this) < a) || ((*this) == a);
}

bool BigInt::operator>=(const BigInt& a) const {
    return ((*this) > a) || ((*this) == a);
}

std::ostream& operator<<(std::ostream& s, const BigInt& a) {
    if (!a.minus)
        return s << a._data;
    else
        return s << '-' << a._data;
}

size_t BigInt::len() const { return size; }

int main()
{
    BigInt a("11");
    BigInt b("-11");
    std::cout << (b * a) << std::endl;
}