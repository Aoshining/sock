#include <torch/extension.h>
#include <math.h>

torch::Tensor forward(const torch::Tensor& input) {
    return 0.5 * input * (1.0 + torch::erf(input / sqrt(2.0)));
}

torch::Tensor backward(const torch::Tensor& grad_output, const torch::Tensor& input) {
    torch::Tensor tanh = 0.5 * (1.0 + torch::erf(input / sqrt(2.0)));
    torch::Tensor exp = input * (torch::exp(-0.5 * pow(input,2)) / sqrt(2.0 * M_PI));
    return grad_output * (tanh + exp);
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
    m.def("forward", &forward, "GELU forward");
    m.def("backward", &backward, "GELU backward");
}