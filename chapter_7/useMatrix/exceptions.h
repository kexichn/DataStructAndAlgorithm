#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

// exceptions.h  -- define the exception class

#include <string>

using std::string;
class BaseException
{
public:
	BaseException() = default;
	virtual ~BaseException() = default;
	BaseException(const string& s) { m_information = s; }
	virtual string what() { return m_information; }
	
protected:
	string m_information;	
};

class illegalParameterValue : public BaseException
{
public:
	illegalParameterValue(const string& s) : BaseException(s) { }
	virtual ~illegalParameterValue() = default;
};

class illegalIndex : public BaseException
{
public:
	illegalIndex(const string& s) : BaseException(s) { }
	virtual ~illegalIndex() = default;
};

class matrixIndexOutOfRange : public BaseException 
{
public:
	matrixIndexOutOfRange() : BaseException("matrix index out of range") {  }
	virtual ~matrixIndexOutOfRange() = default;
};

class matrixSizeMismatch : public BaseException
{
public:
	matrixSizeMismatch() : BaseException("matrix size mismatch") {  }
	virtual ~matrixSizeMismatch() = default;
};

#endif
