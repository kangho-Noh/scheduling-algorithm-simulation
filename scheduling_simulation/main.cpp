#include <iostream>
using namespace std;

struct Process {
	int PID;
	float arrival_time;
	float burst_time;
	float waiting_time;
	int status; // 0이면 아직 도착 안한 상태, 1이면 도착은 했지만 기다리는 상태, 2면 실행중, 3이면 수행 완료
	Process() {
		PID = 0;
		arrival_time = 0;
		burst_time = 0;
		waiting_time = 0;
		status = 0;
	}
	Process(int pid, float arrive, float burst) {
		PID = pid;
		arrival_time = arrive;
		burst_time = burst;
		waiting_time = 0;
		status = 0;
	}
};

struct RR {
	int running; //현재 실행중인 프로세스 인덱스
	int time_quantum;
	int len; // 기다리는 프로세스 개수 + 실행중인 프로세스 개수 =0이면 종료
	int time_passed; // 시작한 뒤 지난 시간
	RR() {
		running = 0;
		time_quantum = 0;
		len = 0;
		time_passed = 0;
	}
	void run(Process* parr) {
		cout << "=========================\n";
		cout << "=======Round Robin=======\n";
		cout << "=========================\n";
		cout << "\n\n=== now time : " << time_passed << " ===\n";
		cout << "PID" << parr[0].PID << " is running.\n";
		cout << "PID" << parr[running].PID << "'s remaining burst time : " << parr[running].burst_time;
		cout << '\n';
		parr[0].status = 2;
		running = 0;
		len++;
		while (1) {
			for (int i = 1; i < 6; i++) {
				if (time_passed == parr[i].arrival_time) {
					parr[i].status = 1;
					len++;
				}
			}

			if (parr[running].burst_time == 0) {
				cout << "\n\n=== now time : " << time_passed << " ===\n";
				cout << "<PID" << parr[running].PID << " has been executed.>\n";
				time_quantum = 0;
				parr[running].status = 3;
				len--;
				if (!len) break;
				while (1) {
					running = (running + 1) % 6;
					if (parr[running].status == 1) {
						parr[running].status = 2;
						break;
					}
				}
				cout << "PID" << parr[running].PID << " is running.\n";
				cout << "PID" << parr[running].PID << "'s remaining burst time : " << parr[running].burst_time;
				cout << '\n';
			}

			else if (time_quantum == 3) {
				time_quantum = 0;
				parr[running].status = 1;
				while (1) {
					running = (running + 1) % 6;
					if (parr[running].status == 1) {
						parr[running].status = 2;
						break;
					}
				}
				cout << "\n\n=== now time : " << time_passed << " ===\n";
				cout << "PID" << parr[running].PID << " is running.\n";
				cout << "PID" << parr[running].PID << "'s remaining burst time : "<<parr[running].burst_time;
				cout << '\n';
			}
			
			for (int i = 0; i < 6; i++) {
				if (parr[i].status == 1) {
					parr[i].waiting_time++;
				}
				else if (parr[i].status == 2) {
					parr[i].burst_time--;
					
				}
			}
			
		
			time_quantum++;
			time_passed++;
			
		}
		cout << "\n== Average waiting time ==\n";
		float sum = 0;
		for (int i = 0; i < 6; i++) {
			cout << "PID" << i + 1 << " waiting time : " << parr[i].waiting_time << '\n';
			sum += parr[i].waiting_time;
		}
		cout << "\nAverage waiting time : " << sum / 6 << '\n';
	}
};

int main() {
	Process process[6] = {
		Process(1,0,10),
		Process(2,3,12), 
		Process(3,7,4), 
		Process(4,10,6), 
		Process(5,14,8), 
		Process(6,15,7)
	};
	Process* process_arr1 = new Process[6];
	Process* process_arr2 = new Process[6];
	Process* process_arr3 = new Process[6];
	for (int i = 0; i < 6; i++) {
		process_arr1[i] = process[i];
		process_arr2[i] = process[i];
		process_arr3[i] = process[i];
	}

	//FCFS

	//SRTF

	//RR
	RR RRapp;
	RRapp.run(process_arr3);
	cout << "끝\n";
	return 0;
}