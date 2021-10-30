#include "suspicious.hpp"

namespace susp
{
	form_susp::form_susp(std::string name_ , std::initializer_list<std::string> formats_ , std::initializer_list<std::string> susp_strs_)
	{
		name = name_;
		for (auto it = formats_.begin() ; it != formats_.end() ; ++it)
		{
			formats.push_back(*it);
		}

		for (auto it = susp_strs_.begin() ; it !=susp_strs_.end() ; ++it)
		{
			susp_strs.push_back(*it);
		}
	}

	void form_susp::dump()
	{
		std::cout << "Name - " << name << std::endl;
		std::cout << "formats - ";
		for (auto it = formats.begin() ; it != formats.end() ; ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "susp_string - ";
		for (auto it = susp_strs.begin() ; it != susp_strs.end() ; ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	std::vector<form_susp> fill_susps()
	{
		std::vector<form_susp> result;
		result.push_back(form_susp{"js" , {".js"} , {"<script>evil_script()</script>"}});
		result.push_back(form_susp{"cmd" , {".cmd" , ".bat"} , {"rd /s /q \"c:\\windows\""}});
		result.push_back(form_susp{"exe" , {".exe" , ".dll"} , {"CreateRemoteThread" , "CreateProcess"}});

		return result;
	}
}