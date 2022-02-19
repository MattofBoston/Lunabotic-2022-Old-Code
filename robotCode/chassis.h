#include "movement.h"

class chassis
{
    private:
        TalonPair * __bleft;
        TalonPair * __brght;
        TalonPair * __fleft;
        TalonPair * __frght;
    public:
        chassis(bool);
        chassis(TalonPair*, TalonPair* , TalonPair*, TalonPair*);
        void setup(bool);
        void SETSPEED(double, double);
        void PIVOT(int, double);
        void SWITCHMANUAL();

};

chassis::chassis(bool isManual){
    __bleft = new TalonPair(RearLeft);
    __brght = new TalonPair(RearRight);
    __frght = new TalonPair(FrontRight);
    __fleft = new TalonPair(FrontLeft);
    setup(isManual);
    cout<<"Successfully created chassis control group"<<endl;
};
chassis::chassis(TalonPair* b_left, TalonPair* b_rght , TalonPair* f_left, TalonPair* f_rght)
{
    __bleft = b_left;
    __brght = b_rght;
    __fleft = f_left;
    __frght = f_rght;

    setup(false);

};
void chassis::SETSPEED(double _lSpeed, double _rspeed){
    __fleft->SETSPEED(_lSpeed);
    __frght->SETSPEED(_rspeed);
    __bleft->SETSPEED(_lSpeed);
    __brght->SETSPEED(_rspeed);
    cout<< "Chassis Speed Left: " <<_lSpeed << " Right: " <<_rspeed<<endl;
}

//Use int for issues regarding likely precision
//More than likely just use like time or something, or rather a boolean sensor input
void chassis::PIVOT(int angle, double speed){
    //catch invalid inputs greater than 360 and convert to valid input
    //In case angle is greater than 180, faster to turn counter clockwise instead of clockwise
    if(abs(angle % 360) > 180){
        speed = -speed;
        cout<<"Pivoting counter-clockwise at speed " <<speed <<endl;
    }else{
        cout<<"Pivoting clockwise at speed " <<speed <<endl;
    };
    
    __fleft->SETSPEED(speed);
    __frght->SETSPEED(-speed);
    __bleft->SETSPEED(speed);
    __brght->SETSPEED(-speed);

    return;
    
}
void chassis::setup(bool isManual){
    __brght->INVERT();
    __frght->INVERT();
    if(isManual){
        __brght->SWITCHMANUAL();
        __frght->SWITCHMANUAL();
        __bleft->SWITCHMANUAL();
        __frght->SWITCHMANUAL();
    }
    return;
}
