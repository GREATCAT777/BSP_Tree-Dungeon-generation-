#pragma once
template<typename T>
class MyVector4
{
private:
	T m_x;
	T m_y;
	T m_z;
	T m_w;

public:
	MyVector4(T x, T y, T z, T w) :m_x(x), m_y(y), m_z(z), m_w(w) {};
	MyVector4(const MyVector4<T>& rhs) :m_x(rhs.m_x), m_y(rhs.m_y), m_z(rhs.m_z), m_w(rhs.m_w) {};
	~MyVector4() {};

	const MyVector4<T>& operator=(const MyVector4<T>& rhs) {
		m_x = rhs.m_x;
		m_y = rhs.m_y;
		m_z = rhs.m_z;
		m_w = rhs.m_w;

		return *this;
	};
	const MyVector4<T>& operator+(const MyVector4<T>& rhs) {
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		m_z += rhs.m_z;
		m_w += rhs.m_w;

		return *this;
	};
	const MyVector4<T>& operator-(const MyVector4<T>& rhs) {
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		m_z -= rhs.m_z;
		m_w -= rhs.m_w;

		return *this;
	};
};