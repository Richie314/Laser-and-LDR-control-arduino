#include "Laser.h"
Laser::Laser(uint8_t VccPin, uint8_t LeftPin, uint8_t RightPin, uint8_t GroundPin) : Vcc(VccPin), Ground(GroundPin), Left(LeftPin), Right(RightPin) 
{
    pinMode(VccPin, OUTPUT);
    pinMode(GroundPin, OUTPUT);
    pinMode(LeftPin, OUTPUT);
    pinMode(RightPin, OUTPUT);
    this->type = Type::VccLeftRightGround;
};
Laser::Laser(uint8_t LeftPin, uint8_t RightPin) : Vcc(0), Ground(0), Left(LeftPin), Right(RightPin) 
{
    pinMode(LeftPin, OUTPUT);
    pinMode(RightPin, OUTPUT);
    this->type = Type::VccAndGround;
    this->Stop();
};
Laser::Laser(uint8_t SinglePin) : Vcc(0), Ground(0), Left(SinglePin), Right(0) 
{
    pinMode(SinglePin, OUTPUT);
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
    case Type::VccLeftRightGround:
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
    case Type::VccLeftRightGround:
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
    digitalWrite(this->Vcc, HIGH);
    digitalWrite(this->Left, LOW);
    digitalWrite(this->Right, LOW);
    digitalWrite(this->Ground, LOW);
}
void Laser::StopFour() const
{
    digitalWrite(this->Vcc, LOW);
    digitalWrite(this->Left, LOW);
    digitalWrite(this->Right, LOW);
    digitalWrite(this->Ground, LOW);
}

void Laser::StartVccGnd() const
{
    digitalWrite(this->Left, LOW);
    digitalWrite(this->Right, LOW);
}
void Laser::StopVccGnd() const
{
    digitalWrite(this->Left, HIGH);
    digitalWrite(this->Right, LOW);
}

void Laser::StartOne() const
{
    digitalWrite(this->Left, HIGH);
}
void Laser::StopOne() const
{
    digitalWrite(this->Left, LOW);
}
