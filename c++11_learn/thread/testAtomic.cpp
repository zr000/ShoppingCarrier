#include <iostream>
#include <thread>
#include <string>
#include <atomic>
#include <vector>
#include <mutex>

using namespace std;

int main(int argc, char** argv)
{
	std::atomic_int count{ 100 };
	std::mutex printMutex;

	int nthread = std::thread::hardware_concurrency();

	vector<std::shared_ptr<std::thread>> thpool;

	for (int i = 0; i < nthread; i++) {
		thpool.push_back(std::make_shared<std::thread>([&count, &printMutex]() {

			while (true)
			{
				int t = count.fetch_sub(1);
				if (t < 0)
					break;
				std::unique_lock<std::mutex> lock(printMutex);
				cout << t << endl;
				lock.unlock();
				
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}));
	}

	for (auto &th : thpool) {
		th->join();
	}

	return 0;
}