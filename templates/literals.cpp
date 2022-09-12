// User-defined literals.
inline constexpr std::size_t operator"" _zu(unsigned long long value) {
	return static_cast<std::size_t>(value);
}
inline std::regex operator"" _re(char const *value, std::size_t) {
	return std::regex(value);
}
