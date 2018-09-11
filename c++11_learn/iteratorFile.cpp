#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <string>
#include <list>
#include <functional>
#include <iterator>
#include <queue>

#include <tuple>


using namespace std;

class CTraversalPath : public std::iterator<std::forward_iterator_tag,CTraversalPath> {
public:
    CTraversalPath(const string& folder)
    {
        if (folder.back() == '\\' || folder.back() == '/')
            m_basePath = folder.substr(0, folder.length() - 1);

        m_currPath = m_basePath;

        if (folder.length() > 0)
            m_pathQueue.push(m_basePath);
    }

public:
    

private:
    tuple<string, list<string>, list<string> > TravPath(const string& path, bool followlinks)
    {
        DIR* d = opendir(path.c_str());
        if (d == NULL)
            return tuple<string, list<string>, list<string> >();
        
        list<string> childFiles;
        list<string> childFolder;

        struct dirent* dirinfo = readdir(d);
        
        while (dirinfo != NULL) {
            if (strcmp(dirinfo->d_name, ".") != 0 &&
                strcmp(dirinfo->d_name, "..") != 0 &&
                S_ISDIR(dirinfo->d_type))
            {
                m_pathQueue.push(path + dirinfo->d_name);
                childFolder.push_back(path + "/" + dirinfo->d_name);
            }

            string currPath = path + "/" + dirinfo->d_name;

            if (S_ISREG(dirinfo->d_type)) {
                childFiles.push_back(currPath);
            }

            if (followlinks && S_ISLNK(dirinfo->d_type)) {
				vector<char> buf;
				buf.assign(1024, '\0');
                readlink(currPath.c_str(), buf.data(), buf.size());
                struct stat* st;
                if (0 == lstat(buf.date(), st)) {
                    if (S_ISDIR(st->st_mode))
                        childFolder.push_back(buf.data());
                    else if (S_ISREG(st->st_mode))
                        childFiles.push_back(buf.data());
                }
            }

            dirinfo = readdir(d); 
        }
        
        closedir(d);
        return std::make_tuple(path, childFolder, childFiles);  
    }

    tuple<string, list<string>, list<string> > walk(bool followlinks = false) 
    {
        string folder;
        if (m_pathQueue.size() > 0)	{
            folder = m_pathQueue.front();
        }

        return TravPath(folder, followlinks);
    }

private:
    bool   m_followlinks;
    string m_basePath;

    string m_currPath;
    queue<string> m_pathQueue;
};

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;
    
    string exe_path;
	{
    vector<char> buf;
	buf.assign(1024, '\0');
    readlink("/proc/self/exe", buf.data(), 1024);
    *(strrchr(buf.data(), '/') + 1) = 0;
    exe_path = buf.data();
    }


    return 0;
}
