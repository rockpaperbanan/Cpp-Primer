#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <iostream>
#include "sales_data_exceptions.h"



class Sales_data;

namespace std
{
	template<> struct hash<Sales_data>;
}


class Sales_data {
friend std::ostream& operator<<(std::ostream&, const Sales_data&);
friend std::istream& operator>>(std::istream&, Sales_data&);
friend bool operator==(const Sales_data&, const Sales_data&);

friend std::ostream& print(std::ostream&, const Sales_data&);
friend std::istream& read(std::istream&, Sales_data&);
friend Sales_data operator+(const Sales_data&, const Sales_data&);

friend struct std::hash<Sales_data>;

public:
	// constructors
	Sales_data() = default;
	Sales_data(const std::string& s): bookNo(s) { }
	Sales_data(const std::string& s, unsigned n, double p):
	           bookNo(s), units_sold(n), revenue(p*n) { }
	Sales_data(std::istream&);
	Sales_data& operator=(const std::string&);

	std::string isbn() const { return bookNo; }
	Sales_data& operator+=(const Sales_data&);
	operator std::string() const { return bookNo; }
	explicit operator double() const { return revenue; }

	using PMEM = double (Sales_data::*)() const;
	static PMEM get_pavg_price()
		{ return &Sales_data::avg_price; }
private:
	double avg_price() const;  
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

// non-member Sales_data operations
inline
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{ return lhs.isbn() < rhs.isbn(); }

inline
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() == rhs.isbn() && 
	       lhs.units_sold == rhs.units_sold && 
	       lhs.revenue == rhs.revenue;
}

inline
bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
	return !(lhs == rhs);
}

inline double Sales_data::avg_price() const
{
	if (units_sold)
		return revenue/units_sold;
	else
		return 0;
}

// old versions
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream& print(std::ostream&, const Sales_data&);
std::istream& read(std::istream&, Sales_data&);

// new operator functions
Sales_data operator+(const Sales_data&, const Sales_data&);
std::ostream& operator<<(std::ostream&, const Sales_data&);
std::istream& operator>>(std::istream&, Sales_data&);

template<> struct std::hash<Sales_data>
{
	size_t operator()(const Sales_data& s) const
		{ return hash<string>()(s.bookNo) ^
				 hash<unsigned>()(s.units_sold) ^
				 hash<double>()(s.revenue);
		}
};

#endif
