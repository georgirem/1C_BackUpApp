#include <vector>
#include <iostream>
#include <fstream>

using std::string;
using std::vector;

std::string readFile(const std::string& fileName) {
    std::ifstream f(fileName);
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    std::string s(size, ' ');
    f.seekg(0);
    f.read(&s[0], size);
    s.erase( std::remove(s.begin(), s.end(), '\r'), s.end() );
    return s;
}
vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == '\n') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    
    return words;
}
vector<string> SplitIntoBlocks(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == '[') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
            word += c;
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}
// структурка для хранения данных
struct Connection {
    string name_;                   //[Наименование секции]
    string Connect_;                //Connect=
    string ID_;                     //ID=
    string OrderInList_;            //OrderInList=
    string Folder_;                 //Folder=
    string OrderInTree_;            //OrderInTree=
    string External_;               //External=
    string ClientConnectionSpeed_;  //ClientConnectionSpeed=
    string App_;                    //App=
    string DefaultApp_;             //DefaultApp=
    string WA_;                     //WA=
    string WSA_;                    //WSA=
    string Version_;                //Version=
    string DefaultVersion_;         //DefaultVersion=
    string AdditionalParameters_;   //AdditionalParameters=
    string WebCommonInfoBaseURL_;   //WebCommonInfoBaseURL=
    string HttpsCA_;                //HttpsCA=
    string HttpsCert_;              //HttpsCert=
    string HttpsCAFile_;            //HttpsCAFile=
    string HttpsCertFile_;          //HttpsCertFile=
    string HttpsCertSelect_;        //HttpsCertSelect=
    // остальные поля добавить по мере необходимости
};

class ConnectionManager {
public:
    //шаблонный метод чтобы фильтровать соединения из контейнера
    //template <typename Predicate>
    //vector<Connection> GetBy(Predicate user_filter);
    
    vector<Connection> GetDBList(const string& list_of_1cdb) {
        int i = 0;
        
        for (const string& word : SplitIntoBlocks(list_of_1cdb)) {
            connections_.push_back(Connection());
            for (const string& word_ : SplitIntoWords(word)) {
                if (!word_.find("[")) {
                    connections_[i].name_ = word_;
                } else if (!word_.find("Connect")){
                    connections_[i].Connect_ = word_;
                }  else if (!word_.find("ID")){
                    connections_[i].ID_ = word_;
                } else if (!word_.find("OrderInList")){
                    connections_[i].OrderInList_ = word_;
                } else if (!word_.find("Folder")){
                    connections_[i].Folder_ = word_;
                } else if (!word_.find("OrderInTree")){
                    connections_[i].OrderInTree_ = word_;
                } else if (!word_.find("External")){
                    connections_[i].External_ = word_;
                } else if (!word_.find("ClientConnectionSpeed")){
                    connections_[i].ClientConnectionSpeed_ = word_;
                } else if (!word_.find("App")){
                    connections_[i].App_ = word_;
                } else if (!word_.find("DefaultApp")){
                    connections_[i].DefaultApp_ = word_;
                } else if (!word_.find("WA")){
                    connections_[i].WA_ = word_;
                } else if (!word_.find("WSA")){
                    connections_[i].WSA_ = word_;
                } else if (!word_.find("Version")){
                    connections_[i].Version_ = word_;
                } else if (!word_.find("DefaultVersion")){
                    connections_[i].DefaultVersion_ = word_;
                } else if (!word_.find("AdditionalParameters")){
                    connections_[i].AdditionalParameters_ = word_;
                } else if (!word_.find("WebCommonInfoBaseURL")){
                    connections_[i].WebCommonInfoBaseURL_ = word_;
                } else if (!word_.find("HttpsCA")){
                    connections_[i].HttpsCA_ = word_;
                } else if (!word_.find("HttpsCert")){
                    connections_[i].HttpsCert_ = word_;
                } else if (!word_.find("HttpsCAFile")){
                    connections_[i].HttpsCAFile_ = word_;
                } else if (!word_.find("HttpsCertFile")){
                    connections_[i].HttpsCertFile_ = word_;
                } else if (!word_.find("HttpsCertSelect")){
                    connections_[i].HttpsCertSelect_ = word_;
                }
            }
            ++i;
        }
        return connections_;
    }
    
private:
    // контейнер для хранения структур
    vector<Connection> connections_;// = {path = "pa"s, name = "na"s, label = "la"s};
    
};

int main() {
    ConnectionManager Connections;
    vector<Connection> DB_List_;
    string fileName = "/Users/admin/Documents/Projects/Reading1CDBListFile/Reading1CDBListFile/ibases.v8i";
    string ibases = readFile(fileName);
    
    
    DB_List_ = Connections.GetDBList(ibases);
    for (auto DB : DB_List_){
        std::cout << DB.name_ + "  " + DB.Connect_<< std::endl;
    }
    return 0;
}
