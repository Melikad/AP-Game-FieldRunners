#ifndef DATA_HPP

#define DATA_HPP "DATA_HPP"

#include "functions.hpp"
#include "enemies.hpp"
#include "towers.hpp"

#define playerInitialLife 20
#define playerInitialBudget 200

class Data{
private:
    std :: vector<std :: vector<Enemy*>> enemyWaves;
    std :: vector<Point> path;
    std :: vector<Enemy*> aliveEnemies;
    bool anyActiveWave = 0;
    int playerLife = playerInitialLife;
    int playerBudget = playerInitialBudget;
    std :: vector<Tower*> towers;
public:
    void setPath(std :: vector<Point> inputPath);
    void setEnemyWave(std :: vector<int> typesCount, int waveNumber);
    void reverseEnemyWaves();
    std :: vector<Enemy*> getAliveEnemies();
    bool isActiveWave();
    std :: vector<Point> getPath();
    void setActiveWave();
    void addNextEnemy(int &newWaveDelayTime);
    void gameOver(Window* window);
    void setPlayerLife(int killedLifePoint, Window* window);
    void addTower(Tower* tower);
    bool decreaseBudget(int money);
    std :: vector<Tower*> getTowers();
    void removeKilledEnemies();
    int getEnemiesNumber();
    int getRemainedLife();
    int getRemainedBudget();
};

#endif
