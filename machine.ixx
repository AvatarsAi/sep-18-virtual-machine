export module machine;
//This module contains the simulated hardware of the project
//In respect to my possibly incomplete knowleadge of computer enginnering
//i choose to work with words not bit, assuming 64bits == 1 word
//floating points not supported in this version

import <chrono>;
import <utility>;
import <cstdint>;

namespace Machine {
	//Somethings to get from this namespace
	//Only identifiers/names beginning with uppercase will be exported,
	//anything else is "local" to this namespace

	class clock {
		//The CPU Clock
	public:
		clock() = default;
		 std::pair<std::int64_t, bool> counter(int rate = 214748364) {
			//counter(int) is use to simulate a wait pause in milliseconds "if possible"
			//The wait pause is use in the clock of the cpu

			auto t1 = std::chrono::high_resolution_clock::now(); //t1 starts
			for (int x = 0; x < rate; ++x); //simulated "expensive" operation
			auto t2 = std::chrono::high_resolution_clock::now(); //t2 starts, meaning t1 "ends"

			if (std::int64_t res = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()) {
				//res takes the difference, in milliseconds, if possible of both t1 and t2 using duration_cast
				[[likely]] return std::pair<std::int64_t, bool>{res, true};
			}
			[[unlikely]] return std::pair<int, bool>{0, false};
		}


	};

	class Alu { //The arthmetic logic unit

		//storage are defined in terms of word
		//assuming 64bit is one word
		using storage = std::int64_t;
		storage first{};
		storage second{};
		storage accumulator{}; //store result of arithmetic
	
		
	public:

		Alu(storage f1, storage f2) :first{ f1 }, second{ f2 } {}

		// i have abstrated away things like half adders and full adders 
		//there are complex to implement on a 64bit arch. but not impossible
		////overflow and underflow safety is present in all arithmetic types

		storage ADD() {
			this->accumulator = storage{ first + second };
			return this->accumulator;
		}

		storage SUB() {
			this->accumulator = storage{ first - second };
			return this->accumulator;
		}

		storage MUL() {
			this->accumulator = storage{ first * second };
			return this->accumulator;
		}
		
		storage DIV() {
			this->accumulator = storage{ first / second };
			return this->accumulator;
		}

		//logical unit
		bool is_equal(storage first, storage second) { return first == second; }
		bool one_is_greater(storage first, storage second) { return first > second; }
		bool second_is_greater(storage first, storage second) { return second > first; }
		bool one_is_non_zero(storage first, storage second) { return first != 0; }

		
	};

	class CPU {
	public:
		CPU() = default;
	private:

	};


	constexpr int MyFunc() {
		return 10;
	}

}

export constexpr  int Machine::MyFunc();