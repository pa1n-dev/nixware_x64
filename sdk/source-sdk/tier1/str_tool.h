#pragma once

inline void v_binarytohex(const byte* in, int inputbytes, char* out, int outsize)
{
	char doublet[10];
	int i;

	out[0] = 0;

	for (i = 0; i < inputbytes; i++)
	{
		unsigned char c = in[i];
		snprintf(doublet, sizeof(doublet), "%02x", c);
		strncat(out, doublet, outsize);
	}
}