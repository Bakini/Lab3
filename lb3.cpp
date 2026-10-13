#include <iostream>
#include <string>
#include <limits>

struct node
{
    std::string inf;
    int prio;
    node *next;
};

struct spisok
{
    node *head = nullptr;
    node *last = nullptr;
    int dlina = 0;
};

spisok pq;
spisok q;
spisok st;

void clear_input()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

node *get_struct()
{
    node *p = new node;
    std::string s;
    std::cout << "Введите название объекта: ";
    if (!(std::cin >> s))
    {
        std::cout << "Запись не была произведена\n";
        clear_input();
        delete p;
        return nullptr;
    }
    p->inf = s;
    p->prio = 0;
    p->next = nullptr;
    return p;
}

void pq_push()
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
        clear_input();
        delete p;
        return;
    }
    if (pq.head == nullptr)
    {
        pq.head = p;
        pq.last = p;
    }
    else if (p->prio > pq.head->prio)
    {
        p->next = pq.head;
        pq.head = p;
    }
    else
    {
        node *struc = pq.head;
        while (struc->next != nullptr && struc->next->prio >= p->prio)
        {
            struc = struc->next;
        }
        p->next = struc->next;
        struc->next = p;
        if (p->next == nullptr)
        {
            pq.last = p;
        }
    }
    pq.dlina++;
    std::cout << "Добавлено по приоритету: " << p->inf << " (приоритет " << p->prio << ")\n";
}

void q_push()
{
    node *p = get_struct();
    if (p == nullptr)
    {
        return;
    }
    if (q.head == nullptr)
    {
        q.head = p;
        q.last = p;
    }
    else
    {
        q.last->next = p;
        q.last = p;
    }
    q.dlina++;
    std::cout << "Добавлено в конец очереди: " << p->inf << "\n";
}

void st_push()
{
    node *p = get_struct();
    if (p == nullptr)
    {
        return;
    }
    p->next = st.head;
    st.head = p;
    if (st.last == nullptr)
    {
        st.last = p;
    }
    st.dlina++;
    std::cout << "Положено на вершину стека: " << p->inf << "\n";
}

void spop(spisok &s)
{
    if (s.head == nullptr)
    {
        std::cout << "Пусто\n";
        return;
    }
    node *struc = s.head;
    std::cout << "Извлечено: " << struc->inf << " (приоритет " << struc->prio << ")\n";
    s.head = s.head->next;
    if (s.head == nullptr)
    {
        s.last = nullptr;
    }
    delete struc;
    s.dlina--;
}

void review(spisok &s)
{
    if (s.head == nullptr)
    {
        std::cout << "Пусто\n";
        return;
    }
    std::cout << "Элементов " << s.dlina << ":\n";
    node *struc = s.head;
    int i = 1;
    while (struc != nullptr)
    {
        std::cout << i << ") Имя - " << struc->inf << ", приоритет - " << struc->prio << "\n";
        struc = struc->next;
        i++;
    }
}

node *find(spisok &s, std::string name)
{
    if (s.head == nullptr)
    {
        std::cout << "Список пуст\n";
        return nullptr;
    }
    node *struc = s.head;
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

void del(spisok &s, std::string name)
{
    if (s.head == nullptr)
    {
        std::cout << "Список пуст\n";
        return;
    }
    node *struc = s.head;
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
                s.head = struc->next;
            }
            else
            {
                prev->next = struc->next;
            }
            if (struc == s.last)
            {
                s.last = prev;
            }
            struc = struc->next;
            delete dead;
            s.dlina--;
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

void clear(spisok &s)
{
    while (s.head != nullptr)
    {
        node *p = s.head;
        s.head = s.head->next;
        delete p;
    }
    s.last = nullptr;
    s.dlina = 0;
}

void menu()
{
    std::cout << "Приоритетная очередь (задание 1):\n";
    std::cout << "1 - добавить по приоритету\n";
    std::cout << "2 - извлечь (самый приоритетный)\n";
    std::cout << "3 - просмотр\n";
    std::cout << "4 - поиск по названию\n";
    std::cout << "5 - удаление по названию\n";
    std::cout << "Очередь (задание 2):\n";
    std::cout << "6 - добавить в конец\n";
    std::cout << "7 - извлечь из начала\n";
    std::cout << "8 - просмотр\n";
    std::cout << "Стек (задание 3):\n";
    std::cout << "9 - положить (push)\n";
    std::cout << "10 - снять (pop)\n";
    std::cout << "11 - просмотр\n";
    std::cout << "12 - показать меню\n";
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
            if (std::cin.eof())
            {
                break;
            }
            clear_input();
            std::cout << "Введите число (12 - показать меню)\n";
            cmd = -1;
            continue;
        }
        switch (cmd)
        {
        case 1:
            pq_push();
            break;
        case 2:
            spop(pq);
            break;
        case 3:
            review(pq);
            break;
        case 4:
            std::cout << "Введите название для поиска: ";
            std::cin >> name;
            p = find(pq, name);
            if (p != nullptr)
            {
                std::cout << "Найдено: " << p->inf << ", приоритет " << p->prio << "\n";
            }
            break;
        case 5:
            std::cout << "Введите название для удаления: ";
            std::cin >> name;
            del(pq, name);
            break;
        case 6:
            q_push();
            break;
        case 7:
            spop(q);
            break;
        case 8:
            review(q);
            break;
        case 9:
            st_push();
            break;
        case 10:
            spop(st);
            break;
        case 11:
            review(st);
            break;
        case 12:
            menu();
            break;
        case 0:
            std::cout << "Выход\n";
            break;
        default:
            std::cout << "Нет такого пункта (12 - показать меню)\n";
        }
    }
    clear(pq);
    clear(q);
    clear(st);
    return 0;
}
