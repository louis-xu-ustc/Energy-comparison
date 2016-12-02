//
// Created by Yunpeng Xu on 11/24/16.
//

#include <math.h>
#include <stdio.h>

#define TASK_NUM    (5)

typedef struct sysclock_task_s {
	int budget;
	int period;
} sysclock_task_t;

sysclock_task_t task_list[TASK_NUM] = {
	{800, 1000},
	{300, 1000},
	{400, 1700},
	{90, 1300},
	{10, 1600},
};

double freq_list[TASK_NUM] = {1.0, 1.0, 1.0, 1.0, 1.0};
double final_freq = 0.0;





void main(int argc, char **argv) {
	
	for (int i = 0; i < TASK_NUM; i++) {
		int period = task_list[i].period;
		for (int j = 0; j <= i; j++) {
			int p = task_list[j].period;
			for (int k = 1; k * p <= period; k++) { //10, 20, 30
				int t = k * p;
				int tmp = 0;
				for (int l = 0; l <= i; l++) {
					int tmp1 = ceil((double)t/task_list[l].period);
					int tmp2 = tmp1 * task_list[l].budget;
					tmp += tmp2;
				}
				double util = (double)tmp / t;
				if (util < freq_list[i]) {
					freq_list[i] = util;
				}
				printf("task:%d, time:%d, util:%f\n", i, t, util);
			}
		}
		printf("\n");
	}
	for (int i =0; i < TASK_NUM; i++) {
		printf("task:%d, freq:%0.2f\n", i, freq_list[i]);
		if (freq_list[i] > final_freq)
			final_freq = freq_list[i];
	}
	printf("sys-clock freq: %0.2f\n", final_freq);
	double power = 0.00442 * pow(final_freq, 1.67) + 25.72;
	printf("sysclock energy is %f\n", power);
	
	
}
