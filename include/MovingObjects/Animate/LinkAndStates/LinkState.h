#pragma once

#include <memory>
#include "Utilities.h"

class Link;

class LinkState
{
public:
    virtual ~LinkState() = default;

    virtual std::unique_ptr<LinkState> handleInput(Input input, bool shielding, bool pushing) = 0;
    virtual void enter(Link& link) = 0;
};
