#pragma once

#include <complex>
#include <vector>

namespace engine::audio::fft {

class FFT {
  public:
    FFT(int resolution = default_resolution);

    std::vector<std::complex<float>> update(const std::vector<std::complex<float>> &a);

    int resolution() const;
    float hann_window(int index) const;
    float hann_window_total() const;

  private:
    static inline constexpr std::size_t default_resolution = 2048;

    std::size_t m_resolution;

    float m_hann_window_total;

    std::vector<int> m_bit_reversed_indices;
    std::vector<float> m_hann_window;
    std::vector<std::complex<float>> m_twiddle_factors;

    std::vector<std::complex<float>> bit_reverse_copy(const std::vector<std::complex<float>> &a);
};

} // namespace engine::audio::fft
