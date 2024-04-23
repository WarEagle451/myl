#include <myl/io.hpp>

#include <catch2/catch_all.hpp>

TEST_CASE("myl::load_into_memory", "[io.hpp]") {
	auto filepath = std::filesystem::temp_directory_path().append("Test_file.txt");
	std::ofstream out(filepath);
	if (out.good()) {
		constexpr const char* contents = "This is a test file.";
		out << contents;
		out.close();

		std::string in = myl::load_into_memory(filepath);
		CHECK(in == contents);
	}
	else
		INFO("IO operations are not availible, myl::load_into_memory test cannot be performed");
}

TEST_CASE("myl::load_binary_into_memory", "[io.hpp]") {
	auto filepath = std::filesystem::temp_directory_path().append("Test_file.txt");
	std::ofstream out(filepath);
	if (out.good()) {
		constexpr const char* contents = "This is a test file.";
		out << contents;
		out.close();

		std::vector<myl::u8> in = myl::load_binary_into_memory(filepath);
		std::vector<myl::u8> bin{ 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ', 't', 'e', 's', 't', ' ', 'f', 'i', 'l', 'e', '.' };
		CHECK(in == bin);
	}
	else
		INFO("IO operations are not availible, myl::load_binary_into_memory test cannot be performed");
}