#include <iostream>
#include <windows.h>
using namespace std;

class Array {
    unsigned int capacity = 10;
    int* data = new int[capacity];
    unsigned int length = 0;

public:
    Array() {}

    Array(const string& str) {
        int value = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                value = value * 10 + (str[i] - '0');
            }
            else if (str[i] == ' ') {
                *this += value;
                value = 0;
            }
        }
        *this += value;
    }

    Array(const Array& original) {
        this->length = original.length;
        this->capacity = original.capacity;
        this->data = new int[capacity];
        for (int i = 0; i < length; i++)
            this->data[i] = original.data[i];
    }

    ~Array() {
        if (data != nullptr) delete[] data;
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;
        delete[] data;
        capacity = other.capacity;
        length = other.length;
        data = new int[capacity];
        for (int i = 0; i < length; i++)
            data[i] = other.data[i];
        return *this;
    }

    void AddToBack(int value) {
        if (length >= capacity) {
            capacity *= 2;
            int* temp = new int[capacity];
            for (int i = 0; i < length; i++) temp[i] = data[i];
            delete[] data;
            data = temp;
        }
        data[length++] = value;
    }

    void RemoveByValue(int value) {
        int newLength = 0;
        for (int i = 0; i < length; i++) {
            if (data[i] != value) data[newLength++] = data[i];
        }
        length = newLength;
    }

    int& operator[](int index) {
        return data[index];
    }

    const int& operator[](int index) const {
        return data[index];
    }

    string ToString() const {
        string result = "";
        for (int i = 0; i < length; i++) {
            int num = data[i];
            string temp = "";
            if (num == 0) temp = "0";
            while (num > 0) {
                char digit = '0' + (num % 10);
                temp = digit + temp;
                num /= 10;
            }
            result += temp + " ";
        }
        return result;
    }

    operator string() const {
        return ToString();
    }

    bool operator==(const Array& other) const {
        if (length != other.length) return false;
        for (int i = 0; i < length; i++)
            if (data[i] != other.data[i]) return false;
        return true;
    }

    bool operator!=(const Array& other) const {
        return !(*this == other);
    }

    void Print() const {
        cout << "Array elements: ";
        for (int i = 0; i < length; i++) cout << data[i] << " ";
        cout << "\n";
    }

    friend void operator+=(Array& a, int value) {
        a.AddToBack(value);
    }

    friend void operator-=(Array& a, int value) {
        a.RemoveByValue(value);
    }
};

int main() {
    SetConsoleOutputCP(1251);

    Array a;
    a += 10;
    a += 20;
    a.Print();

    Array b = a;
    b += 30;
    b.Print();

    a = b;
    a.Print();

    cout << (a == b ? "Equal" : "Not equal") << "\n";
    b += 99;
    cout << (a != b ? "Different" : "Same") << "\n";

    string s = (string)a;
    cout << s << "\n";

    Array c("5 6 7 8 9");
    c.Print();

    cout << c[2] << "\n";
    c[2] = 77;
    c.Print();
}
