#include "MapGenerator.h"
#include <iostream>

char* MapGenerator::generate() {
	initializeMap();
	for (int i = 0; i < mIterations; i++)
		doIteration();
	return mMap;
}

void MapGenerator::initializeMap() {
	mMap = new char[mWidth * mHeight];
	// The borders are set to zero
	memset(mMap, 0, mWidth * mHeight * sizeof(char));
	for (int y = 1; y < mHeight - 1; y++)
		for (int x = 1; x < mWidth - 1; x++)
			mMap[y*mWidth + x] = random(1, 100) < mStartAliveChance ? 1 : 0;
}

void MapGenerator::doIteration() {
	char* newMap = new char[mWidth*mHeight];
	for (int y = 0; y < mHeight; y++)
		for (int x = 0; x < mWidth; x++) {
			// Set the borders to 0
			if (x == 0 || y == 0 || x == mWidth - 1 || y == mHeight - 1) {
				newMap[y*mWidth + x] = 0;
				continue;
			}

			int aliveNeighbours = getAliveNeighbours(x, y);
			if (mMap[y*mWidth + x])
				newMap[y*mWidth + x] = aliveNeighbours < mDeathThreshold ? 0 : 1;
			else
				newMap[y*mWidth + x] = aliveNeighbours > mBirthThreshold ? 1 : 0;
		}
	delete mMap;
	mMap = newMap;
}

int MapGenerator::getAliveNeighbours(int x, int y) {
	int count = 0;
	for (int i = y - 1; i < y + 2; i++)
		for (int j = x - 1; j < x + 2; j++) {
			// Ignores itself and beyond the borders
			if (j < 0 || j > mWidth || i < 0 || i > mHeight || (i == y && j == x))
				continue;
			count += mMap[i*mWidth + j];
		}
	return count;
}