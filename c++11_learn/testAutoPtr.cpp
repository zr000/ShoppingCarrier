#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

class item {
public:
    item(){ ncnt++; };
    ~item(){ ncnt--; }
    item(item& im) = delete;
    static int ncnt;
};

int item::ncnt = 0;

void finish()
{
    cout << "cnt over = " << item::ncnt << endl;
}

void work(item& im)
{
    int a = im.ncnt;
}

void work(std::shared_ptr<item> pitem)
{
    ;
}

int main(int argc, char** argv)
{
    atexit(finish);

    vector<std::shared_ptr<item>> items;

    for (int i = 0; i < 100; i++)
    {
        auto pitem = std::make_shared<item>();
        item a;
        work(a);
        items.push_back(pitem);
        work(pitem);
    }
    
    cout << "cnt=" << item::ncnt << endl;

    return 0;
}