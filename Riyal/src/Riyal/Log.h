#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Riyal {

	class RIYAL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define RY_CORE_TRACE(...)    ::Riyal::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RY_CORE_INFO(...)     ::Riyal::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RY_CORE_WARN(...)     ::Riyal::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RY_CORE_ERROR(...)    ::Riyal::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RY_CORE_FATAL(...)    ::Riyal::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define RY_TRACE(...)	      ::Riyal::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RY_INFO(...)	      ::Riyal::Log::GetClientLogger()->info(__VA_ARGS__)
#define RY_WARN(...)	      ::Riyal::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RY_ERROR(...)	      ::Riyal::Log::GetClientLogger()->error(__VA_ARGS__)
#define RY_FATAL(...)	      ::Riyal::Log::GetClientLogger()->fatal(__VA_ARGS__)