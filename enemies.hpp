#ifndef ENEMIES_HPP

#define ENEMIES_HPP "ENEMIES_HPP"

#include "rsdl.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <chrono>

#define blockLength 60

#define boardXdistance 122
#define boardYdistance 176

#define enemyHealthConstValue 0.1
#define coefficientConstValue 0.9

class Data;

class Enemy{
private:
    int x = 0;
    int y = 0;
    int currentPathLocation = 0;
    Point currentCoordinate = Point(0, 0);
    double initialHealth;
    std :: string imageAddress;
    double speed;
    int killPoint;
    int reachEndPoint;
    double waveNumber;
    bool alive = 1;
    int id;
public:
    void setInitialHealth(int input);
    void setImageAddress(std :: string input);
    void setSpeed(int input);
    void setKillPoint(int input);
    void setReachEndPoint(int input);
    void setWaveNumber(int input);
    int getInitialHealth();
    double getHealth();
    void goForward(std :: vector<Point> path, int length);
    bool move(int loopDuration, std :: vector<Point> path);
    int getReachEndPoint();
    void draw(Window* window);
    Point getCoordinate();
    bool isAlive();
    void kill();
    void setId(int input);
    int getId();
};

class TheRunner : public Enemy{
private:
public:
    TheRunner(int waveNumber, int id);
};

class StubbornRunner : public Enemy{
private:
public:
    StubbornRunner(int waveNumber, int id);
};

class SuperTrooper : public Enemy{
private:
public:
    SuperTrooper(int waveNumber, int id);
};

class Scrambler : public Enemy{
private:
public:
    Scrambler(int waveNumber, int id);
};

#endif
