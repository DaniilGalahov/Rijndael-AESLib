#pragma once
#include "AESLib.h"

namespace AESBridge {
	public enum class Mode : int
	{
		AES128 = 0,
		AES192 = 1,
		AES256 = 2
	};

	public ref class AES sealed
	{
	public:
		static cli::array<System::Byte>^ Encrypt(cli::array<System::Byte>^ openData, cli::array<System::Byte>^ userKey, Mode mode);
		static cli::array<System::Byte>^ Decrypt(cli::array<System::Byte>^ encryptedData, cli::array<System::Byte>^ userKey, Mode mode);
	};
}