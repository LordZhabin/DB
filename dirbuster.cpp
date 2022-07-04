#include<iostream>
#include<fstream>
#include<string> 
#include<string_view>
#include<map>
#include<vector>
#include<cstdlib>
#include<typeinfo>
#include<ctime>

using namespace std;

struct FOUND {
	string s1, s2, s3;
};

const unsigned DEF_TIMEOUT = 3;
string default_dir_list_file = "dir_list.txt";

void sort_alphabet(string namefile){
	system(("sort -k6 " + namefile).c_str());
}

void filter_http_status(string n_status){
	
}

void print_map(std::string_view comment, const std::map<std::string, string>& m)
{
    std::cout << comment ;
    // iterate using C++17 facilities
    for (const auto& [key, value] : m) {
        std::cout << '[' << key << "] = " << value << "; ";
    }
// C++11 alternative:
//  for (const auto& n : m) {
//      std::cout << n.first << " = " << n.second << "; ";
//  }
// C++98 alternative
//  for (std::map<std::string, int>::const_iterator it = m.begin(); it != m.end(); it++) {
//      std::cout << it->first << " = " << it->second << "; ";
//  }
    std::cout << '\n';
}

void print_banner(){

}

int FETCH(string url, string output, bool ssl_verify = true, bool write_response = false, unsigned timeout = DEF_TIMEOUT){
	string domain, dt_string, data, res;
	//domain = 
	ofstream out;
	out.open(output, std::ios::app);
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	dt_string = asctime(timeinfo);
	dt_string.pop_back();
	cout << dt_string << endl;
	
	ofstream buf("buffer.txt", std::ios::app);
	data.clear();
	system(("curl -s -o /dev/null -w \"%{http_code}\" \"" + url + "\" >> file.txt").c_str());
	ifstream o1;
	o1.open("file.txt");
	o1 >> data;
	if(data == "200"){
		buf << url << endl;
		}
	else
		cout << data << endl;
	res = dt_string + "\t" + url + "\t" + "http status: " + data; 
	out << res << endl;
	o1.close();
	ofstream ofs;
	ofs.open("file.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	
	buf.close();
	out.close();
	return 0;
}

int parse_arguments(map<string, string> ARGS){
	bool isPort = false, isPorts = false;
	for (auto it = ARGS.begin(); it != ARGS.end(); it++) {
        	//td::cout << '[' << key << "] = " << value << "; ";
  
		if (it->first == "--port" || it->first  == "-p") {
			isPort = true;
		}
		if (it->first  == "--pfile" || it->first  == "-P") {
			if(isPort == true){
				cout << "Не имеется возможности сочетания параметров файла с портами (pfile) и отдельно указанного порта (port)." <<endl;
				cout << "Пожалуйста, выберите один из параметров." <<endl;
				return -1;
			}
			isPorts = true;
			ifstream in(it->second);
			if(!in.is_open()){
				cout << "Невозможно найти файл " << it->second << endl;
				return -1;
			}
		}
		if(it->first  == "--dlist" || it->first  == "-l") {
			ifstream in(it->second);
			if(!in.is_open()){
				cout << "Невозможно найти файл " << it->second << endl;
				return -1;
			}
		}
		if(it->first  == "--ignoresertificate" || it->first  == "-p") {
		
		}
		if(it->first  == "--verbosity" || it->first  == "-p") {
			cout << "" << endl;
		}
		if(it->first  == "--useragent" || it->first == "-p") {
		
		}
	}
	if (isPorts == true)
		return 2;
	else if (isPort == true)
		return 1;
	else
		return 0;
}

void print_information(){
	cout << endl << "Usage: dirbust [OPTIONS] [PARAMETR][FILENAME]" << endl;
	cout << "Option" << '\t' << "Long option\t\tMeaning" << endl;
	cout << "-d" << '\t' << "--domain\t\tимя домена или хоста для парсинга данных" << endl;
	cout << "-v" << '\t' << "--verbosity\t\tвывести подробности" << endl;
	cout << "-p" << '\t' << "--port\t\t\tнаименование порта" << endl;
	cout << "-P" << '\t' << "--pfile\t\t\tимя файл с перечислением портов" << endl;
	cout << "-t" << '\t' << "--threads\t\tколичество используемых потоков" << endl;
	cout << "-o" << '\t' << "--output\t\tфайл для записи полученных данных" << endl;
	cout << "-l" << '\t' << "--dlist\t\t\tсписок слов словаря" << endl;
	cout << "-w" << '\t' << "--writeresponse\t\tнаписать запрос" << endl;
	cout << "-i" << '\t' << "--ignorecertificate\tИгнорировать ошибки сертификатов" << endl;
	cout << "-u" << '\t' << "--useragent\t\tИспользуемый пользователький агент" << endl;
	cout << "-s" << '\t' << "--ssl\t\t\tиспользовать SSL или нет" << endl;
	cout << "-T" << '\t' << "--timeout\t\tТаймаут" << endl;
	return;
}

int main(int argc, char *argv[]){

	vector<string> A, port_list, dir_list, url_list;
	map<string, string> ARGS;
	bool SSL_is = false;
	cout<<"Имя программы " << argv[0] << endl;
	
	if(argc == 1)
		cout<<"Вы не ввели никаких аргументов!" << endl;
	else{
		cout<<"Было введено " << argc - 1 << " аргументов." << endl;
		for (int count=1; count < argc; ++count){
        		//std::cout << count << " " << argv[count] << '\n';
        		A.push_back(argv[count]);
		}
	}
	for (int i = 0; i<A.size(); i++){
		cout << A[i] << ' ';
		if (A[i] == "-h" || A[i] == "--help"){
        		print_information();
        		return 0;
        		}
		if (A[i] == "-d" || A[i] == "--domain")
        		ARGS.insert(pair{"domain", argv[i + 2]});
        	if (A[i] == "-p" || A[i] == "--port")
        		ARGS.insert(pair{"port", argv[i + 2]});
        	if (A[i] == "-P" || A[i] == "--pfile")
        		ARGS.insert(pair{"portfile", argv[i + 2]});
        	if (A[i] == "-l" || A[i] == "--dlist")
        		ARGS.insert(pair{"dlist", argv[i + 2]});
        	if (A[i] == "-o" || A[i] == "--output")
        		ARGS.insert(pair{"output", argv[i + 2]});
        	else
        		ARGS.insert(pair{"output", "output.csv"});
        	if (A[i] == "-s" || A[i] == "--ssl")
        		SSL_is = true;
	}
	cout << endl;
	A.clear();
	int port_is = parse_arguments(ARGS);
	
	//print_map("created data^ ", ARGS);
	
	
	
	
	
	string line;
	bool YES = false;
	
	
	for (auto it = ARGS.begin(); it != ARGS.end(); it++) {
		if (it->first == "dlist"){
			YES = true;
			ifstream in(it->second);
			if (in.is_open()){
				while (getline(in, line)){
			    		//std::cout << line << std::endl;
			    		dir_list.push_back(line);
				}
    			} else {
    				cout << "Невозможно найти файл: " << it->second << endl;
    			}
    		in.close();
		}
	}
	
	if(!YES) {
		ifstream in(default_dir_list_file);
		if (in.is_open()){
			while (getline(in, line)){
		    		//std::cout << line << std::endl;
		    		dir_list.push_back(line);
			}
    		}
    		in.close();
	}

	if (port_is == 2){
		ifstream in(ARGS["portfile"]);
		if (in.is_open()){
			while (getline(in, line)){
		    		std::cout << line << std::endl;
		    		port_list.push_back(line);
			}
		in.close();
    		}
	} else if (port_is == 1) {
		port_list.push_back(ARGS["port"]);
	} else if(SSL_is == true)
		port_list.push_back("443");
	else
		port_list.push_back("80");
	
	
	//многопоточнойсть!
	string URL;
	for (int i = 0; i < port_list.size(); i++){
		for (int j = 0; j < dir_list.size(); j++){
			if (SSL_is == true){
				URL = "https://";
				URL.append(ARGS["domain"] + ":");
				URL.append(port_list[i] + "/");
				URL.append(dir_list[j]);
				cout << URL << endl;
				FETCH(URL, ARGS["output"]);
			} else {
				URL = "http://";
				URL.append(ARGS["domain"] + ":");
				URL.append(port_list[i] + "/");
				URL.append(dir_list[j]);
				cout << URL << endl;
				FETCH(URL, ARGS["output"]);
			}
			URL.clear();
		}
	}
	
	while(true){
		ifstream F("buffer.txt");
		if (F.peek() != EOF){
			while (getline(F, line)){
		   		url_list.push_back(line);
			}
	    		F.close();
			cout << "Success!" << endl;
			}
		else{
			cout << "Empty" << endl;
			break;
		}
		for (int k = 0; k < url_list.size(); k++){
			for (int i = 0; i < port_list.size(); i++){
				for (int j = 0; j < dir_list.size(); j++){
					URL.append(url_list[k]);
					URL.append("/" + dir_list[j]);
					cout << URL << endl;
					FETCH(URL, ARGS["output"]);
					URL.clear();
				}
			}
		}
		url_list.clear();	
		ofstream ofs;
		ofs.open("buffer.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}
	
    	return 0;
}
