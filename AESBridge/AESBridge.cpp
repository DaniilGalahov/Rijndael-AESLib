#include "AESBridge.h"
#include <vector>
#include <cstring>
#include <vcclr.h>

static std::vector<unsigned char> ToNative(cli::array<System::Byte>^ a)
{
    std::vector<unsigned char> v;
    if (a != nullptr && a->Length > 0) {
        v.resize(a->Length);
        pin_ptr<System::Byte> p = &a[0];
        std::memcpy(v.data(), p, a->Length);
    }
    return v;
}

static cli::array<System::Byte>^ ToManaged(const std::vector<unsigned char>& v)
{
    auto a = gcnew cli::array<System::Byte>(static_cast<int>(v.size()));
    if (!v.empty()) {
        pin_ptr<System::Byte> p = &a[0];
        std::memcpy(p, v.data(), v.size());
    }
    return a;
}

cli::array<System::Byte>^ AESBridge::AES::Encrypt(cli::array<System::Byte>^ openData,
    cli::array<System::Byte>^ userKey,
    AESBridge::Mode mode)
{
    try {
        auto d = ToNative(openData);
        auto k = ToNative(userKey);
        auto out = AESLib::Encrypt(std::move(d), std::move(k),
            static_cast<AESLib::Mode>(mode));
        return ToManaged(out);
    }
    catch (const std::exception& ex) {
        throw gcnew System::InvalidOperationException(gcnew System::String(ex.what()));
    }
    catch (...) {
        throw gcnew System::InvalidOperationException("Native AES error.");
    }
}

cli::array<System::Byte>^ AESBridge::AES::Decrypt(cli::array<System::Byte>^ encryptedData,
    cli::array<System::Byte>^ userKey,
    Mode mode)
{
    try {
        auto d = ToNative(encryptedData);
        auto k = ToNative(userKey);
        auto out = AESLib::Decrypt(std::move(d), std::move(k),
            static_cast<AESLib::Mode>(mode));
        return ToManaged(out);
    }
    catch (const std::exception& ex) {
        throw gcnew System::InvalidOperationException(gcnew System::String(ex.what()));
    }
    catch (...) {
        throw gcnew System::InvalidOperationException("Native AES error.");
    }
}