#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "functions.h"
extern uint32_t strings_are_equal(const char* first, const uint32_t first_length, const char* secound, const uint32_t secound_length)
{
	if (first == NULL && secound == NULL) return 1;
	if (first == NULL || secound == NULL) return 0;
	if (first_length != secound_length) return 0;
	for (uint32_t character_index = 0; character_index < first_length; ++character_index)
	{
		if (first[character_index] != secound[character_index]) return 0;
	}
	return 1;
}