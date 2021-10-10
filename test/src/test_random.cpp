#include <gtest/gtest.h>

#include <iostream>
#include <random>
#include <set>
#include <utils/random.hpp>

using namespace gal::toolbox::utils;

namespace
{
	constexpr auto test_times = 10000;

	template<typename Engine>
	constexpr auto test_engine(Engine&& engine)
	{
		std::cout << std::fixed << std::setprecision(3);
		std::cout << "\n# Test overlap (" << test_times << " times) \n";

		std::set<typename Engine::result_type> set;
		for (auto j = 0; j < test_times; ++j)
		{
			set.insert(engine());
		}

		std::cout << "\n# Test " << Engine::bits_of_this << " bits type <" << typeid(typename Engine::result_type).name() << ">(mangled) overlap(bound: " << Engine::min() << " -> " << Engine::max() << ").\nresult: " << set.size() << '(' << (static_cast<float>(set.size()) / test_times * 100) << "%)" << std::endl;
	}
}// namespace

TEST(TestRandom, TestXSR256P)
{
	test_engine(xor_shift_rotate_256_plus_engine{});
}

TEST(TestRandom, TestXSR256PP)
{
	test_engine(xor_shift_rotate_256_plus_plus_engine{});
}

TEST(TestRandom, TestXSR256SS)
{
	test_engine(xor_shift_rotate_256_star_star_engine{});
}

TEST(TestRandom, TestXSR128P)
{
	test_engine(xor_shift_rotate_128_plus_engine{});
}

TEST(TestRandom, TestXSR128PP)
{
	test_engine(xor_shift_rotate_128_plus_plus_engine{});
}

TEST(TestRandom, TestXSR128SS)
{
	test_engine(xor_shift_rotate_128_star_star_engine{});
}

TEST(TestRandom, TestXRSR128P)
{
	test_engine(xor_rotate_shift_rotate_128_plus_engine{});
}

TEST(TestRandom, TestXRSR128PP)
{
	test_engine(xor_rotate_shift_rotate_128_plus_plus_engine{});
}

TEST(TestRandom, TestXRSR128SS)
{
	test_engine(xor_rotate_shift_rotate_128_star_star_engine{});
}

TEST(TestRandom, TestStlDist)
{
	std::cout << "\n# Test overlap (" << test_times << " times) \n";
	for (auto i = 0; i < 5; ++i)
	{
		xor_shift_rotate_256_plus_plus_engine											  engine{};
		std::uniform_int_distribution<xor_shift_rotate_256_plus_plus_engine::result_type> dist;
		std::set<xor_shift_rotate_256_plus_plus_engine::result_type>					  set;
		for (auto j = 0; j < test_times; ++j)
		{
			set.insert(dist(engine));
		}
		std::cout << set.size() << '\n';
	}
}
