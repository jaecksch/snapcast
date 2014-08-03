#ifndef STREAM_H
#define STREAM_H


#include <deque>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "doubleBuffer.h"
#include "chunk.h"
#include "timeUtils.h"


class Stream
{
public:
	Stream();
	void addChunk(Chunk* chunk);
	Chunk* getNextChunk();
	time_point_ms getNextPlayerChunk(short* outputBuffer, int correction = 0);
	void getSilentPlayerChunk(short* outputBuffer);
	void getChunk(short* outputBuffer, double outputBufferDacTime, unsigned long framesPerBuffer);
	void setBufferLen(size_t bufferLenMs);

private:
	void updateChunkTime(Chunk* chunk);
	void sleepMs(int ms);

	size_t currentSample;
	int everyN;
	int sleep;
	std::deque<Chunk*> chunks;
	std::mutex mtx;
	std::mutex mutex;
	std::unique_lock<std::mutex>* pLock;
	std::condition_variable cv;
	DoubleBuffer<int>* pBuffer;
	DoubleBuffer<int>* pShortBuffer;

	int median;
	int shortMedian;
	time_t lastUpdate;
	int bufferMs;
};



#endif


