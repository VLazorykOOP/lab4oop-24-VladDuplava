#include <iostream>
#include <iomanip>
using namespace std;

class VectorDouble {
private:
    double* v;
    int size;
    int state;
    static double badIndexRef;
    static int numVec;

public:
    // Конструктори
    VectorDouble(int n = 1) {
        if (n <= 0) n = 1;
        size = n;
        v = new double[size];
        for (int i = 0; i < size; i++) v[i] = 0.0;
        state = 0;
        ++numVec;
    }

    VectorDouble(int n, double val) : VectorDouble(n) {
        for (int i = 0; i < size; i++) v[i] = val;
    }

    VectorDouble(int n, double* arr) : VectorDouble(n) {
        if (arr != nullptr)
            for (int i = 0; i < size; ++i)
                v[i] = arr[i];
    }

    VectorDouble(const VectorDouble& other) {
        size = other.size;
        v = new double[size];
        for (int i = 0; i < size; i++) v[i] = other.v[i];
        state = other.state;
        ++numVec;
    }

    VectorDouble& operator=(const VectorDouble& other) {
        if (this != &other) {
            if (v) delete[] v;
            size = other.size;
            v = new double[size];
            for (int i = 0; i < size; i++) v[i] = other.v[i];
            state = other.state;
        }
        return *this;
    }

    VectorDouble& operator=(VectorDouble&& other) noexcept {
        if (this != &other) {
            if (v) delete[] v;
            size = other.size;
            v = other.v;
            state = other.state;
            other.v = nullptr;
            other.size = 0;
            other.state = -1;
        }
        return *this;
    }

    // Деструктор
    ~VectorDouble() {
        delete[] v;
        --numVec;
    }

    // Ініціалізація
    void Init(int n, double val = 0.0) {
        if (size != n) {
            delete[] v;
            size = n;
            v = new double[size];
        }
        for (int i = 0; i < size; i++) v[i] = val;
    }

    // Доступ до елементів
    double& operator[](int i) {
        if (i >= 0 && i < size) {
            state = 0;
            return v[i];
        }
        state = 1;
        return badIndexRef;
    }

    // Стани
    int getState() const { return state; }
    int getSize() const { return size; }

    // Ввід/вивід
    void Input() {
        int n;
        cout << "Введіть розмір вектора: ";
        cin >> n;
        Init(n);
        cout << "Введіть " << n << " елементів:\n";
        for (int i = 0; i < size; i++) {
            cin >> v[i];
        }
    }

    void Output() const {
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            cout << fixed << setprecision(2) << v[i] << " ";
        }
        cout << "]" << endl;
    }

    // Унарні оператори
    VectorDouble operator-() const {
        VectorDouble result(size);
        for (int i = 0; i < size; i++) result.v[i] = -v[i];
        return result;
    }

    // Арифметика з числами
    VectorDouble operator*(double val) const {
        VectorDouble res(size);
        for (int i = 0; i < size; i++) res.v[i] = v[i] * val;
        return res;
    }

    VectorDouble operator/(double val) const {
        VectorDouble res(size);
        for (int i = 0; i < size; i++) res.v[i] = v[i] / val;
        return res;
    }

    // Оператор +
    VectorDouble operator+(const VectorDouble& other) const {
        VectorDouble res(size);
        for (int i = 0; i < size; i++) res.v[i] = v[i] + other.v[i];
        return res;
    }

    // Оператор виводу
    friend ostream& operator<<(ostream& out, const VectorDouble& vec) {
        out << "[ ";
        for (int i = 0; i < vec.size; i++) {
            out << fixed << setprecision(2) << vec.v[i] << " ";
        }
        out << "]";
        return out;
    }

    // Оператор вводу
    friend istream& operator>>(istream& in, VectorDouble& vec) {
        for (int i = 0; i < vec.size; i++) in >> vec.v[i];
        return in;
    }

    static int CountVectors() {
        return numVec;
    }
};

// Статичні поля
double VectorDouble::badIndexRef = 0.0;
int VectorDouble::numVec = 0;


int main() {
    VectorDouble a(3, 2.5);
    VectorDouble b(3, 1.5);
    VectorDouble c = a + b;

    cout << "a + b = " << c << endl;

    c[1] = 10.0;
    cout << "c після зміни: " << c << endl;

    cout << "Спроба звернення до c[5]: " << c[5] << " (стан: " << c.getState() << ")" << endl;

    c.Output();
    return 0;
}
