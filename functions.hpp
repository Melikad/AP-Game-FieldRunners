#ifndef FUNCTIONS_HPP

#define FUNCTIONS_HPP "FUNCTIONS_HPP"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <chrono>

#include "rsdl.hpp"
#include "enemies.hpp"

double distance(Point src, Point dst);
#define newWaveDelay 3000

#define backgroundImageAddress "Assets//background.png"
#define wavesInputFileAddress "waves.txt"


#define addGatelingTowerKey 'g'
#define addMissileTowerKey 'm'
#define addTeslaTowerKey 't'
#define upgradeTowerKey 'u'

double distance(Point src, Point dst);

Point coordinate(Point pathLocation);

void addTower(Window* window, Data* data, char towerType, Point coordinate);

void upgradeTower(Data* data, Point location);

void inputProcess(Window* window, Data* data);

void moveAliveEnemies(Window* window, Data* data, int duration);

void drawLines(Window* window, Data* data);

void drawEnemies(Window* window, Data* data);

void drawTowers(Window* window, Data* data);

std :: string lifeStringOutput(Data* data);

std :: string budgetStringOutput(Data* data);

void update(Window* window, Data* data, int &duration);

void enemiesProcess(Window* window, Data* data, int &loopDuration, int &counter, int &newWaveDelayTime);

void towersProcess(Window* window, Data* data, int counter);

void process(Window* window, Data* data, int &loopDuration, int &counter, int &newWaveDelayTime);

std :: vector<int> separateString(std :: string str);

Point nextBlock(Point src, Point dst);

std :: vector<Point> makePath(std :: vector<int> numbers);

void handleInput(Data* data);

void preprocess(Window* window, Data* data);

#endif
