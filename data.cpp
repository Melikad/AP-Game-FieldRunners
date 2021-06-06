#include "data.hpp"

void Data :: setPath(std :: vector<Point> inputPath){
    path.clear();
    for(int i = 0; i < inputPath.size(); i++){
        path.push_back(Point(inputPath[i].x*blockLength+boardXdistance+blockLength/2,
                            inputPath[i].y*blockLength+boardYdistance+blockLength/2));
    }
}

int Data :: getEnemiesNumber(){
    int enemiesNumber = 0;
    for(int i = 0; i < enemyWaves.size(); i++){
        enemiesNumber += enemyWaves[i].size();
    }
    return enemiesNumber;
}

void Data :: setEnemyWave(std :: vector<int> typesCount, int waveNumber){
    int id = getEnemiesNumber();
    std :: vector<Enemy*> enemyWave;
    for(int i = 0; i < 4; i++){
        while(typesCount[i]){
            typesCount[i]--;
            Enemy* enemy;
            if(i == 0){
                enemy = new TheRunner(waveNumber, id);
            }
            if(i == 1){
                enemy = new StubbornRunner(waveNumber, id);
            }
            if(i == 2){
                enemy = new SuperTrooper(waveNumber, id);
            }
            if(i == 3){
                enemy = new Scrambler(waveNumber, id);
            }
            enemyWave.push_back(enemy);
        }
    }
    random_shuffle(enemyWave.begin(), enemyWave.end());
    enemyWaves.push_back(enemyWave);
}

void Data :: reverseEnemyWaves(){
    reverse(enemyWaves.begin(), enemyWaves.end());
}

std :: vector<Enemy*> Data ::  getAliveEnemies(){
    return aliveEnemies;
}

bool Data ::  isActiveWave(){
    return anyActiveWave;
}

std :: vector<Point> Data ::  getPath(){
    return path;
}

void Data :: setActiveWave(){
    if(enemyWaves.back().size() == 0)
        enemyWaves.pop_back();
    anyActiveWave = 1;
}

void Data :: addNextEnemy(int &newWaveDelayTime){
    if(!anyActiveWave)
        return;
    if(enemyWaves.empty())
        return;
    Enemy* next = enemyWaves.back().back();
    enemyWaves.back().pop_back();
    aliveEnemies.push_back(next);
    if(enemyWaves.back().empty()){
        newWaveDelayTime = newWaveDelay;
        anyActiveWave = 0;
    }
}

void Data :: gameOver(Window* window){
    window->show_text("YOU LOSE", Point(1*blockLength, blockLength), BLACK, "FreeSans.ttf", 120);
    exit(0);
}

void Data :: setPlayerLife(int killedLifePoint, Window* window){
    playerLife -= killedLifePoint;
    if(playerLife <= 0){
        gameOver(window);
    }
}

void Data :: addTower(Tower* tower){
    towers.push_back(tower);
}

bool Data :: decreaseBudget(int money){
    if(playerBudget-money < 0)
        return 0;
    playerBudget -= money;
}


std :: vector<Tower*> Data :: getTowers(){
    return towers;
}

void Data :: removeKilledEnemies(){
    for(int i = 0; i < aliveEnemies.size(); i++){
        if(!aliveEnemies[i]->isAlive()){
            std :: swap(aliveEnemies[i], aliveEnemies.back());
            aliveEnemies.pop_back();
        }
    }
}

int Data :: getRemainedLife(){
    return playerLife;
}

int Data :: getRemainedBudget(){
    return playerBudget;
}
