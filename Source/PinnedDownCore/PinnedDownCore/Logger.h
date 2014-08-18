#pragma once

#include <string>

namespace PinnedDownCore
{
	enum LogLevel
	{
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Fatal
	};

	class Logger
	{
	public:
		bool IsEnabled(LogLevel logLevel)
		{
			return logLevel >= this->logLevel;
		}

		void LogTrace(const std::wstring & message)
		{
			this->Log(LogLevel::Trace, message);
		}

		void LogDebug(const std::wstring & message)
		{
			this->Log(LogLevel::Debug, message);
		}

		void LogInfo(const std::wstring & message)
		{
			this->Log(LogLevel::Info, message);
		}

		void LogWarn(const std::wstring & message)
		{
			this->Log(LogLevel::Warn, message);
		}

		void LogError(const std::wstring & message)
		{
			this->Log(LogLevel::Error, message);
		}

		void LogFatal(const std::wstring & message)
		{
			this->Log(LogLevel::Fatal, message);
		}

		void Log(LogLevel logLevel, const std::wstring & message)
		{
			if (this->IsEnabled(logLevel))
			{
				this->WriteLog(logLevel, (message + L"\n").c_str());
			}
		}

		std::wstring LogLevelToString(LogLevel logLevel)
		{
			switch (logLevel)
			{
			case LogLevel::Debug:
				return L"DEBUG";
			case LogLevel::Error:
				return L"ERROR";
			case LogLevel::Fatal:
				return L"FATAL";
			case LogLevel::Info:
				return L"INFO";
			case LogLevel::Trace:
				return L"TRACE";
			case LogLevel::Warn:
				return L"WARN";
			default:
				return L"LOG";
			}
		}

		virtual void Flush() { }

	protected:
		Logger(LogLevel logLevel)
		{
			this->logLevel = logLevel;
		}

		virtual void WriteLog(LogLevel logLevel, const wchar_t* const message) = 0;

	private:
		LogLevel logLevel;
	};
}