#include "led.h"

Led::Led()
{
    _colorList[0] = "red";
    _colorList[1] = "green";
    _colorList[2] = "blue";
}

Led::Led(string ledState, string ledColor, int ledRate)
{
    _ledState = ledState;
    _ledColor = ledColor;
    _ledRate = ledRate;
}

string Led::ledState() const
{
    return _ledState;
}

void Led::setLedState(const string &ledState)
{
    _ledState = ledState;
}

string Led::ledColor() const
{
    return _ledColor;
}

void Led::setLedColor(const string &ledColor)
{
    _ledColor = ledColor;
}

string Led::colorList(int i) const
{
    return _colorList[i];
}


int Led::ledRate() const
{
    return _ledRate;
}

void Led::setLedRate(int ledRate)
{
    _ledRate = ledRate;
}


