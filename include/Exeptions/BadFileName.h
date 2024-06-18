#pragma once

#include <exception>

class BadFileName : public std::exception
{
public:
	const char* what() const noexcept {
		return "Failed to open File.\n";
	}
};