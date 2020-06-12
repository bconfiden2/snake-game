#include "Mission.h"
#include "GameSettings.h"

Mission::Mission(const int stage){
    total_mission_list = {
        {5,5,3,3},
        {7,5,9,3},
        {10,4,7,4},
        {5,1,2,1}
    };
    current_mission_list = total_mission_list[stage];
    current_state = {0, 0, 0, 0};
    current_mission_state = {false, false, false, false};

    window = newwin((MAP_Y + 1) / 2, MAP_X, 11, 44);
}

bool Mission::isComplete(UserData &user_data){
    bool isComplete = true;
    current_state = {user_data.getMaxLength(), user_data.getGrowthItemCount(), user_data.getPoisonItemCount(), user_data.getUsedGateCount()};
    for(int i = 0; i<4; i++){
        if(current_state[i] < current_mission_list[i])
        {
            current_mission_state[i] = false;
            isComplete = false;
        }
        else
        {
            current_mission_state[i] = true;
        }
    }
    return isComplete;
}

void Mission::Render()
{
    wborder(window, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    mvwprintw(window, 1, 1, "------MISSION------");
    mvwprintw(window, 3, 1, "B : %-2d (%c)", current_mission_list[0], current_mission_state[0] ? 'v' : ' ');
    mvwprintw(window, 4, 1, "+ : %-2d (%c)", current_mission_list[1], current_mission_state[1] ? 'v' : ' ');
    mvwprintw(window, 5, 1, "- : %-2d (%c)", current_mission_list[2], current_mission_state[2] ? 'v' : ' ');
    mvwprintw(window, 6, 1, "G : %-2d (%c)", current_mission_list[3], current_mission_state[3] ? 'v' : ' ');
    wrefresh(window);
}