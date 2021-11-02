#include "../include/scan.hpp"

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

	scan::scan(const std::string& Dir , std::vector<susp::form_susp>& errs_): errs(errs_)
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

	scan::scan(const std::string& Dir , std::vector<susp::form_susp>&& errs_): errs(errs_)
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

	bool scan::scanning_thread()
	{
		my_time::Timer clock;
		std::filesystem::directory_iterator start(way) , fin;
		std::vector<std::filesystem::directory_entry> entries(start , fin);

		size_t num_thr = std::thread::hardware_concurrency();
		std::vector<std::vector<std::filesystem::path>> thr_paths(num_thr);

		size_t counter = 0;
		size_t num_files = 0;
		for (auto fs = entries.begin() ; fs != entries.end() ; ++fs)
		{
			thr_paths[counter].push_back(fs->path());
			counter++;
			num_files++;
			if (counter == num_thr)
				counter = 0; 
		}

		result.files = num_files;

		if (num_files < num_thr)
			num_thr = num_files;

		std::vector<std::thread> THrs;
		std::vector<scan_dump> thrs_results(num_thr);


		for (size_t i = 0 ; i < num_thr ; ++i)
		{
			THrs.push_back(std::thread([this , i , &thr_paths , &thrs_results] {
				ThreadFunc(thr_paths[i] , thrs_results[i]);
			}));
		}

		counter = 0;
		for (auto it = THrs.begin() ; it != THrs.end() ; ++it)
		{
			(*it).join();
			result.susps["JS"] += thrs_results[counter].susps["JS"];
			result.susps["CMD"] += thrs_results[counter].susps["CMD"];
			result.susps["EXE"] += thrs_results[counter].susps["EXE"];
			result.errors += thrs_results[counter].errors;
			counter++;
		}
		result.scan_time = clock.get_s();
		return true;
	}

	void scan::ThreadFunc(const std::vector<std::filesystem::path>& files, scan_dump& result) 
	{
		for (auto fs = files.begin() ; fs != files.end() ; ++fs)
		{
			for (auto it = errs.begin() ; it != errs.end() ; ++it)
			{
				for (auto tp = it->formats.begin() ; tp != it->formats.end() ; ++tp)
				{
					if (fs->extension() == (*tp))
					{
						for (auto str = it->susp_strs.begin() ; str != it->susp_strs.end() ; ++str)
						{
							try
							{
								if (check_file((*fs) , (*str)))
								{
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
		}
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

std::vector<size_t> prefix_f (const std::string& sought)
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

bool KMP(const std::string& sought , const std::string& for_scan)
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

	bool check_file(const std::filesystem::path& file , const std::string& sought)
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
