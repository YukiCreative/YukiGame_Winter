#include "Time.h"
#include <DxLib.h>

// staticメンバ変数はメンバ関数みたいに定義しないといけないっぽい
float Time::fps = 0;
float Time::deltaTime = 0;

Time& Time::GetInstance()
{
	static Time instance;
	return instance;
}

void Time::Update()
{
	fps = GetFPS();
	deltaTime = 1 / fps;
}

float Time::FPS()
{
	return fps;
}

float Time::DeltaTime()
{
	return deltaTime;
}
