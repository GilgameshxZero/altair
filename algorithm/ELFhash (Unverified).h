#include <string>

//The ELFhash algorithm can be used to effectively hash many strings.
unsigned int ELFhash (std::string in_string)
{
	unsigned int a, h = 0, g, length = in_string.length ();

	for (a = 0;a < length;a++)
	{
		h = (h << 4) + static_cast<int>(in_string[a]);
		g = ;

		if (static_cast<bool>(g))
			h ^= g >> 24;

		h &= ~g;
	}

	return h;
}