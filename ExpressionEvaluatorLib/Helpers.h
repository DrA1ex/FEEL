#ifndef Helpers_h__
#define Helpers_h__

#include <string>
#include <sstream>

class MakeString {
public:
	template<class T>
	MakeString& operator<< (const T& arg) {
		m_stream << arg;
		return *this;
	}
	operator std::string() const {
		return m_stream.str();
	}
protected:
	std::stringstream m_stream;
};

#endif // Helpers_h__
