#include <Anchor/Anchor.h>

#include <iostream>
//#include <vector>

int main()
{
	std::cout << "[C++ Test] Starting compatibility check..." << std::endl;

	Anchor_Context *ctx = Anchor_CreateContext();
	if (!ctx)
	{
		std::cerr << "[C++ Test] Failed to create context!" << std::endl;
		return 1;
	}

	const char *arg0 = "cpp_test_runner";
	const char *arg1 = "-v";
	const char *arg2 = "--help";

	const char *argv[] = { arg0, arg1, arg2, nullptr };
	int argc = 3;

	int result = Anchor_Parse(ctx, argv, argc);

	if (result == -1)
	{
		std::cout << "[C++ Test] Parse returned false." << std::endl;
	}
	else
	{
		std::cout << "[C++ Test] Parse returned true (Success)." << std::endl;
	}

	Anchor_DestroyContext(ctx);

	std::cout << "[C++ Test] Context freed. Test passed." << std::endl;
	return 0;
}
