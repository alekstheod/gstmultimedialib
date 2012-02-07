#pragma once
#include <exception>
#include <string>

/// <summary>
/// The main utilities namespace that contain the utilities classes.
/// </summary>
namespace utils {

/// <summary>
/// The basic exception class
/// </summary>

class AException: public std::exception {
private:
	/// <summary>
	/// Exception message
	/// </summary>
	std::string _message;

public:
	/// <summary>
	/// Basic exception constructor
	/// </summary>
	/// <param name="message">The exception message</param>
	/// <param name="sysMessage">Boolean argument that can allow to append the system message, false as default</sysMessage>
	AException(const std::string &message, bool sysMessage = false);

	/// <summary>
	/// Method that return the pointer to message string.
	/// </summary>
	/// <returns>Pointer to message string</returns>
	virtual const char* what(void) const throw ();

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~AException(void) throw ();
};

}

