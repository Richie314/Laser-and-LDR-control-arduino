#pragma once
#include <Arduino.h>
class Laser {
public:
    enum Type
    {
        SinglePin = 0,
        VccAndGround,
        VccVcc,
        VccVccGroundGround
    };
private:
    uint8_t V1, V2, G1, G2;
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
    Laser(uint8_t v1, uint8_t v2, uint8_t g1, uint8_t g2);
    Laser(uint8_t v, uint8_t g);
    Laser(uint8_t v);

    void Start() const;
    void Stop() const;
    
    Type getType() const;
};