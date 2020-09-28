#include<iostream>;
#include<string>;
#include<cmath>;
#include<vector>
#include<time.h>;

int cg = 1000; // Count of generation
const double PI = acos(-1.0);
int num_of_gen;
int random_int_number = time(0)/10000;
double random_double_result;
std::vector<int> counter_intervals;
int mod = 99991;

void set_rand_number(int&, int);
void set_rand_result(double&, double);

void gen_0();
void gen_1();
void gen_2();
void gen_3();
void gen_4();
void gen_5();
void gen_6();
void gen_7();
void gen_8();
void gen_9();

void simple_counter(std::vector<int>&);
void normal_counter(std::vector<int>&);
void other_counter(std::vector<int>&);

void simple_printer_result();
void normal_printer_result();
void other_printer_result();

int main() {
	std::cout << "Choose the number of generation from 0 to 9: ";
	std::cin >> num_of_gen;

	void(*counter)(std::vector<int>&);
	void(*printer_relust)();

	if (num_of_gen < 5 || num_of_gen == 6) {
		if (num_of_gen == 6) {
			cg /= 2;
		}
		counter = simple_counter;
		printer_relust = simple_printer_result;
		counter_intervals = { 0,0,0,0,0,0,0,0,0,0 };
		
	}
	else if (6 < num_of_gen && num_of_gen < 9) {
		counter = normal_counter;
		printer_relust = normal_printer_result;
		counter_intervals = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	}
	else {
		counter = other_counter;
		printer_relust = other_printer_result;
		counter_intervals = { 0,0,0,0,0,0,0,0,0,0 };
	}
	void(*selected_gen[10])() = {gen_0,gen_1,gen_2,gen_3,gen_4,gen_5,gen_6,gen_7,gen_8,gen_9};

	for (int i = 0; i < cg ;i++) {
		selected_gen[num_of_gen]();
		counter(counter_intervals);
	}
	printer_relust();
	return 0;
}

// All setters ------------------------------------------------------------------------------------------------------------------------------------------------------------

void set_rand_number(int& random_number, int result) {
	random_number = result;
}
void set_rand_result(double& random_result, double result) {
	random_result = result;
}

// All counters -----------------------------------------------------------------------------------------------------------------------------------------------------------
void simple_counter(std::vector<int>& counter_intervals) {
	
	for (int i = 0; i < 10; i++) {
		if (i / 10.0 <= random_double_result && random_double_result < (i + 1) / 10.0) {
			counter_intervals[i] += 1;
			break;
		}
	}
	
}

void normal_counter(std::vector<int>& counter_intervals) {
	for (int i = 0; i < 12; i++) {
		if ((-3+(i/2.0)) <= random_double_result && random_double_result < (-3 + ((i + 1) / 2.0))) {
			counter_intervals[i] += 1;
			break;
		}
	}

}

void other_counter(std::vector<int>& counter_intervals) {
	for (int i = 0; i < 10; i++) {
		if ((i * 10.0) <= random_double_result && random_double_result < (i + 1) * 10.0) {
			counter_intervals[i] += 1;
			break;
		}
	}

}

// All printers -----------------------------------------------------------------------------------------------------------------------------------------------------------

void simple_printer_result() {
	double sum = 0;
	cg = 1000; 
	for (int i = 0; i < 10; i++) {
		std::cout << "[0." << i << " ; 0." << i+1 << "]" << "----------" << (float)counter_intervals[i] / cg << std::endl;
		sum += counter_intervals[i];
	}
	std::cout << sum;
}

void normal_printer_result() {
	double sum = 0;
	for (int i = 0; i < 12; i++) {
		std::cout << "[" << -3 + (i / 2.0) << " ; " << -3 + ((i+1) / 2.0) << "]" << "----------" << (float)counter_intervals[i] / cg << std::endl;
		sum += counter_intervals[i];
	}
	std::cout << sum;
}

void other_printer_result() {
	double sum = 0;
	for (int i = 0; i < 10; i++) {
		std::cout << "[" << i*10 << " ; " << (i+1)*10 << "]" << "----------" << (float)counter_intervals[i] / cg << std::endl;
		sum += counter_intervals[i];
	}
	std::cout << sum;
}


// All generations of random number ---------------------------------------------------------------------------------------------------------------------------------------

// 1.Linear congruent method
void gen_0() {
	int tmp_result = (23 * random_int_number + 101) % mod;
	set_rand_number(random_int_number,tmp_result);

	double result = (double) tmp_result / mod; 
	set_rand_result(random_double_result, result);

}

// 2.Quadratic congruent method
void gen_1() {
	int pow_rand_2 = pow(random_int_number, 2);
	int tmp_result = (24 * pow_rand_2 + 23*random_int_number + 101) % mod;
	set_rand_number(random_int_number, tmp_result);

	double result = (double)tmp_result / mod;
	set_rand_result(random_double_result, result);
	
}

// 3.Fibonacci numbers
void gen_2() {
	static int tmp;
	static int tmp_result;
	static int tmp_result_back = 0; 
	if (!tmp_result_back) {
		tmp_result_back = random_int_number;
		tmp_result = (2 * tmp_result_back) % mod;
	}
	tmp = tmp_result_back;
	tmp_result_back = tmp_result;
	tmp_result = (random_int_number + tmp_result_back) % mod;
	set_rand_number(random_int_number, tmp_result);

	double result = (double)tmp_result / mod;
	set_rand_result(random_double_result, result);
	
}

// 4.Inverse congruent sequence
void gen_3() {
	static bool first_up = true;
	if (first_up) {
		random_int_number = 1;
		first_up = false;
	}
	int mod_num = pow(2, 16);
	double reverse_number = pow(random_int_number, -1);
	int tmp_result = (int)(65537* reverse_number + 65538) % mod_num;
	set_rand_number(random_int_number, tmp_result);

	double result = tmp_result / mod_num;
	set_rand_result(random_double_result, result);
}

// 5.The method of integration
void gen_4() {
	gen_0();
	int first_arg = random_int_number;
	gen_3();
	int second_arg = random_int_number;
	int tmp_result = (abs(second_arg-first_arg)) % mod;
	set_rand_number(random_int_number, tmp_result);

	double result = (double)tmp_result / mod;
	set_rand_result(random_double_result, result);
}

// 6.Rule 3 sigma
void gen_5() {
	double sum = 0;
	int _count_of_sum = 12;
	for (int i = 0; i < _count_of_sum; i++) {
		gen_0();
		sum += random_double_result;
	}
	double tmp_result = sum - _count_of_sum/2;
	set_rand_result(random_double_result, tmp_result);
}

// 7.Polar coordinate method
void gen_6() {
	double S = 0, V1, V2;
	do{
		gen_2();
		V1 = pow(2 * random_double_result - 1, 2);
		gen_2();
		V2 = pow(2 * random_double_result - 1, 2);
		S = V1 + V2;
	} while (S >= 1);
	double tmp_result = V1 * sqrt(-2 * log(S) / S);
	set_rand_result(random_double_result, tmp_result);
	normal_counter(counter_intervals);

	tmp_result = V1 * sqrt(-2 * log(S) / S);
	set_rand_result(random_double_result, tmp_result);

}

// 8.Correlation method
void gen_7() {
	double tmp_result =0;
	double U = 0, V = 0;
	do {
		gen_0();
		U = random_double_result;
		gen_0();
		V = random_double_result;
		tmp_result = sqrt(8 / exp(1)) * ((V - 0.5) / U);
	} while (!(pow(tmp_result, 2) <= -4 * log(U)));
	set_rand_result(random_double_result, tmp_result);
}

// 9.Logarithm method for generating an indicative distribution
void gen_8() {
	gen_0();
	double U = random_double_result, mu = 1.5;;
	double tmp_result = -mu * log(U);
	set_rand_result(random_double_result, tmp_result);

}

// 10.Ahrens method
void gen_9() {
	double U=0, V=0,Y=0, tmp_result=0;
	int a = 3;
	do {
		gen_0();
		U = random_double_result;
		gen_0();
		V = random_double_result;
		Y = tan(PI * U);
		tmp_result = sqrt(2 * a - 1) * Y + a - 1;
	} while (tmp_result <= 0 || V > (1 + pow(Y, 2) * exp((a - 1) * log(tmp_result / (a - 1)) - sqrt(2 * a - 1) * Y)));
	set_rand_result(random_double_result, tmp_result);

}
