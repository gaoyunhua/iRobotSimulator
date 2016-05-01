/*remark: there is an errored case below that should be handled by the students (e.g. by throwing an exception).
There is a remark just before where the error should be handled. */
#include <dirent.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class FilesLister {
public:
    FilesLister(const string &basePath)
            : basePath_(basePath) {
        this->refresh();
    }

    virtual void refresh() {
        DIR *dir;
        struct dirent *ent;
        this->filesList_.clear();
        if ((dir = opendir(this->basePath_.c_str())) != NULL) {
            /* print all the files and directories within directory */
            while ((ent = readdir(dir)) != NULL) {
                this->filesList_.push_back(concatenateAbsolutePath(this->basePath_, ent->d_name));
            }
            closedir(dir);
        } else {
            /* could not open directory
            Remark: IN YOUR CODE, handle this error as well (e.g. throw an exception)... */
            //cout << "Error: could not open directory: " <<  this->basePath_ << endl;
            return;
        }
        std::sort(this->filesList_.begin(), this->filesList_.end());
    }

    vector<string> getFilesList() {
        return this->filesList_;
    }

protected:
    vector<string> filesList_;
    string basePath_;

private:
    static string concatenateAbsolutePath(const string &dirPath, const string &fileName) {
        if (dirPath.empty())
            return fileName;
        if (dirPath.back() == '/')
            return dirPath + fileName;
        return dirPath + "/" + fileName;
    }
};

class FilesListerWithSuffix : public FilesLister {
public:
    FilesListerWithSuffix(const string &basePath, const string &suffix)
            : FilesLister(basePath), suffix_(suffix) {
        this->filterFiles();
    }

    virtual void refresh() {
        FilesLister::refresh();
        this->filterFiles();
    }

protected:
    void filterFiles() {
        vector<string> temp = this->filesList_;
        this->filesList_.clear();
        for (vector<string>::iterator itr = temp.begin();
             itr != temp.end();
             ++itr) {
            if (endsWith(*itr, this->suffix_)) {
                this->filesList_.push_back(*itr);
            }
        }
    }

    static inline bool endsWith(std::string value, std::string ending) {
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    string suffix_;
};

class HousesLister : public FilesListerWithSuffix {
public:
    HousesLister(const string &basePath)
            : FilesListerWithSuffix(basePath, ".house") {
    }
};

class AlgorithmsLister : public FilesListerWithSuffix {
public:
    AlgorithmsLister(const string &basePath)
            : FilesListerWithSuffix(basePath, ".so") {
    }
};


void printStringVector(const vector<string> &vec) {
    for (vector<string>::const_iterator itr = vec.begin();
         itr != vec.end();
         ++itr) {
        cout << *itr;
        if (itr + 1 != vec.end()) {
            cout << ", ";
        }
    }
    cout << endl;
}


//int main(int argc, char **argv) {
//    string basePath = "";
//    if (argc > 1)
//        basePath = argv[0];
//
//    basePath = "dir";
//    system(("mkdir " + basePath).c_str());
//    for (int i = 0; i < 100; ++i) {
//        fclose(fopen((basePath + "/" + "house" + std::to_string(i) + ".house").c_str(), "w"));
//        fclose(fopen((basePath + "/" + "algorithm" + std::to_string(i) + ".so").c_str(), "w"));
//        fclose(fopen((basePath + "/" + "junk" + std::to_string(i) + ".junk").c_str(), "w"));
//    }
//
//    HousesLister housesLister = HousesLister(basePath);
//    AlgorithmsLister algorithmsLister = AlgorithmsLister(basePath);
//    cout << "Houses: " << endl;
//    printStringVector(housesLister.getFilesList());
//    cout << endl;
//    cout << "Algorithms: " << endl;
//    printStringVector(algorithmsLister.getFilesList());
//    return 0;
//}
