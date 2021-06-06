#include "functions.hpp"
#include "rsdl.hpp"
#include "data.hpp"

double distance(Point src, Point dst){
    return sqrt((src.x-dst.x)*(src.x-dst.x)+(src.y-dst.y)*(src.y-dst.y));
}

Point coordinate(Point pathLocation){
    return Point(pathLocation.x*blockLength+boardXdistance+blockLength/2, pathLocation.y*blockLength+boardYdistance+blockLength/2);
}

void addTower(Window* window, Data* data, char towerType, Point coordinate){
    Tower* tower;
    Point location = Point(coordinate.x/blockLength, coordinate.y/blockLength);
    if(towerType == addGatelingTowerKey){
        tower = new Gatling(location);
    }
    if(towerType == addMissileTowerKey){
        tower = new Missile(location);
    }
    if(towerType == addTeslaTowerKey){
        tower = new Tesla(location);
    }
    if(data->decreaseBudget(tower->getBuildPrice()))
        data->addTower(tower);
    else{
        window->show_text("not enough money", Point(8*blockLength, 5*blockLength), RED, "FreeSans.ttf", 100);
    }

}

void upgradeTower(Data* data, Point location){

}

void inputProcess(Window* window, Data* data){
    char pressedKey;
    Point mousePosition;
    while(window->has_pending_event()){
        Event event = window->poll_for_event();
        switch(event.get_type()) {
            case Event::EventType::QUIT:
                exit(0);
                break;
            case Event::EventType::KEY_PRESS:
                pressedKey = event.get_pressed_key();
                mousePosition = get_current_mouse_position();
                if(pressedKey == upgradeTowerKey)
                    upgradeTower(data, mousePosition);
                else
                    addTower(window, data, pressedKey, mousePosition);
                break;
        }
    }
}

void moveAliveEnemies(Window* window, Data* data, int duration){
    std :: vector<Enemy*> aliveEnemies = data->getAliveEnemies();
    for(int i = 0; i < aliveEnemies.size(); i++){
        if(!aliveEnemies[i]->move(duration, data->getPath())){
            data->setPlayerLife(aliveEnemies[i]->getReachEndPoint(), window);
            std :: swap(aliveEnemies[i], aliveEnemies.back());
            aliveEnemies.pop_back();
        }
    }
}

void drawLines(Window* window, Data* data){
    std :: vector<Point> path = data->getPath();
    Point current = Point(0, path[0].y);
    for(int i = 0; i < path.size(); i++){
            window->draw_line(current, path[i], RED);
            current = path[i];
    }
}

void drawEnemies(Window* window, Data* data){
    std :: vector<Enemy*> aliveEnemies = data->getAliveEnemies();
    for(int i = 0; i < aliveEnemies.size(); i++){
        aliveEnemies[i]->draw(window);
    }
}

void drawTowers(Window* window, Data* data){
    std :: vector<Tower*> towers = data->getTowers();
    for(int i = 0; i < towers.size(); i++){
        towers[i]->drawTower(window);
    }
}

std :: string lifeStringOutput(Data* data){
    return "Player Life: " + std :: to_string(data->getRemainedLife());
}

std :: string budgetStringOutput(Data* data){
    return "Player Budget: " + std :: to_string(data->getRemainedBudget());
}

void update(Window* window, Data* data, int &duration){
    window->clear();
    window->draw_img(backgroundImageAddress, NULL_RECT, NULL_RECT);
    window->show_text(lifeStringOutput(data), Point(1*blockLength, blockLength), BLACK, "FreeSans.ttf", 30);
    window->show_text(budgetStringOutput(data), Point(6*blockLength, blockLength), BLACK, "FreeSans.ttf", 30);
    drawLines(window, data);
    drawEnemies(window, data);
    drawTowers(window, data);
    window->update_screen();
}


void enemiesProcess(Window* window, Data* data, int &loopDuration, int &counter, int &newWaveDelayTime){
    data->removeKilledEnemies();
    moveAliveEnemies(window, data, loopDuration);
    if(!data->isActiveWave()){
        if(newWaveDelayTime <= 0){
            data->setActiveWave();
            newWaveDelayTime = newWaveDelay;
        }
    }
    newWaveDelayTime -= loopDuration;
    if(counter%10 == 0){
        data->addNextEnemy(newWaveDelayTime);
    }
}

void towersProcess(Window* window, Data* data, int counter){
    std :: vector<Tower*> towers = data->getTowers();
    for(int i = 0; i < towers.size(); i++){
        towers[i]->getTarget(data->getAliveEnemies());
        if(counter%(towers[i]->getAttackDuration()/loopPeriod) == 0)
            towers[i]->attack();
    }
}

void process(Window* window, Data* data, int &loopDuration, int &counter, int &newWaveDelayTime){
    inputProcess(window, data);
    enemiesProcess(window, data, loopDuration, counter, newWaveDelayTime);
    towersProcess(window, data, counter);
}

std :: vector<int> separateString(std :: string str){
    std :: vector<int> numbers;
    int i = 0;
    while(i < str.size()){
        int number = 0;
        while(i < str.size() && str[i] != ' ' && str[i] != '\n'){
            number *= 10;
            number += (int)str[i]-'0';
            i++;
        }
        numbers.push_back(number);
        i++;
    }
    return numbers;
}

Point nextBlock(Point src, Point dst){
    if(src.x == dst.x)
        return Point(src.x, src.y+1);
    return Point(src.x+1, src.y);
}

std :: vector<Point> makePath(std :: vector<int> numbers){
    std :: vector<Point> path;
    for(int i = 0; i < numbers.size(); i+=2){
        path.push_back(Point(numbers[i], numbers[i+1]));
    }
    return path;
}

void handleInput(Data* data){
    std :: fstream inputFile;
    inputFile.open(wavesInputFileAddress);
    std :: string pathString;
    getline(inputFile, pathString);
    data->setPath(makePath(separateString(pathString)));
    int counter = 0;
    while(!inputFile.eof()){
        counter++;
        std :: string waveString;
        getline(inputFile, waveString);
        if(waveString == "")
            break;
        data->setEnemyWave(separateString(waveString), counter);
    }
    data->reverseEnemyWaves();
}

void preprocess(Window* window, Data* data){
    handleInput(data);
}
