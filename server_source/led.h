#ifndef LED_H
#define LED_H

#include <string>
#include <cstdio>
#include <list>

using namespace std;

class Led
{
public:
    explicit Led();
    explicit Led(string ledState, string ledColor, int ledRate);

    string ledState() const;
    void setLedState(const string &ledState);

    string ledColor() const;
    void setLedColor(const string &ledColor);

    string colorList(int i) const;

    int ledRate() const;
    void setLedRate(int ledRate);

private:
    string _ledState;
    string _ledColor;
    string _colorList[3];
    int _ledRate;
};

#endif // LED_H
