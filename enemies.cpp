#include "enemies.hpp"

void Enemy :: setInitialHealth(int input){
    initialHealth = input;
}

void Enemy :: setImageAddress(std :: string input){
    imageAddress = input;
}

void Enemy :: setSpeed(int input){
    speed = input;
}

void Enemy :: setKillPoint(int input){
    killPoint = input;
}

void Enemy :: setReachEndPoint(int input){
    reachEndPoint = input;
}

void Enemy :: setWaveNumber(int input){
    waveNumber = input;
}

int Enemy ::  getInitialHealth(){
    return initialHealth;
}

double Enemy :: getHealth(){
    return (coefficientConstValue + enemyHealthConstValue * waveNumber) + initialHealth;
}

void Enemy :: goForward(std :: vector<Point> path, int length){
    if(currentPathLocation+1 == path.size()){
        x = path.back().x;
        y = path.back().y;
        return;
    }
    x += std::min(length, path[currentPathLocation+1].x-x)*
            (path[currentPathLocation+1].x > path[currentPathLocation].x? 1: -1);
    length -= abs(x-currentCoordinate.x);
    currentCoordinate.x = x;
    if(length == 0)
        return;
    y += std::min(length, path[currentPathLocation+1].y-y)*
            (path[currentPathLocation+1].y > path[currentPathLocation].y? 1: -1);
    length -= abs(y-currentCoordinate.y);
    currentCoordinate.y = y;
    if(length == 0)
        return;
    currentPathLocation++;
    goForward(path, length);
    return;
}

bool Enemy :: move(int loopDuration, std :: vector<Point> path){
    if(currentCoordinate.x == 0 && currentCoordinate.y == 0)
        currentCoordinate = Point(0, path[0].y), y = path[0].y;
    if(x == path.back().x && y == path.back().y){
        return 0;
    }
    goForward(path, loopDuration*speed/1000);
    return 1;
}

int Enemy :: getReachEndPoint(){
    return reachEndPoint;
}

void Enemy :: draw(Window* window){
    window->draw_img(imageAddress, Rectangle(Point(x-blockLength/2, y-blockLength/2), blockLength, blockLength));
}

Point Enemy :: getCoordinate(){
    return Point(x, y);
}

bool Enemy :: isAlive(){
    return alive;
}

void Enemy :: kill(){
    alive = 0;
}

void Enemy :: setId(int input){
    id = input;
}

int Enemy :: getId(){
    return id;
}

TheRunner :: TheRunner(int waveNumber, int id){
    setInitialHealth(250);
    setImageAddress("Assets//enemies//runner.png");
    setSpeed(50);
    setKillPoint(6);
    setReachEndPoint(1);
    setWaveNumber(waveNumber);
    setId(id);
}

StubbornRunner :: StubbornRunner(int waveNumber, int id){
    setInitialHealth(400);
    setImageAddress("Assets//enemies//stubborn-runner.png");
    setSpeed(30);
    setKillPoint(1);
    setReachEndPoint(4);
    setWaveNumber(waveNumber);
    setId(id);
}

SuperTrooper :: SuperTrooper(int waveNumber, int id){
    setInitialHealth(500);
    setImageAddress("Assets//enemies//supertrooper.png");
    setSpeed(25);
    setKillPoint(8);
    setReachEndPoint(4);
    setWaveNumber(waveNumber);
    setId(id);
}

Scrambler :: Scrambler(int waveNumber, int id){
    setInitialHealth(100);
    setImageAddress("Assets//enemies//scrambler.png");
    setSpeed(90);
    setKillPoint(4);
    setReachEndPoint(2);
    setWaveNumber(waveNumber);
    setId(id);
}
