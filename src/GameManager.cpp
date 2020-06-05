#include "GameManager.h"

GameManager::GameManager(GameFlow &gameflow) : game_flow(gameflow)
{
    curStage = 0;

    games = new Game[MAX_STAGE];

    for (int i = 0; i < MAX_STAGE; i++)
    {
        games[i].Init(i);
    }
}

// 게임 시작 (첫 스테이지 시작) 시 한번
void GameManager::Start()
{
    // 첫스테이지 로드
    curGame = games;
    curGame->gameStart();
    // 스테이지1 시작 프롬프트
    if (game_flow.RenderStageEnter(curStage + 1) == 0)
    {
        curGame->isValid = false;
    }
}

void GameManager::End()
{
    //curGame->gameEnd();
}

// ui_manager 가 키 입력받고 게임에 세팅해줌
void GameManager::SetInput()
{
    curGame->SetInput();
}

// 매 프레임, 유효성 검사만
int GameManager::IsValid()
{
    return curGame->IsValid();
}

// 매 프레임, 게임데이터 업데이트
void GameManager::Update(int tick)
{
    curGame->update(tick);

    if (curGame->isClear())
    {
        curGame->gameEnd();
        StageSetting();
    }
}

// 스테이지 클리어 시 다음 스테이지 세팅, 대기창 띄워줌
void GameManager::StageSetting()
{
    // 마지막 스테이지가 아니라면
    if (++curStage < MAX_STAGE)
    {
        // 다음 스테이지 로드
        curGame = games + curStage;
        // 다음 스테이지 세팅
        curGame->gameStart();
    }

    // 해당 스테이지 클리어 렌더링, 입력대기
    if (game_flow.RenderStageClear(curStage) == 0)
    {
        // 대기중 백스페이스 눌렀을 경우 종료
        curGame->isValid = false;
    }
}