#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <assert.h>
#include <stdexcept>


CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be zero");
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalize();
}

std::pair<int, CRational> CRational::ToCompoundFraction()const
{
	auto intPart = m_numerator / m_denominator;
	return { intPart, *this - intPart };
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	assert(m_denominator > 0);
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
//////////////////////////////////////////////////////////////////////////
double CRational::ToDouble() const
{
	return (static_cast<double>(m_numerator) / m_denominator);
}



//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const CRational::operator+() const
{
	return CRational(m_numerator, m_denominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
//////////////////////////////////////////////////////////////////////////
CRational const operator+(CRational const & rational1, CRational const & rational2)
{
	int resultDenominator = rational1.GetDenominator() * rational2.GetDenominator();
	int resultNumerator1 = rational1.GetNumerator() * rational2.GetDenominator();
	int resultNumerator2 = rational2.GetNumerator() * rational1.GetDenominator();
	int resultNumerator = resultNumerator1 + resultNumerator2;
	return CRational(resultNumerator, resultDenominator);
}


//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
//////////////////////////////////////////////////////////////////////////
const CRational operator -(CRational const & number1, CRational const & number2)
{
	int numerator = number1.GetNumerator() * number2.GetDenominator() - number2.GetNumerator() * number1.GetDenominator();
	int denominator = number1.GetDenominator() * number2.GetDenominator();
	return CRational(numerator, denominator);
}


//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
//////////////////////////////////////////////////////////////////////////
CRational CRational::operator += (CRational const & rational)
{
	m_numerator = (rational.GetNumerator() * m_denominator) + (m_numerator * rational.GetDenominator());
	m_denominator *= rational.GetDenominator();
	Normalize();
	return *this;
}



//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
//////////////////////////////////////////////////////////////////////////
CRational CRational::operator -= (CRational const & rational)
{
	m_numerator = (m_numerator * rational.GetDenominator()) - (rational.GetNumerator() * m_denominator);
	m_denominator *= rational.GetDenominator();
	Normalize();
	return *this;
}



//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
//////////////////////////////////////////////////////////////////////////
CRational const operator/(CRational const & rational1, CRational const & rational2)
{
	int resultDenominator = rational1.GetDenominator() * rational2.GetNumerator();
	int resultNumerator = rational1.GetNumerator() * rational2.GetDenominator();
	return CRational(resultNumerator, resultDenominator);
}

CRational const operator *(CRational const& rational1, CRational const& rational2)
{
	int newNum = rational1.GetNumerator() * rational2.GetNumerator();
	int newDen = rational1.GetDenominator() * rational2.GetDenominator();

	return CRational(newNum, newDen);
}


//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
//////////////////////////////////////////////////////////////////////////
CRational & CRational::operator *=(CRational const & number)
{
	m_numerator *= number.GetNumerator();
	m_denominator *= number.GetDenominator();
	Normalize();

	return *this;
}



//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////
CRational & CRational::operator/=(CRational const & rational)
{
	if (rational.GetNumerator() == 0)
	{
		throw std::invalid_argument("Division by zero");
	}
	m_numerator *= rational.GetDenominator();
	m_denominator *= rational.GetNumerator();
	Normalize();
	return *this;
}



//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////
bool operator == (CRational const & rational1, CRational const & rational2)
{
	return (rational1.GetNumerator() == rational2.GetNumerator()) 
		&& (rational1.GetDenominator() == rational2.GetDenominator());
}

bool operator != (CRational const & rational1, CRational const & rational2)
{
	return !(rational1 == rational2);
}



//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
//////////////////////////////////////////////////////////////////////////
bool operator >= (CRational const & rational1, CRational const & rational2)
{
	return ((rational1.GetNumerator() * rational2.GetDenominator())
		>= (rational2.GetNumerator() * rational1.GetDenominator()));
}

bool operator <= (CRational const & rational1, CRational const & rational2)
{
	return ((rational1.GetNumerator() * rational2.GetDenominator())
		<= (rational2.GetNumerator() * rational1.GetDenominator()));
}

bool operator > (CRational const & rational1, CRational const & rational2)
{
	return ((rational1.GetNumerator() * rational2.GetDenominator())
		> (rational2.GetNumerator() * rational1.GetDenominator()));
}

bool operator < (CRational const & rational1, CRational const & rational2)
{
	return ((rational1.GetNumerator() * rational2.GetDenominator())
		< (rational2.GetNumerator() * rational1.GetDenominator()));
}



//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream & stream, CRational const & rational)
{
	stream << rational.GetNumerator() << "/" << rational.GetDenominator();
	return stream;
}




//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//////////////////////////////////////////////////////////////////////////
std::istream & operator >> (std::istream & stream, CRational & rational)
{
	int numerator;
	int denominator;
	if ((stream >> numerator) && (stream.get() == '/') && (stream >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}
	return stream;
}

