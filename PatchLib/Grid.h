#pragma once

#include <array>
#include <vector>

class Grid
{
public:
	// Construct a grid of given size, initialized to all false
	Grid(size_t rows, size_t cols);

	// Construct a grid of given size, intialized to the input vector. Size of the vector
	// must exactly match rows*cols
	Grid(size_t rows, size_t cols, std::vector<bool> data);
	~Grid();

	// Rotate the grid data by the given number of ninty-degree turns
	void rotate(int turns);

	// Merge a grid into this one by positioning the input grid at the given offset and 
	// performing a union
	void merge(const Grid& grid, size_t row_offset, size_t col_offset);

	// Check if any true elements of the input grid would intersect with the member grid
	bool checkIntersect(const Grid& grid, size_t row_offset, size_t col_offset) const;

	// Set all elements of the grid to false
	void clear();

	// Overwrite all the elements of the grid to the input vector. Size of the vector must 
	// exactly match the grid
	void setData(const std::vector<bool> & data);

	// Get and set the element at the given indexes
	bool at(size_t row, size_t col) const;
	void set(size_t row, size_t col, bool val);

	// Equality operator returns true if grid dimensions and all elements are equal
	bool operator==(const Grid& rhs) const;

	friend std::ostream& operator<<(std::ostream& os, Grid const& g);

private:
	std::vector<bool> m_data;
	size_t m_rows;
	size_t m_cols;
};

