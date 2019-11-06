cdef extern from "../include/dkm.hpp":
	template <typename T, size_t N>
	std::tuple<std::vector<std::array<T, N>>, std::vector<uint32_t>> kmeans_lloyd(const std::vector<std::array<T, N>>& data, const clustering_parameters<T>& parameters)


def py_hello(name: bytes) -> None:
    kmeans_lloyd(data, parameters)