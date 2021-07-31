#include <vector>
#include <type_traits>

template <
    class T, 
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
class Matrix {
    public:
        int rows;
        int columns;
        int size;

        Matrix& operator*(*Matrix);
        Matrix& operator+(*Matrix);
        Matrix& operator-(*Matrix);

    private:
        std::vector<std::vector<T>>;
};