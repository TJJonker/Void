#pragma once

#ifdef VOID_PLATFORM_WINDOWS
	#ifdef VOID_BUILD_DLL
		#define VOID_API __declspec(dllexport)
	#else
		#define VOID_API __declspec(dllimport)
	#endif
#else
	#error Void only supports windows!
#endif

#ifdef VOID_ASSERT_ENABLED
	#define VOID_CORE_ASSERT(x, ...) { if(!(x)) { VOID_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define VOID_ASSERT(x, ...) { if(!(x)) { VOID_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define VOID_CORE_ASSERT(x, ...) 
	#define VOID_ASSERT(x, ...) 
#endif

namespace Void {
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T>CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...)
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T>CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}

#define BIT(x) (1 << x)