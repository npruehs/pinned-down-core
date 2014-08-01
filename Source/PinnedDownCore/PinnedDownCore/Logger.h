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
		bool Logger::IsEnabled(LogLevel logLevel)
		{
			return logLevel >= this->logLevel;
		}

		void Logger::Trace(std::wstring const message)
		{
			this->Log(LogLevel::Trace, message);
		}

		void Logger::Debug(std::wstring const message)
		{
			this->Log(LogLevel::Debug, message);
		}

		void Logger::Info(std::wstring const message)
		{
			this->Log(LogLevel::Info, message);
		}

		void Logger::Warn(std::wstring const message)
		{
			this->Log(LogLevel::Warn, message);
		}

		void Logger::Error(std::wstring const message)
		{
			this->Log(LogLevel::Error, message);
		}

		void Logger::Fatal(std::wstring const message)
		{
			this->Log(LogLevel::Fatal, message);
		}

		void Logger::Log(LogLevel logLevel, std::wstring const message)
		{
			if (this->IsEnabled(logLevel))
			{
				this->WriteLog(logLevel, (message + L"\n").c_str());
			}
		}

		std::wstring Logger::LogLevelToString(LogLevel logLevel)
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

		virtual void Logger::Flush() { }

	protected:
		Logger(LogLevel logLevel)
		{
			this->logLevel = logLevel;
		}

		virtual void Logger::WriteLog(LogLevel logLevel, const wchar_t* const message) = 0;

	private:
		LogLevel logLevel;
	};
}