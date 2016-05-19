#ifndef BAD_DIMENSION_EXCEPTION_H
#define BAD_DIMENSION_EXCEPTION_H

#include <exception>
#include <iostream>

/**
 * @brief Exception class for a bad dimension input 
 */
class BadDimensionException : public std ::exception
{
public:
	
	/**
	 * @brief default constructor
	 */
    BadDimensionException();
    
	/**
	 * @brief constructor receives a string and sets our error message to be that screen
	 * @param our string message
	 */
    BadDimensionException(const std :: string message) : _errorMessage(message)
	{
	}
    
	/**
	 * @brief returns our message overrides std:: exception:: what()
	 * @return our message	 
	 */
    const char* what() const noexcept override
    {
        return _errorMessage.c_str();
    }
    
private:
    
    const std :: string _errorMessage; /**our print message */
};

#endif
