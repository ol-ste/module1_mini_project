#pragma once

class BaseController
{
private:
public:
    virtual void init() = 0;
    virtual void run() = 0;
};
