#pragma once

#include <memory>
#include "Utilities.h"

class Octorok;

class OctorokState
{
public:
    virtual ~OctorokState() = default;

    virtual std::unique_ptr<OctorokState> handleInput(Input) = 0;
    virtual void enter(Octorok&) = 0;
};
