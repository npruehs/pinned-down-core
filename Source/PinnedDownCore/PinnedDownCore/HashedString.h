#pragma once

#include <string>

namespace PinnedDownCore
{
	// Based upon "Game Coding Complete" by Mike McShaffry et al. and the Adler-32 checksum by Mark Adler.
	class HashedString
	{
	public:
		HashedString(std::string string) : HashedString(string.c_str())
		{
		}

		HashedString(char const* const string)
		{
			this->string = string;
			this->length = strlen(string);
			this->hash = this->HashString(string);
		}

		unsigned long GetHash() const
		{
			return this->hash;
		}

		size_t GetLength() const
		{
			return this->length;
		}

		char const* const GetString() const
		{
			return this->string;
		}

		bool operator < (HashedString const & other) const {
			return this->GetHash() < other.GetHash();
		}

		bool operator == (HashedString const & other) const {
			return this->GetHash() == other.GetHash();
		}

	private:
		unsigned long hash;
		char const* string;
		size_t length;

		unsigned long HashedString::HashString(char const* string)
		{
			// Largest prime number smaller than 2^16.
			unsigned long base = 65521L;

			// Largest n such that 255n(n+1)/2 + (n+1)(base-1) <= 2^32 - 1
			unsigned long max = 5552;

			// Check argument.
			if (string == nullptr) {
				return 0;
			}

			unsigned long s1 = 0;
			unsigned long s2 = 0;

#define DO1(buf, i) { s1 += tolower(buf[i]); s2 += s1; }
#define DO2(buf, i) { DO1(buf, i); DO1(buf, i + 1); }
#define DO4(buf, i) { DO2(buf, i); DO2(buf, i + 2); }
#define DO8(buf, i) { DO4(buf, i); DO2(buf, i + 4); }
#define DO16(buf)   { DO8(buf, 0); DO8(buf, 8); }

			// Compute hash.
			for (size_t length = this->length; length > 0;)
			{
				unsigned long k = length < max ? length : max;
				length -= k;

				while (k >= 16)
				{
					DO16(string);
					string += 16;
					k -= 16;
				}

				if (k != 0)
				{
					do
					{
						s1 += *string++;
						s2 += s1;
					} while (--k);
				}

				s1 %= base;
				s2 %= base;
			}

			return (s2 << 16) | s1;

#undef DO1
#undef DO2
#undef DO4
#undef DO8
#undef DO16
		}
	};
}