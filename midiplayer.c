/* Licensed under the MIT License
 * Copyright (c) 2023 Smgdream */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <vfw.h>

// gcc -lvfw32

int main(int argc, char *argv[])
{	
	//wchar_t *wfilename = (wchar_t *)TEXT("C:\\Users\\Nimoe\\Desktop\\song.mid");
	//HWND midi = MCIWndCreate(GetForegroundWindow(), GetModuleHandle(0), WS_CHILD | 8, t);

	if (argv[1] == NULL
	 || !strcmp(argv[1], "/?")
	 || !strcmp(argv[1], "-h")
	 || !strcmp(argv[1], "--help")
	 || !strcmp(argv[1], "help")) {
		printf("midiplayer MIDI_FILEMANE\n");
		return 0;
	}

	printf("Loading midi file...\nplease wait\n");
	HWND midi = MCIWndCreate(NULL, GetModuleHandle(0), 8, argv[1]);
	
	if (MCIWndCanPlay(midi))
	{
		MCIWndPlay(midi);

		printf("After the end of midi press any key to exit\n");
		system("pause > null");
	} else {
		fprintf(stderr, "Play file error: %s\n", argv[1]);
	}

	return 0;
}
