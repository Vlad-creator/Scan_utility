#pragma once

#include "../includes.hpp"
#include "../susp/suspicious.hpp"
#include "../time.hpp"

namespace scan
{

	struct scan_dump final
	{
	public:
		scan_dump(): files(0) , errors(0) {};

		size_t files;
		std::map<std::string , size_t> susps;
		size_t errors;
		size_t scan_time;

		void dump();
	};

	class scan final
	{
	private:
		std::filesystem::path way;
		std::vector<susp::form_susp> errs;

		scan_dump result;
	public:
		scan(const char* Dir , std::vector<susp::form_susp>& errs_);
		scan(const char* Dir , std::vector<susp::form_susp>&& errs_);

		bool scanning();

		void dump();
	};

	bool KNP(std::string& sought , std::string& for_scan);
	bool check_file(const std::filesystem::path& file , std::string& sought);
	std::vector<size_t> prefix_f (std::string& sought);
}