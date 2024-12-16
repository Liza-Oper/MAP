#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

template <typename X, typename Y>
class Map
{
private:
    struct MapNode   ///(1)
    {
        int index;
        X key;
        Y value;
        MapNode* pred;
        MapNode* next;
    };

    MapNode* first; ///���� �� ������ ��
    MapNode* last; ///���� �� ��������� ��
    int size_of_map;
    bool from_first = true;

private:
    void deleteNode(MapNode* node)   ///��� ������ ��� ��� ���������, �� �������� ��������, �������� ���� � �����
    {
        if (node->pred)
        {
            node->pred->next = node->next;
        }
        else
        {
            first = first->next;
        } ///���� ���� ����������, �� next ���������������� �� ���� ����, ���� ���, �� ������ ��������� ������ � ������
        ///� ���������� �������� ���� ���������� �� �����
        if (node->next)
        {
            node->next->pred = node->pred;
        }
        else
        {
            last = last->pred;
        } ///��� ��� ���� ������� ��������� �� ���������������� �� ����������, ���� ��� �� ���������, �� ��� ��������� � ������ �������
        size_of_map--;
    }

public:
    ///������������
    Map()
    {
        first = last = nullptr;
        size_of_map = 0;
    }

    Map(const X& key, const Y& val)
    {
        first = last = nullptr;
        size_of_map = 0;
        insert_(key, val);
    }
///����������
    void insert_(const X& key, const Y& val)
    {
        size_of_map++;
        MapNode* newNode = new MapNode{size_of_map, key, val, last, nullptr}; ///struct Map (1)
        if (!first)
        {
            first = newNode; ///���� ��� ������� ��������, �� ������ ����
        }
        if (last)
        {
            last->next = newNode; ///��� ���������� � ����� � ������ ���
        }
        last = newNode;
    }
///�������� �� �������
    void deleteInd(int id)
    {
        MapNode* it = first;
        while (it)
        {
            if (it->index == id)
            {
                deleteNode(it);
                return;
            }
            it = it->next;
        }
        cout << "No such index in map." << endl;
    }
    ///�������� �� �����
    void deleteKey(const X& key)
    {
        ///������ � �������, ���� �� ������ ���� � ������ ������
        MapNode* it = first;
        while (it)
        {
            if (it->key == key)
            {
                deleteNode(it);
                return;
            }
            it = it->next;
        }
        cout << "No such key in map!" << endl;
    }
    ///�������� �� ��������, ������� ������ ���������
    void deleteVal(const Y& val)
    {
        ///���������� � ������� ��� � ������� ����������
        MapNode* it = first;
        while (it)
        {
            if (it->value == val)
            {
                deleteNode(it);
                return;
            }
            it = it->next; ///�� ���� ���������
        }
        cout << "No such value in map!" << endl;
    }
///�������� ������ � ������ ������, �� � ������� �� ������������ map, ���� ���� �� ������ �� ������� ����� ����
    Y& operator[](const X& key)
    {
        MapNode* it = first;
        while (it)
        {
            if (it->key == key)
            {
                return it->value;
            }
            it = it->next;
        }
        cout << "No such key in map!" << endl;
    }
///���������� �� �������
    void findByID(X key)
    {
        MapNode* it = first;
        while (it)
        {
            if (it->key  == key)
            {
                cout << it->value << endl;
                return;
            }
            it = it->next;
        }
        cout << "No such key in map!" << endl;
    }
///���������� �� �����
    void findByKey(int index)
    {
        MapNode* it = first;
        while (it)
        {
            if (it->index == index)
            {
                cout << it->key <<endl;
                return;
            }
            it = it->next;
        }
        cout << "No such index in map!" << endl;
    }
///���������� �� ��������
    void findByVal(const Y& val)
    {
        MapNode* it = first;
        while (it)
        {
            if (it->value == val)
            {
                cout << it->key << endl;
                return;
            }
            it = it->next;
        }
        cout << "No such value in map!" << endl;
    }
///�����
    void print()
    {
        //� ������ ������
        if (from_first)
        {
            MapNode* it = first;
            while (it)
            {
                cout <<"# "<< it->index<< " Key:" << it->key << " Value: " << it->value << '\n';
                it = it->next;
            }
        }
        //� �����
        else
        {
            MapNode* it = last;
            while (it)
            {
                cout << "# "<< it->index<<" Key: " << it->key << " Value: " << it->value << '\n';
                it = it->pred;
            }
        }
    }
    ///��������� �� ������, � ������ ���������� ������, �� ��������
    void sort_by_key()
    {
        if (!first)
            return;

        bool swapped;
        do
        {
            swapped = false;
            MapNode* it = first;
            while (it && it->next)
            {
                ///���������� ����� � ��������� ��� �������������
                if (it->key > it->next->key || (it->key == it->next->key && it->value > it->next->value))
                {
                    swap(it->key, it->next->key);
                    swap(it->value, it->next->value);
                    swap(it->index, it->next->index);
                    swapped = true;
                }
                it = it->next;
            }
        }
        while (swapped);
    }

    ///��������� �� ���������, ��������� �����, ���� �������� ���������� ��������� �� ������
    void sort_by_val()
    {
        if (!first)
            return;

        bool swapped;
        do
        {
            swapped = false;
            MapNode* it = first;
            while (it && it->next)
            {
                /// ���������� ����
                if (it->value > it->next->value || (it->value == it->next->value && it->key > it->next->key))
                {
                    swap(it->key, it->next->key);
                    swap(it->value, it->next->value);
                    swap(it->index, it->next->index);
                    swapped = true;
                }
                it = it->next;
            }
        }
        while (swapped);
    }

///����� � �����, ����� ��������� � ����� ����������� ����, ������������� ���� ������ ������
    MapNode* begin_()
    {

        from_first = true;
    }

    MapNode* end_()
    {
        from_first = false;
    }
///������� ���, ����� ����� ���� ������������� ��� ����� .-.
    void sortInsert(const X& key, const Y& val)
    {
        size_of_map++;
        MapNode* newNode = new MapNode{size_of_map, key, val, nullptr, nullptr};
        /// ���� �����
        if (!first)
        {
            first = newNode;
            last = newNode;
            return;
        }
        /// ����� ��� ���������� ����� ���� ������ ��� ����� ����� ���������� ���� -> ��������� � �����
        if (last->key <= key)
        {
            last->next = newNode;
            newNode->pred = last;
            last = newNode;
            return;
        }
        /// ����������, ������ ���� ������ ��� �����, �� � ������
        if (key <= first->key)
        {
            first->pred = newNode;
            newNode->next = first;
            first = newNode;
            return;
        }
        /// ���� ������ ������� ���� � ������ ����� ���������� � ��������
        MapNode* left = first;
        MapNode* right = first->next;
        /// ���� ����� ����� ��� �������,/ �������� � ����
        while (left->key > key || key > right->key)
        {
            left = left->next;
            right = right->next;
        }
        /// ��������� ����� ���� ����� ���������� ������
        left->next = newNode; ///�������� ������ �� ������ ���� �� �����
        newNode->pred = left; /// �� ������ �� ����� ����
        right->pred = newNode; ///���� ����� ��� � ������
        newNode->next = right;
    }


///����������� ����
    int count()
    {
        return size_of_map;
    }

    ///������ � �������
    void saveToFile(const string& filename)
    {
        ofstream outFile(filename);
        if (!outFile)
        {
            cerr << "Error opening file for writing!" << endl;
            return;
        }

        MapNode* it = first;
        while (it)
        {
            outFile << it->key << " " << it->value << "\n";
            it = it->next;
        }

        outFile.close();
        cout << "Map saved to file successfully!" << endl;
    }

    ///�������� �� �����
    void loadFromFile(const string& filename)
    {
        ifstream inFile(filename);
        if (!inFile)
        {
            cerr << "Error opening file for reading!" << endl;
            return;
        }

        clear();
        X key;
        Y value;
        while (inFile >> key >> value)
        {
            insert_(key, value);
        }

        inFile.close();
        cout << "Map loaded from file successfully!" << endl;
    }
private:
    void clear()
    {
        MapNode* it = first;
        while (it)
        {
            MapNode* temp = it;
            it = it->next;
            delete temp;
        }
        first = last = nullptr;
        size_of_map = 0;
    }
};

void menu()
{
    cout << "******Please choose options:******\n";
    cout << "\t1 - Add \n";
    cout << "\t2 - Delete by key\n";
    cout << "\t3 - Delete by value\n";
    cout << "\t4 - Delete by index\n";
    cout << "\t5 - Print\n";
    cout << "\t6 - Begin\n";
    cout << "\t7 - End\n";
    cout << "\t8 - Search by index\n";
    cout << "\t9 - Search by key\n";
    cout << "\t10 - Search by value\n";
    cout << "\t11 - Size\n";
    cout << "\t12 - Sort by key\n";
    cout << "\t13 - Load from file\n";
    cout << "\t14 - Save to file \n";
    cout << "\t15 - Sort by value\n";
    cout << "\t16 - Exit\n";
    cout << "Choice:_\b ";
}
int main()
{
    Map<int, string> mp;
    int key,index;
    string value, s;
    bool b= true;
    int a;
    while (b)
    {
        menu();
        cin >> a;
        switch (a)
        {
        case 1:
        {
            cout << "Enter the key and the value:\n";
            cin >> key >> value;
            mp.insert_(key,value);
            break;
        }
        case 2:
        {
            cout << "Enter the key, which you want deleted:\n";
            cin >> key;
            mp.deleteKey(key);
            break;
        }
        case 3:
        {
            cout << "Enter the value, which you want deleted:\n";
            cin >> value;
            mp.deleteVal(value);
            break;
        }
        case 4:
        {
            cout << "Enter the index, which you want deleted:\n";
            cin >> index;
            mp.deleteInd(index);
            break;
        }
        case 5:
        {
            cout << "Your map:\n";
            mp.print();
            break;

        }
        case 6:
        {
            mp.begin_();
            break;

        }
        case 7:
        {
            mp.end_();
            break;
        }
        case 8:
        {
            cout << "Enter the index:\n";
            cin >> index;
            mp.findByID(index);
            break;
        }
        case 9:
        {
            cout << "Enter the key:\n";
            cin >> key;
            mp.findByKey(key);
            break;
        }
        case 10:
        {
            cout << "Enter the value:\n";
            cin >> value;
            mp.findByVal(value);
            break;
        }
        case 11:
        {
            cout << mp.count()<<endl;
            break;
        }
        case 12:
        {
            mp.sort_by_key();
            break;
        }
        case 13:
        {
            cout<<"Name of file: ";
            cin>>s;
            s=s+".txt";
            mp.loadFromFile(s);
            break;
        }
        case 14:
        {
            cout<<"Name of file: ";
            cin>>s;
            s=s+".txt";
            mp.saveToFile(s);
            break;
        }
        case 15:
        {
            mp.sort_by_val();
            break;
        }
        case 16:
        {
            cout<<"Exit...";
            b=false;
            break;
        }
        }

    }
    return 0;
}
