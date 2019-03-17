#pragma once
			
class MyVector2
{
public:
	float m_x;
	float m_y;
public:
	MyVector2() {};
	MyVector2(float x, float y) :m_x(x), m_y(y) {};
	MyVector2(const MyVector2& rhs) :m_x(rhs.m_x), m_y(rhs.m_y) {};
	~MyVector2() {};

	const MyVector2& operator=(const MyVector2& rhs) {
		m_x = rhs.m_x;
		m_y = rhs.m_y;

		return *this;
	};
	const MyVector2& operator+(const MyVector2& rhs) {
		m_x += rhs.m_x;
		m_y += rhs.m_y;

		return *this;
	};
	const MyVector2& operator-(const MyVector2& rhs) {
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;

		return *this;
	};

	operator int() {
		m_x = (int)m_x;
		m_y = (int)m_y;
		return *this;
	};

	operator float() {
		m_x = (float)m_x;
		m_y = (float)m_y;
		return *this;
	};
};