#pragma once

/// <summary>
/// GetFPSとかを計測した結果を効率よく記憶しておきたい
/// ここまで来たらシングルトンにしようか
/// </summary>
class Time
{
private:
	Time() {}
	Time(const Time&) = delete;
	void operator=(const Time&) = delete;

	static float fps;
	/// <summary>
	/// 1フレーム処理するまでに経過した時間
	/// GetFPSの逆数をとっただけの「なんちゃって」です。
	/// </summary>
	static float deltaTime;
public:
	static Time& GetInstance();

	/// <summary>
	/// fpsやdeltaTimeを更新する
	/// 1フレームに一回だけ走らせる
	/// </summary>
	void Update();

	// これらの関数をどうしてもstaticにしてみたい
	static float FPS();
	static float DeltaTime();
};