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
							//std::vector<std::string> file = read_file(fs->path());
							//for (auto check = file.begin() ; check != file.end() ; ++check)
							//{
								//if (KMP((*str) , (*check)))
								//{
									//counter++
									//std::cout << "found error in " << fs->path().filename();
									result.susps[it->name]++;
									continue;
								//}
							//}
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
		std::cout << "JS detects: " << susps["js"] << std::endl << std::endl;
		std::cout << "CMD detects: " << susps["cmd"] << std::endl << std::endl;
		std::cout << "EXE detects: " << susps["exe"] << std::endl << std::endl;
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

	/*bool KMP(std::string sought , std::string for_scan)
	{

	}*/

	std::vector<std::string> read_file(std::filesystem::path file)
	{
		std::vector<std::string> result;
		std::string line;
		std::ifstream in(file.string());
		if (in.is_open())
    	{
	        while (getline(in, line))
	        {
	           result.push_back(line);
	        }
    	}
    	in.close();
    	return result;
	}
}