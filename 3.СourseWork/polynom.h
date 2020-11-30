#ifndef POLYNOM_H
#define POLYNOM_H


class Polynom{
public:
    float a;
    float b;
    float c;
    float d;
    float calculatePolynom(float t){
        return a * t * t * t + b * t * t + c * t + d;
    }
};

#endif // POLYNOM_H
