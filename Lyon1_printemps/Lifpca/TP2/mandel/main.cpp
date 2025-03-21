/********************************************************************
 * Copyright (C) 2018                                               *
 * Initial author: Matthieu Moy                                     *
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>

#include "mandel.h"
#include "display.h"
#include <thread>
#include <vector>
#include <mutex>

#include <iostream>

// Last slice computed. The next slice to compute (the next task) is
// obtained by incrementing this variable.
static int last_slice;

using namespace std;

mutex m;
void init_iteration() {
	last_slice = 0;
}

void init () {
	srand(time(NULL));
	init_x();
}

// Function returning a screen slice to process.
int get_slice() {
	if (last_slice < number_of_slices) {
		// We use usleep to make concurrency problems visible,
		// but this code does essentially "return last_slice++".
		int val = last_slice;
		if (rand() % 2 == 0) usleep(100);
		int tmp = last_slice;
		if (rand() % 2 == 0) usleep(100);
		last_slice = tmp + 1;
		return val;
	} else {
		return -1;
	}
}


void compute_and_draw_slice(int slice_number) {
	int y;
	bool warning_emitted = false;
	
	if (verbose > 0)
		std::cout << "Starting slice " << slice_number << std::endl;
	for (y = 0; y < height; y += rect_height) {
		compute_rect(slice_number, y, warning_emitted);
		// Try replacing the following by "draw_rect" (without _thread_safe):
		draw_rect_thread_safe(slice_number, y);
	}
	if (verbose > 0)
		std::cout << "Finished slice " << slice_number << std::endl;
}


void draw_screen_worker() {
	while (1) {
		m.lock();
		int i = get_slice();
		m.unlock();
		if (i == -1)
			return;
		compute_and_draw_slice(i);
	}
}

/* Multi-threaded version of draw_screen_sequential.
   Returns the number of slices computed (sum of all threads) */
int draw_screen_thread() {
	std::cout << "draw_screen_thread not yet implemented" << std::endl;
	 vector<thread> vec_thread;

  for(int i=0; i < number_of_threads; i++){
    vec_thread.push_back(thread(draw_screen_worker));
  }
  for(int i = 0; i < number_of_threads; i++){
    vec_thread[i].join();

  }
	return number_of_threads;
}

void draw_screen_sequential() {
	int i;
	for (i = 0; i < number_of_slices; i++) {
		compute_and_draw_slice(i);
	}
}

void usage(int /*argc*/, char ** argv) {
	std::cout << "usage: " << argv[0] << " [-h|-?|--help] [--verbose] [--resize] [--slow] [--loop] "
		  << "[--nb-threads NBT] [--nb-slices NBS]"
		  << std::endl << std::endl;
	exit(EXIT_SUCCESS);
}

void parse_command_line(int argc, char ** argv) {
	bool usage_required = false;
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--help") ||
		    !strcmp(argv[i], "-h") ||
		    !strcmp(argv[i], "-?"))
			usage_required = true;
		else if (!strcmp(argv[i], "--verbose")) verbose++;
		else if (!strcmp(argv[i], "--resize")) auto_resize = true;
		else if (!strcmp(argv[i], "--slow"))   slow++;
		else if (!strcmp(argv[i], "--loop"))   auto_loop = true;
		else if (!strcmp(argv[i], "--nb-threads")) {
			i++;
			use_threads = true;
			number_of_threads = atoi(argv[i]);
		} else if (!strcmp(argv[i], "--nb-slices")) {
			i++;
			number_of_slices = atoi(argv[i]);
		} else {
			std::cout << "ERROR: Unknown option: " << argv[i] << std::endl;
			usage_required = true;
		}
	}
	if (usage_required)
		usage(argc, argv);
}

double timevalsub(struct timeval *tv1, const struct timeval *tv2) {
	double res = 0;
	res = tv2->tv_sec - tv1->tv_sec;
	res += (tv2->tv_usec - tv1->tv_usec)*1.0/1000000;
	return res;
}

int main(int argc, char ** argv) {
	parse_command_line(argc, argv);

	std::cout << "auto_resize: " << auto_resize << std::endl;
	std::cout << "slow: " << slow << std::endl;
	std::cout << "auto_loop: " << auto_loop << std::endl;
	std::cout << "number_of_threads: " << number_of_threads << std::endl;
	std::cout << "number_of_slices: " << number_of_slices << std::endl;

	/* Nice zooms to look at :-) */
	/*
	x_min = 0.29725;
	x_max = 0.298;
	y_min = 0.016;
	y_max = 0.0165;
	*/
	/*
	x_min = -0.474453;
	y_min = -0.632657;
	x_max = -0.474449;
	y_max = -0.632652;
	*/

	init();
	while(1) {
		struct timeval time_start, time_end;
		int err;
		clock_t start, end;
		init_iteration();

		clear_screen();

		/* Start clock */
		start = clock();
		err = gettimeofday(&time_start, NULL);
		if (err != 0) {
			perror("gettimeofday");
			exit(EXIT_FAILURE);
		}

		/* The computation itself */
		if (use_threads) {
			int n = draw_screen_thread();
			if (n != number_of_slices) {
				std::cout << "ERROR: Wrong number of slices computed: "
					  << n << " (should be " << number_of_slices << ")"
					  << std::endl;
			}
		} else {
			draw_screen_sequential();
		}

		/* End clock */
		end = clock();
		err = gettimeofday(&time_end, NULL);
		if (err != 0) {
			perror("gettimeofday");
			exit(EXIT_FAILURE);
		}
		double duration = timevalsub(&time_start, &time_end);
		
		std::cout << "Computation time (CPU time): "
			  << (double) (end - start) / CLOCKS_PER_SEC
			  << " seconds. Elapsed time: "
			  << duration << " seconds."
			  << std::endl;


		sleep(1);
		if (auto_resize) resize_according_to_mouse();
		if (! auto_loop) exit(0);
	}
}
