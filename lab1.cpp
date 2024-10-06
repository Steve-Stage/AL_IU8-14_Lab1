/*
	Лабораторная работа 1

	Вариант 11

	Кубическое уравнение. Заданы три корня кубического уравнения: x1, x2, x3. Найти коэффициенты этого уравнения.
*/

#include <iostream>
#include <cinttypes>
#include <numeric>
#include <string>
#include <vector>
#include <utility>

#define abs(a) (((a) >= 0) ? (a) : -(a))

std::pair<int64_t, int64_t> as_frac(double n) // Преобразование типа double в дробь (пару целых чисел)
{
	int64_t sign = (n >= 0.0) ? (1) : (-1);
	n = abs(n);
	double ism = 1e-6;
	int64_t a, b = 1;
	a = int64_t(n);
	double fr = n - double(a);
	std::vector<int64_t> v = { a };
	int cntr = 0;
	while (fr > ism)
	{
		if (cntr >= 10'000'000)
			break;
		cntr++;
		fr = 1.0 / fr;
		int64_t i = int64_t(fr);
		fr -= double(i);
		v.push_back(i);
	}
	a = *v.rbegin();
	for (auto it = std::next(v.rbegin()); it != v.rend(); it++)
	{
		std::swap(a, b);
		a += b * (*it);
	}
	return { sign * a, b };
}

int main()
{
	double x1, x2, x3;
	std::cout << "Enter three different roots (delimited with spaces): ";
	std::cin >> x1 >> x2 >> x3;
	std::pair<int64_t, int64_t> ba = as_frac(-(x1 + x2 + x3)), ca = as_frac(x1 * x2 + x2 * x3 + x1 * x3),
								da = as_frac(-(x1 * x2 * x3));
	/*
	ax^3 + bx^2 + cx + d = 0
	Теорема Виета:
	x1 + x2 + x3 = -b/a
	x1*x2 + x2*x3 + x1*x3 = c/a
	x1 * x2 * x3 = -d/a
	*/
	int64_t a, b = ba.first, c = ca.first, d = da.first;
	int64_t l = std::lcm(ba.second, std::lcm(ca.second, da.second));
	a = l, b *= (l / ba.second), c *= (l / ca.second), d *= (l / da.second);
	std::string sa = ((a == 1) ? ("x^3") : (std::to_string(a) + "x^3")),
				sb = ((b == 0) ? ("") : ((abs(b) == 1) ? ("x^2") : (std::to_string(abs(b)) + "x^2"))),
				sc = ((c == 0) ? ("") : ((abs(c) == 1) ? ("x") : (std::to_string(abs(c)) + "x"))),
				sd = ((d == 0) ? ("") : std::to_string(abs(d)));
	std::cout << "Formula: " << sa << ((b >= 0) ? (" + ") : (" - ")) << sb << ((c >= 0) ? (" + ") : (" - ")) << sc
			  << ((d >= 0) ? (" + ") : (" - ")) << sd << " = 0" << std::endl;
	return 0;
}