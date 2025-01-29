#include "Matrix.hpp"
#include <cassert>

// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix *mat, int width, int height)
{
    if (width <= 0 || height <= 0) throw std::invalid_argument("Invalid Matrix dimensions");
    mat->width = width;
    mat->height = height;
    mat->data.resize(width * height, 0);
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix *mat, std::ostream &os)
{
    os << mat->width << " " << mat->height << std::endl;
    for (int row = 0; row < mat->height; row++)
    {
        for (int col = 0; col < mat->width; col++)
        {
            os << *Matrix_at(mat, row, col) << " ";
        }
        os << std::endl;
    }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix *mat)
{
    return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix *mat)
{
    return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int *Matrix_at(Matrix *mat, int row, int column)
{
    if (row < 0 || row >= mat->height || column < 0 || column >= mat->width)
        throw std::invalid_argument("Invalid Matrix index");
    return &mat->data[row * mat->width + column];
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int *Matrix_at(const Matrix *mat, int row, int column)
{
    if (row < 0 || row >= mat->height || column < 0 || column >= mat->width)
        throw std::invalid_argument("Invalid Matrix index");
    return &mat->data[row * mat->width + column];
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix *mat, int value)
{
    std::fill(mat->data.begin(), mat->data.end(), value);
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix *mat, int value)
{
    // Modify the left and right columns
    for (int row = 0; row < mat->height; row++)
    {
        if (row == 0 || row == mat->height - 1)
        {
            for (int col = 0; col < mat->width; col++)
            {
                *Matrix_at(mat, row, col) = value;
            }
        }
    }

    // Modify the top and bottom rows
    for (int col = 0; col < mat->width; col++)
    {
        if (col == 0 || col == mat->width - 1)
        {
            for (int row = 0; row < mat->height; row++)
            {
                *Matrix_at(mat, row, col) = value;
            }
        }
    }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix *mat)
{
    if (mat->data.empty()) return 0;
    int max = mat->data[0];
    for (int i = 1; i < mat->data.size(); i++)
        if (mat->data[i] > max) max = mat->data[i];
    return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix *mat, int row,
                                      int column_start, int column_end)
{
    // Conditions here for readability
    bool valid_row = row >= 0 && row < mat->height;
    bool valid_column_start = column_start >= 0 && column_start <= mat->width;
    bool valid_column_end = column_end >= 0 && column_end <= mat->width;
    bool valid_column_range = column_start < column_end;
    if (!valid_row || !valid_column_start || !valid_column_end || !valid_column_range)
        throw std::invalid_argument("Invalid indexing");
    else if (mat->data.empty()) return 0;

    // Set the current min and its column
    int min = mat->data[row * mat->width + column_start];
    int min_col = column_start;

    // Start from one after the start column due to initial value
    for (int col = column_start + 1; col < column_end; col++)
    {
        if (mat->data[row * mat->width + col] < min)
        {
            min = mat->data[row * mat->width + col];
            min_col = col;
        }
    }
    return min_col;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix *mat, int row, int column_start,
                            int column_end)
{
    // Conditions here for readability
    bool valid_row = row >= 0 && row < mat->height;
    bool valid_column_start = column_start >= 0 && column_start <= mat->width;
    bool valid_column_end = column_end >= 0 && column_end <= mat->width;
    bool valid_column_range = column_start < column_end;
    if (!valid_row || !valid_column_start || !valid_column_end || !valid_column_range)
        throw std::invalid_argument("Invalid indexing");
    else if (mat->data.empty()) return 0;

    // Set the current min
    int min = mat->data[row * mat->width + column_start];
    
    // Start from one after the start column due to initial value
    for (int col = column_start + 1; col < column_end; col++)
    {
        if (mat->data[row * mat->width + col] < min)
            min = mat->data[row * mat->width + col];
    }
    return min;
}
