//
// DD1388 - Lab 2: The matrix
//

#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>

template <typename T>
class Matrix {

    static_assert(std::is_move_constructible<T>::value, "T must be move-constructible"); // T must be move-constructible
    static_assert(std::is_move_assignable<T>::value, "T most be mov-assignable"); // T must be move-assignable

public:
    // constructors and assignment operators
    /* TODO: Make the appropriate constructor(s) explicit */
    Matrix();
    explicit Matrix(size_t dim);
    Matrix(size_t rows, size_t cols);
    Matrix(const std::initializer_list<T> & list);
    Matrix(Matrix<T> & other);
    Matrix(Matrix<T> && other) noexcept;
    
    Matrix(const Matrix<T>& other);


    Matrix<T> & operator=(const Matrix<T> & other);
    Matrix<T> & operator=(Matrix<T> && other) noexcept;

    ~Matrix();

    // accessors
    size_t rows() const;
    size_t cols() const;

    T & operator()(size_t row, size_t col);
    const T & operator()(size_t row, size_t col) const;

    // operators
    Matrix<T> operator*(const Matrix<T> & other) const;
    Matrix<T> operator+(const Matrix<T> & other) const;
    Matrix<T> operator-(const Matrix<T> & other) const;

    void operator*=(const Matrix<T> & other);
    void operator+=(const Matrix<T> & other);
    void operator-=(const Matrix<T> & other);

    // methods
    void reset();

    void insert_row(size_t row);
    void append_row(size_t row);
    void remove_row(size_t row);
    void insert_column(size_t col);
    void append_column(size_t col);
    void remove_column(size_t col);

    // iterators
    typedef T* iterator;

    iterator begin();
    iterator end();

private:
    size_t m_rows;
    size_t m_cols;
    size_t m_capacity;
    T * m_vec;
    size_t m_LMAO;

    //void copy_from(const Matrix<T>& other);
    //void move_from(Matrix<T>&& other) noexcept;
    //void allocate(size_t rows, size_t cols);
    //void deallocate();
};

// input/output operators
template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m);

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m);

// functions
template<typename T>
Matrix<T> identity(size_t dim);

template<typename T>
Matrix<T>::Matrix(){
    m_rows = 0;
    m_cols = 0;
    m_capacity = m_rows * m_cols;
    m_vec = new T [m_capacity];
}


template<typename T>
Matrix<T>::Matrix(size_t dim)
/*:  Initialize members here */ {
    // or here ...
    //std::cout << "INFO: Making a " << dim << "x" << dim << " matrix." << std::endl;
    size_t zero = 0;
    if (dim > 1000000)
    {
        throw std::out_of_range("The dimensions must be 0 or greater");
    }
    m_rows = dim;
    m_cols = dim;
    m_capacity = m_rows*m_cols;
    m_vec = new T [m_capacity];
}



template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols){
/*:  Initialize members here */ 
    if (rows > 10000000 || cols > 10000000){
        throw std::out_of_range("Rows must be a number that is greater or equal to zero");
    }
    m_rows = rows;
    m_cols = cols;
    m_capacity = rows * cols;
    //std::cout << "Capacity: "<<m_capacity<<std::endl;
    m_vec = new T [m_capacity];
}


template<typename T>
Matrix<T>::Matrix(const std::initializer_list<T> & list)
/*:  Initialize members here */ {
    //std::cout << "INFO :initializer_list is called" << std::endl;
    //std::cout << list.size() << std::endl;
    for (int i=1; i * i <= list.size(); i++)
    {
        if((list.size() % i == 0) && (list.size() / i == i)) {
            //std::cout << "Square found! " << (list.size() / i) << std::endl;
            m_rows = list.size() /i;
            m_cols = list.size() /i;
            m_capacity = m_rows*m_cols;
            m_vec = new T [m_capacity];

            int counter = 0;
            for (size_t i = 0; i < m_rows; i++)
            {
                for (size_t j = 0; j < m_cols; j++)
                {
                    m_vec[j+i*m_cols] = *(list.begin()+counter);
                    counter++;
                }
                
            }
            return;
        }
    }
    throw std::out_of_range("The amount of elements must be an even square root");
    
}

//template<typename T>
//Matrix<T>::Matrix(const Matrix<T>& other) : m_rows(other.m_rows), m_cols(other.m_cols), m_vec(other.m_vec) {}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
    : m_rows(other.m_rows), m_cols(other.m_cols), m_capacity(other.m_capacity)
{
    m_vec = new T[m_capacity];
    for (size_t i = 0; i < m_capacity; i++) {
        m_vec[i] = other.m_vec[i];
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> & other)
/*:  Initialize members here */ {
    // or here ...
    //std::cout << "INFO: & other called" << std::endl;
    m_cols = other.m_cols;
    m_rows = other.m_rows;
    m_capacity = other.m_capacity;
    m_vec = new T [m_capacity];
    for (size_t i = 0; i < m_capacity; i++)
    {
        m_vec[i] = other.m_vec[i];
    }
    
}

// template<typename T>
// Matrix<T>::Matrix(Matrix<T> && other) noexcept
// /*:  Initialize members here */ {
//     // or here ...
//     std::cout<< "INFO: && other called" << std::endl;

// }

template<typename T>
Matrix<T>::Matrix(Matrix<T> && other) noexcept 
    : m_rows(other.m_rows), m_cols(other.m_cols), m_capacity(other.m_capacity), m_vec(other.m_vec) {
    // Reset the other matrix to a valid state
    other.m_rows = 0;
    other.m_cols = 0;
    other.m_capacity = 0;
    other.m_vec = nullptr; // Prevent double free
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & other) {
    //std::cout<<"INFO: const operator = called" << std::endl;
    if (this == &other)
    {
        //std::cout << "Moved the operator to itself" << std::endl;
        //std::cout << this << std::endl;
        //std::cout << &other << std::endl;
        return *this;
    }

    m_cols = other.m_cols;
    m_rows = other.m_rows;
    m_capacity = other.m_capacity;
    delete[]m_vec;
    m_vec = new T [m_capacity];
    for (size_t i = 0; i<other.m_capacity; i++)
    {
        m_vec[i] = other.m_vec[i];

    }
    return *this;

}

template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> && other) noexcept {
    // Implementation goes here
    //std::cout<<"INFO: const operator = noexcept called" << std::endl;
    if (this == &other)
    {
        //std::cout << "Moved the operator to itself" << std::endl;
        //std::cout << this << std::endl;
        //std::cout << &other << std::endl;
        return *this;
    }

    m_cols = other.m_cols;
    m_rows = other.m_rows;
    m_capacity = other.m_capacity;
    delete[]m_vec;
    m_vec = new T [m_capacity];
    for (size_t i = 0; i<other.m_capacity; i++)
    {
        m_vec[i] = other.m_vec[i];
        
    }
    return *this;
    
}

template<typename T>
Matrix<T>::~Matrix() {
    // Implementation goes here
    //std::cout << "INFO: destructor called" << std::endl;
    delete[] m_vec;
}

template<typename T>
size_t Matrix<T>::rows() const {
    //std::cout << "INFO: rows called" << std::endl;
    return m_rows;
    // Implementation goes here
}

template<typename T>
size_t Matrix<T>::cols() const {
    // Implementation goes here
    //std::cout << "INFO: cols called" << std::endl;
    return m_cols;
}

template<typename T>
T & Matrix<T>::operator()(size_t row, size_t col) {
    // Implementation goes here
    //std::cout << "INFO: Operator called" << std::endl;
    int n = m_cols*(row-1)+(col-1);
    //std::cout << n << std::endl;
    if (row > m_rows || col >m_cols)
    {
        throw std::out_of_range("Tried to access a value in a position that is greater than the matrix");
    }
    //std::cout << "INFO: operator() called" << std::endl;
    //std::cout << n << std::endl;
    return m_vec[n];
}

template<typename T>
const T & Matrix<T>::operator()(size_t row, size_t col) const {
    // Implementation goes here
    //std::cout << "INFO: Operator const called" << std::endl;
    //std::cout << m_capacity << std::endl;
    int n = m_cols*(row-1)+(col-1);
    //std::cout << n << std::endl;
    if (row > m_rows || col > m_cols)
    {
        throw std::out_of_range("Tried to read a value in a position that is greater than the matrix");
    }
    //std::cout << "INFO: operator() const called" << std::endl;
    //std::cout << n << std::endl;
    return m_vec[n];
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & other) const {
    // Implementation goes here
    //std::cout << "INFO: * called" << std::endl;
    Matrix<T> mt(m_rows,other.m_cols);
    
    if (m_cols != other.m_rows)
    {
        throw std::out_of_range("Columns of matrix 1 must match the rows of matrix 2");
    }
    for (size_t i = 0; i < m_rows; i++)
    {
        for (size_t j = 0; j < other.m_cols; j++)
        {
            for (size_t k = 0; k < m_cols; k++)
            {
                //std::cout << "i:" << i+1 << std::endl;
                //std::cout << "j:" << j+1 << std::endl;
                //std::cout << "k:" << k+1 << std::endl;
                //std::cout << "this vector:" << m_vec[k+jm_cols] << std::endl;
                //std::cout << "other vector:" << other(k+1,j+1) << std::endl;
                //std::cout << "mult:" << m_vec[k+jm_cols]other(k+1,j+1) << std::endl;
                //std::cout << "" << std::endl;
                mt(i+1,j+1) += m_vec[k+i*m_cols]*other(k+1,j+1);
            }
        }
    }
    return mt;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const {
    // Implementation goes here
    //std::cout<<"INFO: const operator + called" << std::endl;

    Matrix<T> temp(m_rows, other.m_cols);
    if (m_cols != other.m_cols || m_rows != other.m_rows)
    {
        throw std::out_of_range("The dimensions must match the dimensions of each other");
    }
    //temp = new T [m_capacity];
    for (size_t i = 0; i < m_rows; i++)
    {
        for (size_t j = 0; j < m_cols; j++)
        {
            temp(i+1,j+1) = m_vec[j+i*m_cols] + other(i+1,j+1);
        }
        
    }
return temp;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const {
    // Implementation goes here
    //std::cout<<"INFO: const operator - called" << std::endl;
    Matrix<T> temp(m_rows, other.m_cols);
    if (m_cols != other.m_cols || m_rows != other.m_rows)
    {
        throw std::out_of_range("The dimensions must match the dimensions of each other");
    }
    
    
    //temp = new T [m_capacity];
    
    for (size_t i = 0; i < m_rows; i++)
    {
        for (size_t j = 0; j < m_cols; j++)
        {
            temp(i+1,j+1) = m_vec[j+i*m_cols] - other(i+1,j+1);
        }
        
    }

return temp;
}

template<typename T>
void Matrix<T>::operator*=(const Matrix<T> & other) {
    // Implementation goes here
    //std::cout << "INFO: = called" << std::endl;
    Matrix<T> mt(m_rows,other.m_cols);
    if (m_cols != other.m_rows)
    {
        throw std::out_of_range("Columns of matrix 1 must match the rows of matrix 2");
    }
    
    for (size_t i = 0; i < m_rows; i++)
    {
        for (size_t j = 0; j < other.m_cols; j++)
        {
            for (size_t k = 0; k < m_cols; k++)
            {
                //std::cout << "i:" << i+1 << std::endl;
                //std::cout << "j:" << j+1 << std::endl;
                //std::cout << "k:" << k+1 << std::endl;
                //std::cout << "this vector:" << m_vec[k+jm_cols] << std::endl;
                //std::cout << "other vector:" << other(k+1,j+1) << std::endl;
                //std::cout << "mult:" << m_vec[k+jm_cols]other(k+1,j+1) << std::endl;
                //std::cout << "" << std::endl;
                mt(i+1,j+1) += m_vec[k+i*m_cols]*other(k+1,j+1);
            }
        }
    }
    m_rows = mt.m_rows;
    m_cols = mt.m_cols;
    m_capacity = m_rows*m_cols;
    delete[] m_vec;
    m_vec = new T [m_capacity];
    for (size_t i = 0; i < m_capacity; i++)
    {
        m_vec[i] = mt.m_vec[i];
    }
}

template<typename T>
void Matrix<T>::operator+=(const Matrix<T> & other) {
    // Implementation goes here
    //std::cout << "INFO: +=" << std::endl;
    Matrix<T> mt(m_rows,other.m_cols);
    if (m_cols != other.m_cols || m_rows != other.m_rows)
    {
        throw std::out_of_range("The dimensions of each matrix should match each other");
    }
    for (size_t i = 0; i < m_rows; i++)
    {
        for (size_t j = 0; j < m_cols; j++)
        {
            mt(i+1,j+1) = m_vec[j+i*m_cols] + other(i+1,j+1);
        }
        
    }
    m_rows = mt.m_rows;
    m_cols = mt.m_cols;
    m_capacity = m_rows*m_cols;
    delete[] m_vec;
    m_vec = new T [m_capacity];
    for (size_t i = 0; i < m_capacity; i++)
    {
        m_vec[i] = mt.m_vec[i];
    }
    
}

template<typename T>
void Matrix<T>::operator-=(const Matrix<T> & other) {
    // Implementation goes here
    //std::cout << "INFO: -=" << std::endl;
    Matrix<T> mt(m_rows,other.m_cols);
    if (m_cols != other.m_cols || m_rows != other.m_rows)
    {
        throw std::out_of_range("The dimensions of each matrix should match each other");
    }
    for (size_t i = 0; i < m_rows; i++)
    {
        for (size_t j = 0; j < m_cols; j++)
        {
            mt(i+1,j+1) = m_vec[j+i*m_cols] - other(i+1,j+1);
        }
        
    }
    m_rows = mt.m_rows;
    m_cols = mt.m_cols;
    m_capacity = m_rows*m_cols;
    delete[] m_vec;
    m_vec = new T [m_capacity];
    for (size_t i = 0; i < m_capacity; i++)
    {
        m_vec[i] = mt.m_vec[i];
    }
    
}

template<typename T>
void Matrix<T>::reset() {
    // Implementation goes here
    //std::cout << "INFO RESET" << std::endl;
    for (size_t i = 0; i < m_capacity; i++)
    {
        m_vec[i]=0;
    }
    

}

template<typename T>
void Matrix<T>::insert_row(size_t row) {
    // Implementation goes here
    //std::cout << "INFO: insert row of zeroes before row number: "<< row << std::endl;
    int *m_vec_temp = m_vec;
    m_capacity = m_capacity +m_cols;
    m_vec = new T [m_capacity];
    
    for (size_t i = 0; i < m_capacity; i++){   
        m_vec[i]=0;
            //if (i > (m_cols*(row-1)-1) && i < (m_cols*(row-1) + m_cols){
            if (i < (m_cols*(row-1)) ){
                //copy
                //std::cout << i << std::endl;
                m_vec[i] = m_vec_temp[i];
            }
            if (i > (m_cols*(row-1))+m_cols-1){
                //std::cout << (i-m_cols) << std::endl;
                m_vec[i] = m_vec_temp[i-m_cols];
            }
        }

    
    delete[] m_vec_temp;
    m_rows++;
}

template<typename T>
void Matrix<T>::append_row(size_t row) {
    // Implementation goes here
    //std::cout << "INFO: insert row of zeroes after row number: "<< row << std::endl;
    int *m_vec_temp = m_vec;
    m_capacity = m_capacity +m_cols;
    m_vec = new T [m_capacity];
    
    for (size_t i = 0; i < m_capacity; i++){  
        m_vec[i]=0; 
            //if (i > (m_cols*(row-1)-1) && i < (m_cols*(row-1) + m_cols){
            if (i < (m_cols*(row)) ){
                //copy
                //std::cout << i << std::endl;
                m_vec[i] = m_vec_temp[i];
            }
            if (i > (m_cols*(row))+m_cols-1){
                //std::cout << (i-m_cols) << std::endl;
                m_vec[i] = m_vec_temp[i-m_cols];
            }
        }

    
    delete[] m_vec_temp;
    m_rows++;
}

template<typename T>
void Matrix<T>::remove_row(size_t row) {
    // Implementation goes here
    //std::cout << "INFO: remove row number: "<< row << std::endl;
    int *m_vec_temp = m_vec;
    m_capacity = m_capacity - m_cols;
    m_vec = new T [m_capacity];

    for (size_t i = 0; i < m_capacity; i++){
        m_vec[i]=0;
        //std::cout << row << std::endl;   
        if (i < (m_cols*(row-1)) ){
                //std::cout << i << std::endl;
                m_vec[i] = m_vec_temp[i];
            }
        if (i >= ((m_cols*(row-1))) ){
                //std::cout << (i+m_cols) << std::endl;
                m_vec[i] = m_vec_temp[i+m_cols];
            }

    
        //std::cout << m_vec[i] << std::endl;
        //std::cout << " " << std::endl;
        }

    
    delete[] m_vec_temp;
    m_rows--;
}

template<typename T>
void Matrix<T>::insert_column(size_t col) {
    // Implementation goes here
    //std::cout << "INFO: insert row of zeroes before col number: "<< col << std::endl;
    int *m_vec_temp = m_vec;
    m_capacity = m_capacity+m_rows;
    m_vec = new T [m_capacity];
    m_cols++;
    int pos = 0;
    int temp = 0;
    for (size_t i = 0; i < m_rows; i++){       //For-loop that pick out the zero value on each row
        int zero_col = (i*(m_cols))+(col-1);
        for (size_t j = 0; j < m_cols; j++){
            m_vec[pos] = m_vec_temp[temp];
            if (zero_col == pos){
                m_vec[pos] = 0;
                temp--;
            }
            pos++;
            temp++;
        }
    }
    delete[] m_vec_temp;
}

template<typename T>
void Matrix<T>::append_column(size_t col) {
    // Implementation goes here
        //std::cout << "INFO: Append row of zeroes before col number: "<< col << std::endl;
    int *m_vec_temp = m_vec;
    m_capacity = m_capacity +m_rows;
    m_vec = new T [m_capacity];
    m_cols++;
    int pos = 0;
    int temp = 0;
    for (size_t i = 0; i < m_rows; i++){       //For-loop that pick out the zero value on each row
        int zero_col = (i*(m_cols))+(col);
        for (size_t j = 0; j < m_cols; j++){
            m_vec[pos] = m_vec_temp[temp];
            if (zero_col == pos){
                m_vec[pos] = 0;
                temp--;
            }
            pos++;
            temp++;
        }
    }
    delete[] m_vec_temp;

}

template<typename T>
void Matrix<T>::remove_column(size_t col) {
    //std::cout << "INFO: Remove row of zeroes before col number: "<< col << std::endl;
    int *m_vec_temp = m_vec;
    m_capacity = m_capacity -m_rows;
    m_vec = new T [m_capacity];
    int j=0;
    for (size_t i = 0; i < m_capacity; i++){   
            //std::cout<<"i: " << i << std::endl;
        
        if (i == col-1 + (m_cols-1)*(j)){
            j++;
            
            //m_vec[i] = m_vec_temp[i];

        }
        if (i < col-1 + m_cols*j){
            m_vec[i] = m_vec_temp[i+j];
            //std::cout << " m_vec "<< m_vec[i] << std::endl;
        }
        }

    
    delete[] m_vec_temp;
    m_cols--;
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::begin() {
    // Implementation goes here
    //std::cout << "INFO: begin() called" << std::endl;
    int *first_element = std::addressof(m_vec[0]);
    //std::cout << first_element << std::endl;
    return first_element;


}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::end() {
    // Implementation goes here
    //std::cout << "INFO: end() called" <<std::endl;
    int last_element_nr = m_capacity-1;
    int * last_element = std::addressof(m_vec[last_element_nr]);
    //std::cout << last_element << std::endl;
    return last_element;
}

template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m) {
    // Implementation goes here
    //std::cout<<"INFO: isttream called" << std::endl;

    for (size_t i = 1; i <m.rows()+1; i++)
    {
        //std::cout << "New row started" << std::endl;
        for (size_t j = 1; j < m.cols()+1; j++)
        {
            //std::cout << "Currently at Row:" << i << "/" << m.rows() << " and Column:" << j << "/"<<m.cols() << "   Input: ";
            is >> m(i,j);
            //std::cout << std::endl;
        }
        
    }
    return is;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m) {
    // Implementation goes here
    //std::cout<<"INFO: operator ostream is called " << std::endl;
    for (size_t i = 1; i < m.rows()+1; i++){
        for (size_t j = 1; j < m.cols()+1; j++){
            std::cout<<m(i,j) << " ";
        }
        os << std::endl;
    }
    return os;
}


template<typename T>
Matrix<T> identity(size_t dim) {
    // Implementation goes here
    //std::cout << "INFO: identity called" << std::endl;
    Matrix<int> mi(dim);
    int mover = 0;
    for (size_t i = 1; i < dim+1; i++){
        for (size_t j = 1; j < dim+1; j++){
            mi(i,j) = 0;
            if (i == j)
            {
                mi(i,j) = 1;
            }
        }
    }
    return mi;
}


#endif //MATRIX_H