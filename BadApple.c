#include <stdio.h>
#include <Windows.h>
#include "Melody.h"

#define START_DELAY 1000

DWORD WINAPI playTrack(LPVOID lpParam) {
	Track* track = (Track*)lpParam;

	for (int i = 0; i < track->arraySize; i++) {
		unsigned int freq = track->freqs[i];
		unsigned int dur = track->durs[i] / 100;

		if (freq > 0) {
			Beep(freq, dur);
		}
		else {
			Sleep(dur);
		}
	}

	return 0;
}

int main() {

	HANDLE threads[TRACKS];

	Sleep(START_DELAY);

	printf("Bad Apple!!\n");

	// Create a thread for each track
	for (int i = 0; i < TRACKS; i++) {
		threads[i] = CreateThread(
			NULL,
			0,
			playTrack,
			&tracks[i],
			0,
			NULL
		);

		if (threads[i] == NULL) {
			printf("Error creating thread %d\n", i);
			return 1;
		}
	}

	WaitForMultipleObjects(TRACKS, threads, TRUE, INFINITE);

	for (int i = 0; i < TRACKS; i++) {
		CloseHandle(threads[i]);
	}

	return 0;
}