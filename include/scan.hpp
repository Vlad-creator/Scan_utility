#pragma once

#include "includes.hpp"
#include "suspicious.hpp"
#include "time.hpp"

namespace scan
{
	/*! Scan_dump - structure that contains
	 * information about scanning
	 * std::map used because we need to save information <key , value>
	 * and often search for a value by its key.
	 */
	struct scan_dump final
	{
	public:
		scan_dump(): files(0) , errors(0) {};

		size_t files;
		std::map<std::string , size_t> susps;
		size_t errors;
		size_t scan_time;
		/*!
		 * dump() - function for showing information
		 * that contains in scan_dump
		 */
		void dump();
	};

	class scan final
	{
	private:
		std::filesystem::path way;
		std::vector<susp::form_susp> errs;

	public:
		scan_dump result;

		scan(const char* Dir , std::vector<susp::form_susp>& errs_);
		scan(const char* Dir , std::vector<susp::form_susp>&& errs_);
		scan(const std::string& Dir , std::vector<susp::form_susp>& errs_);
		scan(const std::string& Dir , std::vector<susp::form_susp>&& errs_);

		/*!function that scanning directory
		 * 
		 * @result true - scanning was successfull
		 */
		bool scanning();

		void dump();
	};

	/*!Knuth-Morrisph-Pratt algorithm for finding
	 * sought string in main string
	 * 
	 * @param [in] sought sought - string that we want to find
	 * @param [in] for_scan for_scan - the string in which the search is performed
	 * 
	 * @result true - found , false - not found
	 */
	bool KMP(std::string& sought , std::string& for_scan);

	/*!function for checking file for line presence
	 * 
	 * @param [in] sought sought - string that we want to find
	 * @param [in] file file - the file in which the search is performed
	 * 
	 * @result true - found , false - not found
	 */
	bool check_file(const std::filesystem::path& file , std::string& sought);

	/*!function for making prefix function of string
	 * 
	 * @param [in] sought sought - string the function of which to find
	 * 
	 * @result prefix function of sought string
	 */
	std::vector<size_t> prefix_f (std::string& sought);
}