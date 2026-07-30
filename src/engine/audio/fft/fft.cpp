#include <bit>
#include <cmath>
#include <numbers>

#include "engine/audio/fft/fft.hpp"

namespace engine::audio::fft {

/* NOTE: FFT using cooley-tukey algorithm with radix-2 variation */
FFT::FFT(int resolution) : m_resolution(resolution), m_hann_window_total(0.0f) {
    const std::size_t N = resolution;
    const int N_HALF = N >> 1;
    const int bits = std::bit_width(N) - 1;
    const float PI = std::numbers::pi_v<float>;

    // Calculate bit reversed indices and hann window
    m_hann_window.resize(N);
    m_bit_reversed_indices.resize(N);

    for (int i = 0; i < N; ++i) {
        int index = i;

        m_bit_reversed_indices[i] = 0;

        for (int j = 0; j < bits; ++j) {
            m_bit_reversed_indices[i] = (m_bit_reversed_indices[i] << 1) | (index & 1);
            index >>= 1;
        }

        m_hann_window[i] = 0.5f * (1.0f - std::cos(2.0f * PI * static_cast<float>(i) / static_cast<float>(N - 1)));
        m_hann_window_total += m_hann_window[i];
    }

    // Calculate twiddle factors
    m_twiddle_factors.reserve(N_HALF);

    for (int k = 0; k < N_HALF; ++k) {
        float theta = (-2.0f * PI * static_cast<float>(k)) / static_cast<float>(N);
        m_twiddle_factors.emplace_back(std::cos(theta), std::sin(theta));
    }
}

std::vector<std::complex<float>> FFT::update(const std::vector<std::complex<float>> &a) {
    const std::size_t N = m_resolution;

    int bits = std::bit_width(N) - 1;

    std::vector<std::complex<float>> A = bit_reverse_copy(a);

    for (int s = 1; s <= bits; ++s) {
        int m = 1 << s;
        int m_half = m >> 1;

        int twiddle_stride = N >> s;

        for (int j = 0; j < m_half; ++j) {
            std::complex<float> &w = m_twiddle_factors[j * twiddle_stride];

            for (int k = 0; k < N; k += m) {
                std::complex<float> t = w * A[k + j + m_half];
                std::complex<float> u = A[k + j];
                A[k + j] = u + t;
                A[k + j + m_half] = u - t;
            }
        }
    }

    return A;
}

std::vector<std::complex<float>> FFT::bit_reverse_copy(const std::vector<std::complex<float>> &a) {
    int n = a.size();

    std::vector<std::complex<float>> A(n);

    for (int k = 0; k < n; ++k) {
        A[m_bit_reversed_indices[k]] = a[k];
    }

    return A;
}

int FFT::resolution() const {
    return m_resolution;
}

float FFT::hann_window(int index) const {
    return m_hann_window[index];
}

float FFT::hann_window_total() const {
    return m_hann_window_total;
}

} // namespace engine::audio::fft
