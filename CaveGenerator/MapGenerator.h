#include <cstdlib>

inline int random(int min, int max) { return rand() % (max + 1 - min) + min; }

/*
	This class generates an array of characters
	that represents a tilemap.
	0 represents a rock (or dead) cell.
	1 represents a floor (or alive) cell.
*/
class MapGenerator {
public:
	MapGenerator(int width, int height) : mWidth(width), mHeight(height) {}
	
	void setIterations(int i) { mIterations = i; }
	void setDeathThreshold(int t) { mDeathThreshold = t; }
	void setBirthThreshold(int t) { mBirthThreshold = t; }
	void setChanceToStartAlive(int s) { mStartAliveChance = s; }
	void setSeed(int s) { srand(s); }

	/*
		Generates the map and returns a pointer to it.
		This class never deletes this pointer, so it
		must be handled by the application.
	*/
	char* generate();

protected:
	char* mMap = nullptr;
	int mWidth;
	int mHeight;
	int mIterations = 0;
	/*
		If the number of alive neighbouring cells
		is lower than this, the cell dies.
	*/
	int mDeathThreshold = 0;
	/*
		If the number of alive neighbouring cells
		is greater than this, the cell becomes alive.
	*/
	int mBirthThreshold = 0;
	/*
		The probability for a cell to be alive in the beginning
	*/
	int mStartAliveChance = 0;

	/* Initializes the map with died or alive cells */
	void initializeMap();
	/* Makes an iteration over all the cell map */
	void doIteration();
	int getAliveNeighbours(int x, int y);
};