#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>


class Util
{
private:
	static Util* _instance;
private:

public:
	Util() {};
	~Util() {};
	static Util& Instance() {					//싱글톤
		if (_instance == nullptr)
			_instance = new Util();

		return *_instance;
	}

	//float Range(const float min, const float max) {
	//	srand((unsigned int)time(NULL));
	//	return ((max - min)*((float)rand() / RAND_MAX)) + min; //RAND_MAX 는 rand()에서 나올수있는 최대 값
	//}
	//int Range(const int min, const int max) {
	//	srand((unsigned int)time(NULL));
	//	return ((max - min)*((int)rand() / RAND_MAX)) + min;;
	//}

	 template<typename T>
	 inline T RandomRange(const T min, const T max) {

		 srand((unsigned int)time(NULL));

		 return ((max - min)*((T)rand() / RAND_MAX)) + min;;
	 }
};

