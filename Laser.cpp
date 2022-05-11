#include "Laser.h"
Laser::Laser(uint8_t v1, uint8_t v2, uint8_t g1, uint8_t g2) : V1(v1), V2(v2), G1(g1), G2(g2) 
{
    pinMode(v1, OUTPUT);
    pinMode(v2, OUTPUT);
    if (g1 != 0 && g2 != 0)
    {
        pinMode(g1, OUTPUT);
        pinMode(g2, OUTPUT);
        this->type = Type::VccVccGroundGround;
    } else {
        this->type = Type::VccVcc;
    }
    this->Stop();
};
Laser::Laser(uint8_t v, uint8_t g) : V1(v), V2(0), G1(g), G2(0) 
{
    pinMode(v, OUTPUT);
    pinMode(g, OUTPUT);
    this->type = Type::VccAndGround;
    this->Stop();
};
Laser::Laser(uint8_t v) : V1(v), V2(0), G1(0), G2(0) 
{
    pinMode(v, OUTPUT);
    this->type = Type::SinglePin;
    this->Stop();
};

void Laser::Start() const
{
    switch (this->getType())
    {
    case Type::SinglePin:
        this->StartOne();
        break;
    case Type::VccAndGround:
        this->StartVccGnd();
        break;
    case Type::VccVcc:
        this->StartTwoVcc();
        break;
    case Type::VccVccGroundGround:
        this->StartFour();
        break;
    }
}
void Laser::Stop() const
{
    switch (this->getType())
    {
    case Type::SinglePin:
        this->StopOne();
        break;
    case Type::VccAndGround:
        this->StopVccGnd();
        break;
    case Type::VccVcc:
        this->StopTwoVcc();
        break;
    case Type::VccVccGroundGround:
        this->StopFour();
        break;
    }
}
Laser::Type Laser::getType() const
{
    return this->type;
}

void Laser::StartFour() const
{
    digitalWrite(this->V1, HIGH);
    digitalWrite(this->V2, HIGH);
    digitalWrite(this->G1, LOW);
    digitalWrite(this->G2, LOW);
}
void Laser::StopFour() const
{
    digitalWrite(this->V1, LOW);
    digitalWrite(this->V2, LOW);
    digitalWrite(this->G1, LOW);
    digitalWrite(this->G2, LOW);
}

void Laser::StartVccGnd() const
{
    digitalWrite(this->V1, LOW);
    digitalWrite(this->G1, LOW);
}
void Laser::StopVccGnd() const
{
    digitalWrite(this->V1, HIGH);
    digitalWrite(this->G1, LOW);
}

void Laser::StartTwoVcc() const
{
    digitalWrite(this->V1, HIGH);
    digitalWrite(this->V2, HIGH);
}
void Laser::StopTwoVcc() const
{
    digitalWrite(this->V1, LOW);
    digitalWrite(this->V2, LOW);
}

void Laser::StartOne() const
{
    digitalWrite(this->V1, HIGH);
}
void Laser::StopOne() const
{
    digitalWrite(this->V1, LOW);
}
