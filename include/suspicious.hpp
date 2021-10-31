#pragma once

#include "includes.hpp"

namespace susp
{
	struct form_susp final
	{
	public:
		form_susp(std::string name_ , std::initializer_list<std::string> formats_ , std::initializer_list<std::string> susp_strs_);
		std::string name;
		std::vector<std::string> formats;
		std::vector<std::string> susp_strs;
		~form_susp() {};

		void dump();
	};

	std::vector<form_susp> fill_susps();
}