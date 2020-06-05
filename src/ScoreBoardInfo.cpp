#include "ScoreBoardInfo.h"

ScoreBoardInfo::ScoreBoardInfo() 
{ 
    current_length = 3; 
    max_length = 3; 
    growth_item_count = 0; 
    poison_item_count = 0; 
    used_gate_count = 0; 
}

int ScoreBoardInfo::getCurrentLength(){//현재 길이 반환
    return current_length;
}
void ScoreBoardInfo::setCurrentLength(int current_length){ //현재 길이 설정
    this -> current_length = current_length;
    ScoreBoardInfo::setMaxLength(current_length);
}
int ScoreBoardInfo::getMaxLength(){ //최대 길이 반환
    return max_length;
}
void ScoreBoardInfo::setMaxLength(int current_length){ //최대 길이 설정
    this -> max_length = (this -> max_length, current_length);
    if(current_length>max_length) max_length=current_length;
}
int ScoreBoardInfo::setGrowthItemCount(int growth_item_count){ //성장아이템 먹은 횟수 반환
    return growth_item_count;
}
void ScoreBoardInfo::getGrowthItemCount(){ //성장아이템 먹은 횟수 설정
    this -> growth_item_count = growth_item_count;
}
int ScoreBoardInfo::setPoisonItemCount(int poison_item_count){ //감소아이템 먹은 횟수 반환
    return poison_item_count;
}
void ScoreBoardInfo::getPoisonItemCount(){ //감소아이템 먹은 횟수 설정
    this -> poison_item_count = poison_item_count;
    
}
int ScoreBoardInfo::setUsedGateCount(int used_gate_count){ //게이트를 사용한 횟수 반환
    return used_gate_count;
}
void ScoreBoardInfo::getUsedGateCount(){ //게이트를 사용한 횟수 설정
    this -> used_gate_count = used_gate_count;
};