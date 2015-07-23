#include <cstdlib>

inline int random(int min, int max) { return rand() % (max + 1 - min) + min; }

class MapGenerator {
public:
	MapGenerator(int width, int height) : mWidth(width), mHeight(height) {}
	~MapGenerator() {}
	
	void setIterations(int i) { mIterations = i; }
	void setDeathThreshold(int t) { mDeathThreshold = t; }
	void setBirthThreshold(int t) { mBirthThreshold = t; }
	void setChanceToStartAlive(int s) { mStartAliveChance = s; }
	void setSeed(int s) { srand(s); }

	void print();
	char* generate();
protected:
	char* mMap = nullptr;
	int mWidth;
	int mHeight;
	int mIterations = 0;
	int mDeathThreshold = 0;
	int mBirthThreshold = 0;
	int mStartAliveChance = 0;

	void initializeMap();
	void doIteration();
	int getAliveNeighbours(int x, int y);
};