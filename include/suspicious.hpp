#pragma once

#include "includes.hpp"

namespace susp
{
	/*!struct form_susp contains the information
	 * about error that we can find in some file
	 */
	struct form_susp final
	{
	public:
		form_susp(std::string name_ , std::initializer_list<std::string> formats_ , std::initializer_list<std::string> susp_strs_);
		/*!name of error*/
		std::string name;
		/*!file's formats that can contain this error*/
		std::vector<std::string> formats;
		/*!strings make the suspicious*/
		std::vector<std::string> susp_strs;
		~form_susp() {};

		void dump();
	};

	/*!function that make vector of suspicious
	 * that we want to find
	 */
	std::vector<form_susp> fill_susps();
}