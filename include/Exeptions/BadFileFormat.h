#pragma once

#include <exception>

class BadFileFormat : public std::exception
{
public:
	const char* what() const noexcept {
		return "Bad file Format.\n";
	}
};