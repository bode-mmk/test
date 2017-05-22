#include <iostream>
#include <chrono>

int main() {
	using namespace std::chrono;

	//現在時刻の取得
	auto now_time = std::chrono::system_clock::now();

	//標準時刻からの時差+9:00を足す
	auto now_hour = duration_cast<hours>(now_time.time_since_epoch()) % 24h + 9h;
	auto now_minute = duration_cast<minutes>(now_time.time_since_epoch()) % 60min;
	auto now_sec = duration_cast<seconds>(now_time.time_since_epoch()) % 60s;

	std::cout << "現在時刻は" << now_hour.count() << "時" << now_minute.count() << "分" << now_sec.count() << "秒です" << std::endl;

  //:TODO 年月日を取得したい
}
