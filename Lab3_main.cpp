#include <iostream>
#include <string>

struct node
{
    std::string inf;
    int prio;
    node *next;
};

node *head = nullptr;
node *last = nullptr;
int dlina = 0;

node *get_struct()
{
    node *p = new node;
    std::string s;
    std::cout << "Введите название объекта: ";
    if (!(std::cin >> s))
    {
        std::cout << "Запись не была произведена\n";
        delete p;
        return nullptr;
    }
    p->inf = s;
    p->prio = 0;
    p->next = nullptr;
    return p;
}

void spstore_prio()
{
    node *p = get_struct();
    if (p == nullptr)
    {
        return;
    }
    std::cout << "Введите приоритет (целое число): ";
    if (!(std::cin >> p->prio))
    {
        std::cout << "Запись не была произведена\n";
        delete p;
        return;
    }
    if (head == nullptr)
    {
        head = p;
        last = p;
    }
    else if (p->prio > head->prio)
    {
        p->next = head;
        head = p;
    }
    else
    {
        node *struc = head;
        while (struc->next != nullptr && struc->next->prio >= p->prio)
        {
            struc = struc->next;
        }
        p->next = struc->next;
        struc->next = p;
        if (p->next == nullptr)
        {
            last = p;
        }
    }
    dlina++;
    std::cout << "Добавлено по приоритету: " << p->inf << " (приоритет " << p->prio << ")\n";
}

void spstore()
{
    node *p = get_struct();
    if (p == nullptr)
    {
        return;
    }
    if (head == nullptr)
    {
        head = p;
        last = p;
    }
    else
    {
        last->next = p;
        last = p;
    }
    dlina++;
    std::cout << "Добавлено в конец: " << p->inf << "\n";
}

void spush()
{
    node *p = get_struct();
    if (p == nullptr)
    {
        return;
    }
    p->next = head;
    head = p;
    if (last == nullptr)
    {
        last = p;
    }
    dlina++;
    std::cout << "Добавлено в начало: " << p->inf << "\n";
}

void spop()
{
    if (head == nullptr)
    {
        std::cout << "Список пуст\n";
        return;
    }
    node *struc = head;
    std::cout << "Извлечено из начала: " << struc->inf << " (приоритет " << struc->prio << ")\n";
    head = head->next;
    if (head == nullptr)
    {
        last = nullptr;
    }
    delete struc;
    dlina--;
}

void review()
{
    if (head == nullptr)
    {
        std::cout << "Список пуст\n";
        return;
    }
    std::cout << "Список, элементов " << dlina << ":\n";
    node *struc = head;
    int i = 1;
    while (struc != nullptr)
    {
        std::cout << i << ") Имя - " << struc->inf << ", приоритет - " << struc->prio << "\n";
        struc = struc->next;
        i++;
    }
}

node *find(std::string name)
{
    if (head == nullptr)
    {
        std::cout << "Список пуст\n";
        return nullptr;
    }
    node *struc = head;
    while (struc != nullptr)
    {
        if (struc->inf == name)
        {
            return struc;
        }
        struc = struc->next;
    }
    std::cout << "Элемент не найден\n";
    return nullptr;
}

void del(std::string name)
{
    if (head == nullptr)
    {
        std::cout << "Список пуст\n";
        return;
    }
    node *struc = head;
    node *prev = nullptr;
    int flag = 0;
    while (struc != nullptr)
    {
        if (struc->inf == name)
        {
            node *dead = struc;
            flag = 1;
            if (prev == nullptr)
            {
                head = struc->next;
            }
            else
            {
                prev->next = struc->next;
            }
            if (struc == last)
            {
                last = prev;
            }
            struc = struc->next;
            delete dead;
            dlina--;
        }
        else
        {
            prev = struc;
            struc = struc->next;
        }
    }
    if (flag == 0)
    {
        std::cout << "Элемент не найден\n";
    }
    else
    {
        std::cout << "Удаление выполнено\n";
    }
}

void clear()
{
    while (head != nullptr)
    {
        node *p = head;
        head = head->next;
        delete p;
    }
    last = nullptr;
    dlina = 0;
}

void menu()
{
    std::cout << "1 - добавить по приоритету (задание 1)\n";
    std::cout << "2 - добавить в конец, очередь (задание 2)\n";
    std::cout << "3 - добавить в начало, стек (задание 3)\n";
    std::cout << "4 - извлечь из начала\n";
    std::cout << "5 - просмотр списка\n";
    std::cout << "6 - поиск по названию\n";
    std::cout << "7 - удаление по названию\n";
    std::cout << "8 - очистить список\n";
    std::cout << "0 - выход\n";
}

int main()
{
    int cmd = -1;
    std::string name;
    node *p = nullptr;
    menu();
    while (cmd != 0)
    {
        std::cout << "Пункт: ";
        if (!(std::cin >> cmd))
        {
            break;
        }
        switch (cmd)
        {
        case 1:
            spstore_prio();
            break;
        case 2:
            spstore();
            break;
        case 3:
            spush();
            break;
        case 4:
            spop();
            break;
        case 5:
            review();
            break;
        case 6:
            std::cout << "Введите название для поиска: ";
            if (!(std::cin >> name))
            {
                cmd = 0;
                break;
            }
            p = find(name);
            if (p != nullptr)
            {
                std::cout << "Найдено: " << p->inf << ", приоритет " << p->prio << "\n";
            }
            break;
        case 7:
            std::cout << "Введите название для удаления: ";
            if (!(std::cin >> name))
            {
                cmd = 0;
                break;
            }
            del(name);
            break;
        case 8:
            clear();
            std::cout << "Список очищен\n";
            break;
        case 9:
            menu();
            break;
        case 0:
            std::cout << "Выход\n";
            break;
        default:
            std::cout << "Нет такого пункта (9 - показать меню)\n";
        }
    }
    clear();
    return 0;
}