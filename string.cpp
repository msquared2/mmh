#include "stdafx.h"

namespace mmh {
	t_size poweroften(t_size raiseTo)
	{
		t_size ret = 1, i;
		for (i = 0; i < raiseTo; i++)
			ret *= 10;
		return ret;
	}

	const char * g_convert_utf16_to_ascii(const WCHAR * str_utf16, t_size len, pfc::string_base & p_out)
	{
		char * replacement = "_";
		t_size len_max = min(wcslen(str_utf16), len);
		if (len_max)
		{
			int size_ascii = WideCharToMultiByte(20127, NULL, str_utf16, len_max, NULL, NULL, replacement, NULL);
			if (!size_ascii)
				throw exception_win32(GetLastError());

			pfc::array_t<char> str_ascii;
			str_ascii.set_size(size_ascii + 1);
			str_ascii.fill_null();
			int ret = WideCharToMultiByte(20127, NULL, str_utf16, len_max, str_ascii.get_ptr(), size_ascii, replacement, NULL);
			if (!ret)
				throw exception_win32(GetLastError());
			p_out.set_string(str_ascii.get_ptr(), size_ascii);
		}
		else p_out.reset();
		return p_out.get_ptr();
	}

	const char * g_convert_utf8_to_ascii(const char * p_source, pfc::string_base & p_out)
	{
		pfc::stringcvt::string_wide_from_utf8 str_utf16(p_source);
		g_convert_utf16_to_ascii(str_utf16, pfc_infinite, p_out);
		return p_out.get_ptr();
	}

	char format_digit(unsigned p_val)
	{
		PFC_ASSERT(p_val < 16);
		return (p_val < 10) ? p_val + '0' : p_val - 10 + 'A';
	}
}