#include "Grid.h"
#include <cassert>
#include <algorithm>


Grid::Grid(size_t rows, size_t cols) :
	m_data(rows*cols, false),
	m_rows(rows),
	m_cols(cols)
{	
}

Grid::Grid(size_t rows, size_t cols, std::vector<bool> data) :
	m_data(data),
	m_rows(rows),
	m_cols(cols)
{
}

Grid::~Grid()
{
}

void Grid::rotate(int turns)
{
	assert(false);

	// Alias rotations greater than 3
	turns = turns % 4;

	// No rotation, no change
	if (turns == 0) {
		return;
	}
#if 0
	if (turns == 1)
	{
		for (size_t c = 0; c < m_bitmap[0].size(); i++)
		{
			for (size_t r = 0; r < m_bitmap.size(); j++)
			{
				(*bitm_p)[i][j] = m_bitmap[i][j];
			}
		}
	}
#endif
}

// Iterate over the input grid and add any true elements to the member grid.
// Any true elements of the input grid must fall within the bounds of the member grid
void Grid::merge(const Grid & grid, size_t row_offset, size_t col_offset)
{
	for (size_t r = 0; r < grid.m_rows; r++) {
		for (size_t c = 0; c < grid.m_cols; c++) {
			if (grid.at(r, c) == true) {
				// No true elements should be outside the bounds of the member grid
				assert(r + row_offset < m_rows);
				assert(c + col_offset < m_cols);

				// This element of the member grid should not already be set to true
				assert(at(r + row_offset, c + col_offset) == false);

				set(r + row_offset, c + col_offset, true);
			}
		}
	}
}

bool Grid::checkIntersect(const Grid & grid, size_t row_offset, size_t col_offset) const
{
	for (size_t r = 0; r < grid.m_rows; r++) {
		for (size_t c = 0; c < grid.m_cols; c++) {
			if (grid.at(r, c) == true) {
				// No true elements should be outside the bounds of the member grid
				assert(r + row_offset < m_rows);
				assert(c + col_offset < m_cols);
				
				if (at(r + row_offset, c + col_offset) == true) {
					// Found an intersection
					return true;
				}
			}
		}
	}

	return false;
}

void Grid::clear()
{
	m_data.clear();
	m_data.insert(m_data.begin(), m_rows*m_cols, false);
}

void Grid::setData(const std::vector<bool> & data)
{
	assert(data.size() == m_rows * m_cols);
	m_data = data;
}

bool Grid::at(size_t row, size_t col) const
{
	assert(row < m_rows);
	assert(col < m_cols);
	return m_data[col + row*m_cols];
}

void Grid::set(size_t row, size_t col, bool val)
{
	m_data[col + row * m_cols] = val;
}

bool Grid::operator==(const Grid & rhs) const
{
	if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
		return false;
	}
	return m_data == rhs.m_data;	
}

std::ostream & operator<<(std::ostream & os, Grid const & g)
{
	// TODO : Could be implemented cleaner with an iterator
	for (size_t r = 0; r < g.m_rows; r++) {
		for (size_t c = 0; c < g.m_cols; c++) {
			os << (g.at(r, c) ? "X" : "-");
		}
		os << std::endl;
	}

	return os;
}
