#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Item.h"
#include "Point.h"
#include "ItemManager.h"
using namespace std;

ItemManager::ItemManager(){
    last_made_tick = 0;
    delay = 3;
    growth_odd = 6;
    disappear_tick = 20;
    items = {};
}
void ItemManager::makeItem(int current_tick, const vector<vector<int>>& map){
    if(items.size() < 3 && current_tick >= last_made_tick + delay)
    {
        int temp;
        last_made_tick = current_tick;
        int rand_x;
        int rand_y;
        do{
            srand((unsigned int)time(NULL));
            temp = rand();
            rand_x = temp%18 + 1;
            temp = rand();
            rand_y = temp%18 + 1;
        }
        while(map[rand_x][rand_y]!=0);
        Point create_location = Point(rand_x,rand_y);
        temp = rand()%10;
        int kind;
        if(temp<=growth_odd){
            kind = 1;
        }else{
            kind = 2;
        }
        //Item add_item = Item(create_location, kind, current_tick);
        items.emplace_back(Item(create_location, kind, current_tick));
    }
}

int ItemManager::eatItem(const Point& next_head_point){
    for(int i = 0; i<items.size(); i++){
        if(items[i].getPos() == next_head_point) {
            if(items[i].getKinds() == 1){
                items.erase(items.begin()+i);
                return 1;
            }        
            else{
                items.erase(items.begin()+i);
                return 2;
            }
        }       
    }
    return 0;
}
void ItemManager::deleteItem(const int current_tick, GameData &game_data){
    for(int i = 0; i<items.size(); i++){
        if(items[i].getCreatedTick() + disappear_tick <= current_tick ){
            game_data.setPositionInfo(items[i].getPos().x, items[i].getPos().y, 0);
            items.erase(items.begin()+i);

        }
    }
}

void ItemManager::update(GameData &game_data, UserData &user_data){

    int current_tick = game_data.getCurrentTick();
    Point next_head_point = game_data.getNextHeadPoint();
    vector<vector<int>> map = game_data.getMap();

    makeItem(current_tick, map);
    deleteItem(current_tick, game_data);
    switch(eatItem(next_head_point))
    {
        case 0:
            break;
        case 1:
            user_data.GrowthItemIncrease();
            break;
        case 2:
            user_data.PoisonItemIncrease();
            break;
    }

    vector<Point> items_pos = {};
    vector<int> items_type = {};

    for(int i = 0; i<items.size(); i++){
        items_pos.push_back(items[i].getPos());
        items_type.push_back(items[i].getKinds());
    }

    game_data.updateItemPosition(items_pos, items_type);
}