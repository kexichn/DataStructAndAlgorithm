#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

// exceptions.h  -- define the exception class

#include <string>

using std::string;
class BaseException
{
public:
	BaseException() = default;
	BaseException(const string& s) { m_information = s; }
	virtual string what() { return m_information; }
	
protected:
	string m_information;	
};

class illegalParameterValue : public BaseException
{
public:
	illegalParameterValue(const string& s) : BaseException(s) { }	
};

class illegalIndex : public BaseException
{
public:
	illegalIndex(const string& s) : BaseException(s) { }	
};

#endif
