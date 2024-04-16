#include <iostream>
#include <vector>

using namespace std;

class SparseMatrix
{
private:
    struct Element
    {
        int row;
        int col;
        int value;
    };

    vector<Element> elements;
    int rows;
    int columns;

public:
    SparseMatrix(int i, int j) : rows(i), columns(j) {}

    void addElement(int i, int j, int value)
    {
        if (i >= 0 && i < rows && j >= 0 && j < columns)
        {
            Element elem = { i, j, value };
            elements.push_back(elem);
        }
        else
        {
            cout << "Coordinates out of range. " << endl;
            return;
        }
    }

    int getElement(int i, int j)
    {
        if (i >= 0 && i < rows && j >= 0 && j < columns)
        {
            for (const auto& elem : elements)
            {
                if (elem.row == i && elem.col == j)
                {
                    return elem.value;
                }
            }
            return 0;
        }
        else
        {
            cout << "Coordinates out of range. " << endl;
            return -10;
        }
    }

    SparseMatrix add_matrix(const SparseMatrix& other) const {
        if (rows != other.rows || columns != other.columns)
        {
            cout << "Matrices have different size" << endl;
            return SparseMatrix(0, 0);
        }

        SparseMatrix result(rows, columns);
        for (const auto& elem : elements)
        {
            result.addElement(elem.row, elem.col, elem.value);
        }

        for (const auto& elem : other.elements)
        {
            bool found = false;
            for (auto& res_elem : result.elements)
            {
                if (res_elem.row == elem.row && res_elem.col == elem.col)
                {
                    res_elem.value += elem.value;
                    found = true;
                    break;
                }
            }

            if (!found) {
                result.addElement(elem.row, elem.col, elem.value);
            }
        }

        return result;
    }

    SparseMatrix subtract_matrix(const SparseMatrix& other) const {
        if (rows != other.rows || columns != other.columns)
        {
            cout << "Matrices have different size" << endl;
            return SparseMatrix(0, 0);
        }

        SparseMatrix result(rows, columns);
        for (const auto& elem : elements)
        {
            result.addElement(elem.row, elem.col, elem.value);
        }

        for (const auto& elem : other.elements)
        {
            bool found = false;
            for (auto& res_elem : result.elements)
            {
                if (res_elem.row == elem.row && res_elem.col == elem.col)
                {
                    res_elem.value -= elem.value;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                result.addElement(elem.row, elem.col, -elem.value);
            }
        }

        return result;
    }

    SparseMatrix multiply_matrix(SparseMatrix& other)
    {
        if (columns != other.rows)
        {
            cout << "Invalid matrix sizes" << endl;
            return SparseMatrix(0, 0);
        }

        SparseMatrix result(rows, other.columns);
        for (const auto& elem1 : elements)
        {
            for (const auto& elem2 : other.elements)
            {
                if (elem1.col == elem2.row)
                {
                    int val = result.getElement(elem1.row, elem2.col) + elem1.value * elem2.value;
                    result.addElement(elem1.row, elem2.col, val);
                }
            }
        }
        return result;
    }

    void print_matrix()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                cout << getElement(i, j) << " ";
            }
            cout << endl;
        }
    }

    SparseMatrix multiply_scalar(int scalar) const
    {
        SparseMatrix result(rows, columns);

        for (const auto& elem : elements)
        {
            int val = elem.value * scalar;
            result.addElement(elem.row, elem.col, val);
        }

        return result;
    }

    void removeElement(int r, int j)
    {
        if (r < 0 || r >= rows || j < 0 || j >= columns)
        {
            cout << "Coordinates are out of range." << endl;
            return;
        }

        int index = -1;
        for (size_t i = 0; i < elements.size(); ++i)
        {
            if (elements[i].row == r && elements[i].col == j)
            {
                index = i;
                break;
            }
        }

        if (index != -1)
        {
            elements.erase(elements.begin() + index);
        }
    }
};

int main()
{
    SparseMatrix A(4, 7);
    A.addElement(0, 2, 1);
    A.addElement(1, 5, 8);
    A.addElement(3, 4, 3);

    cout << "Your first matrix (A): " << endl;
    A.print_matrix();
    cout << endl;


    SparseMatrix B(4, 7);
    B.addElement(0, 2, 3);
    B.addElement(1, 1, 4);
    B.addElement(2, 2, 5);

    SparseMatrix C(7, 4);
    C.addElement(0, 2, 1);
    C.addElement(1, 1, 3);
    C.addElement(2, 2, 2);

    cout << "Your second matrix (B):" << endl;
    B.print_matrix();
    cout << endl;

    cout << "Your third matrix (C):" << endl;
    C.print_matrix();
    cout << endl;

    SparseMatrix sum = A.add_matrix(B);
    cout << "A + B =" << endl;
    sum.print_matrix();
    cout << endl;

    SparseMatrix difference = A.subtract_matrix(B);
    cout << "A - B = " << endl;
    difference.print_matrix();
    cout << endl;

    SparseMatrix D = A.multiply_matrix(C);
    cout << "A * C = " << endl;
    D.print_matrix();
    cout << endl;

    SparseMatrix R = A.multiply_scalar(4);
    cout << "4 * A = " << endl;
    R.print_matrix();
    cout << endl;

    B.removeElement(0, 2);
    cout << "Removed element i = 0, j = 2: " << endl;
    B.print_matrix();
    cout << endl;
    return 0;
}
