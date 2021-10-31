#include "scan.hpp"

namespace scan
{
	scan::scan(const char* Dir , std::vector<susp::form_susp>& errs_): errs(errs_)
	{
		way = std::filesystem::path(Dir);
		for (auto it = errs_.begin() ; it != errs_.end() ; ++it)
		{
			result.susps[it->name] = 0;
		}
	}

	scan::scan(const char* Dir , std::vector<susp::form_susp>&& errs_): errs(errs_)
	{
		way = std::filesystem::path(Dir);
		for (auto it = errs_.begin() ; it != errs_.end() ; ++it)
		{
			result.susps[it->name] = 0;
		}
	}

	void scan::dump()
	{
		result.dump();
	}

	bool scan::scanning()
	{
		my_time::Timer clock;
		std::filesystem::directory_iterator start(way) , fin;
		std::vector<std::filesystem::directory_entry> entries(start , fin);
		for (auto fs = entries.begin() ; fs != entries.end() ; ++fs)
		{
			for (auto it = errs.begin() ; it != errs.end() ; ++it)
			{
				for (auto tp = it->formats.begin() ; tp != it->formats.end() ; ++tp)
				{
					if (fs->path().extension() == (*tp))
					{
						for (auto str = it->susp_strs.begin() ; str != it->susp_strs.end() ; ++str)
						{
								try
								{
									if (check_file(fs->path() , (*str)))
									{
										//std::cout << "found error in " << fs->path().filename() << std::endl;
										result.susps[it->name]++;
										continue;
									}
								}
								catch (std::exception const& e)
								{
									result.errors++;
								}
						}
					}
				}
			} 
			result.files++;
		}
		result.scan_time = clock.get_s();
		return true;
	}

	void scan_dump::dump()
	{
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "====== Scan result ======" << std::endl << std::endl;
		std::cout << "Processed files: " << files << std::endl << std::endl;
		std::cout << "JS detects: " << susps["JS"] << std::endl << std::endl;
		std::cout << "CMD detects: " << susps["CMD"] << std::endl << std::endl;
		std::cout << "EXE detects: " << susps["EXE"] << std::endl << std::endl;
		std::cout << "Errors: " << errors << std::endl << std::endl;
		std::cout << "Execution time: ";
		for (auto it = susps.begin() ; it != susps.end() ; ++it)
		{
			
		}
		std::cout.width(2);
		std::cout.fill('0'); 
		std::cout << scan_time / 3600 << ":";
		std::cout.width(2);
		std::cout.fill('0');
		std::cout << scan_time / 60 % 60 << ":";
		std::cout.width(2);
		std::cout.fill('0');
		std::cout << scan_time / 60 << std::endl << std::endl;
		std::cout << "=========================" << std::endl;
	}

std::vector<size_t> prefix_f (std::string& sought)
{
	size_t length = sought.length();
	std::vector<size_t> pref(length);
	for (size_t i = 1 ; i < length ; ++i)
	{
		size_t j = pref[i - 1];
		while ((j > 0) && (sought[i] != sought[j]))
		{
			j = pref[j - 1];
		}
		if (sought[i] == sought[j])
		{
			++j;
		}
		pref[i] = j;
	}
	return pref;
}

bool KMP(std::string& sought , std::string& for_scan)
{
	std::string res = sought + '#' + for_scan;
	std::vector<size_t> pref = prefix_f(res);
	for (size_t i = sought.length() + 1 ; i < res.length() ; ++i)
	{
		if (pref[i] == sought.length())
			return true;
	}
	return false;
}

	bool check_file(const std::filesystem::path& file , std::string& sought)
	{
		std::vector<std::string> result;
		std::string line;
		std::ifstream in(file.string());
		if (in.is_open())
    	{
	        while (getline(in, line))
	        {
	           if (KMP(sought , line))
	           {
	           		return true;
	           }
	        }
    	}
    	else
    	{
    		throw (std::logic_error{"error"});
    	}
    	in.close();
    	return false;
	}
}