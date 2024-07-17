#include "pch.h"
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"
#include <ctime> // for std::time()

// 전역 변수
Board board;
Player player;

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	// 25 * 25짜리 board 초기화
	// 홀수를 넣어야 벽이 생성됨
	board.Init(25, &player);
	player.Init(&board);

	uint64 lastTick = 0;

	while (true)
	{
#pragma region 프레임 관리
		// 현재 시간 카운트
		const uint64 currentTick = ::GetTickCount64();
		// 다음 Tick이 발생하는 때까지 시간
		const uint64 DeltaTime = currentTick - lastTick;
		// lastTick 업데이트
		lastTick = currentTick;
#pragma endregion

		// 입력

		// 로직
		player.Tick(DeltaTime);

		// 렌더링
		board.Render();
	}
}