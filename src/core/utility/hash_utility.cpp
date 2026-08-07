#include "core/utility/hash_utility.hpp"

#include "core/exceptions/runtime_exception.hpp"

#include <openssl/evp.h>

#include <fstream>

namespace core::utility {

std::string HashUtility::hash_file(const std::filesystem::path &path) {
    std::ifstream file(path, std::ios::binary);

    std::unique_ptr<EVP_MD_CTX, void (*)(EVP_MD_CTX *)> context(EVP_MD_CTX_new(), EVP_MD_CTX_free);

    if (!context) {
        throw exceptions::RuntimeException("Failed to create OpenSSL context.");
    }

    if (EVP_DigestInit_ex(context.get(), EVP_sha256(), nullptr) != 1) {
        throw exceptions::RuntimeException("Failed to initialize SHA-256 digest.");
    }

    // use 4kb for now
    constexpr std::size_t buffer_size = 4096;
    char buffer[4096];

    while (file.read(buffer, buffer_size) || file.gcount() > 0) {
        if (EVP_DigestUpdate(context.get(), buffer, file.gcount()) != 1) {
            throw exceptions::RuntimeException("Failed to update SHA-256 digest.");
        }
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_length = 0;

    if (EVP_DigestFinal_ex(context.get(), hash, &hash_length) != 1) {
        throw exceptions::RuntimeException("Failed to finalize SHA-256 digest.");
    }

    std::stringstream hex_stream;

    for (int i = 0; i < hash_length; ++i) {
        hex_stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return hex_stream.str();
}

} // namespace core::utility
