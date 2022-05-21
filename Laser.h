#pragma once
#include <Arduino.h>
class Laser {
public:
    enum Type
    {
        SinglePin = 0,
        VccAndGround,
        VccLeftRightGround
    };
private:
    uint8_t Vcc, Left, Right, Ground;
    Type type;

    void StartFour() const;
    void StopFour() const;

    void StartVccGnd() const;
    void StopVccGnd() const;
    
    void StartTwoVcc() const;
    void StopTwoVcc() const;
    
    void StartOne() const;
    void StopOne() const;
public:
    Laser(uint8_t VccPin, uint8_t LeftPin, uint8_t RightPin, uint8_t GroundPin);
    Laser(uint8_t LeftPin, uint8_t RightPin);
    Laser(uint8_t SinglePin);

    void Start() const;
    void Stop() const;
    
    Type getType() const;
};