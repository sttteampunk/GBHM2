#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

void obzac()
{
	std::cout << "\n//============================================================================//\n\n";
};

//tsk1
template <typename T>
void Swap(T& ptr1, T& ptr2) noexcept
{
	assert(ptr1 != ptr2);

	T temp(std::move(ptr1));
	ptr1 = std::move(ptr2);
	ptr2 = std::move(temp);
}
class Item
{
private:
	int value = 0;
public:
	Item(int input)
		: value(input)
	{

	}

	void printValue();

};

void Item::printValue()
{
	std::cout << value << std::endl;
}


//task2
template <typename T>
void SortPointers(std::vector<T*>& v)
{
	std::sort(v.begin(), v.end(), [](const T* a, const T* b) {return *a < *b; });
}

template <typename T>
void PrintVector(const std::vector<T*>& v)
{
	auto iter = v.begin();
	while (iter != v.end())
	{
		std::cout << **iter << " ";
		++iter;
	}
	std::cout << std::endl;
}

template <typename T>
void RandomFillVector(std::vector<T*>& v, int size)
{
	v.resize(size);
	auto iter = v.begin();
	while (iter != v.end())
	{
		*iter = new T;
		++iter;
	}
}

template <>
void RandomFillVector(std::vector<int*>& v, int size)
{
	std::srand(static_cast<uint16_t>(std::time(0)));
	v.resize(size);
	auto iter = v.begin();
	while (iter != v.end())
	{
		int* ptr = new int();
		*ptr = rand() % 100;
		*iter = ptr;
		++iter;
	}
}

//task3
void countVowels1()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream file("voina-i-mir.txt");
	if (!file.is_open())
	{
		std::cout << "Could not read the file!" << std::endl;
		return;
	}

	std::string vowels = "AEIOUYaeiouy";

	size_t count = std::count_if(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), [=](char x) {return vowels.find(x) != std::string::npos; });
	file.close();

	auto finish = std::chrono::high_resolution_clock::now();
	auto result = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
	std::cout << "(Count_if + find) took " << result.count() << " milliseconds.\n";
	std::cout << "Number of vowels: " << count << std::endl;
}


void countVowels2()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream file("voina-i-mir.txt");
	if (!file.is_open())
	{
		std::cout << "Could not read the file!" << std::endl;
		return;
	}

	std::string vowels = "AEIOUYaeiouy";

	size_t count = std::count_if(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), [=](char x) -> bool {for (auto chr : vowels) { if (chr == x) return true; } return false; });
	file.close();

	auto finish = std::chrono::high_resolution_clock::now();
	auto result = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
	std::cout << "(Count_if + for) took " << result.count() << " milliseconds.\n";
	std::cout << "Number of vowels: " << count << std::endl;
}

void countVowels3()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream file("voina-i-mir.txt");
	if (!file.is_open())
	{
		std::cout << "Could not read the file!" << std::endl;
		return;
	}

	std::string vowels = "AEIOUYaeiouy";
	size_t count = 0;

	for (auto it = std::istreambuf_iterator<char>(file); it != std::istreambuf_iterator<char>(); ++it)
	{
		if (vowels.find(*it) != std::string::npos) ++count;
	}

	file.close();

	auto finish = std::chrono::high_resolution_clock::now();
	auto result = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
	std::cout << "(For + find) took " << result.count() << " milliseconds.\n";
	std::cout << "Number of vowels: " << count << std::endl;
}

void countVowels4()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream file("voina-i-mir.txt");
	if (!file.is_open())
	{
		std::cout << "Could not read the file!" << std::endl;
		return;
	}

	std::string vowels = "AEIOUYaeiouy";
	size_t count = 0;

	for (auto it = std::istreambuf_iterator<char>(file); it != std::istreambuf_iterator<char>(); ++it)
	{
		for (char chr : vowels)
		{
			if (*it == chr && *it != std::string::npos) ++count;
		}
	}

	file.close();

	auto finish = std::chrono::high_resolution_clock::now();
	auto result = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
	std::cout << "(For + for) took " << result.count() << " milliseconds.\n";
	std::cout << "Number of vowels: " << count << std::endl;
}


int main()
{
	{
		obzac();
		std::unique_ptr<Item> ptr1(new Item(1488));
		std::unique_ptr<Item> ptr2(new Item(1989));
		ptr1->printValue();
		ptr2->printValue();
		swap(ptr1, ptr2);
		ptr1->printValue();
		ptr2->printValue();
		obzac();
	}

	{
		obzac();
		std::cout << "Initial vector:" << std::endl;
		std::vector<int*> ptrVector;
		RandomFillVector(ptrVector, 10);
		PrintVector(ptrVector);
		std::cout << "Sorted vector:" << std::endl;
		SortPointers(ptrVector);
		PrintVector(ptrVector);
		obzac();
	}

	{
		obzac();
		
		countVowels1();

		countVowels2();

		countVowels3();

		countVowels4();
		obzac();
	}
}