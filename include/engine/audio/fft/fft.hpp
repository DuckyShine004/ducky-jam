#pragma once

#include <vector>
#include <complex>

namespace engine::audio::fft {

class FFT {
  public:
    FFT(int resolution = m_RESOLUTION);

    std::vector<std::complex<float>> update(const std::vector<std::complex<float>> &a);

    int resolution() const;
    float hann_window(int index) const;
    float hann_window_total() const;

  private:
    std::vector<std::complex<float>> bit_reverse_copy(const std::vector<std::complex<float>> &a);

    static inline constexpr std::size_t m_RESOLUTION = 2048;

    std::size_t m_resolution;

    float m_hann_window_total;

    std::vector<int> m_bit_reversed_indices;
    std::vector<float> m_hann_window;
    std::vector<std::complex<float>> m_twiddle_factors;
};

} // namespace engine::audio::fft
