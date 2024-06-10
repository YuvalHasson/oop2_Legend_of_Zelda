#pragma once

#include <memory>
#include "Utilities.h"
class Link;

class LinkState{
public:
    virtual ~LinkState() = default;

    virtual std::unique_ptr<LinkState> handleInput(Input input) = 0;
    virtual void enter(Link& link) = 0;
};
