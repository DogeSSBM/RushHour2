#pragma once

char grid[GRIDLEN][GRIDLEN];

void printGrid(void)
{
	for(uint y = 0; y < GRIDLEN; y++){
		for(uint x = 0; x < GRIDLEN; x++){
			putchar(grid[x][y]);
		}
		putchar('\n');
	}
}

bool isValidChar(const int c)
{
	if(c == '-')
		return true;
	for(uint i = 0; i < NUMCAR; i++){
		if(c == carArr[i].letter)
			return true;
	}
	return false;
}

bool parseLevelFile(File *f)
{
	if(flen(f) < 42){
		printf("Levels should be >= 42bytes\n");
		printf("Size of file: %ld\n", flen(f));
	}
	rewind(f);
	int c;
	for(uint y = 0; y < 6; y++){
		for(uint x = 0; x < 6; x++){
			c = fgetc(f);
			if(!isValidChar(c))
				return false;
			grid[x][y] = c;
		}
		c = fgetc(f);
		if(c != '\n' && y != 5)
			return false;
	}
	return true;
}

void loadGrid(const char *levelStr)
{
	if(strlen(levelStr) > 2){
		printf("strlen(LevelStr) incorrect len.\n");
		printf("LevelStr: %s\n", levelStr);
		exit(1);
	}
	char path[] = "./lvls/00";
	sprintf(path, "./lvls/%s", levelStr);
	File *f = fopen(path, "r");
	if(f == NULL){
		printf("could not open path: %s\n", path);
		exit(1);
	}
	if(!parseLevelFile(f)){
		printf("Error parsing level file\n");
	}
	printGrid();
}

// grid position to screen pixel location
uint gridToScreen(const uint pos)
{
	return SCALE*pos;
}

// screen pixel location to grid position
uint screenToGrid(const uint pos)
{
	return pos/SCALE;
	//return pos/SCALE + (pos%SCALE > HSCALE);
}

void moveCarGrid(Car *car, const Direction dir)
{

}
