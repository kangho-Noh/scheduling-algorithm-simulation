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
	int running; //현재 실행중인 프로세스 번호
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
		running = 1;
		parr[0].status = 2;
		len++;
		while (len) {

			bool executed = false;
			for (int i = 0; i < 6; i++) {
				if (parr[i].status == 1) {
					parr[i].waiting_time++;
				}
				else if (parr[i].status == 2) {
					parr[i].burst_time--;
					if (parr[i].burst_time == 0) {
						executed = true;
						parr[i].status = 3;
						len--;
					}
				}
			}

			for (int i = 0; i < 6; i++) {
				if (time_passed == parr[i].arrival_time) {
					parr[i].status = 1;
					len++;
				}
			}

			if (time_quantum == 2 || executed) {
				//출력
				time_quantum = 0;
				//다음거 수행
			}
			time_quantum++;
			time_passed++;
		}
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
}