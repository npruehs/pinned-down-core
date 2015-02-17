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
		bool IsEnabled(LogLevel logLevel) const
		{
			return logLevel >= this->logLevel;
		}

		void LogTrace(const std::string & message)
		{
			this->Log(LogLevel::Trace, message);
		}

		void LogDebug(const std::string & message)
		{
			this->Log(LogLevel::Debug, message);
		}

		void LogInfo(const std::string & message)
		{
			this->Log(LogLevel::Info, message);
		}

		void LogWarn(const std::string & message)
		{
			this->Log(LogLevel::Warn, message);
		}

		void LogError(const std::string & message)
		{
			this->Log(LogLevel::Error, message);
		}

		void LogFatal(const std::string & message)
		{
			this->Log(LogLevel::Fatal, message);
		}

		void Log(LogLevel logLevel, const std::string & message)
		{
			if (this->IsEnabled(logLevel))
			{
				this->WriteLog(logLevel, (message + "\n").c_str());
			}
		}

		std::string LogLevelToString(LogLevel logLevel) const
		{
			switch (logLevel)
			{
			case LogLevel::Debug:
				return "DEBUG";
			case LogLevel::Error:
				return "ERROR";
			case LogLevel::Fatal:
				return "FATAL";
			case LogLevel::Info:
				return "INFO";
			case LogLevel::Trace:
				return "TRACE";
			case LogLevel::Warn:
				return "WARN";
			default:
				return "LOG";
			}
		}

		virtual void Flush() { }

	protected:
		Logger(LogLevel logLevel)
		{
			this->logLevel = logLevel;
		}

		virtual void WriteLog(LogLevel logLevel, const char* const message) = 0;

	private:
		LogLevel logLevel;
	};
}