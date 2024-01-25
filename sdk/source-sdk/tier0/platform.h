#pragma once

template <typename T>
inline T d_word_swap_c(T dw)
{
	UINT32 temp;

	temp = *((UINT32*)&dw) >> 24;
	temp |= ((*((UINT32*)&dw) & 0x00FF0000) >> 8);
	temp |= ((*((UINT32*)&dw) & 0x0000FF00) << 8);
	temp |= ((*((UINT32*)&dw) & 0x000000FF) << 24);

	return *((T*)&temp);
}

inline long little_long(long val)
{
	int test = 1;
	return (*(char*)&test == 1) ? val : d_word_swap_c(val);
}
